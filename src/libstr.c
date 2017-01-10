/*
The MIT License (MIT)

Copyright (c) 2015 - 2016. Latino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "latgc.h"
#include "latino.h"
#include "latlist.h"
#include "latmem.h"
#include "latobj.h"

#define LIB_CADENA_NAME "cadena"

int __lista_obtener_indice(lista *list, void *data);

char *__str_analizar_fmt(const char *s, size_t len) {
  char *ret = __memoria_asignar(NULL, len + 1);
  int i = 0;
  int j = 0;
  int c = '@';
  for (i = 0; i < ((int)len); i++) {
    switch (s[i]) {
    case '\\': {
      switch (s[i + 1]) {
      case '/':
        c = '/';
        i++;
        goto save;
      case '"':
        c = '\"';
        i++;
        goto save;
      case 'a':
        c = '\a';
        i++;
        goto save;
      case 'b':
        c = '\b';
        i++;
        goto save;
      case 'f':
        c = '\f';
        i++;
        goto save;
      case 'n':
        c = '\n';
        i++;
        goto save;
      case 'r':
        c = '\r';
        i++;
        goto save;
      case 't':
        c = '\t';
        i++;
        goto save;
      case '\\':
        c = '\\';
        i++;
        goto save;
      case 'u':
        c = s[i];
        ret[j] = c;
        j++;
        i++;
        int k;
        for (k = 0; k <= 4; k++) {
          c = s[i];
          ret[j] = c;
          j++;
          i++;
        }
      default:
        c = s[i];
        break;
      }
    } break;
    default:
      c = s[i];
      break;
    }
  save:
    ret[j] = c;
    j++;
  }
  ret[j] = '\0';
  return ret;
}

char *__str_analizar(const char *s, size_t len) {
  char *ret = __memoria_asignar(NULL, len + 1);
  int i = 0;
  int j = 0;
  int c = '@';
  for (i = 0; i < ((int)len); i++) {
    switch (s[i]) {
    case '\\': {
      switch (s[i + 1]) {
      case '\\':
        c = '\\';
        i++;
        ret[j] = c;
        j++;
        c = '\\';
        i++;
        ret[j] = c;
        j++;
      case 'u':
        c = s[i];
        ret[j] = c;
        j++;
        i++;
        int k;
        for (k = 0; k <= 4; k++) {
          c = s[i];
          ret[j] = c;
          j++;
          i++;
        }
      default:
        c = s[i];
        break;
      }
    } break;
    default:
      c = s[i];
      break;
    }
    ret[j] = c;
    j++;
  }
  ret[j] = '\0';
  // printf("ret: %s\n", ret);
  return ret;
}

char *__str_decimal_a_cadena(double d) {
  char *buffer = __memoria_asignar(NULL, 32);
  snprintf(buffer, 32, "%.14g", d);
  return buffer;
}

char *__str_logico_a_cadena(int i) {
  char *buffer = __memoria_asignar(NULL, 11);
  if (i)
    snprintf(buffer, 11, "%s", "verdadero");
  else
    snprintf(buffer, 11, "%s", "falso");
  return buffer;
}

bool __str_inicia_con(const char *base, const char *str) {
  return (strstr(base, str) - base) == 0;
}

bool __str_termina_con(char *base, char *str) {
  int blen = strlen(base);
  int slen = strlen(str);
  return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

int __str_intercambiar_posicion(char *base, char *str, int startIndex) {
  int result;
  int baselen = strlen(base);
  if ((int)strlen(str) > baselen || startIndex > baselen) {
    result = -1;
  } else {
    if (startIndex < 0) {
      startIndex = 0;
    }
    char *pos = strstr(base + startIndex, str);
    if (pos == NULL) {
      result = -1;
    } else {
      result = pos - base;
    }
  }
  return result;
}

int __str_posicion(char *base, char *str) {
  return __str_intercambiar_posicion(base, str, 0);
}

int __str_ultima_posicion(char *base, char *str) {
  int result;
  if (strlen(str) > strlen(base)) {
    result = -1;
  } else {
    int start = 0;
    int endinit = strlen(base) - strlen(str);
    int end = endinit;
    int endtmp = endinit;
    while (start != end) {
      start = __str_intercambiar_posicion(base, str, start);
      end = __str_intercambiar_posicion(base, str, end);
      if (start == -1) {
        end = -1;
      } else if (end == -1) {
        if (endtmp == (start + 1)) {
          end = start;
        } else {
          end = endtmp - (endtmp - start) / 2;
          if (end <= start) {
            end = start + 1;
          }
          endtmp = end;
        }
      } else {
        start = end;
        end = endinit;
      }
    }
    result = start;
  }
  return result;
}

char *__str_insertar(char *dest, char *src, int pos) {
  int srclen = strlen(src);
  int dstlen = strlen(dest);
  if (pos < 0) {
    pos = dstlen + pos;
  }
  if (pos > dstlen) {
    pos = dstlen;
  }
  char *m = __memoria_asignar(NULL, srclen + dstlen + 1);
  memcpy(m, dest, pos);
  memcpy(m + pos, src, srclen);
  memcpy(m + pos + srclen, dest + pos, dstlen - pos + 1);
  return m;
}

char *__str_rellenar_izquierda(char *base, char *c, int n) {
  char *ret = __memoria_asignar(NULL, MAX_STR_LENGTH);
  int len = strlen(base);
  int i, final = len - 1;
  for (i = 0; i < (n - final); i++) {
    ret = strcat(ret, c);
  }
  ret = strcat(ret, base);
  return ret;
}

char *__str_rellenar_derecha(char *base, char *c, int n) {
  char *ret = __memoria_asignar(NULL, MAX_STR_LENGTH);
  int len = strlen(base);
  strcpy(ret, base);
  int i, final = len - 1;
  for (i = 0; i < (n - final); i++) {
    ret = strcat(ret, c);
  }
  return ret;
}

char *__str_reemplazar(char *str, const char *orig, const char *rep) {
  char *buffer = __memoria_asignar(NULL, MAX_STR_LENGTH);
  char *p;
  int i = 0;
  while (str[i]) {
    if (!(p = strstr(str + i, orig))) {
      strcpy(buffer, str);
      return buffer;
    }
    strncpy(buffer + strlen(buffer), str + i, (p - str) - i);
    buffer[p - str] = '\0';
    strcat(buffer, rep);
    // printf("STR:%s\n",buffer);
    i = (p - str) + strlen(orig);
  }
  return buffer;
}

char *__str_subcadena(const char *str, int beg, int n) {
  char *ret = __memoria_asignar(NULL, n + 1);
  strncpy(ret, (str + beg), n);
  *(ret + n) = 0;
  return ret;
}

char *__str_minusculas(const char *str) {
  int i = 0;
  int len = strlen(str);
  char *ret = (char *)__memoria_asignar(NULL, len + 1);
  for (i = 0; i < len; i++) {
    ret[i] = tolower(str[i]);
  }
  ret[len] = 0;
  return ret;
}

char *__str_mayusculas(const char *str) {
  int i = 0;
  int len = strlen(str);
  char *ret = __memoria_asignar(NULL, len + 1);
  for (i = 0; i < len; i++) {
    ret[i] = toupper(str[i]);
  }
  ret[len] = 0;
  return ret;
}

char *__str_quitar_espacios(const char *str) {
  char *start;
  char *end;
  for (start = (char *)str; *start; start++) {
    if (!isspace((unsigned char)start[0]))
      break;
  }
  for (end = start + strlen(start); end > start + 1; end--) {
    if (!isspace((unsigned char)end[-1]))
      break;
  }
  char *ret = __memoria_asignar(NULL, (end - start) + 1);
  *end = 0;
  if (start > str) {
    memcpy(ret, start, (end - start) + 1);
  } else {
    memcpy(ret, str, strlen(str));
  }
  return ret;
}

void lat_cadena_concatenar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *s1 = lat_obj2cstring(a);
  char *s2 = lat_obj2cstring(b);
  int len = strlen(s1) + strlen(s2) + 1;
  char *s3 = __memoria_asignar(mv, len);
  strcat(s3, s1);
  strcat(s3, s2);
  lat_objeto *r = lat_cadena_nueva(mv, s3);
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
  __memoria_liberar(mv, s1);
  __memoria_liberar(mv, s2);
}

void lat_cadena_comparar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = lat_numerico_nuevo(mv, strcmp(__cadena(a), __cadena(b)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_contiene(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *result = strstr(__cadena(a), __cadena(b));
  if (result != NULL) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else {
    lat_apilar(mv, mv->objeto_falso);
  }
}

void lat_cadena_termina_con(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  if (__str_termina_con(__cadena(a), __cadena(b)))
    lat_apilar(mv, mv->objeto_verdadero);
  else
    lat_apilar(mv, mv->objeto_falso);
}

void lat_cadena_es_igual(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  if (strcmp(__cadena(a), __cadena(b)) == 0) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else {
    lat_apilar(mv, mv->objeto_falso);
  }
}

/*
void lat_format(lat_mv* mv){
}
*/

