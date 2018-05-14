import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;

public class Solution {

 /*
     * Complete the findNumber function below.
     */
    static String findNumber(int[] arr, int k) {
        /*
         * Write your code here.
         */
            
         boolean found = Arrays.stream(arr).anyMatch(x -> x == k);
         if(found)
             return "YES";
        else
            return "NO";
    }




 private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));

        int arrCount = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])*");

        int[] arr = new int[arrCount];

        for (int arrItr = 0; arrItr < arrCount; arrItr++) {
            int arrItem = scanner.nextInt();
            scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])*");
            arr[arrItr] = arrItem;
        }

        int k = scanner.nextInt();
        scanner.skip("(\r\n|[\n\r\u2028\u2029\u0085])*");

        String res = findNumber(arr, k);

        bufferedWriter.write(res);
        bufferedWriter.newLine();

        bufferedWriter.close();

        scanner.close();
    }
}

