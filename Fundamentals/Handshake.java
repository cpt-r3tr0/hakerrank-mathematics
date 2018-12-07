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
        for(int i =0;i <T; i++){
            int n = sc.nextInt();
            if(n>1)
                System.out.println((n*(n-1))/2);
            else
                System.out.println(""+0);
        }
    }
}
