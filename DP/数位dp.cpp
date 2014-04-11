/*
    求[1,n]内有多少个数字，该数字有13，且能被13整除   n<=10^9
    
    x % 13 = 0
    (pre*10^pos + next) % 13 = 0   pre是之前确定的部分
    需要的参数为pre , pos , 状态have
    have记录pre拥有"13"，pos+1位为"1"，没有"13"   分别用have = 2,1,0表示
    
    然后记忆化搜索

*/
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int dp[10][13][3];
int digit[10];

__int64 dfs(int pos , int pre , int have , bool doing)
{
    if(pos == -1)
        return have == 2 && pre == 0;

    if(!doing && dp[pos][pre][have] != -1)
        return dp[pos][pre][have];

    int ans = 0;
    int end = doing ? digit[pos] : 9;
    for(int i = 0 ; i <= end ; i ++)
    {
        int npre = (pre*10 + i) % 13;
        int nhave = have;
        if(have == 0 && i == 1)
            nhave = 1;
        else if(have == 1 && i != 1)
            nhave = 0;
        if(have == 1 && i == 3)
            nhave = 2;
        ans += dfs(pos-1 , npre , nhave , doing && i == end );
    }

    if(!doing)
        dp[pos][pre][have] = ans;
    return ans;
}


int cal(int x)
{
    int pos = 0;
    while(x)
    {
        digit[pos++] = x % 10;
        x /= 10;
    }
    return dfs(pos - 1 , 0 , 0 , 1);
}

int main()
{
    memset(dp,-1,sizeof(dp));
    int n;
    while(~scanf("%d",&n))
        printf("%d\n",cal(n));
    return 0;
}
