package jadelex;

public class Jump extends BaseToken  implements Yytoken
{
	private int x;
	private int y;
	
	protected Jump(int x, int y) 
	{
		super(TokenType.JUMP);
		this.x = x;
		this.y = y;
	}
	
	public int getX()
	{
		return this.x;
	}
	
	public int getY()
	{
		return this.y;
	}
	
	public String toString()
	{
		return super.toString()+"[X="+this.x+", Y="+this.y+"]";
	}

}
