const int maxn=40010;
struct edge
{
    int to,nxt;
    ll v;
}e[maxn<<1];
int tot=0;
int head[maxn];
int st[maxn<<1][20];
int dep[maxn];
int q[maxn<<1];
int p[maxn];
ll d[maxn];
int id;
void init()
{
    tot=0;
    id=0;
    mem(st,0);
    mem(head,-1);
    mem(p,0);
    mem(q,0);
}
void ae(int u,int v,ll w)
{
     e[tot]={v,head[u],w};
    head[u]=tot++;
    e[tot]={u,head[v],w};
    head[v]=tot++;
}
void dfs(int rt,int fa,ll dis)
{
    p[rt]=++id;
    q[id]=rt;
    d[rt]=d[fa]+dis;
    for(int i=head[rt];~i;i=e[i].nxt)
    {
        if(e[i].to!=fa)
        {
            dep[e[i].to]=dep[rt]+1;
            dfs(e[i].to,rt,e[i].v);
            q[++id]=rt;
        }
    }
}
void rmq()
{
    for(int i=1;i<=id;++i)
        st[i][0]=q[i];
    for(int j=1;(1<<j)<=id;++j)
        for(int i=1;i+(1<<j)-1<=id;++i)
            if(dep[st[i][j-1]]<dep[st[i+(1<<(j-1))][j-1]])
                st[i][j]=st[i][j-1];
            else
                st[i][j]=st[i+(1<<(j-1))][j-1];
}
int lca(int u,int v)
{
    if(p[u]>p[v])
        swap(u,v);
    int k=log(p[v]-p[u]+1)/log(2);
    if(dep[st[p[u]][k]]<dep[st[p[v]-(1<<k)+1][k]])
        return st[p[u]][k];
    else
        return st[p[v]-(1<<k)+1][k];
}
ll dis(int u,int v)
{
    return d[u]+d[v]-d[fa]-d[fa];
}
