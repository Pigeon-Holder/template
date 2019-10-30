const int maxn=1e5+5;
struct node
{
    int ls,rs,v;
}t[maxn*20];
int sz=0;
int hd[maxn];
void update(int p,int v,int l,int r,int lst,int &rt)
{
    t[++sz]=t[lst];
    rt=sz;
    ++t[rt].v;
    if(l==r)
        return;
    int m=(l+r)>>1;
    if(p<=m)
        update(p,v,l,m,t[lst].ls,t[rt].ls);
    else
        update(p,v,m+1,r,t[lst].rs,t[rt].rs);
}
int query(int v,int l,int r,int lst,int rt)
{
    if(l==r)
        return l;
    int num=t[t[rt].ls].v-t[t[lst].ls].v;
    int m=(l+r)>>1;
    if(num>=v)
        return query(v,l,m,t[lst].ls,t[rt].ls);
    else
        return query(v-num,m+1,r,t[lst].rs,t[rt].rs);
}
