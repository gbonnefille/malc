/*
 */

#include "mal.h"

struct _mal_ushort_list_t {
  unsigned int element_count;
  bool *presence_flags;
  mal_ushort_t *content;
};

mal_ushort_list_t *mal_ushort_list_new(unsigned int element_count) {
  mal_ushort_list_t *self = (mal_ushort_list_t *) calloc(1, sizeof(mal_ushort_list_t));
  if (!self)
    return NULL;

  self->content = (mal_ushort_t *) calloc(element_count, sizeof(mal_ushort_t));
  if (!self->content && (element_count > 0))
  {
    free(self);
    return NULL;
  }
  self->presence_flags = (bool *) calloc(element_count, sizeof(bool));
  if (!self->presence_flags && (element_count > 0))
  {
    free(self->content);
    free(self);
    return NULL;
  }
  self->element_count = element_count;
  return self;
}

void mal_ushort_list_destroy(mal_ushort_list_t **self_p) {
  if (*self_p) {
    if ((*self_p)->element_count > 0)
    {
      free((*self_p)->content);
      free((*self_p)->presence_flags);
    }
    free (*self_p);
    (*self_p) = NULL;
  }
}

unsigned int mal_ushort_list_get_element_count(mal_ushort_list_t *self) {
  return self->element_count;
}

bool *mal_ushort_list_get_presence_flags(mal_ushort_list_t *self) {
  return self->presence_flags;
}

mal_ushort_t *mal_ushort_list_get_content(mal_ushort_list_t *self) {
  return self->content;
}

int mal_ushort_list_add_encoding_length_malbinary(mal_ushort_list_t *self,
    mal_encoder_t *encoder, void *cursor) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_add_list_size_encoding_length(encoder, list_size, cursor);
  if (rc < 0)
    return rc;
  for (int i = 0; i < list_size; i++)
  {
    mal_ushort_t list_element = self->content[i];
    bool presence_flag = self->presence_flags[i];
    rc = mal_encoder_add_presence_flag_encoding_length(encoder, presence_flag, cursor);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_encoder_add_ushort_encoding_length(encoder, list_element, cursor);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_ushort_list_encode_malbinary(mal_ushort_list_t *self,
    mal_encoder_t *encoder, void *cursor) {
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = mal_encoder_encode_list_size(encoder, cursor, list_size);
  if (rc < 0)
    return rc;
  for (int i = 0; i < list_size; i++)
  {
    mal_ushort_t list_element = self->content[i];
    bool presence_flag = self->presence_flags[i];
    rc = mal_encoder_encode_presence_flag(encoder, cursor, presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = mal_encoder_encode_ushort(encoder, cursor, list_element);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

int mal_ushort_list_decode_malbinary(mal_ushort_list_t *self,
    mal_decoder_t *decoder, void *cursor) {
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
  self->content = (mal_ushort_t *) calloc(list_size, sizeof(mal_ushort_t *));
  if (self->content == NULL)
    return -1;
  self->presence_flags = (bool *) calloc(list_size, sizeof(bool *));
  if (self->presence_flags == NULL)
    return -1;
  for (int i = 0; i < list_size; i++)
  {
    rc = mal_decoder_decode_presence_flag(decoder, cursor, &self->presence_flags[i]);
    if (rc < 0)
      return rc;
    if (self->presence_flags[i])
    {
      rc = mal_decoder_decode_ushort(decoder, cursor, &self->content[i]);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}

void mal_ushort_list_test(bool verbose) {
  printf(" * mal_ushort_list: ");
  if (verbose)
    printf("\n");

  //  @selftest
  // ...
  //  @end
  printf("OK\n");
}

