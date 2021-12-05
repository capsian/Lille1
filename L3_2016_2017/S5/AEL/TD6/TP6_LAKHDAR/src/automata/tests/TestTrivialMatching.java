package automata.tests;

import java.io.IOException;
import automata.NDAutomatonWithDeterminisation;
import automata.StateException;
import automata.dotToFile;

public class TestTrivialMatching {

	
	public static void main(String[] args) throws StateException, IOException {
		TrivialMatching a = new TrivialMatching("annie", "honnit", "ni", "nina", "rene", "irene", "rein");
		//TrivialMatching a = new TrivialMatching("potato","theater","tattou","other","at");
		//TrivialMatching a = new TrivialMatching("create","at","cry");
		//TrivialMatching a = new TrivialMatching("create","at","cry");
		
		System.out.println("Initial automate : ");
		System.out.println("check word annie : "+a.accept("annie"));
		System.out.println("check word anniee : "+a.accept("anniee"));
		System.out.println("check word honnit : "+a.accept("honnit"));
		System.out.println("check word ni : "+a.accept("ni"));
		System.out.println("check word nina : "+a.accept("nina"));
		System.out.println("check word rene : "+a.accept("rene"));
		System.out.println("check word irene : "+a.accept("irene"));
		System.out.println("check word rein : "+a.accept("rein"));
		
		NDAutomatonWithDeterminisation cible = new NDAutomatonWithDeterminisation();
		a.deterministic(cible);
		System.out.println("Deterministe automate : ");
		System.out.println("check word annie : "+cible.accept("annie"));
		System.out.println("check word anniee : "+cible.accept("anniee"));
		System.out.println("check word honnit : "+cible.accept("honnit"));
		System.out.println("check word ni : "+cible.accept("ni"));
		System.out.println("check word nina : "+cible.accept("nina"));
		System.out.println("check word rene : "+cible.accept("rene"));
		System.out.println("check word irene : "+cible.accept("irene"));
		System.out.println("check word rein : "+cible.accept("rein"));
		
		dotToFile.dot(a    , "output/automate-trivialtest-nondeterministe.dot");
		dotToFile.dot(cible, "output/automate-trivialtest-deterministe.dot");
		System.out.println("création output/automate-trivialtest-deterministe.dot");
		System.out.println("création output/automate-trivialtest-nondeterministe.dot");
	}
}
