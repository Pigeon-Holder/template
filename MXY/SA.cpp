不同子串个数：
对于一个后缀sa[i]，它产生了n-sa[i]个前缀，减去height[i]个相同的前缀(与前一个比较)
则产生了n-sa[i]-height[i]个子串
for(int i=1;i<=N;i++)
    ans+=n+1-sa[i]-height[i];

出现k次可重叠最长子串：
二分长度l，height>=l的连续段长就是出现次数

不可重叠出现k次：
同样二分长度l，
连续段长的height位置对应的sa拿出来，如果能找出一个子序列满足每两个之间差>=l就成立

const int maxn=1e6+5;
char s[maxn];
struct SA
{
    int t[maxn],fir[maxn],sec[maxn],sa[maxn],rnk[maxn],height[maxn];
    int N;
    void bsort(int n,int m,int fir[],int sec[],int res[])
    {
        for(int i=1;i<=m;++i)
            t[i]=0;
        for(int i=1;i<=n;++i)
            ++t[fir[i]];
        for(int i=1;i<=m;++i)
            t[i]+=t[i-1];
        for(int i=n;i;--i)
            res[t[fir[sec[i]]]--]=sec[i];
    }
    void getsa(int n,int m)
    {
        N=n;
        //mem(fir,0);mem(sec,0);mem(sa,0);mem(t,0);
        for(int i=1;i<=m;++i)
            t[i]=0;
        for(int i=1;i<=n;++i)
            fir[i]=s[i],sec[i]=i;
        bsort(n,m,fir,sec,sa);
        for(int k=1;k<=n;k<<=1)
        {
            int cnt=0;
            for(int i=n-k+1;i<=n;++i)
                sec[++cnt]=i;
            for(int i=1;i<=n;++i)
                if(sa[i]>k)
                    sec[++cnt]=sa[i]-k;
            bsort(n,m,fir,sec,sa);
            //for(int i=1;i<=n;++i) sec[i]=0;
            swap(fir,sec);
            fir[sa[1]]=1,cnt=1;
            for(int i=2;i<=n;++i)
                fir[sa[i]]=sec[sa[i]]==sec[sa[i-1]]&&sec[sa[i]+k]==sec[sa[i-1]+k]?cnt:++cnt;
            if(cnt==n)
                break;
            m=cnt;
        }
    }
    void geth(int n)
    {
        for(int i=1;i<=n;++i)
            rnk[sa[i]]=i;
        int j,k=0;
        for(int i=1;i<=n;++i)
        {
            if(k)
                --k;
            j=sa[rnk[i]-1];
            while(s[i+k]==s[j+k])
                ++k;
            height[rnk[i]]=k;
        }
    }
    int st[maxn][25];
    int len[maxn];
    void rmq(int n)
    {
        for(int i=1;i<=n;++i)
            len[i]=log(i)/log(2);
        for(int i=1;i<=n;++i)
            st[i][0]=height[i];
        for(int j=1;(1<<j)<=n;++j)
            for(int i=1;i+(1<<j)-1<=n;++i)
                st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
    int query(int u,int v)
    {
        if(u==v)
            return N-u+1;
        int l=rnk[u],r=rnk[v];
        if(l>r)
            swap(l,r);
        ++l;
        int k=len[r-l+1];
        return min(st[l][k],st[r-(1<<k)+1][k]);
    }
}sa;
