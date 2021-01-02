/******************************************************************************
 * Copyright (c) 2019 Lenguaje-Latino, programación con sintaxis al Español.  *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the              *
 * "Software"), to deal in the Software without restriction, including        *
 * without limitation the rights to use, copy, modify, merge, publish,        *
 * distribute, distribute with modifications, sublicense, and/or sell         *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included    *
 * in all copies or substantial portions of the Software.                     *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS    *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                 *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.     *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,     *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR      *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                 *
 *                                                                            *
 * Except as contained in this notice, the name(s) of the above copyright     *
 * holders shall not be used in advertising or otherwise to promote the       *
 * sale, use or other dealings in this Software without prior written         *
 * authorization.                                                             *
 *****************************************************************************/

/******************************************************************************
 *     Author: Melvin Guerrero <melving24@gmail.com>                2019-on   *
 *    Website: Manual Latino   <https://manuallatino.blogspot.com>  2018-2020 *
 *             GitHub Oficial  <https://github.com/lenguaje-latino> 2015-on   *
 *                                                                            *
 *       Desc: Curses library for Lenguaje-Latino                             *
 *                                                                            *
 *  Curses API <https://invisible-island.net/ncurses/man/ncurses.3x.html>     *
 *****************************************************************************/

#if (defined __WIN32__) || (defined _WIN32)
#include "PDCursesMod\curses.h"
#else
#include <curses.h>
#endif

#include "..\include\latcompat.h"
#include "latino.h"
// #include "latobj.h"

#define LIB_CURSES_NAME "curses"

// /* Definiciones */

// Atributos
#define NORMAL     A_NORMAL
#define RESALTAR   A_STANDOUT
#define SUBRAYAR   A_UNDERLINE
#define AL_REVES   A_REVERSE
#define PARPADEO   A_BLINK
#define OSCURO     A_DIM
#define NEGRITAS   A_BOLD
#define PROTEGER   A_PROTECT
#define INVISIBLE  A_INVIS
#define ALTERNAR   A_ALTCHARSET
#define TEXTO      A_CHARTEXT
#define COLOR      A_COLOR

#if 1
#define ITALICA    A_ITALIC
#endif

//Colores
#define NEGRO      COLOR_BLACK
#define ROJO       COLOR_RED
#define VERDE      COLOR_GREEN
#define AZUL       COLOR_BLUE
#define MAGENTA    COLOR_MAGENTA
#define CIAN       COLOR_CYAN
#define BLANCO     COLOR_WHITE

#define atributoson(r) attron(r)

//****** LISTA DE FUNCIONES

