import java.io.*;
import java.util.*;

public class Solution {
  static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
  static StringTokenizer st;

  public static void main(String[] args) {
    int n = nextInt(), m = nextInt();
    BitSet[] a = {new BitSet(n), new BitSet(n)};
    for (int i = 0; i < m; i++) {
      String op = next();
      int x = nextInt(), y = nextInt();
      switch (op) {
        case "AND":
          a[x-1].and(a[y-1]);
          break;
        case "OR":
          a[x-1].or(a[y-1]);
          break;
        case "XOR":
          a[x-1].xor(a[y-1]);
          break;
        case "FLIP":
          a[x-1].flip(y);
          break;
        case "SET":
          a[x-1].set(y);
          break;
      }
      System.out.format("%d %d\n", a[0].cardinality(), a[1].cardinality());
    }
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
