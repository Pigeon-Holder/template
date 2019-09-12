
const int maxn=2e5+5;
struct tr
{
    int ls,rs,v;
}t[maxn*300];
int root[maxn];
int a[maxn],b[2*maxn];
int ql[maxn],qr[maxn],qk[maxn],qo[maxn];
int cnt;
void init()
{
    cnt=0;
    mem(root,0);
}
void build(int l,int r,int &rt)
{
    t[rt].v=0;
    rt=++cnt;
    if(l==r)
        return;
    int m=(l+r)>>1;
    build(l,m,t[rt].ls);
    build(m+1,r,t[rt].rs);
}
void update(int p,int v,int l,int r,int lst,int &rt)
{
    t[++cnt]=t[lst];
    rt=cnt;
    t[rt].v+=v;
    if(l==r)
        return;
    int m=(l+r)>>1;
    if(m>=p)
        update(p,v,l,m,t[lst].ls,t[rt].ls);
    else
        update(p,v,m+1,r,t[lst].rs,t[rt].rs);
}
int le[maxn],ri[maxn],sl,sr;
int query(int k,int l,int r)
{
    if(l==r)
        return l;
    int m=(l+r)>>1,lv=0;
    for(int i=1;i<=sl;++i)
        lv-=t[t[le[i]].ls].v;
    for(int i=1;i<=sr;++i)
        lv+=t[t[ri[i]].ls].v;
    if(lv>=k)
    {
        for(int i=1;i<=sl;++i)
            le[i]=t[le[i]].ls;
        for(int i=1;i<=sr;++i)
            ri[i]=t[ri[i]].ls;
        return query(k,l,m);
    }
    else
    {
        for(int i=1;i<=sl;++i)
            le[i]=t[le[i]].rs;
        for(int i=1;i<=sr;++i)
            ri[i]=t[ri[i]].rs;
        return query(k-lv,m+1,r);
    }
}
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        assert(n<=100000&&m<=100000);
        init();
        int sz=0;
        for(int i=1;i<=n;++i)
            scanf("%d",a+i),b[++sz]=a[i];
        for(int i=1,l,r,k;i<=m;++i)
        {
            char s[2];
            scanf("%s",s);
            if(s[0]=='Q')
            {
                qo[i]=0;
                scanf("%d%d%d",&l,&r,&k);
                qk[i]=k,ql[i]=l,qr[i]=r;
            }
            else
            {
                qo[i]=1;
                scanf("%d%d",&l,&k);
                ql[i]=l;
                qk[i]=k;
                b[++sz]=k;
            }
        }
        sort(b+1,b+sz+1);
        sz=unique(b+1,b+sz+1)-b-1;
        for(int i=1;i<=sz;++i)
            a[i]=lower_bound(b+1,b+sz+1,a[i])-b;
        for(int i=1;i<=m;++i)
            if(qo[i])
                qk[i]=lower_bound(b+1,b+sz+1,qk[i])-b;
        for(int i=1;i<=n;++i)
        {
            for(int j=i;j<=n;j+=lowbit(j))
                update(a[i],1,1,sz,root[j],root[j]);
        }
        for(int i=1;i<=m;++i)
        {
            if(!qo[i])
            {
                sl=sr=0;
                for(int j=ql[i]-1;j;j-=lowbit(j))
                    le[++sl]=root[j];
                for(int j=qr[i];j;j-=lowbit(j))
                    ri[++sr]=root[j];
                printf("%d\n",b[query(qk[i],1,sz)]);
            }
            else
            {
                for(int j=ql[i];j<=sz;j+=lowbit(j))
                    update(a[ql[i]],-1,1,sz,root[j],root[j]);
                a[ql[i]]=qk[i];
                for(int j=ql[i];j<=sz;j+=lowbit(j))
                    update(a[ql[i]],1,1,sz,root[j],root[j]);
            }
        }
    }
}