// CURS_ADD_WCH
// CURS_ADDCH
// CURS_ATTR
static void cur_attr_get(lat_mv *mv) {}
static void cur_wattr_get(lat_mv *mv) {}
static void cur_attr_set(lat_mv *mv) {}
static void cur_wattr_set(lat_mv *mv) {}
static void cur_attr_off(lat_mv *mv) {}
static void cur_wattr_off(lat_mv *mv) {}
static void cur_attr_on(lat_mv *mv) {}
static void cur_wattr_on(lat_mv *mv) {}
static void cur_attroff(lat_mv *mv) {
    int *num = latC_tope(mv);
    lat_objeto *o = latC_desapilar(mv);
    printw("%s", num);
    char *atr = latC_checar_cadena(mv, o);
    if (strcmp(atr, "A_NORMAL") == 0 || strcmp(atr, "NORMAL") == 0) {
        attroff(A_NORMAL);
    } else if (strcmp(atr, "A_STANDOUT") == 0 || strcmp(atr, "RESALTAR") == 0) {
        attroff(A_STANDOUT);
    } else if (strcmp(atr, "A_UNDERLINE") == 0 || strcmp(atr, "SUBRAYAR") == 0) {
        attroff(A_UNDERLINE);
    } else if (strcmp(atr, "A_REVERSE") == 0 || strcmp(atr, "AL_REVES") == 0) {
        attroff(A_REVERSE);
    } else if (strcmp(atr, "A_BLINK") == 0 || strcmp(atr, "PARPADEO") == 0) {
        attroff(A_BLINK);
    } else if (strcmp(atr, "A_DIM") == 0 || strcmp(atr, "OSCURO") == 0) {
        attroff(A_DIM);
    } else if (strcmp(atr, "A_BOLD") == 0 || strcmp(atr, "NEGRITAS") == 0) {
        attroff(A_BOLD);
    } else if (strcmp(atr, "A_PROTECT") == 0 || strcmp(atr, "PROTEGER") == 0) {
        attroff(A_PROTECT);
    } else if (strcmp(atr, "A_INVIS") == 0 || strcmp(atr, "INVISIBLE") == 0) {
        attroff(A_INVIS);
    } else if (strcmp(atr, "A_ALTCHARSET") == 0 || strcmp(atr, "ALTERNAR") == 0) {
        attroff(A_ALTCHARSET);
    } else if (strcmp(atr, "A_CHARTEXT") == 0 || strcmp(atr, "TEXTO") == 0) {
        attroff(A_CHARTEXT);
    } else if (strcmp(atr, "A_COLOR") == 0 || strcmp(atr, "COLOR") == 0) {
        attroff(A_COLOR);
    } else {
        attroff(A_NORMAL);
    }
    /*
    for (int x=0; x < 24; x++) {
        if (strcmp(atributosLista[x], atr)==0) {
            if (x>12) {
                x=x-12;
                char *atributo = latC_astring(mv, atributosLista[x]);
                attroff(atributo);
                break;
            } else {
                char *atributo = latC_astring(mv, atributosLista[x]);
                attroff(atributo);
                break;
            }
        }
    }
    */
}
static void cur_wattroff(lat_mv *mv) {}
static void cur_attron(lat_mv *mv) {
    lat_objeto *at = latC_desapilar(mv);
    chtype atrs = (chtype)latC_checar_cadena(mv, at);
    //int atrs = latC_checar_numerico(mv, at);
    //int atrs = (int)latC_adouble(mv, at);
    //char *atrs = latC_checar_cadena(mv, at);
    atributoson(atrs);
}
static void cur_wattron(lat_mv *mv) {}
static void cur_attrset(lat_mv *mv) {}
static void cur_wattrset(lat_mv *mv) {}
static void cur_chgat(lat_mv *mv) {}
static void cur_wchgat(lat_mv *mv) {}
static void cur_mvchgat(lat_mv *mv) {}
static void cur_mvwchgat(lat_mv *mv) {}
static void cur_color_set(lat_mv *mv) {}
static void cur_wcolor_set(lat_mv *mv) {}
static void cur_standend(lat_mv *mv) {}
static void cur_wstandend(lat_mv *mv) {}
static void cur_standout(lat_mv *mv) {}
static void cur_wstandout(lat_mv *mv) {}

// CURS_BEEP
static void cur_beep(lat_mv *mv) { beep(); }
static void cur_flash(lat_mv *mv) { flash(); }

// CURS_BKGD
// static void cur_bkgdset(lat_mv *mv){bkgdset(<#chtype#>);}
// static void cur_wbkgdset(lat_mv *mv){wbkgdset(<#WINDOW *#>, <#chtype#>);}
// static void cur_bkgd(lat_mv *mv){bkgd(<#chtype#>);}
// static void cur_wbkgd(lat_mv *mv){wbkgd(<#WINDOW *#>, <#chtype#>);}
// static void cur_getbkgd(lat_mv *mv){getbkgd(<#WINDOW *#>);}

// CURS_BKGRND -- para borrar
// static void cur_bkgrnd(lat_mv *mv){bkgrnd();}
// static void cur_wbkgrnd(lat_mv *mv){wbkgrn();}

