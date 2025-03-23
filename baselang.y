%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void yyerror(const char *s);
int yylex(void);
FILE *yyin; // Declare yyin for file input
%}

// Token definitions
%token REQ FUNC MAIN IO FS PRINT EXIT INV AS STAGE
%token STRING NUMBER IDENTIFIER STAR NULL_TOKEN // Renamed NULL to NULL_TOKEN

%left '+' '-'
%left '*' '/'

// Grammar rules
%%
program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    req_statement
    | func_statement
    | invocation
    | print_statement
    | exit_statement
    ;

req_statement:
    REQ IDENTIFIER ';' {
        printf("Required module: %s\n", $2);
    }
    ;

func_statement:
    FUNC IDENTIFIER '(' ')' '{' statement_list '}' {
        printf("Function defined: %s\n", $2);
    }
    ;

invocation:
    INV '(' FUNC '(' IDENTIFIER ')' ')' AS STAGE '(' ')' {
        printf("Invoking function: %s\n", $4);
    }
    ;

print_statement:
    IO PRINT '(' STRING ')' ';' {
        printf("Print statement: %s\n", $3);
    }
    ;

exit_statement:
    EXIT '(' STAR NULL_TOKEN ')' ';' { // Use NULL_TOKEN here
        printf("Exiting program.\n");
        exit(0);
    }
    ;

%%

// Error handling
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
        yyin = file; // Set the input to the file
    }
    return yyparse();
}
