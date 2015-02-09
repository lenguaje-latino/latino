%{
#include <stdio.h>
#include "y.tab.h"
int nchar, nword, nline;
int lineno;
int yylineno;
%}

%option noyywrap
%option yylineno

ignora  " "|\t\n
letra [A-Za-z]
digito [0-9]
boleano "verdadero"|"falso"
com "#"

%%
{ignora}*                                   {;}
{ignora}*{com}.*                            {;}
"."                                         {return ('.');}
";"                                         {return (';');}
":"                                         {return (':');}
"["                                         {return ('[');}
"]"                                         {return (']');}
"{"                                         {return ('{');}
"}"                                         {return ('}');}
"("                                         {return ('(');}
")"                                         {return (')');}
","                                         {return (',');}
"principal"                                 {return PRINCIPAL;}
"fin"                                       {return FIN;}
"="                                         {return ASIGNADOR;}
"+"                                         {return SUMA;}
"-"                                         {return RESTA;}
"*"                                         {return MULTIPLICACION;}
"/"                                         {return DIVISION;}
"%"                                         {return MODULO;}
">"                                         {return MAYOR;}
"<"                                         {return MENOR;}
"<="                                        {return MENORIGUAL;}
">="                                        {return MAYORIGUAL;}
"=="                                        {return IGUAL;}
"!="                                        {return NOIGUAL;}
"++"                                        {return AUMENTAR;}
"--"                                        {return DISMINUIR;}
"constante"                                 {return CONSTANTE;}
"si"                                        {return SI;}
"desde"                                     {return DESDE;}
"hacer"                                     {return HACER;}
"salto"                                     {return SALTO;}
"mientras"                                  {return MIENTRAS;}
"cuando"                                    {return CUANDO;}
"sino"                                      {return SINO;}
"elegir"                                    {return ELEGIR;}
"caso"                                      {return CASO;}
"defecto"                                   {return DEFECTO;}
"hasta"                                     {return HASTA;}
"cadena"                                    {return T_CADENA;}
"logico"                                    {return T_LOGICO;}
"entero"                                    {return T_ENTERO;}
"decimal"                                   {return T_DECIMAL;}
"caracter"                                  {return T_CARACTER;}
"continuar"                                 {return CONTINUAR;}
"romper"                                    {return ROMPER;}
"funcion"                                   {return FUNCION;}
"clase"                                     {return CLASE;}
"propiedad"                                 {return PROPIEDAD;}
"esta"                                      {return ESTA;}
"constructor"                               {return CONSTRUCTOR;}
"retorno"                                   {return RETORNO;}

{digito}+|"-"{digito}+                      {return ENTERO;}
{digito}+"."{digito}+                       {return DECIMAL;}
{boleano}                                   {return LOGICO;}
({letra}|"_")({letra}|{digito}|"_")*                  {return NOMBRECAMPO;}
"\'"({letra}|{digito})"\'"                  {return CARACTER;}
"\""({letra}|{digito}|{ignora})*"\""        {return CADENA;}

%%

