package jadelex;

public class Repeat extends BaseToken implements Yytoken
{
	private int occurrences;
	
	public Repeat(int occurrences) 
	{
		super(TokenType.REPEAT);
		this.occurrences = occurrences;
	}
	
	public int getOccurrences()
	{
		return this.occurrences;
	}
	
	public String toString()
	{
		return super.toString()+"["+this.occurrences+"]";
	}
	
}
