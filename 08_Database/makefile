#The following rule tells make about possible suffixes
#(extensions) of file names.

.SUFFIXES: .c .o

#The following definition of CC ensures that
#gcc will be used to compile the C source files.

CC = gcc

#The following definition of CFLAGS ensures that
#the debugger can be used with the executable file (sample)
#created by running make.

CFLAGS = -g

#The following rule tells make how a ".o" file should
#be created from the corresponding ".c" file.
#Note that the "-c" option must be used here since we are
#compiling source files separately. (Note that the line
#following the ".c.o:" line begins with the "tab" character.)

.c.o:
	$(CC) $(CFLAGS) -c $<

#Dependency rule for the default target and how the
#default target is to be created. (Note that the line
#following the dependency rule begins with the "tab"
#character.)

p1: p1.o  funct_insert.o funct_7.o
	gcc p1.o funct_insert.o funct_7.o -o p1

#Dependency rules for other targets. (We don't need to
#specify how these targets are created since we have already
#given a general rule for creating a ".o" file from the
#corresponding ".c" file.)

p1.o: constants.h struct_def.h globals.h
funct_insert.o: constants.h struct_def.h externs.h 
funct_7.o: constants.h struct_def.h  externs.h


#Target for removing unnecessary files.

clean:
	rm -f *.o core
