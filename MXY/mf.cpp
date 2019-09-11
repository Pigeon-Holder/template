struct DINIC
{
    const ll INF=1LL<<60;
    struct edge
    {
        int to;
        ll v;
        int nxt;
    }e[20005];
    int head[20005];
    int dep[20005];
    int sz;
    void init()
    {
        mem(head,-1);
        sz=0;
    }
    void ae(int u,int v,ll w)
    {
        e[sz]={v,w,head[u]};
        head[u]=sz++;
        e[sz]={u,0,head[v]};
        head[v]=sz++;
    }
    bool bfs(int s,int t)
    {
        mem(dep,-1);
        queue<int>q;
        dep[s]=1;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=head[u];~i;i=e[i].nxt)
            {
                int v=e[i].to,w=e[i].v;
                if(dep[v]==-1&&w)
                {
                    dep[v]=dep[u]+1;
                    if(v==t)
                        return 1;
                    q.push(v);
                }
            }
        }
        return ~dep[t];
    }
    ll dfs(int u,int t,ll flow)
    {
        if(u==t||!flow)
            return flow;
        int ret=0;
        for(int i=head[u];~i;i=e[i].nxt)
        {
            int v=e[i].to;
            ll f=e[i].v;
            if(dep[v]==dep[u]+1&&f)
            {
                int fee=dfs(v,t,min(flow,f));
                if(fee<=0) continue;
                e[i].v-=fee,e[i^1].v+=fee;
                flow-=fee,ret+=fee;
            }
            if(!flow)
                break;
        }
        if(!ret)
            dep[u]=-1;
        return ret;
    }
    ll dinic(int st,int ed)
    {
        ll res=0;
        while(bfs(st,ed))
            res+=dfs(st,ed,INF);
        return res;
    }
}mf;
