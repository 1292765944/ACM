#include <cstdio>  
#include <cstring>  
#include <cstdlib>  
#include <cmath>  
  
const int MAXN = 1501000, N = 500010;  
  
int pn = 0, prime[MAXN], factor[MAXN];  
void get_prime(int n){  
    int i,j;  
    for(i=1;i<=n;i++)  
        factor[i]=i;  
    for(i=2;i<=n;i++){  
        if(i==factor[i])prime[pn++]=i;  
        for(j=0;j<pn && prime[j]*i<=n;j++){  
            factor[i*prime[j]]=prime[j];  
            if(i%prime[j]==0)  
                break;  
        }  
    }  
}  
  
int main()  
{  
    int cases;  
    get_prime(N);  
    scanf("%d", &cases);  
    while(cases--)  
    {  
        int n, tmpn;  
        long long ans = 1;  
        scanf("%d", &n);  
        tmpn = n;  
        while (tmpn != factor[tmpn])  
        {  
            long long fac = factor[tmpn], mtp = fac;  
            while (tmpn % fac == 0)  
            {  
                mtp *= fac;  
                tmpn /= fac;  
            }  
            ans *= (1 - mtp) / (1 - fac);  
        }  
        if (tmpn > 1)  
            ans *= (1 + tmpn);  
        ans -= n;  
        printf("%lld\n", ans);  
    }  
  
    return 0;  
}  
