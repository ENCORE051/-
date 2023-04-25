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
            //dp[i][i] = 0 ����д������Ϊ�˷������
            dp[i][j] = dp[i][i] + dp[i+1][j] + sum[i][j];  
            s[i][j] = i;
            for(int k = i+1; k < j; k++)
            {
                //�Ƚϲ�ͬ�ϵ�k�� ʯ�Ӵ��۴�С
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
    cout<<"��"<<num<< "�� ";
    cout<<"���� A[" << i <<"," <<s[i][j];
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
    //��¼��i����j�Ĵ���
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            sum[i][j] = sum[i][j-1] + p[j];
        }
    }
    getMin();
    
    /*
    ��ӡ��dp���
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
            printf("%3d", dp[i][j]);
        printf("\n");
    }
    */
   trackback(1, n);
   printf("�ܴ��۵���СֵΪ: %d", dp[1][n]);
}
/*
3 4 = 7
7 6 = 13
4 2 = 6
5 6 = 11
13 11 = 24

*/