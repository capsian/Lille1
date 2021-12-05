package automata.tests;

import java.io.PrintWriter;
import java.io.Writer;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import automata.NDAutomatonWithDeterminisation;
import automata.State;
import automata.StateException;

/**
 * 
 * Automate destiné à la recherche d'un ensemble de mots dans un texte.
 * Construit selon l'algorithme de AhoCorasick.
 * 
 * @author Bruno.Bogaert (at) univ-lille1.fr
 *
 */
public class TrivialMatching extends NDAutomatonWithDeterminisation {
	String[] words;

	/**
	 * Construit l'automate à partir d'un ensemble non vide de mots non vides
	 * 
	 * @param words
	 *            mots à rechercher
	 */
	public TrivialMatching(String... words) {
		if (words == null || words.length == 0)
			throw new RuntimeException("Liste vide de mots");

		for (String motif : words) {
			if (motif.length() == 0)
				throw new RuntimeException("motif vide interdit");
		}
		this.words = words;
		root = this.addNewState("root");
		this.setInitial(root);
		repli = new HashMap<State, State>();
		repli.put(root, root);
		this.ending = new State[this.words.length];
		construction();
	}

	private State root;

	private State[] ending; // ending[i] = ending state of words[i] branch

	private Map<State, State> repli;

	/**
	 * Fabrique un nouvel état accessible à partir du noeud parent par la lettre
	 * letter. Calcule également la relation de repli pour le nouvel état.
	 * 
	 * @param parent
	 *            parent du noeud à créer
	 * @param letter
	 *            label de la transition entre parent et noeud à créer
	 * @return état créé
	 * @throws StateException
	 */
	private State addNewState(State parent, char letter) {
		String name = (parent == root ? "" : parent.getName()) + letter;
		State q = super.addNewState(name);
		addTransition(parent, letter, q);
		if (parent == root) {
			repli.put(q, root);
		} else {
			State current = parent;
			Set<State> e;
			do {
				current = repli.get(current);
				e = getTransitionSet(current, letter);
			} while (e.isEmpty() && current != root);
			if (!e.isEmpty()) {
				State r = e.iterator().next();
				repli.put(q, r);
				if (isAccepting(r))
					setAccepting(q);
			} else
				repli.put(q, root);
		}
		return q;

	}

	/**
	 * Complète les transitions définies pour l'état q en utilisant la position
	 * de repli.
	 * 
	 * @param q
	 */
	private void addRegressTransitions(State q) {
		for (char letter : alphabet) {
			Set<State> destSet = getTransitionSet(q, letter);
			if (destSet.isEmpty() || destSet.iterator().next() == root) {
				State dest;
				if (q == root)
					dest = root;
				else
					dest = delta.get(new Key(repli.get(q), letter)).iterator().next();
				addTransition(q, letter, dest);
			}

		}
	}

	@Override
	public Set<State> getTransitionSet(State s, char letter) {
		// Toutes les transitions non explicitement définies renvoient à l'état
		// initial
		Set<State> destSet = super.getTransitionSet(s, letter);
		return (!destSet.isEmpty()) ? destSet : this.getInitialStates();
	}

	/**
	 * Construction de l'automate selon l'algo de Aho Corasick
	 * 
	 */
	private void construction() {
		Arrays.fill(ending, root);

		HashSet<Integer> todo = new HashSet<Integer>(this.words.length);
		for (int i = 0; i < this.words.length; i++)
			todo.add(i);

		int stringIndex = 0;
		while (!todo.isEmpty()) {
			Iterator<Integer> it = todo.iterator();
			while (it.hasNext()) {
				Integer i = it.next();
				char letter = words[i].charAt(stringIndex);
				Key k = new Key(ending[i], letter);
				Set<State> qSet = delta.get(k);
				State q;
				if (qSet == null || qSet.isEmpty()) {
					q = addNewState(ending[i], letter);
					System.out.println("echec " + q.getId() + "  " + repli.get(q).getId());
				} else
					q = qSet.iterator().next();
				ending[i] = q;
				if (stringIndex + 1 == words[i].length()) {
					it.remove();
					setAccepting(ending[i]);
					System.out.println("fin du mot " + words[i]);
				}
			}
			stringIndex++;
		}
		// for (State q : states) {
		// addRegressTransitions(q);
		// }

		for (char letter : usedAlphabet()) {
			addTransition(root, letter, root);
		}

	}

	public Writer writeGraphvizEchec(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		for (State s : states) {
			State e = repli.get(s);
			if (e != root)
				out.println("    " + s.getId() + " -> " + e.getId() + " [style=dotted]");
		}
		return buff;
	}

	public Writer writeGraphvizSkeletonTransitions(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		for (Map.Entry<Key, Set<State>> entry : delta.entrySet()) {
			if (entry.getValue().isEmpty())
				break;
			State dest = entry.getValue().iterator().next();
			if (dest != root && (entry.getKey().from == root
					|| dest.getName().length() > entry.getKey().from.getName().length())) {
				out.print("  " + entry.getKey().from.getId() + " -> " + dest.getId());
				out.println(" [label = \"" + entry.getKey().letter + "\" ]");
			}
		}
		return buff;
	}

	public Writer writeGraphvizLightTransitions(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		for (Map.Entry<Key, Set<State>> entry : delta.entrySet()) {
			if (entry.getValue().isEmpty())
				break;
			State dest = entry.getValue().iterator().next();
			if (dest != root) {
				out.print("  " + entry.getKey().from.getId() + " -> " + dest.getId());
				out.println(" [label = \"" + entry.getKey().letter + "\" ]");
			}
		}
		return buff;
	}

	public Writer writeGraphvizSkeleton(Writer buff) {
		PrintWriter out = new PrintWriter(buff);
		out.println("digraph Automaton { ");
		out.println("nodes [pin=true] ");
		writeGraphvizStates(buff, true);
		writeGraphvizInitials(buff);
		writeGraphvizSkeletonTransitions(buff);
		out.println("}");
		return buff;
	}

	protected Writer writeGraphvizStates(Writer buff, boolean withNames) {
		PrintWriter out = new PrintWriter(buff);
		out.println("  rankdir = LR");
		// out.println("ranksep=2; size = \"7.5,7.5\"");
		Iterator<State> it = states.iterator();
		out.print("{rank=same; ");
		out.print(stateToGV(it.next(), withNames)); // root
		int rank = 0;
		while (it.hasNext()) {
			State s = it.next();
			if (s.getName().length() != rank) {
				rank++;
				out.println("}");
				out.print("{rank=same; ");
			}
			out.print(stateToGV(s, withNames));
		}
		out.println("}");
		return buff;
	}

	public Writer writeGraphvizInner(Writer buff) {
		writeGraphvizStates(buff, true);
		writeGraphvizInitials(buff);
		// writeGraphvizSkeletonTransitions(buff);
		writeGraphvizLightTransitions(buff);
		writeGraphvizEchec(buff);
		return buff;
	}

}
