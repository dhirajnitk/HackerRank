import java.util.*;
public class UniformMax{
    static int findUniformMax(int [] arr) {
        Vector<Integer>v = new Vector<Integer>();
        int MAX = Integer.MIN_VALUE;
        for(int i = 0; i <arr.length; i++) {
            if(arr[i] >=MAX) {
                MAX = arr[i];
                if(! v.isEmpty ()&& arr[v.get(0)] < MAX) 
                    v.clear();
                v.add(i);
            }
        }
        Random r = new Random();
        int index = Math.abs(r.nextInt()) % (v.size()-1) ;
        return v.get(index);
    }
    public static void main(String[] args){
        int [] arr = { 1,3, 6 ,4, 8, 7, 8, 8, 8, 8, 8, 5};
        System.out.println(Arrays.toString(arr));
         System.out.println(findUniformMax(arr));
    }
}