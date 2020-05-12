/**
 * @file List.h
 * 
 * @brief Introduces Java's interface concept in 
 * 
 * @details 
 *        Created by Martin Chekurov
 */

#ifndef LIST_H_
#define LIST_H_

#include<stdlib.h>

/**
 * @brief Represents a dynamic collection of objects
 */ 
typedef struct {

    /**
     * @brief   Appends the specified element to the end of this list
     *
     * @param[in]   class   The #class member is given as an argument
     * @param[in]   element   element to be appended to this list
     *
     * @retval  0  successful
     * @retval  1  fail
     * 
     * @code        
     *              int num = 20;
     *              List* list = some impelemnting class;
     *              list->add(list->class, &num);
     * @endcode
     */
    int (*add)(void* class, void* element);

    /**
     * @brief   Returns the element at the specified position in this list
     *
     * @param[in]   class   The #class member is given as an argument
     * @param[in]   index   index of the element to return
     * @param[out]   element   element to be returned
     *
     * @retval  0  successful
     * @retval  1  fail
     * 
     * @code        
     *              int num = 0;
     *              List* list = some impelemnting class;
     *              list->get(list->class, 5, &num)
     * @endcode
     */
    int (*get)(void* class, size_t index, void* element);

    /**
     * @brief   Returns the number of elements in this list
     *
     * @param[in]   class   The #class member is given as an argument
     * @param[out]   size   number of elements in this list
     *
     * @retval  0  successful
     * @retval  1  fail
     * 
     * @code        
     *              List* list = some impelemnting class;
     *              list->getSize(list->class)
     * @endcode
     */
    int (*getSize)(void* class, size_t* size);

    /**
     * @brief   Removes all elements from the list
     *
     * @param[in]   class   The #class member is given as an argument
     *
     * @retval  0  successful
     * @retval  1  fail
     */
    int (*clear)(void* class);

    /**
     * @brief A pointer to the class that implements the interface
     * 
     * @details 
     *        Each class implementing this interface must assign itself to this pointer.
     *        This pointer is then passed as an argument to all methods of the interface.
     *          
     *        This is done, because the methods must have a way to access the class's interal data
     *        in order to provide implementation that depends on it.
     * 
     * @see getSize           
     */ 
    void *class;
    
}List;

#endif