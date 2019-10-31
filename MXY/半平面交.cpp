点向式直线，求所有直线左侧的公共部分
struct point
{
    double x,y;
    point(){}
    point(double _x,double _y){x=_x,y=_y;};
    point operator-(const point &t)const
    {
        return point(x-t.x,y-t.y);
    }
    point operator+(const point &t)const
    {
        return point(x+t.x,y+t.y);
    }
    point operator*(const double t)const
    {
        return point(x*t,y*t);
    }
};
double cross(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
struct line
{
    point p,v;
    line(){}
    line(point a,point b){p=a,v=b;}
};
bool cmp(line a,line b)
{
    return atan2(a.v.y,a.v.x)-atan2(b.v.y,b.v.x)<-eps;
}
bool onright(point p,line l)
{
    return cross(l.v, p-l.p)<=eps;
}
point ins(line a,line b)
{
    double t=cross(b.v,a.p-b.p)/cross(a.v,b.v);
    return point(a.p.x+t*a.v.x,a.p.y+t*a.v.y);
}
line l[100005];
point p[100005];
line q[100005];
int hpi(int n)
{
    sort(l,l+n,cmp);
    int h=0,t=0;
    q[t++]=l[0];
    for(int i=0;i<n;++i)
    {
        while(h+1<t&&onright(p[t-1],l[i]))
            --t;
        while(h+1<t&&onright(p[h+1],l[i]))
            ++h;
        q[t++]=l[i];
        if(fabs(cross(q[t-1].v,q[t-2].v))<=eps)
        {
            --t;
            if(onright(q[t-1].p,l[i]))
                q[t-1]=l[i];
        }
        if(h+1<t)
            p[t-1]=ins(q[t-1],q[t-2]);
    }
    while(h+1<t&&onright(p[t-1],q[h]))
        --t;
    if(t-(h+1)<=1)
        return 0;
    p[t]=ins(q[h],q[t-1]);
    int sz=0;
    for(int i=h+1;i<=t;++i)
        p[sz++]=p[i];
    return sz;
}
