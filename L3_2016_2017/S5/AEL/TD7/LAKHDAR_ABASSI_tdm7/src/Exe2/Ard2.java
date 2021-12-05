package Exe2;

import java.io.IOException;
import java.util.NoSuchElementException;
import ard.ParserException;
import ard.SyntaxException;
import condenses_lex.*;

public abstract class Ard2
{
	public static final TokenType END_MARKER = TokenType.EOD;
	Tokenizer input;
	
	private boolean invalid = false;
	
	protected Yytoken current;
	private String currentLine;
	private int currentIndex;
	
	protected Ard2(Tokenizer in) throws IOException 
	{
		input = in ;
		shift();
	}

	
	/**
	 * Avance d'une position dans la lecture du texte
	 * @throws ParserException si on est en fin de texte.
	 * @throws IOException 
	 */
	protected void next() throws ParserException, IOException {
		if (current.getType().equals(END_MARKER)){
			throw new ParserException();
		}
		shift();
	}
	
	private void shift() throws IOException{
		try {
			currentIndex++;
			if (currentLine == null || currentIndex >= currentLine.length()) 
			{
				currentLine = input.yytext().toString();
				currentIndex = 0;
			}
			current = input.yylex();
		} catch (NoSuchElementException e) {
			current = new Eod("");
		}
	}
	
	
	/**
	 * Vérifie que le caractère courant correspond au caractère attendu
	 * puis progresse d'une position dans la lecture du texte.
	 * @throws SyntaxException si la vérification de correspondance échoue
	 */
	protected void eat(Yytoken expected) throws SyntaxException, ParserException, IOException {
		if (!current.equals(expected))
			throw new ParserException("expected : " + expected + ", found : " + current);
		next();
	}
	
	/**
	 * Doit simplement invoquer la méthode implémentant l'axiome de la grammaire.
	 * @throws IOException 
	 */
	protected abstract void axiom() throws SyntaxException, ParserException, IOException;
	
	
	/**
	 * Analyse le texte. Déclenche une exception en cas d'erreur.
	 * 
	 * Ne peut être invoquée qu'une seule fois.
	 * 
	 * @throws SyntaxException En cas d'erreur de syntaxe
	 * @throws ParserException  En cas d'erruer de utilisation du parser.
	 * @throws IOException 
	 */
	public void parse() throws SyntaxException, ParserException, IOException{
		if (invalid) 
			throw new ParserException();
		// Axiom :
		axiom();
		// check end of data :
		if (current.getType() != END_MARKER)
			throw new SyntaxException("parse() : Unmatching token");
		this.invalid = true;
	}
}
