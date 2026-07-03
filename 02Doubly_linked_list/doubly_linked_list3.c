#include <stdio.h>
#include <stdlib.h>

// Sadly I used AI to correct my mistakes becuase I could not see them :(

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

void process_number(node **head_ptr, node **tail_ptr, int value);
void head_control(node **head_ptr, node **tail_ptr, int value);
void head_delete(node **head_ptr, node **tail_ptr);
void insert_after_node(node *temp, int value);
void delete_node(node *temp, node **tail_ptr);
void show_list(node *head, node *tail);
void free_list(node *head);

int main(void)
{
    int user_var;
    node *head = NULL;
    node *tail = NULL;
    while (1) {
        printf("Please enter a number: (enter 0 to exit the program):");
        scanf("%d", &user_var);
        if (user_var == 0) break;
        process_number(&head, &tail, user_var);
    }
   
    show_list(head, tail);
}

void process_number(node **head_ptr, node **tail_ptr, int value)
{
    if (*head_ptr == NULL || value < (*head_ptr)->value) {  // Short-circuit evaluation
        head_control(head_ptr, tail_ptr, value);
    }

    else if ((*head_ptr)->value == value) {
        head_delete(head_ptr, tail_ptr);
    }

    else {
        node *temp = *head_ptr;
        int flag = 0;
        while (temp->next != NULL) {
            if (value > temp->value && value < temp->next->value) {
                insert_after_node(temp, value);
                flag = 1;
                break;
            }

            else if (temp->next->value == value) {
                delete_node(temp, tail_ptr);
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 0) {
            node *new_node = malloc(sizeof(node));
            new_node->value = value;  // I forgot this row at first
            new_node->next = NULL;
            new_node->prev = temp;
            temp->next = new_node;
            (*tail_ptr) = new_node;
            return;
        }
    }
}

void head_control(node **head_ptr, node **tail_ptr, int value)
{
    if (*head_ptr == NULL) {
        *head_ptr = malloc(sizeof(node));
        (*head_ptr)->value = value;
        (*head_ptr)->next = NULL;
        (*head_ptr)->prev = NULL;
        *tail_ptr = *head_ptr;
        return; 
    }

    else if (value < (*head_ptr)->value) {
        node *new_node = malloc(sizeof(node));
        new_node->value = value;
        new_node->next = *head_ptr;
        new_node->prev = NULL;
        *head_ptr = new_node;
        return;
    }
}

void head_delete(node **head_ptr, node **tail_ptr)
{
   if ((*head_ptr)->next != NULL) {
        node *copy = *head_ptr;
        *head_ptr = (*head_ptr)->next;
        (*head_ptr)->prev = NULL;
        free(copy);
        return;
   }

   else {
        free(*head_ptr);
        *head_ptr = NULL;
        *tail_ptr = NULL;
        return;
   }
}

void insert_after_node(node *temp, int value)
{
    node *new_node = malloc(sizeof(node));
    new_node->value = value;
    node *control = temp->next;
    temp->next = new_node;
    new_node->prev = temp;
    new_node->next = control;
    control->prev = new_node;
    return;
}

void delete_node(node *temp, node **tail_ptr)
{
    if (temp->next->next != NULL) {
        node *copy = temp->next;
        temp->next = temp->next->next;
        temp->next->prev = temp;  // at first I had an error since I write temp->next->next->prev
        free(copy);
        return;
    }

    else {
        (*tail_ptr) = (*tail_ptr)->prev;
        free(temp->next);
        temp->next = NULL;
        return;
    }
}

void show_list(node *head, node *tail)
{
    printf("\n\nShowing the Ascended list\n\n");
    node *temp = head;
    while (temp != NULL) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }

    printf("\n\nShowing the Descended list\n\n");
    temp = tail;
    while (temp != NULL) {
        printf("%d\n", temp->value);
        temp = temp->prev;
    }
    return;
}

void free_list(node *head)
{
    node *control = NULL;
    node *temp = head;
    while (temp != NULL) {
        control = temp;
        temp = temp->next;
        free(control);
    }
    return;
}