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
// file          : include/CGAL/wmult.h
// author(s)     : Geert-Jan Giezeman
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_WMULT_H
#define CGAL_WMULT_H

#ifdef CGAL_HOMOGENEOUS_H
template <class RT>
inline RT CGAL_wmult(CGAL_Homogeneous<RT>*, const RT &a, const RT & w)
{
    return a*w;
}

template <class RT>
inline RT CGAL_wmult(CGAL_Homogeneous<RT>*,
         const RT &a, const RT & w1, const RT & w2)
{
    return a*w1*w2;
}

template <class RT>
inline RT CGAL_wmult(CGAL_Homogeneous<RT>*, const RT &a,
                    const RT & w1, const RT & w2, const RT & w3)
{
    return a*w1*w2*w3;
}

template <class RT>
inline RT CGAL_wmult(CGAL_Homogeneous<RT>*, const RT &a,
                const RT & w1, const RT & w2, const RT & w3, const RT & w4)
{
    return a*w1*w2*w3*w4;
}
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
template <class RT>
inline RT CGAL_wmult(CGAL_Cartesian<RT> *, const RT &a, const RT & )
{
    return a;
}

template <class RT>
inline RT CGAL_wmult(CGAL_Cartesian<RT> *,
      const RT &a, const RT & , const RT & )
{
    return a;
}

template <class RT>
inline RT CGAL_wmult(CGAL_Cartesian<RT> *, const RT &a,
            const RT & , const RT & , const RT & )
{
    return a;
}

template <class RT>
inline RT CGAL_wmult(CGAL_Cartesian<RT> *, const RT &a,
            const RT & , const RT & , const RT & , const RT & )
{
    return a;
}
#endif // CGAL_CARTESIAN_H

#endif // CGAL_WMULT_H