/**
 * @file List.h
 * 
 * @brief Represents a dynamic collection of objects
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
     * @brief Appends the specified object to the end of this list
     *
     * @param[in] class The #class member is given as an argument
     * @param[in] objects Object to be appended to this list
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *        int num = 20;
     *        List* list = some impelemnting class;
     *        list->add(list->class, &num);
     * @endcode
     */
    int (*add)(void* class, void* object);

    /**
     * @brief Inserts the specified object at the specified position in this list
     *
     * @details Shifts the element currently at that position (if any) and any subsequent elements to the right
     * 
     * @param[in] class The #class member is given as an argument
     * @param[in] index Index at which the specified element is to be inserted
     * @param[in] objects Object to be inserted
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *        int num = 20;
     *        List* list = some impelemnting class;
     *        list->addIndex(list->class, 5, &num);
     * @endcode
     */
    int (*addIndex)(void* class, size_t index, void* object);

    /**
     * @brief Removes all objects from the list
     *
     * @param[in] class The #class member is given as an argument
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     *  @code        
     *         List* list = some impelemnting class;
     *         list->clear(list->class);
     * @endcode
     */
    int (*clear)(void* class);

    /**
     * @brief Removes the object at the specified position in this list.
     *          
     * @details Shifts any subsequent objects to the left
     * 
     * @param[in] class  The #class member is given as an argument
     * @param[in] index The index of the object to be removed
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *         List* list = some impelemnting class;
     *         list->remove(list->class, 6);
     * @endcode
     */
    int (*remove)(void* class, size_t index);
    
    /**
     * @brief Returns the object at the specified position in this list
     *
     * @param[in] class The #class member is given as an argument
     * @param[in] index Index of the object to return
     * @param[out] object Object to be returned
     *
     * @retval  0  Successful
     * @retval  1  Fail
     * 
     * @code        
     *          int num = 0;
     *          List* list = some impelemnting class;
     *          list->get(list->class, 5, &num)
     * @endcode
     */
    int (*get)(void* class, size_t index, void* object);

    /**
     * @brief Replaces the element at the specified position in this list with the specified element
     *
     * @param[in] class The #class member is given as an argument
     * @param[in] index Index of the element to replace
     * @param[out] object Object to be stored at the specified position
     *
     * @retval  0  Successful
     * @retval  1  Fail
     * 
     * @code        
     *          int num = 0;
     *          List* list = some impelemnting class;
     *          list->set(list->class, 5, &num)
     * @endcode
     */
    int (*set)(void* class, size_t index, void* object);

    /**
     * @brief Returns the number of objects in this list
     *
     * @param[in] class The #class member is given as an argument
     * @param[out] size Number of objects in this list
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *         size_t size;
     *         List* list = some impelemnting class;
     *         list->getSize(list->class, &size)
     * @endcode
     */
    int (*getSize)(void* class, size_t* size);

    /**
     * @brief Returns true if this list contains the specified object
     * 
     * @param[in] Class The #class member is given as an argument
     * @param[in] Object element whose presence in this list is to be tested
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *         int num = 99;
     *         List* list = some impelemnting class;
     *         list->contains(list->class, &num)
     * @endcode
     */
    int (*contains)(void* class, void* object);

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