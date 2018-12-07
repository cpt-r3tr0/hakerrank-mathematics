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
        for(int i =0; i<T; i++){
            int n= sc.nextInt();
            int k= sc.nextInt();
            int ans= Math.min((1+2*k),2*(n-1-k));
            System.out.println(""+ans);
        }
    }
}
