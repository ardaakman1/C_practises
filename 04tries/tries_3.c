#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_NUM 10
#define WORD_LENGTH 20
#define DIGIT_NUM 5

typedef struct trie
{
    char word[WORD_LENGTH];
    struct trie* paths[PATH_NUM];
} trie;

trie* root = NULL;

int digit_control();
void add_to_trie(int digits[], char word[20]);
void search_trie(int digits[], int number);
void delete_node(int digits[]);
void free_memory(trie* node);

int main(void)
{
    int element_num;
    char word[WORD_LENGTH];
    int number;
    int digits[DIGIT_NUM];
    int flag = 0;  // to control if there is an elemen in trie (to delete a node)
    printf("please enter the number of words that you want to enter: ");
    scanf("%d", &element_num);
    root = malloc(sizeof(trie));
    if (root == NULL)
    {
        printf("\nMemory could not allocated!\n");
        return 1;
    }
    
    for (int i = 0; i < PATH_NUM; i++)  // I made NULL all of the paths and word
    {
        root->paths[i] = NULL;
    }
    root->word[0] = '\0';

    for (int i = 0; i < element_num; i++)
    {
        number = digit_control();
        printf("please enter the word that you want to enter:");
        fgets(word, WORD_LENGTH, stdin);
        word[strcspn(word, "\n")] = 0;

        digits[0] = number / 10000;
        digits[1] = (number / 1000) % 10;
        digits[2] = (number / 100) % 10;
        digits[3] = (number / 10) % 10;
        digits[4] = number % 10;

        add_to_trie(digits, word);
        printf("\n%s has succesfully written to trie\n", word);
    }

    // flag = 0;
    for (int i = 0; i < PATH_NUM; i++)
    {
        if (root->paths[i] != NULL)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        printf("please enter the number of the word that you want to delete\n");
        number = digit_control();
        digits[0] = number / 10000;
        digits[1] = (number / 1000) % 10;
        digits[2] = (number / 100) % 10;
        digits[3] = (number / 10) % 10;
        digits[4] = number % 10;
        delete_node(digits);
    }

    printf("please enter how many words that you want to search:");
    scanf("%d", &element_num);
    for (int i = 0; i < element_num; i++)
    {
        printf("\nPlease enter the words number that you want to search\n");
        number = digit_control();
        digits[0] = number / 10000;
        digits[1] = (number / 1000) % 10;
        digits[2] = (number / 100) % 10;
        digits[3] = (number / 10) % 10;
        digits[4] = number % 10;
        search_trie(digits, number);
    }

    printf("\n\nfreeing the memory...\n\n");
    free_memory(root);
    return 0;
}

int digit_control()
{
    int number;
    while (1)
    {
        printf("Please enter a number that has %d digits:", DIGIT_NUM);
        scanf("%d", &number);
        getchar();  // to delete \n from scanf (or it will prevent writing in fgets)
        int count = 0;
        int copy_number = number;
        while (copy_number != 0)
        {
            copy_number /= 10;
            count++;
        }

        if (count == DIGIT_NUM)
        {
            break;
        }

        if (copy_number == 0 && count != DIGIT_NUM)
        {
            printf("Your number should have %d digits!\n", DIGIT_NUM);
        }
    }
    return number;
}

void add_to_trie(int digits[], char word[20])
{
    trie* trav = root;
    for (int i = 0; i < DIGIT_NUM; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            trav->paths[digits[i]] = malloc(sizeof(trie));
            for (int j = 0; j < PATH_NUM; j++)
            {
                trav->paths[digits[i]]->paths[j] = NULL;
            }
            trav->paths[digits[i]]->word[0] = '\0';
        }
        trav = trav->paths[digits[i]];
    }
    strcpy(trav->word, word);
}

void search_trie(int digits[], int number)
{
    trie* trav = root;
    for (int i = 0; i < DIGIT_NUM; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            printf("\nCould not found your word\n");
            return;
        }
        trav = trav->paths[digits[i]];
    }
    printf("your word has found!\n");
    printf("number: %d----word: %s\n\n", number, trav->word);
}

void delete_node(int digits[])
{
    trie* trav = root;
    trie* control = NULL;
    for (int i = 0; i < DIGIT_NUM; i++)
    {
        if (trav->paths[digits[i]] == NULL)
        {
            printf("node that you want to delete could not found\n");
        }
        trav = trav->paths[digits[i]];
    }
    free(trav);
    printf("\nYour node deleted succesfully\n");
}

void free_memory(trie* node)
{
    for (int i = 0; i < PATH_NUM; i++)
    {
        if (node->paths[i] != NULL)
        {
            free_memory(node->paths[i]);
        }
    }
    free(node);
}