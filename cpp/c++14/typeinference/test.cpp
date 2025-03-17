auto add(int a, int b) {
    return a + b; // Deduces return type as int
}

auto divide(double a, double b) {
    if (b == 0.0) {
        throw "Error: Division by zero"; 
    }
    return a / b; // Deduces return type as double
}

auto Fact(unsigned int n)
    {
        if (n == 0) {
            return 1u;
        }

        return n * Fact(n - 1);
    }

int main() {
    auto result1 = add(5, 3); // result1 is deduced as int
    auto result2 = divide(10.0, 2.0); // result2 is deduced as double

    return 0;
}