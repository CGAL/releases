
default: settings

# This is a makefile to make an application using the CGAL library. 
# 
# You have to specify four things:

# (1) The Compiler 
# 
#     Pay attention not to put a blank behind the compiler name!!!

# for GNU Compiler
#CC = g++

# for SGI and SUN Pro Compiler
CC = CC


# (2) The Home Directory of LEDA
LEDA_DIR = $(HOME)/Leda


# (3) The Home Directory of CGAL
CGAL_DIR = $(HOME)/Cgal


# (4) The operating system of the machine where you are compiling. 
#
#     Issue the command "sh system" in the CGAL home directory
#     to find out what OS you are using.
# 
#     Pay attention not to put a blank behind the OS name!!!
#
#CGAL_OSTYPE =irix5
#CGAL_OSTYPE =sun4OS4
CGAL_OSTYPE =sun4OS5


#..........................................................................
# Don't edit the following line
include $(CGAL_DIR)/MAKE/makedefs
#..........................................................................

# Among other things 'makedefs' sets the paths where to find LEDA
# and where to find CGAL header files and libraries. 
# If this is different on your system, either change the files we provide
# in our distribution, or overwrite the values:
# LEDA_INCL_DIR =  
# LEDA_LIB_DIR =
# CGAL_INCL_DIR =
# CGAL_LIB_DIR =
# 

#..........................................................................

# add YOUR compiler and linker flags here.
# NEVER remove the CGAL compile or link flags.

CFLAGS = -g0   $(CGAL_CFLAGS)
LDFLAGS = $(CGAL_LDFLAGS) 

# put YOUR sources here:
SOURCES = program.C 
OBJS = $(SOURCES:.C=.o)



program: $(OBJS) 
	@echo "linking"
	$(CC) -o program   $(OBJS)  $(LDFLAGS)


funnelweb: funnelweb.o
	@echo "linking"
	$(CC) -o funnelweb   funnelweb.o  $(LDFLAGS) 


io2window: io2window.o
	@echo "linking"
	$(CC) -o io2window   io2window.o  $(CGAL_WINDOW_LDFLAGS)


conversion : conversion.C
	$(CC) -o conversion conversion.C  $(CFLAGS)  $(LDFLAGS)

io2geomview: io2geomview.o
	@echo "linking"
	$(CC) -o io2geomview   io2geomview.o  -lGeomview $(LDFLAGS) 


touch:
	touch $(SOURCES)

.C.o:
	@echo "compiling "  $(notdir $<)
	$(CC)  $(CFLAGS)  -c $<

