package quizes;

import java.io.FilterOutputStream;
import java.util.HashMap;
import java.util.Map;

public class MinimunSubstring {
    public  static String findMinSubString(String big, String small){
        Map<Character,Integer> map = new HashMap<>();
        String minSubstring = big.substring(0, big.length());
        boolean found = false;

        for(int i = 0; i < big.length(); ++i){
            initMap(map,small);
           if (!isMoveToNextMatch(big,i,map)){
               break;
           }
            for (int j = 0;j - i < minSubstring.length() &&  j < big.length(); j++) {
                map.remove(big.charAt(j));
                if(map.isEmpty()){
                    found = true;
                    if(j - i < minSubstring.length()){
                        minSubstring = big.substring(i , j);
                    }
                    break;
                }

            }
        }
        return  found ? minSubstring : "not found";
    }

    public static void initMap(Map<Character,Integer> map, String string){
        for (int i = 0; i < string.length(); i++) {
            map.put(string.charAt(i),1);
        }
    }

    public static boolean isMoveToNextMatch(String big, int inx, Map<Character,Integer> map){
        while(!map.containsKey(big.charAt(inx)) && inx < big.length() - 1){
            ++inx;
        }
       return inx != big.length() - 1;
    }

    public static void main(String[] args) {
        System.out.println(findMinSubString("abced5e5kuirsd57erfcxde", "e7"));
    }
}
