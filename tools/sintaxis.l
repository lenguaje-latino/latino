%{
#include <stdio.h>
#include "lexico.h"
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
{ignora}*{com}({letra}|{digito}|{ignora})*                       {;}
"."                                         {return ('.');}
";"                                         {return (';');}
":"                                         {return (':');}
"["                                         {return ('[');}
"]"                                         {return (']');}
"{"                                         {return ('{');}
"}"                                         {return ('}');}
"("                                         {return ('(');}
")"                                         {return (')');}
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
"si"                                        {return SI;}
"desde"                                     {return DESDE;}
"hacer"                                     {return HACER;}
"incremento"                                {return INCREMENTO;}
"mientras"                                  {return MIENTRAS;}
"otro"                                      {return OTRO;}
"elegir"                                    {return ELEGIR;}
"caso"                                      {return CASO;}
"hasta"                                     {return HASTA;}
"cadena"                                    {return T_CADENA;}
"logico"                                    {return T_LOGICO;}
"entero"                                    {return T_ENTERO;}
"decimal"                                   {return T_DECIMAL;}
"caracter"                                  {return T_CARACTER;}

{digito}+                                   {return ENTERO;}
{digito}+"."{digito}+                       {return DECIMAL;}
{boleano}                                   {return LOGICO;}
{letra}({letra}|{digito})*                  {return NOMBRECAMPO;}
"\'"({letra}|{digito})"\'"                  {return CARACTER;}
"\""({letra}|{digito}|{ignora})*"\""        {return CADENA;}

%%

yyerror(char *msg)
{
    printf("%s\n", msg);
}

int main(int argc, char* argv[]) {
    FILE* fh = fopen( argv[1], "r" );
    char* nombre_archivo=NULL;
    //you really should not examine argv[1] if there is no argument...
    if(argc<1) {
        printf("uso: sintaxis <nombre_archivo>\n");
        exit(EXIT_FAILURE);
    }
    nombre_archivo=argv[1];
    //check that file opens successfully,
    if(!(fh=fopen(nombre_archivo,"r" ))) {
        printf("error: no se puede abrir el archivo%s\n",nombre_archivo);
        return 0;
    }
    yyin=fopen(nombre_archivo, "rt");
    if(yyin == NULL)
        printf("\nNo se puede leer el archivo");
    else
        yyparse();
    fclose(fh);
}
