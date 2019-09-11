struct LB
{
    ll base[64];
    int sz,tol;
    LB(){mem(base,0);sz=0;tol=0;}
    bool ins(ll v)
    {
        for(int i=63;~i;--i)
            if(v&(1LL<<i))
            {
                if(!base[i])
                {
                    base[i]=v;
                    ++tol;
                    ++sz;
                    return 1;
                }
                else
                    v^=base[i];
            }
        return 0;
    }
    void rebuild()
    {
        for(int i=63;~i;--i)
            for(int j=i-1;~j;--j)
                if(base[i]&(1LL<<j))
                    base[i]^=base[j];
    }
    ll kth(ll v,ll k)
    {
        if(k>=(1LL<<sz)||k<0)
            return -1;
        ll tp[64];
        int cnt=0;
        for(int i=0;i<64;++i)
            if(base[i])
                tp[cnt++]=base[i];
        for(int i=63;~i;--i)
            if(k&(1LL<<i))
                v^=tp[i];
        return v;
    }
    ll mx(ll v)
    {
        return kth(v,(1LL<<sz)-1);
    }
    ll rnk(ll v)
    {
        //整个序列中任选(可为空)，可组成的异或值，每个都出现pow(2,tol-sz)次
        ll r=0;
        for(int i=0;i<64;++i)
        {
            if(base[i])
                if(v&(1LL<<i))
                    r+=(1<<i);
        }
        return r;
    }
    LB join(const LB &t)
    {
        LB r;
        for(int i=0;i<64;++i)
            r.ins(base[i]),r.ins(t.base[i]);
        return r;
    }
    LB inner(const LB &t)
    {
        LB c=t,d=t,res;
        for(int i=63;~i;--i)
        {
            if(!base[i])
                continue;
            ll x=base[i],y=0;
            int j=i;
            for(;~j;--j)
            {
                if(x&(1LL<<j))
                {
                    if(c.base[j])
                        x^=c.base[j],y^=d.base[j];
                    else
                        break;
                }
            }
            if(x)
                c.base[j]=x,d.base[j]=y;
            else
                res.ins(y);
        }
        return res;
    }
    void show()
    {
        cout<<sz<<endl;
        for(int i=0;i<64;++i)
            if(base[i])
            cout<<i<<' '<<(bitset<50>)base[i]<<endl;
    }
};
