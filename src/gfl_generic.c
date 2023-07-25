//
// Created by kaan-yalcinkaya on 18.07.2023.
//



#include <gfl_generic.h>
#include <gfl_memalloc.h>
#include <gfl_error.h>
#include <gfl_utils.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

__attribute__((constructor)) static void gflRunTimeCheck()
{
    if(sizeof(uintmax_t) != sizeof(double))
        fprintf(stderr, "Error: size of uintmax_t and sizeof double not equal\n"), exit(EXIT_FAILURE);
}

#define gflGeneric_cast_m(obj, t1, t2) (t1)(*(t2*)(obj))

struct gflGeneric_s{
    gflGenericType_t type;
    union {
        uintmax_t unsignedNumber;
        intmax_t number;
        double realNumber;
        bool boolean;
        struct {
            uintmax_t length;
            char set[];
        } text;
    };
};

gflGeneric_ptr gflGeneric_initialize(void *pObject, enum gflGenericType_e type, uintmax_t sObject)
{
    if(!pObject) gflError_throw_m(gflError_nullPointer_c);
    if(sObject < 1) gflError_throw_m(gflError_invalidSize_c);
    gflGeneric_ptr pg = NULL;
    switch (type) {
        case gflGeneric_boolean_c:
            pg = gflAlloc_malloc_m(gflGeneric_t, 1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            pg->boolean = *(bool*)pObject;
            break;
        case gflGeneric_number_c:
            pg = gflAlloc_malloc_m(gflGeneric_t, 1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            if(sObject == sizeof(int8_t))
                pg->number = gflGeneric_cast_m(pObject, intmax_t, int8_t);
            else if(sObject == sizeof(int16_t))
                pg->number = gflGeneric_cast_m(pObject, intmax_t, int16_t);
            else if(sObject == sizeof(int32_t))
                pg->number = gflGeneric_cast_m(pObject, intmax_t, int32_t);
            else if(sObject == sizeof(int64_t))
                pg->number = *(intmax_t*)pObject;
            else
                gflError_throw_m(gflError_invalidSize_c);
            break;
        case gflGeneric_realNumber_c:
            pg = gflAlloc_malloc_m(gflGeneric_t ,1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            if(sObject == sizeof(float))
                pg->realNumber = gflGeneric_cast_m(pObject, double, float);
            else if(sObject == sizeof(double))
                pg->realNumber = *(double*)pObject;
            else
                gflError_throw_m(gflError_invalidSize_c);
            break;
        case gflGeneric_text_c:
            pg = (gflGeneric_ptr) malloc(sizeof(gflGeneric_t) + sObject);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            pg->text.length = sObject - 1;
            memcpy(pg->text.set, pObject, sObject);
            break;
        case gflGeneric_unsignedNumber_c:
            pg = gflAlloc_calloc_m(gflGeneric_t, 1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            if(sObject == sizeof(uint8_t))
                pg->unsignedNumber = gflGeneric_cast_m(pObject, uintmax_t, uint8_t);
            else if(sObject == sizeof(uint16_t))
                pg->unsignedNumber = gflGeneric_cast_m(pObject, uintmax_t, uint16_t);
            else if(sObject == sizeof(uint32_t))
                pg->unsignedNumber = gflGeneric_cast_m(pObject, uintmax_t, uint32_t);
            else if(sObject == sizeof(uint64_t))
                pg->unsignedNumber = *(uintmax_t*)pObject;
            else gflError_throw_m(gflError_invalidSize_c);
            break;
        case gflGeneric_undefined_c:
        default:
            gflError_throw_m(gflError_undefinedType_c);
    }
    return pg;
}

void gflGeneric_destroy(gflGeneric_ptr *ppGeneric)
{
    if(!ppGeneric || !*ppGeneric) gflError_throw_m(gflError_nullPointer_c);
    free(*ppGeneric);
    *ppGeneric = NULL;
}

int8_t gflGeneric_compare(gflGeneric_ptr pg1, gflGeneric_ptr pg2)
{
    if(!pg1 || !pg2) gflError_throw_m(gflError_nullPointer_c);
    if(pg1->type != pg2->type) gflError_throw_m(gflError_incompatibleTypes_c);
    switch (pg1->type) {
        case gflGeneric_boolean_c:
            if(pg1->boolean == pg2->boolean) return 0;
            return (pg1->boolean > pg2->boolean) ? 1 : -1;
        case gflGeneric_number_c:
            if(pg1->number == pg2->number) return 0;
            return (pg1->number > pg2->number) ? 1 : -1;
        case gflGeneric_unsignedNumber_c:
            if(pg1->unsignedNumber == pg2->unsignedNumber) return 0;
            return (pg1->unsignedNumber > pg2->unsignedNumber) ? 1 : -1;
        case gflGeneric_realNumber_c:
            if(pg1->realNumber == pg2->realNumber) return 0;
            return (pg1->realNumber > pg2->realNumber) ? 1 : -1;
        case gflGeneric_text_c:
            return (int8_t)strcmp(pg1->text.set, pg2->text.set);
        case gflGeneric_undefined_c:
        default:
            gflError_throw_m(gflError_undefinedType_c);
    }
}

static inline uintmax_t gflGeneric_hash(uintmax_t key)
{
#if defined(gflGeneric_env_m)
    #if gflGeneric_env_m == 64
        key = (key ^ (key >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
        key = (key ^ (key >> 27)) * UINT64_C(0x94d049bb133111eb);
        key = key ^ (key >> 31);
    #elif gflGeneric_env_m == 32
        key = ((key >> 16) ^ key) * 0x119de1f3;
        key = ((key >> 16) ^ key) * 0x119de1f3;
        key = (x >> 16) ^ key;
    #endif
#else 
    #error "Error"
#endif
    return key;
}

uintmax_t gflGeneric_hashCode(gflGeneric_ptr pGeneric)
{
    if(!pGeneric) gflError_throw_m(gflError_nullPointer_c);
    switch (pGeneric->type) {
        case gflGeneric_boolean_c:
        case gflGeneric_number_c:
        case gflGeneric_unsignedNumber_c:
        case gflGeneric_realNumber_c:
            return gflGeneric_hash(pGeneric->unsignedNumber);
        case gflGeneric_text_c: {
            uintmax_t key = 0;
            for (uintmax_t i = 0; i < pGeneric->text.length; ++i) {
                key += pGeneric->text.set[i];
            }
            return gflGeneric_hash(key);
        }
        case gflGeneric_undefined_c:
        default:
            gflError_throw_m(gflError_undefinedType_c);
    }
}

enum gflGenericType_e gflGeneric_typeOf(gflGeneric_ptr pGeneric)
{
    if(!pGeneric) gflError_throw_m(gflError_nullPointer_c);
    return pGeneric->type;
}

void gflGeneric_display(gflGeneric_ptr pGeneric)
{
    if(!pGeneric) gflError_throw_m(gflError_nullPointer_c);
    switch (pGeneric->type) {
        case gflGeneric_boolean_c:
            if(pGeneric->boolean)
                fprintf(stdout, "true\n");
            else
                fprintf(stdout, "false\n");
            break;
        case gflGeneric_number_c:
            fprintf(stdout, "%"PRIiMAX"\n", pGeneric->number);
            break;
        case gflGeneric_unsignedNumber_c:
            fprintf(stdout, "%"PRIuMAX"\n", pGeneric->unsignedNumber);
            break;
        case gflGeneric_realNumber_c:
            fprintf(stdout, "%lf\n", pGeneric->realNumber);
            break;
        case gflGeneric_text_c:
            fprintf(stdout, "%s\n", pGeneric->text.set);
            break;
        case gflGeneric_undefined_c:
            break;
        default:
            gflError_throw_m(gflError_undefinedType_c);
    }
}

gflGeneric_ptr gflGeneric_read(gflGenericType_t type)
{
    gflGeneric_ptr pg = NULL;
    switch (type) {
        case gflGeneric_boolean_c:
        case gflGeneric_number_c:
            pg = gflAlloc_malloc_m(gflGeneric_t, 1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            scanf("%"PRIiMAX, &pg->number);//
            return pg;
        case gflGeneric_unsignedNumber_c:
            pg = gflAlloc_malloc_m(gflGeneric_t, 1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            scanf("%"PRIuMAX, &pg->unsignedNumber);
            return pg;
        case gflGeneric_realNumber_c:
            pg = gflAlloc_malloc_m(gflGeneric_t, 1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            scanf("%lf", &pg->realNumber);
            return pg;
        case gflGeneric_text_c: {
            char str[1024];
            fgets(str, sizeof str, stdin);
            uintmax_t len = strlen(str);
            pg = malloc(sizeof(gflGeneric_t) + len+1);
            if(!pg) gflError_throw_m(gflError_outOfMemory_c);
            pg->type = type;
            strncpy(pg->text.set, str, len+1);
            pg->text.length = len;
            return pg;
        }
        case gflGeneric_undefined_c:
        default:
            gflError_throw_m(gflError_undefinedType_c);
    }
}

void gflGeneric_println(gflGeneric_ptr pGeneric)
{
    gflGeneric_display(pGeneric);
    gflGeneric_destroy(&pGeneric);
}

int8_t gflGeneric_ccompare(gflGeneric_ptr pg1, gflGeneric_ptr pg2)
{
    int8_t ret = gflGeneric_compare(pg1, pg2);
    gflGeneric_destroy(&pg1), gflGeneric_destroy(&pg2);
    return ret;
}

gflGeneric_ptr
gflGeneric_assign(gflGeneric_ptr pGeneric, void *pObject, gflGenericType_t type, uintmax_t sObject)
{
    if(pGeneric) gflGeneric_destroy(&pGeneric);
    return gflGeneric_initialize(pObject, type, sObject);
}

void* gflGeneric_null(gflGeneric_ptr pGeneric)
{
    if(pGeneric) gflGeneric_destroy(&pGeneric);
    return NULL;
}
