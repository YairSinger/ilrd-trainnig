#ifndef __ILRD_COMPOSITE_H__
#define __ILRD_COMPOSITE_H__
#include <iostream>

class Complex{
    private:
        double m_real;
        double m_imaginary;

    public:
        Complex(double real = 0, double imaginary = 0);
        double getReal() const{return m_real;}
        double getImaginary() const{return m_imaginary;}
        void setReal(double real_){m_real = real_;}
        void setImaginary(double imaginary_){m_imaginary = imaginary_;}
        Complex operator+=(const Complex& other){
            m_real += other.m_real;
            m_imaginary += other.m_imaginary;
            return *this;
        }

        Complex& operator*=(const Complex& other){
            m_real *= other.m_real;
            m_imaginary *= other.m_imaginary;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os_, const Complex& comp){
            os_ << comp.m_real << "+" << comp.m_imaginary << "i";
            return os_;
        }

        friend std::istream& operator>>(std::istream& is_, Complex& comp){
            double real, img;
            char sign, i;

            is_ >> real >> sign >> img >> i;

            if(sign != '+' || i != 'i'){
                std::cout << "invalid complex format" << std::endl;
                return is_;
            }
            

            comp.m_real = real;
            comp.m_imaginary = img;
            return is_;
        }
    
      
};

Complex& operator+(const Complex& comp1, const Complex& comp2);



#endif /* __ILRD_COMPOSITE_H__ */