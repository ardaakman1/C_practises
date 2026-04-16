#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _trie
{
    char university[20];
    struct _trie *paths[10];
} trie;

trie* root = NULL;  // we should make it NULL at first because we need a clear empty sign
// to avoid junkvalues and correctly detect non existent paths
int year_control();
void free_memory(trie* node);

int main(void)
{
    char name[20];
    int year;
    int control = 0;
    root = malloc(sizeof(trie));
    if (root == NULL)
    {
        printf("\nMemory could not allocated...\n");
        return 1;
    }
    for (int i = 0; i < 10; i++)
    {
        root->paths[i] = NULL;
    }
    root->university[0] = '\0';  // this makes string expression NULL
    printf("please enter an university name (max 20 charactes): ");
    fgets(name, 20, stdin);
    
    year = year_control();
    int digits[4];
    digits[0] = year / 1000;
    digits[1] = (year / 100) % 10;
    digits[2] = (year / 10) % 10;
    digits[3] = year % 10;

    trie* trav = root;
    for (int i = 0; i < 4; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            trav->paths[digits[i]] = malloc(sizeof(trie));
            for (int j = 0; j < 10; j++)
            {
                trav->paths[digits[i]]->paths[j] = NULL;  // we should make null next paths
            }
            trav->paths[digits[i]]->university[0] = '\0';
        }
        trav = trav->paths[digits[i]];
    }

    name[strcspn(name, "\n")] = 0;
    strcpy(trav->university, name);
    printf("\n\n%s had written in the trie!\n\n", name);

    printf("Please enter the year that you want to search for: ");
    year = year_control();
    
    digits[0] = year / 1000;
    digits[1] = (year / 100) % 10;
    digits[2] = (year / 10) % 10;
    digits[3] = year % 10;

    trav = root;
    int found = 1;
    for (int i = 0; i < 4; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            printf("\nSorry, this year is not in our database.\n");
            found = 0;
            break;
        }
        trav = trav->paths[digits[i]];
    }

    if (found == 1)
    {
        if (trav->university[0] != '\0')
        {
            printf("\nYour university that opu have searched for founded!\n");
            printf("\nyear : %d|||name : %s\n\n", year, trav->university);
        }
    }
    free_memory(root);
    printf("\n\nmemory freed succesfully!\n\n");
    return 0;
}

int year_control()
{
    int year;
    int flag = 0;

    while (flag == 0)
    {
        int count = 0;
        printf("please enter the year it should has 4 digits: ");
        scanf("%d", &year);
        int copy_year = year;
        while (1)
        {
            if (copy_year != 0)
            {
                copy_year /= 10;
                count++;
            }
            if (count == 4) 
            {
                flag = 1;
                break;
            }
            if (copy_year == 0 || count > 4) 
            {
                printf("the year you have entered should have 4 digits!\n");
                break;
            }
        }
    }
    return year;
}

void free_memory(trie* node)
{
    if (node == NULL)
    {
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        free_memory(node->paths[i]);
    }

    free(node);
}