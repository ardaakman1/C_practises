#include <stdio.h>
// merge sort and binary search

void merge(int array[], int min, int max);
void merge_function(int array[], int min, int mid, int max);
int binary_search(int array[], int target, int size);
int main(void) {
    int size;
    printf("Please enter the index number of your array:");
    scanf("%d", &size);
    int array[size];
    for (int i = 0; i < size; i++) {
        printf("array[%d]:", i);
        scanf("%d", &array[i]);
    }
    merge(array, 0, size - 1);
    printf("\nSORTED ARRAY\n");
    for (int i = 0; i < size; i++) {
        printf("array[%d]: %d\n", i, array[i]);
    }
    int target;
    printf("\n\nPlease enter the number that you want to search for: ");
    scanf("%d", &target);
    int result_of_search = binary_search(array, target, size);
    if (result_of_search == -1) {
        printf("Your target could not found\n");
    }

    else {
        printf("Your target is in index %d!\n", result_of_search);
    }
    return 0;
}

void merge(int array[], int min, int max) {
    if (min < max) {
        int mid = min + (max - min) / 2;
        merge(array, min, mid);  // LEFT
        merge(array, mid + 1, max);  // RIGHT
        merge_function(array, min, mid, max);
    }
}

void merge_function(int array[], int min, int mid, int max) {
    int left_length = mid - min + 1;
    int right_length = max - mid;
    int left_array[left_length];
    int right_array[right_length];
    for (int i = 0; i < left_length; i++) {
        left_array[i] = array[min + i];
    }
    for (int i = 0; i < right_length; i++) {
        right_array[i] = array[mid + 1 + i];
    }

    int i = 0, j = 0, k = min;
    while (i < left_length && j < right_length) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        }

        else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_length) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_length) {
        array[k] = right_array[j];
        j++;
        k++;
    }
}

int binary_search(int array[], int target, int size) {
    int high = size - 1;
    int low = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (array[mid] < target) {
            low = ++mid;
        }

        else if (array[mid] > target) {
            high = --mid;
        }

        else {
            return mid;
        }
    }

    return -1;
}