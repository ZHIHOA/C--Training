#include<iostream>
using namespace std;
#include<cmath>
#include<string>
int V[6][11];
int x[5];
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;	
} 
int KnapSack(int w[],int v[],int n,int C)
{
	int i,j;
	for(i=0;i<=n;i++)//初始化第0列 
		V[i][0]=0;
	for(j=0;j<=C;j++)//初始化第0行 
		V[0][j]=0;
	for(i=1;i<=n;i++)//计算第i行，进行第i次迭代 
	{
		for(j=1;j<=C;j++)
		{
			if(j<w[i-1])
				V[i][j]=V[i-1][j];
			else
				V[i][j]=max(V[i-1][j],V[i-1][j-w[i-1]]+v[i-1]);
		}
	}
	for(i=n,j=C;i>0;i--)//求装入背包的物品 
	{
		if(V[i][j]>V[i-1][j])
		{
			x[i-1]=1;
			j=j-w[i-1];
		}
		else
			x[i-1]=0;
	}
	return V[n][C];//返回背包取得的最大价值 
}
int main()
{
	int w[5]={2,2,6,5,4};
	int v[5]={6,3,5,4,6};
	cout<<"背包最大价值是："<<KnapSack(w,v,5,10)<<endl;
	cout<<"装入的物品分别是："; 
	for(int i=0;i<5;i++)
	{
		if(x[i]==1)
			cout<<"物品"<<i+1<<'\t';
	}
	return 0; 
}