struct edge
{
    int to,nxt;
    ll v;
}e[1000005];
int tot=0;
int head[500005];
int fa[500005];
int dep[500005];
ll dis[400005];
int jmp[500005][20];
void init(int n)
{
    tot=0;
    for(int i=1;i<=n;++i)
    {
        dep[i]=0;
        dis[i]=0;
        head[i]=-1;
        for(int j=0;j<20;++j)
            jmp[i][j]=0;
    }
}
void ae(int u,int v,ll w)
{
    e[tot]={v,head[u],w};
    head[u]=tot++;
    e[tot]={u,head[v],w};
    head[v]=tot++;
}
void dfs(int rt,ll d)
{
    jmp[rt][0]=fa[rt];
    dis[rt]=dis[fa[rt]]+d;
    for(int i=1;i<20;++i)
        jmp[rt][i]=jmp[jmp[rt][i-1]][i-1];
    for(int i=head[rt];~i;i=e[i].nxt)
        if(e[i].to!=fa[rt])
        {
            int u=e[i].to;
            fa[u]=rt;
            dep[u]=dep[rt]+1;
            dfs(u,e[i].v);
        }
}
int lca(int u,int v)
{
    if(dep[u]>dep[v])
        swap(u,v);
    for(int i=19;~i;--i)
        if(dep[u]<=dep[jmp[v][i]])
            v=jmp[v][i];
    if(u==v)
        return v;
    for(int i=19;~i;--i)
        if(jmp[u][i]!=jmp[v][i])
        {
            u=jmp[u][i];
            v=jmp[v][i];
        }
    return jmp[u][0];
}
int dist(int u,int v)
{
    return dis[u]+dis[v]-dis[fa]-dis[fa];
}
