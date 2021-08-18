
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
    int data;
    Node *next;
};

Node    *new_node(int);
Node    *read_list(FILE*);
void    read_error();
Node    *add_lists(Node*, Node*);
int     list_size(Node*);
void    print_list(Node*);
void    print2(Node*);
void    *xmalloc(size_t);

int     read_line = 1;



int main(int argc, char **argv) {
    char *filename = (argc > 1) ? argv[1] : "input.txt";
    FILE *fp = fopen(filename, "r");
    if(!fp) {
        printf("failed to open file %s\n", filename);
        exit(1);
    }
    Node *list1 = read_list(fp);
    Node *list2 = read_list(fp);
    fclose(fp);
    print_list(list1);
    printf("+\n");
    print_list(list2);
    printf("=\n");
    print_list(add_lists(list1, list2));
}



Node *new_node(int data) {
    Node *node = (Node*) xmalloc(sizeof(Node));
    node->data = data;
    node->next = 0;
    return node;
}

Node *read_list(FILE *fp) {
    int n;
    if(fscanf(fp, "%d", &n) != 1) read_error();
    Node *head = new_node(-1);
    Node *current = head;
    for(int i = 0; i < n; i++) {
        if(fscanf(fp, "%d", &current->data) != 1) read_error();
        read_line++;
        if(i + 1 < n) {
            current->next = new_node(-1);
            current = current->next;
        }
    }
    return head;
}

void read_error() {
    printf("failed to read expected value on line %d\n", read_line);
    exit(1);
}

Node *add_lists(Node *list1, Node *list2) {
    if(list_size(list2) > list_size(list1)) return add_lists(list2, list1);
    int carry = 0;
    Node *prev = 0;
    Node *cur1 = list1;
    Node *cur2 = list2;
    while(cur1) {
        if(cur2) {
            cur1->data += cur2->data + carry;
        }
        else if(carry) {
            cur1->data += carry;
        }
        else break;
        carry = (cur1->data > 9) ? 1 : 0;
        cur1->data %= 10;
        prev = cur1;
        cur1 = cur1->next;
        cur2 = (cur2) ? cur2->next : 0;
    }
    if(carry) {
        prev->next = new_node(1);
    }
    return list1;
}

int list_size(Node *node) {
    int size = 0;
    while(node) {
        node = node->next;
        size++;
    }
    return size;
}

void print_list(Node *node) {
    printf("(");
    print2(node);
    printf(") ");
    while(node) {
        char *delim = (node->next) ? ", " : "";
        printf("%d%s", node->data, delim);
        node = node->next;
    }
    printf("\n");
}

void print2(Node *node) {
    if(!node) return;
    print2(node->next);
    printf("%d", node->data);
}

void *xmalloc(size_t size) {
    void *p = malloc(size);
    if(!p) {
        printf("failed to allocate %lu bytes\n", size);
        exit(1);
    }
    return p;
}
