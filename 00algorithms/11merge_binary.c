#include <stdio.h>
//segmentetion fault
void merge_function(int array[], int min, int max);
void merge_sort(int array[], int min,int mid, int max);
int main(void)
{
    int element_num;
    int target;
    printf("Please enter the element_num of your array:");
    scanf("%d", &element_num);
    int array[element_num];
    for (int i = 0; i < element_num; i++)
    {
        printf("array[%d]:", i);
        scanf("%d", &array[i]);
    }
    merge_function(array, 0, element_num - 1);
    printf("\n\nSorted array:\n\n");
    for (int i = 0; i < element_num; i++)
    {
        printf("%d\n", array[i]);
    }

    printf("\nPlease enter the number that you want to search:");
    scanf("%d", &target);
    int high = element_num - 1;
    int low = 0;
    int flag = 0;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (array[mid] > target)
        {
            high = mid - 1;
        }
        else if (array[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            printf("\n\nYour target is:%d\nIt found in index:%d\n\n", target, mid);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("\n\nYour target  could not found!\n\n");
    }
    return 0;
}

void merge_function(int array[], int min, int max)
{
    if (min < max)
    {
        int mid = min + (max - min) / 2;
        merge_function(array, min, mid);  // left array
        merge_function(array, mid + 1, max);  // right array

        merge_sort(array, min, mid, max);
    }
}

void merge_sort(int array[], int min,int mid, int max)
{
    int left_length = mid - min + 1;
    int right_length = max - mid;
    int left_array[left_length];
    int rigth_array[right_length];
    for (int i = 0; i < left_length; i++)
    {
        left_array[i] = array[min + i];
    }
    for (int i = 0; i < right_length; i++)
    {
        rigth_array[i] = array[mid + i + 1];
    }

    int i = 0, j = 0, k = min;  // k is index number of merged array that is why it must start with min
    while (i < left_length && j < right_length)
    {
        if (left_array[i] <= rigth_array[j])
        {
            array[k] = left_array[i];
            i++;
        }
        else
        {
            array[k] = rigth_array[j];
            j++;
        }
        k++;
    }
    while (i < left_length)
    {
        array[k] = left_array[i];
        i++;
        k++;
    }
    while (j < right_length)
    {
        array[k] = rigth_array[j];
        j++;
        k++;
    }
}