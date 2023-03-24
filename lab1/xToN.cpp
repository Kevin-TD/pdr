#include <iostream>

int xton(int x, int n) {
    if (n == 0) return 1; 
    return x * xton(x, n - 1);
}

int main() {
    std::cout << xton(2, 3) << "\n";
    std::cout << xton(5, 4) << "\n";
    std::cout << xton(16, 2) << "\n";
    std::cout << xton(4, 4) << "\n";
    std::cout << xton(2, 6) << "\n";

    return 0; 
}