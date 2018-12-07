import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i=0; i<T ;i++){
            int l = sc.nextInt(),
                b = sc.nextInt();
            int fac = gcd(l,b);
            int piece = (l*b*1)/(1*fac*fac);
            System.out.println( "" +piece);
        }
    }


    private static int gcd(int a, int b) {

        int temp;
        // make a greater than b
        if (b > a) {
         temp = a;
         a = b;
         b = temp;
    }

    while (b !=0) {
        // gcd of b and a%b
        temp = a%b;
        // always make a greater than bf
        a =b;
        b =temp;

    }
    return a;
}
}
