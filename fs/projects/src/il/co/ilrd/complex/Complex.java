//Project: Complex
//Group: ilrd_fs149-150
//Writer: Yair Singer
//Reviewer: Isreal Weiss
//Date: 4.01.2024
//

package il.co.ilrd.complex;

import static java.lang.Double.doubleToLongBits;

public class Complex implements Comparable<Complex> {
    private double real;
    private double imaginary;




    private Complex(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public static Complex createFromReal(double real) {
        return new Complex(real, 0);
    }

    public static Complex createFromImaginary(double imaginary) {
        return new Complex(0, imaginary);
    }

    public double getReal() {
        return real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setReal(double newReal) {
        real = newReal;
    }

    public void setImaginary(double newImaginary) {
        imaginary = newImaginary;
    }

    public static Complex add(Complex c, Complex z) {
        return new Complex(c.real + z.real, c.imaginary + z.imaginary);
    }

    public static Complex substract(Complex c, Complex z) {
        return new Complex(c.real - z.real, c.imaginary - z.imaginary);
    }

    // public Complex parse (String strComplex); /* Advanced */

    @Override
    public boolean equals(Object other) {
        if (other instanceof Complex){
            return (this.real == ((Complex) other).real && this.imaginary == ((Complex) other).imaginary);
        }
        else{
            return false;
        }
    }


    @Override
    public String toString() {
        return (real + " " + (imaginary >= 0 ? "+" : "") + imaginary + " i");
    }

    @Override
    public int compareTo(Complex obj) {
        double cmp =  (real - obj.real);
        if (cmp == 0) {
            cmp = (int) (imaginary - obj.imaginary);
            if (cmp == 0) {
                return 0;
            } else {
               return cmp < 0 ? 1 : -1;
            }
        } else {
          return  cmp < 0 ? 1 : -1;
        }
    }

    @Override
    public int hashCode(){
        long bits = doubleToLongBits(real + imaginary);
        return (int)(bits ^ (bits >>> 32));
    }
}