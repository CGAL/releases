// ======================================================================
//
// Copyright (c) 1999,2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-2.3
// release_date  : 2001, August 13
// 
// file          : include/CGAL/known_bit_size_integers.h
// package       : Kernel_basic (3.53)
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2001/04/06 14:49:09 $
// author(s)     : Lutz Kettner
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_KNOWN_BIT_SIZE_INTEGERS_H
#define CGAL_KNOWN_BIT_SIZE_INTEGERS_H

CGAL_BEGIN_NAMESPACE

#if (defined(__sparc__) || defined(__sparc) || defined(sparc)) || \
    (defined(__sgi__)   || defined(__sgi)   || defined(sgi)) || \
    (defined(__i386__)  || defined(__i386)  || defined(i386)) || \
    (defined(__alpha__)  || defined(__alpha)  || defined(alpha)) || \
    (defined(__powerpc__) || defined(__powerpc) || defined(powerpc))
    typedef  signed char             Integer8;
    typedef  short                   Integer16;
    typedef  int                     Integer32;
    typedef  unsigned char           UInteger8;
    typedef  unsigned short          UInteger16;
    typedef  unsigned int            UInteger32;
    // See long_long.h for Integer64.
#else
#  if defined(__BORLANDC__)
    typedef  __int8                  Integer8;
    typedef  __int16                 Integer16;
    typedef  __int32                 Integer32;
    typedef  __int64                 Integer64;
    typedef  unsigned __int8         UInteger8;
    typedef  unsigned __int16        UInteger16;
    typedef  unsigned __int32        UInteger32;
    typedef  unsigned __int64        UInteger64;
#define CGAL_HAS_INTEGER64
#  else
#  if defined(_MSC_VER)
    typedef  signed char             Integer8;
    typedef  short                   Integer16;
    typedef  int                     Integer32;
    typedef  __int64                 Integer64;
    typedef  unsigned char           UInteger8;
    typedef  unsigned short          UInteger16;
    typedef  unsigned int            UInteger32;
    typedef  unsigned __int64        UInteger64;
#define CGAL_HAS_INTEGER64
#  else
#    error "patch this"
#  endif
#  endif
#endif

CGAL_END_NAMESPACE

#endif // CGAL_KNOWN_BIT_SIZE_INTEGERS_H
