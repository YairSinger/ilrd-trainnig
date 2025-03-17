#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h> /*size_t*/

typedef struct hashtable hashtable_t;



/*
@Name: HashtableCreate
@Description: 
    Initializes and returns a new hash table with the given parameters. 
@Parameters: 
    - hash_func: A valid function that takes a unique key and returns an index. 
    - is_key_match: A valid function that takes two keys and returns 1 if they match, and 0 otherwise. 
    - num_of_buckets: The number of indexes or slots in the hash table. num_of_buckets must be > 0

@Return: 
    - Returns a pointer to the newly created hash table. 
    - Return NULL if allocation fail.

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(n), where n is equal to num_of_buckets.
 */
hashtable_t *HashtableCreate(size_t (*hash_func)(const void *key),
                              int (*is_key_match)(const void *lhs, const void *rhs),
                              size_t num_of_buckets);


/*
@Name: HashtableDestroy
@Description: 
    Frees all the memory allocated by the hash table.
    
@Parameters: 
    hashtable - A valid pointer to the hash table.
    
@Return: 
    Void.

@Time Complexity: 
    O(n), where n is the number of elements in the hash table.

@Space Complexity: 
    O(1).
 */
void HashtableDestroy(hashtable_t *hashtable);

/*
@Name: HashtableInsert
@Description: 
    Inserts a key-value pair into the hash table. 

@Parameters: 
    - hashtable: A valid pointer to the hash table.
    - key: A valid pointer to the key for insertion.
    - data: A pointer to the value/data associated with the key.

@Return: 
    - EXIT_SUCCESS (0): If the insertion is successful.
    - EXIT_FAILURE (-1): If the insertion fails.

@Time Complexity: 
    - Best and average case: O(1). This assumes a well-distributed dataset and 
      efficient hash function.
    - Worst case: O(n) where n is the number of elements in a specific bucket 
      due to collisions.

@Space Complexity: 
    O(1) for the insertion operation itself.
 */
int HashtableInsert(hashtable_t *hashtable, const void *key, void* data);

/*
@Name: HashtableRemove
@Description: 
    Removes a key-value pair from the hash table based on the provided key.

@Parameters: 
    hashtable: A valid pointer to the hash table.
    key: A valid pointer to the key that determines which key-value pair should be removed.

@Return: 
    void

@Time Complexity: 
    Best and average case: O(1) (assuming a good hash function and a well-distributed dataset).
    Worst case: O(n) where n is the number of elements in a specific bucket.

@Space Complexity: 
    O(1).
 */
void HashtableRemove(hashtable_t *hashtable, const void *key);

/*
@Name: HashtableFind
@Description: 
    Finds data by key in the hash table.
    
@Parameters: 
    hashtable - a pointer to the hash table.
    key - a pointer to the key.
    
@Return: 
    A pointer to the data if found, NULL otherwise.

@Time Complexity: 
    O(1) on average, O(n) in the worst case.

@Space Complexity: 
    O(1).
 */
void *HashtableFind(const hashtable_t *hashtable, const void *key);


/*
@Name: HashtableForEach
@Description: 
    Performs a given action on each element in the hash table.
    
@Parameters: 
    hashtable - A valid pointer to the hash table.
    action_func - A valid function pointer defining the action to perform on each element.
    action_param - A valid pointer to any additional parameters required by action_func.
    
@Return: 
        - 0 on success
        - non-zero value if any action fails.

@Time Complexity: 
    O(n), where n is the number of elements in the hash table.

@Space Complexity: 
    O(1).
 */
int HashtableForEach(hashtable_t *hashtable, int (*action_func)(void *data, void *param), void *action_param);

/*
@Name: HashtableIsEmpty
@Description: 
    Checks if the given hash table is empty.

@Parameters: 
    - hashtable: A valid pointer to the hash table to check.

@Return: 
    - 1: If the hash table is empty.
    - 0: Otherwise.

@Time Complexity: 
    O(1). Simply checks a property or count of the hash table.

@Space Complexity: 
    O(k). k = num_of_buckets.
 */             
int HashtableIsEmpty(const hashtable_t *hashtable);

/*
@Name: HashtableCountSize
@Description: 
    Returns the number of elements in the hash table.
    
@Parameters: 
    hashtable - A valid pointer to the hash table.
    
@Return: 
    The number of elements in the hash table.

@Time Complexity: 
    O(n).

@Space Complexity: 
    O(1).
 */
size_t HashtableCountSize(const hashtable_t *hashtable);

#endif /* __HASH_TABLE_H__ */
 
