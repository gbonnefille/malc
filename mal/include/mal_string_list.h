/*
 */

#ifndef __MAL_STRING_LIST_H_INCLUDED__
#define __MAL_STRING_LIST_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

mal_string_list_t *mal_string_list_new(unsigned int element_count);

void mal_string_list_destroy(mal_string_list_t **self_p);

unsigned int mal_string_list_get_element_count(mal_string_list_t *self);

mal_string_t **mal_string_list_get_content(mal_string_list_t *self);

void mal_string_list_add_element(mal_string_list_t *self, int index, mal_string_t *element);

int mal_string_list_add_encoding_length_malbinary(mal_string_list_t *self,
    mal_encoder_t *encoder, void *cursor);

int mal_string_list_encode_malbinary(mal_string_list_t *self,
    mal_encoder_t *encoder, void *cursor);

int mal_string_list_decode_malbinary(mal_string_list_t *self,
    mal_decoder_t *decoder, void *cursor);

void mal_string_list_print(mal_string_list_t *self);

//  Self test of this class
void mal_string_list_test(bool verbose);

#ifdef __cplusplus
}
#endif

#endif
