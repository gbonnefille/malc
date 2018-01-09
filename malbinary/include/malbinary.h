/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 CNES
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 */

#ifndef __MALBINARY_H_INCLUDED__
#define __MALBINARY_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "malattributes.h"

#include "mal_encoder.h"
#include "mal_decoder.h"

//  MALBINARY API version macros for compile-time API detection

#define MALBINARY_VERSION_MAJOR 1
#define MALBINARY_VERSION_MINOR 0
#define MALBINARY_VERSION_PATCH 0

#define MALBINARY_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define MALBINARY_VERSION \
    MALBINARY_MAKE_VERSION(MALBINARY_VERSION_MAJOR, MALBINARY_VERSION_MINOR, MALBINARY_VERSION_PATCH)

typedef struct _malbinary_encoder_t malbinary_encoder_t;
typedef struct _malbinary_decoder_t malbinary_decoder_t;

struct _malbinary_cursor_t {
  // Pointer to the first byte of the body, calculated in malbinary_cursor_init from the ptr and
  // offset of the allocated MAL message bytes array.
  // Should never be modified anywhere
  char* body_ptr;
  // Length of the body part, calculated then fixed in malbinary_cursor_init
  // Should never be modified during encoding or decoding
  unsigned int body_length;
  // Current offset during encoding/decoding in the body part, initialized to 0 in malbinary_cursor_init
  unsigned int body_offset;
};

typedef struct _malbinary_cursor_t malbinary_cursor_t;

void malbinary_cursor_destroy(void *cursor);

void malbinary_cursor_reset(void *cursor);
void malbinary_cursor_init(void *cursor,
    char *bytes, unsigned int length, unsigned int offset);
void malbinary_cursor_copy(malbinary_cursor_t *from, malbinary_cursor_t *to);

void malbinary_cursor_assert(void *cursor);

unsigned int malbinary_cursor_get_length(void *cursor);
unsigned int malbinary_cursor_get_offset(void *cursor);

// The format code must be unique among all the available encoding formats
#define MALBINARY_FORMAT_CODE 0

#define MALBINARY_PRESENCE_FLAG_SIZE 1
#define MALBINARY_ATTRIBUTE_TAG_SIZE 1
#define MALBINARY_SHORT_FORM_SIZE 8
#define MALBINARY_SMALL_ENUM_SIZE 1
#define MALBINARY_MEDIUM_ENUM_SIZE 2
#define MALBINARY_LARGE_ENUM_SIZE 4

void malbinary_test(bool verbose);

//  Public API classes
#include "malbinary_encoder.h"
#include "malbinary_decoder.h"

#ifdef __cplusplus
}
#endif

#endif
