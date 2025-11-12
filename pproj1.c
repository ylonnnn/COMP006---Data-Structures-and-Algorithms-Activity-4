#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int digit;
    struct node *next;
};

struct node *create_node(int digit)
{
    // Implicit type casting
    struct node *node = malloc(sizeof(struct node));
    if (node == NULL)
    {
        fprintf(stderr, "failed to allocate memory for a node\n");
        return NULL;
    }

    node->digit = digit;
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

void create_at_end(struct node *node, int digit)
{
    assert(node != NULL);

    node->next = create_node(digit);
}

struct node *copy_node(struct node *head)
{
    assert(head != NULL);

    struct node *cp = create_node(head->digit), *cp_curr = cp,
                *curr = head->next;

    while (curr != NULL)
    {
        create_at_end(cp_curr, curr->digit);
        cp_curr = cp_curr->next;
        curr = curr->next;
    }

    return cp;
}

struct node *node_from_num(int num)
{
    struct node *head = NULL, *curr = NULL;
    int temp = num;

    while (temp)
    {
        if (curr != NULL)
        {
            create_at_end(curr, temp % 10);
            curr = curr->next;
        }

        else
            head = curr = create_node(temp % 10);

        temp /= 10;
    }

    return head;
}

void reverse_list(struct node **head)
{
    assert(head != NULL);
    assert(*head != NULL);

    struct node *prev = NULL, *curr = *head;

    while (curr != NULL)
    {
        struct node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
}

struct node *reverse_list_cp(struct node *head)
{
    assert(head != NULL);

    struct node *cp = copy_node(head);
    reverse_list(&cp);

    return cp;
}

void print_list(struct node *l)
{
    assert(l != NULL);

    struct node *temp = l;

    while (temp != NULL)
    {
        printf("%d -> ", temp->digit);
        temp = temp->next;
    }

    printf("NULL\n");
}

void print_reversed_list(struct node *l)
{
    struct node *r = reverse_list_cp(l);
    print_list(r);

    free_node(r);
}

struct node *add_nodes(struct node *a, struct node *b)
{
    assert(a != NULL);
    assert(b != NULL);

    struct node *sum_node = create_node(0), *sum_curr = sum_node, *a_curr = a,
                *b_curr = b;
    int carry = 0;

    while (a_curr != NULL || b_curr != NULL)
    {
        int a_digit = a_curr != NULL ? a_curr->digit : 0,
            b_digit = b_curr != NULL ? b_curr->digit : 0;

        int sum = a_digit + b_digit + carry, digit = sum % 10;
        carry = sum / 10;

        sum_curr->digit = digit;

        if (a_curr != NULL)
            a_curr = a_curr->next;
        if (b_curr != NULL)
            b_curr = b_curr->next;

        if (a_curr == NULL && b_curr == NULL)
            break;

        sum_curr->next = create_node(0);
        sum_curr = sum_curr->next;
    }

    if (carry)
        sum_curr->next = create_node(carry);

    return sum_node;
}

int main()
{
    struct node *a = node_from_num(1821), *b = node_from_num(883);
    struct node *sum = add_nodes(a, b);

    printf("A: ");
    print_list(a);

    printf("B: ");
    print_list(b);

    printf("Sum: ");
    print_list(sum);

    printf("\nReversed\n");

    printf("A: ");
    print_reversed_list(a);

    printf("B: ");
    print_reversed_list(b);

    printf("Sum: ");
    print_reversed_list(sum);

    // Release the memory used
    free_node(a), free_node(b), free_node(sum);

    return 0;
}
