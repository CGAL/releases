include ../makefile

CFLAGS = -g0  $(CGALFLAGS)

vpath %.h  $(CGAL)/include/CGAL

HEADERS = Onetuple.h Twotuple.h Threetuple.h Fourtuple.h Sixtuple.h \
       Origin.h cartesian_classes.h enum.h \
       misc.h utils.h doublefield.h error.h\
       solve.h determinant.h\
       Point_2.h PointC2.h \
       Vector_2.h  VectorC2.h \
       Direction_2.h DirectionC2.h \
       Segment_2.h SegmentC2.h \
       Line_2.h LineC2.h \
       Ray_2.h RayC2.h\
       Ordertype_2.h OrdertypeC2.h\
       Bbox_2.h


LIBSOURCES = Origin.C OrdertypeC2.C error.C Bbox_2.C doublefield.C


LIBOBJS = $(LIBSOURCES:.C=.o)


$(CGALLIB): $(HEADERS) $(LIBOBJS) 
	@echo "creating " $(notdir $(CGALLIB))
	@$(CC) -xar -o $(CGALLIB) $(LIBOBJS)

.C.o:
	@echo "compiling "  $(notdir $<)
	@$(CC)  $(CFLAGS)   -c $<
