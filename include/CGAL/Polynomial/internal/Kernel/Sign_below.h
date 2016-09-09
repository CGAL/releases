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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Polynomial/internal/Kernel/Sign_below.h $
// $Id: Sign_below.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_INTERNAL_BELOW_AT_ROOT_H
#define CGAL_POLYNOMIAL_INTERNAL_BELOW_AT_ROOT_H

#include <CGAL/Polynomial/basic.h>
#include <CGAL/Polynomial/internal/Rational/Sign_below_rational.h>

namespace CGAL { namespace POLYNOMIAL { namespace internal {

//! Compute the sign after a root.
/*!
  This has specializations for Explicit_roots.
*/
template <class R, class K>
class Sign_below: public Sign_below_rational<K>
{
  typedef Sign_below_rational<K> P;
public:
  Sign_below( K k): P(k) {
  }
  Sign_below(){}
  using P::operator();
  typedef typename K::Function first_argument_type;
  typedef typename K::Root second_argument_type;
  typedef CGAL::Sign result_type;
  result_type operator()(const typename K::Function &p,
				     const typename K::Root &v) const
  {
    CGAL_Polynomial_precondition(0);
    return ZERO;
  }
  
};

} } } //namespace CGAL::POLYNOMIAL::internal
#endif
