/**
 * @file Queue.h
 * 
 * @brief Represents a FIFO collection of objects
 * 
 * @details 
 *        Created by Martin Chekurov
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/**
 * @brief Represents a FIFO collection of objects
 */ 
typedef struct {

    /**
     * @brief Inserts the specified element into this queue if it is possible to do so immediately without violating capacity restriction
     *
     * @param[in] class The #class member is given as an argument
     * @param[in] object The element to add
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *        int num = 20;
     *        Queue* queue = some impelemnting class;
     *        queue->offer(list->class, &num);
     * @endcode
     */
    int (*offer)(void* class, void* object);

    /**
     * @brief Retrieves, but does not remove, the head of this queue
     *
     * @param[in] class The #class member is given as an argument
     * @param[out] object The head of this queue
     *
     * @retval  0  Successful
     * @retval  1  Fail
     * 
     * @code        
     *          int num = 0;
     *          Queue* queue = some impelemnting class;
     *          queue->peek(list->class, &num)
     * @endcode
     */
    int (*peek)(void* class, void* object);

    /**
     * @brief Retrieves and removes the head of this queue
     *
     * @param[in] class The #class member is given as an argument
     * @param[out] object The head of this queue
     *
     * @retval  0  Successful
     * @retval  1  Fail
     * 
     * @code        
     *          int num = 0;
     *          Queue* queue = some impelemnting class;
     *          queue->poll(list->class, &num)
     * @endcode
     */
    int (*poll)(void* class, void* object);   

    /**
     * @brief Destroys the Queue
     * 
     * @param[in] Class The #class member is given as an argument
     *
     * @retval 0 Successful
     * @retval 1 Fail
     * 
     * @code        
     *         Queue* queue = some impelemnting class;
     *         queue->destroy(list->class)
     * @endcode
     */
    int (*destroy)(void* class);

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
    
}Queue;

#endif