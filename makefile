
#
# you have to set the following two paths
#
LEDA = $(HOME)/Leda
CGAL   = $(HOME)/Cgal

#
# CGAL works for the SUN Pro 4.0.1 C++ Compiler
#
CC   = CC 

CGALFLAGS =    -DCGAL_IO -DCGAL_REPCLASS -DCGAL_KERNEL_PRECONDITION -DCGAL_WORKAROUND_0002 -I$(CGAL)/include  -I$(LEDA)/incl -I$(CGAL)/include

CGALLDFLAGS =  -L$(LEDA) -L$(CGAL) -lCGALkernel -lL

CGALLIB = $(CGAL)/libCGALkernel.a


lib: 
	cd src ; $(MAKE) $(CGALLIB)
