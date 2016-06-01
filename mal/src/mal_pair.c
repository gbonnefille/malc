#include "mal.h"


// structure definition for composite mal_pair
struct _mal_pair_t {
  bool first_is_present;
  unsigned char first_attribute_tag;
  union mal_attribute_t first;
  bool second_is_present;
  unsigned char second_attribute_tag;
  union mal_attribute_t second;
};

// fields accessors for composite mal_pair
bool mal_pair_first_is_present(mal_pair_t * self)
{
  return self->first_is_present;
}
void mal_pair_first_set_present(mal_pair_t * self, bool is_present)
{
  self->first_is_present = is_present;
}
unsigned char mal_pair_first_get_attribute_tag(mal_pair_t * self)
{
  return self->first_attribute_tag;
}
void mal_pair_first_set_attribute_tag(mal_pair_t * self, unsigned char attribute_tag)
{
  self->first_attribute_tag = attribute_tag;
}
bool mal_pair_second_is_present(mal_pair_t * self)
{
  return self->second_is_present;
}
void mal_pair_second_set_present(mal_pair_t * self, bool is_present)
{
  self->second_is_present = is_present;
}
unsigned char mal_pair_second_get_attribute_tag(mal_pair_t * self)
{
  return self->second_attribute_tag;
}
void mal_pair_second_set_attribute_tag(mal_pair_t * self, unsigned char attribute_tag)
{
  self->second_attribute_tag = attribute_tag;
}

// default constructor
mal_pair_t * mal_pair_new(void)
{
  mal_pair_t *self = (mal_pair_t *) calloc(1, sizeof(mal_pair_t));
  if (!self)
    return NULL;
  return self;
}

// encoding functions related to transport malbinary
int mal_pair_add_encoding_length_malbinary(mal_pair_t * self, mal_encoder_t * mal_encoder, void * cursor)
{
  int rc = 0;
  ((malbinary_cursor_t *) cursor)->body_length += MALBINARY_PRESENCE_FLAG_SIZE;
  if (self->first_is_present)
  {
    ((malbinary_cursor_t *) cursor)->body_length += MALBINARY_ATTRIBUTE_TAG_SIZE;
    rc = malbinary_encoder_add_attribute_encoding_length(mal_encoder, self->first_attribute_tag, self->first, cursor);
    if (rc < 0)
      return rc;
  }
  ((malbinary_cursor_t *) cursor)->body_length += MALBINARY_PRESENCE_FLAG_SIZE;
  if (self->second_is_present)
  {
    ((malbinary_cursor_t *) cursor)->body_length += MALBINARY_ATTRIBUTE_TAG_SIZE;
    rc = malbinary_encoder_add_attribute_encoding_length(mal_encoder, self->second_attribute_tag, self->second, cursor);
    if (rc < 0)
      return rc;
  }
  return rc;
}
int mal_pair_encode_malbinary(mal_pair_t * self, mal_encoder_t * mal_encoder, void * cursor)
{
  int rc = 0;
  bool presence_flag;
  presence_flag = self->first_is_present;
  rc = malbinary_encoder_encode_presence_flag(mal_encoder, cursor, presence_flag);
  if (rc < 0)
    return rc;
  if (presence_flag)
  {
    rc = malbinary_encoder_encode_attribute_tag(mal_encoder, cursor, self->first_attribute_tag);
    if (rc < 0)
      return rc;
    rc = malbinary_encoder_encode_attribute(mal_encoder, cursor, self->first_attribute_tag, self->first);
    if (rc < 0)
      return rc;
  }
  presence_flag = self->second_is_present;
  rc = malbinary_encoder_encode_presence_flag(mal_encoder, cursor, presence_flag);
  if (rc < 0)
    return rc;
  if (presence_flag)
  {
    rc = malbinary_encoder_encode_attribute_tag(mal_encoder, cursor, self->second_attribute_tag);
    if (rc < 0)
      return rc;
    rc = malbinary_encoder_encode_attribute(mal_encoder, cursor, self->second_attribute_tag, self->second);
    if (rc < 0)
      return rc;
  }
  return rc;
}
int mal_pair_decode_malbinary(mal_pair_t * self, mal_decoder_t * mal_decoder, void * cursor)
{
  int rc = 0;
  bool presence_flag;
  rc = malbinary_decoder_decode_presence_flag(mal_decoder, cursor, &presence_flag);
  if (rc < 0)
    return rc;
  if (presence_flag)
  {
    rc = malbinary_decoder_decode_attribute_tag(mal_decoder, cursor, &self->first_attribute_tag);
    if (rc < 0)
      return rc;
    rc = malbinary_decoder_decode_attribute(mal_decoder, cursor, self->first_attribute_tag, self->first);
    if (rc < 0)
      return rc;
  }
  self->first_is_present = presence_flag;
  rc = malbinary_decoder_decode_presence_flag(mal_decoder, cursor, &presence_flag);
  if (rc < 0)
    return rc;
  if (presence_flag)
  {
    rc = malbinary_decoder_decode_attribute_tag(mal_decoder, cursor, &self->second_attribute_tag);
    if (rc < 0)
      return rc;
    rc = malbinary_decoder_decode_attribute(mal_decoder, cursor, self->second_attribute_tag, self->second);
    if (rc < 0)
      return rc;
  }
  self->second_is_present = presence_flag;
  return rc;
}

// destructor
void mal_pair_destroy(mal_pair_t ** self_p)
{
  if ((*self_p)->first_is_present)
  {
    mal_attribute_destroy(&(*self_p)->first, (*self_p)->first_attribute_tag);
  }
  if ((*self_p)->second_is_present)
  {
    mal_attribute_destroy(&(*self_p)->second, (*self_p)->second_attribute_tag);
  }
  free(*self_p);
  (*self_p) = NULL;
}

// test function
void mal_pair_test(bool verbose)
{
  printf(" * MAL:Pair: ");
  if (verbose)
    printf("\n");
  printf("OK\n");
}
