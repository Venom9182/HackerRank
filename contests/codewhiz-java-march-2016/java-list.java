import java.io.*;
import java.util.*;

public class Solution {
  static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
  static StringTokenizer st;

  public static void main(String[] args) {
    int n = nextInt();
    ArrayList<Integer> a = new ArrayList<Integer>();
    for (int i = 0; i < n; i++)
      a.add(nextInt());
    for (int m = nextInt(); m-- > 0; ) {
      String op = next();
      int x = nextInt();
      if (op.equals("Insert"))
        a.add(x, nextInt());
      else {
        a.remove(x);
      }
    }
    for (int i = 0; i < a.size(); i++)
      System.out.format("%d%c", a.get(i), i == a.size()-1 ? '\n' : ' ');
  }

  static String next() {
    while (st == null || ! st.hasMoreElements()) {
      try {
        st = new StringTokenizer(br.readLine());
      } catch (IOException e) {
      }
    }
    return st.nextToken();
  }

  static int nextInt() {
    return Integer.parseInt(next());
  }
}
