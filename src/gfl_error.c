//
// Created by akaan on 18.07.2023.
//

#include <gfl_error.h>
#include <stdio.h>
#include <stdlib.h>

#define gflError_print_m(msg) \
fprintf(stderr, "Error in function %s: "#msg"\n", func)

noreturn void gflError_handle(gflError_t error, const char *func)
{
    switch (error) {
        case gflError_outOfMemory_c:
            gflError_print_m("Out Of Memory");
            exit(EXIT_FAILURE);
        case gflError_nullPointer_c:
            gflError_print_m("Null Pointer");
            exit(EXIT_FAILURE);
        case gflError_undefinedType_c:
            gflError_print_m("Undefined Type");
            exit(EXIT_FAILURE);
        case gflError_invalidSize_c:
            gflError_print_m("Invalid Size");
            exit(EXIT_FAILURE);
        case gflError_incompatibleTypes_c:
            gflError_print_m("Incompatible Types");
            exit(EXIT_FAILURE);
        case gflError_indexOutOfBounds_c:
            gflError_print_m("Index Out Of Bounds");
            exit(EXIT_FAILURE);
        default:
            gflError_print_m("NoError");
            exit(EXIT_FAILURE);
    }
}