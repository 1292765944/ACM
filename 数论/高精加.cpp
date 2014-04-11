#include <cstdio>
#include <cstring>
int main()
{
	int  a[240] = {0}, b[240] = {0}, c[241] = {0};
	int  i, ka, kb, k;
	char  a1[240], b1[240];

	gets(a1);    ka = strlen(a1);
	gets(b1);    kb = strlen(b1);

	if(ka >= kb) k = ka;
	else k = kb;

	for(i = 0; i < ka; i++)  a[i] = a1[ka-i-1] - '0';
	for(i = 0; i < kb; i++)  b[i] = b1[kb-i-1] - '0';

	for(i = 0; i < k; i++){
		c[i] = a[i] + b[i] + c[i];
		c[i+1] = c[i+1] + c[i]/10;
		c[i] = c[i]%10;
	}

	if(c[k])  k++;

	for(i = k-1; i >= 0; i--)  printf("%d", c[i]);
	return 0;
}

