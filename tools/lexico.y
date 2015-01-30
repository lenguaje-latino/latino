%
int yystopparser=0;
%

%token MAIN END NOMBRECAMPO ENTERO DECIMAL LOGICO CARACTER CADENA NOMBRECAMPO T_CADENA T_LOGICO T_ENTERO T_DECIMAL T_CARACTER ASIGNADOR

%start programa

%%

programa                    : principal funciones | principal;

principal                   : MAIN '(' ')' lineascodigo END;

lineascodigo                : lineacodigo |;

lineacodigo                 : lineacodigo linea | linea;

linea                       : invocarmetodo | crearvariable | cambiarvalor | buclecondicion;

invocarmetodo               : NOMBRECAMPO '(' parametrosenvio ')';

parametrosenvio             : parenvio ',' penvio | penvio;

penvio                      : valor | NOMBRECAMPO;

valor                       : ENTERO | DECIMAL | LOGICO | CARACTER |  CADENA;

crearvariable               : tipodato NOMBRECAMPO | tipodato NOMBRECAMPO asignarvalor;

tipodato                    : T_ENTERO | T_DECIMAL | T_LOGICO | T_CARACTER | T_CADENA;

asignarvalor                : ASIGNADOR operasignacion | 
