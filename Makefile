#Makefile to test the EJ cryptosystem
#
#This software is released under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1 (LGPL 2.1) .
#A copy of it can be found at the URL https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html
#Another copy of it is contained in the file "LICENSES.txt" in the same directory as this file.

CC=g++
# compiler flags: -O2 ie. level 2 optimization ; -m64 ie. optimize for 64 bit CPU
CFLAGS=-O2 -m64
DEPS = ejcrypto.h
TARGETEXECUTABLE=test

.PHONY: $(TARGETEXECUTABLE)
$(TARGETEXECUTABLE): test.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGETEXECUTABLE) test.cpp $(DEPS)
	
.PHONY: clean
clean:
	rm test
