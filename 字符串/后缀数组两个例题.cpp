HDU 4416   求的是两个串的所有不相同的公共字串的个数
void init(){  
    int i,j,nnn,n,tem;  
    scanf("%d",&nnn);  
    scanf("%s",r);  
    la=strlen(r);  
    r[la]='#';  
    tem=la+1;  
    for(i=1;i<=nnn;i++){  
        scanf("%s",&r[tem]);  
        n=strlen(&r[tem]);  
        r[n+tem]='#';  
        for(j=0;j<n;j++){  
            hhh[j+tem]=tem+n;  
            //printf("***%d := %d*****\n",tem+j,hhh[j+tem]);  
        }  
        tem+=n+1;  
        hhh[tem-1]=0;  
        //printf("***%d := %d*****\n",tem-1,hhh[tem-1]);  
    }  
    nn=tem;  
}  
void solve(int n){  
    long long sum=0;  
    int last=0,i,flag=0;  
    //printf("%s\n",r);  
    for(i=1;i<=n;i++){  
        if(sa[i]<la){  
            if(last==0){  
                sum+=la-sa[i]-min(height[i],la-sa[i]);  
                flag=sa[i]+min(height[i],la-sa[i])-1;  
            }  
            else if(last==1){  
                sum+=la-sa[i]-min(height[i],la-sa[i]);  
                flag=sa[i]+min(flag-sa[i-1]+1,min(height[i],la-sa[i]))-1;  
                /*if(min(height[i],la-sa[i])==0) 
                    flag=sa[i]-1; 
                else if(flag>sa[i]+min(height[i],la-sa[i])-1) 
                    flag=sa[i]+min(height[i],la-sa[i])-1;*/  
            }  
            last=1;  
        }  
        else{  
            if(last==1)  
                sum-=max(sa[i-1]+min(height[i],hhh[sa[i]]-sa[i])-1-flag,0);  
            last=0;  
        }  
        //printf("****%d %d %d %lld***\n",sa[i],min(height[i],hhh[sa[i]]-sa[i]),flag,sum);  
    }  
    printf("Case %d: %I64d\n",t,sum);  
}  
POJ 3415求的是两个串的所有公共字串的个数
int count(int num){  
    if(num<k) return 0;  
    else return num-k+1;  
}  
  
void solve(int n){  
    ll ans=0;  
    ll suma=0,sumb=0;  
    int sta[MAXN],top=0;  
    sta[0]=0;  
    ll ca[MAXN],cb[MAXN];  
    ca[1]=cb[1]=0;  
    for(int i=2;i<n;i++){  
        if(sa[i]<=la){  
            ca[i]=ca[i-1]+1;  
            cb[i]=cb[i-1];  
        }  
        else{  
            ca[i]=ca[i-1];  
            cb[i]=cb[i-1]+1;  
        }  
    }  
    for(int i=3;i<n;i++){  
        if(sa[i-1]<=la) suma+=(ll)count(height[i]);  
        else sumb+=(ll)count(height[i]);  
        sta[++top]=i-1;  
        while(top>=2 && height[sta[top]+1]<height[sta[top-1]+1]){  
            suma-=(ll)(count(height[sta[top-1]+1])-count(height[sta[top]+1]))*(ca[sta[top-1]]-ca[sta[top-2]]);  
            sumb-=(ll)(count(height[sta[top-1]+1])-count(height[sta[top]+1]))*(cb[sta[top-1]]-cb[sta[top-2]]);  
            sta[top-1]=sta[top--];  
        }  
        if(sa[i]<=la) ans+=sumb;  
        else ans+=suma;  
    }  
    printf("%lld\n",ans);  
}  

