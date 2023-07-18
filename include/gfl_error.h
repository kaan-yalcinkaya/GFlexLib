//
// Created by kaan-yalcinkaya on 18.07.2023.
//

/**
 * @file gfl_error.h
 *
 * @brief This file contains declarations and functions related to error handling.
 */

#ifndef GFL_GFL_ERROR_H
#define GFL_GFL_ERROR_H

#include <stdnoreturn.h>

/**
 * @brief Macro to throw an error and handle it.
 *
 * This macro throws an error and calls the gflError_handle function to handle it. The macro
 * also includes the name of the current function (__func__) where the error occurred.
 *
 * @param error The error code to be thrown (gflError_t).
 */
#define gflError_throw_m(error) \
gflError_handle((error), __func__)

/**
 * @brief Enum defining the different error codes.
 */
typedef enum gflError_e {
    gflError_outOfMemory_c,       /**< Error: Out of memory. */
    gflError_nullPointer_c,       /**< Error: Null pointer encountered. */
    gflError_undefinedType_c,     /**< Error: Undefined data type. */
    gflError_invalidSize_c,       /**< Error: Invalid size specified. */
    gflError_incompatibleTypes_c  /**< Error: Incompatible data types. */
} gflError_t;

/**
 * @brief Function to handle errors.
 *
 * This function handles errors and takes appropriate action based on the error code.
 * It is a noreturn function, meaning it does not return to the calling function.
 *
 * @param error The error code to be handled (gflError_t).
 * @param func The name of the function where the error occurred (automatically passed by the gflError_throw_m macro).
 */
noreturn void gflError_handle(gflError_t error, const char* func);

#endif // GFL_GFL_ERROR_H
