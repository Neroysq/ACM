//poj1743 2774
#include <stdio.h>
#include <string.h>
const int nmax = 100, lmax = 100000 * 2;

int who[lmax + 18], wre[lmax + 18], sw[lmax + 18], sv[lmax + 18];
int xx[lmax + 18], yy[lmax + 18], n, m, tot, i, p, j, height[lmax + 18], k;
char str[lmax + 18];

bool cmp(int *a, int i, int j, int l)
{
    return a[i] == a[j] && a[i + l] == a[j + l];
}

void da(int n, int m)
{
    int *x = xx, *y = yy, *t;
    for (i = 0; i <= m; ++i) sw[i] = 0;
    for (i = 1; i <= n; ++i) ++sw[x[i] = str[i]];
    for (i = 1; i <= m; ++i) sw[i] += sw[i - 1];
    for (i = n; i; --i) who[sw[x[i]]--] = i;
    for (j = p = 1; p < n; j <<= 1, m = p)
    {
	for (p = 0, i = n - j + 1; i <= n; ++i) y[++p] = i;
	for (i = 1; i <= n; ++i) if (who[i] > j) y[++p] = who[i] - j;
	for (i = 0; i <= m; ++i) sw[i] = 0;
	for (i = 1; i <= n; ++i) ++sw[sv[i] = x[y[i]]];
	for (i = 1; i <= m; ++i) sw[i] += sw[i - 1];
	for (i = n; i; --i) who[sw[sv[i]]--] = y[i];
	for (t = x, x = y, y = t, p = x[who[1]] = 1, i = 2; i <= n; ++i)
	    x[who[i]] = cmp(y, who[i - 1], who[i], j) ? p : ++p;
    }
}
    
void calch()
{
    for (i = n + 1; i; --i) wre[who[i]] = i;
    for (k = 0, i = 1; i <= n; height[wre[i++] - 1] = k)
	for (k ? --k : 0, j = who[wre[i] - 1]; str[j + k] == str[i + k]; ++k);
}

int main()
{
    scanf("%s", str + 1);
    n = strlen(str + 1);
    str[n + 1] = '$';
    da(n + 1, 255);
    calch();
    return 0;
}
