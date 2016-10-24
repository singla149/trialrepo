#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pdd pair<double,double>
#define X first
#define Y second
#define REP(i,a) for(int i=0;i<a;++i)
#define REPP(i,a,b) for(int i=a;i<b;++i)
#define FILL(a,x) memset(a,x,sizeof(a))
#define foreach( gg,itit )  for( typeof(gg.begin()) itit=gg.begin();itit!=gg.end();itit++ )
#define mp make_pair
#define pb push_back
#define all(s) s.begin(),s.end()
#define present(c,x) ((c).find(x) != (c).end())
const double EPS = 1e-8;
const int mod = 1e9+7;
const int N = 1e6+10;
const ll INF = 1e18;

ll power(ll x,ll y)
{
    ll t=1;
    while(y>0)
    {
        if(y%2) y-=1,t=t*x%mod;
        else y/=2,x=x*x%mod;
    }
    return t;
}
#ifdef DEBUG
#define dprintf(fmt,...) fprintf(stderr,fmt,__VA_ARGS__)
#else
#define dprintf(fmt,...)
#endif
int ct[4][105];
map<char,int> M;
int dp[105][4*4*4*4];
vector<int> ctl(int x)
{
    vector<int> a;
    REP(i,4) a.pb(x%4),x/=4;
    return a;
}
int ctb(vector<int> a)
{
    int x=0;
    for(int i=3; i>=0; i--) x=x*4+a[i];
    return x;
}
int main()
{
    M['y']=0;
    M['r']=1;
    M['g']=2;
    M['b']=3;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        FILL(ct,0);
        scanf("%d",&n);
        REP(i,n)
        {
            char s[10];
            scanf("%s",s);
            int p=strlen(s);
            int pl=0;
            REP(j,p) if(s[j]>='0'&&s[j]<='9')
            {
                pl=pl*10+s[j]-'0';
            }
            else break;
            ct[M[s[p-1]]][pl]++;
        }
        FILL(dp,-1);
        int ans=0;
        dp[0][0]=0;
        REP(i,102) REP(j,256)if(dp[i][j]!=-1)
        {
            ans=max(ans,dp[i][j]);
            vector<int> a = ctl(j);
            {
                vector<int> b=a;
                REP(k,4) if(ct[k][i]==0) b[k]=0;
                else b[k]++;
                int cst=dp[i][j];
                REP(k,4) if(b[k]==3)
                {
                    cst+=i+i-1+i-2;
                }
                else if(b[k]==4)
                {
                    cst+=i;
                    b[k]--;
                }
                int pp=ctb(b);
                dp[i+1][pp]=max(dp[i+1][pp],cst);
            }
            int f=0;
            REP(k,4) if(ct[k][i]==0) f=1;
            if(f==0)
            {
                dp[i+1][0]=max(dp[i+1][0],dp[i][j]+4*i);
            }
            REP(k,4)
            {
                int f=0;
                REP(l,4) if(l!=k) if(ct[l][i]==0) f=1;
                if(f==1) continue;
                vector<int> b=a;
                REP(l,4) if(l!=k) b[l]=0;
                int cst=dp[i][j]+3*i;

                if(ct[k][i]==0)
                {
                    b[k]=0;
                }
                else
                {
                    b[k]++;
                    if(b[k]==3) cst+=i+i-1+i-2;
                    else if(b[k]==4) cst+=i,b[k]--;
                }
                int pp=ctb(b);
                dp[i+1][pp]=max(dp[i+1][pp],cst);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
