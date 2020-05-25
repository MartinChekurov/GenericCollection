/**
 * @file ArrayList.h
 * 
 * @brief Represents a dynamic collection of objects, implements the #List interface
 * 
 * @details 
 *        Created by Martin Chekurov
 */
#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#include"List.h"

/**
* @brief Private data of the #ArrayList object.
*/ 
typedef struct ArrayListPrivate_t ArrayListPrivate;

/**
 *  @brief Describes which iterface is to be implemented      
 */
typedef enum {

    /** @brief Implements #List interface       
     */
	ARRAY_LIST_INTEFACE_LIST = 0,

    /** @brief Implements #Queue interface 
     */
	ARRAY_LIST_INTEFACE_QUEUE = 2,
	
}ArrayListInterface;

/**
 *  @brief Type of constructor to be executed.Ref. #newArrayList.       
 */
typedef enum {

    /** @brief Creates an array list with a default allocated size of 16.
     *         No other arguments        
     */
	ARRAY_LIST_DEFAULT = 0,

    /** @brief Creates an array list with a specified object size.
     *         Expected argument is of type size_t
     */
	ARRAY_LIST_OBJECT_SIZE = 2,

    /** @brief Creates an array list with a specified allocated size.
     *         Expected argument is of type size_t   
     */
	ARRAY_LIST_ALLOC_SIZE = 4,

    /** @brief Creates an array list with a compare function.
     *         Expected argument is of type:
     *  @code int (*Cmp)(void*, void*)
     *  @endcode
     *         Used in actions requiring comparing, such as List's method contains()
     */
	ARRAY_LIST_CMP = 8,
	
}ArrayListType;

/**
 * @brief Internal data of the ArrayList object.
 */ 
typedef struct {

    /**
     *  @brief Implements the #List interface.    
     */
    List* list;

   /**
    * @brief Private data of the ArrayList object.
    */ 
    ArrayListPrivate* private;    
    
}ArrayList;

/**
 * @brief Returns an #ArrayList object
 *
 * @details Can be used as an implementation of the #List interface or standalone
 * 
 * @param[in] interface Type of interface to be implemented.Ref. #ArrayListInterface
 * @param[in] type Type of constructor to be executed.Ref. #ArrayListType
 * @param[in] ... The arguments must be in the same order as the bits in #ArrayListType
 *
 * @retval ArrayList Successful
 * @retval NULL Fail
 * 
 * @code        
 *         List list = newArrayList(ARRAY_LIST_INTEFACE_LIST,
 *                                  ARRAY_LIST_OBJECT_SIZE | ARRAY_LIST_ALLOC_SIZE,
 *                                  sizeof(int), 10)->list;
 *         ArrayList* list = newArrayList(ARRAY_LIST_INTEFACE_LIST,
 *                                       ARRAY_LIST_OBJECT_SIZE | ARRAY_LIST_ALLOC_SIZE,
 *                                       sizeof(int), 10);
 * @endcode
 */
ArrayList* newArrayList(ArrayListInterface interface, ArrayListType type, ...);

#endif