#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26
#define SENTENCE_SIZE 80

typedef struct node {
    char word[SENTENCE_SIZE];
    struct node * next;
} node;

int hash_function(char input[]);
void add(node * table[], char input[]);
void search(node * table[], char target[]);
void delete_function(node * table[], char target[]);
void show(node * table[]);
void free_memory(node * table[]);
int main()
{
    node * table[SIZE];
    char input[SENTENCE_SIZE];
    char target[SENTENCE_SIZE];
    char choice;

    for (int i = 0; i < SIZE; i++)
    {
        table[i] = NULL;
    }
    while (1)
    {
        printf("please enter a sentence (max %d characters) (enter EXIT to exit the program):", SENTENCE_SIZE);
        fgets(input, SENTENCE_SIZE, stdin);
        if (strcmp(input, "EXIT\n") == 0) break;
        if (isalpha(input[0]) == 0)
        {
            printf("the first charachter must be a letter!\n");
            continue;
        }
        add(table, input);
    }

    printf("please enter the sentence that you want to search for: ");
    fgets(target, SENTENCE_SIZE, stdin);
    search(table, target);
    
    char temp_choice[10];
    printf("Do you want to delete a sentence:(y/n) ");
    fgets(temp_choice, 10, stdin);
    choice = temp_choice[0];
    if (toupper(choice) == 89)
    {
        printf("please enter the sentence that you want to delete: ");
        fgets(target, SENTENCE_SIZE, stdin);
        delete_function(table, target);
    }
    
    printf("\n\nShowing the current table:\n\n");
    show(table);

    printf("\n\nfreeing the memory...\n\n");
    free_memory(table);
}

int hash_function(char input[])
{
    return toupper(input[0]) - 'A';
}

void add(node * table[],char input[])
{
    int index = hash_function(input);
    node * new_node = malloc(sizeof(node));
    strcpy(new_node->word, input);
    new_node->next = NULL;
    if (table[index] == NULL)
    {
        table[index] = new_node;
    }
    else
    {
        new_node->next = table[index];
        table[index] = new_node;
    }
}

void search(node * table[], char target[])
{
    int index = hash_function(target);
    node * temp = table[index];
    while (temp != NULL)
    {
        if (strcmp(temp->word, target) == 0)
        {
            printf("your target found in index %d!\n\n", index);
            return;
        }
        temp = temp->next;
    }
    printf("Your word could not found\n\n");
}

void delete_function(node * table[], char target[])
{
    int index = hash_function(target);
    if (table[index] == NULL) {  // I did this because if the index is NULL and we would try to look the index the program will return a segmentation fault
        printf("\n\nSentence not found in this index!\n\n");
        return;
    }
    int flag = 0;
    node * temp = table[index];
    node * control = NULL;
    if (strcmp(table[index]->word, target) == 0)
    {
        table[index] = temp->next;
        free(temp);
        flag = 1;
    }
    else
    {
        while (temp->next != NULL)
        {
            if (strcmp(temp->next->word, target) == 0)
            {
                control = temp->next;
                if (control->next == NULL)
                {
                    temp->next = NULL;
                    free(control);
                    flag = 1;
                    break;
                }
                temp->next = control->next;
                free(control);
                flag = 1;
                break;
            }
            temp = temp->next;
        }
    }
    if (flag == 1)
    {
        printf("\n\nYour sentence is succesfully deleted!\n\n");
        return;
    }
    printf("\n\nYour sentence could not found\n\n");
}

void show(node * table[])
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("\nindex[%d]:\n\n", i);
        if (table[i] != NULL)
        {
            node * temp = table[i];
            while (temp != NULL)
            {
                printf("%s\n", temp->word);
                temp = temp->next;
            }
        }
        else
        {
            printf("\n\nEMPTY\n\n");
        }
    }
}

void free_memory(node * table[])
{
    node * control = NULL;
    for (int i = 0; i < SIZE; i++)
    {
        node * temp = table[i];
        while (temp != NULL)
        {
            control = temp;
            temp = temp->next;
            free(control);
        }
    }
}