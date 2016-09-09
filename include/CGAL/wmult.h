//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

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
