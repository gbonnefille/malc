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

#ifndef __MALSPLITBINARY_H_INCLUDED__
#define __MALSPLITBINARY_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include "mal.h"
#include "malattributes.h"
#include "malbinary.h"

//  MALSPLITBINARY API version macros for compile-time API detection

#define MALSPLITBINARY_VERSION_MAJOR 1
#define MALSPLITBINARY_VERSION_MINOR 0
#define MALSPLITBINARY_VERSION_PATCH 0

#define MALSPLITBINARY_MAKE_VERSION(major, minor, patch) \
    ((major) * 10000 + (minor) * 100 + (patch))
#define MALSPLITBINARY_VERSION \
    MALSPLITBINARY_MAKE_VERSION(MALSPLITBINARY_VERSION_MAJOR, MALSPLITBINARY_VERSION_MINOR, MALSPLITBINARY_VERSION_PATCH)

typedef struct _malsplitbinary_encoder_t malsplitbinary_encoder_t;
typedef struct _malsplitbinary_decoder_t malsplitbinary_decoder_t;

struct _malsplitbinary_cursor_t {
  malbinary_cursor_t malbinary_cursor;
  char *bitfield_ptr;
  unsigned int bitfield_idx;
  unsigned int most_significant;
  unsigned int bitfield_length;
};
typedef struct _malsplitbinary_cursor_t malsplitbinary_cursor_t;

extern clog_logger_t malsplitbinary_logger;

void malsplitbinary_set_log_level(int level);

void malsplitbinary_cursor_destroy(void *cursor);
void  malsplitbinary_cursor_reset(void *cursor);
void  malsplitbinary_decoder_cursor_init(void *cursor,
    char *bytes, //message
    unsigned int length, //message length
    unsigned int offset); //message_offset
void  malsplitbinary_encoder_cursor_init(void *cursor,
    char *bytes, //message
    unsigned int length, //message length
    unsigned int offset); //message_offset
void  malsplitbinary_decoder_cursor_reset(void *cursor,
    char *bytes, unsigned int length, unsigned int offset);
void malsplitbinary_cursor_assert(void *cursor);
char *malsplitbinary_cursor_get_bitfield_ptr(malsplitbinary_cursor_t *cursor);
unsigned int malsplitbinary_cursor_get_bitfield_idx(malsplitbinary_cursor_t *cursor);
unsigned int malsplitbinary_cursor_get_most_significant(malsplitbinary_cursor_t *cursor);
unsigned int malsplitbinary_cursor_get_bitfield_length(malsplitbinary_cursor_t *cursor);

char *malsplitbinary_cursor_get_body_ptr(malsplitbinary_cursor_t *cursor);
unsigned int malsplitbinary_cursor_get_body_offset(malsplitbinary_cursor_t *cursor);
void malsplitbinary_cursor_print(malsplitbinary_cursor_t *cursor);

unsigned int malsplitbinary_cursor_get_length(void *cursor);
unsigned int malsplitbinary_cursor_get_offset(void *cursor);

// The format code must be unique among all the available encoding formats
#define MALSPLITBINARY_FORMAT_CODE 1

#define MALSPLITBINARY_PRESENCE_FLAG_SIZE 1
#define MALSPLITBINARY_ATTRIBUTE_TAG_SIZE 1
#define MALSPLITBINARY_SHORT_FORM_SIZE 8
#define MALSPLITBINARY_SMALL_ENUM_SIZE 1
#define MALSPLITBINARY_MEDIUM_ENUM_SIZE 2
#define MALSPLITBINARY_LARGE_ENUM_SIZE 4

//  Public API classes
#include "malsplitbinary_encoder.h"
#include "malsplitbinary_decoder.h"

void malsplitbinary_test(bool verbose);

#ifdef __cplusplus
}
#endif

#endif
