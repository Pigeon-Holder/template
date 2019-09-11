ll mod;
struct mat
{
    ll a[2][2];
    mat(){mem(a,0);}
    void init(){a[0][0]=a[1][1]=1;}
    mat operator * (const mat &t) const
    {
        mat r;
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                for(int k=0;k<2;++k)
                    (r.a[i][j]+=a[i][k]*t.a[k][j]%mod)%=mod;
        return r;
    }
};
mat base[4];
char s[1000005];
mat qp(mat a)
{
    base[0]=a;
    for(int i=1;i<4;++i)
        base[i]=base[i-1]*base[i-1];
    mat res;
    res.init();
    int n=strlen(s);
    for(int i=n-1;~i;--i)
    {
        int v=s[i]-'0';
        for(int j=0;j<4;++j)
            if(v&(1<<j))
                res=res*base[j];
        base[0]=base[1]*base[3];
        for(int i=1;i<4;++i)
        base[i]=base[i-1]*base[i-1];
    }
    return res;
}
