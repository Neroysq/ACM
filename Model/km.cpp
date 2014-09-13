//kmÀ„∑®   Copyright @ mlj

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

const int nmax = 2000, oo = ~0U >> 1;

int w[nmax + 18][nmax + 18], n, ans = 0, slack[nmax + 18];
int lx[nmax + 18], ly[nmax + 18], q[nmax + 18];
bool ss[nmax + 18], tt[nmax + 18];
int x[nmax + 18], y[nmax + 18], pre[nmax + 18];

int bfs(int s)
{
    int h = 0, t = 1;
    q[t] = s;
    for (; h != t;)
    {
	for (; h != t;)
	{
	    int i = q[++h];
	    ss[i] = true;
	    for (int j = 1, tmp; j <= n; ++j)
		if ((tmp = lx[i] + ly[j] - w[i][j]) < slack[j] && !tt[j])
		{
		    slack[j] = tmp;
		    pre[j] = i;
		    if (!slack[j])
		    {
			tt[j] = true;
			if (!y[j]) return j;
			else
			    q[++t] = y[j];
		    }
		}
	}
	int del = oo;
	for (int i = 1; i <= n; ++i)
	    if (slack[i] < del && !tt[i]) del = slack[i];
	for (int i = 1; i <= n; ++i)
	{
	    slack[i] -= del;
	    if (ss[i]) lx[i] -= del;
	    if (tt[i]) ly[i] += del;
	}
	for (int i = 1; i <= n; ++i)
	    if ((!slack[i]) && !tt[i])
	    {
		tt[i] = true;
		if (!y[i]) return i;
		else
		    q[++t] = y[i];
	    }
    }
    return 0;
}

int main()
{
    char str[nmax * 4 + 18];
    FILE *fin = fopen ("km.in", "r");
    FILE *fout = fopen ("km.out", "w");
    fgets (str, sizeof(str), fin);
    sscanf (str, "%d%d", &n, &n);
    for (int i = 1; i <= n; ++i)
    {
	fgets (str, sizeof(str), fin);
	int j = 0;
	for (char *find = strtok( str, " "); find; find = strtok(0, " "))
	{
	    w[i][++j] = atoi(find);
	    if (lx[i] < w[i][j]) lx[i] = w[i][j];
	}
    }
    for (int i = 1; i <= n; ++i)
    {
	memset (ss, false, sizeof(ss));
	memset (tt, false, sizeof(tt));
	memset (slack, 0x3F3F, sizeof(slack));
	int j = bfs(i);
	for (int k; j; k = x[pre[j]], y[j] = pre[j], x[pre[j]] = j, j = k);
    }
    for (int i = 1; i <= n; ++i) ans += lx[i] + ly[i];
    fprintf (fout, "%d", ans);
}

    
    
