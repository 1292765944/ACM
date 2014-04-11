题意：给你n个钟的指针，第i个指针转一圈的时间是i单位，问你从n个钟任选一些指针使得，全部指针第一次回到原来的位置是经过的时间大于等于m，求又多少种选法。

显然时间是你选的指针的最小公倍数，但是好大，dp无从下手。看完神牛的题解才知道有一种dp叫做离散dp，就是直接保存有用的状态就好了，其他的不用，这样空间就可以满足了，因为其实状态数很少。

状态设定很简单：dp[i][j]：i表示以i指针结尾，最小公倍数（lcm）为j的方案数。

转移也很简单就是dp[i][j]=dp[i][j]+dp[i-1][j];

离散用了map，STL太强了，只能这么感慨，map要注意lcm的转移；还有初始状态为dp[i][i]=1;要在更新这个状态的时候加进去：

[cpp] view plaincopy



    #include<cstdio>  
    #include<cstring>  
    #include<string>  
    #include<iostream>  
    #include<algorithm>  
    #include<cmath>  
    #include<map>  
    #define LL long long  
    using namespace std;  
    LL m;int n;  
    typedef map <LL,LL> mp;  
    mp dp[45];  
    LL gcd(LL a,LL b)  
    {  
        return b==0?a:gcd(b,a%b);  
    }  
    LL lcm(LL a,LL b)  
    {  
        return a*b/gcd(a,b);  
    }  
    void DP()  
    {  
        //for(int i=1;i<=40;i++)  
            dp[1][1]=1;  
        for(int i=2;i<=40;i++)  
        {  
            dp[i]=dp[i-1];  
            dp[i][i]+=1;  
            for(mp::iterator j=dp[i-1].begin();j!=dp[i-1].end();j++)  
            {  
                LL lc=lcm(i,j->first);  
                dp[i][lc]+=j->second;  
            }  
        }  
    }  
    void ANS()  
    {  
        LL ans=0;  
        for(mp::iterator i=dp[n].begin();i!=dp[n].end();i++)  
            if(i->first>=m)ans+=i->second;  
        cout<<ans<<'\n';  
    }  
    int main()  
    {  
        int T,t;  
        DP();  
        scanf("%d",&T);  
        for(t=1;t<=T;t++)  
        {  
            cin>>n>>m;  
            printf("Case #%d: ",t);  
            ANS();  
        }  
        return 0;  
    }  
