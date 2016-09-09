default: program
	

include ../makefile

# put YOUR compiler and linker flags here:

CFLAGS = -g  $(CGALFLAGS)
LDFLAGS = $(CGALLDFLAGS)


vpath %.h  $(CGAL)/include/CGAL
vpath %.a  $(CGAL)


# put YOUR sources here:
SOURCES = program.C
OBJS = $(SOURCES:.C=.o)



program: $(OBJS) 
	@echo "linking"
	@$(CC) -o program   $(OBJS)  $(LDFLAGS)


.C.o:
	@echo "compiling "  $(notdir $<)
	@$(CC)  $(CFLAGS)  -c $<

