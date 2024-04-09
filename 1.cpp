#include <iostream>

template<typename T>
bool Check_2_degree(T a) {

    static_assert(std::is_integral<T>::value);

    if (a <= 0)
        return false;
    
    while (a) {
        if (a % 2 == 0)
            a = a >> 1;
        else {
            if (a == 1)
                return true;
            return false;
        }
    }

    return true;
}

int main()
{
    int a;

    std::cout << "Enter number: " << std::endl;
    std::cin  >> a;
    std::cout << Check_2_degree(a) << std::endl;

    char b;

    std::cout << "Enter char: " << std::endl;
    std::cin  >> b;
    std::cout << static_cast<int>(b) << std::endl;
    std::cout << Check_2_degree(b) << std::endl;

    return 0;
}