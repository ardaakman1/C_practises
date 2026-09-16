#include <stdio.h>

void merge(int array[], int low, int high);
void merge_function(int array[], int low, int mid, int high);
int main(void) {
    int size;
    printf("Please enter the index number of your array:");
    scanf("%d", &size);
    int user_array[size];
    for (int i = 0; i < size; i++) {
        printf("array[%d]:", i);
        scanf("%d", &user_array[i]);
    }
    merge(user_array, 0, size - 1);
    printf("\nSORTED ARRAY\n");
    for (int i = 0; i < size; i++) {
        printf("array[%d]: %d\n", i, user_array[i]);
    }
    return 0;
}

void merge(int array[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge(array, low, mid);  // left array
        merge(array, mid + 1, high);  // rigth array
        merge_function(array, low, mid, high);
    }
}

void merge_function(int array[], int low, int mid, int high) {
    int left_length = mid - low + 1;
    int right_length = high - mid;
    int left_array[left_length];
    int right_array[right_length];
    for (int i = 0; i < left_length; i++) {
        left_array[i] = array[low + i];
    }
    for (int i = 0; i < right_length; i++) {
        right_array[i] = array[mid + 1 + i];
    }

    int i = 0, j = 0, k = low;  // k is an index number of merged array
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

    while(j < right_length) {
        array[k] = right_array[j];
        j++;
        k++;
    }

}