package automata;

import java.util.Set;

public class DAutomaton extends NDAutomaton implements DeterministicAutomaton,AutomatonBuilder
{

	@Override
	public State getInitialState() 
	{
		Set<State> tmp = this.getInitialStates();
		
		if (tmp.isEmpty())
			return null;
		else
			return tmp.iterator().next();
	}

	@Override
	public State getTransition(State s, char letter) throws StateException
	{
		Set<State> tmp = this.getTransitionSet(s, letter);
		
		if (tmp.isEmpty())
			return null;
		else
			return tmp.iterator().next();
	}

	@Override
	public State getTransition(String name, char letter) throws StateException 
	{
		Set<State> tmp = this.getTransitionSet(name, letter);
		
		if (tmp.isEmpty())
			return null;
		else
			return tmp.iterator().next();
	}

	@Override
	public State getTransition(Integer id, char letter) throws StateException 
	{
		Set<State> tmp = this.getTransitionSet(id, letter);
		
		if (tmp.isEmpty())
			return null;
		else
			return tmp.iterator().next();
	}
}
