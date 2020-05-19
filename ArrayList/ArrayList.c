#include"ArrayList.h"
#include<stdlib.h>
#include<stdarg.h>
#include<limits.h>
#include<string.h>

#define ARRAY_LIST_INITIAL_SIZE (16)

typedef int (*Cmp)(void*, void*);

struct Private_t {

    size_t size;
    size_t elemSize;
    size_t allocSize;
    void* array;

    Cmp cmp;
};

static int contains_(void* class, void* object, size_t* index)
{
    size_t *obj = 0, size = 0, elemSize = 0, i = 0;
    Cmp cmp = 0;
    if (!class || !object || !index || !((ArrayList*)class)->private ||
        !((ArrayList*)class)->private->cmp) {
        return 1;
    }
    size = ((ArrayList*)class)->private->size;
    elemSize = ((ArrayList*)class)->private->elemSize;
    cmp = ((ArrayList*)class)->private->cmp;
    for (i = 0 ; i < size ; i++) {
        obj = ((ArrayList*)class)->private->array + (i*elemSize);
        if (!cmp(obj, object)) {
            *index = i;
            return 0;
        }
    }
    return 1;
}

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
    size_t pos = 0, size = 0, elemSize = 0, allocSize = 0;
    if (!class || !object || !((ArrayList*)class)->private) {
        return 1;
    }
    size = ((ArrayList*)class)->private->size;
    if (!size >= ((size_t)-1)) {
        return 1;
    }
    elemSize = ((ArrayList*)class)->private->elemSize;
    allocSize = ((ArrayList*)class)->private->allocSize;
    if (size >= allocSize) {
        if (resize(class)) {
            return 1;
        }
    }
    pos = size * elemSize;
    memcpy(((ArrayList*)class)->private->array + pos, object, elemSize);
    ((ArrayList*)class)->private->size++;
    return 0;
}

static int addIndex(void* class, size_t index, void* object)
{
    size_t *src = 0, *dst = 0, size = 0, elemSize = 0, allocSize = 0;
    if (!class || !object || !((ArrayList*)class)->private) {
        return 1;
    }
    size = ((ArrayList*)class)->private->size;
    if (size >= ((size_t)-1) || index >= size) {
        return 1;
    }
    elemSize = ((ArrayList*)class)->private->elemSize;
    allocSize = ((ArrayList*)class)->private->allocSize;
    if (size >= allocSize) {
        if (resize(class)) {
            return 1;
        }
    }
    src = ((ArrayList*)class)->private->array + (index * elemSize);
    dst = ((ArrayList*)class)->private->array + ((index+1) * elemSize);
    memmove(dst, src, (size - index) * elemSize);
    memcpy(src, object, elemSize);
    ((ArrayList*)class)->private->size++;
    return 0;
}

static int get(void* class, size_t index, void* object)
{
    size_t *pos = 0, size = 0, elemSize = 0;
    if (!class || !object || !((ArrayList*)class)->private || (index >= (size_t)-1)) {
        return 1;
    }  
    size = ((ArrayList*)class)->private->size;
    if (!size || index >= size) {
        return 1;
    }
    elemSize = ((ArrayList*)class)->private->elemSize;
    pos = ((ArrayList*)class)->private->array + (index * elemSize);
    memcpy(object, pos, elemSize);
    return 0;
}

static int set(void* class, size_t index, void* object)
{
    size_t *pos = 0, size = 0, elemSize = 0;
    if (!class || !object || !((ArrayList*)class)->private || (index >= (size_t)-1)) {
        return 1;
    }  
    size = ((ArrayList*)class)->private->size;
    if (!size || index >= size) {
        return 1;
    }
    elemSize = ((ArrayList*)class)->private->elemSize;
    pos = ((ArrayList*)class)->private->array + (index * elemSize);
    memset(pos, 0, elemSize);
    memcpy(pos, object, elemSize);
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

static int removeIndex(void* class, size_t index)
{
    size_t *src = 0, *dst = 0;
    size_t size = 0, elemSize = 0;
    if (!class || !((ArrayList*)class)->private || (index >= (size_t)-1)) {
        return 1;
    }
    size = ((ArrayList*)class)->private->size;
    if (!size || index >= size) {
        return 1;
    }
    elemSize = ((ArrayList*)class)->private->elemSize;
    src = ((ArrayList*)class)->private->array + ((index + 1) * elemSize); 
    dst = ((ArrayList*)class)->private->array + (index * elemSize);
    memmove(dst, src, (size - index - 1) * elemSize);
    ((ArrayList*)class)->private->size--;
    return 0;
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
    arrayList->list->get = get;
    arrayList->list->set = set;

    arrayList->list->add = add;
    arrayList->list->addIndex= addIndex;

    arrayList->list->clear = clear;
    arrayList->list->removeIndex = removeIndex;
    arrayList->list->remove = remove;

    arrayList->list->contains = contains;

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