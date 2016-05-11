/* */
#include "request_app.h"

// state
struct _request_app_myprovider_t {
  int encoding_format_code;
  void *encoder;
  void *decoder;
};

request_app_myprovider_t *request_app_myprovider_new(int encoding_format_code,
    void *encoder, void *decoder) {
  request_app_myprovider_t *self = (request_app_myprovider_t *) malloc(
      sizeof(request_app_myprovider_t));
  if (!self)
    return NULL;

  self->encoding_format_code = encoding_format_code;
  self->encoder = encoder;
  self->decoder = decoder;
  return self;
}

int request_app_myprovider_get_encoding_format_code(
    request_app_myprovider_t *self) {
  return self->encoding_format_code;
}

void request_app_myprovider_set_decoder(request_app_myprovider_t *self,
    void *decoder) {
  self->decoder = decoder;
}

void *request_app_myprovider_get_decoder(request_app_myprovider_t *self) {
  return self->decoder;
}

void *request_app_myprovider_get_encoder(request_app_myprovider_t *self) {
  return self->encoder;
}

int request_app_myprovider_initialize(void *self, mal_actor_t *mal_actor) {
  int rc = 0;
  //request_app_myprovider_t *provider = (request_app_myprovider_t *) self;

  rc = mal_routing_register_provider_request_handler(
      mal_actor_get_router(mal_actor),
      TESTAREA_AREA_NUMBER,
      TESTAREA_AREA_VERSION,
      TESTAREA_TESTSERVICE_SERVICE_NUMBER,
      TESTAREA_TESTSERVICE_TESTREQUEST_OPERATION_NUMBER,
      request_app_myprovider_testarea_testservice_testrequest);

  return rc;
}

int request_app_myprovider_finalize(void *self, mal_actor_t *mal_actor) {
  int rc = 0;
  //request_app_myprovider_t *provider = (request_app_myprovider_t *) self;

  return rc;
}

void testarea_testservice_testcomposite_print(
    testarea_testservice_testcomposite_t *self) {
  printf("testarea_testservice_testcomposite_print(");
  printf("stringfield=%s", testarea_testservice_testcomposite_get_stringfield(self));
  printf(",intfield_is_present=%d", testarea_testservice_testcomposite_intfield_is_present(self));
  printf(",intfield=%d", testarea_testservice_testcomposite_get_intfield(self));
  printf(")");
}

int request_app_myprovider_testarea_testservice_testrequest(
    void *self, mal_ctx_t *mal_ctx,
    mal_endpoint_t *mal_endpoint, mal_message_t *message) {
  int rc = 0;

  request_app_myprovider_t *provider = (request_app_myprovider_t *) self;

  printf("request_app_myprovider: URI To=%s\n", mal_message_get_uri_to(message));

  // application code (may decode only a part of the message body)

  // TODO (AF): Use virtual allocation and initialization functions from encoder.
  malbinary_cursor_t cursor;
  malbinary_cursor_init(&cursor,
      mal_message_get_body(message),
      mal_message_get_body_offset(message) + mal_message_get_body_length(message),
      mal_message_get_body_offset(message));

  printf("request_app_myprovider: offset=%d\n", mal_message_get_body_offset(message));

  testarea_testservice_testcomposite_t *parameter_0;
  printf("request_app_myprovider: decode first parameter\n");
  rc = testarea_testservice_testrequest_request_decode_0(provider->encoding_format_code,
      &cursor, provider->decoder, &parameter_0);
  malbinary_cursor_assert(&cursor);
  if (rc < 0)
    return rc;

  printf("parameter_0=");
  testarea_testservice_testcomposite_print(parameter_0);
  printf("\n");

  printf("request_app_myprovider: offset=%d\n", cursor.body_offset);

  mal_string_list_t *parameter_1;
  printf("request_app_myprovider: decode second parameter\n");
  rc = testarea_testservice_testrequest_request_decode_1(provider->encoding_format_code,
      &cursor, provider->decoder, &parameter_1);
  malbinary_cursor_assert(&cursor);
  if (rc < 0)
    return rc;

  printf("parameter_1=");
  mal_string_list_print(parameter_1);
  printf("\n");

  printf("request_app_myprovider: offset=%d\n", cursor.body_offset);

  // parameter_0 may be NULL
  if (parameter_0 == NULL) {
  } else {
  }

  // parameter_1 may be NULL
  if (parameter_1 == NULL) {
  } else {
  }

  // Send response to consumer

  printf("request_app_myprovider: new string list\n");
  mal_string_list_t *string_list = mal_string_list_new(3);
  mal_string_t **string_list_content = mal_string_list_get_content(string_list);
  string_list_content[0] = mal_string_new("response-list-element-1");
  string_list_content[1] = mal_string_new("response-list-element-2");
  string_list_content[2] = mal_string_new("response-list-element-3");

  // TODO (AF): Use virtual allocation and initialization functions from encoder.
  malbinary_cursor_t cursor_r;
  malbinary_cursor_reset(&cursor_r);

  printf("request_app_myprovider: encoding_length_0\n");
  rc = testarea_testservice_testrequest_request_response_add_encoding_length_0(
		  request_app_myprovider_get_encoding_format_code(provider),
		  request_app_myprovider_get_encoder(provider), string_list, &cursor_r);
  if (rc < 0)
    return rc;

  mal_message_t *result_message = mal_message_new(
		  mal_blob_new(0),
		  mal_message_get_qoslevel(message),
		  mal_message_get_priority(message),
		  mal_message_get_domain(message),
		  mal_message_get_network_zone(message),
		  mal_message_get_session(message),
		  mal_message_get_session_name(message),
		  malbinary_cursor_get_body_length(&cursor_r));

  // TODO (AF): Use a virtual function
  malbinary_cursor_init(&cursor_r,
      mal_message_get_body(result_message),
      mal_message_get_body_offset(result_message) + mal_message_get_body_length(result_message),
      mal_message_get_body_offset(result_message));

  printf("request_app_myprovider: encode 0\n");
  rc = testarea_testservice_testrequest_request_response_encode_0(
		  request_app_myprovider_get_encoding_format_code(provider), &cursor_r,
		  request_app_myprovider_get_encoder(provider), string_list);
  malbinary_cursor_assert(&cursor_r);
  if (rc < 0)
    return rc;

  printf("AF: request_app_myprovider: handler send RESPONSE\n");
  rc = testarea_testservice_testrequest_request_response(mal_endpoint, message, result_message, (0 != 0));
  printf("AF: request_app_myprovider: handler RESPONSE sent\n");

  printf("destroy parameter_0: \n");
  testarea_testservice_testcomposite_destroy(&parameter_0);
  printf("destroy parameter_1\n");
  mal_string_list_destroy(&parameter_1);

  printf("destroy MAL init message\n");
  mal_message_destroy(&message, mal_ctx);

  printf("destroy parameter_0\n");
  mal_string_list_destroy(&string_list);

  printf("destroy MAL result message\n");
  mal_message_destroy(&result_message, mal_ctx);

  printf("Provider done.\n");
  return rc;
}

void request_app_myprovider_test(bool verbose) {
  printf(" * request_app_myprovider_test: ");
  if (verbose)
    printf("\n");

  //  @selftest
  // ...
  //  @end
  printf("OK\n");
}
