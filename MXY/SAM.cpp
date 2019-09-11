const int maxn=3e5+5;
char s[maxn];
struct SAM
{
	struct node
	{
		int to[26];
		int len,link,siz;
		ll sum;
	}t[2*maxn];
	int sz,lst;
	int cnt[2*maxn],top[maxn*2];
	int ans[2*maxn];
	int cc[2*maxn];
	int newnode(int len)
	{
	    ++sz;
		mem(t[sz].to,0);
		t[sz].len=len;
		t[sz].link=0;
		t[sz].siz=0;
		t[sz].sum=0;
		return sz;
	}
	void init()
	{
		sz=0;
		lst=1;
		newnode(0);
		mem(cnt,0);
		mem(top,0);
	}
	void add(char w)
	{
	    int c=w-'a';
		int p=lst;
		int now=newnode(t[p].len+1);
		while(p&&!t[p].to[c])
		{
			t[p].to[c]=now;
			p=t[p].link;
		}
		if(!p)
			t[now].link=1;
		else
		{
			int q=t[p].to[c];
			if(t[p].len+1==t[q].len)
				t[now].link=q;
			else
			{
				int clone=newnode(t[p].len+1);
				t[clone].link=t[q].link;
				for(int i=0;i<26;++i)
					t[clone].to[i]=t[q].to[i];
				t[q].link=clone;
				t[now].link=clone;
				while(p&&t[p].to[c]==q)
				{
					t[p].to[c]=clone;
					p=t[p].link;
				}
			}
		}
		lst=now;
		t[now].siz=1;
	}
    void topsort()
	{
	    for(int i=1;i<=sz;++i)
            ++cnt[t[i].len];
        for(int i=1;i<=sz;++i)
            cnt[i]+=cnt[i-1];
        for(int i=1;i<=sz;++i)
            top[cnt[t[i].len]--]=i;
        //run1
        for(int i=1;i<=sz;++i)
            ans[i]=t[i].len;

        //run
        for(int i=sz;i;--i)
        {
            int x=top[i],f=t[x].link;
            t[f].siz+=t[x].siz;
        }
        for(int i=1;i<=sz;++i)
        {
            int x=top[i],f=t[x].link;
            t[x].sum=t[f].sum+1LL*t[x].siz*(t[x].len-t[f].len);
        }
	}
	//两串相同子串数量
	ll run1(char s[])
	{
	    int now=1,len=0;
	    ll res=0;
	    int n=strlen(s);
	    for(int i=0;i<n;++i)
        {
            int c=s[i]-'a';
            if(t[now].to[c])
            {
                ++len;
                now=t[now].to[c];
            }
            else
            {
                while(now&&!t[now].to[c])
                    now=t[now].link;
                if(now)
                {
                    len=t[now].len+1;
                    now=t[now].to[c];
                }
                else
                {
                    now=1;
                    len=0;
                }
            }
            res+=t[t[now].link].sum+1LL*t[now].siz*(len-t[t[now].link].len);
        }
        return res;
	}
	void run(char s[])//多串LCS
	{
	    mem(cc,0);
	    int n=strlen(s);
	    int p=1,l=0;
	    for(int i=0;i<n;++i)
        {
            int c=s[i]-'a';
            while(p&&!t[p].to[c])
                p=t[p].link,l=t[p].len;
            if(!p)
                p=1,l=0;
            else p=t[p].to[c],cc[p]=max(cc[p],++l);

        }
        for(int i=sz;i;--i)
        {
            int x=top[i];
            cc[t[x].link]=max(cc[t[x].link],cc[x]);
        }
        for(int i=1;i<=sz;++i)
            ans[i]=min(ans[i],cc[i]);
	}
	//多串LCS
	int res()
	{
	    int r=0;
	    for(int i=0;i<sz;++i)
            r=max(r,ans[i]);
        return r;
	}
}sam;
