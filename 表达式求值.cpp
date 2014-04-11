#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
#define N 1000100
typedef long long ll;
using namespace std;

char s[N];
int len;
vector<char>out;
stack<char>sta;
const int mod=1000000007;

void gotOper(char opThis,int prec1){
	while(!sta.empty()){
		char opTop=sta.top();
		sta.pop();
		if(opTop=='('){
			sta.push(opTop);
			break;
		}
		else{
			int prec2;
			if(opTop=='|') prec2=1;
			if(opTop=='&') prec2=2;
			if(opTop=='~') prec2=3;
			if(prec2<prec1){
				sta.push(opTop);
				break;
			}
			else out.push_back(opTop);
		}
	}
	sta.push(opThis);
}

void gotParen(char ch){
	while(!sta.empty()){
		char ch=sta.top();
		sta.pop();
		if(ch=='(') break;
		else out.push_back(ch);
	}
}

void cal(){
	while(!sta.empty()) sta.pop();
	out.clear();
	for(int i=0;i<len;i++){
		if(s[i]=='(') sta.push('(');
		else if(s[i]=='~') sta.push('~');
		else if(s[i]=='|') gotOper('|',1);
		else if(s[i]=='&') gotOper('&',2);
		else if(s[i]==')') gotParen(')');
		else if(s[i]=='x') out.push_back('1');
	}
	while(!sta.empty()) out.push_back(sta.top()),sta.pop();
	//for(int i=0;i<out.size();i++) printf("%c ",out[i]);
	//puts("");
}

stack<pair<int,int> >st;

void cal2(){
	while(!st.empty()) st.pop();
	for(int i=0;i<out.size();i++){
		if(out[i]=='1') st.push(make_pair(1,1));
		else if(out[i]=='~'){
			pair<int,int>tmp;
			tmp=st.top();
			st.pop();
			st.push(make_pair(tmp.second,tmp.first));
		}
		else if(out[i]=='|'){
			pair<int,int>tmp1,tmp2;
			tmp1=st.top();
			st.pop();
			tmp2=st.top();
			st.pop();
			st.push(make_pair((((ll)tmp1.first+tmp1.second)%mod*((ll)tmp2.first+tmp2.second)%mod-(ll)tmp1.second*tmp2.second%mod+mod)%mod,(ll)tmp1.second*tmp2.second%mod));
		}
		else if(out[i]=='&'){
			pair<int,int>tmp1,tmp2;
			tmp1=st.top();
			st.pop();
			tmp2=st.top();
			st.pop();
			st.push(make_pair((ll)tmp1.first*tmp2.first%mod,(((ll)tmp1.first+tmp1.second)%mod*((ll)tmp2.first+tmp2.second)%mod-(ll)tmp1.first*tmp2.first%mod+mod)%mod));
		}
	}
	printf("%d\n",st.top().first);
}

int main(){
	scanf("%s",s);
	len=strlen(s);
	cal();
	cal2();
    return 0;
}
