#include <stdio.h>

void merge_sort(int numbers[], int min, int max);
void merge(int numbers[], int min, int mid, int max);

int main(void)
{
    int size;
    printf("please enter the element number:");
    scanf("%d", &size);
    int numbers[size];
    for (int i = 0; i < size; i++)
    {
        printf("numbers[%d]:", i);
        scanf("%d", &numbers[i]);
    }
    merge_sort(numbers, 0, size - 1);

    printf("\n\nSORTED ARRAY\n\n");
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

        merge_sort(numbers, min, mid);  // left part
        merge_sort(numbers, mid + 1, max);  // right part

        merge(numbers, min, mid, max);
    }
}

void merge(int numbers[], int min, int mid, int max)
{
    int left_length = mid - min + 1;
    int right_length = max - mid;
    int left_array[left_length];
    int right_array[right_length];
    for (int i = 0; i < left_length; i++)
    {
        left_array[i] = numbers[min + i];
    }
    for (int i = 0; i < right_length; i++)
    {
        right_array[i] = numbers[mid + 1 + i];
    }

    int i = 0, j = 0, k = min;  // k is the merged arrays first index
    while (i < left_length && j < right_length)
    {
        if (left_array[i] <= right_array[j])
        {
            numbers[k] = left_array[i];
            i++;
        }
        else
        {
            numbers[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_length)
    {
        numbers[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_length)
    {
        numbers[k] = right_array[j];
        j++;
        k++;
    }
}