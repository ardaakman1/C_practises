#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 20
#define PATHS 10
#define CODE_DIGIT 5

typedef struct trie 
{
    char name[NAME_LENGTH];
    struct trie* paths[PATHS];
} trie;
trie* root = NULL;

int code_controller();
void free_memory(trie* node);

int main(void)
{
    char name[NAME_LENGTH];
    int code;  // it should have CODE_DIGIT digits
    root = malloc(sizeof(trie));
    if (root == NULL)
    {
        printf("\nMemory could not allocated...\n");
        return 1;
    }

    for (int i = 0; i < PATHS; i++)
    {
        root->paths[i] = NULL;
    }
    root->name[0] = '\0';  // this (NULL) makes string expression NULL
    printf("\nPlease enter a name (it should has %d characters): ", NAME_LENGTH);
    fgets(name, NAME_LENGTH, stdin);

    code = code_controller();
    int digits[CODE_DIGIT];
    digits[0] = code / 10000;
    digits[1] = (code / 1000) % 10;
    digits[2] = (code / 100) % 10;
    digits[3] = (code / 10) % 10;
    digits[4] = code % 10;

    trie* trav = root;
    for (int i = 0; i < CODE_DIGIT; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            trav->paths[digits[i]] = malloc(sizeof(trie));
            for (int j = 0; j < PATHS; j++)
            {
                trav->paths[digits[i]]->paths[j] = NULL;  // we should make next paths NULL
            }
            trav->paths[digits[i]]->name[0] = '\0';
        }
        trav = trav->paths[digits[i]];
    }
    name[strcspn(name, "\n")] = 0;  // biz buraya neden strcspn koymuştuk
    strcpy(trav->name, name);
    printf("%s had written in trie!\n\n", name);

    printf("Please enter the code that you want to search for: ");
    code = code_controller();

    digits[0] = code / 10000;
    digits[1] = (code / 1000) % 10;
    digits[2] = (code / 100) % 10;
    digits[3] = (code / 10) % 10;
    digits[4] = code % 10;

    trav = root;
    int found = 1;
    for (int i = 0; i < CODE_DIGIT; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            printf("\nSorry your code is not in our database!\n\n");
            break;
        }
        trav = trav->paths[digits[i]];
    }

    if (found == 1)
    {
        if (trav->name[0] != '\0')
        {
            printf("I have found the name that you are searching for!\n\n");
            printf("code: %d----name: %s\n\n", code, trav->name);
        }
    }
    printf("\nfreeing the memory...\n");
    free_memory(root);
    return 0;
}

int code_controller()
{
    int code;
    int flag = 0;
    while (flag == 0)
    {
        int count = 0;
        printf("please enter a number (it should has %d digits): ", CODE_DIGIT);
        scanf("%d", &code);
        int copy_code = code;
        while(1)
        {
            if (copy_code != 0)
            {
                copy_code /= 10;
                count++;
            }
            if (count == CODE_DIGIT) 
            {
                flag = 1;
                break;
            }
            if (copy_code == 0 || count > CODE_DIGIT) 
            {
                printf("the year you have entered should have %d digits!\n", CODE_DIGIT);
                break;
            }
        }
    }
    return code;
}

void free_memory(trie* node)
{
    if (node == NULL) return;
    for (int i = 0; i < PATHS; i++)
    {
        free_memory(node->paths[i]);
    }
    free(node);
}