void lat_cadena_indice(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *r = NULL;
  if (a->tipo == T_STR && b->tipo == T_STR) {
    char *cpos = strstr(__cadena(a), __cadena(b));
    int pos;
    if (cpos == NULL) {
      pos = -1;
    } else {
      pos = cpos - __cadena(a);
    }
    r = lat_numerico_nuevo(mv, pos);
  }
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
  return;
}

void lat_cadena_insertar(lat_mv *mv) {
  lat_objeto *c = lat_desapilar(mv);
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *buf = __str_insertar(__cadena(a), __cadena(b), __numerico(c));
  lat_objeto *tmp = lat_cadena_nueva(mv, buf);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_ultimo_indice(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp =
      lat_numerico_nuevo(mv, __str_ultima_posicion(__cadena(a), __cadena(b)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_rellenar_izquierda(lat_mv *mv) {
  lat_objeto *c = lat_desapilar(mv);
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *buf = __str_rellenar_izquierda(__cadena(a), __cadena(b), __numerico(c));
  lat_objeto *tmp = lat_cadena_nueva(mv, buf);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_rellenar_derecha(lat_mv *mv) {
  lat_objeto *c = lat_desapilar(mv);
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *buf = __str_rellenar_derecha(__cadena(a), __cadena(b), __numerico(c));
  lat_objeto *tmp = lat_cadena_nueva(mv, buf);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_eliminar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *buf = __str_reemplazar(__cadena(a), __cadena(b), "");
  lat_objeto *tmp = lat_cadena_nueva(mv, buf);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_esta_vacia(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  if (strcmp(__cadena(a), "") == 0) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else {
    lat_apilar(mv, mv->objeto_falso);
  }
}

void lat_cadena_longitud(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = NULL;
  if (a->tipo == T_STR) {
    tmp = lat_numerico_nuevo(mv, strlen(__cadena(a)));
  } else if (a->tipo == T_DICT) {
    tmp = lat_numerico_nuevo(mv, __dic_longitud(__dic(a)));
  } else {
    tmp = lat_numerico_nuevo(mv, 0);
  }
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_reemplazar(lat_mv *mv) {
  lat_objeto *c = lat_desapilar(mv);
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *bf = __str_analizar_fmt(__cadena(b), strlen(__cadena(b)));
  char *cf = __str_analizar_fmt(__cadena(c), strlen(__cadena(c)));
  char *tmp = __str_reemplazar(__cadena(a), bf, cf);
  lat_objeto *r = lat_cadena_nueva(mv, tmp);
  lat_apilar(mv, r);
  lat_gc_agregar(mv, r);
  __memoria_liberar(mv, bf);
  __memoria_liberar(mv, cf);
}

void lat_cadena_inicia_con(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  bool emp = __str_inicia_con(__cadena(a), __cadena(b));
  if (emp) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else {
    lat_apilar(mv, mv->objeto_falso);
  }
}

void lat_cadena_subcadena(lat_mv *mv) {
  lat_objeto *c = lat_desapilar(mv);
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = lat_cadena_nueva(
      mv, __str_subcadena(__cadena(a), __numerico(b), __numerico(c)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_minusculas(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = lat_cadena_nueva(mv, __str_minusculas(__cadena(a)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_mayusculas(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = lat_cadena_nueva(mv, __str_mayusculas(__cadena(a)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_quitar_espacios(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  lat_objeto *tmp = lat_cadena_nueva(mv, __str_quitar_espacios(__cadena(a)));
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_es_numerico(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  char *ptr;
  strtod(__cadena(a), &ptr);
  if (strcmp(ptr, "") == 0) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else {
    lat_apilar(mv, mv->objeto_falso);
  }
}

void lat_cadena_es_alfa(lat_mv *mv) {
  lat_objeto *a = lat_desapilar(mv);
  char *cad = __cadena(a);
  bool res = true;
  for (int i = 0; i < strlen(cad); i++) {
    if (!isalnum(cad[i])) {
      res = false;
      break;
    }
  }
  if (res) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else {
    lat_apilar(mv, mv->objeto_falso);
  }
}

void lat_cadena_separar(lat_mv *mv) {
  lat_objeto *b = lat_desapilar(mv);
  lat_objeto *a = lat_desapilar(mv);
  char *sep = " "; // separador default
  if (b->tipo != T_NULL) {
    sep = __cadena(b);
    if (strlen(sep) == 0) {
      sep = " ";
    }
  }
  char *str = strdup(__cadena(a));
  lista *lst = __lista_crear();
  char *tok = strtok(str, sep);
  if (tok) {
    __lista_agregar(lst, lat_cadena_nueva(mv, strdup(tok)));
  }
  while (tok != NULL) {
    tok = strtok(NULL, sep);
    if (tok) {
      __lista_agregar(lst, lat_cadena_nueva(mv, strdup(tok)));
    }
  }
  lat_objeto *tmp = lat_lista_nueva(mv, lst);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_invertir(lat_mv *mv) {
  // TODO: Pendiente implementacion para multibyte
  lat_objeto *a = lat_desapilar(mv);
  char *orig = __cadena(a);
  int i = strlen(orig) - 1;
  char *dest = __memoria_asignar(mv, strlen(orig) + 1);
  int j = 0;
  for (; i >= 0; i--) {
    dest[j] = orig[i];
    j++;
  }
  dest[strlen(orig)] = '\0';
  lat_objeto *tmp = lat_cadena_nueva(mv, dest);
  lat_apilar(mv, tmp);
  lat_gc_agregar(mv, tmp);
}

void lat_cadena_ejecutar(lat_mv *mv) {
  int status;
  lat_objeto *func = ast_analizar_arbol(
      mv, lat_analizar_expresion(__cadena(lat_desapilar(mv)), &status));
  if (status == 0) {
    lat_llamar_funcion(mv, func);
    __obj_eliminar(mv, func);
  } else {
    lat_error("Error al ejeuctar cadena...");
  }
}

void lat_cadena_regex(lat_mv *mv) {
  lat_objeto *cadena_regex = lat_desapilar(mv);
  lat_objeto *cadena = lat_desapilar(mv);
  regex_t regex;
  int reti;
  reti = regcomp(&regex, __cadena(cadena_regex), 0);
  if (reti) {
    lat_error("Linea %d, %d: %s", cadena->num_linea, cadena->num_columna,
              "error al compilar regex.");
  }
  reti = regexec(&regex, __cadena(cadena), 0, NULL, 0);
  if (!reti) {
    lat_apilar(mv, mv->objeto_verdadero);
  } else if (reti == REG_NOMATCH) {
    lat_apilar(mv, mv->objeto_falso);
  } else {
    lat_error("Linea %d, %d: %s", cadena->num_linea, cadena->num_columna,
              "error en el match regex.");
  }
  regfree(&regex);
}

void lat_cadena_match(lat_mv *mv) {
  lat_objeto *regexString = __cadena(lat_desapilar(mv));
  lat_objeto *source = __cadena(lat_desapilar(mv));
  char maxMatches = 50, maxGroups = 50;
  regex_t regexCompiled;
  regmatch_t groupArray[maxGroups];
  unsigned int m;
  char *cursor;
  if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
    lat_error("Linea %d, %d: %s", source->num_linea, source->num_columna,
              "error en el match regex.");
  };
  m = 0;
  cursor = source;
  lat_objeto *l_matches = lat_lista_nueva(mv, __lista_crear());
  for (m = 0; m < maxMatches; m++) {
    if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0))
      break; // No more matches
    unsigned int g = 0;
    unsigned int offset = 0;
    lat_objeto *l_groups = lat_lista_nueva(mv, __lista_crear());
    for (g = 0; g < maxGroups; g++) {
      if (groupArray[g].rm_so == (size_t)-1)
        break; // No more groups
      if (g == 0)
        offset = groupArray[g].rm_eo;
      char cursorCopy[strlen(cursor) + 1];
      strcpy(cursorCopy, cursor);
      cursorCopy[groupArray[g].rm_eo] = 0;
      /*printf("Match %u, Group %u: [%2u-%2u]: %s\n", m, g, groupArray[g].rm_so,
             groupArray[g].rm_eo, cursorCopy + groupArray[g].rm_so);*/
      int len = groupArray[g].rm_eo - groupArray[g].rm_so;
      if (len<=0) {
              lat_apilar(mv, mv->objeto_nulo);
              regfree(&regexCompiled);
              return;
      }
      char *str = __memoria_asignar(mv, len + 1);
      strcpy(str, cursorCopy + groupArray[g].rm_so);
      str[len] = '\0';
      __lista_agregar(__lista(l_groups), lat_cadena_nueva(mv, str));
    }
    cursor += offset;
    __lista_agregar(__lista(l_matches), l_groups);
  }
  lat_apilar(mv, l_matches);
  regfree(&regexCompiled);
}

static const lat_CReg lib_cadena[] = {
    {"esta_vacia", lat_cadena_esta_vacia, 1},
    {"longitud", lat_cadena_longitud, 1},
    {"minusculas", lat_cadena_minusculas, 1},
    {"mayusculas", lat_cadena_mayusculas, 1},
    {"quitar_espacios", lat_cadena_quitar_espacios, 1},
    {"es_numerico", lat_cadena_es_numerico, 1},
    {"es_numero", lat_cadena_es_numerico, 1},
    {"es_alfa", lat_cadena_es_alfa, 1},
    {"invertir", lat_cadena_invertir, 1},
    {"ejecutar", lat_cadena_ejecutar, 1},
    {"concatenar", lat_cadena_concatenar, 2},
    {"comparar", lat_cadena_comparar, 2},
    {"contiene", lat_cadena_contiene, 2},
    {"termina_con", lat_cadena_termina_con, 2},
    {"es_igual", lat_cadena_es_igual, 2},
    {"indice", lat_cadena_indice, 2},
    {"ultimo_indice", lat_cadena_ultimo_indice, 2},
    {"eliminar", lat_cadena_eliminar, 2},
    {"separar", lat_cadena_separar, 2},
    {"inicia_con", lat_cadena_inicia_con, 2},
    {"regex", lat_cadena_regex, 2},
    {"match", lat_cadena_match, 2},
    {"insertar", lat_cadena_insertar, 3},
    {"rellenar_izquierda", lat_cadena_rellenar_izquierda, 3},
    {"rellenar_derecha", lat_cadena_rellenar_derecha, 3},
    {"reemplazar", lat_cadena_reemplazar, 3},
    {"subcadena", lat_cadena_subcadena, 3},
    {NULL, NULL}};

void lat_importar_lib_cadena(lat_mv *mv) {
  lat_importar_lib(mv, LIB_CADENA_NAME, lib_cadena);
}
