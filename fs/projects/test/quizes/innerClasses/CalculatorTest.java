package quizes.innerClasses;

import org.junit.Test;

import static org.junit.Assert.*;

public class CalculatorTest {
    @Test
    public void testCalc(){
        Calculator calc = new Calculator();
        assertEquals(4,calc.operate("Addition",1,3));
        assertEquals(4,calc.operate("Subtraction",5,1));
        assertEquals(4,calc.operate("Multiplication",2,2));
        assertEquals(2,calc.operate("Division",8,3));

    }

}