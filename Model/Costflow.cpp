#include <stdio.h>
#include <memory.h>
#define vmax 200
#define emax 20000
const int oo = (~0U >> 1) >> 1;

int n,m,s = 1,t,cf = 0,que[(vmax << 1) + 18],time = 0,fst[(vmax << 1) + 18],tot = 1;
int d[(vmax << 1) + 18],pre[(vmax << 1) + 18];
bool ed[(vmax << 1) + 18];

struct typedge
{
    int pnt,cst,cty,nxt;
}e[(emax << 1) + 500];

void addedge(int s,int t,int cy,int ct)
{
    e[++tot].nxt = fst[s];
    fst[s] = tot;
    e[tot].pnt = t;
    e[tot].cty = cy;
    e[tot].cst = ct;
    
    e[++tot].nxt = fst[t];
    fst[t] = tot;
    e[tot].pnt = s;
    e[tot].cty = 0;
    e[tot].cst = -ct;
}

bool spfa()
{
    for (int i = 1;i <= t;++i) d[i] = oo;
    d[s] = 0;
    memset(que,0,sizeof(que));
    memset(ed,0,sizeof(ed));
    int now = s,next = s,dt;
    for (int i,pos;now;now = que[pos],que[pos] = 0)
	for (ed[pos = now] = false,i = fst[pos];i;i = e[i].nxt)
	{
	    int j = e[i].pnt;
	    if (e[i].cty && (dt = d[pos] + e[i].cst) < d[j])
	    //if ((dt = d[pos] + e[i].cst) < d[j])
	    {
		   d[j] = dt;
		   pre[j] = i;
		   if (!ed[j]) 
		   {
		       ed[j] = true;
		       que[next] = j;
		       next = j;
		   }
	    }
	}
    return d[t] != oo;
}

void aug()
{
    int del = oo;
    for (int i = t;i != s;i = e[pre[i] ^ 1].pnt)
	if (e[pre[i]].cty < del) del = e[pre[i]].cty;
    for (int i = t;i != s;i = e[pre[i] ^ 1].pnt)
    {
	e[pre[i]].cty -= del;
	e[pre[i] ^ 1].cty += del;
	cf += e[pre[i]].cst * del;
    }
}

int main()
{
    freopen ("run.in","r",stdin);
    freopen ("run.out","w",stdout);
    scanf("%d%d",&n,&m);
    addedge(1,1 + n,oo,0);
    addedge(n,n << 1,oo,0);
    for (int i = 2;i < n;++i)
	addedge(i,i + n,1,0);
    for (int i = 1,ss,tt,cc;i <= m;++i)
	scanf("%d%d%d",&ss,&tt,&cc),addedge(ss + n,tt,1,cc);
    t = n << 1;
    while (spfa()) aug(),++time;
    printf("%d %d",time,cf);
    return 0;
}
