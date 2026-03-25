#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node * next;
    struct node * prev;
} node;
// NOTE: temp->next == (*temp).next   * means look int the pointers value . means look to the struct

node * head_deletef(node * head);
node * body_deletef(node * copy);
void print_list(node * head);
void print_list_reverse(node * tail);
void free_memory(node * head);
int main(void)
{
    node * head = NULL;
    node * tail = NULL;
    node * temp;
    node * control;
    int input;
    while (1)
    {
        printf("Please enter a number (enter 0 to exit the program): ");
        scanf("%d", &input);
        if (input == 0) break;
        node * new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("\n\nSegmentation fault...\n\n");
            return 1;
        }
        new_node->data = input;
        new_node->next = NULL;
        new_node->prev = NULL;
        if (head == NULL)
        {
            head = new_node;
            tail = head;
            continue;
        }
        if (input == head->data)
        {
            if (head->next == NULL)
            {
                tail = NULL;  // if head = tail, tail must be NULL
            }
            head = head_deletef(head);
            free(new_node);
            continue;
        }
        else if (input < head->data)
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
            continue;
        }
        else
        {
            int flag = 0;  // to control if sort or delete is done (buraya ne yazarım bilemedim)
            temp = head;
            while (temp->next != NULL)
            {
                if (input < temp->next->data)
                {
                    control = temp->next;
                    temp->next = new_node;
                    new_node->next = control;
                    control->prev = new_node;
                    new_node->prev = temp;
                    flag = 1;
                    break;
                }
                else if (input == temp->next->data)
                {
                    if (tail == temp->next)
                    {
                        tail = temp;
                    }
                    temp = body_deletef(temp);
                    flag = 1;
                    free(new_node);
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
    printf("\n\nThe list is completed!\n\n");
    print_list(head);
    print_list_reverse(tail);
    free_memory(head);
    return 0;
}

node * head_deletef(node * head)  
{
    node * control = head;
    if (head->next != NULL)
    {
        head = head->next;
        head->prev = NULL;  // we shuld do this because when we printing the list reverse we look until here and 
        // if we don't do this the program will return Segmentation fault
        free(control);
        return head;
    }
    else
    {
        free(control);
        return NULL;
    }
}

node * body_deletef(node * copy)
{
    node * control;
    control = copy->next;
    if (control->next == NULL)
    {
        copy->next = NULL;
    }
    else
    {
        copy->next = control->next;
        control->next->prev = copy;
    }
    free(control);
    return copy;
}

void print_list(node * head)
{
    printf("\n\nShowing the list\n\n");
    node * temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

void print_list_reverse(node * tail)
{
    printf("\n\nShowing the reversed list\n\n");
    node * temp = tail;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->prev;
    }
}

void free_memory(node * head)
{
    printf("\n\nFreeing the memory...\n\n");
    node * temp = head;
    node * control;
    while (temp != NULL)
    {
        control = temp;
        temp = temp->next;
        free(control);
    }
}