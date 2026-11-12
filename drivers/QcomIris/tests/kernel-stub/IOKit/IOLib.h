/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef HOST_IOLIB_H
#define HOST_IOLIB_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
static inline void *IOMallocZero(size_t size) { return calloc(1, size); }
static inline void IOFree(void *address, size_t) { free(address); }
#endif
