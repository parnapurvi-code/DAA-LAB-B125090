#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

/* =====================================================
                     DICTIONARY ITEM
   ===================================================== */

typedef struct
{
    int key;
    int value;
} Item;


/* =====================================================
                  OPERATION COUNTER
   ===================================================== */

long long operations = 0;

void resetCounter()
{
    operations = 0;
}

void step()
{
    operations++;
}


/* =====================================================
                  1. UNSORTED ARRAY
   ===================================================== */

typedef struct
{
    Item a[MAX];
    int n;
} UnsortedArray;


/* Insert */
void UA_Insert(UnsortedArray *D, Item x)
{
    D->a[D->n] = x;
    D->n++;

    step();
}


/* Search */
Item* UA_Search(UnsortedArray *D, int key)
{
    int i;

    for (i = 0; i < D->n; i++)
    {
        step();

        if (D->a[i].key == key)
            return &D->a[i];
    }

    return NULL;
}


/* Delete */
void UA_Delete(UnsortedArray *D, Item *x)
{
    int index;

    if (x == NULL)
        return;

    index = x - D->a;

    /* Order does not matter */
    D->a[index] = D->a[D->n - 1];

    D->n--;

    step();
}


/* Minimum */
Item* UA_Minimum(UnsortedArray *D)
{
    int i;
    int minIndex = 0;

    if (D->n == 0)
        return NULL;

    for (i = 1; i < D->n; i++)
    {
        step();

        if (D->a[i].key < D->a[minIndex].key)
            minIndex = i;
    }

    return &D->a[minIndex];
}


/* Maximum */
Item* UA_Maximum(UnsortedArray *D)
{
    int i;
    int maxIndex = 0;

    if (D->n == 0)
        return NULL;

    for (i = 1; i < D->n; i++)
    {
        step();

        if (D->a[i].key > D->a[maxIndex].key)
            maxIndex = i;
    }

    return &D->a[maxIndex];
}


/* Predecessor */
Item* UA_Predecessor(UnsortedArray *D, Item *x)
{
    int i;
    Item *answer = NULL;

    if (x == NULL)
        return NULL;

    for (i = 0; i < D->n; i++)
    {
        step();

        if (D->a[i].key < x->key)
        {
            if (answer == NULL ||
                D->a[i].key > answer->key)
            {
                answer = &D->a[i];
            }
        }
    }

    return answer;
}


/* Successor */
Item* UA_Successor(UnsortedArray *D, Item *x)
{
    int i;
    Item *answer = NULL;

    if (x == NULL)
        return NULL;

    for (i = 0; i < D->n; i++)
    {
        step();

        if (D->a[i].key > x->key)
        {
            if (answer == NULL ||
                D->a[i].key < answer->key)
            {
                answer = &D->a[i];
            }
        }
    }

    return answer;
}


/* =====================================================
                    2. SORTED ARRAY
   ===================================================== */

typedef struct
{
    Item a[MAX];
    int n;
} SortedArray;


/* Insert */
void SA_Insert(SortedArray *D, Item x)
{
    int i;

    i = D->n - 1;

    while (i >= 0 && D->a[i].key > x.key)
    {
        D->a[i + 1] = D->a[i];

        step();
        i--;
    }

    D->a[i + 1] = x;
    D->n++;

    step();
}


