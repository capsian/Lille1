package automata.tests;

import java.io.IOException;

import automata.AhoCorasick;
import automata.StateException;
import automata.dotToFile;

public class TestAhoCor 
{
	public static void main(String[] args) throws StateException, IOException 
	{
		//AhoCorasick a = new AhoCorasick("annie", "honnit", "ni", "nina", "rene", "irene", "rein");
		//AhoCorasick a = new AhoCorasick("potato","theater","tattou","other","at");
		AhoCorasick a = new AhoCorasick("create","at","cry");
		
		System.out.println(a);
		
		dotToFile.dot(a, "output/automate-AhoCor.dot");
		System.out.println("création output/automate-AhoCor.dot");
	}
}
