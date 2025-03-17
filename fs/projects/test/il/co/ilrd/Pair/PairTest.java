package il.co.ilrd.Pair;

import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.jupiter.api.BeforeEach;

import java.util.Comparator;

import static org.junit.Assert.*;

public class PairTest {

     public static Pair<String, Integer> stringIntegerPair = null;
     public static String str = null;
     public static Integer integer = null;
  @BeforeClass
  public static void reset(){
    str = new String("test");
    integer = new Integer(2);
    stringIntegerPair = Pair.of(str, integer);
  }

  @BeforeEach
  public void resetEach(){
    stringIntegerPair.setKey("test");
    stringIntegerPair.setValue(integer);
  }
    @Test
    public void swap() {
      Pair<Integer,String> integerStringPair = Pair.swap(stringIntegerPair);
      assertEquals( integer, integerStringPair.getKey());
      assertEquals( str, integerStringPair.getValue());
    }



    @Test
    public void setKey() {
    stringIntegerPair.setKey("new string");
    assertEquals("new string", stringIntegerPair.getKey());
    }

    @Test
    public void setValue() {
      Integer integer2 = new Integer(11);
      stringIntegerPair.setValue(integer2);
      assertEquals(integer2, stringIntegerPair.getValue());
    }

    @Test
    public void testHashCode() {

    }

    @Test
    public void testEqualsHashCode() {
      Pair<Integer,String> integerStringPair = Pair.swap(stringIntegerPair);
      Pair<Integer,String> integerStringPair2 = Pair.of(integer,"not test");
      Pair<Integer,String> integerStringPair3 = Pair.of(7, str);

      assertNotEquals(integerStringPair, stringIntegerPair);
      assertNotEquals(integerStringPair, integerStringPair2);
      assertNotEquals(integerStringPair, integerStringPair3);

      assertEquals(integerStringPair,integerStringPair);
      integerStringPair2.setValue("test");
      assertEquals(integerStringPair,integerStringPair2);

      assertEquals(integerStringPair.hashCode(),integerStringPair2.hashCode());
      assertNotEquals(integerStringPair.hashCode(),integerStringPair3.hashCode());
    }

    @Test
  public void testMinMax(){
      class TestClass implements Comparator,Comparable{
        private int index;
        private double dob_num;


        public TestClass(int index, double dob_num) {
          this.index = index;
          this.dob_num = dob_num;
        }

        @Override
        public int compareTo(Object o) {
          return this.index - ((TestClass)o).index;
        }

        @Override
        public int compare(Object o, Object t1) {
          return (int)(this.dob_num - ((TestClass)o).dob_num);
        }
      }

      TestClass obj1 = new TestClass(1,1.2);
      TestClass obj2 = new TestClass(2,2.2);
      TestClass obj3 = new TestClass(5,3.3);
      TestClass obj4 = new TestClass(6,10.1);
      TestClass obj5 = new TestClass(2,2.0);

      TestClass[] arr = {obj1,obj2,obj3,obj4,obj5};
      Pair<TestClass,TestClass> minMaxComparable = Pair.minMax(arr);
      Pair<TestClass,TestClass> minMaxComparator = Pair.minMax(arr, obj1);

      assertEquals(1, minMaxComparable.getKey().index);
      assertEquals(6, minMaxComparable.getValue().index);

      assertEquals(1.2, minMaxComparator.getKey().dob_num);
      assertEquals(10.1, minMaxComparator.getValue().dob_num);


    }
}