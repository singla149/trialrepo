#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for(i=a;i<b;i++)
using namespace std;

FILE *f2=freopen("2.txt","w",stdout);
typedef pair<int,int> pii;
int main()
{
	int n,m;
	while(cin>>n>>m)
	{
		string s;
		int i,j,k;
		cin>>s;
		vector<int> adj[26];
		int done[26],waketim[26];memset(done,0,sizeof(done));
		done[s[0]-'A']=3;
		done[s[1]-'A']=3;
		done[s[2]-'A']=3;
		rep(i,1,m+1)
		{
			cin>>s;
			int x=s[0]-'A',y=s[1]-'A';
			adj[x].pb(y);adj[y].pb(x);
		}
		queue<pii> Q;
		rep(i,0,26 ) waketim[i]=0;
		rep(i,0,26) if(done[i]>=3)
		{
			waketim[i]=0;
			rep(j,0,adj[i].size())
			Q.push(mp(1,adj[i][j]));
		}
		int ans=0;
		while(Q.empty()==false)
		{
			pii P=Q.front();Q.pop();
			int waketime=P.first,index=P.second;
			if(done[index]>=3) continue;
			done[index]++;
			waketim[index]=max(waketim[index],waketime);
			if(done[index]>=3)
			{
				ans=max(ans,waketim[index]);
				rep(j,0,adj[index].size())
				Q.push(mp(waketim[index]+1,adj[index][j]));
			}
		}
		int cnt=0;
		rep(i,0,26) if(done[i]>=3) cnt++;
		if(cnt!=n)
		{
			cout<<"THIS BRAIN NEVER WAKES UP"<<endl;continue;
		}
		cout<<"WAKE UP YOUR DAD IN "<<ans<<" YEARS"<<endl;
	}
}
