const ull mod=19260817;
const int maxn=1e5+5;
char s[maxn];
ull baze[maxn],ha[maxn];
void init(int n)
{
    baze[0]=1;
    for(int i=1;i<maxn;++i)
        baze[i]=baze[i-1]*mod;
    ha[0]=s[0];
    for(int i=1;i<n;++i)
        ha[i]=ha[i-1]*mod+s[i];
}
ull gethash(int l,int r)
{
    return ha[r]-ha[l-1]*baze[r-l+1];
}
ull change(int l,int r,int p,char v)
{
    ull res=ha[r]-ha[l-1]*baze[r-l+1];
    if(l<=p&&p<=r)
        res-=baze[r-p]*(s[p]-v);
    return res;
}
