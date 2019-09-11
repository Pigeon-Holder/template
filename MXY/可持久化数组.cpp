const int maxn=1e6+5;
struct node
{
    int ls,rs;
    int v;
}t[maxn<<5];
int hd[maxn<<5];
int cnt=0;
int a[maxn];

void build(int l,int r,int &rt)
{
    rt=++cnt;
    if(l==r)
    {
        t[rt].v=a[l];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,t[rt].ls);
    build(m+1,r,t[rt].rs);
}

int query(int L,int R,int l,int r,int rt)
{
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

void update(int p,int v,int l,int r,int lst,int &rt)
{
    rt=++cnt;
    t[rt]=t[lst];
    if(l==r)
    {
        t[rt].v=v;
        return;
    }
    int m=(l+r)>>1;
    if(m>=p)
        update(p,v,l,m,t[lst].ls,t[rt].ls);
    else
        update(p,v,m+1,r,t[lst].rs,t[rt].rs);
}

