#include <stdio.h>
// selection sort O(n^2) omega(n^2)
int main(void)
{
    int element_num;
    int i;
    int temp;
    int min_index;
    int total_swap = 0;
    printf("please enter your element number:");
    scanf("%d", &element_num);
    int numbers[element_num];
    for (i = 0; i < element_num; i++)
    {
        printf("number[%d]\n", i);
        scanf("%d", &numbers[i]);
    }

    i = 0;
    while (i != element_num - 1)
    {
        min_index = i;
        for (int j = i + 1; j < element_num; j++)  // j = i + 1 because i is the min_index currently we do not have to check it
        {
            if (numbers[j] < numbers[min_index])
            {
               min_index = j;
            }
        }
        temp = numbers[i];
        numbers[i] = numbers[min_index];
        numbers[min_index] = temp;
        total_swap++; 
        i++;
    }

    printf("\n\nyour numbers\n\n");
    for (i = 0; i < element_num; i++)
    {
        printf("%d\n", numbers[i]);
    }
    printf("\ntotal swap = %d\n", total_swap);
}