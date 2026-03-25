#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
// this is a numeric hash table program
// enter same numebr to delete that numbers
typedef struct node {
    int data;
    struct node * next;
} node;

int hash_function(int input);
void search(node * table[],int target);
void add(node * table[],int input);
void delete(node * table[],int target);
void free_memory(node * table[]);
int main()
{
    node * temp;
    int input;
    int target;
    int value_num;
    int target_index;
    printf("\n\nYour table has %d indexes!\n\n", SIZE);
    node * hash_table[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    printf("please enter how many number that you want to add to hash_table: ");
    scanf("%d", &value_num);
    for (int i = 0; i < value_num; i++)
    {
        printf("please enter a number:");
        scanf("%d", &input);
        add(hash_table,input);
    }
    
    printf("please enter the number that you want to look for:");
    scanf("%d", &target);
    search(hash_table,target);

    printf("please enter the number that you want to delete:");
    scanf("%d", &target);
    delete(hash_table,target);

    printf("\n\nFreeing the memory...\n\n");
    free_memory(hash_table);

    return 0;
}

int hash_function(int input)  // hash function is a function that turns input values into a numeric values
{
    int index = input % SIZE;
    return index;
}
void add(node * table[],int input)
{
    int index = hash_function(input);
    node * new_node = malloc(sizeof(node));
    new_node->data = input;
    new_node->next = table[index];
    table[index] = new_node;
    printf("%d added to %d th box (index)\n", input, index);
}

void search(node * table[],int target)
{
    int index = hash_function(target);
    int flag = 0;
    node * temp = table[index];
    while (temp != NULL)
    {
        if (temp->data == target)
        {
            flag = 1;
            break; 
        }
        temp = temp->next;
    }
    if (flag == 1)
    {
        printf("\n\n%d found in %d th index!\n\n", target, index);
        return;
    }
    else
    {
        printf("\n\n%d could not found!\n\n");
    }
}

void delete(node * table[],int target)
{
    int index = hash_function(target);
    int flag = 0;
    node * temp = table[index];
    node * control;
    if (table[index] == NULL)
    {
        printf("\n\n%d could not found!\n\n", target);
        return;
    }
    if (table[index]->data != target)
    {
        while (temp->next != NULL)
        {
            if (temp->next->data == target)
            {
                control = temp->next;
                temp->next = control->next;
                free(control);
                flag = 1;
                break;
            }
            temp = temp->next;
        }
    }
    else
    {
        control = temp;
        temp = temp->next;
        table[index] = temp;
        free(control);
        flag = 1;
    }
    
    if (flag == 1)
    {
        printf("\n\n%d deleted succesfully!\n\n", target);
        return;
    }
    else
    {
        printf("\n\n%d could not found!\n\n", target);
    }
}

void free_memory(node * table[])
{
    node * temp;
    node * control;
    for (int i = 0; i < SIZE; i++)
    {
        temp = table[i];
        while (temp != NULL)
        {
            control = temp;
            temp = temp->next;
            free(control);
        }
    }
}