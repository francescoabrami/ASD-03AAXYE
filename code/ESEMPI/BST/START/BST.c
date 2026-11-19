#include <stdio.h>
#include <stdlib.h>

typedef struct node * link; 

typedef struct {

    int value;
    int key;

} Item;

typedef struct node {

    int key;
    link left;
    link right;

} node_t;

link BSTInit(void);
link BSTNew(int key);
link BSTInsert(link h, int key);
link BSTSearch(link h, int key);
link BSTmax(link h);
link BSTmin(link h);
void BSTpreorder(link h);
void BSTpostorder(link h);
void BSTinorder(link h);
int BSTcount(link h);
int BSTheight(link h);
void BSTfree(link h);
void BSTstampa(link h, int level);
link ROTATEright(link h);
link ROTATEleft(link h);
link BSTinsertRoot(link h, int key);
link BSTlist(link h);
link ListToBST(link * head, int n);

link BSTinit(void) {

    return NULL;

}

link BSTNew(int key) {

    link x = malloc(sizeof(*x));

    x->key = key;
    x->left = NULL;
    x->right = NULL;

    return x;

}

link BSTInsert(link h, int key) {

    if (h == NULL) {

        return BSTNew(key);

    }
    
    if (key < h->key) {

        h->left = BSTInsert(h->left, key);

    }

    else if (key > h->key) {

        h->right = BSTInsert(h->right, key);

    }

    return h;

}

link BSTSearch(link h, int key) {

    while (h != NULL && key != h->key) {

        if (key < h->key) {

            h = h->left;

        }
        
        else {

            h = h->right;

        }    

    }

    return h;

}

link BSTmax(link h) {

    if (h == NULL) {

        return NULL;

    }
        
    if (h->right == NULL) {

        return h;

    }
        
    return BSTmax(h->right);

}

link BSTmin(link h) {

    if (h == NULL) {

        return NULL;

    }

    if (h->left == NULL) {

        return h;

    }

    return BSTmin(h->left);

}

void BSTpreorder(link h) {

    if (h == NULL) {

        return;

    }

    printf("%d ", h->key);

    BSTpreorder(h->left);

    BSTpreorder(h->right);

    return;

}

void BSTpostorder(link h) {

    if (h == NULL) {

        return;

    }

    BSTpostorder(h->left);

    BSTpostorder(h->right);

    printf("%d ", h->key);

    return;

}

void BSTinorder(link h) {

    if (h == NULL) {

        return;

    }

    BSTinorder(h->left);

    printf("%d ", h->key);

    BSTinorder(h->right);

    return;

}

int BSTcount(link h) {

    if (h == NULL) {

        return 0;

    }

    return 1 + BSTcount(h->left) + BSTcount(h->right);

}

int BSTheight(link h) {

    if (h == NULL) {

        return -1;

    }

    int hl = BSTheight(h->left);
    int hr = BSTheight(h->right);

    return (hl > hr ? hl : hr) + 1;

}

void BSTfree(link h) {

    if (h == NULL) {

        return;

    }

    BSTfree(h->left);
    BSTfree(h->right);

    free(h);

    return;

}

void BSTstampa(link h, int level) {

    if (h == NULL) {

        return;

    }

    BSTstampa(h->right, level + 1);

    for (int i = 0; i < level; i++) {

        printf("    ");

    }

    printf("%d\n", h->key);

    BSTstampa(h->left, level + 1);

    return;

}

link ROTATEright(link h) {

    if (h == NULL || h->left == NULL) {

        return h;

    }

    link x = h->left;

    h->left = x->right;
    x->right = h;

    return x;

}

link ROTATEleft(link h) {

    if (h == NULL || h->right == NULL) {

        return h;

    }

    link x = h->right;

    h->right = x->left;
    x->left = h;

    return x;

}

link BSTinsertRoot(link h, int key) {

    if (h == NULL) {

        return BSTNew(key);

    }

    if (key < h->key) {

        h->left = BSTinsertRoot(h->left, key);

        h = ROTATEright(h);

    }

    else if (key > h->key) { 

        h->right = BSTinsertRoot(h->right, key);

        h = ROTATEleft(h);

    }

    return h;

}

void BSTtoList(link * root) {

    link *p = root;

    while (*p != NULL) {

        if ((*p)->left != NULL) {

            *p = ROTATEright(*p);

        }

        else {

            p = &((*p)->right);

        }

    }

}

link ListToBST(link * head, int n) {


    if (n <= 0) {

        return NULL;

    }

    link left = ListToBST(head, n /2);
    link root = * head;

    *head = (*head)->right;
    root->left = left;

    root->right = ListToBST(head, n - n / 2 - 1);

    return root;

}

int main (void) {

    link root = BSTinit();

    root = BSTInsert(root, 50);
    root = BSTInsert(root, 30);
    root = BSTInsert(root, 70);
    root = BSTInsert(root, 20);
    root = BSTInsert(root, 40);
    root = BSTInsert(root, 60);
    root = BSTInsert(root, 80);
    root = BSTInsert(root, 10);
    root = BSTInsert(root, 96);
    root = BSTInsert(root, 12);
    root = BSTInsert(root, 5);
    root = BSTInsert(root, 4);

    link key = NULL;
    link min = NULL;
    link max = NULL;

    key = BSTSearch(root, 80);

    if (key != NULL) {

        printf("FOUND! VALUE %d\n\n", key->key);

    } 

    else {

        printf("NOT FOUND!\n\n");

    }

    min = BSTmin(root);
    max = BSTmax(root);

    printf("MAX %d \n\nMIN %d\n\n", max->key, min->key);

    printf("PREORDER: ");
    BSTpreorder(root);
    printf("\n\n");

    printf("POSTORDER: ");
    BSTpostorder(root);
    printf("\n\n");

    printf("INORDER: ");
    BSTinorder(root);
    printf("\n\n");

    printf("COUNT: %d\n\n", BSTcount(root));
    printf("HEIGHT: %d\n\n", BSTheight(root));

    printf("ALBERO: \n\n");
    BSTstampa(root, 0);

    root = BSTinsertRoot(root, 35);
    printf("HEIGHT: %d\n", BSTheight(root));
    BSTstampa(root, 0);

    BSTInsert(root, 1);

    root = BSTinsertRoot(root, 20);
    printf("HEIGHT: %d\n", BSTheight(root));
    BSTstampa(root, 0);

    printf("LIST:\n\n");
    BSTtoList(&root);

    root = BSTInsert(root, 100);
    root = BSTInsert(root, 150);

    BSTstampa(root, 0);

    for (int i = 300; i < 400; i++) {

        root = BSTInsert(root, i);

    }

    for (int i = 600; i < 1000; i++) {

        root = BSTInsert(root, i);

    }

    printf("BALANCED BST:\n\n");
    root = ListToBST(&root, BSTcount(root));
    BSTstampa(root, 0);

    min = BSTmin(root);
    max = BSTmax(root);

    printf("MAX %d \n\nMIN %d\n\n", max->key, min->key);

    printf("COUNT: %d\n\n", BSTcount(root));
    printf("HEIGHT: %d\n\n", BSTheight(root));

    BSTtoList(&root);
    BSTstampa(root, 0);

    BSTfree(root);
    root = NULL;

    return 0;

}


