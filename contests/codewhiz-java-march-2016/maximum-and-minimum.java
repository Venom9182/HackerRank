import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

  public static void print(int A[],int i){
    try{
      System.out.println(A[i]);
    }

    finally {
      List<Integer> a = new ArrayList<Integer>();
      Collections.addAll(a, Arrays.stream(A).boxed().toArray(Integer[]::new));
      System.out.format("%d %d\n", Collections.max(a), Collections.min(a));
    }
  }

  public static void main(String[] args) {
    int N;
    Scanner st=new Scanner(System.in);
    N=st.nextInt();
    int A[]=new int[N];
    for(int i=0;i<N;i++)
    {
      A[i]=st.nextInt();
    }
    int i=st.nextInt();
    try
    {
      print(A,i);

    }
    catch(Exception e){
      System.out.println(e.getClass().getName());
    }

  }// end of main
}// end of Solution
