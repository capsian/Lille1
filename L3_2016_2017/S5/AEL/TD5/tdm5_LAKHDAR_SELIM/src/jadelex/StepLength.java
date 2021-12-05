package jadelex;

public class StepLength extends BaseToken implements Yytoken
{
	private int lenght;
	
	
	protected StepLength(int stepLength) 
	{
		super(TokenType.STEP_LENGTH);
		this.lenght = stepLength;
	}
	
	public int getLength()
	{
		return this.lenght;
	}

	public String toString()
	{
		return super.toString()+"["+lenght+"]";
	}
}
