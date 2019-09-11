const int maxn=1e6+1;
struct node
{
    int ls,rs;
    int mk;
    ll v;
    ll lzy;
}t[maxn*40];
int hd[maxn];
int tot=0;
int a[maxn];
void init()
{
    tot=0;
}
void build(int l,int r,int &rt)
{
    rt=++tot;
    t[rt].lzy=t[rt].mk=0;
    if(l==r)
    {
        t[rt].ls=t[rt].rs=0;
        t[rt].v=a[l];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,t[rt].ls);
    build(m+1,r,t[rt].rs);
    t[rt].v=t[t[rt].ls].v+t[t[rt].rs].v;
}
void pushdown(int l,int r,int rt)
{
    if(t[rt].lzy&&l<r)
    {
        int ls=++tot;
        t[ls]=t[t[rt].ls];
        t[rt].ls=ls;
        int rs=++tot;
        t[rs]=t[t[rt].rs];
        t[rt].rs=rs;
        int m=(l+r)>>1;
        t[ls].v+=t[rt].lzy*(m-l+1);
        t[rs].v+=t[rt].lzy*(r-m);
        t[ls].lzy+=t[rt].lzy;
        t[rs].lzy+=t[rt].lzy;
        t[rt].lzy=0;
    }
}
void update(ll v,int L,int R,int l,int r,int lst,int &rt)
{
    pushdown(l,r,lst);
    rt=++tot;
    t[rt]=t[lst];
    if(L<=l&&r<=R)
    {
        t[rt].v+=v*(r-l+1);
        t[rt].lzy+=v;
        return;
    }
    int m=(l+r)>>1;
    if(m>=R)
        update(v,L,R,l,m,t[lst].ls,t[rt].ls);
    else if(m<L)
        update(v,L,R,m+1,r,t[lst].rs,t[rt].rs);
    else
    {
        update(v,L,m,l,m,t[lst].ls,t[rt].ls);
        update(v,m+1,R,m+1,r,t[lst].rs,t[rt].rs);
    }
    t[rt].v=t[t[rt].ls].v+t[t[rt].rs].v;
}
ll query(int L,int R,int l,int r,int rt)
{
    pushdown(l,r,rt);
    if(L<=l&&r<=R)
        return t[rt].v;
    int m=(l+r)>>1;
    if(m>=R)
        return query(L,R,l,m,t[rt].ls);
    else if(m<L)
        return query(L,R,m+1,r,t[rt].rs);
    else
        return query(L,m,l,m,t[rt].ls)+query(m+1,R,m+1,r,t[rt].rs);
}
int main()
{
    int n,m;
    init();
    int ca=0;
    while(~scanf("%d%d",&n,&m))
    {
        ++ca;
        if(ca>1)
            puts("");
        for(int i=1;i<=n;++i)
            scanf("%d",a+i);
        int T=0;
        build(1,n,hd[0]);
        while(m--)
        {
            char op[3];
            int l,r,d;
            scanf("%s",op);
            if(op[0]=='C')
            {
                scanf("%d%d%d",&l,&r,&d);
                update(d,l,r,1,n,hd[T],hd[T+1]);
                ++T;
            }
            else if(op[0]=='Q')
            {
                scanf("%d%d",&l,&r);
                printf("%lld\n",query(l,r,1,n,hd[T]));
            }
            else if(op[0]=='H')
            {
                scanf("%d%d%d",&l,&r,&d);
                printf("%lld\n",query(l,r,1,n,hd[d]));
            }
            else if(op[0]=='B')
                scanf("%d",&T);
        }
    }
}
