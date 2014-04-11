#include<stdio.h>
#include<string.h>
char s1[1001000],s2[10010];
int next[10010];
void getnext(){
	int i=1,j=0,k;
	next[1]=0;
	k=strlen(&s2[1]);
	while(i<=k){
		if(j==0 || s2[i]==s2[j]){
			i++,j++;
			next[i]=j;
		}
		else
			j=next[j];
	}
}
int kmp(){
	int i=1,j=1,sum=0,k1,k2;
	k1=strlen(&s1[1]);
	k2=strlen(&s2[1]);
	while(i<=k1){
		if(j==0 || s1[i]==s2[j])
			++i,++j;
		else
			j=next[j];
		if(j>k2){
			sum++;
			j=next[j];
		}
	}
	return sum;
}
int main(){
	int t,T;
	scanf("%d",&T);
	for(t=1;t<=T;t++){
		scanf("%s%s",&s2[1],&s1[1]);
		getnext();
		printf("%d\n",kmp());
	}
}
