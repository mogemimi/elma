bison:
	@flex src/Parser/Lexer.l
	@bison src/Parser/Parser.y

build:
	@cmake -Bbuild -H.
	@make -C build

xcode:
	@mkdir -p build
	@cd build && cmake -G Xcode ..

format:
	@clang-format -i \
		src/AST/*.cpp \
		src/AST/*.h \
		src/Basic/*.cpp \
		src/Basic/*.h \
		src/CodeGen/*.cpp \
		src/CodeGen/*.h \
		src/Driver/*.cpp \
		src/Driver/*.h \
		src/Printer/*.cpp \
		src/Printer/*.h \
		src/Sema/*.cpp \
		src/Sema/*.h \
		test/*.cpp \
		tools/driver/*.cpp

clean:
	@rm -f src/Parser/Lexer.cpp
	@rm -f src/Parser/Lexer.h
	@rm -f src/Parser/Parser.cpp
	@rm -f src/Parser/Parser.h
	@rm -f src/Parser/stack.hh