/* Search - Binary Search */
Item* SA_Search(SortedArray *D, int key)
{
    int left = 0;
    int right = D->n - 1;

    while (left <= right)
    {
        int mid;

        step();

        mid = (left + right) / 2;

        if (D->a[mid].key == key)
            return &D->a[mid];

        if (D->a[mid].key < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return NULL;
}


/* Delete */
void SA_Delete(SortedArray *D, Item *x)
{
    int index;
    int i;

    if (x == NULL)
        return;

    index = x - D->a;

    for (i = index; i < D->n - 1; i++)
    {
        D->a[i] = D->a[i + 1];
        step();
    }

    D->n--;

    step();
}


/* Minimum */
Item* SA_Minimum(SortedArray *D)
{
    if (D->n == 0)
        return NULL;

    step();

    return &D->a[0];
}


/* Maximum */
Item* SA_Maximum(SortedArray *D)
{
    if (D->n == 0)
        return NULL;

    step();

    return &D->a[D->n - 1];
}


/* Predecessor */
Item* SA_Predecessor(SortedArray *D, Item *x)
{
    int index;

    if (x == NULL)
        return NULL;

    index = x - D->a;

    if (index == 0)
        return NULL;

    step();

    return &D->a[index - 1];
}


/* Successor */
Item* SA_Successor(SortedArray *D, Item *x)
{
    int index;

    if (x == NULL)
        return NULL;

    index = x - D->a;

    if (index == D->n - 1)
        return NULL;

    step();

    return &D->a[index + 1];
}


/* =====================================================
               SINGLY LINKED LIST NODE
   ===================================================== */

typedef struct SNode
{
    Item data;
    struct SNode *next;
} SNode;


/* =====================================================
             3. SINGLY UNSORTED LIST
   ===================================================== */

typedef struct
{
    SNode *head;
} SinglyUnsorted;


/* Insert */
void SU_Insert(SinglyUnsorted *D, Item x)
{
    SNode *node;

    node = (SNode*)malloc(sizeof(SNode));

    node->data = x;
    node->next = D->head;
    D->head = node;

    step();
}


/* Search */
SNode* SU_Search(SinglyUnsorted *D, int key)
{
    SNode *p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key == key)
            return p;

        p = p->next;
    }

    return NULL;
}


/* Delete */
void SU_Delete(SinglyUnsorted *D, SNode *x)
{
    SNode *p;

    if (x == NULL)
        return;

    if (x == D->head)
    {
        D->head = x->next;
        free(x);

        step();
        return;
    }

    p = D->head;

    while (p->next != x)
    {
        p = p->next;
        step();
    }

    p->next = x->next;

    free(x);

    step();
}


/* Minimum */
SNode* SU_Minimum(SinglyUnsorted *D)
{
    SNode *p;
    SNode *answer;

    if (D->head == NULL)
        return NULL;

    answer = D->head;

    p = D->head->next;

    while (p != NULL)
    {
        step();

        if (p->data.key < answer->data.key)
            answer = p;

        p = p->next;
    }

    return answer;
}


/* Maximum */
SNode* SU_Maximum(SinglyUnsorted *D)
{
    SNode *p;
    SNode *answer;

    if (D->head == NULL)
        return NULL;

    answer = D->head;

    p = D->head->next;

    while (p != NULL)
    {
        step();

        if (p->data.key > answer->data.key)
            answer = p;

        p = p->next;
    }

    return answer;
}


/* Predecessor */
SNode* SU_Predecessor(SinglyUnsorted *D, SNode *x)
{
    SNode *p;
    SNode *answer = NULL;

    if (x == NULL)
        return NULL;

    p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key < x->data.key)
        {
            if (answer == NULL ||
                p->data.key > answer->data.key)
            {
                answer = p;
            }
        }

        p = p->next;
    }

    return answer;
}


/* Successor */
SNode* SU_Successor(SinglyUnsorted *D, SNode *x)
{
    SNode *p;
    SNode *answer = NULL;

    if (x == NULL)
        return NULL;

    p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key > x->data.key)
        {
            if (answer == NULL ||
                p->data.key < answer->data.key)
            {
                answer = p;
            }
        }

        p = p->next;
    }

    return answer;
}


/* =====================================================
                4. SINGLY SORTED LIST
   ===================================================== */

typedef struct
{
    SNode *head;
} SinglySorted;


/* Insert */
void SS_Insert(SinglySorted *D, Item x)
{
    SNode *node;
    SNode *p;

    node = (SNode*)malloc(sizeof(SNode));

    node->data = x;

    if (D->head == NULL ||
        x.key < D->head->data.key)
    {
        node->next = D->head;
        D->head = node;

        step();
        return;
    }

    p = D->head;

    while (p->next != NULL &&
           p->next->data.key < x.key)
    {
        p = p->next;
        step();
    }

    node->next = p->next;
    p->next = node;

    step();
}


/* Search */
SNode* SS_Search(SinglySorted *D, int key)
{
    SNode *p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key == key)
            return p;

        if (p->data.key > key)
            return NULL;

        p = p->next;
    }

    return NULL;
}


