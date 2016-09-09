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
// file          : src/Color.C
// package       : iostream (2.1)
// source        : $RCSfile: Color.C,v $
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1999/03/08 13:28:32 $
// author(s)     : Andreas Fabri, Hervé Brönnimann
//
// coordinator   : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/config.h>
#include <CGAL/IO/Color.h>

CGAL_BEGIN_NAMESPACE

const Color BLACK  = Color(0, 0, 0);
const Color WHITE  = Color(255, 255, 255);
const Color RED    = Color(255, 0, 0);
const Color GREEN  = Color(0, 255, 0);
const Color BLUE   = Color(0, 0, 255);
const Color VIOLET = Color(255, 0, 255);
const Color ORANGE = Color(255, 170, 0);

CGAL_END_NAMESPACE
