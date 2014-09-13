#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#define PB push_back
#define MP make_pair
#define BG begin()
#define ED end()
#define SZ(x) ((int)((x).size()))
#define FF first
#define SS second
#define foreach(i,x) for (__typeof((x).begin()) i=(x).begin();i!=(x).end();i++)
#define FOR(i,l,r) for (int i=(l);i<=(r);i++)
#define ROF(i,r,l) for (int i=(r);i>=(l);i--)
using namespace std;
#define N 1000
#define eps 1e-12

double a[N],b[N],c[N],d[N],x[N],y[N];
int q[N],e[N],c0;

bool cmp(int i,int j) {return d[i]<d[j]-eps || (d[i]<d[j]+eps && c[i]<c[j]-1e-8);}

bool ok(double x,double y,int i) {return a[i]*x+b[i]*y>c[i]-1e-8;}

void jd(int i,int j) {
  double a1,b1,c1,a2,b2,c2,X,Y,S;
  a1=a[q[i]],b1=b[q[i]],c1=c[q[i]];
  a2=a[q[j]],b2=b[q[j]],c2=c[q[j]];
  X=c1*b2-c2*b1;
  Y=c1*a2-c2*a1;
  S=a1*b2-a2*b1;
  if (abs(S)>eps) {
    x[j]=X/S,y[j]=-Y/S;
  } else c0=1;
}

void add(int i) {
  a[i]=y[i+1]-y[i],b[i]=x[i]-x[i+1];
  c[i]=a[i]*x[i]+b[i]*y[i];
  double mo=sqrt(a[i]*a[i]+b[i]*b[i]);
  a[i]/=mo,b[i]/=mo,c[i]/=mo;
  d[i]=atan2(b[i],a[i]);
  e[i]=i;
}

int main() {
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int T;
  scanf("%d",&T);
  while (T--) {
  int n;
  c0=0;
  scanf("%d",&n);
  FOR(i,1,n) scanf("%lf%lf",x+i,y+i);
  x[n+1]=x[1],y[n+1]=y[1];
  FOR(i,1,n) add(i);
  sort(e+1,e+n+1,cmp);
  int t=0;
  FOR(i,1,n) {
    if (i==1 || abs(d[e[i-1]]-d[e[i]])>eps) t++;
    e[t]=e[i];
  };

  int beg=1,clo=0;
  FOR(i,1,t) {
    while (beg<clo && !ok(x[clo],y[clo],e[i])) clo--;
    while (beg<clo && !ok(x[beg+1],y[beg+1],e[i])) beg++;
    q[++clo]=e[i];
    if (beg<clo) jd(clo-1,clo);
  };
  while (beg<clo-1 && !ok(x[clo],y[clo],e[beg])) clo--;

  if (c0 || clo-beg<2) puts("NO"); else puts("YES");
  };
  return 0;
}