// CURS_BORDER
// static void cur_border(lat_mv *mv){border(<#chtype#>, <#chtype#>, <#chtype#>,
// <#chtype#>, <#chtype#>, <#chtype#>, <#chtype#>, <#chtype#>);}
static void cur_wborder(lat_mv *mv) {
    lat_objeto *br = latC_desapilar(mv);
    lat_objeto *bl = latC_desapilar(mv);
    lat_objeto *tr = latC_desapilar(mv);
    lat_objeto *tl = latC_desapilar(mv);
    lat_objeto *bs = latC_desapilar(mv);
    lat_objeto *ts = latC_desapilar(mv);
    lat_objeto *rs = latC_desapilar(mv);
    lat_objeto *ls = latC_desapilar(mv);
    lat_objeto *vent = latC_desapilar(mv);
    int brc = (int)latC_adouble(mv, br);
    int blc = (int)latC_adouble(mv, bl);
    int trc = (int)latC_adouble(mv, tr);
    int tlc = (int)latC_adouble(mv, tl);
    int bm = (int)latC_adouble(mv, bs);
    int tp = (int)latC_adouble(mv, ts);
    int rg = (int)latC_adouble(mv, rs);
    int lf = (int)latC_adouble(mv, ls);
    WINDOW *ventana = (WINDOW *)latC_checar_cptr(mv, vent);
    wborder(ventana, lf, rg, tp, bm, tlc, trc, blc, brc);
}
static void cur_caja(lat_mv *mv) {
    lat_objeto *hor = latC_desapilar(mv);
    lat_objeto *ver = latC_desapilar(mv);
    lat_objeto *vent = latC_desapilar(mv);
    int h = (int)latC_adouble(mv, hor);
    int v = (int)latC_adouble(mv, ver);
    WINDOW *ventana = (WINDOW *)latC_checar_cptr(mv, vent);
    box(ventana, v, h);
}
// static void cur_hline(lat_mv *mv){hline(<#chtype#>, <#int#>)}
// static void cur_whline(lat_mv *mv){whline(<#WINDOW *#>, <#chtype#>,
// <#int#>);} static void cur_vline(lat_mv *mv){vline(<#chtype#>, <#int#>);}
// static void cur_wvline(lat_mv *mv){wvline(<#WINDOW *#>, <#chtype#>,
// <#int#>);} static void cur_mvhline(lat_mv *mv){mvhline(<#int#>, <#int#>,
// <#chtype#>, <#int#>);} static void cur_mvwhline(lat_mv *mv){mvwhline(<#WINDOW
// *#>, <#int#>, <#int#>, <#chtype#>, <#int#>);} static void cur_mvvline(lat_mv
// *mv){mvvline(<#int#>, <#int#>, <#chtype#>, <#int#>);} static void
// cur_mvwvline(lat_mv *mv){mvwvline(<#WINDOW *#>, <#int#>, <#int#>, <#chtype#>,
// <#int#>);}

// CURS_BORDER_SET -- para borrar
// static void cur_borderset(lat_mv *mv) { border_set }

// CURS_CLEAR
static void cur_limpiar(lat_mv *mv) { clear(); }

