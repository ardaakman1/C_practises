#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int value;
} node;

node *delete_body(node *temp);
node *delete_head(node *head);
void show_list(node *head);
void free_memory(node *head);

int main(void)
{
    int input;
    node *head = NULL;
    while (1)
    {
        printf("Please enter a number (enter 0 to exit the program):");
        scanf("%d", &input);
        if (input == 0) break;
        if (head == NULL)
        {
            node *new_node = malloc(sizeof(node));
            new_node->next = NULL;
            new_node->value = input;
            head = new_node;
            continue;
        }
        else if (input == head->value)
        {
            head = delete_head(head);
            continue;
        }
        else if (input < head->value)
        {
            node *new_node = malloc(sizeof(node));
            new_node->next = NULL;
            new_node->value = input;
            new_node->next = head;
            head = new_node;
            continue;
        }
        else
        {
            node *temp = head;
            int flag = 0;
            while (temp->next != NULL)
            {
                if (temp->next->value == input)
                {
                    temp = delete_body(temp);
                    flag = 1;
                    break;
                }
                else if (temp->value < input && input < temp->next->value)
                {
                    node *new_node = malloc(sizeof(node));
                    new_node->value = input;
                    new_node->next = temp->next;
                    temp->next = new_node;
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if (flag == 0)
            {
                node *new_node = malloc(sizeof(node));
                new_node->next = NULL;
                new_node->value = input;
                temp->next = new_node;
            }
        }
    }
    printf("\n\nShowing the list...\n\n");
    show_list(head);
    printf("\n\nFreeing the memory...\n\n");
    free_memory(head);
    return 0;
}

node *delete_body(node *temp)
{
    node *control = temp->next;
    temp->next = control->next;
    free(control);
    return temp;
}

node *delete_head(node *head)  // I had an error while compiling 
{  // collect2.exe: error: ld returned 1 exit status this is because I wrote head_deleted
    if (head->next != NULL)
    {
        node *control = head;
        head = head->next;
        free(control);
        return head;
    }
    else
    {
        free(head);
        return NULL;
    }
}

void show_list(node *head)
{
    node *temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

void free_memory(node *head)
{
    node *temp = head;
    while(temp != NULL)
    {
        node *control = temp;
        temp = temp->next;
        free(control);
    }
}