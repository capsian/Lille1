package jade;
import drawing.*;
import java.awt.Point;

public class DrawingMachine implements JadeMachine 
{
	private DrawingFrame frame;
    private int stepLength;
    private boolean isActive;
    
    public DrawingMachine()
    {
        this.frame = new DrawingFrame();
        this.stepLength = 0;
        this.isActive = false;
    }

	@Override
	public void setStepLength(int n) 
	{
		if(n>0)
            this.stepLength = n;
	}

	@Override
	public void setPenMode(boolean active) 
	{
		this.isActive = active;
	}

	@Override
	public void move(Direction d) 
	{
		Point p = this.frame.getCurrentPoint();
		
		try
		{
	        switch(d)
	        {
	            case NORTH:
	                p.setLocation(p.getX(),p.getY()-this.stepLength);
	                this.frame.drawTo(p);
	                break;
	            case SOUTH:
	                p.setLocation(p.getX(),p.getY()+this.stepLength);
	                this.frame.drawTo(p);
	                break;
	            case WEST:
	                p.setLocation(p.getX()-this.stepLength,p.getY());
	                this.frame.drawTo(p);
	                break;
	            case EAST:
	                p.setLocation(p.getX()+this.stepLength,p.getY());
	                this.frame.drawTo(p);
	                break;
	        }  	
		}
        catch(Exception e)
        {System.out.println("*** Erreur Drawing Move, drawTo ***");}
	}

	@Override
	public void jump(int x, int y) 
	{
		Point p = new Point(x,y);
        
        try
        {
        	this.frame.goTo(p);
        }
        catch(Exception e)
        {System.out.println("*** Erreur Drawing Jump ***");}
	}

	@Override
	public void bye(int x, int y) 
	{
		Point p = new Point(x,y);
        
        try
        {
        	this.frame.goTo(p);
        }
        catch(Exception e)
        {System.out.println("*** Erreur Drawing Bye ***");}
	}
}
