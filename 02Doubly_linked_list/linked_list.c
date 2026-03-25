#include <stdio.h>
#include <stdlib.h>
// sorted linked list you can enter numbers and they will sort automatically
// if you enter a number that you entered before that number (that node) will be deleted
typedef struct node {
    int data;
    struct node * next;
} node;

node * head_deletef(node * head);
node * body_deletef(node * copy); // I said copy because this struct is copy of the temp
void show_list(node * head);
void free_memory(node * head);
int main()
{
    node * head = NULL;
    node * temp;
    node * control; // to control (or save) a node (when sorting)
    int input;
    while (1)
    {
        printf("please enter a number (enter 0 to exit the program): ");
        scanf("%d",&input);
        if (input == 0) break;
        node * new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("\n\nSegmentation fault...\n\n");
            return 1;
        }
        new_node->data = input;
        new_node->next = NULL;
        if (head == NULL)
        {
            head = new_node;
            continue;
        }
        if (head->data == input)
        {
            head = head_deletef(head);
            free(new_node);
            continue;
        }
        else if (input < head->data)
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
                if (input < temp->next->data)
                {
                    control = temp->next;
                    temp->next = new_node;
                    new_node->next = control;
                    flag = 1;
                    break;
                }

                else if (input == temp->next->data)
                {
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
            }
        }
    }
    printf("\n\nthe list is completed!\n\n");
    show_list(head);
    printf("\n\nFreeing the memory...\n\n");
    return 0;
}

node * head_deletef(node * head)
{
    node * temp = head;
    if (head->next != NULL)
    {
        head = head->next;
        free(temp);
        return head;
    }
    else // if the user have only entered head
    {
        free(temp);
        return NULL;
    }
}

node * body_deletef(node * copy)
{
    node * control; // to control that specific node
    control = copy->next;
    copy->next = control->next;
    free(control);
    return copy;
}

void show_list(node * head)
{
    printf("\n\nShowing the list:\n\n");
    node * temp = head;
    while (temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

void free_memory(node * head)
{
    node * temp = head;
    node * control;
    while (temp != NULL)
    {
        control = temp;
        temp = temp->next;
        free(control);
    }
}