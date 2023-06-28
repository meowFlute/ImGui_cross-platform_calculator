%code top {
  #include <assert.h>
  #include <ctype.h>  /* isdigit. */
  #include <stdio.h>  /* printf. */
  #include <stdlib.h> /* abort. */
  #include <string.h> /* strcmp. */

  int calcyylex (FILE *, FILE *);
  void calcyyerror (FILE *, FILE *, char const *);
}

%define api.header.include {"calc.h"}
%define api.prefix {calcyy}

/* Generate CALCYYSTYPE from the types used in %token and %type.  */
%define api.value.type union
%token <double> CALCNUM "number"
%type  <double> expr term fact
%lex-param {FILE * input_stream}
%lex-param {FILE * output_stream}
%parse-param {FILE * input_stream}
%parse-param {FILE * output_stream}

/* Generate the parser description file (calc.output).  */
%verbose

/* Nice error messages with details. */
%define parse.error detailed

/* Enable run-time traces (calcyydebug).  */
%define parse.trace

/* Formatting semantic values in debug traces.  */
%printer { fprintf (yyo, "%g", $$); } <double>;

%% /* The grammar follows.  */
input:
  %empty
| input line
;

line:
  '\n'
| expr '\n'  { fprintf (output_stream, "%.10g\n", $1); }
| error '\n' { yyerrok; }
;

expr:
  expr '+' term { $$ = $1 + $3; }
| expr '-' term { $$ = $1 - $3; }
| term
;

term:
  term '*' fact { $$ = $1 * $3; }
| term '/' fact { $$ = $1 / $3; }
| fact
;

fact:
  "number"
| '(' expr ')' { $$ = $2; }
;

%%

int
calcyylex (FILE * input_stream, FILE * output_stream)
{
  int c;
  
  /* Ignore white space, get first nonwhite character.  */
  while ((c = getc(input_stream)) == ' ' || c == '\t')
  {
    continue;
  }

  if (c == EOF)
  {
    return 0;
  }

  /* Char starts a number => parse the number.         */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, input_stream);
      if (fscanf (input_stream, "%lf", &calcyylval.CALCNUM) != 1)
      {
        abort ();
      }
      return CALCNUM;
    }

  /* Any other character is a token by itself.        */
  return c;
}

/* Called by calcyyparse on error.  */
void
calcyyerror (FILE * input_stream, FILE * output_stream, char const *s)
{
  fprintf (output_stream, "%s\n", s);
}
