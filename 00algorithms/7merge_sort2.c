#include <stdio.h>
// O(n * logn) omega(n * logn)
void merge_sort(int numbers[], int min, int max);
void merge(int numbers[], int min, int mid, int max);

int main(void)
{
    int size;
    printf("\nPlease enter the element number: ");
    scanf("%d", &size);
    int numbers[size];
    for (int i = 0; i < size; i++)
    {
        printf("numbers[%d]: ", i);
        scanf("%d", &numbers[i]);
    }
    merge_sort(numbers, 0, size - 1);

    printf("\n\nYOUR SORTED ARRAY\n\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", numbers[i]);
    }
}

void merge_sort(int numbers[], int min, int max)
{
    if (min < max)
    {
        int mid = min + (max - min) / 2;

        merge_sort(numbers, min, mid); // left part
        merge_sort(numbers, mid + 1, max); // right part

        merge(numbers, min, mid, max);
    }
}

void merge(int numbers[], int min, int mid, int max)
{
    int i, j, k;
    int left_length = mid - min + 1;
    int right_length = max - mid;
    int left_temp[left_length], right_temp[right_length];  // temporary arrays
    for (i = 0; i < left_length; i++)
    {
        left_temp[i] = numbers[min + i];
    }

    for (i = 0; i < right_length; i++)
    {
        right_temp[i] = numbers[mid + 1 + i];
    }

    i = 0, j = 0, k = min;
    while (i < left_length && j < right_length)
    {
        if (left_temp[i] <= right_temp[j])
        {
            numbers[k] = left_temp[i];
            i++;
        }
        else
        {
            numbers[k] = right_temp[j];
            j++;
        }
        k++;
    }

    while (i < left_length)
    {
        numbers[k] = left_temp[i];
        i++;
        k++;
    }

    while (j < right_length)
    {
        numbers[k] = right_temp[j];
        j++;
        k++;
    }
}

// if array is sorted bubble sort might be better
// but if its average or worst scenerio merge sort will be faster
// just it will use more memory