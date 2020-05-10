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
typedef struct Private_t Private;

/**
 *  @brief Type of constructor to be executed.Ref #newArrayList
 */
typedef enum {

    /**
     * @brief Creates an #ArrayList with a default allocated size of 16.
     * 
     * @details
     *         Constructor arguments(in order):
     *         
     *         ARRAY_LIST_DEFAULT  
     *      
     *         size_t - size of the elements in the list        
     */
    ARRAY_LIST_DEFAULT,

    /**
     * @brief Creates an #ArrayList with a specified allocated size.
     * 
     * @details
     *         Constructor arguments(in order):
     *         
     *         ARRAY_LIST_SET_SIZE
     * 
     *         size_t - allocated size of the list
     *         
     *         size_t - size of the elements in the list  
     *         
     */
    ARRAY_LIST_SET_SIZE

}ArrayListConstructor;

/**
 * @brief Internal data of the ArrayList object.
 */ 
typedef struct {

    /**
     *  @brief Implements the #List interface.    
     */
    List list;

   /**
    * @brief Private data of the ArrayList object.
    */ 
    Private* private;    
    
}ArrayList;

/**
 * @brief   Returns an #ArrayList object
 *
 * @details
 *          Can be used as an implementation of the #List interface or standalone
 * 
 * @param[in]   constuctor   type of constructor to be executed.Ref #ArrayListConstructor
 * @param[in]   ...   var args.Ref #ArrayListConstructor
 *
 * @retval  ArrayList  object if successful
 * @retval  NULL  if fail 
 * 
 * @code        
 *         List list = newArrayList(ARRAY_LIST_SET_SIZE, 5, sizeof(int))->list;
 *         ArrayList* list = newArrayList(ARRAY_LIST_SET_SIZE, 5, sizeof(int));
 * @endcode
 */
ArrayList* newArrayList(ArrayListConstructor constuctor, ...);

#endif