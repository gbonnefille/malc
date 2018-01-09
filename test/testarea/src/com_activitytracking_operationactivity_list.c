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
#include "com.h"

struct _com_activitytracking_operationactivity_list_t {
  unsigned int element_count;
  com_activitytracking_operationactivity_t ** content;
};

// default constructor
com_activitytracking_operationactivity_list_t * com_activitytracking_operationactivity_list_new(unsigned int element_count)
{
  com_activitytracking_operationactivity_list_t *self = (com_activitytracking_operationactivity_list_t *) calloc(1, sizeof(com_activitytracking_operationactivity_list_t));
  if (!self)
    return NULL;
  self->element_count = element_count;
  self->content = (com_activitytracking_operationactivity_t **) calloc(element_count, sizeof(com_activitytracking_operationactivity_t *));
  if (!self->content && (element_count > 0))
  {
    free(self);
    return NULL;
  }
  return self;
}

// destructor, free the list, its content and its elements
void com_activitytracking_operationactivity_list_destroy(com_activitytracking_operationactivity_list_t ** self_p)
{
  if ((*self_p)->element_count > 0)
  {
    for (int i = 0; i < (*self_p)->element_count; i++)
    {
      if ((*self_p)->content[i] != NULL)
        com_activitytracking_operationactivity_destroy(&(*self_p)->content[i]);
    }
    free((*self_p)->content);
  }
  free (*self_p);
  (*self_p) = NULL;
}

// fields accessors for composite list com_activitytracking_operationactivity_list
unsigned int com_activitytracking_operationactivity_list_get_element_count(com_activitytracking_operationactivity_list_t * self)
{
  return self->element_count;
}
com_activitytracking_operationactivity_t ** com_activitytracking_operationactivity_list_get_content(com_activitytracking_operationactivity_list_t * self)
{
  return self->content;
}

// encoding functions related to transport malbinary
int com_activitytracking_operationactivity_list_add_encoding_length_malbinary(com_activitytracking_operationactivity_list_t * self, mal_encoder_t * encoder, void * cursor)
{
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_add_list_size_encoding_length(encoder, list_size, cursor);
  if (rc < 0)
    return rc;
  for (int i = 0; i < list_size; i++)
  {
    com_activitytracking_operationactivity_t * list_element = self->content[i];
    bool presence_flag = (list_element != NULL);
    rc = mal_encoder_add_presence_flag_encoding_length(encoder, presence_flag, cursor);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = com_activitytracking_operationactivity_add_encoding_length_malbinary(list_element, encoder, cursor);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}
int com_activitytracking_operationactivity_list_encode_malbinary(com_activitytracking_operationactivity_list_t * self, mal_encoder_t * encoder, void * cursor)
{
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_encode_list_size(encoder, cursor, list_size);
  if (rc < 0)
    return rc;
  com_activitytracking_operationactivity_t ** content = self->content;
  for (int i = 0; i < list_size; i++)
  {
    com_activitytracking_operationactivity_t *list_element = content[i];
    bool presence_flag = (list_element != NULL);
    rc = mal_encoder_encode_presence_flag(encoder, cursor, presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = com_activitytracking_operationactivity_encode_malbinary(list_element, encoder, cursor);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}
int com_activitytracking_operationactivity_list_decode_malbinary(com_activitytracking_operationactivity_list_t * self, mal_decoder_t * decoder, void * cursor)
{
  int rc = 0;
  unsigned int list_size;
  rc = mal_decoder_decode_list_size(decoder, cursor, &list_size);
  if (rc < 0)
    return rc;
  if (list_size == 0)
  {
    self->element_count = 0;
    self->content = NULL;
    return 0;
  }
  self->content = (com_activitytracking_operationactivity_t **) calloc(list_size, sizeof(com_activitytracking_operationactivity_t *));
  if (self->content == NULL)
    return -1;
  self->element_count = list_size;
  for (int i = 0; i < list_size; i++)
  {
    bool presence_flag;
    rc = mal_decoder_decode_presence_flag(decoder, cursor, &presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      self->content[i] = com_activitytracking_operationactivity_new();
      if (self->content[i] == NULL) return -1;
      rc = com_activitytracking_operationactivity_decode_malbinary(self->content[i], decoder, cursor);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

// test function
void com_activitytracking_operationactivity_list_test(bool verbose)
{
  printf(" * list of com_activitytracking_operationactivity: ");
  if (verbose)
    printf("\n");
  printf("OK\n");
}
