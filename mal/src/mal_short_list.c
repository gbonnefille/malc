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

#include "mal.h"

struct _mal_short_list_t {
  unsigned int element_count;
  bool *presence_flags;
  mal_short_t *content;
};

mal_short_list_t *mal_short_list_new(unsigned int element_count) {
  mal_short_list_t *self = (mal_short_list_t *) calloc(1, sizeof(mal_short_list_t));
  if (!self)
    return NULL;

  self->content = (mal_short_t *) calloc(element_count, sizeof(mal_short_t));
  if (!self->content && (element_count > 0))
  {
    mal_short_list_destroy(&self);
    return NULL;
  }
  self->presence_flags = (bool *) calloc(element_count, sizeof(bool));
  if (!self->presence_flags && (element_count > 0))
  {
    mal_short_list_destroy(&self);
    return NULL;
  }
  self->element_count = element_count;
  return self;
}

void mal_short_list_clear(mal_short_list_t * self){
  if (self) {
    if (self->element_count > 0)
    {
      self->element_count = 0;
      free(self->content);
      self->content = NULL;
      free(self->presence_flags);
      self->presence_flags = NULL;
    }
  }
}

void mal_short_list_destroy(mal_short_list_t **self_p) {
  if (self_p && *self_p) {
    mal_short_list_clear((*self_p));
    free (*self_p);
    (*self_p) = NULL;
  }
}

unsigned int mal_short_list_get_element_count(mal_short_list_t *self) {
  return self->element_count;
}

bool *mal_short_list_get_presence_flags(mal_short_list_t *self) {
  return self->presence_flags;
}

mal_short_t *mal_short_list_get_content(mal_short_list_t *self) {
  return self->content;
}

int mal_short_list_add_encoding_length_malbinary(mal_short_list_t *self,
    mal_encoder_t *encoder, void *cursor) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_add_list_size_encoding_length(encoder, list_size, cursor);
  if (rc < 0)
    return rc;
  for (int i = 0; i < list_size; i++)
  {
    mal_short_t list_element = self->content[i];
    bool presence_flag = self->presence_flags[i];
    rc = mal_encoder_add_presence_flag_encoding_length(encoder, presence_flag, cursor);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_encoder_add_short_encoding_length(encoder, list_element, cursor);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_short_list_encode_malbinary(mal_short_list_t *self,
    mal_encoder_t *encoder, void *cursor) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_encode_list_size(encoder, cursor, list_size);
  if (rc < 0)
    return rc;
  for (int i = 0; i < list_size; i++)
  {
    mal_short_t list_element = self->content[i];
    bool presence_flag = self->presence_flags[i];
    rc = mal_encoder_encode_presence_flag(encoder, cursor, presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_encoder_encode_short(encoder, cursor, list_element);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_short_list_decode_malbinary(mal_short_list_t *self,
    mal_decoder_t *decoder, void *cursor) {
  int rc = 0;
  unsigned int list_size;
  rc = mal_decoder_decode_list_size(decoder, cursor, &list_size);
  if (rc < 0)
    return rc;
  if (list_size == 0) {
    mal_short_list_clear(self);
    return 0;
  }
  self->content = (mal_short_t *) calloc(list_size, sizeof(mal_short_t *));
  if (self->content == NULL)
    return -1;
  self->presence_flags = (bool *) calloc(list_size, sizeof(bool *));
  if (self->presence_flags == NULL)
    return -1;
  self->element_count = list_size;
  for (int i = 0; i < list_size; i++) {
    rc = mal_decoder_decode_presence_flag(decoder, cursor, &self->presence_flags[i]);
    if (rc < 0)
      return rc;
    if (self->presence_flags[i]) {
      rc = mal_decoder_decode_short(decoder, cursor, &self->content[i]);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

void mal_short_list_test(bool verbose) {
  printf(" * mal_short_list: ");
  if (verbose)
    printf("\n");

  //  @selftest
  // ...
  //  @end
  printf("OK\n");
}
