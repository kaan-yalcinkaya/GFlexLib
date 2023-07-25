//
// Created by akaan on 25.07.2023.
//

#ifndef GFL_GFL_LIST_H
#define GFL_GFL_LIST_H

#include <gfl_generic.h>

#define gflList_pushBack_m(pList, data) \
    gflList_pushBack((pList), gflGeneric_initialize_m((data)))

#define gflList_pushFront_m(pList, data) \
    gflList_pushFront((pList), gflGeneric_initialize_m((data)))

#define gflList_insert_m(pList, index, data) \
    gflList_insert((pList), (index), gflGeneric_initialize_m((data)))

#define gflList_remove_m(pList, data) \
    gflList_remove((pList), gflGeneric_initialize_m((data)))

#define gflList_search_m(pList, data) \
    gflList_search((pList), gflGeneric_initialize_m((data)))

typedef struct gflList_s* gflList_ptr;

gflList_ptr gflList_initialize();
gflList_ptr gflList_initList(gflList_ptr pList);

void gflList_destroy(gflList_ptr *ppList);

void gflList_pushBack(gflList_ptr pList, gflGeneric_ptr data);
void gflList_pushFront(gflList_ptr pList, gflGeneric_ptr data);
void gflList_insert(gflList_ptr pList, uintmax_t index, gflGeneric_ptr data);

void gflList_popBack(gflList_ptr pList);
void gflList_popFront(gflList_ptr pList);
void gflList_delete(gflList_ptr pList, uintmax_t index);
void gflList_remove(gflList_ptr pList, gflGeneric_ptr data);

gflGeneric_ptr gflList_get(gflList_ptr pList, uintmax_t index);
bool gflList_search(gflList_ptr pList, gflGeneric_ptr data);
uintmax_t gflList_size(gflList_ptr pList);
void gflList_print(gflList_ptr pList);

#endif //GFL_GFL_LIST_H