/* Delete */
void SS_Delete(SinglySorted *D, SNode *x)
{
    SNode *p;

    if (x == NULL)
        return;

    if (x == D->head)
    {
        D->head = x->next;
        free(x);

        step();
        return;
    }

    p = D->head;

    while (p->next != x)
    {
        p = p->next;
        step();
    }

    p->next = x->next;

    free(x);

    step();
}


/* Minimum */
SNode* SS_Minimum(SinglySorted *D)
{
    if (D->head == NULL)
        return NULL;

    step();

    return D->head;
}


/* Maximum */
SNode* SS_Maximum(SinglySorted *D)
{
    SNode *p;

    if (D->head == NULL)
        return NULL;

    p = D->head;

    while (p->next != NULL)
    {
        p = p->next;
        step();
    }

    return p;
}


/* Predecessor */
SNode* SS_Predecessor(SinglySorted *D, SNode *x)
{
    SNode *p;
    SNode *previous = NULL;

    if (x == NULL || x == D->head)
        return NULL;

    p = D->head;

    while (p != x)
    {
        previous = p;
        p = p->next;

        step();
    }

    return previous;
}


/* Successor */
SNode* SS_Successor(SinglySorted *D, SNode *x)
{
    if (x == NULL)
        return NULL;

    step();

    return x->next;
}


/* =====================================================
                DOUBLY LINKED NODE
   ===================================================== */

typedef struct DNode
{
    Item data;

    struct DNode *prev;
    struct DNode *next;

} DNode;


/* =====================================================
             5. DOUBLY UNSORTED LIST
   ===================================================== */

typedef struct
{
    DNode *head;
} DoublyUnsorted;


/* Insert */
void DU_Insert(DoublyUnsorted *D, Item x)
{
    DNode *node;

    node = (DNode*)malloc(sizeof(DNode));

    node->data = x;

    node->prev = NULL;
    node->next = D->head;

    if (D->head != NULL)
        D->head->prev = node;

    D->head = node;

    step();
}


/* Search */
DNode* DU_Search(DoublyUnsorted *D, int key)
{
    DNode *p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key == key)
            return p;

        p = p->next;
    }

    return NULL;
}


/* Delete */
void DU_Delete(DoublyUnsorted *D, DNode *x)
{
    if (x == NULL)
        return;

    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        D->head = x->next;

    if (x->next != NULL)
        x->next->prev = x->prev;

    free(x);

    step();
}


/* Minimum */
DNode* DU_Minimum(DoublyUnsorted *D)
{
    DNode *p;
    DNode *answer;

    if (D->head == NULL)
        return NULL;

    answer = D->head;
    p = D->head->next;

    while (p != NULL)
    {
        step();

        if (p->data.key < answer->data.key)
            answer = p;

        p = p->next;
    }

    return answer;
}


/* Maximum */
DNode* DU_Maximum(DoublyUnsorted *D)
{
    DNode *p;
    DNode *answer;

    if (D->head == NULL)
        return NULL;

    answer = D->head;
    p = D->head->next;

    while (p != NULL)
    {
        step();

        if (p->data.key > answer->data.key)
            answer = p;

        p = p->next;
    }

    return answer;
}


/* Predecessor */
DNode* DU_Predecessor(DoublyUnsorted *D, DNode *x)
{
    DNode *p;
    DNode *answer = NULL;

    if (x == NULL)
        return NULL;

    p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key < x->data.key)
        {
            if (answer == NULL ||
                p->data.key > answer->data.key)
            {
                answer = p;
            }
        }

        p = p->next;
    }

    return answer;
}


/* Successor */
DNode* DU_Successor(DoublyUnsorted *D, DNode *x)
{
    DNode *p;
    DNode *answer = NULL;

    if (x == NULL)
        return NULL;

    p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key > x->data.key)
        {
            if (answer == NULL ||
                p->data.key < answer->data.key)
            {
                answer = p;
            }
        }

        p = p->next;
    }

    return answer;
}


/* =====================================================
              6. DOUBLY SORTED LIST
   ===================================================== */

typedef struct
{
    DNode *head;
} DoublySorted;


