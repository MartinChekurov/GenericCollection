#include"LinkedList.h"
#include<stdlib.h>
#include<stdarg.h>
#include<limits.h>
#include<string.h>

typedef int (*Cmp)(void*, void*);

typedef struct Node_t {

    void* data;
    struct Node_t* pNext;

}Node;

struct LinkedListPrivate_t {

    Node* head;
    size_t size;
    size_t elemSize;

    Cmp cmp;
};

static Node* newNode(void* data, size_t dataSize)
{
    if (!data) {
        return NULL;
    }
    Node* node = malloc(sizeof(*node));
    if (!node) {
        return NULL;
    }
    memset(node, 0, sizeof(*node));
    node->data = malloc(dataSize);
    if (!node->data) {
        return NULL;
    }
    memcpy(node->data, data, dataSize);
    return node;
}

static int destroyNode(Node* node)
{
    if (!node) {
        return 1;
    }
    free(node->data);
    free(node);
    return 0;
}

static Node* getIndex(LinkedList* list, size_t index)
{
    Node* node = NULL;
    size_t count = 0;
    if (!list || !list->private) {
        return NULL;
    }
    node = list->private->head;
    while(node && count < list->private->size) {
        if (count == index) {
            return node;
        }
        node = node->pNext;
        count++;
    }
    return NULL;
}

static int contains_(void* class, void* object, size_t* index)
{
    size_t i = 0;
    Node* node = 0;
    LinkedList* list = class;
    if (!list || !object || !index || !list->private ||
        !list->private->cmp) {
        return 1;
    }
    for (i = 0 ; i < list->private->size ; i++) {
        node = getIndex(list, i);
        if (node && node->data) {
            if (!list->private->cmp(node->data, object)) {
                *index = i;
                return 0;
            }
        }
    }
    return 1;
}

static int getSize(void* class, size_t* size)
{
    LinkedList* list = class;
    if (!list || !size) {
        return 1;
    }
    *size = list->private->size;
    return 0;
}

static int add(void* class, void* object)
{   
    LinkedList* list = class;
    Node* node = 0, *currNode = 0;
    if (!list || !object || !list->private) {
        return 1;
    }
    if (!list->private->size >= ((size_t)-1)) {
        return 1;
    }
    node = newNode(object, list->private->elemSize);
    if (!node) {
        return 1;
    }
    if (!list->private->head) {
        list->private->head = node;
        node->pNext = NULL;       
    } else {
        currNode = list->private->head;
        while(currNode->pNext) {
            currNode = currNode->pNext;
        }
        currNode->pNext = node;
        node->pNext = 0;
    }
    list->private->size++;
    return 0;
}

static int addIndex(void* class, size_t index, void* object)
{
    LinkedList* list = class;
    Node* node = 0, *currNode = 0;
    size_t i = 0;
    if (!list || !object || !list->private) {
        return 1;
    }
    if (!list->private->size >= ((size_t)-1) ||
        index >= list->private->size) {
        return 1;
    }
    node = newNode(object, list->private->elemSize);
    if (!node) {
        return 1;
    }
    if (!list->private->head) {
        list->private->head = node;
        node->pNext = NULL;       
    } else {
        currNode = list->private->head;
        while(currNode->pNext) {
            if (i+1 == index) {
                node->pNext = currNode->pNext;
                currNode->pNext = node;
                list->private->size++;
                return 0;
            }
            i++;
            currNode = currNode->pNext;
        }
    }
    return 1;
}

static int get(void* class, size_t index, void* object)
{
    LinkedList* list = class;
    Node* node = 0;
    if (!list || !object || !list->private || (index >= (size_t)-1)) {
        return 1;
    }  
    node = getIndex(list, index);
    if (node && node->data) {
        memcpy(object, node->data, list->private->elemSize);
        return 0;
    }
    return 1;
}

static int set(void* class, size_t index, void* object)
{
    LinkedList* list = class;
    Node* node = NULL;
    if (!list || !object || !list->private || (index >= (size_t)-1)) {
        return 1;
    }  
    if (!list->private->size || index >= list->private->size) {
        return 1;
    }
    node = getIndex(list, index);
    if (!node) {
        return 1;
    }
    memcpy(node->data, object, list->private->elemSize);
    return 0;
}

static int clear(void* class)
{
    Node* node = NULL;
    LinkedList* list = class;
    if (!list) {
        return 1;
    }
    while(list->private->head) {
        node = list->private->head;
        list->private->head = node->pNext;
        if (destroyNode(node)) {
            return 1;
        }
    }
    list->private->size = 0;
    return 0;
}

static int removeIndex(void* class, size_t index)
{
    LinkedList* list = class;
    Node* currNode = NULL;
    size_t i = 0;
    if (!list || !list->private || (index >= (size_t)-1)) {
        return 1;
    }
    if (!list->private->size || index >= list->private->size) {
        return 1;
    }
    currNode = list->private->head;
    while(currNode && currNode->pNext) {
        if (i+1 == index) {
            currNode->pNext = currNode->pNext->pNext;
            list->private->size--;
            return 0;
        }
        currNode = currNode->pNext;
        i++;
    }
    return 1;
}

static int remove(void* class, void* object)
{   
    int status = 0;
    size_t index = 0;
    if (!class || !object) {
        return 1;
    }
    status = contains_(class, object, &index);
    if (status) {
        return 1;
    }
    status = removeIndex(class, index);
    if (status) {
        return 1;
    }
    return 0;
}

static int contains(void* class, void* object)
{
    int status = 0;
    size_t index = 0;
    if (!class || !object) {
        return 1;
    }
    status = contains_(class, object, &index);
    if (status) {
        return 1;
    }
    return 0;
}

static int destroy(void* class)
{
    LinkedList* list = class;
    if (!list || !list->private) {
        return 1;
    }
    clear(list);
    free(list->private);
    free(list->list);
    free(list);
    return 0;
}

static LinkedList* constructor(size_t elemSize, Cmp cmp)
{
    LinkedList* linkedList = calloc(1, sizeof(*linkedList));
    if (!linkedList) {
        return NULL;
    }
    linkedList->private = calloc(1, sizeof(*linkedList->private));
    if (!linkedList->private) {
        return NULL;
    }
    linkedList->list = calloc(1, sizeof(*linkedList->list));
    if (!linkedList->private) {
        return NULL;
    }
    
    linkedList->list->getSize = getSize;
    linkedList->list->get = get;
    linkedList->list->set = set;

    linkedList->list->add = add;
    linkedList->list->addIndex= addIndex;

    linkedList->list->clear = clear;
    linkedList->list->removeIndex = removeIndex;
    linkedList->list->remove = remove;

    linkedList->list->contains = contains;

    if (cmp) {
        linkedList->private->cmp = cmp;
    }
    linkedList->list->class = linkedList;
    linkedList->private->elemSize = elemSize;
    return linkedList;
}

LinkedList* newLinkedList(LinkedListType type, ...)
{   
    size_t elemSize = 0;
    Cmp cmp = 0;

    size_t i = 0;
    LinkedList* linkedList = NULL;

    if (!type) {
        return 0;
    }

    va_list args;
    va_start(args, type);

    if (type & LINKED_LIST_OBJECT_SIZE) {
        elemSize = va_arg(args, size_t);
    }
    if (type & LINKED_LIST_CMP) {
        cmp = va_arg(args, Cmp);
    }

    linkedList = constructor(elemSize, cmp);
    va_end(args);
    return linkedList;
}