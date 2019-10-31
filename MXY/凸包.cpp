bool cmp2(const point &a,const point &b)
{
    if(a.x==b.x)
        return a.y<b.y;
    return a.x<b.x;
}
int Andrew(int n)
{
    sort(p,p+n,cmp2);
    int sz=0;
    for(int i=0;i<n;++i)
    {
        while(sz>1&&cross(p[i]-a[sz-2],p[i]-a[sz-1])<=eps)
            --sz;
        a[sz++]=p[i];
    }
    int tp=sz;
    for(int i=n-2;i>=0;--i)
    {
        while(sz>tp&&cross(p[i]-a[sz-2],p[i]-a[sz-1])<=eps)
            --sz;
        a[sz++]=p[i];
    }
    return --sz;
}
