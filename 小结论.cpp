#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main(){
    int mm[200],i,j;
    

    for(i=1;i<=100;i++){
        for(j=(i-1)&i;j;j=(j-1)&i)
            printf("%d %d  ",j,i-j);          //枚举i（二进制形式的i）的子集
    }
    
    for(i=1;i<=100;i++){
        for(j=(i-1)&i;j>=i/2 && j;j=(j-1)&i)
            printf("%d %d  ",j,i-j);         //枚举i（二进制形式的i）的子集的一半
    }
    
    for(i=1;i<=100;i++)
        printf("%d %d\n",i,(i)&(-i));        //即2进制数i中从最低位开始连续0的位数的关于2的幂
        

    mm[0]=-1;
    for(i=1;i<=100;i++)
        mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1]; //求log以2为底i的对数
}

