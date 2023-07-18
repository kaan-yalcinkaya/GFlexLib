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
            gflError_print_m("OutOfMemory");
            exit(EXIT_FAILURE);
        case gflError_nullPointer_c:
            gflError_print_m("NullPointer");
            exit(EXIT_FAILURE);
        case gflError_undefinedType_c:
            gflError_print_m("UndefinedType");
            exit(EXIT_FAILURE);
        case gflError_invalidSize_c:
            gflError_print_m("InvalidSize");
            exit(EXIT_FAILURE);
        case gflError_incompatibleTypes_c:
            gflError_print_m("IncompatibleTypes");
            exit(EXIT_FAILURE);
        default:
            gflError_print_m("NoError");
            exit(EXIT_FAILURE);
    }
}