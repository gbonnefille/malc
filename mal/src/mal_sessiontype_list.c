#include "mal.h"

struct _mal_sessiontype_list_t {
  unsigned int element_count;
  bool * presence_flags;
  mal_sessiontype_t * content;
};

// default constructor
mal_sessiontype_list_t * mal_sessiontype_list_new(unsigned int element_count)
{
  mal_sessiontype_list_t *self = (mal_sessiontype_list_t *) calloc(1, sizeof(mal_sessiontype_list_t));
  if (!self)
    return NULL;
  self->element_count = element_count;
  if (element_count == 0)
    return self;
  self->presence_flags = (bool *) calloc(element_count, sizeof(bool));
  if (!self->presence_flags)
  {
    free(self);
    return NULL;
  }
  self->content = (mal_sessiontype_t *) calloc(element_count, sizeof(mal_sessiontype_t));
  if (!self->content)
  {
    free(self->presence_flags);
    free(self);
    return NULL;
  }
  return self;
}

// destructor, free the list and its content
void mal_sessiontype_list_destroy(mal_sessiontype_list_t ** self_p)
{
  if ((*self_p)->element_count > 0)
  {
    free((*self_p)->presence_flags);
    free((*self_p)->content);
  }
  free (*self_p);
  (*self_p) = NULL;
}

// fields accessors for enumeration list mal_sessiontype_list
unsigned int mal_sessiontype_list_get_element_count(mal_sessiontype_list_t * self)
{
  return self->element_count;
}
bool * mal_sessiontype_list_get_presence_flags(mal_sessiontype_list_t * self)
{
  return self->presence_flags;
}
mal_sessiontype_t * mal_sessiontype_list_get_content(mal_sessiontype_list_t * self)
{
  return self->content;
}

// encoding functions related to transport malbinary
int mal_sessiontype_list_add_encoding_length_malbinary(mal_sessiontype_list_t * self, mal_encoder_t * encoder, void * cursor)
{
  int rc = 0;
  unsigned int list_size = self->element_count;
  malbinary_encoder_add_list_size_encoding_length(encoder, list_size, cursor);
  malbinary_add_length((malbinary_cursor_t *) cursor, list_size);
  bool * presence_flags = self->presence_flags;
  for (int i = 0; i < list_size; i++)
  {
    bool presence_flag = presence_flags[i];
    if (presence_flag)
    {
      ((malbinary_cursor_t *) cursor)->body_length += MALBINARY_SMALL_ENUM_SIZE;
    }
  }
  return rc;
}
int mal_sessiontype_list_encode_malbinary(mal_sessiontype_list_t * self, mal_encoder_t * encoder, void * cursor)
{
  int rc = 0;
  unsigned int list_size = self->element_count;
  rc = malbinary_encoder_encode_list_size(encoder, cursor, list_size);
  if (rc < 0)
    return rc;
  bool * presence_flags = self->presence_flags;
  for (int i = 0; i < list_size; i++)
  {
    bool presence_flag = presence_flags[i];
    rc = malbinary_encoder_encode_presence_flag(encoder, cursor, presence_flag);
    if (rc < 0)
      return rc;
    if (presence_flag)
    {
      rc = malbinary_encoder_encode_small_enum(encoder, cursor, self->content[i]);
      if (rc < 0)
        return rc;
    }
  }
  return rc;
}
int mal_sessiontype_list_decode_malbinary(mal_sessiontype_list_t * self, mal_decoder_t * decoder, void * cursor)
{
  int rc = 0;
  unsigned int list_size;
  rc = malbinary_decoder_decode_list_size(decoder, cursor, &list_size);
  if (rc < 0)
    return rc;
  bool * presence_flags = self->presence_flags;
  for (int i = 0; i < list_size; i++)
  {
    bool presence_flag;
    rc = malbinary_decoder_decode_presence_flag(decoder, cursor, &presence_flag);
    if (rc < 0)
      return rc;
    presence_flags[i] = presence_flag;
    if (presence_flag)
    {
    }
  }
  return rc;
}

// test function
void mal_sessiontype_list_test(bool verbose)
{
  printf(" * list of mal_sessiontype: ");
  if (verbose)
    printf("\n");
  printf("OK\n");
}
