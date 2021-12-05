package jadelex;
import jade.Direction;

%%

%class TokenizerV1
%implements Tokenizer
%public
%unicode
%line
%column

%{
  private int lastInt = 0 ;
%}


%state STEP
%state JUMP1
%state JUMP2
%state REPEAT

PENON=baisser
PENOFF=lever

LineTerminator=\r|\n|\r\n
InputCharacter=[^\r\n]
WHITESPACE=[\R|[\t\f]|[\s]]

Comment={TraditionalComment}|{EndOfLineComment}|{DocumentationComment}
TraditionalComment="/*"[^*]~"*/"|"/*""*"+"/"
EndOfLineComment="//"{InputCharacter}*{LineTerminator}?
DocumentationComment="/**"{CommentContent}"*"+"/"
CommentContent=([^*]|\*+[^/*])*

EAST=est
NORTH=nord
WEST=ouest
SOUTH=sud

PAS=pas

MOVE=aller

FOIS=fois

ENTIER_SIMPLE=[:digit:]+

%%

{PENON}
	{return new PenMode(true);}
	
{PENOFF}
	{return new PenMode(false);}

{EAST}
	{return new Move(Direction.EAST);}

{NORTH}
	{return new Move(Direction.NORTH);}

{WEST}
	{return new Move(Direction.WEST);}

{SOUTH}
	{return new Move(Direction.SOUTH);}

{LineTerminator}
	{}
	
{Comment}
	{}
	
<YYINITIAL,STEP,JUMP1,JUMP2,REPEAT> {WHITESPACE}
    {}

{PAS}
	{ yybegin(STEP); }

<STEP> {ENTIER_SIMPLE}
	{ yybegin(YYINITIAL); return new StepLength(Integer.parseInt(yytext()));}
	
{MOVE}
	{ yybegin(JUMP1); } 

<JUMP1> {ENTIER_SIMPLE}
	{
		 lastInt = Integer.parseInt(yytext());
		 yybegin(JUMP2);
	}
	
<JUMP2> {ENTIER_SIMPLE}
	{
		yybegin(YYINITIAL); return new Jump(lastInt,Integer.parseInt(yytext()));
	}
	
{ENTIER_SIMPLE}
	{
		lastInt = Integer.parseInt(yytext());
		yybegin(REPEAT); 
	}
	
<REPEAT> {FOIS}
	{
		 yybegin(YYINITIAL); return new Repeat(lastInt);
	}
	
	
	
	
	
