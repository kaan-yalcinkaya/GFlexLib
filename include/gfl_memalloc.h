//
// Created by akaan on 18.07.2023.
//

#ifndef GFL_GFL_MEMALLOC_H
#define GFL_GFL_MEMALLOC_H

#include <stdlib.h>

#define gflAlloc_malloc_m(type, count) \
(type*) malloc(sizeof(type) * (count))

#define gflAlloc_calloc_m(type, count) \
(type*) calloc((count), sizeof(type))

#endif //GFL_GFL_MEMALLOC_H
