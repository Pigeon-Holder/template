const int maxn=1e5+5;
struct edge
{
    int to,nxt;
    ll w;
}e[maxn*2];
int head[maxn],tot;
void ae(int u,int v,ll w)
{
    e[tot]={v,head[u],w};
    head[u]=tot++;
    e[tot]={u,head[v],w};
    head[v]=tot++;
}
int fa[maxn][20];
int dep[maxn];
ll dis[maxn];
void dfs(int u,int f,ll w)
{

    cout<<u<<' '<<f<<' '<<w<<"?"<<endl;
    fa[u][0]=f;
    for(int i=1;i<20;++i)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    dis[u]=dis[f]+w;
    dep[u]=dep[f]+1;
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==f)
            continue;
        dfs(v,u,e[i].w);
    }
}
ll ds(int u,int v)
{
    ll res=dis[u]+dis[v];
    if(dep[u]>dep[v])
        swap(u,v);
    for(int i=19;~i;--i)
        if(dep[u]<=dep[fa[v][i]])
            v=fa[v][i];
    if(u==v)
        return res-2*dis[v];
    for(int i=19;~i;--i)
        if(fa[u][i]!=fa[v][i])
            u=fa[u][i],v=fa[v][i];
    return res-2*dis[fa[u][0]];
}
int col[maxn];
int le[maxn],ri[maxn];
void init()
{
    mem(head,-1);
    mem(le,0);
    mem(ri,0);
    tot=0;
}
int main()
{
    int n,q;
    while(~scanf("%d%d",&n,&q))
    {
        init();
        for(int i=1;i<=n;++i)
            scanf("%d",col+i);
        for(int i=1,u,v;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            ae(u,v,1);
        }
        dep[1]=1;dis[1]=0;
        dfs(1,0,0);
        for(int i=1;i<=n;++i)
        {
            int c=col[i];
            if(!le[c])
                le[c]=i;
            if(!ri[c])
            {
                ri[c]=i;
                continue;
            }
            ll d1=ds(le[c],ri[c]),d2=ds(le[c],i),d3=ds(ri[c],i);
            ll md=max(max(d1,d2),d3);
            if(md==d1)
                continue;
            else if(md==d2)
                ri[c]=i;
            else
                le[c]=i;
        }
        while(q--)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            ll d1=ds(le[a],le[b]),d2=ds(le[a],ri[b]),d3=ds(ri[a],le[b]),d4=ds(ri[a],ri[b]);
            printf("%lld\n",max(d1,max(d2,max(d3,d4))));
        }
    }
}
