import java.util.*;

public class BinarySearch<T>{
    public <T extends Comparable<T>> boolean binarySearchRecursive(T[] array, T x, int left, int right){
        if (left > right)
            return false;
        else{
            int mid = left + (right - left)/2;
            if(array[mid] == x)
                return true;
            else if(array[mid].compareTo(x) <0)
                return binarySearchRecursive(array,x, mid +1, right);
            else 
                return binarySearchRecursive(array,x, left, mid-1);

        }
    }

    public <T extends Comparable<T>> boolean binarySearchIterative(T[] array, T x){
        int left = 0;
        int right = array.length-1;
        while(left <= right) {
            int mid = left + (right - left)/2;
            if(array[mid] == x)
                return true;
            else if(array[mid].compareTo(x)<0)
                 left = mid + 1;
            else 
                 right = mid -1;
         }
         return false;
    }

    public  <T extends Comparable<T>> int  binarySearchIterativeFastRight(T[] array, T x){
        int left = 0;
        int right = array.length;
        while(right - left >1) {
            int mid = left + (right - left)/2;
            if(array[mid].compareTo(x) <=0)
                left = mid;
            else
                right = mid;
         }
         return left;
    }

    public  <T extends Comparable<T>> int  binarySearchIterativeFastLeft(T[] array, T x){
        int left = -1;
        int right = array.length-1;
        while(right - left >1) {
            int mid = left + (right - left)/2;
            if(array[mid].compareTo(x) >=0)
                right = mid;
            else
                left = mid;
         }
         return right;
    }

    public  <T extends Comparable<T>> boolean binarySearchRecursive(T [] array, T x) {
        return binarySearchRecursive(array,x, 0, array.length-1);
    }
    public static void main(String [] args) {
        Integer [] arr = { 1, 3, 5, 7, 9, 10, 10 ,10 ,10, 11, 13};
        BinarySearch bSearch = new BinarySearch();
        System.out.println(bSearch.binarySearchRecursive(arr, 7));
        System.out.println(bSearch.binarySearchIterative(arr,7));
        System.out.println(bSearch.binarySearchIterativeFastRight(arr,10));
        System.out.println(bSearch.binarySearchIterativeFastLeft(arr,10));
    }
}