// CURS_COLOR
static void cur_startcolor(lat_mv *mv) {
    if (!has_colors()) {
        printw("Su terminal no soporta colores");
        // getch();
    }
    start_color();
}
// static void cur_hascolor(lat_mv *mv){has_colors();}
static void cur_canchangecolor(lat_mv *mv) { can_change_color(); }
static void cur_initpair(lat_mv *mv) {
    lat_objeto *uc = latC_desapilar(mv);
    lat_objeto *pc = latC_desapilar(mv);
    lat_objeto *n = latC_desapilar(mv);
    char *ucolor = latC_checar_cadena(mv, uc);
    char *pcolor = latC_checar_cadena(mv, pc);
    int numero = latC_checar_numerico(mv, n);
    init_pair(numero, pcolor, ucolor);
}
// static void cur_initcolor(lat_mv *mv){init_color(<#short#>, <#short#>,
// <#short#>, <#short#>);} static void cur_colorcontent(lat_mv
// *mv){color_content(<#short#>, <#short *#>, <#short *#>, <#short *#>);} static
// void cur_paircontent(lat_mv *mv){pair_content(<#short#>, <#short *#>, <#short
// *#>);}
static void cur_colorpair(lat_mv *mv) {
    lat_objeto *i = latC_desapilar(mv);
    int numero = latC_checar_numerico(mv, i);
    COLOR_PAIR(numero);
}
// static void cur_pairnumber(lat_mv *mv){PAIR_NUMBER(<#a#>);}
/*static void cur_color(lat_mv *mv){
 lat_objeto *color = latC_desapilar(mv);
 char *c = latC_checar_cadena(mv, color);
*/

// CURS_DELCH
// CURS_DELETELN
// CURS_EXTEND
// CURS_GET_WCH
// CURS_GET_WSTR
// CURS_GETCCHAR
// CURS_GETCH
static void cur_tomarcaracter(lat_mv *mv) {
    // int c = getch();
    int c = "\0";
    sleep_ms(5000);
    latC_apilar_double(mv, c);
}

// CURS_GETYX
// CURS_INITSCR
// static void cur_nuevaterm(lat_mv *mv){newterm(char *, file *, file *);};
static void cur_iniciarpantalla(lat_mv *mv) { initscr(); }
static void cur_salirpantalla(lat_mv *mv) { endwin(); }

// CURS_INOPTS
static void cur_cpausa(lat_mv *mv) { cbreak(); }
static void cur_nocbreak(lat_mv *mv) { nocbreak(); }
static void cur_crudo(lat_mv *mv) { raw(); };
static void cur_eco(lat_mv *mv) { echo(); }
static void cur_noeco(lat_mv *mv) { noecho(); }
// static void cur_teclado(lat_mv *mv) { keypad(stdscr, TRUE); };
static void cur_mediotiempo(lat_mv *mv) {
    lat_objeto *mTiempo = latC_desapilar(mv);
    double tiempo = latC_checar_numerico(mv, mTiempo);
    halfdelay(tiempo);
};

// CURS_KERNEL
// CURS_LEGACY
// CURS_MOUSE
// CURS_MOVE
static void cur_mover(lat_mv *mv) {
    lat_objeto *xx = latC_desapilar(mv);
    lat_objeto *yy = latC_desapilar(mv);
    int x = latC_checar_numerico(mv, xx);
    int y = latC_checar_numerico(mv, yy);
    move(y, x);
}
static void cur_movervent(lat_mv *mv) {
    lat_objeto *xx = latC_desapilar(mv);
    lat_objeto *yy = latC_desapilar(mv);
    lat_objeto *vent = latC_desapilar(mv);
    int x = latC_checar_numerico(mv, xx);
    int y = latC_checar_numerico(mv, yy);
    WINDOW *ventana = (WINDOW *)latC_checar_cptr(mv, vent);
    wmove(ventana, y, x);
}

