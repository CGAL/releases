// Copyright (c) 2006-2008 Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Number_types/include/CGAL/Sqrt_extension/Scalar_factor_traits.h $
// $Id: Scalar_factor_traits.h 56667 2010-06-09 07:37:13Z sloriot $
//
//
// Author(s)     : Michael Hemmer   <hemmer@mpi-inf.mpg.de>


#ifndef CGAL_SQRT_EXTENSION_SCALAR_FACTOR_TRAITS_H
#define CGAL_SQRT_EXTENSION_SCALAR_FACTOR_TRAITS_H

#include <CGAL/basic.h>

namespace CGAL {

// This is the specialization for Sqrt_extension
template <class COEFF, class INTERNAL>
class Scalar_factor_traits< Sqrt_extension<COEFF, INTERNAL> > {
public:

    //! the number type for which this instance has been instantiated
    typedef Sqrt_extension<COEFF, INTERNAL> NT;
      //! the number type of scalars that can be extracted from NT
    typedef typename Scalar_factor_traits<COEFF>::Scalar Scalar;

    class Scalar_factor
    {
    public:
        //! argument type
        typedef NT argument_type;
        //! first argument type
        typedef NT first_argument_type;
        //! second argument type
        typedef Scalar second_argument_type;
        //! result type
        typedef Scalar result_type;

        Scalar
        operator () (const NT& x, const Scalar& d_ = Scalar(0) ) {
            typename Scalar_factor_traits<COEFF>::Scalar_factor sfac;

            Scalar d(d_);
            Scalar unity(1);
            if(d==unity) return d;
            d=sfac(x.a0(),d);
            if(d==unity) return d;
            if(x.is_extended())
                d=sfac(x.a1(),d);
            return d;
        }
    };

    class Scalar_div
    {
    public:
        //! first_argument_type
        typedef NT first_argument_type;
        //! second_argument_type
        typedef Scalar second_argument_type;
        //! divides an extension \c a by a scalar factor \c b
        void operator () (NT& a, const Scalar& b) {
            CGAL_precondition(b != Scalar(0));
            typename Scalar_factor_traits<COEFF>::Scalar_div sdiv;
            sdiv(a.a0(), b); sdiv(a.a1(), b); // perform division in place
        }
    };
};

} //namespace CGAL

#endif
