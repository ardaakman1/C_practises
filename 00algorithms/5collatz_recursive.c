#include <stdio.h>

int collatz(int number, int count);
int main(void)
{
    int number;
    printf("please enter a number:");
    scanf("%d", &number);
    int count = 0;
    printf("\n\nthere are %d steps\n\n", collatz(number, count));
}

int collatz(int number, int count)
{
    if (number == 1)
        return count;
    else if (number % 2 == 0)
    {
        count++;
        return collatz(number /= 2, count);
    }
    else
    {
        count++;
        return collatz(3 * number + 1, count);
    }
}

// In CS50 shorts they did not use count they just say return 1 + collatz(...)
// and when number == 1 return 0;