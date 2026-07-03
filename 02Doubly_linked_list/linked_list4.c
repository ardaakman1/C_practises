#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

node *head_control(int value, node *head);
node *head_delete(node *head);
void delete_node(node *temp); // at first I used node *function but I do not have to do that
void insert_after_node(node * temp, int value);  // since temp in the main already affected by these functions (temp->next)
void show_list(node * head);
void free_list(node * head);

int main(void)
{
    int user_var;
    node * head = NULL;
    while(1) {
        printf("Please enter a number (enter 0 to exit the program):");
        scanf("%d", &user_var);
        if (user_var == 0) break;
        if (head == NULL) {
            head = head_control(user_var, head);
            continue;
        }

        else if (user_var < head->value) {
            head = head_control(user_var, head);
            continue;
        }

        else if (head->value == user_var){
            head = head_delete(head);
            continue;
        }
        else {
            node *temp = head;
            int flag = 0;
            while (temp->next != NULL) {
                if (user_var == temp->next->value) {
                    flag = 1;
                    delete_node(temp);
                    break;
                }

                else if (user_var > temp->value && user_var < temp->next->value) {
                    flag = 1;
                    insert_after_node(temp, user_var);
                    break;
                }
                temp = temp->next;
            }

            if (flag == 0) {
                node *new_node = malloc(sizeof(node));
                new_node->next = NULL;
                new_node->value = user_var;
                temp->next = new_node;
            }
        }
    }

    printf("\n\nShowing the list...\n\n");
    show_list(head);

    printf("\n\nFreeing the memory\n\n");
    free_list(head);
    return 0;
}

node *head_control(int value, node *head)
{
    if (head == NULL){
        head = malloc(sizeof(node));
        head->value = value;
        head->next = NULL;
    }
    
    else if (value < head->value) {
        node *new_node = malloc(sizeof(node));
        new_node->value = value;
        new_node->next = head;
        head = new_node;
    }
    return head;
}

node *head_delete(node *head)
{
    if (head->next != NULL) {
        node * copy = head;
        head = head->next;
        free(copy);
    }

    else {
        free(head);
        head = NULL;
    }
    return head;
}

void delete_node(node *temp)
{
    if (temp->next->next == NULL){
        free(temp->next);
        temp->next = NULL;
    }

    else {
        node *copy = temp->next;
        temp->next = temp->next->next;
        free(copy);
    }
}

void insert_after_node(node * temp, int value)
{
    node *new_node = malloc(sizeof(node));
    node *copy = NULL;
    new_node->value = value;
    copy = temp->next;
    temp->next = new_node;
    new_node->next = copy;
}

void show_list(node * head)
{
    node *temp = head;
    while (temp != NULL) {
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

void free_list(node * head)
{
    node *temp = head;
    node * control = NULL;
    while (temp != NULL) {
        control = temp;
        temp = temp->next;
        free(control);
    }
}