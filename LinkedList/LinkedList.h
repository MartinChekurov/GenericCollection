/**
 * @file LinkedList.h
 * 
 * @brief Represents a dynamic collection of objects, implements the #List interface
 * 
 * @details 
 *        Created by Martin Chekurov
 */
#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include"List.h"

/**
* @brief Private data of the #LinkedList object.
*/ 
typedef struct LinkedListPrivate_t LinkedListPrivate;

/**
 *  @brief Type of constructor to be executed.Ref. #newLinkedList.       
 */
typedef enum {

    /** @brief Creates an empty linked list.
     *         No other arguments        
     */
	LINKED_LIST_DEFAULT = 0,

    /** @brief Creates a linked list with a specified object size.
     *         Expected argument is of type size_t
     */
	LINKED_LIST_OBJECT_SIZE = 2,

    /** @brief Creates a linked list with a compare function.
     *         Expected argument is of type:
     *  @code int (*Cmp)(void*, void*)
     *  @endcode
     *         Used in actions requiring comparing, such as List's method contains()
     */
	LINKED_LIST_CMP = 8,
	
}LinkedListType;

/**
 * @brief Internal data of the LinkedList object.
 */ 
typedef struct {

    /**
     *  @brief Implements the #List interface.    
     */
    List* list;

   /**
    * @brief Private data of the LinkedList object.
    */ 
    LinkedListPrivate* private;    
    
}LinkedList;

/**
 * @brief Returns an #LinkedList object
 *
 * @details Can be used as an implementation of the #List interface or standalone
 * 
 * @param[in] Constuctor type of constructor to be executed.Ref. #LinkedListType
 * @param[in] ... The arguments must be in the same order as the bits in #LinkedListType
 *
 * @retval LinkedList Successful
 * @retval NULL Fail
 * 
 * @code        
 *         List list = newLinkedList(LINKED_LIST_OBJECT_SIZE, sizeof(int))->list;
 *         LinkedList* list = newLinkedList(LINKED_LIST_OBJECT_SIZE, sizeof(int));
 * @endcode
 */
LinkedList* newLinkedList(LinkedListType type, ...);

#endif