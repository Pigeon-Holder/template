vector<int>p;
void gp(int n)
{
    for(int i=0;pr[i]*pr[i]<=n;++i)
    {
        if(n%pr[i]==0)
        {
            p.pb(pr[i]);
            while(n%pr[i]==0)
                n/=pr[i];
        }
    }
    if(n!=1)
        p.pb(n);
}
