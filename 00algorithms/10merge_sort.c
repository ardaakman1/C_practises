#include <stdio.h>

void merge_sort(int numbers[], int min, int max);
void merge_function(int numbers[], int min, int mid, int max);
int main (void)
{
    int element_num;
    printf("Please enter the element number of your array:");
    scanf("%d", &element_num);
    int numbers[element_num];
    for (int i = 0; i < element_num; i++)
    {
        printf("numbers[%d]:", i);
        scanf("%d", &numbers[i]);
    }
    merge_sort(numbers, 0, element_num - 1);
    printf("\n\nSORTED ARRAY\n\n");
    for (int i = 0; i < element_num; i++)
    {
        printf("%d\n", numbers[i]);
    }
}

void merge_sort(int numbers[], int min, int max)
{
    if (min < max)
    {
        int mid = min + (max - min) / 2;
        merge_sort(numbers, min, mid);  // left array
        merge_sort(numbers, mid + 1, max);  // right array

        merge_function(numbers, min, mid, max);
    }
}

void merge_function(int numbers[], int min, int mid, int max)
{
    int left_length = mid - min + 1;
    int right_length = max - mid;
    int left_array[left_length];
    int rigth_array[right_length];
    for (int i = 0; i < left_length; i++)
    {
        left_array[i] = numbers[min + i];
    }
    for (int i = 0; i  < right_length; i++)
    {
        rigth_array[i] = numbers[mid + 1 + i];
    }
    int i = 0, j = 0, k = min;  // k is index number of merged array
    while (i < left_length && j < right_length)
    {
        if (left_array[i] < rigth_array[j])
        {
            numbers[k] = left_array[i];
            i++;
        }
        else
        {
            numbers[k] = rigth_array[j];
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
        numbers[k] = left_array[j];
        j++;
        k++;
    }
}