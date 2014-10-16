#include <stdio.h>
const int smax = 960000, cmax = 1000000000 + 1, nmax = 50000;

struct tps{
  tps *l, *r;
  int s;
}pl[smax + 18], *root[nmax + 18], *null = pl;

int n, m, t, tot, a[nmax + 18], globe;
char com;

tps *newp(tps *a)
{
  tps *b = pl + (++tot);
  return *b = *a, b;
}

void add(tps *&A, int L, int R, int i, int k)
{
  A = newp(A);
  if (L == R) {
    A->s += k;
    return ;
  }
  if (!A->l || !A->r)
    ++tot;
  int mid = (L + R) >> 1;
  i > mid ? add(A->r, mid + 1, R, i, k) : add(A->l, L, mid, i, k);
  A->s = A->l->s + A->r->s;
}

void getsum(tps *A, int L, int R, int l, int r)
{
  if (!A->s) return;
  if (L >= l && R <= r) {
    globe += A->s;
    return;
  }
  int mid = (L + R) >> 1;
  if (r >  mid) getsum(A->r, mid + 1, R, l, r);
  if (l <= mid) getsum(A->l, L,     mid, l, r);
}

void change(int i, int c)
{
  int k = i;
  for (; i <= n; i += i & -i)
    add(root[i], 1, cmax, a[k], -1), add(root[i], 1, cmax, c, 1);
}

int gets(int i, int l, int r)
{
  globe = 0;
  for (; i; i -= i & -i)
    getsum(root[i], 1, cmax, l, r);
  return globe;
}

int ask(int s, int t, int k)
{
  int l = 1, r = cmax;
  for (int mid, tmp; (mid = (l + r) >> 1), l < r; )
    ((tmp = gets(t, l, mid) - gets(s, l, mid)) >= k) ? r = mid : (l = mid + 1, k -= tmp);
  return l - 1;
}

int main()
{
  freopen("zoj2112.in", "r", stdin);
  freopen("zoj2112.out", "w", stdout);
  null->l = null->r = null;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    tot = 1;
    root[0] = pl + 1;
    root[0]->l = root[0]->r = null, root[0]->s = 0;
    for (int i = 1; i <= n; ++i) root[i] = root[0];
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i), ++a[i];
      for (int j = i; j <= n; j += j & -j)
	add(root[j], 1, cmax, a[i], 1);
    }
    for (int i, b, c; m--; )
      if (scanf("\n%c%d%d", &com, &i, &b), com == 'C') 
	change(i, b + 1), a[i] = b + 1;
      else
	scanf("%d", &c), printf("%d\n", ask(i - 1, b, c));
  }
  return 0;
}

