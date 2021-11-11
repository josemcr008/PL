/*!
  \file interpreter.l
  \brief Lexical or scanner file
*/
%{
#include <iostream>

/*********************/
/* NEW in example 4 */
/* atof */
#include <stdlib.h>
#include <string>
/*********************/

/* Macros for the screen */
#include "../includes/macros.hpp"

/*********************/
/*
  NEW in example 16
  AST class
  IMPORTANT: must be written before interpreter.tab.h
*/
#include "../ast/ast.hpp"
/*********************/

/*  interpreter.tab.h contains the numeric values of the tokens produced by the parser */
#include "interpreter.tab.h"

/********************/
/* NEW in example 3 */
#include "../error/error.hpp"
/********************/


/*********************************************/
/* NEW in example 7 */
/* Table of symbols */
#include "../table/table.hpp"

#include "../table/numericVariable.hpp"

extern lp::Table table; //!< External Table of Symbols
/*********************************************/

extern int lineNumber; //!< External line counter

using namespace std;
%}


/*! \name REGULAR DEFINITIONS  */

DIGIT  [0-9]

LETTER [a-zA-Z]

NUMBER {DIGIT}+(\.{DIGIT}+)?([Ee][+|-]?{DIGIT}+)?

IDENTIFIER  {LETTER}({LETTER}|{DIGIT}|"_"({LETTER}|{DIGIT}))*

ERRORID1 {IDENTIFIER}"_"
ERRORID2 {DIGIT}{IDENTIFIER}
ERRORID3	"_"{IDENTIFIER}
ERRORID4	 {LETTER}({LETTER}|{DIGIT}|"__"({LETTER}|{DIGIT}))*

SIMBOL  ("$"|"&")

