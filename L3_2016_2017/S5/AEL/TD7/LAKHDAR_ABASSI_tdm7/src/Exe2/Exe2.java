package Exe2;

import java.io.IOException;
import ard.ParserException;
import ard.SyntaxException;
import condenses_lex.Tokenizer;

public class Exe2 extends Ard2
{
	private String extandedFormat;

	protected Exe2(Tokenizer in) throws IOException 
		{super(in);}

	@Override
	protected void axiom() throws SyntaxException, ParserException, IOException 
		{this.extandedFormat = S();}
	
	public String getExtandedFormat()
		{return this.extandedFormat;}
	
	private int R() throws SyntaxException, ParserException, IOException 
	{
		switch (current.getType()) 
		{
		case ENTIER: 	
			// R -> Entier
			return C();
		case LETTRE: case OUVRANTE: case FERMANTE: case EOD:
			// R -> eps
			return 1;
		default:
			throw new SyntaxException("R(): No rule token current = " + current);
		}
	}
	
	private int C() throws SyntaxException, ParserException, IOException 
	{
		int tmp;
		switch (current.getType()) {
		case ENTIER:
			tmp = Integer.parseInt(current.getValue());
			//System.out.println("C(): tmp = " + tmp + " current = " + current);
			eat(current);
			break;
		default:
			throw new SyntaxException("C(): No rule token current = " + current);
		}
		return tmp;
	}
	
	private String E() throws SyntaxException, ParserException, IOException {
		String tmp;
		switch (current.getType())
		{
			case LETTRE:
				// E -> L
				return L();
			case OUVRANTE:
				// E -> (S)
				eat(current);
				tmp = S();
				eat(current);
				//System.out.println("E() : tmp = " + tmp);
				return tmp;
			default:
				throw new SyntaxException("E(): No rule token current = " + current);
		}
	}
	
	private String L() throws SyntaxException, ParserException, IOException {
		switch (current.getValue()) 
		{
			case "a":
				eat(current);
				return "a";
			case "b":
				eat(current);
				return "b";
			case "c":
				eat(current);
				return "c";
			default:
				throw new SyntaxException("L(): No rule token current = " + current);
		}
	}
	
	private String S() throws SyntaxException, ParserException, IOException {
		String tmp = "";
		String r = "";
		int i;
		switch (current.getType()) 
		{
			case LETTRE:	case OUVRANTE:
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
			
			case FERMANTE:	case EOD:
				// S -> eps
				return "";
			default:
				throw new SyntaxException("S(): No rule token current = " + current);
		}
	}

}
