#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define SIZE 5
typedef struct node {
    int value;
    struct node * next;
} node;

int hash_function(int number);
void add_table(node * table[], int number);
int find_target(node * table[], int target);
void delete_function(node * table[], int target);
void show_table(node * table[]);
void free_memory(node * table[]);

int main(void)
{
    node * temp = NULL;
    int element_num;
    int number;
    int target;
    printf("\nYour table has %d indexes!\n", SIZE);
    node * table[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = NULL;  // I make all indexes NULL because they will eventually become end of the array
    }
    printf("Please enter the element number your table:");
    scanf("%d", &element_num);
    for (int i = 0; i < element_num; i++)
    {
        printf("Please enter a number:");
        scanf("%d", &number);
        add_table(table, number);
    }
    printf("Please enter the number that you want to search for: ");
    scanf("%d", &target);
    number = find_target(table, target);
    if (number == 0)
    {
        printf("\n%d could not found in this table!\n", target);
    }
    else
    {
        printf("\n%d found in %d th and its %d th element\n", target, hash_function(target), number);
    }

    printf("Do you want to delete an element?(y/n)");
    char choice;
    getchar();
    scanf("%c", &choice);
    if (toupper(choice) == 89)
    {
        printf("Please enter the number that you want to delete: ");
        scanf("%d", &target);
        delete_function(table, target);
    }

    printf("\n\nShowing the table...\n\n");
    show_table(table);

    printf("\n\nFreeing the memory...\n\n");
    free_memory(table);

}

int hash_function(int number)
{
    return number % SIZE;
}

void add_table(node * table[], int number)
{
    int index = hash_function(number);
    node * new_node = malloc(sizeof(node));
    new_node->value = number;
    new_node->next = table[index];
    table[index] = new_node;
}

int find_target(node * table[], int target)
{
    int index = hash_function(target);
    node * temp = table[index];
    int count = 1;  // becuase it is not an array I will say it as element number
    int flag = 0;
    while (temp != NULL)
    {
        if (temp->value == target)
        {
            flag = 1;
            break;
        }
        temp = temp->next;
        count++;
    }
    if (flag == 0) return 0;
    else return count;
}

void delete_function(node * table[], int target)
{
    int index = hash_function(target);
    node * temp = table[index];
    node * control = NULL;
    node * prev = NULL;
    while (temp != NULL)
    {
        if (temp->value == target)
        {
            control = temp;
            temp = temp->next;
            if (control == table[index])
            {
                table[index] = table[index]->next;
            }
            else
            {
                prev->next = temp;
            }
            free(control);
            printf("\nYour target is succesfully deleted!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("\nCould not found your target!\n");
}

void show_table(node * table[])
{
    for (int i = 0; i < SIZE; i++)
    {
        node * temp = table[i];
        printf("\nindex: %d\n\n", i);
        while (temp != NULL)
        {
            printf("%d\n", temp->value);
            temp = temp->next;
        }
    }
}

void free_memory(node * table[])
{
    for (int i = 0; i < SIZE; i++)
    {
        node * temp = table[i];
        node * control = NULL;
        while (temp != NULL)
        {
            control = temp;
            temp = temp->next;
            free(control);
        }
    }
}