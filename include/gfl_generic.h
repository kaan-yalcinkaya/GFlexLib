//
// Created by kaan-yalcinkaya on 18.07.2023.
//


/**
 * @file gfl_generic.h
 *
 * @brief This file contains declarations and functions related to generic data handling.
 */

#ifndef GFL_GFL_GENERIC_H
#define GFL_GFL_GENERIC_H

#include <stdint.h>

/**
 * @brief Macro to determine the type of a given value.
 *
 * This macro determines the type of the given value and maps it to one of the enum constants
 * from gflGenericType_t.
 *
 * @param c The value for which the type needs to be determined.
 * @return The corresponding gflGenericType_t enum value.
 */
#define gflGeneric_typeOf_m(c)               \
    _Generic((c),                            \
        int8_t: gflGeneric_number_c,         \
        int16_t: gflGeneric_number_c,        \
        int32_t: gflGeneric_number_c,        \
        int64_t: gflGeneric_number_c,        \
        uint8_t: gflGeneric_unsignedNumber_c,     \
        uint16_t: gflGeneric_unsignedNumber_c,    \
        uint32_t: gflGeneric_unsignedNumber_c,    \
        uint64_t: gflGeneric_unsignedNumber_c,    \
        float: gflGeneric_realNumber_c,      \
        double: gflGeneric_realNumber_c,     \
        long double: gflGeneric_undefined_c, \
        char *: gflGeneric_text_c,           \
        default: gflGeneric_undefined_c)

/**
 * @brief Macro to initialize a gflGeneric_t object for a given value.
 *
 * This macro creates and initializes a gflGeneric_t object for a given value with its type and size.
 *
 * @param c The value for which the gflGeneric_t object needs to be initialized.
 * @return A pointer to the initialized gflGeneric_t object.
 */
#define gflGeneric_initialize_m(c) \
    gflGeneric_initialize(&((typeof(c)){(c)}), gflGeneric_typeOf_m((c)), sizeof((c)))

/**
 * @brief Macro to print the given value.
 *
 * This macro initialize a new generic object for the given value and print the value.
 * The temporary object created after printing is freed.
 *
 * @param c The value for which the gflGeneric_t object needs to be printed.
 */
#define gflGeneric_println_m(c) \
    gflGeneric_println(gflGeneric_initialize_m((c)))

/**
 * @brief Macro to compare two values.
 *
 * This macro initialize new generic objects to compares two values and returns the result of the comparison.
 * The temporary objects created afted comparison is freed.
 *
 * @param c1 The first value for comparison.
 * @param c2 The second value for comparison.
 * @return An integer indicating the result of the comparison:
 *         - 0 if the values are equal.
 *         - A negative value if the first value is less than the second.
 *         - A positive value if the first value is greater than the second.
 */
#define gflGeneric_compare_m(c1, c2) \
    gflGeneric_ccompare(gflGeneric_initialize_m((c1)), gflGeneric_initialize_m((c2)))


/**
 * @def gflGeneric_assign_m(pgeneric, c)
 *
 * @brief Macro to assign a value to a gflGeneric_t object.
 *
 * This macro assigns a value to a gflGeneric_t object using the gflGeneric_assign function. The macro
 * takes care of determining the type and size of the value automatically.
 *
 * @param pgeneric Pointer to the gflGeneric_t object to which the value will be assigned.
 * @param c The value that will be assigned to the gflGeneric_t object.
 */
#define gflGeneric_assign_m(pgeneric, c) \
    gflGeneric_assign((pgeneric), &((typeof(c)){(c)}), gflGeneric_typeOf_m((c)), sizeof((c)))

/**
 * @brief Enum defining the different types of generic data.
 */
typedef enum gflGenericType_e
{
    gflGeneric_number_c = 1,    /**< Integer data type. */
    gflGeneric_unsignedNumber_c,/**< Unsigned integer data type */
    gflGeneric_realNumber_c,    /**< Floating-point data type. */
    gflGeneric_text_c,          /**< Text (char*) data type. */
    gflGeneric_undefined_c      /**< Undefined data type. */
} gflGenericType_t;

/**
 * @brief Structure representing a generic data object.
 */
struct gflGeneric_s;

/**
 * @brief Typedef for the gflGeneric_s structure.
 */
typedef struct gflGeneric_s gflGeneric_t;

/**
 * @brief Typedef for a pointer to the gflGeneric_s structure.
 */
typedef struct gflGeneric_s *gflGeneric_ptr;

/**
 * @brief Initialize a gflGeneric_t object.
 *
 * This function creates and initializes a gflGeneric_t object for a given data object,
 * its type, and size.
 *
 * @param pObject Pointer to the data object.
 * @param type The type of the data object (gflGenericType_t).
 * @param sObject The size of the data object.
 * @return A pointer to the initialized gflGeneric_t object.
 */
