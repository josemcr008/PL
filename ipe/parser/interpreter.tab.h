/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    PRINT = 259,
    READ = 260,
    IF = 261,
    THEN = 262,
    ELSE = 263,
    END_IF = 264,
    WHILE = 265,
    DO = 266,
    END_WHILE = 267,
    REPETIR = 268,
    UNTIL = 269,
    FOR = 270,
    FROM = 271,
    PASS = 272,
    END_FOR = 273,
    CASE = 274,
    VALUE = 275,
    END_CASE = 276,
    LUGAR = 277,
    CASOS = 278,
    VALOR = 279,
    DEFECTO = 280,
    FIN_CASOS = 281,
    BORRAR = 282,
    COLON = 283,
    PRINTCAD = 284,
    READ_CAD = 285,
    LETFCURLYBRACKET = 286,
    RIGHTCURLYBRACKET = 287,
    ASSIGNMENT = 288,
    COMMA = 289,
    NUMBER = 290,
    CADENA = 291,
    BOOL = 292,
    VARIABLE = 293,
    UNDEFINED = 294,
    CONSTANT = 295,
    BUILTIN = 296,
    OR = 297,
    AND = 298,
    GREATER_OR_EQUAL = 299,
    LESS_OR_EQUAL = 300,
    GREATER_THAN = 301,
    LESS_THAN = 302,
    EQUAL = 303,
    NOT_EQUAL = 304,
    NOT = 305,
    PLUS = 306,
    MINUS = 307,
    CONCAT = 308,
    PLUS_UNO = 309,
    MULTIPLICATION = 310,
    DIVISION = 311,
    MODULO = 312,
    DIVENTERA = 313,
    POTENCIA = 314,
    LPAREN = 315,
    RPAREN = 316,
    UNARY = 317,
    POWER = 318
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 138 "interpreter.y" /* yacc.c:1909  */

  char * identifier; 				 /* NEW in example 7 */
  double number;
  bool logic;						 /* NEW in example 15 */
  char * cadena;
  lp::ExpNode *expNode;  			 /* NEW in example 16 */
  std::list<lp::ExpNode *>  *parameters;    // New in example 16; NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts; /* NEW in example 16 */
  lp::Statement *st;				 /* NEW in example 16 */
  lp::AST *prog;					 /* NEW in example 16 */
  lp::CasosStmt *casos;

#line 131 "interpreter.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
