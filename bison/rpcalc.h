/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_RPCALCYY_BISON_RPCALC_H_INCLUDED
# define YY_RPCALCYY_BISON_RPCALC_H_INCLUDED
/* Debug traces.  */
#ifndef RPCALCYYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define RPCALCYYDEBUG 1
#  else
#   define RPCALCYYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define RPCALCYYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined RPCALCYYDEBUG */
#if RPCALCYYDEBUG
extern int rpcalcyydebug;
#endif

/* Token kinds.  */
#ifndef RPCALCYYTOKENTYPE
# define RPCALCYYTOKENTYPE
  enum rpcalcyytokentype
  {
    RPCALCYYEMPTY = -2,
    RPCALCYYEOF = 0,               /* "end of file"  */
    RPCALCYYerror = 256,           /* error  */
    RPCALCYYUNDEF = 257,           /* "invalid token"  */
    RPCALCNUM = 258                /* RPCALCNUM  */
  };
  typedef enum rpcalcyytokentype rpcalcyytoken_kind_t;
#endif

/* Value type.  */
#if ! defined RPCALCYYSTYPE && ! defined RPCALCYYSTYPE_IS_DECLARED
typedef double RPCALCYYSTYPE;
# define RPCALCYYSTYPE_IS_TRIVIAL 1
# define RPCALCYYSTYPE_IS_DECLARED 1
#endif


extern RPCALCYYSTYPE rpcalcyylval;


int rpcalcyyparse (FILE * input_stream, FILE * output_stream);


#endif /* !YY_RPCALCYY_BISON_RPCALC_H_INCLUDED  */
