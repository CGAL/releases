# This is the makefile to make the CGAL library. 
# 
# You have to specify three things:

# (1) The Appropriate Compiler 
# 
#     Pay attention not to put a blank  behind the compiler name!!!

# for GNU Compiler
# CC   = g++

# for SGI and SUN Pro Compiler
CC = CC


# (2) The Home Directory of LEDA
LEDA_DIR = $(HOME)/Leda

# (3) The Home Directory of CGAL
CGAL_DIR = $(HOME)/Cgal



# Don't edit below this line.
#..........................................................................
include ../makedefs                # general settings
#include ./makeheaders             # creates .C and .h from funnelweb files
CFLAGS = -g0  $(CGAL_CFLAGS)
LDFLAGS =  -L$(LEDA_LIB_DIR)  -lL


LIBSOURCES = Origin.C OrdertypeC2.C  Bbox_2.C doublefield.C \
             utils.C Aff_transformationC2.C enum.C


LIBOBJS = $(LIBSOURCES:.C=.o)


lib:  $(CGAL_LIB_DIR)/$(CGALLIB)

sharedlib:  $(CGAL_LIB_DIR)/$(CGALSHAREDLIB)

$(CGAL_LIB_DIR)/$(CGALLIB):  $(HEADERS) $(LIBOBJS) 
	$(ARPREPROCESSOR) $(LIBOBJS)
	$(AR) $(CGALLIB) $(LIBOBJS)
	$(ARPOSTPROCESSOR) $(CGALLIB)
	mv $(CGALLIB) $(CGAL_LIB_DIR)/$(CGALLIB)

$(CGAL_LIB_DIR)/$(CGALSHAREDLIB):  $(LIBOBJS)
	$(AR_SHPREPROCESSOR) $(LIBOBJS)
	$(AR_SH) $(CGALSHAREDLIB) $(LIBOBJS) $(LDFLAGS)
	$(AR_SHPOSTPROCESSOR) $(CGALSHAREDLIB)
	mv $(CGALSHAREDLIB) $(CGAL_LIB_DIR)/$(CGALSHAREDLIB)

clean:
	cd $(CGAL_DIR)/src; rm -f $(LIBOBJS)
	rm -f $(CGAL_LIB_DIR)/$(CGALLIB)
	rm -f $(CGAL_LIB_DIR)/$(CGALSHAREDLIB)

touch:
	cd $(CGAL_DIR)/src; touch $(LIBSOURCES)


.C.o:
	@echo "compiling "  $(notdir $<)
	$(CC)  $(CFLAGS)  -c $<
