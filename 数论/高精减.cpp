#include <cstdio>
#include <cstring>
int main()
{
	int a[240]={0}, b[240]={0};
	int  i, ka, kb;
	char  a1[240], b1[240];

	gets(a1);      ka = strlen(a1);
	gets(b1);      kb = strlen(b1);

	for(i = 0; i < ka; i++)  a[i] = a1[ka-i-1] - '0';
	for(i = 0; i < kb; i++)  b[i] = b1[kb-i-1] - '0';

	for(i = 0; i < ka; i++){
		if(a[i] < b[i]){
			a[i + 1]--;
			a[i]+=10;
		}
		a[i] = a[i] - b[i];
	}

	while(!a[ka - 1]){
		ka--;
		if(!ka)  {printf("0"); break;}
	}

	for(i = ka-1; i >= 0; i--)  printf("%d", a[i]);
	return 0;
}

