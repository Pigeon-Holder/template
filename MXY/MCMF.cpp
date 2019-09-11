const int maxn=1005;
struct MCMF
{
    struct edge
    {
        int to,nxt;
        ll cap,cos,flow;
        edge(){}
        edge(int _to,int _nxt,ll _cap,ll _cos,ll _flow)
        {
            to=_to,nxt=_nxt,cap=_cap,cos=_cos,flow=_flow;
        }
    }e[100005];
    int head[maxn],tot,n;
    void ae(int u,int v,ll cap,ll cos)
    {
        e[tot]=edge(v,head[u],cap,cos,0);
        head[u]=tot++;
        e[tot]=edge(u,head[v],0,-cos,0);
        head[v]=tot++;
    }
    int h[maxn],pre[maxn];
    ll dis[maxn];
    ll cost,flow,INF;
    void init(int a)
    {
        n=a;
        tot=0;
        flow=cost=0;
        mem(head,-1);
        mem(dis,127);
        INF=dis[0];
    }
    void go(int s,int t,int f)
    {
        mem(h,0);
        while(f>0)
        {
            priority_queue<pli,vector<pli>,greater<pli> >q;
            mem(dis,127);
            dis[s]=0;
            q.push(mp(0,s));
            mem(pre,-1);
            while(!q.empty())
            {
                pli now=q.top();
                q.pop();
                if(dis[now.se]<now.fi)
                    continue;
                int u=now.se;
                for(int i=head[u];~i;i=e[i].nxt)
                {
                    edge &t=e[i];
                    if(t.cap>t.flow&&dis[t.to]>dis[u]+t.cos+h[u]-h[t.to])
                    {
                        dis[t.to]=dis[u]+t.cos+h[u]-h[t.to];
                        pre[t.to]=i;
                        q.push(mp(dis[t.to],t.to));
                    }
                }
            }
            if(dis[t]==INF)
                break;
            for(int i=0;i<=n;++i)
                h[i]+=dis[i];
            ll d=f;
            for(int i=pre[t];~i;i=pre[e[i^1].to])
                d=min(d,e[i].cap-e[i].flow);
            f-=d;
            flow+=d;
            cost+=d*h[t];
            for(int i=pre[t];~i;i=pre[e[i^1].to])
            {
                e[i].flow+=d;
                e[i^1].flow-=d;
            }
        }
    }
}mcmf;

int main()
{
    int n,m;
    while(cin>>n>>m)
    {
        mcmf.init(n);
        for(int i=0;i<m;++i)
        {
            int u,v,c,f;
            cin>>u>>v>>f>>c;
            mcmf.ae(u,v,f,c);
        }
        mcmf.go(1,n,1e18);
        cout<<mcmf.flow<<' '<<mcmf.cost<<endl;
    }
}
