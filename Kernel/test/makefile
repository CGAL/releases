

# This is a makefile to make testsuites for the CGAL Kernel
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
#     It is a good idea to put all these lines in comments and to
#     define an environment variable in your .profile or .login
#
#     Pay attention not to put a blank behind the OS name!!!
#
#CGAL_OSTYPE =irix5 
#CGAL_OSTYPE =sun4OS4
CGAL_OSTYPE =sun4OS5



# (3) The Home Directory of LEDA
#
# symbolic link to the distribution
LEDA_DIR = $(HOME)/Leda

# (4) The Home Directory of CGAL
#
# symbolic link to the distribution
CGAL_DIR = $(HOME)/Cgal


# If the makefiles for Cgal are not under $(CGAL_DIR) you
# have to change the following:

CGAL_MAKE_DIR = $(CGAL_DIR)/MAKE

# If the header files and the libraries are not installed in 
# subdirectories of the LEDA/CGAL root files, you may have to
# change the following too:
 

CGAL_INCL_DIR = $(CGAL_DIR)/include
CGAL_LIB_DIR = $(CGAL_DIR)/lib/$(CGAL_OSTYPE)_$(CC)



LEDA_INCL_DIR = $(LEDA_DIR)/incl
LEDA_LIB_DIR = $(LEDA_DIR)/lib/$(CGAL_OSTYPE)_$(CC)




#..........................................................................
# Don't edit the following line
include $(CGAL_MAKE_DIR)/$(CGAL_OSTYPE)_$(CC)/application
#..........................................................................


# add YOUR compiler and linker flags here.
# NEVER remove the CGAL compile or link flags.

CFLAGS = $(CGAL_FLAG_G)   -g $(CGAL_CFLAGS) -DCARTESIAN -I./include -UCGAL_CHECK_PRECONDITIONS
LDFLAGS = $(CGAL_LDFLAGS) 

PURE_CGAL_LDFLAGS = -L$(CGAL_LIB_DIR)  -R$(CGAL_LIB_DIR) \
                    -l$(CGAL_LIB_NAME)  -lm


#..........................................................................

FIELDTYPE = CGAL_Double_eps # CGAL_Rational 
RINGTYPE  = CGAL_Double_eps # double # CGAL_Integer


MAIN = -DMAIN -DCGAL_REPCLASS -DFIELDTYPE=$(FIELDTYPE) -DRINGTYPE=$(RINGTYPE) 


TWO_D  = Point2.C Vector2.C Direction2.C \
         Line2.C Ray2.C Segment2.C Triangle2.C\
	 Iso_rectangle2.C Intersection2.C \
         Transformation2.C

THREE_D = Point3.C Vector3.C Direction3.C \
          Line3.C Ray3.C Segment3.C\
          Plane3.C Triangle3.C  Tetrahedron3.C 
          

TWO_D_OBJS = $(TWO_D:.C=.o)
THREE_D_OBJS = $(THREE_D:.C=.o)

all : two_d three_d

touch: 
	touch *.C

test_kernel_2: test_kernel_2.o
	$(CC) -o test_kernel_2 test_kernel_2.o  $(LDFLAGS)

test_kernel_3: test_kernel_3.o
	$(CC) -o test_kernel_3 test_kernel_3.o $(LDFLAGS)

rot: rot.o
	$(CC) -o rot rot.o $(LDFLAGS)

two_d: two_d.o $(TWO_D_OBJS)
	@echo "linking"
	$(CC) -o two_d  two_d.o $(TWO_D_OBJS)  $(LDFLAGS)

three_d: three_d.o  $(THREE_D_OBJS)
	@echo "linking"
	$(CC) -o three_d  three_d.o  $(THREE_D_OBJS)   $(LDFLAGS)


pvd2: pvd2.o Point2.o Vector2.o Direction2.o
	$(CC) -o pvd2 pvd2.o Point2.o Vector2.o Direction2.o  $(LDFLAGS)

pure: pure.C
	$(CC) -H -o pure pure.C $(PURE_CGAL_CFLAGS) -DCARTESIAN $(PURE_CGAL_LDFLAGS)

intersection2 :  Intersection2.C
	$(CC) -o intersection2  Intersection2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

point2 : Point2.C
	$(CC) -o point2  Point2.C $(CFLAGS) $(MAIN)  $(LDFLAGS)

point3 : Point3.C 
	$(CC) -o point3 Point3.C  $(CFLAGS)  $(MAIN) $(LDFLAGS)

vector2 : Vector2.C
	$(CC) -o vector2 Vector2.C  $(CFLAGS) $(MAIN)   $(LDFLAGS)

vector3 : Vector3.C
	$(CC) -o vector3 Vector3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

direction2 : Direction2.C
	$(CC) -o direction2 Direction2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

direction3 : Direction3.C
	$(CC) -o direction3 Direction3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

line2 : Line2.C
	$(CC) -o line2 Line2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

line3 : Line3.C
	$(CC) -o line3 Line3.C  $(CFLAGS) $(MAIN) $(LDFLAGS) 

segment2 :  Segment2.C
	$(CC) -o segment2 Segment2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

segment3 : Segment3.C
	$(CC) -o segment3 Segment3.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

ray2 : Ray2.C
	$(CC) -o ray2 Ray2.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)

ray3 : Ray3.C
	$(CC) -o ray3 Ray3.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)

plane3: Plane3.C
	$(CC) -o plane3 Plane3.C  $(CFLAGS) $(MAIN)   $(LDFLAGS)

triangle2 : Triangle2.C
	$(CC) -o triangle2 Triangle2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

triangle3 : Triangle3.C
	$(CC) -o triangle3 Triangle3.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)

circle2 : Circle2.C
	$(CC) -o circle2 Circle2.C  $(CFLAGS) $(MAIN) $(LDFLAGS)

tetrahedron3 : Tetrahedron3.C
	$(CC) -o tetrahedron3 Tetrahedron3.C  $(CFLAGS) $(MAIN)  $(LDFLAGS)


transformation2: Transformation2.C
	$(CC) -o transformation2 Transformation2.C  $(CFLAGS)  $(MAIN) $(LDFLAGS)

transformation3: Transformation3.o
	$(CC) -o transformation3 Transformation3.o  $(CFLAGS) $(MAIN) $(LDFLAGS)

predicate2: Predicates.o
	$(CC) -o predicate2 Predicate2.o $(LDFLAGS) $(CGAL_WINDOW_LDFLAGS)

parabola2: Parabola2.o
	$(CC) -o parabola2 Parabola2.o $(CGAL_WINDOW_LDFLAGS)


.C.o:
	@echo "compiling "  $(notdir $<)
	$(CC)  $(CFLAGS)   -DCGAL_REPCLASS -DFIELDTYPE=$(FIELDTYPE) -DRINGTYPE=$(RINGTYPE) -c $<



