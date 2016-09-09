// Copyright (c) 2009 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Polynomial/include/CGAL/Polynomial/Degree.h $
// $Id: Degree.h 52628 2009-10-20 08:59:26Z lrineau $
// 
//
// Author(s)     : Michael Hemmer <hemmer@mpi-inf.mpg.de> 
//
// ============================================================================


#ifndef CGAL_POLYNOMIAL_DEGREE_H
#define CGAL_POLYNOMIAL_DEGREE_H

#include <CGAL/Exponent_vector.h>
#include <CGAL/Polynomial/misc.h>


CGAL_BEGIN_NAMESPACE

namespace internal{

template <typename Polynomial > struct Degree;

// Polynomial musst be at least univariate ! 
template <typename Coeff_ > 
struct Degree<Polynomial<Coeff_> >
  : public std::unary_function< Polynomial<Coeff_> , int  >{
  
private: 
  typedef Polynomial<Coeff_> Polynomial_d;
  
  // for univariate polynomials 
  template <typename Coeff>
  int degree(const Polynomial<Coeff>& p, int i) const {
    (void) i; 
    CGAL_assertion(i == 0);
    return p.degree();
  }
  
  // for multivariate polynomials
  template <typename Coeff>
  int degree(const Polynomial<Polynomial<Coeff> >& p, int i) const {
    typedef Polynomial<Polynomial<Coeff> > Poly;
    
    if(i == (Dimension<Poly>::value-1))
      return p.degree();
    
    int result = 0;
    for(typename Poly::const_iterator it = p.begin(); it != p.end(); it++){
      result = (std::max)(result,degree(*it,i));
    }
    return result; 
  }

public:
  int operator()(
      const Polynomial_d& p, 
      int i = (Dimension<Polynomial_d>::value-1)) const {
    CGAL_assertion(i < Dimension<Polynomial_d>::value);
    CGAL_assertion(i >= 0);
    int result =  this->degree(p,i);
    CGAL_assertion_code(typename Polynomial_traits_d<Polynomial_d>::Swap swap;); 
    CGAL_assertion(swap(p,i,Dimension<Polynomial_d>::value-1).degree()==result);
    return result; 
  }     

};

} // namespace internal
CGAL_END_NAMESPACE

#endif //CGAL_POLYNOMIAL_DEGREE_H
