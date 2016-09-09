default: program
# This is a makefile to make an application using the CGAL library. 
# 
# You have to specify three things:

# (1) The Appropriate Compiler 
# 
#     Pay attention not to put a blank behind the compiler name!!!

# for GNU Compiler
# CC = g++

# for SGI and SUN Pro Compiler
CC = CC


# (2) The Home Directory of LEDA
LEDA_DIR = $(HOME)/Leda

# (3) The Home Directory of CGAL
CGAL_DIR = $(HOME)/Cgal

#..........................................................................
# Don't edit the following line
include $(CGAL_DIR)/makedefs
#..........................................................................

# add YOUR compiler and linker flags here.
# NEVER remove the CGAL compile or link flags.

CFLAGS = -g  $(CGAL_CFLAGS)
LDFLAGS = $(CGAL_LDFLAGS)

# put YOUR sources here:
SOURCES = program.C
OBJS = $(SOURCES:.C=.o)



program: $(OBJS) 
	@echo "linking"
	$(CC) -o program   $(OBJS)  $(LDFLAGS)


.C.o:
	@echo "compiling "  $(notdir $<)
	$(CC)  $(CFLAGS)  -c $<


touch:
	touch $(SOURCES)