package il.co.ilrd.Complex;

import il.co.ilrd.complex.Complex;
import org.junit.jupiter.api.*;

import static org.junit.jupiter.api.Assertions.*;

class ComplexTest {
   static Complex com1;
   static Complex com2;
    static Complex com3;
    @BeforeAll
    public static void setUp(){
        com1 = Complex.createFromReal(5.2);
        com1.setImaginary(-2);
        com2 = Complex.createFromReal(3);
        com2.setImaginary(4);
        com3 = Complex.createFromReal(0);
        com3.setImaginary(0);
    }

    @AfterEach
    public void resetAfterTest(){
        com1.setReal(5.2);
        com1.setImaginary(-2);
        com2.setReal(3);
        com2.setImaginary(4);
        com3.setReal(0);
        com3.setImaginary(0);
    }


    @Test
    @DisplayName("createFromRealPositive")
    void createFromRealPositive() {
        Complex cpx = Complex.createFromReal(5);
        assertEquals(5,cpx.getReal() );
        assertEquals(0,cpx.getImaginary());
    }

    @Test
    @DisplayName("createFromRealNegative")
    void createFromRealNegative() {
        Complex cpx = Complex.createFromReal(-5);
        assertEquals(-5,cpx.getReal());
        assertEquals(0,cpx.getImaginary());
    }

    @Test
    @DisplayName("createFromRealZero")
    void createFromRealZero() {
        Complex cpx = Complex.createFromReal(0);
        assertEquals(0 , cpx.getReal());
        assertEquals(0,cpx.getImaginary());
    }
    @Test
    @DisplayName("createFromImaginaryPos")
    void createFromImaginaryPos() {
        Complex cpx = Complex.createFromImaginary(5);
        assertEquals(5,cpx.getImaginary());
        assertEquals(0 , cpx.getReal());
    }

    @Test
    @DisplayName("createFromImaginaryNeg")
    void createFromImaginaryNeg() {
        Complex cpx = Complex.createFromImaginary(-5);
        assertEquals(-5,cpx.getImaginary());
        assertEquals(0 , cpx.getReal());
    }

    @Test
    @DisplayName("createFromImaginaryZ")
    void createFromImaginaryZ() {
        Complex cpx = Complex.createFromImaginary(0);
        assertEquals(0,cpx.getImaginary());
        assertEquals(0 , cpx.getReal());
    }


    @Test
    @DisplayName("setReal")
    void setReal() {
        Complex cpx = Complex.createFromReal(5);
        cpx.setReal(-3);
        assertEquals(-3 , cpx.getReal());
        cpx.setReal(0);
        assertEquals(0 , cpx.getReal());
    }

    @Test
    @DisplayName("setImaginary")
    void setImaginary() {
        Complex cpx = Complex.createFromImaginary(5);
        cpx.setImaginary(-3);
        assertEquals(-3 , cpx.getImaginary());
        cpx.setImaginary(0);
        assertEquals(0 , cpx.getImaginary());
    }

    @Test
    @DisplayName("addTwoValidComplex")
    void add() {
        Complex res = Complex.createFromReal(8.2);
        res.setImaginary(2);
        com3 = Complex.add(com1,com2);
        assertEquals(com3, res);
    }

    @Test
    @DisplayName("substractValidComplex")
    void substractValidComplex() {
        Complex res = Complex.createFromReal(2.2);
        res.setImaginary(-6);
        com3 = Complex.substract(com1,com2);
        assertEquals(com3, res);
    }

    @Test
    void parse() {

    }

    @Test
    @DisplayName("testEqualsTrue")
    void testEqualsTrue() {
        com2.setReal(com1.getReal());
        com2.setImaginary(com1.getImaginary());
        assertTrue(com2.equals(com1) && com1.equals(com2));
    }
    @Test
    @DisplayName("testEqualsSelf")
    void testEqualsSelf() {
        assertTrue(com2.equals(com2));
    }

    @Test
    @DisplayName("testEqualsFalse")
    void testEqualsFalse() {
        assertNotEquals(com2, com1);
    }

    @Test
    void testToString() {
        String com1Str = "5.2 -2.0 i";
        String com2Str = "3.0 +4.0 i";
        assertTrue(com1Str.equals(com1.toString()) && com2Str.equals(com2.toString()));
    }

    @Test
    @DisplayName("compareTo")
    void compareTo() {
        com2.setReal(com1.getReal());
        com2.setImaginary(com1.getImaginary());
        assertEquals(0, com1.compareTo(com2));
        assertEquals(-1, com2.compareTo(com3));
        assertEquals(1, com3.compareTo(com2));
    }

    @Test
    void testHashCode() {
        com2.setReal(com1.getReal());
        com2.setImaginary(com1.getImaginary());
        assertEquals(com2.hashCode(),com1.hashCode());
        assertNotEquals(com2.hashCode(), com3.hashCode());
    }
}