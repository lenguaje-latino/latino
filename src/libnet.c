#include <stdio.h>
#include <curl/curl.h>

#include "libnet.h"

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;
  return size*nmemb;
}

void lat_peticion(lat_mv* mv){
  lat_objeto* o = lat_desapilar(mv);
  lat_objeto* r = NULL;
  char* url = __cadena(o);
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if(curl) {
    struct string s;
    init_string(&s);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
      lat_fatal_error("Linea %d, %d: %s", o->num_linea, o->num_columna, curl_easy_strerror(res));
    }
    r = lat_cadena_nueva(mv, strdup(s.ptr));
    curl_easy_cleanup(curl);
  }
  lat_apilar(mv, r);
}
