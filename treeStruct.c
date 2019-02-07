#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Wanted to test out definitions so implemented them into the "addToTree" function.

#define PASS 0
#define FAIL 1

// Node and stack structures.

struct Node {

    int data;
    int checked;
    struct Node *leftp;
    struct Node *rightp;
    void (*print)(struct Node*);

};

struct Stack {

    struct Node *items[10];
    int sp;

};

void printNodeData(struct Node *node) {

    printf("Data -> %d\nLeft Pointer -> %p\nRight Pointer -> %p\n", node->data, node->leftp, node->rightp);

}

// Methods for stack operations, push operation currently hard coded for up to 10 items.

void pushItem(struct Stack *stack, struct Node *node) {

    if (stack->sp > 10) {

        printf("Error: Stack full\n");
        return;

    }
    stack->items[stack->sp] = node;
    stack->sp++;

}

struct Node* popItem(struct Stack *stack) {

    if (stack->sp == 0) {

        printf("Error: Stack empty\n");
        return NULL;

    } else {

    stack->sp--;
    struct Node *node = stack->items[stack->sp-1];
    stack->items[stack->sp] = NULL;

    return (node);

    }

}

// Stack initialiser.

struct Stack *newStack() {

    struct Stack *stack = (struct Stack*) malloc(sizeof(struct Stack));

    stack->sp = 0;

    for (int i = 0; i < 10; i++) {

        stack->items[i] = NULL;

    }

    return (stack);
}

// Node initialiser.

struct Node *newNode(int data) {

    struct Node *node = (struct Node*) malloc(sizeof(struct Node));

    node->data = data;

    node->leftp = NULL;
    node->rightp = NULL;

    node->checked = 0;

    node->print = printNodeData;

    return (node);

}

// Method for adding an item to the correct space in the tree.

int addToTree(struct Node *root, struct Node *node) {

    struct Node *check = root;
    struct Node *parent = NULL;

    int a = 0;

    while (a == 0) {

        if (check == NULL) {

            break;

        }

        if (node->data > check->data) {

            parent = check;
            check = check->rightp;

        } else if (node->data < check->data) {

            parent = check;
            check = check->leftp;

        } else if(node->data == check->data) {

            printf("Data value matches value already in tree, skipping...\n\r");
            return FAIL;

        } else {

            printf("Error!\n");
            return FAIL;

        }

    }

    if (node->data > parent->data) {

        parent->rightp = node;

    } else if (node->data < parent->data) {

        parent->leftp = node;

    } else {

        return FAIL;

    }

    return PASS;

}

// Pre-order traversal function, may come back to this in the future and implement in and post order traversals...

void traverse (struct Node *root) {

    struct Stack *tree = newStack();
    struct Node *currentNode = NULL;

    int a = 0;
    int goback = 0;

    currentNode = root;

    while (a == 0) {

        if (goback == 0) {

        pushItem(tree, currentNode);

        }

        goback = 0;

        if (currentNode->checked != 1) {

            printf("Got data from node %p -> %d\n\r", currentNode, currentNode->data);

        } else {

            printf("Revisited node %p -> %d\n\r", currentNode, currentNode->data);

        }

        currentNode->checked = 1;

        if ((currentNode->leftp != NULL) && (currentNode->leftp->checked != 1)) {

            currentNode = currentNode->leftp;

        } else if ((currentNode->rightp != NULL) && (currentNode->rightp->checked != 1)) {

            currentNode = currentNode->rightp;

        } else if ((currentNode == root) && (root->leftp->checked == 1) && (root->rightp->checked == 1)) {

            printf("Done!\n\r");
            a++;


        } else if (tree->sp != 0) {

            popItem(tree);
            currentNode = tree->items[tree->sp-1];
            goback = 1;

        }

    }


}

int main() {

    // Declare nodes you want here (probably better to use an array of nodes but up to you).
    // Use the "addToTree" function by passing in the root node and the node you want to add.

    struct Node *rootNode = newNode(15);
    struct Node *a = newNode(5);
    struct Node *b = newNode(18);
    struct Node *c = newNode(10);
    struct Node *d = newNode(30);

    // Manual way of setting node pointers, kinda obselete now since I wrote the "addToTree" method.

    rootNode->leftp = a;
    rootNode->rightp = b;

    // Just demonstrating how you can use the return value of the add method to verify that the node was added correctly.

    if (addToTree(rootNode, c) == PASS) {

        if(addToTree(rootNode, d) == PASS) {

            printf("Successfully added nodes!\n\r");
            printf("Data at right pointer of 'a' -> %d\n\r", a->rightp->data);
            printf("Data at right pointer of 'b' -> %d\n\r", b->rightp->data);

        }

    }

    struct Node *e = newNode(3);
    struct Node *f = newNode(16);
    struct Node *g = newNode(16);

    addToTree(rootNode, e);
    addToTree(rootNode, f);
    addToTree(rootNode, g);

    // Traversal method only requires the root node to be passed in.

    traverse(rootNode);

    // Testing printNode function pointer.

    g->print(g);

}
