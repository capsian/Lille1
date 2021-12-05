package jadelex;

import jade.Direction;

public class Move extends BaseToken implements Yytoken
{
	private Direction move;
	
	public Move(Direction move) 
	{
		super(TokenType.MOVE);
		this.move = move;
	}
	
	public Direction getDirection()
	{
		return this.move;
	}
	
	public String toString()
	{
		return super.toString()+"["+move+"]";
	}
	
}
