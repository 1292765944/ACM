#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int gao(char *a,int len){
    int i=0,j=1,k=0;
    while(i<len && j<len && k<len){
        int cmp = a[(j+k)%len]-a[(i+k)%len];
        if(cmp==0)
            k++;
        else{
            if(cmp>0)
                j+=k+1;
            else
                i+=k+1;
            if(i==j)j++;
            k=0;
        }
    }
    return min(i,j);
}
int main(){
    char s[100];
    int len;
    while(scanf("%s",s)==1){
        len=strlen(s);
        printf("%d\n",gao(s,len));
    }
}

