package automata;


public class TestND {

	public static void main(String[] args) throws StateException {

		/* Fabrication de l'automate */

		//AutomatonBuilder a = new NDAutomatonIncomplete();
		AutomatonBuilder a = new NDAutomatonWithDeterminisation();
		//NDAutomatonWithDeterminisation deter = new NDAutomatonWithDeterminisation();

		/*
		 * Définition des états Notez que les états sont numérotés 0, 1, 2, ...
		 * dans l'ordre de leur création dans l'automate par défaut les états
		 * sont nommés "qi", où i est leur numéro On peut leur choisir un autre
		 * nom en le passant en paramètre de la méthode addNewState
		 */
		a.addNewState();
		a.addNewState();
		a.addNewState();
		a.addNewState();
		a.addNewState();
		a.addNewState();
		a.addNewState();

		/*
		 * Définition des états initiaux et des états acceptants Le paramètre
		 * est indifféremment le numéro ou le nom d'un état
		 */
		a.setInitial("q0");
		a.setAccepting("q0");
		a.setAccepting("q2");
		a.setAccepting("q4");
		a.setAccepting("q6");

		/*
		 * Définition des transitions
		 */
		a.addTransition("q0", 'a', "q1");
		a.addTransition("q1", 'b', "q2");
		a.addTransition("q2", 'a', "q1");
		
		a.addTransition("q0", 'b', "q3");
		a.addTransition("q3", 'a', "q4");
		a.addTransition("q4", 'b', "q3");
		
		a.addTransition("q3", 'a', "q5");
		a.addTransition("q5", 'a', "q6");
		a.addTransition("q6", 'b', "q3");
		
		/*
		 * Affichage de l'automate, en mode texte
		 */
		System.out.println(a);

		/*
		 * Dessin de l'automate (fabrication d'un fichier Graphviz)
		 */
		dotToFile.dot(a, "output/automate-testND-nondeterminsite.dot");
		System.out.println("création output/automate-testND-nondeterminsite.dot");

		/*
		 * Test de la méthode accept() à réactiver quand vous aurez développé
		 * une classe avec une vraie méthode accept()
		 */

		System.out.println("check word baabaa : "+a.accept("baabaa"));
		System.out.println("check word aaab : "+a.accept("aaab"));
		System.out.println("check word bbab : "+a.accept("bbab"));
		System.out.println("check word bab : "+a.accept("bab"));

		/*
		 * Déterminisation
		 * 
		 * à essayer avec une instance de la classe
		 * NDAutomatonWithDeterminisation quand vous l'aurez écrite
		 * 
		 */
		AutomatonBuilder det = new NDAutomatonWithDeterminisation();
		NDAutomatonWithDeterminisation nd =  (NDAutomatonWithDeterminisation) a;
		nd.deterministic(det);
		
		System.out.println("\nDéterminisation\n");
		System.out.println(det);
		dotToFile.dot(det, "output/automate-testND-determinsite.dot");
		System.out.println("output/automate-testND-determinsite.dot");
		
		System.out.println("check word baabaa : "+det.accept("baabaa"));
		System.out.println("check word aaab : "+det.accept("aaab"));
		System.out.println("check word bbab : "+det.accept("bbab"));
		System.out.println("check word bab : "+det.accept("bab"));
	}
}
