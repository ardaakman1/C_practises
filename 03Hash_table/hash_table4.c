#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SENTENCE_SIZE 52  // because 50 charachters 1 \n and 1 \0
#define ARRAY_SIZE 26
typedef struct node {
    char sentence[SENTENCE_SIZE];
    struct node * next;
} node;

int hash_funtion(char input[]);
void add(node * table[], char input[]);
void delete_function(node * table[], char target[]);
void show_list(node * table[]);
void free_memory(node * table[]);
int main(void)
{
    node * table[ARRAY_SIZE] = {NULL};
    char input[SENTENCE_SIZE];
    char choice;
    while (1)
    {
        printf("\nPlease enter a sentence your sentence has max %d charachters (enter EXIT to exit the program):", SENTENCE_SIZE);
        fgets(input, SENTENCE_SIZE, stdin);
        if (strcmp(input, "EXIT\n") == 0) break;
        if (isalpha(input[0]) == 0)
        {
            printf("\nThe first character you have entered have to be a letter!\n");
            continue;
        }
        add(table, input);
    }

    printf("\nDo you want to delete a sentence: (y/n)");
    scanf("%c", &choice);
    getchar();
    if (toupper(choice) == 89)
    {
        printf("Please enter a sentence that you want to delete: ");
        fgets(input, SENTENCE_SIZE, stdin);
        delete_function(table, input);
    }

    printf("\n\nShowing the list...\n\n");
    show_list(table);

    printf("\n\nFreeing the memory...\n\n");
    free_memory(table);
    return 0;
}


int hash_funtion(char input[])
{
    return toupper(input[0]) - 'A';
}

void add(node * table[], char input[])
{
    int index = hash_funtion(input);
    node * new_node = malloc(sizeof(node));
    new_node->next = NULL;
    strcpy(new_node->sentence, input);
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

void delete_function(node * table[], char target[])
{
    int index = hash_funtion(target);
    if (table[index] == NULL)
    {
        printf("\nSentence that you want to delete could not found\n");
        return;
    }
    node * temp = table[index];
    node * prev = temp;
    int flag = 0;
    while (temp != NULL)
    {
        if (strcmp(temp->sentence, target) == 0)
        {
            if (temp == table[index])
            {
                table[index] = table[index]->next;
                free(temp);
                flag = 1;
                break;
            }
            else
            {
                prev->next = temp->next;
                free(temp);
                flag = 1;
                break;
            }
        }
        prev = temp;
        temp = temp->next;
    }

    if (flag == 0)
    {
        printf("\nSentence that you want to delete could not found\n");
        return;
    }
    else
    {
        printf("\nYour sentence deleted succesfully!\n");
    }
}

void show_list(node * table[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        node * temp = table[i];
        printf("\n\nindex %d\n\n", i);
        while (temp != NULL)
        {
            printf("%s\n", temp->sentence);
            temp = temp->next;
        }
    }
}

void free_memory(node * table[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        node * temp = table[i];
        while (temp != NULL)
        {
            node * control = temp;
            temp = temp->next;
            free(control);
        }
    }
}