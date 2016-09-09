// ======================================================================
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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.2
// release_date  : 1999, January 18
// 
// source        : basic.fw
// file          : include/CGAL/known_bit_size_integers.h
// package       : Kernel_basic (1.2.12)
// revision      : 1.2.12
// revision_date : 08 Jan 1999 
// author(s)     : Lutz Kettner
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#define CGAL_KNOWN_BIT_SIZE_INTEGERS_H

#if (defined(__sparc__) || defined(__sparc) || defined(sparc)) || \
    (defined(__sgi__)   || defined(__sgi)   || defined(sgi)) || \
    (defined(__i386__)  || defined(__i386)  || defined(i386))
    typedef  signed char             CGAL_Integer8;
    typedef  short                   CGAL_Integer16;
    typedef  int                     CGAL_Integer32;
    typedef  long long int           CGAL_Integer64;
    typedef  unsigned char           CGAL_UInteger8;
    typedef  unsigned short          CGAL_UInteger16;
    typedef  unsigned int            CGAL_UInteger32;
    typedef  unsigned long long int  CGAL_UInteger64;
#else
#  error "patch this"
#endif

#endif // CGAL_KNOWN_BIT_SIZE_INTEGERS_H
