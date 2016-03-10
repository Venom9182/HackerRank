#include <cassert>
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
using namespace std;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

map<string, map<string, string>> attr;
map<string, set<string>> child;
set<string> top;
stack<string> st;

string s;
int p;

void spc() { while (isspace(s[p])) p++; }
char chr() { char x = s[p++]; spc(); return x; }

string word() {
  int q = p;
  while (s[p] && ! isspace(s[p]) && s[p] != '>' && s[p] != '=' && s[p] != '<' && s[p] != '"') p++;
  auto r = s.substr(q, p-q);
  spc();
  return r;
}

string inqq() {
  int q = p;
  string r;
  while (s[p] != '"')
    if (s[p] == '\\')
      r += s[p+1], p += 2;
    else
      r += s[p++];
  return r;
}

void lt() {
  while (s[p]) {
    assert(chr() == '<');
    if (s[p] == '/') {
      chr();
      assert(st.top() == word());
      assert(chr() == '>');
      st.pop();
    } else {
      auto tag = word();
      if (st.size())
        child[st.top()].insert(tag);
      else
        top.insert(tag);
      child[tag];
      st.push(tag);
      while (s[p] != '>') {
        auto key = word();
        assert(chr() == '=');
        assert(chr() == '"');
        auto val = inqq();
        assert(chr() == '"');
        attr[tag][key] = val;
      }
      chr();
    }
  }
}

int main()
{
  int n, m;
  string a;
  cin >> n >> m;
  getline(cin, a);
  stack<string> st;
  while (n--) {
    getline(cin, a);
    s += a;
  }
  spc();
  lt();
  while (m--) {
    getline(cin, a);
    int i = 0;
    string root;
    bool ok = false, tilde = false;
    for(;;) {
      int j = a.find_first_of(".~", i);
      auto tag = a.substr(i, j-i);
      if (j == string::npos) {
        if (tilde && attr[root].count(tag)) {
          cout << attr[root][tag] << endl;
          ok = true;
          break;
        }
        break;
      }
      if (root.empty()) {
        if (top.count(tag))
          root = tag;
        else
          break;
      } else if (child[root].count(tag))
        root = tag;
      else
        break;
      tilde = a[j] == '~';
      i = j+1;
    }
    if (! ok)
      cout << "Not Found!" << endl;
  }
}
