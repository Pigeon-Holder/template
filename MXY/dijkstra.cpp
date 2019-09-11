struct edge
{
    int to,nxt;
    ll v;
    edge(){}
    edge(int a,int b,ll c){to=a;nxt=b;v=c;}
}e[20005];
int head[105];
int tot;
void ae(int u,int v,ll w)
{
    e[tot]=edge(v,head[u],w);
    head[u]=tot++;
    e[tot]=edge(u,head[v],w);
    head[v]=tot++;
}
void init()
{
    tot=0;
    mem(head,-1);
}
ll dis[105];
bool vis[105];
void dijkstra(int st)
{
    mem(vis,0);
    mem(dis,127);
    dis[st]=0;
    priority_queue<pli,vector<pli>,greater<pli> >q;
    q.push(mp(0,st));
    while(!q.empty())
    {
        pli now=q.top();
        q.pop();
        int u=now.se;
        ll c=now.fi;
        if(vis[u])
            continue;
        vis[u]=1;
        for(int i=head[u];~i;i=e[i].nxt)
        {
            int v=e[i].to;
            ll w=e[i].v;
            if(dis[u]+w<dis[v])
            {
                dis[v]=dis[u]+w;
                q.push(mp(dis[v],v));
            }
        }
    }
}