extern gflGeneric_ptr gflGeneric_initialize(void *pObject, enum gflGenericType_e type, uintmax_t sObject);

/**
 * @brief Destroy a gflGeneric_t object.
 *
 * This function destroys a gflGeneric_t object and frees any allocated memory.
 *
 * @param ppGeneric Pointer to a pointer to the gflGeneric_t object.
 */
extern void gflGeneric_destroy(gflGeneric_ptr *ppGeneric);

/**
 * @brief Compare two gflGeneric_t objects.
 *
 * This function compares two gflGeneric_t objects and returns the result of the comparison.
 *
 * @param pg1 Pointer to the first gflGeneric_t object for comparison.
 * @param pg2 Pointer to the second gflGeneric_t object for comparison.
 * @return An integer indicating the result of the comparison:
 *         - 0 if the objects are equal.
 *         - A negative value if the first object is less than the second.
 *         - A positive value if the first object is greater than the second.
 */
extern int8_t gflGeneric_compare(gflGeneric_ptr pg1, gflGeneric_ptr pg2);

/**
 * @brief Compare two gflGeneric_t objects and destroy them.
 *
 * This function compares two gflGeneric_t objects and returns the result of the comparison.
 *
 * @param pg1 Pointer to the first gflGeneric_t object for comparison.
 * @param pg2 Pointer to the second gflGeneric_t object for comparison.
 * @return An integer indicating the result of the comparison:
 *         - 0 if the objects are equal.
 *         - A negative value if the first object is less than the second.
 *         - A positive value if the first object is greater than the second.
 */
extern int8_t gflGeneric_ccompare(gflGeneric_ptr pg1, gflGeneric_ptr pg2);

/**
 * @brief Calculate the hash code for a gflGeneric_t object.
 *
 * This function calculates the hash code for a gflGeneric_t object.
 *
 * @param pGeneric Pointer to the gflGeneric_t object.
 * @return The hash code for the gflGeneric_t object.
 */
extern uintmax_t gflGeneric_hashCode(gflGeneric_ptr pGeneric);

/**
 * @brief Get the type of a gflGeneric_t object.
 *
 * This function returns the type of a gflGeneric_t object.
 *
 * @param pGeneric Pointer to the gflGeneric_t object.
 * @return The type of the gflGeneric_t object (gflGenericType_t).
 */
extern enum gflGenericType_e gflGeneric_typeOf(gflGeneric_ptr pGeneric);

/**
 * @brief Display the content of a gflGeneric_t object.
 *
 * This function displays the content of a gflGeneric_t object.
 *
 * @param pGeneric Pointer to the gflGeneric_t object.
 */
extern void gflGeneric_display(gflGeneric_ptr pGeneric);

/**
 * @brief Print the content of a gflGeneric_t object to the standard output and destroy the object.
 *
 * This function prints the content of a gflGeneric_t object to the standard output and destroy the object.
 *
 * @param pGeneric Pointer to the gflGeneric_t object.
 */
extern void gflGeneric_println(gflGeneric_ptr pGeneric);

/**
 * @brief Read a gflGeneric_t object from the user.
 *
 * This function reads a gflGeneric_t object of the specified type from the user.
 *
 * @param type The type of the gflGeneric_t object to read (gflGenericType_t).
 * @return A pointer to the read gflGeneric_t object.
 */
extern gflGeneric_ptr gflGeneric_read(gflGenericType_t type);

/**
 * @brief Assign a value to a gflGeneric_t object.
 *
 * This function assigns a value to a gflGeneric_t object. The value is provided as a void pointer,
 * and the function also requires the type and size information of the value. The function takes care
 * of updating the gflGeneric_t object with the new value and its type information. 
 *
 * @param pGeneric Pointer to the gflGeneric_t object to which the value will be assigned.
 * @param pObject Pointer to the value that will be assigned to the gflGeneric_t object.
 * @param type The type of the value being assigned (gflGenericType_t).
 * @param sObject The size of the value being assigned.
 * @return A pointer to the updated gflGeneric_t object after the assignment.
 */
extern gflGeneric_ptr 
gflGeneric_assign(gflGeneric_ptr pGeneric, void *pObject, gflGenericType_t type, uintmax_t sObject);

/**
 * @brief Set a pointer to null in the gflGeneric_s struct.
 *
 * This function sets the pointer in the gflGeneric_s struct to null.
 *
 * @param pGeneric Pointer to the gflGeneric_s struct.
 * @return void* A pointer to null.
 *
 * @note The function does not check if pGeneric is a valid pointer. Ensure pGeneric is valid before calling this function.
 */
extern void* gflGeneric_null(gflGeneric_ptr pGeneric);

#endif // GFL_GFL_GENERIC_H
