//
// Created by kaan-yalcinkaya on 25.07.2023.
//

/**
 * @file gfl_list.h
 * @brief Header file for a generic linked list implementation.
 */

#ifndef GFL_GFL_LIST_H
#define GFL_GFL_LIST_H

#include <gfl_generic.h>

/**
 * @def gflList_pushBack_m(pList, data)
 * @brief Macro to push data to the back of the linked list.
 *
 * The macro wraps the gflList_pushBack function, automatically initializing the data
 * as a generic object using gflGeneric_initialize_m macro before pushing it to the back of the list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be added to the list.
 */
#define gflList_pushBack_m(pList, data) \
    gflList_pushBack((pList), gflGeneric_initialize_m((data)))

/**
 * @def gflList_pushFront_m(pList, data)
 * @brief Macro to push data to the front of the linked list.
 *
 * The macro wraps the gflList_pushFront function, automatically initializing the data
 * as a generic object using gflGeneric_initialize_m macro before pushing it to the front of the list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be added to the list.
 */
#define gflList_pushFront_m(pList, data) \
    gflList_pushFront((pList), gflGeneric_initialize_m((data)))

/**
 * @def gflList_insert_m(pList, index, data)
 * @brief Macro to insert data into the linked list at the specified index.
 *
 * The macro wraps the gflList_insert function, automatically initializing the data
 * as a generic object using gflGeneric_initialize_m macro before inserting it at the given index.
 *
 * @param pList Pointer to the linked list.
 * @param index Index where the data should be inserted.
 * @param data Data to be added to the list.
 */
#define gflList_insert_m(pList, index, data) \
    gflList_insert((pList), (index), gflGeneric_initialize_m((data)))

/**
 * @def gflList_remove_m(pList, data)
 * @brief Macro to remove data from the linked list.
 *
 * The macro wraps the gflList_remove function, automatically initializing the data
 * as a generic object using gflGeneric_initialize_m macro before removing it from the list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be removed from the list.
 */
#define gflList_remove_m(pList, data) \
    gflList_remove((pList), gflGeneric_initialize_m((data)))

/**
 * @def gflList_search_m(pList, data)
 * @brief Macro to search for data in the linked list.
 *
 * The macro wraps the gflList_search function, automatically initializing the data
 * as a generic object using gflGeneric_initialize_m macro before searching for it in the list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be searched for in the list.
 * @return true if the data is found, false otherwise.
 */
#define gflList_search_m(pList, data) \
    gflList_search((pList), gflGeneric_initialize_m((data)))

/**
 * @typedef gflList_ptr
 * @brief Pointer to the linked list.
 */
typedef struct gflList_s* gflList_ptr;

/**
 * @fn gflList_ptr gflList_initialize()
 * @brief Initialize a new empty linked list.
 *
 * @return Pointer to the newly created linked list.
 */
gflList_ptr gflList_initialize();

/**
 * @fn gflList_ptr gflList_initList(gflList_ptr pList)
 * @brief Initialize a linked list using an existing list.
 *
 * This function will initialize the given linked list and clear its contents, if any.
 *
 * @param pList Pointer to the linked list to be initialized.
 * @return Pointer to the initialized linked list.
 */
gflList_ptr gflList_initList(gflList_ptr pList);

/**
 * @fn void gflList_destroy(gflList_ptr *ppList)
 * @brief Destroy a linked list and free its memory.
 *
 * @param ppList Pointer to the pointer of the linked list to be destroyed.
 */
void gflList_destroy(gflList_ptr *ppList);

/**
 * @fn void gflList_pushBack(gflList_ptr pList, gflGeneric_ptr data)
 * @brief Push data to the back of the linked list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be added to the list.
 */
void gflList_pushBack(gflList_ptr pList, gflGeneric_ptr data);

/**
 * @fn void gflList_pushFront(gflList_ptr pList, gflGeneric_ptr data)
 * @brief Push data to the front of the linked list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be added to the list.
 */
void gflList_pushFront(gflList_ptr pList, gflGeneric_ptr data);

/**
 * @fn void gflList_insert(gflList_ptr pList, uintmax_t index, gflGeneric_ptr data)
 * @brief Insert data into the linked list at the specified index.
 *
 * @param pList Pointer to the linked list.
 * @param index Index where the data should be inserted.
 * @param data Data to be added to the list.
 */
void gflList_insert(gflList_ptr pList, uintmax_t index, gflGeneric_ptr data);

/**
 * @fn void gflList_popBack(gflList_ptr pList)
 * @brief Pop data from the back of the linked list.
 *
 * @param pList Pointer to the linked list.
 */
void gflList_popBack(gflList_ptr pList);

/**
 * @fn void gflList_popFront(gflList_ptr pList)
 * @brief Pop data from the front of the linked list.
 *
 * @param pList Pointer to the linked list.
 */
void gflList_popFront(gflList_ptr pList);

/**
 * @fn void gflList_delete(gflList_ptr pList, uintmax_t index)
 * @brief Delete data from the linked list at the specified index.
 *
 * @param pList Pointer to the linked list.
 * @param index Index of the data to be deleted.
 */
void gflList_delete(gflList_ptr pList, uintmax_t index);

/**
 * @fn void gflList_remove(gflList_ptr pList, gflGeneric_ptr data)
 * @brief Remove data from the linked list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be removed from the list.
 */
void gflList_remove(gflList_ptr pList, gflGeneric_ptr data);

/**
 * @fn gflGeneric_ptr gflList_get(gflList_ptr pList, uintmax_t index)
 * @brief Get data from the linked list at the specified index.
 *
 * @param pList Pointer to the linked list.
 * @param index Index of the data to be retrieved.
 * @return Pointer to the data at the specified index, or NULL if the index is out of bounds.
 */
gflGeneric_ptr gflList_get(gflList_ptr pList, uintmax_t index);

/**
 * @fn bool gflList_search(gflList_ptr pList, gflGeneric_ptr data)
 * @brief Search for data in the linked list.
 *
 * @param pList Pointer to the linked list.
 * @param data Data to be searched for in the list.
 * @return true if the data is found, false otherwise.
 */
bool gflList_search(gflList_ptr pList, gflGeneric_ptr data);

/**
 * @fn uintmax_t gflList_size(gflList_ptr pList)
 * @brief Get the size of the linked list.
 *
 * @param pList Pointer to the linked list.
 * @return The number of elements in the linked list.
 */
uintmax_t gflList_size(gflList_ptr pList);

/**
 * @fn void gflList_print(gflList_ptr pList)
 * @brief Print the contents of the linked list.
 *
 * @param pList Pointer to the linked list.
 */
void gflList_print(gflList_ptr pList);

#endif // GFL_GFL_LIST_H

