#include"ArrayList.h"
#include<stdlib.h>
#include<stdarg.h>
#include<limits.h>
#include<string.h>

#define ARRAY_LIST_INITIAL_SIZE (10)

struct Private_t {

    size_t size;

    size_t elemSize;
    size_t allocSize;
    void* array;
};

int  getSize(void* class);
char add    (void* class, void* element);
char get    (void* class, int index, void* element);

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

static ArrayList* constructor(size_t allocSize, size_t elemSize)
{
    ArrayList* arrayList = calloc(1, sizeof(*arrayList));
    if (!arrayList) {
        return NULL;
    }
    arrayList->private = calloc(1, sizeof(*arrayList->private));
    if (!arrayList->private) {
        return NULL;
    }
    arrayList->list.class = arrayList;
    arrayList->list.getSize = getSize;
    arrayList->list.add = add;
    arrayList->list.get = get;
    arrayList->private->elemSize = elemSize;
    arrayList->private->allocSize = allocSize;
    arrayList->private->array = calloc(arrayList->private->allocSize, arrayList->private->elemSize);
    if (!arrayList->private->array) {
        return NULL;
    }
    return arrayList;
}

ArrayList* newArrayList(ArrayListConstructor constuctor, ...)
{
    ArrayList* arrayList = NULL;
    va_list args;
    va_start(args, constuctor);
    switch(constuctor) {
        case ARRAY_LIST_DEFAULT:
            arrayList = constructor(ARRAY_LIST_INITIAL_SIZE, va_arg(args, size_t));
            break;
        case ARRAY_LIST_SET_SIZE:
            arrayList = constructor(va_arg(args, size_t), va_arg(args, size_t));
            break;
    }
    va_end(args);
    return arrayList;
}

int getSize(void* class)
{
    size_t size = 0;
    if (!class) {
        return -1;
    }
    size = ((ArrayList*)class)->private->size;
    return size > INT_MAX ? -1 : size;
}

char add(void* class, void* element)
{
    size_t pos = 0;
    if (!class || !element) {
        return 1;
    }
    if (((ArrayList*)class)->private->size >= ((ArrayList*)class)->private->allocSize) {
        if (resize(class)) {
            return 1;
        }
    }
    pos = ((ArrayList*)class)->private->size * ((ArrayList*)class)->private->elemSize;
    memcpy(((ArrayList*)class)->private->array + pos, element, ((ArrayList*)class)->private->elemSize);
    ((ArrayList*)class)->private->size++;
    return 0;
}

char get(void* class, int index, void* element)
{
    size_t pos = 0;
    if (!class || !element || !((ArrayList*)class)->private->size) {
        return 1;
    }  
    ((ArrayList*)class)->private->size--;
    pos = ((ArrayList*)class)->private->size * ((ArrayList*)class)->private->elemSize;
    memcpy(element, ((ArrayList*)class)->private->array + pos, ((ArrayList*)class)->private->elemSize);
    return 0;
}