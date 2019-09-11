const int maxn=1e5+5;
ll num[maxn<<3],lzy[maxn<<3];
void build(int l,int r,int rt)
{
    num[rt]=lzy[rt]=0;
    if(l==r)
        return;
    int m=(l+r)>>1;
    build(l,m,lson);
    build(m+1,r,rson);
}
void pushdown(int l,int r,int rt)
{
    if(lzy[rt])
    {
        int v=lzy[rt];
        num[lson]+=(v>>1);
        num[rson]+=v-(v>>1);
        lzy[lson]+=(v>>1);
        lzy[rson]+=v-(v>>1);
        lzy[rt]=0;
    }
}
//[L,R]区间的数每个增加v个
void update(int L,int R,int v,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        num[rt]+=v*(R-L+1);
        lzy[rt]+=v*(R-L+1);
        return;
    }
    pushdown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=R)
        update(L,R,v,l,m,lson);
    else if(m<L)
        update(L,R,v,m+1,r,rson);
    else
    {
        update(L,m,v,l,m,lson);
        update(m+1,R,v,m+1,r,rson);
    }
    num[rt]=num[lson]+num[rson];
}
//询问第k大
int query(int k,int l,int r,int rt)
{
    if(l==r)
        return l;
    pushdown(l,r,rt);
    int m=(l+r)>>1;
    if(k<=num[lson])
        return query(k,l,m,lson);
    else
        return query(k-num[lson],m+1,r,rson);
}
//询问[L,R]值域内的数量
int cnt(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R)
        return num[rt];
    pushdown(l,r,rt);
    int m=(l+r)>>1;
    if(m>=R)
        return cnt(L,R,l,m,lson);
    else if(m<L)
        return cnt(L,R,m+1,r,rson);
    else
        return cnt(L,m,l,m,lson)+cnt(m+1,R,m+1,r,rson);
}
