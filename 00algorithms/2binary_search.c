#include <stdio.h>
// we do this in sorted arrays (logically)
// O(log n) omega(1)
int main()
{
    int numbers[] = {1, 2, 5, 6, 8, 10, 14 ,15 ,17 ,19 ,21, 23, 27, 29, 30, 31, 33 ,36 ,39 ,40};
    int my_number;
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int high = size - 1;
    int low = 0;
    int flag = 0;
    printf("please enter the number that you want to search: ");
    scanf("%d", &my_number);
    while (low <= high)
    {
        int mid = low + (high - low) / 2; // we do this because of integer overflow
        if (numbers[mid] > my_number)
        {
            high = mid - 1;
        }
        else if (numbers[mid] < my_number)
        {
            low = mid + 1;
        }
        else
        {
            printf("your number is at : index :%d\n", mid);
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("your number is not in the array!\n");
    }
    return 0;
}

