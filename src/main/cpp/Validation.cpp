#include<cstdio>
#include<vector>
#include<string.h>
using namespace std;

#define USERN 80000
#define ITEMN 11000

struct UserPref{
	int itemID;
	float pref;
};
struct TestPref{
	int itemID;
	int pref;
};

int topN = 10;

int main(int argc, char* argv[]){
	FILE *ftest = fopen(argv[1],"r");
	FILE *fresult = fopen(argv[2],"r");
	
	if(argc == 4){
		topN = 0;
		int i = 0;
		while(argv[3][i] != '\0')
			topN = topN*10 + argv[3][i] - '0'; 
	}
	
	vector<struct UserPref> userPref[USERN];
	vector<struct TestPref> testPref[USERN];

	char *str = new char[400000];
	int userID,itemID;
	float pref;
	int i;
	while(fgets(str, 400000, fresult)){
		i = 0;
		userID = 0;
		while(str[i] != '\t')
			userID = userID * 10 + str[i++] - '0';
		i++;
		while(i < strlen(str) && str[i] != '\n'){
			itemID = 0;
			while(str[i] != ':')
				itemID = itemID * 10 + str[i++] - '0';
			i++;
			pref = 0;
			while(str[i] != '.')
				pref = pref * 10 + str[i++] - '0';
			i++;
			float base = 0.1;
			while(str[i] != ','){
				pref = pref + (str[i++] - '0') * base;
				base /= 10;   
			}
			i++;
			UserPref upref;
			upref.itemID = itemID;
			upref.pref = pref;
			userPref[userID].push_back(upref);
		}
	}

//	for(int i = 0; i < 50; i++)
//		printf("%d:%f\n",userPref[2][i].itemID,userPref[2][i].pref);
	int t;
	int ipref;	
	while(fscanf(ftest,"%d%d%d%d",&userID, &itemID, &ipref, &t) != EOF){
		TestPref tpref;
		tpref.itemID = itemID;
		tpref.pref = ipref;
		testPref[userID].push_back(tpref);
	}
		
	int numSum = 0, correctSumP = 0, correctSumR = 0;

	int predictPref;
	int userItem[11000];
	int stepLen;
	for(int i = 0; i < 11000; i++)
		userItem[i] = -1;

	for(int i = 0; i < USERN; i++)
		if(testPref[i].size() > 0){
			numSum += testPref[i].size();
			for(int j = 0; j < testPref[i].size(); j++)
				userItem[testPref[i][j].itemID] = testPref[i][j].pref;
			
			stepLen = userPref[i].size() / 5;
		
			for(int j = 0; j < userPref[i].size(); j++){
				itemID = userPref[i][j].itemID;
				if(userItem[itemID]>0){
					if(userPref[i][j].pref >= 0.9) predictPref = 5;
					else if(0.6 <= userPref[i][j].pref && userPref[i][j].pref < 0.9) predictPref = 4;
					else if(0.4 <= userPref[i][j].pref && userPref[i][j].pref < 0.6) predictPref = 3;
					else if(0.2 <= userPref[i][j].pref && userPref[i][j].pref < 0.4) predictPref = 2;
					else predictPref = 1;
					if(predictPref == userItem[itemID]) correctSumP++;
					
					if(j < stepLen) predictPref = 5;
					else if(stepLen <= j && j < 2*stepLen) predictPref = 4;
					else if(2*stepLen <= j && j < 3*stepLen) predictPref = 3;
					else if(3*stepLen <= j && j < 4*stepLen) predictPref = 2;
					else predictPref = 1;			
					if(predictPref == userItem[itemID]) correctSumR++;
				}
			}

			for(int j = 0; j < testPref[i].size(); j++)
				userItem[testPref[i][j].itemID] = -1;		
		}
	printf("numSum:%d\ncorrectSumP:%d\ncorrectSumR:%d\n",numSum,correctSumP,correctSumR);	
	printf("correctSumP:%f\ncorrectSumR:%f\n",(float)correctSumP/numSum, (float)correctSumR/numSum);

	return 0;
}
