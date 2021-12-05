package automata;

import java.util.HashMap;
import java.util.Map;

public class AhoCorasick extends DAutomaton
{
	protected String[] words;
	protected State[] endNode;
	protected State root;
	protected Map<State, State> repli;
	
	public AhoCorasick(String... words)
	{
		this.words = words;
		this.endNode = new State[words.length];
		this.repli = new HashMap<State, State>();
		this.construct();
		this.addTransitions();
	}
	
	public void construct()
	{
		this.root = this.addNewState("root");
		this.setInitial(this.root);
		
		for (int i = 0; i < words.length; i++) 
			endNode[i] = this.root;
		
		int maxWordLength = sizeLongestWord(words);
		
		for (int l=0; l<maxWordLength; l++)
		{
			for (int i=0; i<this.words.length; i++)
			{
				if (l<this.words[i].length())
				{
					State q = createNewState(this.endNode[i], this.words[i].charAt(l));
					this.endNode[i] = q;
					if (l+1 == this.words[i].length())
						setAccepting(this.endNode[i]);
				}
			}	
		}
	}
	
	private State createNewState(State parent, char letter)
	{
		String qName = "";
		if (parent.getName() == "root")
			qName += letter;
		else
			qName = parent.getName() + letter;
		
		State q = null;
		try 
			{q = this.addNewState(qName);}
		catch (StateException e) 
			{return getTransition(parent, letter);}		
		
		this.addTransition(parent, letter, q);
		
		if(parent.equals(this.root))
			this.repli.put(q, this.root);
		else
		{
			State s = parent;
			State stateForLetter = null;
			do
			{
				s = this.repli.get(s);
				stateForLetter = this.getTransition(s, letter);
			}
			while (stateForLetter == null && !s.equals(this.root));
			
			if (stateForLetter != null)
			{
				this.repli.put(q, stateForLetter);
				if (this.isAccepting(stateForLetter))
					this.setAccepting(q);
			}
			else
				this.repli.put(q, this.root);
		}
		
		return q;
	}
	
	public void addTransitions()
	{
		for (State q : this.getStates()) 
		{
			for (Character l : this.usedAlphabet()) 
			{
				if (this.getTransition(q, l) == null)
				{
					if (q.equals(this.root))
						this.addTransition(q, l, this.root);
					else
						this.addTransition(q, l, getTransition(repli.get(q), l));
				}
			}
			
		}
	}
	
	private int sizeLongestWord(String[] words)
	{
		int l=0;
		for (String wrd : words)
			if (wrd.length() > l)
				l = wrd.length();	
		return l;
	}
}
