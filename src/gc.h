/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gc.h
 * Author: primi
 *
 * Created on 8 de septiembre de 2016, 09:03 AM
 */

#ifndef _GC_H_
#define _GC_H_

#include <time.h>

#include "liblist.h"
#include "object.h"
#include "vm.h"

/**\brief Bandera habilitar o deshabilitar GC */
#define HABILITAR_GC 0

#define TIME_THIS(X)                                         \
  {                                                          \
    struct timespec ts1, ts2;                                \
    clock_gettime( CLOCK_REALTIME, &ts1 );                   \
    X;                                                       \
    clock_gettime( CLOCK_REALTIME, &ts2 );                   \
    printf( #X " demora: %f\n",                              \
      (float) ( 1.0*(1.0*ts2.tv_nsec - ts1.tv_nsec*1.0)*1e-9 \
      + 1.0*ts2.tv_sec - 1.0*ts1.tv_sec ) );                 \
  }

/** Agrega un objeto al colector de basura
  *
  * \param vm: Apuntador a Maquina Virtual
  * \param o: Objeto a agregar
  *
  */
void __colector_agregar(lat_mv* vm, lat_objeto* o);

/** Ejecuta la limpieza de objetos basura
  *
  * \param vm: Apuntador a Maquina Virtual  
  *
  */
void __colector_limpiar(lat_mv* vm);

#endif /* _GC_H_ */

