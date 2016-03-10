import java.io.*;
import java.util.*;
interface performOperation{
    int check(int a);
}
class Math{
   public static int checker(performOperation p ,int num){
       return p.check(num);
   }
   performOperation checkEvenOdd() {
     return n -> n % 2;
   }
   performOperation checkPrime() {
     return n -> n > 1 && java.util.stream.IntStream.range(2, n).noneMatch(x -> n % x == 0) ? 0 : 1;
   }
   performOperation checkPalindrome() {
     return n -> reverse(n) == n ? 0 : 1;
   }
   int reverse(int n) {
     int r = 0;
     do {
       r = r*10+n%10;
       n /= 10;
     } while (n > 0);
     return r;
   }
}

public class Solution {

    public static void main(String[] args)throws IOException {
        Math ob = new Math();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T=Integer.parseInt(br.readLine());
        performOperation op;
        int ret =0;
        String ans=null;
        while(T-->0){
            String s=br.readLine().trim();
            StringTokenizer st=new StringTokenizer(s);
            int ch=Integer.parseInt(st.nextToken());
            int num=Integer.parseInt(st.nextToken());
            if(ch==1){
                op = ob.checkEvenOdd();  
                ret = ob.checker(op,num);
                ans = (ret == 0)?"EVEN":"ODD";
            }
            else if(ch==2){
                op = ob.checkPrime();
                ret = ob.checker(op,num);
                ans = (ret == 0)?"PRIME":"COMPOSITE";
            }
            else if(ch==3){
                op = ob.checkPalindrome();
                ret = ob.checker(op,num);
              	ans = (ret == 0)?"PALINDROME":"NOT PALINDROME";

            }
            System.out.println(ans);
        }
    }
          
}