// CURS_OUTOPTS
// CURS_OVERLAY
// CURS_PRINTW
static void cur_imprimir(lat_mv *mv) {
    lat_objeto *cadena = latC_desapilar(mv);
    char *tmpdato = latC_astring(mv, cadena);
    printw("%s", tmpdato);
}
static void cur_ventimprimir(lat_mv *mv) {
    lat_objeto *cdn = latC_desapilar(mv);
    lat_objeto *vent = latC_desapilar(mv);
    char *cadena = latC_checar_cadena(mv, cdn);
    WINDOW *ventana = (WINDOW *)latC_checar_cptr(mv, vent);
    wprintw(ventana, "%s", cadena);
}
static void cur_mvimprimir(lat_mv *mv) {
    lat_objeto *cdn = latC_desapilar(mv);
    lat_objeto *xx = latC_desapilar(mv);
    lat_objeto *yy = latC_desapilar(mv);
    char *cadena = latC_astring(mv, cdn);
    int x = latC_checar_numerico(mv, xx);
    int y = latC_checar_numerico(mv, yy);
    mvprintw(y, x, "%s", cadena);
}
static void cur_mvventimprimir(lat_mv *mv) {
    lat_objeto *cdn = latC_desapilar(mv);
    lat_objeto *xx = latC_desapilar(mv);
    lat_objeto *yy = latC_desapilar(mv);
    lat_objeto *vent = latC_desapilar(mv);
    char *cadena = latC_checar_cadena(mv, cdn);
    int x = latC_checar_numerico(mv, xx);
    int y = latC_checar_numerico(mv, yy);
    WINDOW *ventana = (WINDOW *)latC_checar_cptr(mv, vent);
    mvwprintw(ventana, y, x, "%s", cadena);
}
// static void cur_vw_printw(lat_mv *mv) { vw_printw(win, cadena, FUNCION_VAR_ARGS); }

// CURS_REFRESH
static void cur_refrescar(lat_mv *mv) { refresh(); }
static void cur_refrescarvent(lat_mv *mv) {
    lat_objeto *vent = latC_desapilar(mv);
    WINDOW *ventana = (WINDOW *)latC_checar_cptr(mv, vent);
    wrefresh(ventana);
}

// CURS_SLK
// CURS_TERMATTRS
static void cur_velocidadtransmision(lat_mv *mv) { baudrate(); }
static void cur_borrarchar(lat_mv *mv) { erasechar(); }
//static void cur_erasewchar(lat_mv *mv){erasewchar(char * ch);}
static void cur_has_ic(lat_mv *mv) { has_ic(); }
static void cur_has_il(lat_mv *mv) { has_il(); }
static void cur_killchar(lat_mv *mv) { killchar(); }
//static void cur_killwchar(lat_mv *mv){killwchar(char * ch);}
static void cur_longname(lat_mv *mv) { longname(); }
//static void cur_term_attrs(lat_mv *mv){term_attrs();}
static void cur_termattrs(lat_mv *mv) { termattrs(); }
static void cur_termname(lat_mv *mv) { termname(); }

// CURS_TERMINFO
// CURS_UTIL
// CURS_WINDOW
static void cur_ventana(lat_mv *mv) {
    lat_objeto *cxx = latC_desapilar(mv);
    lat_objeto *cyy = latC_desapilar(mv);
    lat_objeto *wancho = latC_desapilar(mv);
    lat_objeto *walto = latC_desapilar(mv);
    double cx = latC_checar_numerico(mv, cxx);
    double cy = latC_checar_numerico(mv, cyy);
    double wan = latC_checar_numerico(mv, wancho);
    double wal = latC_checar_numerico(mv, walto);
    WINDOW *ventana = newwin(wal, wan, cy, cx);
    lat_objeto *vent = latC_crear_cdato(mv, ventana);
    latC_apilar(mv, vent);
}

// DEFINE_KEY
// NEW_PAIR

//****** FIN DE LAS FUNCIONES

