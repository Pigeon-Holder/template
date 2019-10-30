typedef unsigned u32;
const int maxn = 200200;
const int N = 3.5e7,V = 70000;
int sm;
namespace tree{
    int L[N],R[N],size[N],tot;
    inline void del(int x){
        for(int i = x + 1;i <= tot; ++i) L[i] = R[i] = size[i] = 0;
        tot = x;
    }
    inline void add(int & rt,int pos,int v,int l=0,int r=V){
        if(!rt) rt = ++ tot; size[rt] += v;
        if(l == r) return ;
        int mid = (l + r) >> 1;
        if(pos <= mid) add(L[rt],pos,v,l,mid);
        else add(R[rt],pos,v,mid+1,r);
    }
    inline int kth(std::vector<int> & v,int k){
        int l = 0,r = V;
        while(l != r){
            int sm = 0,mid = (l + r) >> 1;
            for(std::vector<int>::iterator it = v.begin();it != v.end();++it)
                sm += size[L[*it]];
            if(k <= sm){
                for(std::vector<int>::iterator it = v.begin();it != v.end();++it) *it = L[*it];
                r = mid;
            }else{
                for(std::vector<int>::iterator it = v.begin();it != v.end();++it) *it = R[*it];
                l = mid + 1,k -= sm;
            }
        }
        return l;
    }
    inline int merge(int x,int y){
        if(!size[x] && !size[y]) return 0;
        int p = ++ tot; size[p] = size[x] + size[y];
        L[p] = merge(L[x],L[y]), R[p] = merge(R[x],R[y]);
        return p;
    }
}
using tree::add; using tree::kth; using tree::merge;
int son[maxn][2],p[maxn];
int rt[maxn],fa[maxn],v[maxn],size[maxn];
int idx;
inline void up(int x){ size[x] = size[son[x][0]] + size[son[x][1]] + 1; }
inline void up2(int x){ rt[x] = merge(rt[son[x][0]],rt[son[x][1]]),add(rt[x],v[x],1); up(x); }
inline int get(int x,int p=1){ return son[fa[x]][p] == x; } 
inline void rotate(int x){
    int y=fa[x],z=fa[y],b=get(x);
    const int r = rt[y];
    son[y][b]=son[x][!b],son[x][!b]=y;
    fa[son[y][b]]=y,fa[y]=x,fa[x]=z;
    up2(y); rt[x] = r; up(x);
}
inline void ins(int&x,int v,int pos,int f){
    if(!x){
        size[x = ++idx] = 1; add(rt[x],v,1); ::v[x] = v; fa[x] = f;
        return ;
    }
    if(size[son[x][0]] >= pos){
        ins(son[x][0],v,pos,x);
        up(x),add(rt[x],v,1);
        if(p[son[x][0]] > p[x]) rotate(x = son[x][0]);
    }else{
        ins(son[x][1],v,pos - size[son[x][0]] - 1,x);
        up(x),add(rt[x],v,1);
        if(p[son[x][1]] > p[x]) rotate(x = son[x][1]);
    }
}
inline int find(int rt,int k){
    if(size[son[rt][0]] >= k) return find(son[rt][0],k);
    if(size[son[rt][0]] + 1 == k) return rt;
    return find(son[rt][1],k - size[son[rt][0]] - 1);
}
inline void mdf(int x,int s){
    const int r = v[x]; v[x] = s;
    while(x) add(rt[x],r,-1),add(rt[x],s,1),x=fa[x];
}
inline int build(int l,int r,int f){
    if(l > r) return 0;
    int id = std::max_element(p + l,p + r + 1) - p;
    fa[id] = f, son[id][0] = build(l,id-1,id); son[id][1] = build(id+1,r,id); up2(id);
    return id;
}
inline void qry(int x,int l,int r,int L,int R,std::vector<int> & v,int&rt){
    if(!x || r < L || l > R) return ;
    if(L <= l && r <= R) return v.push_back(::rt[x]);
    const int mid = l + size[son[x][0]];
    qry(son[x][0],l,mid-1,L,R,v,rt);
    qry(son[x][1],mid+1,r,L,R,v,rt);
    if(L <= mid && mid <= R) add(rt,::v[x],1);
}
inline void dfs(int x){
    if(!x) return ;
    dfs(son[x][0]),std::cout << v[x] << ' ',dfs(son[x][1]);
}
int n,q;
int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(0);
    std::cin >> n; idx = n;
    for(int i=1;i<maxn;++i) p[i] = i;
    for(int i=1;i<=5;++i) std::random_shuffle(p,p + maxn);
    for(int i=1;i<=n;++i) std::cin >> v[i];
    int rt = build(1,n,0); std::cin >> q;
    for(int i=1,last = 0;i<=q;++i){
        char ch;int x,y,k,v;
        std::cin >> ch;
        if(ch == 'Q'){//[x, y]区间第k小
            std::cin >> x >> y >> k;
            x ^= last,y ^= last,k ^= last; std::vector<int> v; int r = 0;
            int T = tree::tot;
            qry(rt,1,size[rt],x,y,v,r); v.push_back(r);
            std::cout << (last = kth(v,k)) << '\n';
            tree::del(T);
        }
        if(ch == 'M'){//第x个位置改为v
            std::cin >> x >> v,x ^= last,v ^= last;
            mdf(find(rt,x),v);
        }
        if(ch == 'I'){//在第x个前插入一个v
            std::cin >> x >> v,x ^= last,v ^= last;
            ins(rt,v,x-1,0);
        }
    }
