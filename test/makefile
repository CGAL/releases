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
#
CGAL_DIR = $(HOME)/Cgal


# (4) The operating system of the machine where you are compiling.
# 
#     Issue the command "sh system" in the CGAL home directory
#     to find out what OS you are using. 
#
#     Pay attention not to put a blank behind the OS name!!!
#
#CGAL_OSTYPE =sun4OS4
CGAL_OSTYPE =sun4OS5
#CGAL_OSTYPE =irix5


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

FIELDTYPE = double # CGAL_Rational 
RINGTYPE  = double # CGAL_Integer

# Note that it is better to switch the precondition tests concerning
# exact computation off when using double coordinates
#
# Note furter that the compiler option -g0 is 'better' than -g for SUN Pro CC
#

CFLAGS =  -g0  $(CGAL_CFLAGS) -UCGAL_CHECK_EXACTNESS_PRECONDITIONS -DCARTESIAN 
           # -DHOMOGENEOUS

LDFLAGS =  $(CGAL_LDFLAGS) 


MAIN = -DMAIN -DCGAL_REPCLASS -DFIELDTYPE=$(FIELDTYPE) -DRINGTYPE=$(RINGTYPE) 


TWO_D  = Points2.C Vectors2.C Directions2.C \
         Lines2.C Rays2.C Segments2.C Triangles2.C\
	 Iso_rectangles2.C Intersection2.C

THREE_D = Points3.C Vectors3.C Directions3.C \
          Lines3.C Rays3.C Segments3.C\
          Planes3.C Triangles3.C  Tetrahedrons3.C 
          

TWO_D_OBJS = $(TWO_D:.C=.o)
THREE_D_OBJS = $(THREE_D:.C=.o)

all : two_d three_d

touch: 
	touch *.C

two_d: two_d.o $(TWO_D_OBJS)
	@echo "linking"
	$(CC) -o two_d  two_d.o $(TWO_D_OBJS)  $(LDFLAGS)

three_d: three_d.o  $(THREE_D_OBJS)
	@echo "linking"
	$(CC) -o three_d  three_d.o  $(THREE_D_OBJS)   $(LDFLAGS)


pvd2: pvd2.o Points2.o Vectors2.o Directions2.o
	$(CC) -o pvd2 pvd2.o Points2.o Vectors2.o Directions2.o  $(LDFLAGS)

intersection2 :  Intersection2.C
	$(CC) -o intersection2  Intersection2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

points2 : Points2.C
	$(CC) -o points2  Points2.C $(CFLAGS) $(MAIN)  $(LDFLAGS)

points3 : Points3.C 
	$(CC) -o points3 Points3.C  $(CFLAGS)  $(MAIN) $(LDFLAGS)

vectors2 : Vectors2.C
	$(CC) -o vectors2 Vectors2.C  $(CFLAGS) $(MAIN)   $(LDFLAGS)

vectors3 : Vectors3.C
	$(CC) -o vectors3 Vectors3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

directions2 : Directions2.C
	$(CC) -o directions2 Directions2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

directions3 : Directions3.C
	$(CC) -o directions3 Directions3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

lines2 : Lines2.C
	$(CC) -o lines2 Lines2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

lines3 : Lines3.C
	$(CC) -o lines3 Lines3.C  $(CFLAGS) $(MAIN) $(LDFLAGS) 

segments2 :  Segments2.C
	$(CC) -o segments2 Segments2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

segments3 : Segments3.C
	$(CC) -o segments3 Segments3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

rays2 : Rays2.C
	$(CC) -o rays2 Rays2.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)

rays3 : Rays3.C
	$(CC) -o rays3 Rays3.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)

planes3: Planes3.C
	$(CC) -o planes3 Planes3.C  $(CFLAGS) $(MAIN)   $(LDFLAGS)

triangles2 : Triangles2.C
	$(CC) -o triangles2 Triangles2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

triangles3 : Triangles3.C
	$(CC) -o triangles3 Triangles3.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)

tetrahedrons3 : Tetrahedrons3.C
	$(CC) -o tetrahedrons3 Tetrahedrons3.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)


transformations2: Transformations2.C
	$(CC) -o transformations2 Transformations2.C  $(CFLAGS)  $(MAIN) $(LDFLAGS)

transformations3: Transformations3.C
	$(CC) -o transformations3 Transformations3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

polygons2 : Polygons2.C
	$(CC) -o polygons2 Polygons2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

predicates2: Predicates.o
	$(CC) -o predicates2 Predicates2.o $(LDFLAGS) $(CGAL_WINDOW_LDFLAGS)

parabola2: Parabola2.o
	$(CC) -o parabola2 Parabola2.o $(CGAL_WINDOW_LDFLAGS)

map : map.C
	$(CC) -o map map.C  $(CFLAGS)  $(MAIN) $(LDFLAGS)

op : op.C
	$(CC) -o op op.C  $(CFLAGS)  $(MAIN) $(LDFLAGS)

.C.o:
	@echo "compiling "  $(notdir $<)
	$(CC)  $(CFLAGS)  -DCGAL_REPCLASS -DFIELDTYPE=$(FIELDTYPE) -DRINGTYPE=$(RINGTYPE) -c $<



