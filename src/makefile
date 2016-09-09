default: settings

# This is the makefile to make the CGAL library. 
# 
# You have to specify four things:

# (1) The Compiler  
# 
#     Pay attention not to put a blank  behind the compiler name!!!

# for GNU Compiler
#CC   = g++

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


# Don't edit below this line.
#..........................................................................
include  $(CGAL_DIR)/MAKE/makedefs      # general settings

CFLAGS = -g0  $(CGALLIB_CFLAGS)


LIBSOURCES = Origin.C predicates_on_pointsC2.C  Bbox_2.C doublefield.C \
             utils.C aff_transformation_tags.C enum.C Double_eps.C Rational.C \
             Bbox_2_intersections.C  Color.C double-specializationsC2.C

LIBOBJS = $(LIBSOURCES:.C=.o)


lib:  $(CGAL_LIB_DIR)/$(CGALLIB)

#.................................
# We recursively call 'make' setting a flag, in order to make a shared library
sharedlib:
	$(MAKE) sharedlib_internal CGAL_SH_LIB_CFLAGS_FNAME = SH_LIB_CFLAGS

sharedlib_internal:  $(CGAL_LIB_DIR)/$(CGALSHAREDLIB)

$(CGAL_LIB_DIR)/$(CGALLIB):  $(HEADERS) $(LIBOBJS) 
	$(ARPREPROCESSOR) $(LIBOBJS)
	$(AR) $(CGALLIB) $(LIBOBJS)
	$(ARPOSTPROCESSOR) $(CGALLIB)
	mv $(CGALLIB) $(CGAL_LIB_DIR)/$(CGALLIB)

$(CGAL_LIB_DIR)/$(CGALSHAREDLIB):  $(LIBOBJS)
	$(AR_SHPREPROCESSOR) $(LIBOBJS)
	$(AR_SH) $(CGALSHAREDLIB) $(LIBOBJS) 
	$(AR_SHPOSTPROCESSOR) $(CGALSHAREDLIB)
	mv $(CGALSHAREDLIBS) $(CGAL_LIB_DIR)/

clean:
	cd $(CGAL_DIR)/src; rm -f $(LIBOBJS)
	rm -f $(CGAL_LIB_DIR)/$(CGALLIB)
	rm -f $(CGAL_LIB_DIR)/$(CGALSHAREDLIB)

touch:
	cd $(CGAL_DIR)/src; touch $(LIBSOURCES)


.C.o:
	@echo "compiling "  
	$(CC)  $(CFLAGS)  -c $<
