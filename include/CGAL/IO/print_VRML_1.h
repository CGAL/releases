// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/IO/print_VRML_1.h
// package       : Polyhedron_IO (2.5)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/03/24 11:16:26 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Print a Polyhedron_3 in VRML 1.0 file format (.wrl)
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_PRINT_VRML_1_H
#define CGAL_IO_PRINT_VRML_1_H 1
#ifndef CGAL_IO_POLYHEDRON_VRML_1_OSTREAM_H
#include <CGAL/IO/Polyhedron_VRML_1_ostream.h>
#endif // CGAL_IO_POLYHEDRON_VRML_1_OSTREAM_H

CGAL_BEGIN_NAMESPACE

template <class Traits, class HDS>
void
print_VRML_1( std::ostream& out, const Polyhedron_3<Traits,HDS>& P) {
    VRML_1_ostream os( out);
    os << P;
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_PRINT_VRML_1_H //
// EOF //
