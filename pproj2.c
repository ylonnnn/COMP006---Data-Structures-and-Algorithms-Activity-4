#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int val;
    struct node *next;
};

struct node *create_node(int val)
{
    // Implicit type cast
    struct node *node = malloc(sizeof(struct node));
    if (node == NULL)
    {
        fprintf(stderr, "failed to allocate memory for a node\n");
        return NULL;
    }

    node->val = val;
    node->next = NULL;

    return node;
}

void free_node(struct node *node)
{
    assert(node != NULL);

    if (node->next != NULL)
        free_node(node->next);

    free(node);
}

void print_list(struct node *l)
{
    assert(l != NULL);

    int n = 1;
    struct node *curr = l;

    while (curr != NULL)
    {
        printf("Data %d = %d\n", n++, curr->val);
        curr = curr->next;
    }
}

int main()
{
    int n;
    printf("Input the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        fprintf(stderr,
                "cannot create a linked list with less than 1 nodes!\n");
        return 0;
    }

    struct node *head = create_node(0), *curr = head;

    for (int i = 0; i < n; ++i)
    {
        int data;
        printf("Input data for node %d: ", i + 1);
        scanf("%d", &data);

        curr->val = data;
        if (i < n - 1)
            curr->next = create_node(0);

        curr = curr->next;
    }

    printf("Data entered in the list are:\n");
    print_list(head);

    // Release the memory used
    free_node(head);

    return 0;
}
