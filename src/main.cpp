// main.cpp
#include <iostream>
#include "math_lib.h"

int main() {
    std::cout << "2 + 3 = " << MathLib::add(2, 3) << std::endl;
    
    // Задержка перед закрытием окна
    system("pause"); // Только для Windows
    return 0;
}
