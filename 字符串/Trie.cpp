1.Trie树构造
#include<cstdio>
#include<cstring>
#define MAXN 400003
#define SN 26
#define MAXL 300003
#define MOD 20071027
using namespace std;

struct Trie {
	Trie *s[SN];
	bool end;
	void clear() {
		memset(s, 0, sizeof(s));
		end=false;
	}
}trie[MAXN];

char str[MAXL], tmp[103];
int n, tot, dp[MAXL];

void insert() {
	Trie *cur=&trie[0];
	for(int i=0; tmp[i]; ++i) {
		int p=tmp[i]-'a';
		if(!cur->s[p]) {
			trie[tot].clear();
			cur->s[p]=&trie[tot++];
		}
		cur=cur->s[p];
	}
	cur->end=true;
}

int l;

void chk(int add,int jmp) {
	Trie *cur=&trie[0];
	for(int i=jmp;cur; ++i) {
		if(cur->end) {
			dp[i-1]=(dp[i-1]+add)%MOD;
		}
		if(i==l+1)return ;
		int p=str[i]-'a';
		cur=cur->s[p];
	}
}

int main() {

	for(int cas=1; scanf("%s",&str[1])!=EOF; ++cas) {
		scanf("%d", &n);
		trie[0].clear();
		tot=1;
		for(int i=0; i<n; ++i) {
			scanf("%s", tmp);
			insert();
		}
		memset(dp, 0, sizeof(dp));
		dp[0]=1;

		l=strlen(&str[1]);
		for(int i=1; i<=l; ++i) {
            if(dp[i-1])
                chk(dp[i-1],i);
		}
		printf("Case %d: %d\n", cas, dp[l]);
	}

	return 0;
}

