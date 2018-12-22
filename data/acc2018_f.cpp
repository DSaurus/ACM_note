#include<bits/stdc++.h>
using namespace std;
#define MAXN 200005
#define sqr(x) ((x)*(x))
typedef long long ll;
typedef pair<int,int> pii;
int n,t,last,sum[MAXN];
int query(int l,int r){
	cout<<"? "<<l<<" "<<r<<endl;
	cout.flush();
	int t;	cin>>t;
	int ret=((t-last)&1);
	last=t;
	return ret;
}
int main(){
	cin>>n>>t;
	last=sum[n]=t;
	if(n&1){
		for(int i=2;i<n;i++){
			int q[2]={};
			while(!q[i&1]||q[i&1^1])	q[query(i-1,i)]^=1;
			sum[i]=(sum[n]-last+i)/2;
			while(q[0]||q[1])	q[query(i-1,i)]^=1;
		}
		if(n>1){
			int q[2]={};
			while(!q[0]||q[1])	q[query(2,n)]^=1;
			sum[1]=sum[n]-(sum[n]-last+n-1)/2;
		}
	}
	else{
		for(int i=1;i<n;i++){
			int q[2]={};
			while(!q[i&1]||q[i&1^1])	q[query(i,i)]^=1;
			sum[i]=(sum[n]-last+i)/2;
			while(q[0]||q[1])	q[query(i,i)]^=1;
		}
	}
	cout<<"! ";
	for(int i=1;i<=n;i++)
		cout<<sum[i]-sum[i-1];
	cout<<endl;
	cout.flush();
	return 0;
}