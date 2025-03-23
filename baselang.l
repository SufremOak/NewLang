%{
#include "baselang.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

// Define tokens
"req"          { return REQ; }
"func"         { return FUNC; }
"Main"         { return MAIN; }
"io"           { return IO; }
"fs"           { return FS; }
"print"        { return PRINT; }
"exit"         { return EXIT; }
"inv"          { return INV; }
"as"           { return AS; }
"Stage"        { return STAGE; }
"Hello, World!" { return STRING; }
"\\n"          { return STRING; }
"\\0"          { return NULL_TOKEN; }
"*"            { return STAR; }
[0-9]+         { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval = strdup(yytext); return IDENTIFIER; }
"{"            { return '{'; }
"}"            { return '}'; }
"("            { return '('; }
")"            { return ')'; }
";"            { return ';'; }
[ \t]+         { /* Ignore whitespace */ }
\n             { /* Ignore newlines */ }
.              { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;
}
