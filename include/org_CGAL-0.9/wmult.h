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


// Author: Geert-Jan Giezeman

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
