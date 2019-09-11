ll qp(ll x,char s[],ll mod)
{
    int n=strlen(s);
    ll base[4];base[0]=x%mod;
    for(int i=1;i<4;++i)
        base[i]=base[i-1]*base[i-1]%mod;
    ll res=1;
    for(int i=n-1;~i;--i)
    {
        int v=s[i]-'0';
        for(int j=0;j<4;++j)
            if(v&(1<<j))
                res=res*base[j]%mod;
        base[0]=base[1]*base[3]%mod;
        for(int j=1;j<4;++j)
            base[j]=base[j-1]*base[j-1]%mod;
    }
    return res%mod;
}
