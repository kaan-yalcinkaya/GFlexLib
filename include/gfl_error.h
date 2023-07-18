//
// Created by akaan on 18.07.2023.
//

#ifndef GFL_GFL_ERROR_H
#define GFL_GFL_ERROR_H

#include <stdnoreturn.h>

#define gflError_throw_m(error) \
gflError_handle((error), __func__)

typedef enum gflError_e{
    gflError_outOfMemory_c,
    gflError_nullPointer_c,
    gflError_undefinedType_c,
    gflError_invalidSize_c,
    gflError_incompatibleTypes_c
}gflError_t;

noreturn void gflError_handle(gflError_t error, const char *func);

#endif //GFL_GFL_ERROR_H
