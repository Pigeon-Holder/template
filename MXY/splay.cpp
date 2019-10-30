const int maxn=1e5+5;
struct node
{
    int f,val,cnt,sz;
    int son[2];
}t[maxn];
int tot,root;
void init()
{
    tot=0;
    root=0;
}
int newnode(int v,int f)
{
    ++tot;
    t[tot].cnt=t[tot].sz=1;
    t[tot].val=v;t[tot].f=f;
    mem(t[tot].son,0);
    return tot;
}
void pushup(int rt)
{
    if(!rt)
        return;
    t[rt].sz=t[rt].cnt;
    if(t[rt].son[0])
        t[rt].sz+=t[t[rt].son[0]].sz;
    if(t[rt].son[1])
        t[rt].sz+=t[t[rt].son[1]].sz;
}
void rot(int rt)
{
    int f=t[rt].f,ff=t[f].f;
    int k=t[f].son[1]==rt;
    t[ff].son[t[ff].son[1]==f]=rt;
    t[rt].f=ff;
    t[f].son[k]=t[rt].son[k^1];
    t[t[rt].son[k^1]].f=f;
    t[rt].son[k^1]=f;
    t[f].f=rt;
    pushup(f);
    pushup(rt);
}

inline void splay(int rt,int goal)
{
    for(int f;(f=t[rt].f)!=goal;rot(rt))
        if(t[f].f!=goal)
            rot((t[t[rt].f].son[0]==f)==(t[f].son[0]==rt)?f:rt);
    if(!goal)
        root=rt;
}
void find(int v)
{
    int now=root;
    if(!now)
        return;
    while(t[now].son[v>t[now].val]&&v!=t[now].val)
        now=t[now].son[v>t[now].val];
    splay(now,0);
}
int next(int v,int f)
{
    find(v);
    if(t[root].val<v&&!f)
        return root;
    if(t[root].val>v&&f)
        return root;
    int now=t[root].son[f];
    while(t[now].son[f^1])
        now=t[now].son[f^1];
    return now;
}
void ins(int v)
{
    if(!root)
    {
        root=newnode(v,0);
        return;
    }
    int now=root,lst=0;
    while(1)
    {
        if(v==t[now].val)
        {
            ++t[now].cnt;
            pushup(now);
            pushup(lst);
            splay(now,0);
            return;
        }
        lst=now;
        now=t[now].son[v>t[now].val];
        if(!now)
        {
            t[lst].son[v>t[lst].val]=newnode(v,lst);
            pushup(lst);
            splay(tot,0);
            return;
        }
    }
}

int rnk(int v)
{
    find(v);
    return t[t[root].son[0]].sz+1;
}
int kth(int k)
{
    int now=root;
    while(1)
    {
        int v=t[now].son[0];
        if(t[v].sz+t[now].cnt<k)
            k-=t[v].sz+t[now].cnt,now=t[now].son[1];
        else
            if(t[v].sz>=k)
            now=v;
            else return t[now].val;
    }
}

void del(int v)
{
    find(v);
    if(t[root].cnt>1)
    {
        --t[root].cnt;
        pushup(root);
        return;
    }
    else if(!t[root].son[0]&&!t[root].son[1])
    {
        init();
        return;
    }
    else if(!t[root].son[0])
    {
        root=t[root].son[1];
        t[root].f=0;
        return;
    }
    else if(!t[root].son[1])
    {
        root=t[root].son[0];
        t[root].f=0;
        return;
    }
    int f=root,pre=next(v,0);
    splay(pre,0);
    t[root].son[1]=t[f].son[1];
    t[t[f].son[1]].f=root;
    pushup(root);
}
int main()
{
    init();
    int n;
    for(scanf("%d",&n);n;--n)
    {
        int op,k;
        scanf("%d%d",&op,&k);
        if(op==1)//插入k
            ins(k);
        else if(op==2)//删除1个k
            del(k);
        else if(op==3)//查询k的排名
            printf("%d\n",rnk(k));
        else if(op==4)//查询第k小
            printf("%d\n",kth(k));
        else if(op==5)//小于k且最大的数
            printf("%d\n",t[next(k,0)].val);
        else if(op==6)//大于k且最小的数
            printf("%d\n",t[next(k,1)].val);
    }
}
