//
// Created by akaan on 18.07.2023.
//

#ifndef GFL_GFL_GENERIC_H
#define GFL_GFL_GENERIC_H

#include <stdint.h>

#define gflGeneric_typeOf_m(c) \
    _Generic((c),              \
    int8_t: gflGeneric_number_c,                 \
    int16_t: gflGeneric_number_c,                \
    int32_t: gflGeneric_number_c,                \
    int64_t: gflGeneric_number_c,                \
    uint8_t: gflGeneric_undefined_c,                \
    uint16_t: gflGeneric_undefined_c,               \
    uint32_t: gflGeneric_undefined_c,               \
    uint64_t: gflGeneric_undefined_c,               \
    float: gflGeneric_realNumber_c,                  \
    double: gflGeneric_realNumber_c,                  \
    long double: gflGeneric_undefined_c,            \
    char*: gflGeneric_text_c,                  \
    default: gflGeneric_undefined_c\
    )

#define gflGeneric_initialize_m(c) \
gflGeneric_initialize(&((typeof(c)){(c)}), gflGeneric_typeOf_m((c)), sizeof((c)))

#define gflGeneric_println_m(c) \
gflGeneric_println(gflGeneric_initialize_m((c)))

#define gflGeneric_compare_m(c1, c2) \
gflGeneric_ccompare(gflGeneric_initialize_m((c1)), gflGeneric_initialize_m((c2)))

typedef enum gflGenericType_e{
    gflGeneric_number_c = 1,
    gflGeneric_realNumber_c,
    gflGeneric_text_c,
    gflGeneric_undefined_c
}gflGenericType_t;

struct gflGeneric_s;

typedef struct gflGeneric_s gflGeneric_t;
typedef struct gflGeneric_s* gflGeneric_ptr;

extern gflGeneric_ptr gflGeneric_initialize(void *pObject, enum gflGenericType_e type, uintmax_t sObject);
extern void gflGeneric_destroy(gflGeneric_ptr *ppGeneric);
extern int8_t gflGeneric_compare(gflGeneric_ptr pg1, gflGeneric_ptr pg2);
extern int8_t gflGeneric_ccompare(gflGeneric_ptr pg1, gflGeneric_ptr pg2);
extern uintmax_t gflGeneric_hashCode(gflGeneric_ptr pGeneric);
extern enum gflGenericType_e gflGeneric_typeOf(gflGeneric_ptr pGeneric);
extern void gflGeneric_display(gflGeneric_ptr pGeneric);
extern void gflGeneric_println(gflGeneric_ptr pGeneric);
extern gflGeneric_ptr gflGeneric_read(gflGenericType_t type);

#endif //GFL_GFL_GENERIC_H
