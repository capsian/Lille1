testND:
	mkdir -p bin/ output/
	javac -cp src/ src/automata/TestND.java -d bin/
	java -cp bin/ automata.TestND
	dot -O -Tpdf output/automate-testND-nondeterminsite.dot
	dot -O -Tpdf output/automate-testND-determinsite.dot
	evince output/automate-testND-nondeterminsite.dot.pdf output/automate-testND-determinsite.dot.pdf&
	
testND2:
	mkdir -p bin/ output/
	javac -cp src/ src/automata/tests/TestND2.java -d bin/
	java -cp bin/ automata.tests.TestND2
	dot -O -Tpdf output/automate-testND2-deterministe.dot
	dot -O -Tpdf output/automate-testND2-nondeterministe.dot
	evince output/automate-testND2-nondeterministe.dot.pdf output/automate-testND2-deterministe.dot.pdf&
	
testND3:
	mkdir -p bin/ output/
	javac -cp src/ src/automata/tests/TestND3.java -d bin/
	java -cp bin/ automata.tests.TestND3
	dot -O -Tpdf output/automate-testND3-deterministe.dot
	dot -O -Tpdf output/automate-testND3-nondeterministe.dot
	evince output/automate-testND3-nondeterministe.dot.pdf output/automate-testND3-deterministe.dot.pdf&
	
trivialtest:
	mkdir -p bin/ output/
	javac -cp src/ src/automata/tests/TestTrivialMatching.java -d bin/
	java -cp bin/ automata.tests.TestTrivialMatching
	dot -O -Tpdf output/automate-trivialtest-deterministe.dot
	dot -O -Tpdf output/automate-trivialtest-nondeterministe.dot
	evince output/automate-trivialtest-deterministe.dot.pdf output/automate-trivialtest-nondeterministe.dot.pdf&
	
ahocorasick:
	mkdir -p bin/ output/
	javac -cp src/ src/automata/tests/TestAhoCor.java -d bin/
	java -cp bin/ automata.tests.TestAhoCor
	dot -O -Tpdf output/automate-AhoCor.dot
	evince output/automate-AhoCor.dot.pdf&
	
clean:
	rm -rf bin output *.dot