//****** LISTA DE COMANDOS
static const lat_CReg libcurses[] = {
    // CURS_ADD_WCH
    // CURS_ADDCH
    // CURS_ATTR
    {"atrion", cur_attron, 1},                      {"attron", cur_attron,1},
    {"atrioff", cur_attroff, 1},                    {"attroff", cur_attroff,1},

    // 	//CURS_BEEP
    {"beep", cur_beep, 0},
    {"flash", cur_flash, 0},

    // CURS_BKGD
    // CURS_BKGRND -- para borrar
    // CURS_BORDER
    {"caja", cur_caja, 3},                          {"box", cur_caja, 3},
    {"bordevent", cur_wborder, 9},                  {"wborder", cur_wborder, 9},

    // CURS_BORDER_SET -- para borrar
    // CURS_CLEAR
    {"limpiar", cur_limpiar, 0},                    {"clear", cur_limpiar, 0},

    // CURS_COLOR
    {"inicolor", cur_startcolor,0},                 {"start_color", cur_startcolor, 0},
    {"pintura", cur_initpair, 3},                   {"init_pair", cur_initpair, 3},
    {"COLORIDO", cur_colorpair,1},                  {"COLOR_PAIR", cur_colorpair,1},
    // {"color", cur_color, 1},

    // CURS_DELCH
    // CURS_DELETELN
    // CURS_EXTEND
    // CURS_GET_WCH
    // CURS_GET_WSTR
    // CURS_GETCCHAR
    // CURS_GETCH
    {"leer", cur_tomarcaracter, 0},                 {"getch", cur_tomarcaracter, 0},

    // CURS_GETYX
    // CURS_INITSCR
    // {"nuevaterm", cur_nuevaterm, 3},                {"newterm", cur_nuevaterm, 3},
    {"iniciarpantalla", cur_iniciarpantalla, 0},    {"initscr", cur_iniciarpantalla, 0},
    {"finpantalla", cur_salirpantalla, 0},          {"endwin", cur_salirpantalla, 0},

    // CURS_INOPTS
    {"crudo", cur_crudo, 0},                        {"raw", cur_crudo, 0},
    {"pausa", cur_cpausa, 0},                       {"cbreak", cur_cpausa, 0},
    {"eco", cur_eco, 0},                            {"echo", cur_eco, 0},
    {"noeco", cur_noeco, 0},                        {"noecho", cur_noeco, 0},
    // {"teclado", cur_teclado, 2},                    {"keypad", cur_teclado, 2},
    {"mediotiempo", cur_mediotiempo, 1},            {"halfdelay", cur_mediotiempo, 1},

    // CURS_KERNEL
    // CURS_LEGACY
    // CURS_MOUSE
    // CURS_MOVE
    {"mover", cur_mover, 2},                        {"move", cur_mover, 2},
    {"movervent", cur_movervent, 3},                {"wmove", cur_movervent, 3},

    // CURS_OUTOPTS
    // CURS_OVERLAY
    // CURS_PRINTW
    {"imprimir", cur_imprimir, 1},                  {"printw", cur_imprimir, 1},
    {"imprimirvent", cur_ventimprimir, 2},          {"wprintw", cur_ventimprimir, 2},
    {"imprimirmv", cur_mvimprimir, 3},              {"mvprintw", cur_mvimprimir, 3},
    {"imprimirmvvent", cur_mvventimprimir, 4},      {"mvwprintw", cur_mvventimprimir, 4},

    // CURS_REFRESH
    {"refrescar", cur_refrescar, 0},                {"refresh", cur_refrescar, 0},
    {"refrescarvent", cur_refrescarvent, 1},        {"wrefresh", cur_refrescarvent, 1},

    // CURS_SLK
    // CURS_TERMATTRS
    {"vtransmision", cur_velocidadtransmision, 0},  {"baudrate", cur_velocidadtransmision, 0},

    // CURS_TERMINFO
    // CURS_UTIL
    // CURS_WINDOW
    {"ventana", cur_ventana,4},                     {"newwin", cur_ventana, 4},

    // DEFINE_KEY
    // NEW_PAIR

    // PROPIEDADES
    {"A_NORMAL", A_NORMAL},
    {"A_RESALTAR", A_STANDOUT},
    {"A_SUBRAYAR", A_UNDERLINE},

    {NULL, NULL, 0}};

//****** FIN DE COMANDOS

//****** INVOCACION DE LIBRERIA
void latC_abrir_liblatino_curseslib(lat_mv *mv) {
    latC_abrir_liblatino(mv, LIB_CURSES_NAME, libcurses);
}
