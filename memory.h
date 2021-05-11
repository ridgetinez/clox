#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type *) reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount) \
    (type *) reallocate(pointer, sizeof(type) * (oldCount), 0)

void *reallocate(void *ptr, size_t oldSize, size_t newSize);