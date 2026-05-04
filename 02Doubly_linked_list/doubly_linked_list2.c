#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node * next;
    struct node * prev;
} node;

void show_list(node * head);
void show_list_reverse(node * tail);
void free_memory(node * head);

int main(void)
{
    node * head = NULL;
    node * tail = NULL;
    node * control = NULL;
    int input;
    while (1)
    {
        printf("please enter a number (enter 0 to exit):");
        scanf("%d", &input);
        if (input == 0) break;
        node * new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("\n\nMemory could not allocated...\n\n");
            return 1;
        }
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->value = input;
        if (head == NULL && tail == NULL)
        {
            head = new_node;
            tail = head;
            continue;
        }
        else if (head->value == input)
        {
            if (head == tail)
            {
                node * temp = head;
                head = NULL;
                tail = NULL;
                free(temp);
            }
            else
            {
                control = head;
                head = head->next;
                head->prev = NULL;
                free(control);
            }
            free(new_node);
            continue;
        }
        else if (input < head->value)
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            continue;
        }
        else
        {
            node * temp = head;
            int flag = 0;
            while (temp->next != NULL)
            {
                if (input < temp->next->value)
                {
                    control = temp->next;
                    temp->next = new_node;
                    new_node->next = control;
                    control->prev = new_node;
                    new_node->prev = temp;
                    flag = 1;
                    break;
                }

                else if (input == temp->next->value)
                {
                    control = temp->next;
                    if (temp->next == tail)
                    {
                        tail = temp;
                        control->prev = NULL;
                        temp->next = NULL;
                    }
                    else
                    {
                        temp->next = control->next;
                        control->next->prev = temp;
                    }
                    free(control);
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if (flag == 0)
            {
                temp->next = new_node;
                new_node->prev = temp;
                tail = new_node; 
            }
        }
    }
    printf("\n\nShowing the list...\n\n");
    show_list(head);
    printf("\n\nShowing the reversed list...\n\n");
    show_list_reverse(tail);
    printf("\n\nFreeing the memory...\n\n");
    free_memory(head);
    return 0;
}

void show_list(node * head)
{
    node * temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

void show_list_reverse(node * tail)
{
    node * temp = tail;
    while (temp != NULL)
    {
        printf("%d\n", temp->value);
        temp = temp->prev;
    } 
}

void free_memory(node * head)
{
    node * control = NULL;
    node * temp = head;
    while (temp != NULL)
    {
        control = temp;
        temp = temp->next;
        free(control);
    }
}