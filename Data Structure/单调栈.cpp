1.POJ 2796
题意：找一个子序列。 使得这个序列的和乘以序列最小数最大。
分析：这是一个单调栈的问题，维护栈单调不减。
需要找到每个元素 最左能扩展到那 ，最右能扩展到那，当然最小的是你枚举的那个元素。
在单调栈中，我们知道栈顶元素是栈顶元素之前的最大值，现在只需要知道它向右扩展到哪里，当遇到比栈顶小的说明向右扩展到这里
#include<iostream>
#include<stdio.h>
using namespace std;
const int A=100005;
int st[A],elem[A];
long long sum[A];
int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&elem[i]);
			sum[i]=sum[i-1]+elem[i];
		}
		elem[n+1]=-1;
		long long ans=-1,tmp;
		int top=0,l,r;
		for(int i=1;i<=n+1;i++)
		{
			while(top!=0&&elem[st[top]]>elem[i])
			{
				tmp=elem[st[top]]*(sum[i-1]-sum[st[top-1]]);//栈顶元素是序列的最小元素
				if(ans<tmp)
				{
					ans=tmp;
					l=st[top-1]+1;
					r=i-1;
				}
				top--;
			}
			top++;
			st[top]=i;
		}
		printf("%lld\n%d %d\n",ans,l,r);
	}
}

2.求最大面积
样例：7 2 1 4 5 1 3 3（宽度均为1）
当我们扫扫描到第一个高度 H1 = 2的时候，我可以标记它的起始位置1， 因为我们还不知道它将向右扩展到什么地方，所以继续扫面。

当遇到第二项 H2 = 1, 因为这项比之前的小，我们知道，用H1做高度的长方形结束了，算出它的面积。

同时这个时候，我们多了一个高度H2，用它做长方形高度的长方形起始位置应该是在哪里呢？ 因为H1的高度比H2要高，所以这个起始位置自然是H1所在的位置。


为了模拟上面的过程，我们引入单调栈~

我们先定义我们我们要保存的每一项数据

struct Node

{

      int height;

      int startPosition;

};

用来描述某一个高度，和这个高度的起始位置。

然后我们按照高度来组织成单调栈。我们来看一下它是如何工作的。

为了不用考虑堆栈为空的情况，我们用插入栈底 一个高度（0， 0）的项。

数据： 

 2 1 4 5 1 3 3

这样初始化

(0 , 0)

I = 1

当扫描到(2， 1）时候，因为高度2 大于栈顶，插入

(0, 0),  (2, 1)

I = 2: 

当扫描到1的时候，因为1小于栈顶高度2， 我们认为栈顶的那个高度应不能再向右扩展了，所以我们将它弹出

这个时候扫描到 i = 2;

高度是 (i - 1(H1.startIndex)) * H1.height = 2;

我们得到一个面积是2的长方形。

同时我们发现高度是1的当前高度，可以扩展到 H1所在的下标，所以我们插入( 1, 1) 堆栈变成

(0, 0), (1, 1) 因为(2, 1)已经不能向右伸展了，已经被弹出了


i = 3

(0, 0), (1, 1), ( 4 3)

i = 4

(0, 0), (1, 1), (4, 3), (5, 4)

i = 5 

这个时候当前高度小于栈顶高度，我们认为栈顶已经不能向右扩展，所以弹出，并且获得面积 ( i  - H5.startindex) * H5.height = (5 - 4 ) * 5 = 5

弹出这个元素后，其实(4, 3)的高度也要比 1 大，所以把这个也弹出来，同样方式获得面积 8.

最后我们的堆栈是

(0, 0) , (1, 1)

i  = 6

(0, 0), (1, 1), ( 3, 6)

i = 7

(0, 0), (1, 1), (3, 6)

i = 8

最后一步是有点特殊的，因为我们必须要把所有的元素都弹出来，因为栈里面的高度，都坚持到了最后，我们要把这些高度组成的长方形拿出来检测。

我们可以假设扫面到8的时候，高度是0,（最小值）

弹出(3,6)获得面积 (8 - 6 ) * 3 = 6

弹出(1, 1)获得面积(8 - 1) * 1 = 7


最后的面积是8.

#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
using namespace std; 
struct point{
	int h;
	int w;
}stack[50005];
int main(){
	int n,i,curw,curh;
	while(scanf("%d",&n) && n!=-1){
		int lasth=0,top=0,ans=0;

		for(i=1;i<=n;i++){
			scanf("%d %d",&curw,&curh);
			if(curh>=lasth){
				stack[top].h=curh;
				stack[top++].w=curw;
			}
			else{
				int totw=0;
				while(top>0){
					if(stack[top-1].h>curh){
						if((totw+stack[top-1].w)*stack[top-1].h>ans)
							ans=(totw+stack[top-1].w)*stack[top-1].h;
						totw+=stack[top-1].w;
						top--;
					}
					else
						break;
				}
				stack[top].h=curh;
				stack[top++].w=totw+curw;
			}	
			lasth=stack[top-1].h;
		}
		int totw=0;
		while(top>0){
			if((totw+stack[top-1].w)*stack[top-1].h>ans)
				ans=(totw+stack[top-1].w)*stack[top-1].h;
			totw+=stack[top-1].w;
			top--;
		}
		printf("%d\n",ans);
	}
}
