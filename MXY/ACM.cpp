struct ACM
{
    struct node
    {
        int to[128],fail,id,cnt;
    }a[505*205];
    char str[505][202];
    int res[505];
    int tot=0;
    int newnode()
    {
        mem(a[tot].to,0);
        a[tot].fail=a[tot].id=a[tot].cnt=0;
        return tot++;
    }
    void init()
    {
        mem(res,0);
        tot=0;
        newnode();
    }
    void add(char s[],int id)
    {
        int n=strlen(s);
        int now=0;
        for(int i=0;i<n;++i)
        {
            int k=s[i];
            if(!a[now].to[k])
                a[now].to[k]=newnode();
            now=a[now].to[k];
        }
        if(!a[now].id)
        {
            a[now].id=id;
            for(int i=0;i<n;++i)
                str[id][i]=s[i];
        }
        ++a[now].cnt;
    }
    void build()
    {
        queue<int>q;
        a[0].fail=0;
        for(int i=0;i<128;++i)
            if(a[0].to[i])
            {
                a[a[0].to[i]].fail=0;
                q.push(a[0].to[i]);
            }
        while(!q.empty())
        {
            int now=q.front();
            q.pop();
            for(int i=0;i<128;++i)
            {
                int son=a[now].to[i];
                if(son)
                {
                    a[son].fail=a[a[now].fail].to[i];
                    q.push(son);
                }
                else
                    a[now].to[i]=a[a[now].fail].to[i];
            }
        }
    }
    int query(char s[])
    {
        mem(res,0);
        int n=strlen(s);
        int now=0,cnt=0;
        for(int i=0;i<n;++i)
        {
            int k=s[i];
            now=a[now].to[k];
            int tp=now;
            while(tp)
            {
                if(a[tp].id)
                    res[a[tp].id]+=a[tp].cnt,cnt+=a[tp].cnt;
                tp=a[tp].fail;
            }
        }
        return cnt;
    }
}acm;
