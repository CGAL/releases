 # This is the makefile for compiling a CGAL application.

#---------------------------------------------------------------------#
#                    include platform specific settings
#---------------------------------------------------------------------#
# Choose the right include file from the <cgalroot>/make directory.

# CGAL_MAKEFILE = ENTER_YOUR_INCLUDE_MAKEFILE_HERE
include $(CGAL_MAKEFILE)

#---------------------------------------------------------------------#
#                    compiler flags
#---------------------------------------------------------------------#

CPPFLAGS = $(CGAL_CXXFLAGS) \
           -g \
           -I../../include \
	   -lm 

#---------------------------------------------------------------------#
#                    linker flags
#---------------------------------------------------------------------#

LDFLAGS = $(CGAL_LDFLAGS)

#---------------------------------------------------------------------#
#                    target entries
#---------------------------------------------------------------------#


everything: kdtest_2 kdtest_3 kdtest_4 kdtest_5\
	kdtest_10 kdtest_20 kdtest_30

clean:
	rm -f *.o 
	rm -f core kdtest_*


#-----------------------------------------------------------------
# kdtest_* : Test program for kd-tree alone
#-----------------------------------------------------------------
kdtest_2: kdtest_2.o 
	$(CGAL_CXX) kdtest_2.o  $(CGAL_WINDOW_LDFLAGS) $(LDFLAGS) -o kdtest_2
kdtest_2.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_2.o -D_DIM=2 -c $(CPPFLAGS) kdtest.C

kdtest_3: kdtest_3.o 
	$(CGAL_CXX) kdtest_3.o  $(CGAL_WINDOW_LDFLAGS) $(LDFLAGS) -o kdtest_3
kdtest_3.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_3.o -D_DIM=3 -c $(CPPFLAGS) kdtest.C

kdtest_4: kdtest_4.o 
	$(CGAL_CXX) kdtest_4.o  $(CGAL_WINDOW_LDFLAGS) $(CPPFLAGS) -o kdtest_4
kdtest_4.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_4.o -D_DIM=4 -c $(CPPFLAGS) kdtest.C

kdtest_5: kdtest_5.o
	$(CGAL_CXX) kdtest_5.o  $(CGAL_WINDOW_LDFLAGS) $(CPPFLAGS) -o kdtest_5
kdtest_5.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_5.o -D_DIM=5 -c $(CPPFLAGS) kdtest.C

kdtest_10: kdtest_10.o 
	$(CGAL_CXX) kdtest_10.o  $(CGAL_WINDOW_LDFLAGS) $(CPPFLAGS) -o kdtest_10
kdtest_10.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_10.o -D_DIM=10 -c $(CPPFLAGS) kdtest.C

kdtest_20: kdtest_20.o 
	$(CGAL_CXX) kdtest_20.o  $(CGAL_WINDOW_LDFLAGS) $(CPPFLAGS) -o kdtest_20
kdtest_20.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_20.o -D_DIM=20 -c $(CPPFLAGS) kdtest.C

kdtest_30: kdtest_30.o 
	$(CGAL_CXX) kdtest_30.o  $(CGAL_WINDOW_LDFLAGS) $(CPPFLAGS) -o kdtest_30
kdtest_30.o: kdtest.C tester.h
	$(CGAL_CXX)  -o kdtest_30.o -D_DIM=30 -c $(CPPFLAGS) kdtest.C


#---------------------------------------------------------------------#
#                    suffix rules
#---------------------------------------------------------------------#

.C.o:
	$(CGAL_CXX) $(CPPFLAGS) -c $<
#	$(CGAL_CXX)  -c $(CPPFLAGS) $*.C







