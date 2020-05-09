#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include"List.h"

typedef struct Private_t Private;

typedef enum {

    ARRAY_LIST_DEFAULT,
    ARRAY_LIST_SET_SIZE

}ArrayListConstructor;

typedef struct {

    /*There is no leading paddings.
    * The address of a struct is the same as the address of its first member.
    * This is why the interface have to be the first elememt.
    * List* list = (List*)arrayList(); is guarantied to work.
    */
    List list;

    Private* private;    
    
}ArrayList;

ArrayList* newArrayList(ArrayListConstructor constuctor, ...);

#endif