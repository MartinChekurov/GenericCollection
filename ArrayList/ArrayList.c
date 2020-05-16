#include"ArrayList.h"
#include<stdlib.h>
#include<stdarg.h>
#include<limits.h>
#include<string.h>
#include<stdio.h>

#define ARRAY_LIST_INITIAL_SIZE (16)

typedef int (*Cmp)(void*, void*);

struct Private_t {

    size_t size;
    size_t elemSize;
    size_t allocSize;
    void* array;

    Cmp cmp;
};

static char resize(ArrayList* arrayList)
{
    void* newArray = NULL;
    if (!arrayList) {
        return 1;
    }
    newArray = realloc(arrayList->private->array, arrayList->private->allocSize * 2);
    if (!newArray) {
        return 1;
    }
    arrayList->private->array = newArray;
    arrayList->private->allocSize *= 2;
    return 0;
}

static int getSize(void* class, size_t* size)
{
    if (!class || !size) {
        return 1;
    }
    *size = ((ArrayList*)class)->private->size;
    return 0;
}

static int add(void* class, void* object)
{
    size_t pos = 0, *size = 0, *elemSize = 0, *allocSize = 0;
    if (!class || !object || !((ArrayList*)class)->private) {
        return 1;
    }
    size = &(((ArrayList*)class)->private->size);
    if (!*size >= ((size_t)-1)) {
        return 1;
    }
    elemSize = &(((ArrayList*)class)->private->elemSize);
    allocSize = &(((ArrayList*)class)->private->allocSize);
    if (*size >= *allocSize) {
        if (resize(class)) {
            return 1;
        }
    }
    pos = (*size) * (*elemSize);
    memcpy(((ArrayList*)class)->private->array + pos, object, *elemSize);
    (*size)++;
    return 0;
}

static int get(void* class, size_t index, void* object)
{
    size_t *pos = 0, *size = 0, *elemSize = 0;
    if (!class || !object || !((ArrayList*)class)->private || (index >= (size_t)-1)) {
        return 1;
    }  
    size = &(((ArrayList*)class)->private->size);
    if (!*size || index >= *size) {
        return 1;
    }
    (*size)--;
    elemSize = &(((ArrayList*)class)->private->elemSize);
    pos = ((ArrayList*)class)->private->array + ((*size)*(*elemSize));
    memcpy(object, pos, *elemSize);
    return 0;
}

static int set(void* class, size_t index, void* object)
{
    size_t *pos = 0, *size = 0, *elemSize = 0;
    if (!class || !object || !((ArrayList*)class)->private || (index >= (size_t)-1)) {
        return 1;
    }  
    size = &(((ArrayList*)class)->private->size);
    if (!*size || index >= *size) {
        return 1;
    }
    elemSize = &(((ArrayList*)class)->private->elemSize);
    pos = ((ArrayList*)class)->private->array + (index)*(*elemSize);
    memset(pos, 0, *elemSize);
    memcpy(pos, object, *elemSize);
    return 0;
}

static int clear(void* class)
{
    if (!class) {
        return 1;
    }
    ((ArrayList*)class)->private->size = 0;
    return 0;
}

static int remove_(void* class, size_t index)
{
    size_t *src = 0, *dst = 0;
    size_t *size = 0, *elemSize = 0;
    if (!class || !((ArrayList*)class)->private || (index >= (size_t)-1)) {
        return 1;
    }
    size = &(((ArrayList*)class)->private->size);
    if (!*size || index >= *size) {
        return 1;
    }
    elemSize = &(((ArrayList*)class)->private->elemSize);
    src = ((ArrayList*)class)->private->array + ((index + 1) * (*elemSize)); 
    dst = ((ArrayList*)class)->private->array + ((index) * (*elemSize));
    memmove(dst, src, (*size - index - 1) * (*elemSize));
    (*size)--;
    return 0;
}

static int contains(void* class, void* object)
{
    size_t *obj = 0, *size = 0, *elemSize = 0, i = 0;
    Cmp cmp = 0;
    if (!class || !object || !((ArrayList*)class)->private ||
        !((ArrayList*)class)->private->cmp) {
        return 1;
    }
    size = &(((ArrayList*)class)->private->size);
    elemSize = &(((ArrayList*)class)->private->elemSize);
    cmp = ((ArrayList*)class)->private->cmp;
    for (i = 0 ; i < *size ; i++) {
        obj = ((ArrayList*)class)->private->array + (i*(*elemSize));
        if (!cmp(obj, object)) {
            return 0;
        }
    }
    return 1;
}

static ArrayList* constructor(size_t elemSize, size_t allocSize, Cmp cmp)
{
    ArrayList* arrayList = calloc(1, sizeof(*arrayList));
    if (!arrayList) {
        return NULL;
    }
    arrayList->private = calloc(1, sizeof(*arrayList->private));
    if (!arrayList->private) {
        return NULL;
    }
    arrayList->list = calloc(1, sizeof(*arrayList->list));
    if (!arrayList->private) {
        return NULL;
    }
    arrayList->list->getSize = getSize;
    arrayList->list->add = add;
    arrayList->list->get = get;
    arrayList->list->clear = clear;
    arrayList->list->remove = remove_;
    arrayList->list->contains = contains;
    arrayList->list->set = set;

    if (cmp) {
        arrayList->private->cmp = cmp;
    }
    arrayList->list->class = arrayList;
    arrayList->private->elemSize = elemSize;
    arrayList->private->allocSize = allocSize;
    arrayList->private->array = calloc(arrayList->private->allocSize, arrayList->private->elemSize);
    if (!arrayList->private->array) {
        return NULL;
    }
    return arrayList;
}

ArrayList* newArrayList(ArrayListType type, ...)
{   
    size_t elemSize = 0;
    size_t allocSize = ARRAY_LIST_INITIAL_SIZE;
    Cmp cmp = 0;

    size_t i = 0;
    ArrayList* arrayList = NULL;

    if (!type) {
        return 0;
    }

    va_list args;
    va_start(args, type);

    if (type & ARRAY_LIST_OBJECT_SIZE) {
        elemSize = va_arg(args, size_t);
    }
    if (type & ARRAY_LIST_ALLOC_SIZE) {
        allocSize = va_arg(args, size_t);
    }
    if (type & ARRAY_LIST_CMP) {
        cmp = va_arg(args, Cmp);
    }

    arrayList = constructor(elemSize, allocSize, cmp);
    va_end(args);
    return arrayList;
}