public class Atoi {
    public static int atoi (String str){
        int inx = 0;
        int sign = 1;
        int res = 0;
        int len = str.length();
        char c = str.charAt(inx);

        while (c == ' ' && inx < len){
            c = str.charAt(++inx);
        }

        if (c == '-'){
            c = str.charAt(++inx);
            sign = -1;
        }

       for (;inx  < len && str.charAt(inx) >= '0' && str.charAt(inx) <= '9' ; ++inx){
           c = str.charAt(inx);
           res *= 10;
           res += c - '0';
       }

        return res * sign;
    }
}
