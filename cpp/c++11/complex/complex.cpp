#include <iostream>
#include <sstream>

class Complex {
    private:
        float m_real;
        float m_img;
    public:
        Complex (float real_ = 0, float img_ = 0):m_real(real_), m_img(img_){}
        float getReal() const { return m_real;};
        float getImg() const { return m_img;};
        Complex operator+(const Complex& other)const{
            
            return Complex(other.m_real + m_real, other.m_img + m_img);
        }
        Complex operator-(const Complex& other)const{
            
            return Complex( m_real - other.m_real, m_img - other.m_img );
        }
        Complex operator*(const Complex& other)const{
            
            return Complex( m_real * other.m_real, m_img * other.m_img );
        }
        Complex operator/(const Complex& other)const{
            
            return Complex( m_real / other.m_real, m_img / other.m_img );
        }
        Complex& operator+=(const Complex& other){
             *this = *this + other;
             return *this;            
        }
        Complex& operator-=(const Complex& other){
            *this = *this - other;
             return *this;            
        }
        Complex& operator*=(const Complex& other){
            *this = *this * other;
             return *this;            
        }
        Complex& operator/=(const Complex& other){
             *this = *this / other;
             return *this;            
        }
        bool operator==(const Complex& other)const{
            return m_real == other.m_real && m_img == other.m_img;
        }

         bool operator!=(const Complex& other)const{
            return !(*this == other);
        }
        friend std::istream& operator>>(std::istream& stream, Complex& obj){
            return stream >> obj.m_real >> obj.m_img;             
        }

        friend std::ostream& operator<<(std::ostream& stream, Complex& obj){
             stream << obj.m_real;
             if(obj.m_img > 0){
                stream << "+";
             }
             return stream << obj.m_img <<"[i]";
        }   


};



void testComplexOperations() {
    Complex c1(3.0, 4.0);  // Complex number 3 + 4i
    Complex c2(1.0, 2.0);  // Complex number 1 + 2i

    // Test addition
    Complex sum = c1 + c2;
    std::cout << "Test Addition: ";
    if (sum == Complex(4.0, 6.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    // Test subtraction
    Complex diff = c1 - c2;
    std::cout << "Test Subtraction: ";
    if (diff == Complex(2.0, 2.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    // Test multiplication (This is not a real multiplication of complex numbers, see your code)
    Complex prod = c1 * c2;
    std::cout << "Test Multiplication: ";
    if (prod == Complex(3.0, 8.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    // Test division (This is not a real division of complex numbers, see your code)
    Complex quot = c1 / c2;
    std::cout << "Test Division: ";
    if (quot == Complex(3.0, 8.0)) {  // Division logic is wrong in the implementation, see explanation below
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed " << c1 << "\n";
    }

    // Test compound assignment operators
    c1 += c2;
    std::cout << "Test += Operator: ";
    if (c1 == Complex(4.0, 6.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    c1 -= c2;
    std::cout << "Test -= Operator: ";
    if (c1 == Complex(3.0, 4.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    c1 *= c2;
    std::cout << "Test *= Operator: ";
    if (c1 == Complex(3.0, 8.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    c1 /= c2;
    std::cout << "Test /= Operator: ";
    if (c1 == Complex(3.0, 4.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed " << c1 << "\n";
    }

    // Test equality operator
    std::cout << "Test == Operator: ";
    if (c1 == Complex(3.0, 4.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    // Test inequality operator
    std::cout << "Test != Operator: ";
    if (c1 != c2) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

     // Test stream insertion and extraction operators
    std::cout << "Test Stream Insertion (<<) Operator: ";
    std::stringstream ss1;
    ss1 << c1;
    std::string result = ss1.str();
    if (result == "3+4[i]") { // assuming the output format is "real+imaginary[i]"
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }

    std::cout << "Test Stream Extraction (>>) Operator: ";
    Complex c3;
    std::stringstream ss2("5.0 6.0");
    ss2 >> c3;
    if (c3 == Complex(5.0, 6.0)) {
        std::cout << "Passed\n";
    } else {
        std::cout << "Failed\n";
    }
}

int main() {
    testComplexOperations();
    return 0;
}