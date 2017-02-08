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

#include "latmv.h"

#ifndef _WIN32
#include<stdlib.h>

#include "hiredis.h"
#include "latino.h"
#include "latgc.h"

#define LIB_REDIS_NAME "redis"

void lat_redis_conectar(lat_mv *mv) {
        lat_objeto *puerto = lat_desapilar(mv);
        lat_objeto *servidor = lat_desapilar(mv);
        char *ip = "127.0.0.1";
        int port = 6379;
        if (puerto->tipo != T_NULL) {
                port = __numerico(puerto);
        };
        if (servidor->tipo != T_NULL) {
                ip = __cadena(servidor);
        };
        redisContext *redis;
        struct timeval timeout = {1, 500000}; // 1.5 segundos
        redis = redisConnectWithTimeout(ip, port, timeout);
        if (redis == NULL || redis->err) {
                if (redis) {
                        redisFree(redis);
                        filename = servidor->nombre_archivo;
                        lat_error("Linea %d, %d: %s", servidor->num_linea,
                        servidor->num_columna, "error en conexión.");
                } else {
                        filename = servidor->nombre_archivo;
                        lat_error("Linea %d, %d: %s", servidor->num_linea,
                        servidor->num_columna, "error en contexto redis.");
                };
        };
        //encapsulo el dato (struct) de redis
        lat_objeto *cref = lat_cdato_nuevo(mv, redis);
        lat_apilar(mv, cref);
}

void lat_redis_desconectar(lat_mv *mv) {
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisFree(conexion);
}

void lat_redis_ping(lat_mv *mv) {
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "PING");
        if (respuesta->str) {
                lat_objeto *tmp = lat_cadena_nueva(mv, strdup(respuesta->str));
                lat_apilar(mv, tmp);
        } else {
                lat_apilar(mv, mv->objeto_falso);
        }
        freeReplyObject(respuesta);
}

void lat_redis_asignar(lat_mv *mv) {
        lat_objeto *cadena = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        char *str = __cadena(cadena);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "GETSET %s %s", __cadena(hash), __cadena(cadena));
        if (!respuesta->str) {
                lat_apilar(mv, lat_cadena_nueva(mv, strdup(str)));
        } else {
                lat_apilar(mv, mv->objeto_falso);
        }
        freeReplyObject(respuesta);
}

void lat_redis_hasignar(lat_mv *mv) {
        lat_objeto *cadena = lat_desapilar(mv);
	lat_objeto *llave = lat_desapilar(mv);
	lat_objeto *hash = lat_desapilar(mv);
	lat_objeto *o = lat_desapilar(mv);
	redisContext *conexion = __cdato(o);
	redisReply *respuesta;
	respuesta = redisCommand(conexion, "HSET %s %s %s", __cadena(hash), __cadena(llave), __cadena(cadena));
	freeReplyObject(respuesta);
	if (respuesta->integer) {
		lat_apilar(mv, mv->objeto_verdadero);
	} else {
		lat_apilar(mv, mv->objeto_falso);
	};
}

void lat_redis_obtener(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "GET %s", __cadena(hash));
        lat_objeto *tmp;
        if (respuesta->str) {
                tmp = lat_cadena_nueva(mv, strdup(respuesta->str));
        } else {
                tmp = mv->objeto_nulo;
        }
        lat_apilar(mv, tmp);
        freeReplyObject(respuesta);
}

void lat_redis_hobtener(lat_mv *mv) {
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "HGET %s %s", __cadena(hash), __cadena(llave));
        lat_objeto *tmp;
        if (respuesta->str) {
                tmp = lat_cadena_nueva(mv, strdup(respuesta->str));
        } else {
                tmp = mv->objeto_nulo;
        }
        lat_apilar(mv, tmp);
        freeReplyObject(respuesta);
}

void lat_redis_borrar(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "DEL %s", __cadena(hash));
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
        freeReplyObject(respuesta);
}

void lat_redis_hborrar(lat_mv *mv) {
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "HDEL %s %s", __cadena(hash), __cadena(llave));
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
        freeReplyObject(respuesta);
}

void lat_redis_aumentar(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "INCR %s", __cadena(hash));
        if (!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_objeto *tmp = lat_numerico_nuevo(mv, (double)respuesta->integer);
                lat_apilar(mv, tmp);
        }
        freeReplyObject(respuesta);
}

void lat_redis_haumentar(lat_mv *mv) {
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "HINCRBY %s %s 1", __cadena(hash),
        __cadena(llave));
        if (!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_objeto *tmp = lat_numerico_nuevo(mv, (double)respuesta->integer);
                lat_apilar(mv, tmp);
        }
        freeReplyObject(respuesta);
}

void lat_redis_incrementar(lat_mv *mv) {
        lat_objeto *numero = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        long int numerico = __numerico(numero);
        respuesta = redisCommand(conexion, "INCRBY %s %i", __cadena(hash), numerico);
        if (!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_objeto *tmp = lat_numerico_nuevo(mv, respuesta->integer);
                lat_apilar(mv, tmp);
        }
        freeReplyObject(respuesta);
}

void lat_redis_hincrementar(lat_mv *mv) {
        lat_objeto *numero = lat_desapilar(mv);
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        long int numerico = __numerico(numero);
        respuesta = redisCommand(conexion, "HINCRBY %s %s %i", __cadena(hash),
        __cadena(llave), numerico);
        if (!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_objeto *tmp = lat_numerico_nuevo(mv, respuesta->integer);
                lat_apilar(mv, tmp);
        }
        freeReplyObject(respuesta);
}

