package automata;
import java.util.Set;


public class NDAutomaton extends AbstractNDAutomaton implements Recognizer, AutomatonBuilder
{

	@Override
	public boolean accept(String word) throws StateException 
	{
		Set<State> startSet = new PrintSet<State>();
		Set<State> tmp = new PrintSet<State>();
		startSet = this.getInitialStates();
		
		for (int i=0; i<word.length(); i++)
		{
			tmp = getTransitionSet(startSet, word.charAt(i));
			
			if (tmp.isEmpty())
				return false;
			else
				startSet = tmp;
		}
		for (State state : startSet) 
		{
			if (isAccepting(state))
				return true;
		}
		
		return false;
	}
	
	protected Set<State> getTransitionSet(Set<State> startSet, char letter)
	{
		Set<State> result = new PrintSet<State>();
		Set<State> tmp = new PrintSet<State>();
	
		for (State state : startSet) 
		{
			if ((tmp = getTransitionSet(state,letter)) != null)
				result.addAll(tmp);
		}
		
		return result;
	}
}
