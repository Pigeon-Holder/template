const int maxn=1e6+5;
int nxt[maxn];//a[0~i]的前缀和后缀最长的相同长度
char a[maxn],b[maxn];//目标串，模式串
void getnxt(int m)//对模式串使用
{
    int i=0,j=-1;
    nxt[0]=-1;
    while(i<m)
    {
        if(j==-1||b[i]==b[j])
        {
            ++i;
            ++j;
            nxt[i]=j;
        }
        else
            j=nxt[j];
    }
}
int kmp(int n,int m)
{
    int ans=0;
    int i=0,j=0;
    while(i<n)
    {
        if(j==-1||a[i]==b[j])
            ++i,++j;
        else
            j=nxt[j];
        if(j==m)
        {
            ++ans;
            j=nxt[j];
        }
    }
    return ans;
}
