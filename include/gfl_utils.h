//
// Created by akaan on 18.07.2023.
//

#ifndef GFL_GFL_UTILS_H
#define GFL_GFL_UTILS_H

#define gflGeneric_ILP_m 0
#define gflGeneric_LP_m 1
#define gflGeneric_LLP_m 2

#if defined(_WIN32) && !defined(_WIN64)
    #define gflGeneric_env_m 32
    #define gflGeneric_dataModel_m gflGeneric_ILP_m
#elif defined(_WIN64)
    #define gflGeneric_env_m 64
    #define gflGeneric_dataModel_m gflGeneric_LLP_m
#elif defined(__unix__) && (defined(__x86_64__) || defined(__ppc64__))
    #define gflGeneric_env_m 64
    #define gflGeneric_dataModel_m gflGeneric_LP_m
#else
    #define gflGeneric_env_m 32
    #define gflGeneric_dataModel_m gflGeneric_ILP_m
#endif

#if defined(__GNUC__) || defined(__clang__)
    #if __SIZEOF_FLOAT__ == __SIZEOF_POINTER__
        #define gflGeneric_flt_m
    #elif __SIZEOF_DOUBLE__ == __SIZEOF_POINTER__
        #define gflGeneric_dbl_m
    #elif __SIZEOF_LONG_DOUBLE__ == __SIZEOF_POINTER__
        #define gflGeneric_ldbl_m
    #endif
#else
    #error "Compiler does not supported."
#endif



#include <stdint.h>
#include <float.h>
#include <stdbool.h>
#include <stddef.h>

#if gflGeneric_dataModel_m == 0
    typedef long long_t;
    typedef unsigned long ulong_t;
#elif gflGeneric_dataModel_m == 1
    typedef long long long_t;
    typedef unsigned long long ulong_t;
#elif gflGeneric_dataModel_m == 2
    typedef long long_t;
    typedef unsigned long ulong_t;
#endif

#endif //GFL_GFL_UTILS_H
