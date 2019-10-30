const int maxn=1e6+5;
int nxt[maxn];//b和b的第i个后缀b[i~m]的最长公共前缀
int ext[maxn];//b和a的第i个后缀a[i~n]的最长公共前缀
char a[maxn],b[maxn];
void exnxt(int m)
{
    nxt[0]=m;
    int j=0,k=0;
    for(int i=1;i<m;++i)
    {
        if(j-i>nxt[i-k])
            nxt[i]=nxt[i-k];
        else
        {
            nxt[i]=max(j-i,0);
            while(b[i+nxt[i]]==b[nxt[i]])
                ++nxt[i];
            if(i+nxt[i]>j)
            {
                j=i+nxt[i];
                k=i;
            }
        }
    }
}
void exkmp(int n,int m)
{
    int l=0;
    while(l<n&&l<m&&b[l]==a[l])
        ++l;
    ext[0]=l;
    int j=0,k=0;
    for(int i=1;i<n;++i)
    {
        int p=ext[k]+k-1;
        if(nxt[i-k]<p-i+1)
            ext[i]=nxt[i-k];
        else
        {
            j=max(p-i+1,0);
            while(i+j<n&&j<m&&a[i+j]==b[j])
                ++j;
            ext[i]=j;
            k=i;
        }
    }
}
