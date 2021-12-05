package condenses_lex;

%%

%class TokenizerV1
%implements Tokenizer
%public
%unicode
%line
%column

%state ESCAPE


LineTerminator=\r|\n|\r\n

ENTIER_SIMPLE=[:digit:]+
NORMAL_LETTER=[abc]
OUVRANTE=[(]
FERMANTE=[)]
ESCAPE_LETTER=\\
UNKNOWN=[^]


%%

{OUVRANTE}
	{return new Ouvrante(true);}
	
{FERMANTE}
	{return new Fermante(true);}

{ENTIER_SIMPLE}
	{return new Entier(Integer.parseInt(yytext()));}

{NORMAL_LETTER}
	{return new Lettre(yytext());}
	
{ESCAPE_LETTER}
	{yybegin(ESCAPE);}

<ESCAPE> {ENTIER_SIMPLE}
	{ yybegin(YYINITIAL); return new Entier(Integer.parseInt(yytext()));}
	
<ESCAPE> {NORMAL_LETTER}
	{ yybegin(YYINITIAL); return new Lettre(yytext());}

{LineTerminator}
	{return new Eod(yytext());}
	
{UNKNOWN}
	{return new Unknown(yytext()); }
