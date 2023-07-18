# GFlexLib
GFlextLib is a library that provides a generic type for arithmetic types in c.

# Types
enum gflGenericType_e: It can take 4 values, these are:<br>
1. gflGeneric_number_c: int8_t, int16_t, int32_t, int64_t<br>
2. gflGeneric_realNumber_c: float, double<br>
3. gflGeneric_text_c: char*<br>
4. gflGeneric_undefined_c: unsigned integer types and pointer types.<br><br>
struct gflGeneric_s: Generic type that can hold all arithmetic types.

# Type Aliases
enum gflGenericType_e: gflGenericType_t<br>
struct gflGeneric_s: gflGeneric_t<br>
struct gflGeneric_s*: gflGeneric_ptr<br>

# Macros
gflGeneric_typeof_m: Finds the type of the given value. is number for all integer values, realNumber for all floating point values, and text for pointer to character types.<br>
gflGeneric_initialize_m: Assigns the given value to a variable of type gflGeneric_ptr.<br>
gflGeneric_println_m: Frees the given value from ram after print.<br>
gflGeneric_compare_m: Compares two given values ​​and frees them from memory.<br>

# Functions
```
/**
 * @brief Initializes a generic object.
 *
 * This function initializes a generic object with the given parameters.
 *
 * @param pObject Pointer to the object to be initialized.
 * @param type The type of the generic object.
 * @param sObject The size of the object.
 * @return A pointer to the initialized generic object.
 */
extern gflGeneric_ptr gflGeneric_initialize(void *pObject, enum gflGenericType_e type, uintmax_t sObject);

/**
 * @brief Destroys a generic object.
 *
 * This function releases the resources associated with the given generic object.
 *
 * @param ppGeneric Pointer to the pointer of the generic object to be destroyed.
 */
extern void gflGeneric_destroy(gflGeneric_ptr *ppGeneric);

/**
 * @brief Compares two generic objects.
 *
 * This function compares two generic objects and returns the result.
 *
 * @param pg1 Pointer to the first generic object.
 * @param pg2 Pointer to the second generic object.
 * @return An integer representing the comparison result:
 *         - 0 if both objects are equal.
 *         - A positive value if pg1 is greater than pg2.
 *         - A negative value if pg1 is less than pg2.
 */
extern int8_t gflGeneric_compare(gflGeneric_ptr pg1, gflGeneric_ptr pg2);

/**
 *
 * After this function compares two generic objects, it frees the given objects.
 *
 * @param pg1 Pointer to the first generic object.
 * @param pg2 Pointer to the second generic object.
 * @return An integer representing the comparison result:
 *         - 0 if both objects are equal.
 *         - A positive value if pg1 is greater than pg2.
 *         - A negative value if pg1 is less than pg2.
 */
extern int8_t gflGeneric_ccompare(gflGeneric_ptr pg1, gflGeneric_ptr pg2);

/**
 * @brief Computes the hash code of a generic object.
 *
 * This function calculates the hash code of the given generic object.
 *
 * @param pGeneric Pointer to the generic object.
 * @return The hash code of the generic object.
 */
extern uintmax_t gflGeneric_hashCode(gflGeneric_ptr pGeneric);

/**
 * @brief Gets the type of a generic object.
 *
 * This function returns the type of the given generic object.
 *
 * @param pGeneric Pointer to the generic object.
 * @return The type of the generic object as an enum gflGenericType_e value.
 */
extern enum gflGenericType_e gflGeneric_typeOf(gflGeneric_ptr pGeneric);

/**
 * @brief Displays a generic object.
 *
 * This function displays the contents of the given generic object.
 *
 * @param pGeneric Pointer to the generic object to be displayed.
 */
extern void gflGeneric_display(gflGeneric_ptr pGeneric);

/**
 * @brief Prints a generic object followed by a newline character.
 *
 * This function prints the contents of the given generic object followed by a newline character.
 *
 * @param pGeneric Pointer to the generic object to be printed.
 */
extern void gflGeneric_println(gflGeneric_ptr pGeneric);

/**
 * @brief Reads a generic object of the specified type.
 *
 * This function reads a generic object of the specified type.
 *
 * @param type The type of the generic object to be read.
 * @return A pointer to the read generic object.
 */
extern gflGeneric_ptr gflGeneric_read(gflGenericType_t type);

```
