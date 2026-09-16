#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_LENGTH 20
#define DIGIT_NUM 5

// it has not ended yet

typedef struct _trie {
    char word[WORD_LENGTH];
    struct _trie *paths[DIGIT_NUM];
} _trie;

_trie *root = NULL;

int digit_control(int path_code);
void trie_add(int path_code, char word[]);


int main(void)
{
    int path_code = 0;
    char word[WORD_LENGTH] = {0};  // this makes char array (string) NULL
    while (1) {
        printf("Please enter the code number (to path), enter 0 to exit the program\n");
        printf("You can enter exit to word to exit the program\n");
        printf("Your code must have %d digits:", DIGIT_NUM);
        scanf("%d", &path_code);
        getchar();  // çünkü enter a bastığımda fgets i bozuyor bu yüzden getchar() kullandım
        if (path_code == 0) break;
        if (digit_control(path_code)) continue;
        fgets(word, WORD_LENGTH, stdin);
        word[strcspn(word, "\n")] = '\0';  // strcspn fonksiyonu karakter değil metin bekler bu yüzden'\n' değil "\n" olacak
        trie_add(path_code, word);


    }
}

int digit_control(int path_code)
{
    int count = 0;
    while (path_code != 0) {
        path_code /= 10;
        count++;
    }

    if (count == 5) {
        return 0;
    }

    else {
        printf("\nYour Code must have %d digits\n", DIGIT_NUM);
        return 1;
    }
}

void trie_add(int path_code, char word[])
{
    if (root == NULL) {
        root = malloc(sizeof(_trie));
        for (int i = 0; i < DIGIT_NUM; i++) {
            root->paths[i] = NULL;
        }
    }

    int copy_code = path_code;
    int control_number = 10000;
    _trie *trav = root;
    for (int i = 0; copy_code != 0; i++) {
        copy_code = path_code;
        copy_code /= control_number;
        copy_code %= 10;
        control_number /= 10;
        if (trav->paths[copy_code] == NULL) {
            trav->paths[copy_code] = malloc(sizeof(_trie));
            trav = trav->paths[copy_code];
            for (int j = 0; j < DIGIT_NUM; j++) {
                trav->paths[j] = NULL;
            }
            continue;
        }
        trav = trav->paths[copy_code];
    }

    strcpy(trav->word, word);
}