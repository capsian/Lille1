package automata.tests;

import automata.AutomatonBuilder;
import automata.NDAutomatonWithDeterminisation;
import automata.StateException;
import automata.dotToFile;

public class TestND3 {

	public static void main(String[] args) throws StateException {
		AutomatonBuilder a = new NDAutomatonWithDeterminisation();
		
		a.addNewState("q0");a.addNewState("q1");a.addNewState("q2");a.addNewState("q3");
		a.setInitial("q0");
		a.setAccepting("q2");a.setAccepting("q3");
		a.addTransition("q0", 'a', "q0");a.addTransition("q0", 'b', "q0");a.addTransition("q0", 'a', "q1");a.addTransition("q1", 'a', "q2");
		a.addTransition("q1", 'b', "q3");a.addTransition("q2", 'a', "q2");a.addTransition("q2", 'b', "q2");a.addTransition("q3", 'a', "q3");
		a.addTransition("q3", 'b', "q3");

		// test accept
		System.out.println("check word aa : "+a.accept("aa"));
		System.out.println("check word bb : "+a.accept("bb"));
		System.out.println("check word aba : "+a.accept("aba"));
		System.out.println("check word bba : "+a.accept("bba"));
		
		// Déterministation	
		NDAutomatonWithDeterminisation cible = new NDAutomatonWithDeterminisation();
		NDAutomatonWithDeterminisation nd = (NDAutomatonWithDeterminisation) a;
		nd.deterministic(cible);
		
		dotToFile.dot(a, "output/automate-testND3-nondeterministe.dot");
		dotToFile.dot(cible, "output/automate-testND3-deterministe.dot");
		System.out.println("création output/automate-testND3-nondeterministe.dot");
		System.out.println("création output/automate-testND3-deterministe.dot");
	}

}
