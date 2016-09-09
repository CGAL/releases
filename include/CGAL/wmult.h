// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// file          : include/CGAL/wmult.h
// package       : Distance_2 (2.4.2)
// source        : sqdistance_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_WMULT_H
#define CGAL_WMULT_H

CGAL_BEGIN_NAMESPACE


#if defined CGAL_HOMOGENEOUS_H
template <class RT>
inline RT wmult(Homogeneous<RT>*, const RT &a, const RT & w)
{
    return a*w;
}

template <class RT>
inline RT wmult(Homogeneous<RT>*,
         const RT &a, const RT & w1, const RT & w2)
{
    return a*w1*w2;
}

template <class RT>
inline RT wmult(Homogeneous<RT>*, const RT &a,
                    const RT & w1, const RT & w2, const RT & w3)
{
    return a*w1*w2*w3;
}

template <class RT>
inline RT wmult(Homogeneous<RT>*, const RT &a,
                const RT & w1, const RT & w2, const RT & w3, const RT & w4)
{
    return a*w1*w2*w3*w4;
}
#endif // CGAL_HOMOGENEOUS_H

#if defined CGAL_SIMPLE_HOMOGENEOUS_H
template <class RT>
inline RT wmult(Simple_homogeneous<RT>*, const RT &a, const RT & w)
{
    return a*w;
}

template <class RT>
inline RT wmult(Simple_homogeneous<RT>*,
         const RT &a, const RT & w1, const RT & w2)
{
    return a*w1*w2;
}

template <class RT>
inline RT wmult(Simple_homogeneous<RT>*, const RT &a,
                    const RT & w1, const RT & w2, const RT & w3)
{
    return a*w1*w2*w3;
}

template <class RT>
inline RT wmult(Simple_homogeneous<RT>*, const RT &a,
                const RT & w1, const RT & w2, const RT & w3, const RT & w4)
{
    return a*w1*w2*w3*w4;
}
#endif // CGAL_SIMPLE_HOMOGENEOUS_H

#if defined CGAL_CARTESIAN_H
template <class RT>
inline RT wmult(Cartesian<RT> *, const RT &a, const RT & )
{
    return a;
}

template <class RT>
inline RT wmult(Cartesian<RT> *,
      const RT &a, const RT & , const RT & )
{
    return a;
}

template <class RT>
inline RT wmult(Cartesian<RT> *, const RT &a,
            const RT & , const RT & , const RT & )
{
    return a;
}

template <class RT>
inline RT wmult(Cartesian<RT> *, const RT &a,
            const RT & , const RT & , const RT & , const RT & )
{
    return a;
}
#endif // CGAL_CARTESIAN_H

#if defined CGAL_SIMPLE_CARTESIAN_H
template <class RT>
inline RT wmult(Simple_cartesian<RT> *, const RT &a, const RT & )
{
    return a;
}

template <class RT>
inline RT wmult(Simple_cartesian<RT> *,
      const RT &a, const RT & , const RT & )
{
    return a;
}

template <class RT>
inline RT wmult(Simple_cartesian<RT> *, const RT &a,
            const RT & , const RT & , const RT & )
{
    return a;
}

template <class RT>
inline RT wmult(Simple_cartesian<RT> *, const RT &a,
            const RT & , const RT & , const RT & , const RT & )
{
    return a;
}
#endif // CGAL_SIMPLE_CARTESIAN_H

CGAL_END_NAMESPACE

#endif // CGAL_WMULT_H
