给你一个数字序列arr，再给一个数字序列brr，arr和brr中的数字都是1到s（s<=25)。每个序列里的数字都有个排名，也就是第几小，现在我们要用arr来匹配brr，在本题中匹配的意思，每个数字的排名都一样，即同是第k小，最后输出匹配的所有位置，一行一个位置。
#include<stdio.h>
#include<string.h>
int a[100010],b[25010];
int c[30];                //树状数组中的元素
int m1[25010],m2[25010];  //（匹配串中）m1表示小于，m2表示小于等于
int n,k,s;
int next[25010];
int pop[100010],all;
int lowbit(int x){
	return x&(x^(x-1));
}
int sum(int x){
	int ss=0;
	while(x>0){
		ss+=c[x];
		x-=lowbit(x);
	}
	return ss;
}
void update(int x,int val){
	while(x<=s){
		c[x]+=val;
		x+=lowbit(x);
	}
}
void getnext(){
	int i=1,j=0,kk;
	next[1]=0;
	while(i<=k){
		if(j==0 || (sum(b[i]-1)==m1[j] && sum(b[i])==m2[j])){
			i++,j++;
			next[i]=j;
			if(i==k+1) return ;
			update(b[i],1);
		}
		else{
            for(kk=i-j+1;kk<=i-next[j];kk++)        //这里对next[j]之前的b[i]都要消除
				update(b[kk],-1);
			j=next[j];
        }
	}
} 
int kmp(){                //这里对待匹配串用树状数组记录
	int i=1,j=1,f;
	update(a[1],1);
	while(i<=n){
		if(j==0 ||(sum(a[i]-1)==m1[j] && sum(a[i])==m2[j])){
			++i,++j;
			if(i<=n)
				update(a[i],1);
		}
		else{
			for(f=i-j+1;f<=i-next[j];f++)
				update(a[f],-1);
			j=next[j];
		}
		if(j>k){
			for(f=i-j+1;f<=i-next[j];f++)
				update(a[f],-1);
			all++;
			pop[all]=i-1;
			j=next[j];
		}
	}
	return all;
}
int main(){
	int i,j;
	scanf("%d %d %d",&n,&k,&s);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);

	memset(c,0,sizeof(c));
	memset(m1,0,sizeof(m1));
	memset(m2,0,sizeof(m2));

	for(i=1;i<=k;i++){
		scanf("%d",&b[i]);
		update(b[i],1);
		m1[i]=sum(b[i]-1);
		m2[i]=sum(b[i]);
	}

	memset(c,0,sizeof(c));
	getnext();

	memset(c,0,sizeof(c));
	printf("%d\n",kmp());
	for(i=1;i<=all;i++)
		printf("%d\n",pop[i]+1-k);
}
