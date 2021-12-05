package ard;

import java.io.Reader;

public class Exe1 extends Ard
{
	private String extandedFormat;
	
	protected Exe1(Reader in) 
	{
		super(in);
		this.extandedFormat = new String();
	}
	
	private String S() throws SyntaxException, ParserException {
		String tmp = "";
		String r = "";
		int i;
		switch (current) {
		case 'a':	case 'b':	case 'c':	case '(':
			// S -> ERS
			r = E();
			//System.out.println("S() : r = " + r);
			i = R();
			//System.out.println("S() : i = " + i);
			for (int j = 0; j < i; j++) 
			{
				tmp += r;
			}
			//System.out.println("S() : tmp* = " + tmp);
			tmp += S();
			//System.out.println("S() : tmp** = " + tmp);
			return tmp;
		case ')':	
		case END_MARKER:
			// S -> eps
			return "";
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private int R() throws SyntaxException, ParserException {
		switch (current) {
		case 'a': 	
		case 'b':
		case 'c':	
		case '(':	
		case ')':	
		case END_MARKER:
			// R -> eps
			// why not 0 ??
			return 1;
		case '0': case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : case '8' : case '9':
			// R -> C
			return C();
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private String E() throws SyntaxException, ParserException {
		String tmp;
		switch (current) {
		case 'a':	case 'b':	case 'c':
			// E -> L
			return L();
		case '(':
			// E -> (S)
			eat('(');
			tmp = S();
			eat(')');
			//System.out.println("E() : tmp = " + tmp);
			return tmp;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private String L() throws SyntaxException, ParserException {
		switch (current) {
		case 'a':
			eat('a');
			return "a";
		case 'b':
			eat('b');
			return "b";
		case 'c':
			eat('c');
			return "c";
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
	}
	
	private int C() throws SyntaxException, ParserException {
		int tmp;
		switch (current) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			tmp = Integer.parseInt(String.valueOf(current));
			eat(current);
			break;
		default:
			throw new SyntaxException(ErrorType.NO_RULE,current);
		}
		return tmp;
	}

	@Override
	protected void axiom() throws SyntaxException, ParserException
		{this.extandedFormat = S();}
	
	public String getExtandedFormat()
		{return this.extandedFormat;}
}
