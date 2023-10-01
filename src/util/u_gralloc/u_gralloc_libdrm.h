/* Copied from:
 * https://gitlab.freedesktop.org/mesa/drm/-/blob/6abc164052e4902f67213baa279d743cf46227d4/android/gralloc_handle.h
 */

/*
 * Copyright (C) 2010-2011 Chia-I Wu <olvaffe@gmail.com>
 * Copyright (C) 2010-2011 LunarG Inc.
 * Copyright (C) 2016 Linaro, Ltd., Rob Herring <robh@kernel.org>
 * Copyright (C) 2018 Collabora, Robert Foss <robert.foss@collabora.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __ANDROID_GRALLOC_HANDLE_H__
#define __ANDROID_GRALLOC_HANDLE_H__

#include <cutils/native_handle.h>
#include <stdint.h>

struct gralloc_handle_t {
	native_handle_t base;

	/* dma-buf file descriptor
	 * Must be located first since, native_handle_t is allocated
	 * using native_handle_create(), which allocates space for
	 * sizeof(native_handle_t) + sizeof(int) * (numFds + numInts)
	 * numFds = GRALLOC_HANDLE_NUM_FDS
	 * numInts = GRALLOC_HANDLE_NUM_INTS
	 * Where numFds represents the number of FDs and
	 * numInts represents the space needed for the
	 * remainder of this struct.
	 * And the FDs are expected to be found first following
	 * native_handle_t.
	 */
	int prime_fd;

	/* api variables */
	uint32_t magic; /* differentiate between allocator impls */
	uint32_t version; /* api version */

	uint32_t width; /* width of buffer in pixels */
	uint32_t height; /* height of buffer in pixels */
	uint32_t format; /* pixel format (Android) */
	uint32_t usage; /* android libhardware usage flags */

	uint32_t stride; /* the stride in bytes */
	int data_owner; /* owner of data (for validation) */
	uint64_t modifier __attribute__((aligned(8))); /* buffer modifiers */

	union {
		void *data; /* pointer to struct gralloc_gbm_bo_t */
		uint64_t reserved;
	} __attribute__((aligned(8)));
};

#define GRALLOC_HANDLE_VERSION 4
#define GRALLOC_HANDLE_MAGIC 0x60585350
#define GRALLOC_HANDLE_NUM_FDS 1
#define GRALLOC_HANDLE_NUM_INTS (	\
	((sizeof(struct gralloc_handle_t) - sizeof(native_handle_t))/sizeof(int))	\
	 - GRALLOC_HANDLE_NUM_FDS)

#endif /* __ANDROID_GRALLOC_HANDLE_H__ */