CADENA	 "'"([^']|"\\\'")*"'"

COMENTARIO_VARIAS 	<<([^(>>)])*>>

COMENTARIO_UNA	@([^(\n)])*



/* NEW in example 3 */
/* STATE  */
%x ERROR

/*! \name REGULAR EXPRESSIONS  */
%%

[ \t] 	{ ; }    /* skip white space and tabular */

\n      {
			/* Line counter */
           	lineNumber++;

			/* MODIFIED in example 3 */
			/* COMMENTED in example 5 */
        	/* return NEWLINE; */
        }

";"		{
			/* NEW in example 5 */
			return SEMICOLON;
		}

":" {
      return COLON;
    }


","		{
			/* NEW in example 14 */
			return COMMA;
		}

{NUMBER}  {
					  /* MODIFIED in example 4 */
					  /* Conversion of type and sending of the numerical value to the parser */
					   yylval.number = atof(yytext);

                       return NUMBER;
                      }
{CADENA}			{
            std::string aux= strdup(yytext);
            aux=aux.substr ( 1, aux.size()-2 );
            char* aux2 = strcpy(new char[aux.length() + 1], aux.c_str());          //  yylval.cadena =  aux;
            yylval.cadena = aux2;

						return CADENA;
			}

{IDENTIFIER}   		 {
						for(int i = 0; yytext[i]!='\0'; i++){
							yytext[i] = tolower(yytext[i]);
						}
						 /* NEW in example 7 */
						 std::string identifier(yytext);

						/*
                          strdup() function returns a pointer to a new string
                          which  is a duplicate of the string yytext
                        */
						  yylval.identifier =  strdup(yytext);

						/* If the identifier is not in the table of symbols then it is inserted */
						 if (table.lookupSymbol(identifier) == false)
							{
								/*
								 The identifier is inserted into the symbol table
								 as undefined Variable with value 0.0
								*/

								lp::NumericVariable *n = new lp::NumericVariable(identifier,VARIABLE,UNDEFINED,0.0);



								/* A pointer to the new NumericVariable is inserted into the table of symbols */
								table.installSymbol(n);

								return VARIABLE;
							}

						/* MODIFIED in example 11 */
						/*
							If the identifier is in the table of symbols then its token is returned
								The identifier can be a variable or a numeric constant
						*/
						else
							{
								lp::Symbol	*s = table.getSymbol(identifier);

/*
								std::cout << "lex: "<< s->getName()
										  << "token " << s->getToken()
  										  << std::endl;
*/

								/*  If the identifier is in the table then its token is returned  */
								return s->getToken();
							}
                     }


{COMENTARIO_VARIAS} {printf("Encontrado comentario de varias lineas\n") ;}

{COMENTARIO_UNA}	{printf("Encontrado comentario de una linea\n");}

{ERRORID1} {printf("Error en el identificador %s.\nEl identificador no puede acabar en '_'\n",yytext);}
{ERRORID2} {printf("Error en el identificador %s.\nEl identificador no puede empezar en numero.\n",yytext);}
{ERRORID3} {printf("Error en el identificador %s. \nEl identificador no puede empezar en '_'.\n",yytext);}
{ERRORID4} {printf("Error en el identificador %s\nEl identificador no puede contener dos '_' seguidas.\n",yytext);}


{SIMBOL}    {printf("Simbolo no permitido %s\n", yytext);}

"-"		{ return MINUS;  } 			/* NEW in example 3 */
"+"		{ return PLUS;   } 			/* NEW in example 3 */
"++"  {return PLUS_UNO;}

"*"	    { return MULTIPLICATION; } 	/* NEW in example 3 */
"/"     { return DIVISION; } 		/* NEW in example 3 */
"#div"	{ return DIVENTERA;}

"("     { return LPAREN; } 			/* NEW in example 3 */
")"	    { return RPAREN; } 			/* NEW in example 3 */



"#mod"     { return MODULO; }			/* NEW in example 5 */

":=" 	{ return ASSIGNMENT; }		/* NEW in example 7 */

"**"	{return POTENCIA;}

"^"	{ 	printf("Error: Quizas queria poner '**'\n");
			return 0; }		/* NEW in example 15 */


"="	{ return EQUAL; }			/* NEW in example 15 */

"=="	{ 	printf("Error: Quizas queria poner '<>'\n");
			return 0; }		/* NEW in example 15 */

"<>"	{ return NOT_EQUAL; }		/* NEW in example 15 */

"><"	{ 	printf("Error: Quizas queria poner '<>'\n");
			return 0; }		/* NEW in example 15 */

"!="	{ 	printf("Error: Quizas queria poner '<>'\n");
			return 0; }		/* NEW in example 15 */

">="	{ return GREATER_OR_EQUAL; }/* NEW in example 15 */

"=>"	{ 	printf("Error: Quizas queria poner '>='\n");
			return 0; }		/* NEW in example 15 */

"<="	{ return LESS_OR_EQUAL; }	/* NEW in example 15 */

"=<"	{ 	printf("Error: Quizas queria poner '<='\n");
			return 0; }		/* NEW in example 15 */

">"		{ return GREATER_THAN; }	/* NEW in example 15 */

"<"		{ return LESS_THAN; }		/* NEW in example 15 */

"#no"		{ return NOT; }				/* NEW in example 15 */

"#o"	{ return OR; }				/* NEW in example 15 */

"#y"	{ return AND; }				/* NEW in example 15 */

"&&"	{ 	printf("Error: Quizas queria poner '#y'\n");
			return 0; }		/* NEW in example 15 */

"{"		{ return LETFCURLYBRACKET; } 	/* NEW in example 17 */

"}"		{ return RIGHTCURLYBRACKET; }	/* NEW in example 17 */

"#borrar" {	return BORRAR;  }


"#lugar"  {return LUGAR;}

"||"	{return CONCAT;}



^# { /* The interpreter finishes when the symbol # is written at the beginning of the line */
	//  PLACE(24,10);
  	  std::cout <<  BIYELLOW;
   	  std::cout <<  ">>>>>>> End of program <<<<<<<";
 	  std::cout << std::endl;
   	  std::cout << RESET;
	 //PLACE(25,1);

  	  return 0;
	}


<<EOF>> { /* The interpreter finishes when finds the end of file character */
		/*  PLACE(24,10);
	  	  std::cout <<  BICYAN;
	   	  std::cout <<  ">>>>>>> End of file <<<<<<<";
	 	  std::cout << std::endl;
	   	  std::cout << RESET;
		  PLACE(25,1);
		*/
	  	  return 0;
	}


.								{
									/* Any other character */
									/* MODIFIIED in example 3 */
									/* Change to error state */
									BEGIN(ERROR);

									/*
										The current value of yytext
										will be concatenated with the next character
									*/
									yymore();
								}

<ERROR>[^0-9+\-*/()\^% \t\n\;a-zA-Z=<>!&]	{ /* MODIFIED in examples 5, 7, 15 */
								  /* NEW in example 3 */
								  /*
									The current value of yytext
									will be concatenated with the next character
								  */
									yymore();
								}

<ERROR>(.|\n)                {
								/* NEW in example 3 */
								/* Rewind one position */
								yyless(yyleng-1);

								/* Display the error message */
								warning("Lexical error", yytext);

								/* Restore the initial state */
   								BEGIN(INITIAL);
							}
%%
