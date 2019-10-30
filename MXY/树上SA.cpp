const int maxn=5e5+5;
char s[maxn];
int t[maxn],fir[maxn],sec[maxn],id[maxn],tp[maxn],sa[maxn],fa[maxn];
void bsort(int n,int m,int fir[],int sec[],int res[])
{
    for(int i=1;i<=m;++i)
        t[i]=0;
    for(int i=1;i<=n;++i)
        ++t[fir[i]];
    for(int i=1;i<=m;++i)
        t[i]+=t[i-1];
    for(int i=n;i;--i)
        res[t[fir[sec[i]]]--]=sec[i];
}
void getsa(int n,int m)
{
    //mem(fir,0);mem(sec,0);mem(sa,0);mem(t,0);
    for(int i=1;i<=n;++i)
        fir[i]=s[i],sec[i]=i;
    bsort(n,128,fir,sec,sa);
    for(int i=1;i<=n;++i)
        id[sa[i]]=i;
    for(int k=1;k<n;k<<=1)
    {
        for(int i=1;i<=n;++i)
            tp[i]=id[fa[i]];
        bsort(n,n,tp,sa,sec);
        bsort(n,m,fir,sec,sa);
        swap(fir,sec);
        id[sa[1]]=fir[sa[1]]=m=1;
        for(int i=2;i<=n;++i)
        {
            fir[sa[i]]=(sec[sa[i]]==sec[sa[i-1]]&&sec[fa[sa[i]]]==sec[fa[sa[i-1]]])?m:++m;
            id[sa[i]]=i;
        }
        bool ok=0;
        for(int i=n;i;--i)
            fa[i]=fa[fa[i]],ok|=fa[i];
        if(!ok)
            break;
    }
}
由自己的串决定大小
否则由父亲的串决定大小
否则以编号从小到大决定
