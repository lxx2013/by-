CC=clang++-3.6
LLVMCONF=llvm-config-3.6
LEX=lex
YACC=bison
CFLAGS=-I include
YFLAGS=
LFLAGS=
all: bin/libdemo.a bin/parser
bin/libdemo.o:src/libdemo.c
	clang-3.6  -c -o $@ $< 
bin/libdemo.a:bin/libdemo.o
	ar rcs $@ $<   
bin/parser: bin/lexer.o bin/parser.o bin/main.o bin/util.o bin/global.o bin/node.o bin/dumpdot.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -g -o $@ $^ 

src/parser.cc include/tok.hh: config/parser.y
	$(YACC) $(YFLAGS) --defines=include/tok.hh -o src/parser.cc $< 

bin/parser.o: src/parser.cc include/node.hh include/util.hh include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $< 

src/lexer.cc: config/lexer.l
	$(LEX) $(LFLAGS) -o $@ $< 

bin/lexer.o: src/lexer.cc include/tok.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $< 

bin/node.o: src/node.cc include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -std=c++11 -c -g -o  $@ $< 

bin/main.o: src/main.cc include/tok.hh include/util.hh include/global.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -g -o $@ $< 

bin/util.o: src/util.cc include/util.hh include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -g -c -o $@ $< 

bin/global.o: src/global.cc include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -g -o $@ $< 

bin/dumpdot.o: src/dumpdot.cc include/dumpdot.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -std=c++11 -c -g -o $@ $< 

.PHONY: clean
clean:
	rm -f bin/*.o bin/*.o src/lexer.cc src/parser.cc include/tok.hh test/*.temp.c
	rm -f *.png *.dot *.output *.c *.ll *.o *.out
