package il.co.ilrd.collection;

import java.util.Map;




//import sun.security.util.ArrayUtil;

import java.util.*;

public class ArrayWrapper {

    public static void main(String[] args) {
        Integer[] integers = new Integer[]{5,8,7,2,1};
        int i = 0;
        for(; i < 5; ++i){
            System.out.println(integers[i]);
        }
        List<Integer> list= new ArrayList<Integer>(Arrays.asList(integers));
        Collections.sort(list);
        System.out.println(list.toString());

        Map<String,Integer> days = new HashMap<>();
        days.put("Sunday", 1);
        days.put("Monday" , 2);
        days.put("Tuesday", 3);
        days.put("Wednesday", 4);
        days.put("Thursday",5);
        days.put("Friday", 6);

        for (Map.Entry<String, Integer> stringIntegerEntry : days.entrySet()) {
            System.out.println(stringIntegerEntry);
        }
        for (Integer value : days.values()) {
            System.out.println(value);
        }
        DataObject obj1 = new DataObject(1,"a");
        DataObject obj2 = new DataObject(3,"b");
        DataObject obj3 = new DataObject(5,"a");
        DataObject obj4 = new DataObject(1,"d");
        DataObject[] arr = {obj1, obj2, obj3, obj4};

        Map<Integer, String> map = new HashMap<>();

        for (int j = 0; j < arr.length; j++) {
            map.put(arr[j].getValue(), arr[j].getCode());
        }

        for (Map.Entry<Integer, String> integerStringEntry : map.entrySet()) {
            System.out.println(integerStringEntry);
        }

    }
}

class DataObject{
    private int value;
    private String code;

    public DataObject(int value, String code) {
        this.value = value;
        this.code = code;
    }

    public int getValue() {
        return value;
    }

    public String getCode() {
        return code;
    }
}