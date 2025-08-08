lexer: src/lexer.l
	flex src/lexer.l
	gcc lex.yy.c -o lexer -lfl

clean:
	rm -f lexer lex.yy.c
