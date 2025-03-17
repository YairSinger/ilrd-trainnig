#include <iostream>

template <typename T>
void myMemcpy(T *dest, const T *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}

int main()