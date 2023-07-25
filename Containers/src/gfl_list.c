//
// Created by akaan on 25.07.2023.
//

#include <setjmp.h>
#include <gfl_list.h>
#include <gfl_error.h>
#include <gfl_memalloc.h>

jmp_buf buf_ins;

typedef struct gflList_Node_s gflList_node_t;
typedef struct gflList_Node_s* gflList_node_ptr;
typedef struct gflList_s gflList_t;

struct gflList_Node_s{
    gflGeneric_ptr data;
    gflList_node_ptr prev, next;
};

struct gflList_s{
    gflList_node_ptr head, tail;
    uintmax_t size;
};

static inline gflList_node_ptr gflList_node_initialize(gflGeneric_ptr data)
{
    gflList_node_ptr pNode = gflAlloc_malloc_m(gflList_node_t, 1);
    if(!pNode) longjmp(buf_ins, gflError_outOfMemory_c);
    pNode->data = data;
    pNode->prev = pNode->next = NULL;
    return pNode;
}

static inline void gflList_node_destroy(gflList_node_ptr *ppNode)
{
    gflGeneric_destroy(&(*ppNode)->data);
    free(*ppNode);
    *ppNode = NULL;
}

gflList_ptr gflList_initialize()
{
    gflList_ptr pList = gflAlloc_malloc_m(gflList_t, 1);
    if(!pList) gflError_throw_m(gflError_outOfMemory_c);
    pList->size = UINTMAX_C(0);
    pList->head = pList->tail = NULL;
    return pList;
}

gflList_ptr gflList_initList(gflList_ptr pList)
{
    gflList_ptr rpList = gflList_initialize();
    gflList_node_ptr iter = pList->head;
    while (iter){
        gflList_pushBack(rpList, iter->data);
        iter = iter->next;
    }
    return rpList;
}

void gflList_destroy(gflList_ptr *ppList)
{
    if(!ppList || !*ppList) gflError_throw_m(gflError_nullPointer_c);
    gflList_node_ptr temp = NULL;
    while ((*ppList)->head){
        temp = (*ppList)->head;
        (*ppList)->head = (*ppList)->head->next;
        gflList_node_destroy(&temp);
    }
    free(*ppList);
    *ppList = NULL;
}

void gflList_pushBack(gflList_ptr pList, gflGeneric_ptr data)
{
    if(!pList || !data) gflError_throw_m(gflError_nullPointer_c);
    gflError_t ret = setjmp(buf_ins);
    if(!pList->head){
        if(!ret) {
            pList->head = gflList_node_initialize(data);
            pList->tail = pList->head;
            pList->size++;
            return;
        }
        else
            gflError_throw_m(gflError_outOfMemory_c);
    }
    if(!ret){
        pList->tail->next = gflList_node_initialize(data);
        pList->tail->next->prev = pList->tail;
        pList->tail = pList->tail->next;
        pList->size++;
    }
    else
        gflError_throw_m(gflError_outOfMemory_c);
}

void gflList_pushFront(gflList_ptr pList, gflGeneric_ptr data)
{
    if(!pList || !data) gflError_throw_m(gflError_nullPointer_c);
    gflError_t ret = setjmp(buf_ins);
    if(!pList->head){
        if(!ret) {
            pList->head = gflList_node_initialize(data);
            pList->tail = pList->head;
            pList->size++;
            return;
        }
        else
            gflError_throw_m(gflError_outOfMemory_c);
    }
    if(!ret){
        pList->head->prev = gflList_node_initialize(data);
        pList->head->prev->next = pList->head;
        pList->head = pList->head->prev;
        pList->size++;
    }
    else
        gflError_throw_m(gflError_outOfMemory_c);
}

void gflList_insert(gflList_ptr pList, uintmax_t index, gflGeneric_ptr data)
{
    if(!pList || !data) gflError_throw_m(gflError_nullPointer_c);
    if(index > pList->size) gflError_throw_m(gflError_indexOutOfBounds_c);
    if(index == 0) gflList_pushFront(pList, data);
    else if(index == pList->size) gflList_pushBack(pList, data);
    else{
        uintmax_t i = UINTMAX_C(0);
        gflList_node_ptr iter = pList->head;
        while (iter){
            if(index == i){
                gflError_t ret = setjmp(buf_ins);
                if(ret) gflError_throw_m(ret);
                gflList_node_ptr pNode = gflList_node_initialize(data);
                pNode->next = iter;
                pNode->prev = iter->prev;
                iter->prev->next = pNode;
                iter->prev = pNode;
                pList->size++;
                return;
            }
            iter = iter->next, i++;
        }
    }
}

