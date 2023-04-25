#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

const int n = 4;
int m[n+1][n+1];
int s[n+1][n+1];
int num = 1;

void MatrixChain(int *p)
{
    for(int i = 1; i <= n; i++)
        m[i][i] = 0;    //把对角线置为0  单个矩阵不能相乘
    
    for(int r = 2; r <= n; r++) //r 为连乘矩阵的链长度
    {
        for(int i = 1; i <= n - r + 1; i++)
        {
            int j = i + r - 1;  //j为 长度为r的链的最后一个相乘的矩阵编号
            m[i][j] = m[i+1][j] + p[i-1]*p[i]*p[j];
            s[i][j] = i;    //记录断点
            for(int k = i+1; k < j; k++)
            {
                //计算每一个断点的 乘法次数， 然后在进行比较
                int temp = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if(temp < m[i][j])
                {
                    m[i][j] = temp;
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
    //int p[n+1] = {30,35,15,5,10,20,25}; 
    int p[n+1] = {50,10,40,30,5}; //存储着4个矩阵
    MatrixChain(p);
    trackback(1, n);
    printf("最少的计算次数： %d", m[1][n]);
}
/*
40*30*5 = 6000
10*40*5 = 2000
50*10*5 = 2500
*/