void lat_redis_hllaves(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        lat_objeto *elementos = lat_lista_nueva(mv, __lista_crear());
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "HKEYS %s", __cadena(hash));
        if (respuesta->elements) {
                for (int i=0; i < respuesta->elements; i++) {
                        __lista_agregar(__lista(elementos), lat_cadena_nueva(mv, strdup(respuesta->element[i]->str)));
                };
                lat_apilar(mv, elementos);
        } else {
                lat_apilar(mv, mv->objeto_nulo);
        };
        freeReplyObject(respuesta);
}

void lat_redis_llaves(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        lat_objeto *elementos = lat_lista_nueva(mv, __lista_crear());
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "KEYS %s", __cadena(hash));
        if (respuesta->elements) {
                for (int i=0; i < respuesta->elements; i++) {
                        __lista_agregar(__lista(elementos), lat_cadena_nueva(mv, strdup(respuesta->element[i]->str)));
                };
                lat_apilar(mv, elementos);
        } else {
                lat_apilar(mv, mv->objeto_nulo);
        };
        freeReplyObject(respuesta);
}

void lat_redis_smiembros(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        lat_objeto *elementos = lat_lista_nueva(mv, __lista_crear());
        redisReply *respuesta;
        respuesta = redisCommand(conexion, "SMEMBERS %s", __cadena(hash));
        if (respuesta->elements) {
                for (int i=0; i < respuesta->elements ; i++) {
                        __lista_agregar(__lista(elementos), lat_cadena_nueva(mv, strdup(respuesta->element[i]->str)));
                };
                lat_apilar(mv, elementos);
        } else {
                lat_apilar(mv, mv->objeto_nulo);
        };
        freeReplyObject(respuesta);
}

void lat_redis_sagregar(lat_mv *mv) {
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "SADD %s %s", __cadena(hash), __cadena(llave));
        freeReplyObject(respuesta);
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
}

void lat_redis_sborrar(lat_mv *mv) {
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "SREM %s %s", __cadena(hash), __cadena(llave));
        freeReplyObject(respuesta);
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
}

void lat_redis_sesmiembro(lat_mv *mv) {
        lat_objeto *llave = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "SISMEMBER %s %s", __cadena(hash), __cadena(llave));
        freeReplyObject(respuesta);
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
}

void lat_redis_expirar(lat_mv *mv) {
        lat_objeto *tiempo = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        int num = __numerico(tiempo);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "EXPIRE %s %d", __cadena(hash), num);
        freeReplyObject(respuesta);
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
}

void lat_redis_adjuntar(lat_mv *mv) {
        lat_objeto *string = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "APPEND %s %s", __cadena(hash), __cadena(string));
        freeReplyObject(respuesta);
        if(!respuesta->integer) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
}

void lat_redis_setex(lat_mv *mv) {
        lat_objeto *tiempo = lat_desapilar(mv);
        lat_objeto *cadena = lat_desapilar(mv);
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        int num = __numerico(tiempo);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "SETEX %s %d %s", __cadena(hash), num, __cadena(cadena));
        freeReplyObject(respuesta);
        if(!respuesta->str) {
                lat_apilar(mv, mv->objeto_falso);
        } else {
                lat_apilar(mv, mv->objeto_verdadero);
        }
}

void lat_redis_tiempo(lat_mv *mv) {
        lat_objeto *hash = lat_desapilar(mv);
        lat_objeto *o = lat_desapilar(mv);
        redisContext *conexion = __cdato(o);
        redisReply *respuesta;
        respuesta =
        redisCommand(conexion, "TTL %s", __cadena(hash));
        freeReplyObject(respuesta);
        if(respuesta->integer) {
                if (respuesta->integer==-2) {
                        lat_apilar(mv, mv->objeto_falso);
                } else if (respuesta->integer==-1) {
                        lat_apilar(mv, mv->objeto_nulo);
                } else {
                        lat_apilar(mv, lat_numerico_nuevo(mv, respuesta->integer));
                }
        } else {
                lat_apilar(mv, lat_numerico_nuevo(mv, 0));
        }
}

static const lat_CReg lib_redis[] = {
        {"conectar", lat_redis_conectar, 2},
        {"desconectar", lat_redis_desconectar, 1},
        {"ping", lat_redis_ping, 1},
        {"asignar", lat_redis_asignar, 3},
        {"hasignar", lat_redis_hasignar, 4},
        {"obtener", lat_redis_obtener, 2},
        {"hobtener", lat_redis_hobtener, 3},
        {"borrar", lat_redis_borrar, 2},
        {"hborrar", lat_redis_hborrar, 3},
        {"aumentar", lat_redis_aumentar, 2},
        {"haumentar", lat_redis_haumentar, 3},
        {"incrementar", lat_redis_incrementar, 3},
        {"hincrementar", lat_redis_hincrementar, 4},
        {"hllaves", lat_redis_hllaves, 2},
        {"llaves", lat_redis_llaves, 2},
        {"smiembros", lat_redis_smiembros, 2},
        {"sagregar", lat_redis_sagregar, 3},
        {"sborrar", lat_redis_sborrar, 3},
        {"sesmiembro", lat_redis_sesmiembro, 3},
        {"expirar", lat_redis_expirar, 3},
        {"adjuntar", lat_redis_adjuntar, 3},
        {"setex", lat_redis_setex, 4},
        {"tiempo", lat_redis_tiempo, 2},
        {NULL, NULL}
};

#endif

void lat_importar_lib_redis(lat_mv *mv) {
        #ifndef _WIN32
        lat_importar_lib(mv, LIB_REDIS_NAME, lib_redis);
        #endif
}
