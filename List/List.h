/**
 * @file List.h
 * 
 * @brief Created by Martin Chekurov.
 * 
 * @details 
 *        Introduces Java's interface concept in C.
 */

#ifndef LIST_H_
#define LIST_H_

/**
 * @brief Represents a collection of objects.
 */ 
typedef struct {

    /**
     * @brief   Returns the number of elements in this list
     *
     * @param[in]   class   The #class member is given as an argument
     *
     * @return  the number of elements in this list or -1 in case of an error
     *
     * @retval  size_t  number of elements
     * 
     * @code        
     *              List* list = some impelemnting class;
     *              list->getSize(list->class)
     * @endcode
     */
    int (*getSize)(void* class);

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
    char (*add)(void* class, void* element);

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
    char (*get)(void* class, int index, void* element);

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