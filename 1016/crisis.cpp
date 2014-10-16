#include <stdio.h>
#include <math.h>
#define ef else if
typedef double db;
const int nmax = 20000, mmax = 50000;
struct tps {
    db dx, dy, alp;
    bool lur;
    tps *l, *r;
}*st[mmax + 18], TMP, *null = &TMP;

int n, q, wdt;
db x[nmax + 18], y[nmax + 18], nx, ny;
char com[10];

int eps(db x)
{
    return x < -1e-7 ? -1 : x > 1e-7;
}

tps *newp(tps *b)
{
    tps *a = new tps;
    return *a = *b, a;
}

tps *build(int l, int r)
{
    tps *a = newp(null);
    a->dx = a->dy = a->alp = 0;
    if (l == r)
	return a->dx = x[l], a->dy = y[l], a;
    else {
	int mid = (l + r) >> 1;
	if (l <= mid) a->l = build(l, mid);
	if (r > mid) a->r = build(mid + 1, r);
    }
    return a;
}

void rpushdown(tps *&A, db dx, db dy, db alp, bool clear)
{
    if (clear) {
	A->lur = clear;
	A->dx = dx;
	A->dy = dy;
	A->alp = alp;
	return;
    }
    if (eps(alp)){
	A->alp += alp;
	db a = sin(alp), b = cos(alp);
	db nx = b * A->dx - a * A->dy, ny = b * A->dy + a * A->dx;
	A->dx = nx, A->dy = ny;
    }
    A->dx += dx, A->dy += dy;
}

void pushdown(tps *&A)
{
    if (!A->lur && !eps(A->dx) && !eps(A->dy) && !eps(A->alp)) return;
    if (A->l != null) 
	rpushdown(A->l = newp(A->l), A->dx, A->dy, A->alp, A->lur);
    if (A->r != null)
	rpushdown(A->r = newp(A->r), A->dx, A->dy, A->alp, A->lur);
    A->dx = A->dy = A->alp = A->lur = 0;
}

void change(tps *&A, int L, int R, int l, int r, db a, db b, db c, bool mode)
{
    A = newp(A);
    if (L < R) pushdown(A);
    if (L >= l && R <= r)
	rpushdown(A, a, b, c, mode);
    else {
	int mid = (L + R) >> 1;
	if (l <= mid) change(A->l, L, mid, l, r, a, b, c, mode);
	if (r > mid) change(A->r, mid + 1, R, l, r, a, b, c, mode);
    }
}

void ask(tps *&A, int L, int R, int k, db &a, db &b)
{
    tps *nA = A;
    for (int mid; L < R; ) 
	if (pushdown(nA), k > (mid = (L + R) >> 1))
	    nA = nA->r, L = mid + 1;
	else
	    nA = nA->l, R = mid;
    a = nA->dx, b = nA->dy;
}

int main()
{
    freopen("crisis.in", "r", stdin);
    freopen("crisis.out", "w", stdout);
    null->l = null->r = null;
    null->lur = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lf%lf", x + i, y + i);
    st[0] = build(1, n);
    scanf("%d", &q);
    for (int l, r, a; q--; )
	if (scanf("%s", com), com[0] == 'C')
	    scanf("%d", &a), wdt -= a;
        ef (com[0] == 'R')
	    scanf("%d", &a), wdt += a;
	ef (com[0] == 'A')
	    scanf("%d", &a), ask(st[wdt], 1, n, a, nx, ny), printf("%.5f %.5f\n", nx, ny);
	else {
	    scanf("%d%d", &l, &r);
	    if (com[0] == 'M')
		scanf("%lf%lf", &nx, &ny), change(st[wdt + 1] = st[wdt], 1, n, l, r, nx, ny, 0, 0);
	    ef (com[0] == 'P')
		scanf("%lf", &nx), change(st[wdt + 1] = st[wdt], 1, n, l, r, 0, 0, nx, 0);
	    else change(st[wdt + 1] = st[wdt], 1, n, l, r, 0, 0, 0, 1);
	    ++wdt;
	}
    return 0;
}