/* Insert */
void DS_Insert(DoublySorted *D, Item x)
{
    DNode *node;
    DNode *p;

    node = (DNode*)malloc(sizeof(DNode));

    node->data = x;

    if (D->head == NULL ||
        x.key < D->head->data.key)
    {
        node->prev = NULL;
        node->next = D->head;

        if (D->head != NULL)
            D->head->prev = node;

        D->head = node;

        step();
        return;
    }

    p = D->head;

    while (p->next != NULL &&
           p->next->data.key < x.key)
    {
        p = p->next;
        step();
    }

    node->next = p->next;
    node->prev = p;

    if (p->next != NULL)
        p->next->prev = node;

    p->next = node;

    step();
}


/* Search */
DNode* DS_Search(DoublySorted *D, int key)
{
    DNode *p = D->head;

    while (p != NULL)
    {
        step();

        if (p->data.key == key)
            return p;

        if (p->data.key > key)
            return NULL;

        p = p->next;
    }

    return NULL;
}


/* Delete */
void DS_Delete(DoublySorted *D, DNode *x)
{
    if (x == NULL)
        return;

    if (x->prev != NULL)
        x->prev->next = x->next;
    else
        D->head = x->next;

    if (x->next != NULL)
        x->next->prev = x->prev;

    free(x);

    step();
}


/* Minimum */
DNode* DS_Minimum(DoublySorted *D)
{
    if (D->head == NULL)
        return NULL;

    step();

    return D->head;
}


/* Maximum */
DNode* DS_Maximum(DoublySorted *D)
{
    DNode *p;

    if (D->head == NULL)
        return NULL;

    p = D->head;

    while (p->next != NULL)
    {
        p = p->next;
        step();
    }

    return p;
}


/* Predecessor */
DNode* DS_Predecessor(DoublySorted *D, DNode *x)
{
    if (x == NULL)
        return NULL;

    step();

    return x->prev;
}


/* Successor */
DNode* DS_Successor(DoublySorted *D, DNode *x)
{
    if (x == NULL)
        return NULL;

    step();

    return x->next;
}


/* =====================================================
                     MAIN FUNCTION
   ===================================================== */

int main()
{
    UnsortedArray UA = {0};
    SortedArray SA = {0};

    SinglyUnsorted SU = {NULL};
    SinglySorted SS = {NULL};

    DoublyUnsorted DU = {NULL};
    DoublySorted DS = {NULL};

    int i;

    /*
       Insert 10 dictionary items.

       Example:
       key = 1, value = 10
       key = 2, value = 20
       ...
    */

    for (i = 1; i <= 10; i++)
    {
        Item x;

        x.key = i;
        x.value = i * 10;

        UA_Insert(&UA, x);
        SA_Insert(&SA, x);

        SU_Insert(&SU, x);
        SS_Insert(&SS, x);

        DU_Insert(&DU, x);
        DS_Insert(&DS, x);
    }


    /* =========================
              TEST SEARCH
       ========================= */

    Item *a;

    a = UA_Search(&UA, 5);

    if (a != NULL)
        printf("Unsorted Array Search: %d -> %d\n",
               a->key, a->value);


    a = SA_Search(&SA, 5);

    if (a != NULL)
        printf("Sorted Array Search: %d -> %d\n",
               a->key, a->value);


    /* =========================
              MINIMUM
       ========================= */

    a = SA_Minimum(&SA);

    if (a != NULL)
        printf("Sorted Array Minimum: %d -> %d\n",
               a->key, a->value);


    /* =========================
              MAXIMUM
       ========================= */

    a = SA_Maximum(&SA);

    if (a != NULL)
        printf("Sorted Array Maximum: %d -> %d\n",
               a->key, a->value);


    /* =========================
          SINGLY SORTED
       ========================= */

    SNode *s;

    s = SS_Search(&SS, 5);

    if (s != NULL)
    {
        printf("Singly Sorted Search: %d -> %d\n",
               s->data.key,
               s->data.value);

        s = SS_Predecessor(&SS, s);

        if (s != NULL)
            printf("Predecessor of 5: %d\n",
                   s->data.key);
    }


    /* =========================
          DOUBLY SORTED
       ========================= */

    DNode *d;

    d = DS_Search(&DS, 5);

    if (d != NULL)
    {
        printf("Doubly Sorted Search: %d -> %d\n",
               d->data.key,
               d->data.value);

        d = DS_Successor(&DS, d);

        if (d != NULL)
            printf("Successor of 5: %d\n",
                   d->data.key);
    }


    return 0;
}