基于Hadoop的协同过滤推荐算法实践

工程中主要包含两部分代码，采用的数据集为movielens的数据
 java部分：通过MR生成用户向量和项目共现矩阵，推荐矩阵
 cpp部分：验证，测试部分

用户向量：由于具有大量项目，所以项目-用户矩阵是个稀疏矩阵，为了节省空间，以记录条的形式存储该矩阵。
 每一行的格式为 {userID,{itemID 1 ,preference 1 },{itemID 2 ,preference 2 }...

项目共现矩阵：因为用户具有偏好性，可以用共现矩阵代替相似度矩阵，如果一个用户对两个项目的评分都为正分（分数>=4），
 则这两个项目共现

推荐矩阵：用户对项目的偏好值

