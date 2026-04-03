#include <stdio.h>
//bubble sort O(n^2) and omega(n)
int main()
{
    int element_num;
    printf("please enter your arrays element number: ");
    scanf("%d", &element_num);
    int numbers[element_num];
    int i;
    for (i = 0; i < element_num; i++)
    {
        printf("please enter numbers[%d]:", i);
        scanf("%d", &numbers[i]);
    }
    int swap_count = -1;
    int total_count = 0;
    int temp;
    int limit = element_num;
    while (swap_count != 0)
    {
        swap_count = 0;
        i = 0;
        while (i + 1 != limit)
        {
            if (numbers[i] > numbers[i + 1])
            {
                temp = numbers[i + 1];
                numbers[i + 1] = numbers[i];
                numbers[i] = temp;
                swap_count++;
            }
            i++;
            total_count++;
        }
        limit--;
    }

    printf("\n\nYOUR LIST\n\n");
    for (i = 0; i < element_num; i++)
    {
        printf("%d\n", numbers[i]);
    }

    printf("total count = %d", total_count);
    return 0;
}