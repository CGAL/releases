/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

// Source: cartesian_classes.h
// Author: Andreas Fabri

#ifndef CGAL_CARTESIAN_CLASSES_H
#define CGAL_CARTESIAN_CLASSES_H


#include <CGAL/basic_classes.h>

template < class FT >
class CGAL_PointC2;

template < class FT >
class CGAL_VectorC2;

template < class FT >
class CGAL_DirectionC2;

template < class FT >
class CGAL_LineC2;

template < class FT >
class CGAL_RayC2;

template < class FT >
class CGAL_SegmentC2;

template < class FT >
class CGAL_TriangleC2;

template < class FT >
class CGAL_CircleC2;

template < class FT >
class CGAL_ParabolaC2;

template < class FT >
class CGAL_Parabola_arcC2;

template < class FT >
class CGAL_Iso_rectangleC2;

template < class FT >
class CGAL_Iso_rectangleC3;

template < class FT >
class CGAL_Aff_transformation_baseC2;

template < class R >
class CGAL_Aff_transformation_base_2;

template < class FT >
class CGAL_Aff_transformationC2;

template < class FT >
class CGAL_PlaneC3;

template < class FT >
class CGAL_PointC3;

template < class FT >
class CGAL_VectorC3;

template < class FT >
class CGAL_DirectionC3;

template < class FT >
class CGAL_LineC3;

template < class FT >
class CGAL_RayC3;

template < class FT >
class CGAL_SegmentC3;

template < class FT >
class CGAL_TriangleC3;

template < class FT >
class CGAL_TetrahedronC3;

template < class FT >
class CGAL_Aff_transformationC3;

class dint;  // integers in the range of [..] stored in a double

#endif // CGAL_CARTESIAN_CLASSES_H
