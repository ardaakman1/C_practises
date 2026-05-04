#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node * next;
} node;

node * delete_head(node * head);
void delete_body(node * temp);
void show_list(node * head);
void free_memory(node * head);

int main(void)
{
    node * head = NULL;
    node * temp = NULL;
    node * control = NULL;
    int input;
    while (1)
    {
        printf("please enter a number (enter 0 to exit the program):");
        scanf("%d", &input);
        if (input == 0) break;
        node * new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("\n\nMemory could not allocated\n\n");
            return 1;
        }
        new_node->next = NULL;
        new_node->value = input;
        if (head == NULL)
        {
            head = new_node;
            continue;
        }

        else if (input == head->value)
        {
            head = delete_head(head);
            free(new_node);
            continue;
        }

        else if (input < head->value)
        {
            new_node->next = head;
            head = new_node;
            continue;
        }
        else
        {
            int flag = 0;
            temp = head;
            while (temp->next != NULL)
            {
                if (input < temp->next->value)
                {
                    control = temp->next;
                    temp->next = new_node;
                    new_node->next = control;
                    flag = 1;
                    break;
                }

                else if (input == temp->next->value)
                {
                    delete_body(temp);
                    free(new_node);
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }
            if (flag == 0)
            {
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

node * delete_head(node * head){
    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }
    else
    {
        node * control = NULL;
        control = head;
        head = head->next;
        free(control);
        return head;
    }
}

void delete_body(node * temp)
{
    node * control = NULL;
    control = temp->next;
    temp->next = control->next;
    free(control);
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

void free_memory(node * head)
{
    node * temp = head;
    node * control = NULL;
    while (temp != NULL)
    {
        control = temp;
        temp = temp->next;
        free(control);
    }
}