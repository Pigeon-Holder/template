const int maxn=4e5+5;
struct PAM
{
    struct node
    {
        int to[26],len,fail,cnt;
    }t[maxn+2];
    char s[maxn];
    int lst,sz,len;
    int newnode(int len)
    {
        mem(t[sz].to,0);
        t[sz].fail=t[sz].cnt=0;
        t[sz].len=len;
        return sz++;
    }
    void init()
    {
        len=0;
        sz=lst=0;
        newnode(0);
        newnode(-1);
        t[0].fail=1;
    }
    int getfail(int now)
    {
        while(s[len-t[now].len-1]!=s[len])
            now=t[now].fail;
        return now;
    }
    void add(char w)
    {
        s[++len]=w;
        int c=w-'a';
        int now=getfail(lst);
        if(!t[now].to[c])
        {
            newnode(t[now].len+2);
            t[sz-1].fail=t[getfail(t[now].fail)].to[c];
            t[now].to[c]=sz-1;
        }
        lst=t[now].to[c];
        ++t[lst].cnt;
    }
    void cnt()
    {
        for(int i=sz-1;~i;--i)
            t[t[i].fail].cnt+=t[i].cnt;
    }
}pam;
