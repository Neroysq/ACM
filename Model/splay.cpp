#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int nmax = 300000 + 18;

int gcd(int a, int b)
{
	return b ? gcd(b, a % b) : a;
}

struct Spode {
	int x, ds, ls, size;
	int l, exil, exid;
	int debug;
	Spode *c[2], *f;
	bool dir() {return this == f->c[1]; };
	void update() {
		if (l) ls = x, ds = 0; else ls = 0, ds = x;
		size = c[0]->size + 1 + c[1]->size;
		exil = c[0]->exil | l | c[1]->exil;
		exid = c[0]->exid | (!l) | c[1]->exid;
		ls = gcd(ls, gcd(c[0]->ls, c[1]->ls));
		ds = gcd(ds, gcd(c[0]->ds, c[1]->ds));
	}
	void display() {
		printf("%d %d %d %d \n%d %d %d\n%d %d %d\n", x, ls, ds, size, l, exil, exid, c[0]->debug, f->debug, c[1]->debug);
	}
}P[nmax], piu, *null = &piu, *root;

int n, tot;

void rotate(Spode *a)
{
	Spode *b = a->f;
	bool m = a->dir();
	a->f = b->f, b->c[m] = a->c[!m];
	if (b->f != null) b->f->c[b->dir()] = a;
	if (a->c[!m] != null) a->c[!m]->f = b;
	a->c[!m] = b;
	b->f = a;
	b->update();
}

void splay(Spode *a, Spode *b)
{
	while (a->f != b)
		if (a->f->f == b) rotate(a);
		else
			(a->dir() == a->f->dir() ? 
			rotate(a->f) :
			rotate(a)),
			rotate(a);
	a->update();
	if (b != null) b->update();
	if (b == null) root = a;
}

Spode *build(int l, int r)
{
	int mid = (l + r + 1) >> 1;
	Spode *b = &P[mid];
	b->size = 1;
	b->f = b->c[0] = b->c[1] = null;
	b->debug = mid;
	
	if (l < mid)
		b->c[0] = build(l, mid - 1), b->c[0]->f = b;
	else
		b->c[0] = null;
	if (r > mid)
		b->c[1] = build(mid + 1, r), b->c[1]->f = b;
	else
		b->c[1] = null;
	b->update();
	return b;
}

Spode *find_rank(int x)
{
	Spode *a = root;
	while (a->c[0]->size + 1 != x)
		if (a->c[0]->size + 1 == x) break;
		else if (a->c[0]->size < x)
			x -= a->c[0]->size + 1, a = a->c[1];
		else
			a = a->c[0];
	return a;
}

int query(int l, int r, int sta)
{
	++l, ++r;
	Spode *L = find_rank(l - 1), *R = find_rank(r + 1);
	splay(R, null);
	splay(L, R);
	if (sta)
		return L->c[1]->exil ? L->c[1]->ls : -1;
	else
		return L->c[1]->exid ? L->c[1]->ds : -1;
}

void insert(int pos, int val, int sta)
{
	++pos;
	Spode *b = &P[++tot];
	b->x = val;
	b->l = sta;
	b->c[0] = b->c[1] = null;
	b->update();
	Spode *L = find_rank(pos), *R = find_rank(pos + 1);
	splay(L, null);
	splay(R, L);
	R->c[0] = b;
	b->f = R;
	R->update();
	L->update();
}

void erase(int pos)
{
	++pos;
	Spode *L = find_rank(pos - 1), *R = find_rank(pos + 1);
	splay(L, null);
	splay(R, L);
	R->c[0] = null;
	R->update();
	L->update();
}

void changesta(int pos)
{
	++pos;
	Spode *L = find_rank(pos - 1), *R = find_rank(pos + 1);
	splay(L, null);
	splay(R, L);
	R->c[0]->l ^= 1;
	R->c[0]->update();
	R->update();
	L->update();
}

void changeval(int pos, int val)
{
	++pos;
	Spode *L = find_rank(pos - 1), *R = find_rank(pos + 1);
	splay(L, null);
	splay(R, L);
	R->c[0]->x = val;
	R->c[0]->update();
	R->update();
	L->update();
}

void dfs(Spode *a)
{
	if (a == null) return;
	a->display();
	dfs(a->c[0]);
	dfs(a->c[1]);
}

//PID ZOJ 3765
int main()
{
	while (scanf("%d", &n) == 1) {
		int Q;
		scanf("%d", &Q);
		for (int i = 1; i <= n; ++i)
			scanf("%d%d", &P[i].x, &P[i].l);
		null->x = null->l = null->ls = null->ds = null->exil = null->exid = null->size = 0;
		null->c[0] = null->c[1] = null->f = null;
		
		null->debug = -1;
		
		P[0].l = 0;
		P[0].x = 0;
		P[n + 1].l = 0;
		P[n + 1].x = 0;
		tot = n + 1;
		root = build(0, n + 1);
		for (int i = 1; i <= Q; ++i) {
			char com[10];
			scanf("%s", com);
			if (com[0] == 'Q') {
				int l, r, sta;
				scanf("%d%d%d", &l, &r, &sta);
				printf("%d\n", query(l, r, sta));
			}
			else if (com[0] == 'I') {
				int pos, val, sta;
				scanf("%d%d%d", &pos, &val, &sta);
				insert(pos, val, sta);
			}
			else if (com[0] == 'D') {
				int pos;
				scanf("%d", &pos);
				erase(pos);
			}
			else if (com[0] == 'R') {
				int pos;
				scanf("%d", &pos);
				changesta(pos);
			}
			else {
				int pos, val;
				scanf("%d%d", &pos, &val);
				changeval(pos, val);
			}
		}
	}
	return 0;
}
