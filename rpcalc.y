/* Parser for rpcalc.   -*- C -*-

   Copyright (C) 1988-1993, 1995, 1998-2015, 2018-2021 Free Software
   Foundation, Inc.

   This file is part of Bison, the GNU Compiler Compiler.

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

/* Reverse Polish Notation calculator. */

%{
  #include <stdio.h>
  #include <math.h>
  int rpcalcyylex (FILE *, FILE *);
  void rpcalcyyerror (FILE *, FILE *, char const *);
%}

%define api.value.type {double}
%define api.prefix {rpcalcyy}
%token RPCALCNUM
%lex-param {FILE * input_stream}
%lex-param {FILE * output_stream}
%parse-param {FILE * input_stream}
%parse-param {FILE * output_stream}

%% /* Grammar rules and actions follow. */

input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'      { fprintf (output_stream, "%.10g\n", $1); }
;

exp:
  RPCALCNUM
| exp exp '+'   { $$ = $1 + $2;      }
| exp exp '-'   { $$ = $1 - $2;      }
| exp exp '*'   { $$ = $1 * $2;      }
| exp exp '/'   { $$ = $1 / $2;      }
| exp exp '^'   { $$ = pow ($1, $2); }  /* Exponentiation */
| exp 'n'       { $$ = -$1;          }  /* Unary minus   */
;
%%

/* The lexical analyzer returns a double floating point
   number on the stack and the token RPCALCNUM, or the numeric code
   of the character read if not a number.  It skips all blanks
   and tabs, and returns 0 for end-of-input. */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int rpcalcyylex (FILE * input_stream, FILE * output_stream)
{
  int c = getc(input_stream);
  /* Skip white space. */
  while (c == ' ' || c == '\t')
    c = getc(input_stream);
  /* Process numbers. */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, input_stream);
      if (fscanf (input_stream, "%lf", &rpcalcyylval) != 1)
        abort ();
      return RPCALCNUM;
    }
  /* Return end-of-input. */
  else if (c == EOF)
    return RPCALCYYEOF;
  /* Return a single char. */
  else
    return c;
}

#include <stdio.h>

/* Called by rpcalcyyparse on error. */
void
rpcalcyyerror (FILE * input_stream, FILE * output_stream, char const *s)
{
  fprintf (output_stream, "%s\n", s);
}