void gflList_popBack(gflList_ptr pList)
{
    if(!pList) gflError_throw_m(gflError_nullPointer_c);
    if(!pList->head) gflError_throw_m(gflError_indexOutOfBounds_c);
    if(pList->tail->prev){
        gflList_node_ptr temp = pList->tail;
        pList->tail = pList->tail->prev;
        pList->tail->next = NULL;
        gflList_node_destroy(&temp);
        pList->size--;
        return;
    }
    gflList_node_destroy(&pList->tail);
    pList->head = NULL;
    pList->size = 0;
}

void gflList_popFront(gflList_ptr pList)
{
    if(!pList) gflError_throw_m(gflError_nullPointer_c);
    if(!pList->head) gflError_throw_m(gflError_indexOutOfBounds_c);
    if(pList->head->next){
        gflList_node_ptr temp = pList->head;
        pList->head = pList->head->next;
        pList->head->prev = NULL;
        gflList_node_destroy(&temp);
        pList->size--;
        return;
    }
    gflList_node_destroy(&pList->head);
    pList->tail = NULL;
    pList->size = 0;
}

void gflList_delete(gflList_ptr pList, uintmax_t index)
{
    if(!pList) gflError_throw_m(gflError_nullPointer_c);
    if(!pList->head || index >= pList->size)
        gflError_throw_m(gflError_indexOutOfBounds_c);
    if(index == 0) gflList_popFront(pList);
    else if(index == pList->size - 1) gflList_popBack(pList);
    else{
        uintmax_t i = UINTMAX_C(0);
        gflList_node_ptr iter = pList->head;
        while (iter){
            if(index == i){
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                gflList_node_destroy(&iter);
                pList->size--;
                return;
            }
            iter = iter->next, i++;
        }
    }
}

void gflList_remove(gflList_ptr pList, gflGeneric_ptr data)
{
    if(!pList || !data) gflError_throw_m(gflError_nullPointer_c);
    if(!pList->head) gflError_throw_m(gflError_indexOutOfBounds_c);

    gflList_node_ptr iter = pList->head;
    while (iter){
        if(gflGeneric_typeOf(data) != gflGeneric_typeOf(iter->data)) goto diff;
        if(!gflGeneric_compare(data, iter->data))
        {
            if(iter == pList->head) gflList_popFront(pList);
            else if(iter == pList->tail) gflList_popBack(pList);
            else{
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                gflList_node_destroy(&iter);
                pList->size--;
            }
            gflGeneric_destroy(&data);
            return;
        }
        diff:
            iter = iter->next;
    }
    gflError_throw_m(gflError_indexOutOfBounds_c);
}

gflGeneric_ptr gflList_get(gflList_ptr pList, uintmax_t index)
{
    if(!pList) gflError_throw_m(gflError_nullPointer_c);
    if(pList->head || index >= pList->size) gflError_throw_m(gflError_indexOutOfBounds_c);

    uintmax_t i = UINTMAX_C(0);
    gflList_node_ptr iter = pList->head;
    while (iter){
        if(index == i) return iter->data;
        iter = iter->next, i++;
    }
}

bool gflList_search(gflList_ptr pList, gflGeneric_ptr data)
{
    if(!pList || !data) gflError_throw_m(gflError_nullPointer_c);
    if(!pList->head) gflError_throw_m(gflError_indexOutOfBounds_c);
    gflList_node_ptr iter = pList->head;
    while (iter){
        if(gflGeneric_typeOf(data) != gflGeneric_typeOf(iter->data)) goto diff;
        if(!gflGeneric_compare(data, iter->data)){
            gflGeneric_destroy(&data);
            return true;
        }
        diff:
            iter = iter->next;
    }
    gflGeneric_destroy(&data);
    return false;
}

uintmax_t gflList_size(gflList_ptr pList)
{
    if(!pList) gflError_throw_m(gflError_nullPointer_c);
    return pList->size;
}

void gflList_print(gflList_ptr pList)
{
    if(!pList) gflError_throw_m(gflError_nullPointer_c);
    gflList_node_ptr iter = pList->head;
    while (iter){
        gflGeneric_display(iter->data);
        iter = iter->next;
    }
}