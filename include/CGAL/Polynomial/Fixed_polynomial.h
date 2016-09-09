// Copyright (c) 2005  Stanford University (USA).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Kinetic_data_structures/include/CGAL/Polynomial/Fixed_polynomial.h $
// $Id: Fixed_polynomial.h 33689 2006-08-24 15:54:13Z drussel $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_FIXED_POLYNOMIAL_POLYNOMIAL_H_
#define CGAL_FIXED_POLYNOMIAL_POLYNOMIAL_H_
#include <CGAL/Polynomial/basic.h>


#include <CGAL/Polynomial/internal/Fixed_polynomial_impl.h>
//#include <utility>
#include <sstream>

CGAL_POLYNOMIAL_BEGIN_NAMESPACE

//! A basic polynomial class
/*!  The implementation is proved by internal::Polynomial_impl. This
  strips leading 0s. When debugging is on, a string representation of
  the polynomial is stored. This is fairly key for debugging, but
  rather slow.
*/
template <class NTT, int D>
class Fixed_polynomial: public internal::Fixed_polynomial_impl<Fixed_polynomial<NTT, D>, NTT, D>
{
  typedef Fixed_polynomial<NTT, D> This;
  typedef internal::Fixed_polynomial_impl<This, NTT, D>  Parent;

public:
  
  // hack to try to fix pgCC
  //using typename Parent::iterator;
  typedef typename Parent::iterator iterator;

  //================
  // CONSTRUCTORS
  //================

  //! Default
  Fixed_polynomial() {
  }

  //! Make a constant polynomial
  Fixed_polynomial(const NTT& c): Parent(c) {
  }

  //! Make a polynomial from an iterator range
  template<typename Iterator>
  Fixed_polynomial(Iterator first, Iterator beyond)
    : Parent(first,beyond) {
  }

  Fixed_polynomial(const Parent &p): Parent(p) {
  }

};

CGAL_POLYNOMIAL_END_NAMESPACE
#endif
