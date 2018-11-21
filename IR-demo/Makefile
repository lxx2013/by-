CFLAGS=-I include
LLVMCONF=llvm-config-3.6



all:demo libdemo.a
demo:demo.cc
	clang++-3.6 $(CFLAGS) -o $@ $< `llvm-config-3.6 --cxxflags --ldflags --system-libs --libs core native`
libdemo.o:libdemo.c
	clang-3.6  -c -o $@ $< 
libdemo.a:libdemo.o
	ar rcs $@ $<  


clean:
	rm -rf demo libdemo.so libdemo.a test *.o *.ll
