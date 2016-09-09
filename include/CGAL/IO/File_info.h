// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/IO/File_info.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_IO_FILE_INFO_H
#define CGAL_IO_FILE_INFO_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifdef CGAL_IO_FILE_INFO_H
#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif
#ifndef CGAL_VECTOR_3_H
#include <CGAL/Vector_3.h>
#endif
#ifndef CGAL_AFF_TRANSFORMATION_3_H
#include <CGAL/Aff_transformation_3.h>
#endif
#else // CGAL_IO_FILE_INFO_H //
// This is code from the CEBAP project and useless in CGAL.
#ifndef CGAL__MATRIX_3_H
#include <CGAL/_Matrix_3.h>
#endif
#endif // CGAL_IO_FILE_INFO_H //

struct  CGAL_File_info {
#ifdef CGAL_IO_FILE_INFO_H
    typedef  CGAL_Aff_transformation_3< CGAL_Cartesian<double> >  Matrix;
    typedef  CGAL_Vector_3< CGAL_Cartesian<double> >              Vector;
#else // CGAL_IO_FILE_INFO_H //
    // This is code from the CEBAP project now useless in CGAL.
    typedef  CGAL__Matrix_3<double>  Matrix;
    typedef  CGAL_Vector_3<double>  Vector;
#endif

    Matrix   linear;
    bool     normalized_to_sphere;
    double   radius;
    bool     rounded;
    int      rounded_bits;
    bool     terrain;
    Vector   terrain_vector;

    CGAL_File_info() :
#ifdef CGAL_IO_FILE_INFO_H
        linear                ( CGAL_SCALING, 1.0),
#else // CGAL_IO_FILE_INFO_H //
        // This is code from the CEBAP project now useless in CGAL.
        linear                ( 1.0),
#endif
        normalized_to_sphere  ( false),
        radius                ( 0.0),
        rounded               ( false),
        rounded_bits          ( 0),
        terrain               ( false),
        terrain_vector        ( 0.0, 0.0, 0.0)
    {}
};
#endif // CGAL_IO_FILE_INFO_H //
// EOF //
