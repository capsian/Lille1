CC      = gcc
INCLUDE = -I include/
CFLAGS  = -Wall -Wextra -pedantic -g

BUILD   = build
BIN     = ${BUILD}/bin/
SRC     = src

#######################

%.o: src/*/%.c include/*/%.h
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

%.o: src/*/%.c
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

%.o: src/%.c include/%.h
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

%.o: src/%.c
	${CC} ${INCLUDE} ${CFLAGS} -c $< -o ${BUILD}/$@

#######################

all: lexer unlexer parser

lexer : lexer.o token.o tokenizer.o utils.o
			cd ${BUILD} && ${CC} ${LDFLAGS} -o ../$(BIN)$@ $^

unlexer : unlexer.o token.o utils.o
			cd ${BUILD} && ${CC} ${LDFLAGS} -o ../$(BIN)$@ $^

parser : parser.o unlex_tokens.o token.o rules.o tree.o
			cd ${BUILD} && ${CC} ${LDFLAGS} -o ../$(BIN)$@ $^

unserializer : unserializer.o token.o structs.o evaluate.o global_environnement.o
			cd ${BUILD} && ${CC} ${LDFLAGS} -o ../$(BIN)$@ $^

#######################

test_lexer: lexer unlexer
	./build/bin/lexer -i ./tests/exemples/1-tokens-divers-lo.js
	./build/bin/unlexer -i ./tests/exemples/1-tokens-divers-lo.js.lex

test_parser: test_lexer
	./build/tools/parser < ./tests/1-lexer.lex > ./tests/1-lexer.parse
	
test_interprete: unserializer test_parser
	./build/bin/unserializer ./tests/1-lexer.parse


#######################

clean:
	rm -f build/*.o || true

realclean: clean
	rm -f build/bin/* tests/*.lex tests/*.parse || true

.PHONY : all clean realclean
