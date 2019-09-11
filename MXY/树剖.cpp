#include<bits/stdc++.h>
using namespace std;
#define mem(a,b) memset((a),b,sizeof((a)))
#define clr(v) (v).clear()
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define mp make_pair
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned long long
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define lowbit(i) (i&(-i))
#define lson rt<<1
#define rson lson|1
#define fi first
#define se second

const int maxn=1e5+5;
struct ed
{
    int to,nxt;
}e[maxn<<2];
int head[maxn];
int tot;
int fa[maxn],dep[maxn],siz[maxn],son[maxn],rk[maxn],top[maxn],id[maxn];
int cnt,n;
ll t[maxn<<2];
ll lzy[maxn<<2];
ll a[maxn],mod;
void init()
{
    mem(head,-1);
    tot=0;
    cnt=0;
}
void ae(int u,int v)
{
    e[tot]={v,head[u]};
    head[u]=tot++;
    e[tot]={u,head[v]};
    head[v]=tot++;
}
void dfs1(int u)
{
    dep[u]=dep[fa[u]]+1;
    siz[u]=1;
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v==fa[u])
            continue;
        fa[v]=u;
        dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int t)
{
    top[u]=t;
    id[u]=++cnt;
    rk[cnt]=u;
    if(!son[u])
        return;
    dfs2(son[u],t);
    for(int i=head[u];~i;i=e[i].nxt)
    {
        int v=e[i].to;
        if(v!=son[u]&&v!=fa[u])
            dfs2(v,v);
    }
}
void build(int l,int r,int rt)
{
    lzy[rt]=0;
    if(l==r)
    {
        t[rt]=a[rk[l]]%mod;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,lson);
    build(m+1,r,rson);
    t[rt]=(t[lson]+t[rson])%mod;
}
void pushdown(int l,int r,int rt)
{
    if(lzy[rt])
    {
        int m=(l+r)>>1;
        (lzy[lson]+=lzy[rt])%=mod;
        (lzy[rson]+=lzy[rt])%=mod;
        (t[lson]+=lzy[rt]*(m-l+1))%=mod;
        (t[rson]+=lzy[rt]*(r-m))%=mod;
        lzy[rt]=0;
    }
}
void update(int L,int R,ll k,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        t[rt]+=k*(r-l+1);
        lzy[rt]+=k;
        return;
    }
    pushdown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=R)
        update(L,R,k,l,m,lson);
    else if(m<L)
        update(L,R,k,m+1,r,rson);
    else
    {
        update(L,m,k,l,m,lson);
        update(m+1,R,k,m+1,r,rson);
    }
    t[rt]=(t[lson]+t[rson])%mod;
}
ll query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
        return t[rt];
    pushdown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=R)
        return query(L,R,l,m,lson)%mod;
    else if(m<L)
        return query(L,R,m+1,r,rson)%mod;
    else
        return (query(L,m,l,m,lson)+query(m+1,R,m+1,r,rson))%mod;
}
int lca(int x,int y)
{
    if(x==y)
        return x;
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy])
            x=fa[fx];
        else
            y=fa[fy];
        fx=top[x];
        fy=top[y];
    }
    if(id[x]<=id[y])
        return x;
    else
        return y;
}
ll sum(int x,int y)
{
    ll ans=0;
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy])
        {
            (ans+=query(id[fx],id[x],1,n,1))%=mod;
            x=fa[fx];
        }
        else
        {
            (ans+=query(id[fy],id[y],1,n,1))%=mod;
            y=fa[fy];
        }
        fx=top[x];
        fy=top[y];
    }
    /*
    基于边权:
    if(id[x]==id[y])
        return ans;
    else if(id[x]<id[y])
        ans+=query(id[x]+1,id[y],1,n,1);
    else
        ans+=query(id[y]+1,id[x],1,n,1);
    return ans;
    */
    //基于点权:
    if(id[x]<=id[y])
        (ans+=query(id[x],id[y],1,n,1))%=mod;
    else
        (ans+=query(id[y],id[x],1,n,1))%=mod;
    return ans;
}
void update_t(int x,int y,ll v)
{
    int fx=top[x],fy=top[y];
    while(fx!=fy)
    {
        if(dep[fx]>=dep[fy])
        {
            update(id[fx],id[x],v,1,n,1);
            x=fa[fx];
        }
        else
        {
            update(id[fy],id[y],v,1,n,1);
            y=fa[fy];
        }
        fx=top[x];
        fy=top[y];
    }
    /*
    基于边权:
    if(id[x]==id[y])
        return;
    else if(id[x]<id[y])
        update(id[x]+1,id[y],v,1,n,1);
    else
        update(id[y]+1,id[x],v,1,n,1);
    */
    if(id[x]<=id[y])
        update(id[x],id[y],v,1,n,1);
    else
        update(id[y],id[x],v,1,n,1);
}
int main()
{
    int q,rt;
    //节点数,询问数,根,取模
    while(~scanf("%d%d%d%lld",&n,&q,&rt,&mod))
    {
        init();
        for(int i=1;i<=n;++i)
            scanf("%lld",a+i);
        for(int i=1,u,v;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            ae(u,v);
        }
        dfs1(rt);
        dfs2(rt,rt);
        build(1,n,1);
        int op,x,y;
        ll v;
        while(q--)
        {
            scanf("%d",&op);
            if(op==1)
            {
                //x~y路径上的点加上v
                scanf("%d%d%lld",&x,&y,&v);
                update_t(x,y,v);
            }
            else if(op==2)
            {
                //x~y路径上的点求和
                scanf("%d%d",&x,&y);
                printf("%lld\n",sum(x,y));
            }
            else if(op==3)
            {
                //以x为根的子树的节点都加上v
                scanf("%d%lld",&x,&v);
                update(id[x],id[x]+siz[x]-1,v,1,n,1);
            }
            else if(op==4)
            {
                //以x为根的子树的和
                scanf("%d",&x);
                printf("%lld\n",query(id[x],id[x]+siz[x]-1,1,n,1));
            }
        }
    }

}
