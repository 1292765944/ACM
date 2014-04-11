#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
char s[100100],tmp[100100],str[20][20],temp[100100];
int dp[100100][20];
int n,l1,l2;
int pos,ans;
int cal(char * s1,char * s2,int len1,int len2){  //这里dp[i][j]表示s2的0~j的字串成为s1的0～i的字串最小距离
    int i,j;
    //memset(dp,0,sizeof(dp));           //被MEMSET卡了！！！！！！
    //for(int i=0;i<=l1;i++)  如果这四行加上，dp[i][j]表示的是s1串前i位与s2前j位的全部匹配的编辑距离  
    //{  
    //    dp[i][0] = i;  
    //}  
    for(i=0;i<=len2;i++)
        dp[0][i]=i;
    for(i=1;i<=len1;i++)
        for(j=1;j<=len2;j++){
            dp[i][j]=min(min(dp[i][j-1],dp[i-1][j])+1,dp[i-1][j-1]+(s1[i-1]!=s2[j-1]));
        }
    int tem=20;
    for(i=1;i<=len1;i++)
        tem=min(tem,dp[i][len2]);
    return tem;
}

