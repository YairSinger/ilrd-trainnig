//Project: EWeekDay enum
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Oron Shifman
//Date: 4.01.2024
// Status: Approved

package il.co.ilrd.enum_week_day;

//import com.sun.xml.internal.ws.addressing.WsaTubeHelper;
//import il.co.ilrd.SinglyLinkedList.SinglyLinkedList;

import java.util.Arrays;

public enum EWeekDay {
     SUNDAY,
     MONDAY,
     TUESDAY,
     WEDNESDAY,
     THURSDAY,
     FRIDAY,
     SATURDAY;

     public int getDayIntValue(){
         return this.ordinal() + 1;
     }
     public static EWeekDay fromValue(int dayValue){
             switch(dayValue) {
                 case 1:
                     return SUNDAY;
                 case 2:
                     return MONDAY;
                 case 3:
                     return TUESDAY;
                 case 4:
                     return WEDNESDAY;
                 case 5:
                     return THURSDAY;
                 case 6:
                     return FRIDAY;
                 case 7:
                     return SATURDAY;
             }
             return null;
     }
     public static void printAllEWeekDayEnums(){
         System.out.println(Arrays.asList(EWeekDay.values()));
     }
}

