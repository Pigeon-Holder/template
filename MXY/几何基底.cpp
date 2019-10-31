皮克定理:整点多边形面积=内部点+边上点/2-1
struct point
{
    double x,y;point(){}point(const double &a,const double &b){x=a;y=b;}
    int quad()const
    {
        if(dcmp(x)==0&&dcmp(y)==0)
            return -1;
        if(dcmp(x)>=0&&dcmp(y)==1)
            return 1;
        if(dcmp(x)==1&&dcmp(y)<=0)
            return 2;
        if(dcmp(x)<=0&&dcmp(y)==-1)
            return 3;
        return 4;
    }
    point operator+(const point &t)const
    {
        return point(x+t.x,y+t.y);
    }
    point operator-(const point &t)const
    {
        return point(x-t.x,y-t.y);
    }
    //a*b=|a||b|cos(w)
    double operator*(const point &t)const
    {
        return x*t.x+y*t.y;
    }
    //a^b=|a||b|sin(w)
    double operator^(const point &t)const
    {
        return x*t.y-y*t.x;
    }
    double len()
    {
        return sqrt(x*x+y*y);
    }
    //逆时针
    point rot(const double &rad)const
    {
        double sn=sin(rad),cs=cos(rad);
        double tx=x*cs-y*sn,ty=x*sn+y*cs;
        if(dcmp(tx)==0)tx=0;
        if(dcmp(ty)==0)ty=0;
        return point(tx,ty);
    }
    bool operator==(const point &t)const
    {
        return dcmp(x-t.x)==0&&dcmp(y-t.y)==0;
    }
    //斜率无穷大到到无穷小
    bool operator<(const point &t)const
    {
        if(quad()==t.quad())
            return dcmp(*this^t)==-1;
        return quad()<t.quad();
    }/*
    bool operator<(const point &t)const
    {
        if(dcmp(x-t.x)==0)
            return y<t.y;
        return x<t.x;
    }*/
}p[1005];

struct line
{
    point a,b;line(){}line(const point &q,const point &w){a=q;b=w;}
    //斜率无穷大到无穷小，相同按靠左
    bool operator<(const line &t)const
    {
        point p1=b-a,p2=t.b-t.a;
        if(dcmp(p1^p2)==0)
            return a.x<t.a.x;
        return p1<p2;
    }
    //点在线段上
    bool on(const point &t)const
    {
        point p1=a-t,p2=b-t;
        return dcmp(p1^p2)==0&&dcmp(p2*p2/p1.len()/p2.len()+1)==0;
    }
    //两直线交点
    point ins(const line &t)const
    {
        point p1=b-a,p2=t.b-t.a;
        if(dcmp(p1^p2)==0)
            return point(1e15,1e15);
        double f=(t.a.x-a.x)*p1.y-(t.a.y-a.y)*p1.x;
        f/=(p1.x*p2.y-p1.y*p2.x);
        return point(t.a.x+f*p2.x,t.a.y+f*p2.y);
    };
    line rot(const double &rad)const
    {
        point p1=b-a;
        p1=p1.rot(rad);
        point p2=a+p1;
        return line(a,p2);
    }
    //投影点
    point prj(const point &t)const
    {
        point p1=b-a;p1=point(-p1.y,p1.x);
        line li=line(t,t+p1);
        p1=ins(li);
        return p1;
    }
    //对称点
    point sym(const point &t)const
    {
        point p1=prj(t);
        return point(2*p1.x-t.x,2*p1.y-t.y);
    }
    //点到线段距离
    double dis(const point &t)const
    {
        point p1=b-a,p2=t-a,p3=t-b;
        if(dcmp(p1*p2)<=0)
            return p2.len();
        if(dcmp(p1*p3)>=0)
            return p3.len();
        p1=prj(t);
        p1=p1-t;
        return p1.len();
    }
    //线段之间距离
    double dis(const line &t)const
    {
        point p1=ins(t);
        if(dcmp((p1-t.a).len()+(p1-t.b).len()-(t,a-t.b).len())==0)
            return 0;
        double ans=1e15;
        ans=min(ans,dis(t.a));
        ans=min(ans,dis(t.b));
        ans=min(ans,t.dis(a));
        ans=min(ans,t.dis(b));
        return ans;
    }
};
