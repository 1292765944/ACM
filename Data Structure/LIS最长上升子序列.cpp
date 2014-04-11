1.最长上升子序列

#include <cstdio>
#define SIZE 1010
using namespace std;
int main()
{
    int i, j, n, top, temp;
    int s[SIZE];
    scanf("%d",&n);
    top = 0;
	s[0]=-1;
    for (i = 0; i < n; i++){
        scanf("%d",&temp);
		if (temp >s[top])
            s[++top] = temp;
        else{
            int low = 1, high = top;
            int mid;              //查找第一个大于等于temp的，因为要找单调增。 如果要求找单调不减的，要找第一个大于temp的
            while(low <= high)
            {
                mid = (low + high)>>1;
                if (temp>s[mid])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            s[low] = temp;
        }
    }
    printf("%d\n",top);
    return 0;
}

2.
题意：给出一个序列，问该序列的最长上升子序列的长度是多少，以及相同长度的，组成元素完全不同的最长上升子序列的个数。
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define INF 100000
#define MAXN 100000
int dp[MAXN],data[MAXN],mark[MAXN];
int main()
{
	int N,i,j,s,num,maxlen;
	while(scanf("%d",&N)!=EOF)
	{
		for(i=0;i<N;i++)
		{
			scanf("%d",&data[i]);
		}
		memset(mark,0,sizeof(mark));
		s=0;
		num=1;
		while(1)
		{
			memset(dp,1,sizeof(dp));
			maxlen=-INF;
			for(i=0;i<N;i++)
			{
				if(mark[i])continue;
				j=lower_bound(dp,dp+N,data[i])-dp;         //  如果是求最长单调不减序列，则此处换为upper_bound();
				dp[j]=data[i];
				if(j>maxlen)
				{
					maxlen=j;
					mark[i]=1;
				}
			}
			if(s<maxlen+1)s=maxlen+1;
			else if(s==maxlen+1)num++;
			else break;
		}
		printf("%d\n%d\n",s,num);
	}
	return 0;
}
