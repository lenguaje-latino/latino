/*
The MIT License (MIT)

Copyright (c) Latino - Lenguaje de Programacion

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

#include "latino.h"

#define LIB_UI_NAME "ui"

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

static void ui_winProc(lat_mv *mv) {
    // lat_objeto *l = latC_desapilar(mv);
    // lat_objeto *k = latC_desapilar(mv);
    // lat_objeto *j = latC_desapilar(mv);
    // lat_objeto *i = latC_desapilar(mv);
    // lat_objeto *h = latC_desapilar(mv);
    // lat_objeto *g = latC_desapilar(mv);
    // lat_objeto *f = latC_desapilar(mv);
    // lat_objeto *e = latC_desapilar(mv);
    // lat_objeto *d = latC_desapilar(mv);
    // lat_objeto *c = latC_desapilar(mv);
    // lat_objeto *b = latC_desapilar(mv);
    // lat_objeto *a = latC_desapilar(mv);
    // int *lpParam        = (int)latC_checar_numerico(mv, l);
    // int *hInstance      = (int)latC_checar_numerico(mv, k);
    // int *hMenu          = (int)latC_checar_numerico(mv, j);
    // int *hWndParent     = (int)latC_checar_numerico(mv, i);
    // int *nHeight        = (int)latC_checar_numerico(mv, h);
    // int *nWidth         = (int)latC_checar_numerico(mv, g);
    // int *y              = (int)latC_checar_numerico(mv, f);
    // int *x              = (int)latC_checar_numerico(mv, e);
    // int *dwStyle        = (int)latC_checar_numerico(mv, d);
    // char *lpWindowName  = latC_checar_cadena(mv, b);
    // int *lpClassName    = (int)latC_checar_numerico(mv, a);

    // HWND hwnd = CreateWindowEx(0,"lpWindowName","Learn to program", WS_OVERLAPPEDWINDOW,
    // CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    // NULL, NULL, 3, NULL);
    // if (hwnd == NULL) {
    //     return 0;
    // }
    // ShowWindow(hwnd, 5);
}

//Mensajes
static void ui_messagebox(lat_mv *mv) {
    // lat_objeto *d = latC_desapilar(mv);
    // lat_objeto *c = latC_desapilar(mv);
    // lat_objeto *b = latC_desapilar(mv);
    // lat_objeto *a = latC_desapilar(mv);
    // int *dd = (int)latC_checar_numerico(mv, d);
    // char *cc = latC_checar_cadena(mv, c);
    // char *bb = latC_checar_cadena(mv, b);
    // int *aa = (int)latC_checar_numerico(mv, a);
    // int m = (int)MessageBox(aa,bb,cc,dd);
    // lat_objeto *msj = latC_crear_numerico(mv, m);
    // latC_apilar(mv, msj);
}

static void ui_flash(lat_mv *mv) {
    // FlashWindow(0,true);
}

// static void ui_proc(lat_mv *mv) {
    
// }

static const lat_CReg libui[] = {
    {"ventana", ui_winProc, 0},
    {"mensaje", ui_messagebox, 4},
    {"flash", ui_flash, 0},
    {NULL, NULL}};

void latC_abrir_liblatino_uilib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_UI_NAME, libui);
}