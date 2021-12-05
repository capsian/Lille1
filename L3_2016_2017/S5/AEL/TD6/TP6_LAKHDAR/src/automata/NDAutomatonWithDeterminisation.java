package automata;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public class NDAutomatonWithDeterminisation extends NDAutomaton
{
	public NDAutomatonWithDeterminisation()
	{
		super();
	}
	
	/**
	*Construit un automate déterministe et complet équivalent
	*cible est supposé être un automate initialement vide
	*cible va recevoir l’automate déterministe créé
	*
	*@return déterminisé de l’automate (le résultat est l’objet reçu en paramètre)
	*/
	public Automaton deterministic(AutomatonBuilder cible)
	{
		HashMap<Set<State>, State> treated = new HashMap<Set<State>, State>();
		
		/* init untreated with initstates */
		ArrayList<Set<State>> tmp = new ArrayList<Set<State>>();
		tmp.add(this.getInitialStates());
		
		boolean isInitial = true;

		while (!tmp.isEmpty())
		{
			Set<State> current = tmp.get(0);
						
			if (!treated.containsKey(current))
				treated.put(current, cible.addNewState());
			
			for (Character l : this.alphabet)
			{
				Set<State> lState = this.getTransitionSet(current, l);
				if(!lState.isEmpty())
				{
					if(!treated.containsKey(lState))
					{
						tmp.add(lState);
						treated.put(lState, cible.addNewState(compactName(lState)));
					}
					cible.addTransition(treated.get(current), l, treated.get(lState));
				}
			}
			
			if (isInitial)
			{
				cible.setInitial(treated.get(current));
				isInitial = false;
			}
			
			if (containAcceptingState(current))
				cible.setAccepting(treated.get(current));
			
			tmp.remove(current);
		}
		return cible;
	}
	
	private String compactName(Set<State> states)
	{
		String r = "";
		for (State state : states) 
		{
			r += state.getName();
		}
		return r;	
	}
	
	private boolean containAcceptingState(Set<State> states)
	{
		for (State state : states) 
		{
			if (this.isAccepting(state))
				return true;
		}
		return false;
	}
}
