package quizes;

public class StringsQuize {

    public static void main(String[] args) {
        String str = new String("abcd");
        String str2 = new String("abcba");
        String str3 = new String("abc");

        printReverse(str);
        if(isPalindrome(str) == false && isPalindrome(str2) == true){
            System.out.println("passed isPalindrome");
        }
        else{
            System.out.println(str + " " + isPalindrome(str));
            System.out.println("palindrome " + str2 + " "+ isPalindrome(str));
        }
        printPermutations(str3);

    }
    private static void printReverse(String org){
        char c = '\0';
        int len = org.length() - 1;
        while (len >= 0){
            c = org.charAt(len);
            System.out.println(c);
            --len;
        }
    }

    private static boolean isPalindrome(String str){
        int rInx = str.length() - 1;
        int lInx = 0;
        char left = str.charAt(lInx), right = str.charAt(rInx);

        while (left == right && lInx <= rInx){
            left = str.charAt(lInx);
            ++lInx;
            right = str.charAt(rInx);
            --rInx;
        }
        return lInx > rInx;
    }


    private static void  printPermutations(String str){
        StringBuilder new_str = new StringBuilder(str);
        permute(new_str, 0);
    }
    private static void permute(StringBuilder str, int swapInx){
        int runner = swapInx;
        int len = str.length() - 1;
        if (swapInx == len){
            System.out.println(str);
        }
        else{
            while(runner <= len){
                swap(str,swapInx, runner);
                permute(str, swapInx + 1);
                swap(str,swapInx, runner);
                ++runner;
            }
        }
    }

    private static void swap(StringBuilder str , int inx1, int inx2){
        char a = str.charAt(inx1);
        str.setCharAt(inx1, str.charAt(inx2));
        str.setCharAt(inx2,a);
    }


}
