// COP 3502; Lab Assignment 6
// Mia Gonzalez
// March 7, 2024

#include <stdio.h>
#include <stdlib.h>

void bubSort(int arr[], int n, int swap_count[]) {
    int i, j, temp, swaps = 0;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swaps++;
            }
        }
        swap_count[i] += swaps;
        swaps = 0;
    }
    for (i = 0; i < n; i++) {
        swap_count[n] += swap_count[i];
    }
}

void selSort(int arr[], int n, int swap_count[]) {
    int i, j, min_index, temp, swaps = 0;
    for (i = 0; i < n-1; i++) {
        min_index = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_index])
                min_index = j;
        }
        if (min_index != i) {
            temp = arr[min_index];
            arr[min_index] = arr[i];
            arr[i] = temp;
            swaps++;
        }
        swap_count[i] += swaps;
        swaps = 0;
    }
    for (i = 0; i < n; i++) {
        swap_count[n] += swap_count[i];
    }
}

void printArray(int arr[], int swap_count[], int n, const char *array_name) {
    printf("%s:\n", array_name);
    for (int i = 0; i < n; i++) {
        printf("%d: %d\n", arr[i], swap_count[i]);
    }
    printf("Total # of swaps: %d\n\n", swap_count[n]);
}

int main() {
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int n = sizeof(array1) / sizeof(array1[0]);
    int swap_count1[101] = {0}; 
    int swap_count2[101] = {0}; 

    bubSort(array1, n, swap_count1);
    bubSort(array2, n, swap_count2);

    printf("Bubble Sort:\n");
    printArray(array1, swap_count1, n, "array1");
    printArray(array2, swap_count2, n, "array2");

    selSort(array1, n, swap_count1);
    selSort(array2, n, swap_count2);

    printf("Selection Sort:\n");
    printArray(array1, swap_count1, n, "array1");
    printArray(array2, swap_count2, n, "array2");

    return 0;
}
