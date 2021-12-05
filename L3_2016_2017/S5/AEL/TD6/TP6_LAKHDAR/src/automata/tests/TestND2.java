package automata.tests;

import automata.AutomatonBuilder;
import automata.NDAutomatonWithDeterminisation;
import automata.StateException;
import automata.dotToFile;

public class TestND2 {

	public static void main(String[] args) throws StateException 
	{	
		AutomatonBuilder a = new NDAutomatonWithDeterminisation();
		
		a.addNewState("ini");a.addNewState("a");a.addNewState("b");a.addNewState("c");a.addNewState("bc");a.addNewState("ca");
		a.setInitial("ini");
		a.setAccepting("a");a.setAccepting("bc");a.setAccepting("ca");
		a.addTransition("ini", 'a', "a");a.addTransition("ini", 'b', "b");a.addTransition("ini", 'c', "c");a.addTransition("b", 'c', "bc");
		a.addTransition("c", 'a', "ca");a.addTransition("ini", 'a', "ini");	a.addTransition("ini", 'b', "ini");a.addTransition("ini", 'c', "ini");
	
		// test accept
		System.out.println("check word aaa : "+a.accept("aaa"));
		System.out.println("check word bc : "+a.accept("bc"));
		System.out.println("check word bca : "+a.accept("bca"));
		System.out.println("check word bccc : "+a.accept("bccc"));
		
		// Déterministation	
		NDAutomatonWithDeterminisation cible = new NDAutomatonWithDeterminisation();
		NDAutomatonWithDeterminisation nd = (NDAutomatonWithDeterminisation) a;
		nd.deterministic(cible);

		// test accept
		System.out.println("\nDéterminisation\n");
		System.out.println("check word aaa : "+cible.accept("aaa"));
		System.out.println("check word bc : "+cible.accept("bc"));
		System.out.println("check word bca : "+cible.accept("bca"));
		System.out.println("check word bccc : "+cible.accept("bccc"));
		
		dotToFile.dot(a, "output/automate-testND2-nondeterministe.dot");
		dotToFile.dot(cible, "output/automate-testND2-deterministe.dot");
		System.out.println("création output/automate-testND2-nondeterministe.dot");
		System.out.println("création output/automate-testND2-deterministe.dot");
	}
}
