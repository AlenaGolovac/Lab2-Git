#include <iostream>
#include <stdlib.h>
#include "stringProcessor.h"
#include "sort.h"

int main() {
    std::cout << "=== STARTING MAC TEST ===\n" << std::endl;

    // ТЕСТ 1: Сортування масиву
    std::cout << "Test 1: Sorting array..." << std::endl;
    char* arr[] = { (char*)"banana", (char*)"apple", (char*)"cherry", (char*)"date" };
    size_t length = 4;
    
    quick_sort(arr, length);
    
    std::cout << "Result: ";
    for(int i=0; i<length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n-------------------------\n";

    // ТЕСТ 2: Обробка рядка
    std::cout << "Test 2: Processing string..." << std::endl;
    char inputStr[] = "Fruits: zebra, apple, mango;"; 
    
    std::cout << "Input:  " << inputStr << std::endl;
    char* result = process_string(inputStr);
    
    if (result) {
        std::cout << "Output: " << result << std::endl;
        free(result);
    } else {
        std::cout << "Error: Invalid string format" << std::endl;
    }

    std::cout << "\n=== TESTS FINISHED ===" << std::endl;
    return 0;
}
