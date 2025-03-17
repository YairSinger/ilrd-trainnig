package il.co.ilrd.EWeekDay;

//import il.co.ilrd.SinglyLinkedList.SinglyLinkedList;
import il.co.ilrd.enum_week_day.EWeekDay;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class EWeekDayTest {

    @Test
    @DisplayName("getDayIntValueValidDay")
    void getDayIntValueValidDay() {
        EWeekDay day = EWeekDay.FRIDAY;
        assertEquals(6,day.getDayIntValue());
        day = EWeekDay.SATURDAY;
        assertEquals(7,day.getDayIntValue());
        day = EWeekDay.SUNDAY;
        assertEquals(1,day.getDayIntValue());
    }

    @Test
    @DisplayName("fromValueValid")
    void fromValueValid() {
       assertSame(EWeekDay.fromValue(3) , EWeekDay.TUESDAY);
    }

    @Test
    @DisplayName("fromValueValid")
    void fromValueInvalid() {
        assertNull(EWeekDay.fromValue(10));
    }

    @Test
    void printAllEWeekDayEnums() {
        EWeekDay.printAllEWeekDayEnums();
    }
}