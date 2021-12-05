package Exe2;

import java.io.IOException;
import java.io.InputStreamReader;
import ard.ParserException;
import ard.SyntaxException;
import condenses_lex.Tokenizer;
import condenses_lex.TokenizerV1;

public class Main 
{
	public static void main(String[] args) throws SyntaxException, ParserException, IOException 
	{
		while (true)
		{
			System.out.println("mot ? > ");
			Tokenizer yy = new TokenizerV1(new InputStreamReader(System.in)) ;
		    Exe2 parser = new Exe2(yy);
		    
			try 
			{
				parser.parse();
				System.out.println("extended : " + parser.getExtandedFormat());
			} 
			catch (SyntaxException e) 
			    {System.out.println("Erreur : " + e.getMessage());}
		}
			
	}
}
