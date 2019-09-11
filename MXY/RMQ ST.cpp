int a[100005];
int st[100005][30];
int len[100005];
void init(int n)
{
    for(int i=1;i<=n;++i)
        len[i]=log(i)/log(2);
    for(int i=1;i<=n;++i)
        st[i][0]=a[i];
    for(int j=1;(1<<j)<=n;++j)
        for(int i=1;i+(1<<j)-1<=n;++i)
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int query(int l,int r)
{
    int k=len[r-l+1];
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
