sg博弈

首先写个SG打表程序

[cpp] view plaincopy

    #include<cstdio>  
    #include<stdlib.h>  
    #include<cstring>  
    #include<queue>  
    using namespace std;  
    int sg[110],k;  
    int find(int i){  
        if(sg[i]!=-1)return sg[i];  
        int use[100],j;  
        memset(use,0,sizeof(use));  
        for(j=1;j<=i;j*=k)  
            use[find(i-j)]=1;  
        j=0;  
        while(use[j])j++;  
        return sg[i]=j;  
    }  
    int main(){  
        int n,i;  
        scanf("%d",&k);  
        memset(sg,-1,sizeof(sg));  
        for(i=1;i<=100;i++){  
            printf("%d %d\n",i,find(i));  
        }  
    }  


然后可以发现规律，当k为奇数时，1，0，1，0，1，0。。。。这样变化，故n为奇数只需移走1个石头，而n为偶数必败

当k为偶数时，SG表是一个k+1的循环，比如k=4时，1，0，1，2，0，1，0，1，2，0.。。。故分析可知sg值为0的必败，sg值为1的只需要移走1个石头，sg值为2时，如果移走一个，则走到sg为1的点上还是必败，而移动k个石子易知可到达必胜态

AC程序

[cpp] view plaincopy

    #include<cstdio>  
    #include<stdlib.h>  
    #include<cstring>  
    #include<queue>  
    using namespace std;  
      
    int main(){  
        int i,t,T,k,s;  
        scanf("%d",&T);  
        for(t=1;t<=T;t++){  
            scanf("%d %d",&s,&k);  
            if(k&1){  
                if(s&1)printf("1\n");  
                else printf("0\n");  
            }  
            else{  
                int tem=s%(k+1);  
                if(tem==k)printf("%d\n",k);  
                else{  
                    if(tem&1)printf("1\n");  
                    else printf("0\n");  
                }  
            }  
        }  
    }  



如这就是一个阶梯博弈的初始状态 2 1 3 2 4 ... 只能把后面的点往前面放...如何来分析这个问题呢...其实阶梯博弈经过转换可以变为Nim..把所有奇数阶梯看成N堆石子..做nim..把石子从奇数堆移动到偶数堆可以理解为拿走石子..就相当于几个奇数堆的石子在做Nim..( 如所给样例..2^3^4=5 不为零所以先手必败)为什么可以这样来转化？
   假设我们是先手...所给的阶梯石子状态的奇数堆做Nim先手能必胜...我就按照能赢的步骤将奇数堆的石子移动到偶数堆...如果对手也是移动奇数堆..我们继续移动奇数堆..如果对手将偶数堆的石子移动到了奇数堆..那么我们紧接着将对手所移动的这么多石子从那个偶数堆移动到下面的奇数堆...两次操作后...相当于偶数堆的石子向下移动了几个..而奇数堆依然是原来的样子...即为必胜的状态...就算后手一直在移动偶数堆的石子到奇数堆..我们就一直跟着他将石子继续往下移..保持奇数堆不变...如此做下去..我可以跟着后手把偶数堆的石子移动到0..然后你就不能移动这些石子了...所以整个过程..将偶数堆移动到奇数堆不会影响奇数堆做Nim博弈的过程..整个过程可以抽象为奇数堆的Nim博弈...
   其他的情况...先手必输的...类似推理...只要判断奇数堆做Nim博弈的情况即可...
   为什么是只对奇数堆做Nim就可以...而不是偶数堆呢？...因为如果是对偶数堆做Nim...对手移动奇数堆的石子到偶数堆..我们跟着移动这些石子到下一个奇数堆...那么最后是对手把这些石子移动到了0..我们不能继续跟着移动...就只能去破坏原有的Nim而导致胜负关系的不确定...所以只要对奇数堆做Nim判断即可知道胜负情况...


