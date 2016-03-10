#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) FOR(i, 0, n)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int MOD = 1000000007, N = 100, M = 8, C = (M+1)/2+1, S = 844, P = 3389;
char a[N][M+1];
bool empty[N];
int s, djs[M], info[M], pos[M], b[P], nxt[S];
struct State { int cnt, s; } states[2][S];

int find(int x)
{
  while (djs[x] != x)
    djs[x] = djs[djs[x]], x = djs[x];
  return x;
}

void union0(int x, int y)
{
  x = find(x);
  y = find(y);
  if (x < y)
    djs[y] = x, info[x] |= info[y];
  else if (x > y)
    djs[x] = y, info[y] |= info[x];
}

int main()
{
  int n = ri(), m = ri(), ncur = 1, npre, ans = 0;
  State *cur = states[0], *pre = states[1];
  cur[0].s = 0;
  cur[0].cnt = 1;
  REP(i, n) {
    scanf("%s", a[i]);
    empty[i] = count(a[i], a[i]+m, '.') == 0;
  }
  ROF(i, 0, n-1)
    empty[i] &= empty[i+1];
  REP(i, n) {
    int o = count(a[i], a[i]+m, '?');
    npre = ncur;
    ncur = 0;
    swap(cur, pre);
    fill_n(b, P, -1);
    for (auto j = pre; j < pre+npre; j++)
      REP(mask, 1 << o) {
        // make disjoint sets of current row
        int id = mask, flag = 0;
        fill_n(pos, C, -1);
        fill_n(djs, m, -1);
        fill_n(info, m, 0);
        REP(k, m)
          if (a[i][k] == '.' || a[i][k] == '?' && (flag = id&1, id >>= 1, flag))
            djs[k] = k && djs[k-1] >= 0 ? k-1 : k;
          else
            djs[k] = -1;

        // connect with previous row
        int s, ss = j->s;
        fill_n(pos, C, -1);
        REP(k, m) {
          if (~ djs[k] && ss & 7) {
            if (info[find(k)] & 1 << (ss & 7))
              goto no_update;
            if (~ pos[ss&7])
              union0(k, pos[ss&7]);
            else {
              pos[ss&7] = k;
              info[find(k)] |= 1 << (ss & 7);
            }
          }
          ss >>= 3;
        }

        // check unconnected components
        flag = 0;
        ss = j->s;
        REP(k, m) {
          if (ss & 7 && pos[ss&7] == -1)
            flag |= 1 << (ss & 7);
          ss >>= 3;
        }

        // encode
        id = 1;
        s = 0;
        fill_n(pos, M, -1);
        REP(k, m)
          if (djs[k] == k) {
            pos[k] = id;
            s |= id++ << 3*k;
          } else if (~ djs[k])
            s |= pos[find(k)] << 3*k;
        if (flag) {
          if (__builtin_popcount(flag) == 1 && ! s && empty[i])
            (ans += j->cnt) %= MOD;
          goto no_update;
        }

        for (id = b[s%P]; id != -1; id = nxt[id])
          if (cur[id].s == s) {
            (cur[id].cnt += j->cnt) %= MOD;
            break;
          }
        if (id == -1) {
          nxt[ncur] = b[s%P];
          b[s%P] = ncur;
          cur[ncur].s = s;
          cur[ncur++].cnt = j->cnt;
        }
no_update:;
      }
  }

  REP(i, ncur) {
    int s = cur[i].s;
    REP(j, m) {
      if ((s & 7) > 1)
        goto no_add;
      s >>= 3;
    }
    (ans += cur[i].cnt) %= MOD;
no_add:;
  }
  printf("%d\n", ans);
}
