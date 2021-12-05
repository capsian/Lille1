package automata;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

public class dotToFile
{
	public static void dot(Automaton a, String fileName) {
		File f = new File(fileName);
		try {
			PrintWriter sortieDot = new PrintWriter(f);
			sortieDot.println(a.toGraphviz());
			sortieDot.close();
		} catch (IOException e) {
			System.out.println("création du fichier " + fileName + " impossible");
		}
	}
}
