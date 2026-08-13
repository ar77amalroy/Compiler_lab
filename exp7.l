%{
#include "y.tab.h"
%}

%%

"int"       { return KEYWORD; }
"float"     { return KEYWORD; }
"double"    { return KEYWORD; }

[a-zA-Z_][a-zA-Z0-9_]*   { return IDENTIFIER; }

[ \t\n]+    ;

.           { return INVALID; }

%%
