#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int n;
const int maxn = 20;
int dp[maxn][maxn];
int s[maxn][maxn];
int sum[maxn][maxn];
int num =1;


void getMin()
{
    for(int i = 1; i <= n;i++)
        dp[i][i] = 0;
    
    for(int r = 2; r <= n; r++)
    {
        for(int i = 1; i <= n - r + 1; i++)
        {
            int j = i + r - 1;
            //dp[i][i] = 0 这里写出来是为了方便理解
            dp[i][j] = dp[i][i] + dp[i+1][j] + sum[i][j];  
            s[i][j] = i;
            for(int k = i+1; k < j; k++)
            {
                //比较不同断点k的 石子代价大小
                int temp = dp[i][k] + dp[k+1][j] + sum[i][k] + sum[k+1][j];
                if(temp < dp[i][j])
                {
                    dp[i][j] = temp;
                    s[i][j] = k;
                }
            }
        }
    }
}

void trackback(int i, int j)
{
    if(i == j)
        return ;
    trackback(i, s[i][j]);
    trackback(s[i][j] + 1, j);
    cout<<"第"<<num<< "步 ";
    cout<<"计算 A[" << i <<"," <<s[i][j];
    cout<<"] and A["<< (s[i][j] + 1) <<","<<j << "]"<<endl;
    num++;
}

int main()
{
    scanf("%d", &n);
    int p[n + 1];
    for(int i = 1; i <= n;i++)
    {
        scanf("%d", &p[i]);
        sum[i][i] = p[i];
    }
    //记录第i到第j的代价
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            sum[i][j] = sum[i][j-1] + p[j];
        }
    }
    getMin();
    
    /*
    打印出dp表格
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            printf("%3d", dp[i][j]);
        printf("\n");
    }
    */
   trackback(1, n);
   printf("总代价的最小值为: %d", dp[1][n]);
}
/*
3 4 = 7
7 6 = 13
4 2 = 6
5 6 = 11
13 11 = 24

*/