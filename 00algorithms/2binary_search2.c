#include <stdio.h>
// O(log n) Omega(1)
int main(void) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 10, 15, 17 ,19, 45, 57, 100, 689};
    int user_var;
    printf("Please enter the number that you want to search for: ");
    scanf("%d", &user_var);
    int size = sizeof(array) / sizeof(array[0]);
    int high = size - 1;
    int low = 0;
    int flag = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (user_var < array[mid]) {
            high = --mid;
        }

        else if (user_var > array[mid]) {
            low = ++mid;
        }

        else {
            flag = 1;
            printf("Your number has found in %dth index!\n", mid);
            break;
        }
    }

    if (flag == 0) {
        printf("Your number could not found in the array\n");
    }
    return 0;
}