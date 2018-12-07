import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        Scanner sc = new Scanner(System.in);
        int row = sc.nextInt();
        int col = sc.nextInt();
        int yrow;
        int xcol;
        col--;
        boolean isEven;
        isEven = row % 2 == 0;
        xcol = isEven ? 1 : 0;
        xcol += (col*2);
        yrow = isEven ? (row / 2) - 1 : row / 2;
        if (yrow == 0) System.out.println(""+xcol);
        else System.out.println(""+yrow+""+xcol);
    }
}
