const int maxn=2e6+5;
//区间异或最大值
struct LTRIE
{
    struct node
    {
        int to[2];
        int siz;
    }t[maxn];
    int rt[maxn];
    int sz=0;
    void init()
    {
        mem(rt,0);
        sz=0;
    }
    int newnode()
    {
        ++sz;
        mem(t[sz].to,0);
        t[sz].siz=0;
        return sz;
    }
    void add(int n,int id)
    {
        int now=newnode();
        rt[id]=now;
        int pre=rt[id-1];
        for(int i=31;~i;--i)
        {
            for(int j=0;j<2;++j)
                t[now].to[j]=t[pre].to[j];
            t[now].siz=t[pre].siz+1;
            int k=((n>>i)&1);
            t[now].to[k]=newnode();
            now=t[now].to[k];
            pre=t[pre].to[k];
        }
        t[now].siz=t[pre].siz+1;
    }
    int query(int l,int r,int n)
    {
        int ans=0;
        int now=rt[r],pre=rt[l];
        for(int i=31;~i;--i)
        {
            int k=!((n>>i)&1);
            if(t[t[now].to[k]].siz>t[t[pre].to[k]].siz)
            {
                ans|=(1<<i);
                now=t[now].to[k];
                pre=t[pre].to[k];
            }
            else
                now=t[now].to[!k],pre=t[pre].to[!k];
        }
        return ans;
    }
}lt;
