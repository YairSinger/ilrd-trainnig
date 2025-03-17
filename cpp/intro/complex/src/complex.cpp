#include "../include/complex.hpp"

Complex::Complex(double real, double imaginary):
            m_real(real), m_imaginary(imaginary){}

Complex& operator+(const Complex& comp1, const Complex& comp2){
    Complex res(comp1.getReal() + comp2.getReal(), comp1.getImaginary() + comp2.getImaginary());
    return res;
}





