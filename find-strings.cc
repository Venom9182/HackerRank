#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

namespace KoAluru
{
  bool *t;
  int *b;

  template<typename T>
  void bucket(T a[], int n, int k, bool end)
  {
    fill_n(b, k, 0);
    REP(i, n) b[a[i]]++;
    if (end)
      FOR(i, 1, k) b[i] += b[i-1];
    else {
      int s = 0;
      REP(i, k)
        s += b[i], b[i] = s-b[i];
    }
  }

  template<typename T>
  void plus_to_minus(T a[], int sa[], int n, int k)
  {
    bucket(a, n, k, false);
    sa[b[a[n-1]]++] = n-1;
    REP(i, n-1) {
      int j = sa[i]-1;
      if (j >= 0 && ! t[j])
        sa[b[a[j]]++] = j;
    }
  }

  template<typename T>
  void minus_to_plus(T a[], int sa[], int n, int k)
  {
    bucket(a, n, k, true);
    ROF(i, 0, n) {
      int j = sa[i]-1;
      if (j >= 0 && t[j])
        sa[--b[a[j]]] = j;
    }
  }

  template<typename T>
  void ka(T a[], int sa[], int n, int k)
  {
    t[n-1] = false;
    ROF(i, 0, n-1)
      t[i] = a[i] < a[i+1] || a[i] == a[i+1] && t[i+1];
    bool minor = 2 * count(t, t+n, false) > n;
    bucket(a, n, k, minor);
    fill_n(sa, n, -1);
    if (minor) {
      REP(i, n)
        if (t[i])
          sa[--b[a[i]]] = i;
      plus_to_minus(a, sa, n, k);
      minus_to_plus(a, sa, n, k);
    } else {
      sa[b[a[n-1]]++] = n-1;
      REP(i, n-1)
        if (! t[i])
          sa[b[a[i]]++] = i;
      minus_to_plus(a, sa, n, k);
      plus_to_minus(a, sa, n, k);
    }

    int last = -1, name = 0, nn = count(t, t+n, minor), *sa2, *pi;
    if (minor)
      sa2 = sa, pi = sa+n-nn;
    else
      sa2 = sa+n-nn, pi = sa;
    fill_n(b, n, -1);
    REP(i, n)
      if (sa[i] >= 0 && minor == t[sa[i]]) {
        bool diff = last == -1;
        int p = sa[i];
        if (! diff)
          REP(j, n) {
            if (last+j >= n || p+j >= n || a[last+j] != a[p+j] || t[last+j] != t[p+j]) {
              diff = true;
              break;
            } else if (j > 0 && (minor == t[last+j] || minor == t[p+j]))
              break;
          }
        if (diff) {
          name++;
          last = p;
        }
        b[p] = name-1;
      }
    nn = 0;
    REP(i, n)
      if (b[i] >= 0)
        pi[nn++] = b[i];

    if (name < nn)
      ka(pi, sa2, nn, name);
    else
      REP(i, nn)
        sa2[pi[i]] = i;

    ROF(i, 0, nn)
      t[i] = a[i] < a[i+1] || a[i] == a[i+1] && t[i+1];
    nn = 0;
    bucket(a, n, k, minor);
    if (minor) {
      REP(i, n)
        if (minor == t[i])
          pi[nn++] = i;
      REP(i, nn)
        sa[i] = pi[sa2[i]];
      ROF(i, 0, nn) {
        int j = sa[i];
        sa[i] = -1;
        sa[--b[a[j]]] = j;
      }
    } else {
      REP(i, n)
        if (minor == t[i])
          pi[nn++] = i;
      ROF(i, 0, nn)
        sa[n-nn+i] = pi[sa2[i]];
      REP(i, nn) {
        int j = sa[n-nn+i];
        sa[n-nn+i] = -1;
        sa[b[a[j]]++] = j;
      }
    }
    if (minor)
      plus_to_minus(a, sa, n, k);
    else
      minus_to_plus(a, sa, n, k);
  }

  template<typename T>
  void main(T a[], int sa[], int b[], int n, int k)
  {
    if (n > 0) {
      KoAluru::b = b;
      t = new bool[n];
      ka(a, sa, n, k);
      delete[] t;
    }
  }

  template<typename T>
  void calc_rank_lcp(T a[], int sa[], int n, int rnk[], int lcp[])
  {
    REP(i, n)
      rnk[sa[i]] = i ? sa[i-1] : -1;
    int l = 0;
    REP(i, n) {
      int j = rnk[i];
      if (j != -1)
        for (; a[i+l] == a[j+l] && a[i+l]; l++);
      rnk[i] = l;
      l && l--;
    }
    REP(i, n) {
      lcp[i] = rnk[sa[i]];
      rnk[sa[i]] = i;
    }
  }
};

const int N = 50, M = 2000*N+N;
char a[M];
int sa[M], rnk[M], lcp[M], l[M];
ll cnt[M];

int main()
{
  int n = ri(), m = 0;
  REP(i, n) {
    scanf("%s", a+m);
    int len = strlen(a+m);
    FOR(i, m, m+len)
      l[i] = m+len-i;
    m += strlen(a+m);
    a[m++] = i;
  }
  KoAluru::main(a, sa, rnk, m, 127);
  KoAluru::calc_rank_lcp(a, sa, m, rnk, lcp);
  cnt[0] = l[sa[0]];
  FOR(i, 1, m)
    cnt[i] = cnt[i-1]+l[sa[i]]-lcp[i];
  for (int q = ri(); q--; ) {
    int k = ri(), id = lower_bound(cnt, cnt+m, k) - cnt;
    if (id == m)
      puts("INVALID");
    else {
      char &c = a[sa[id]+lcp[id]+k-cnt[id-1]], cc = c;
      c = '\0';
      puts(a+sa[id]);
      c = cc;
    }
  }
}
