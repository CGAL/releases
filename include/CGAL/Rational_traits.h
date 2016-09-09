// Copyright (c) 2006-2007 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Algebraic_foundations/include/CGAL/Rational_traits.h $
// $Id: Rational_traits.h 51456 2009-08-24 17:10:04Z spion $
//
//
// Author(s)     : Michael Hemmer    <hemmer@mpi-inf.mpg.de>
//
// =============================================================================

// This file is for backward compatibility 
// Rational_traits will be replaced by Fraction_traits

#ifndef CGAL_RATIONAL_TRAITS_H
#define CGAL_RATIONAL_TRAITS_H 

#include <CGAL/number_type_basic.h>
#include <CGAL/Fraction_traits.h>

CGAL_BEGIN_NAMESPACE

namespace internal{

template <class Rational, bool > 
struct Rational_traits_base
{
    typedef Rational RT;
    
    const RT& numerator   (const Rational& r) const { return r; }
    RT denominator (const Rational&) const { return RT(1); }
    
    Rational make_rational(const RT & n, const RT & d) const
    { return n / d; } 
};

template <class Rational> 
struct Rational_traits_base<Rational, true>
{
private:
    typedef Fraction_traits<Rational> FT;
    typedef typename FT::Decompose Decomose;
    typedef typename FT::Compose Compose;

public:
    typedef typename FT::Numerator_type RT;
    
    RT numerator (const Rational& r) const {
        RT num,den; 
        Decomose()(r,num,den);
        return num;
    }

    RT denominator (const Rational& r) const { 
        RT num,den; 
        Decomose()(r,num,den); 
        return den; 
    }
    
    Rational make_rational(const RT & n, const RT & d) const
    { return Compose()(n,d); } 
    Rational make_rational(const Rational & n, const Rational & d) const
    { return n/d; } 
};
}// namespace internal

// use Fraction_traits if Is_fraction && Num and Den are the same 
template <class T>
class Rational_traits 
    : public internal::Rational_traits_base<T,
::boost::is_same<typename Fraction_traits<T>::Is_fraction,Tag_true>::value 
&&
::boost::is_same<
typename Fraction_traits<T>::Numerator_type,
typename Fraction_traits<T>::Denominator_type
>::value >
{};

CGAL_END_NAMESPACE

#endif // CGAL_RATIONAL_TRAITS_H
// EOF

