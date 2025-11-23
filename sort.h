#ifndef SORT
#define SORT
#include "stringProcessor.h"
#include <cstring> // Потрібно для strcmp

// Функція обміну вказівників (Swap)
void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Допоміжна рекурсивна функція для QuickSort
void quickSortRecursive(char** arr, int low, int high) {
    if (low < high) {
        char* pivot = arr[high]; // Опорний елемент
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            // Порівнюємо рядки: якщо arr[j] < pivot
            if (strcmp(arr[j], pivot) < 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);
        int pi = i + 1;

        // Рекурсивні виклики
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

// Головна функція, яку викликає програма
void quick_sort(char** arr, size_t length)
{
   if (length > 0) {
       quickSortRecursive(arr, 0, length - 1);
   }
}
#endif // !SORT