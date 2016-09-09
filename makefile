#-----------------------------------------------------------------------#
# This is a makefile that can be used for quickly installing the CGAL
# libraries. Use this method only if you are an experienced user! The
# following steps are required:
#
# 1) Set up the necessary configuration variables.
#
# 2) Enter 'make install' on the command line. This will create an
#    include makefile in the 'make' directory, by making a call to the
#    install_cgal script.
#
# 3) Enter 'make lib' or 'make shared' on the command line. This will
#    create the CGAL libraries.
# 
# N.B. This is NOT the recommended way to install CGAL!!!
#-----------------------------------------------------------------------#


#-----------------------------------------------------------------------#
#                         configuration
#-----------------------------------------------------------------------#

# DO NOT PUT SPACES BEFORE OR AFTER

# CGAL directory
CGAL_DIR=/KM/projects/CGAL/CGAL-1.0           # enter full pathname

# CONFIGURATION
#CGAL_CC=/opt/gnu/bin/g++
#CGAL_CC=/KM/opt/bin/eg++
CGAL_CC=/opt/SUNWspro/bin/CC
#CGAL_CC=/usr/bin/CC -32
#CGAL_CC=/usr/bin/CC

# COMPANION LIBRARIES

#-------------#
#    STL      #
#-------------#
# STL include directory (required if the compiler has no built-in STL!).
#STL_DIR=/KM/opt/HP_STL
STL_DIR=/KM/projects/CGAL/STL/OldSTLport

#-------------#
#    LEDA     #
#-------------#
# Remove the leda entries from the install command if you don't use LEDA.
LEDA_DIR=/LEDA/BETA

# For standard distributions of LEDA you should not have to change
# these variables.
LEDA_INCL_DIR=$(LEDA_DIR)/incl
#LEDA_LIB_DIR=$(LEDA_DIR)/irix64/CC64
LEDA_LIB_DIR=$(LEDA_DIR)/solaris/CC

#-------------#
#    GMP      #
#-------------#
# Remove the gmp entries from the install command if you don't use GMP.
GMP_DIR=/KM/projects/CGAL/Work_in_Progress/Number_types/gmp-2.0.2
GMP_INCL_DIR=$(GMP_DIR)/sparc_sun_solaris/include
GMP_LIB_DIR=$(GMP_DIR)/sparc_sun_solaris/lib
#GMP_INCL_DIR=$(GMP_DIR)/mips-sgi-irix6.2-64/include
#GMP_LIB_DIR=$(GMP_DIR)/mips-sgi-irix6.2-64/lib

#-----------------------------------------------------------------------#
#                         targets
#-----------------------------------------------------------------------#

all: install cgal_lib cgal_sharedlib

install:
	./install_cgal \
	     -gmp  --GMP_INCL_DIR "$(GMP_INCL_DIR)" \
 	           --GMP_LIB_DIR "$(GMP_LIB_DIR)" \
	     -leda --LEDA_INCL_DIR "$(LEDA_INCL_DIR)" \
	           --LEDA_LIB_DIR "$(LEDA_LIB_DIR)" \
	           --STL_DIR "$(STL_DIR)" \
	     -ni "$(CGAL_CC)"


#	     -leda --LEDA_INCL_DIR "$(LEDA_INCL_DIR)" \
#	           --LEDA_LIB_DIR "$(LEDA_LIB_DIR)" \


cgal_lib:
	cd src ; make -f makefile_lib

cgal_sharedlib:
	cd src ; make -f makefile_sharedlib

