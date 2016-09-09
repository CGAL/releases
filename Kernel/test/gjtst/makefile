

# This is a makefile to make an application using the CGAL library. 
# 


# Please adapt it to your environment

# (1) The Compiler  
# 
#     Pay attention not to put a blank  behind the compiler name!!!

# for GNU Compiler
CC   = g++

# for SGI and SUN Pro Compiler
#CC = CC

# (2) The operating system of the machine where you are compiling.
#
#     Issue the command "sh system" in the CGAL home directory
#     to find out what OS you are using.
#
#     Pay attention not to put a blank behind the OS name!!!
#
#CGAL_OSTYPE =irix5
#CGAL_OSTYPE =sun4OS4
CGAL_OSTYPE =sun4OS5



# (3) The Home Directory of LEDA
#
# symbolic link to the distribution
LEDA_DIR = /LEDA/INSTALLATION

# (4) The Home Directory of CGAL
#
# symbolic link to the distribution
CGAL_DIR = /KM/projects/CGAL/Work_in_Progress/test_version_8_11_96/CGAL-0.5

# If the makefiles for Cgal are not under $(CGAL_DIR) you
# have to change the following:

CGAL_MAKE_DIR = $(CGAL_DIR)/MAKE


# If the header files and the libraries are not installed in 
# subdirectories of the LEDA/CGAL root files, you may have to
# change the following too:
 

CGAL_INCL_DIR = $(CGAL_DIR)/include
CGAL_LIB_DIR = $(CGAL_DIR)/lib/$(CGAL_OSTYPE)_$(CC)



LEDA_INCL_DIR = $(LEDA_DIR)/incl
LEDA_LIB_DIR = $(LEDA_DIR)/solaris/g++




#..........................................................................
# Don't edit the following line
include $(CGAL_MAKE_DIR)/$(CGAL_OSTYPE)_$(CC)/application
#..........................................................................


# add YOUR compiler and linker flags here.
# NEVER remove the CGAL compile or link flags.

CFLAGS =  $(CGAL_FLAG_G)   $(CGAL_CFLAGS) -DCGAL_INCLUDE_CODE


LDFLAGS = $(CGAL_LDFLAGS) 

#..........................................................................


tst06: tst06.o
	$(CC) -o tst06 tst06.o $(LDFLAGS) 

tst02: tst02.o
	$(CC) -o tst02 tst02.o $(LDFLAGS) 

tst03: tst03.o
	$(CC) -o tst03 tst03.o $(LDFLAGS) 

tst04: tst04.o
	$(CC) -o tst04 tst04.o $(LDFLAGS) 

tst05: tst05.o
	$(CC) -o tst05 tst05.o $(LDFLAGS) 

tst06: tst06.o
	$(CC) -o tst06 tst06.o $(LDFLAGS) 


tst07: tst07.o
	$(CC) -o tst07 tst07.o $(LDFLAGS) 

tst08: tst08.o
	$(CC) -o tst08 tst08.o $(LDFLAGS) 

tst09: tst09.o
	$(CC) -o tst09 tst09.o $(LDFLAGS) 

tst10: tst10.o
	$(CC) -o tst10 tst10.o $(LDFLAGS) 

tst11: tst11.o
	$(CC) -o tst11 tst11.o $(LDFLAGS) 

tst21: tst21.o
	$(CC) -o tst21 tst21.o $(LDFLAGS) 

tst22: tst22.o
	$(CC) -o tst22 tst22.o $(LDFLAGS) 

tst22a: tst22a.o
	$(CC) -o tst22a tst22a.o $(LDFLAGS) 

tst23: tst23.o
	$(CC) -o tst23 tst23.o $(LDFLAGS) 

tst24: tst24.o
	$(CC) -o tst24 tst24.o $(LDFLAGS) 

tst25: tst25.o
	$(CC) -o tst25 tst25.o $(LDFLAGS) 


tst32: tst32.o
	$(CC) -o tst32 tst32.o $(LDFLAGS) 

tst33: tst33.o
	$(CC) -o tst33 tst33.o $(LDFLAGS) 

tst51: tst51.o
	$(CC) -o tst51 tst51.o $(LDFLAGS) 

tst52: tst52.o
	$(CC) -o tst52 tst52.o $(LDFLAGS) 

tst53: tst53.o
	$(CC) -o tst53 tst53.o $(LDFLAGS) 

tst57: tst57.o
	$(CC) -o tst57 tst57.o $(LDFLAGS) 

tst70: tst70.o
	$(CC) -o tst70 tst70.o $(LDFLAGS) 



.C.o:
	@echo "compiling "  $(notdir $<)
	$(CC)  $(CFLAGS)   -c $<

