// Copyright (c) 2008 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.6-branch/Polynomial/include/CGAL/Polynomial_type_generator.h $
// $Id: Polynomial_type_generator.h 52628 2009-10-20 08:59:26Z lrineau $
// 
//
// Author(s)     : Michael Hemmer <hemmer@informatik.uni-mainz.de> 
//
// ========================================================================


#ifndef CGAL_POLYNOMIAL_TYPE_GENERATOR_H
#define CGAL_POLYNOMIAL_TYPE_GENERATOR_H

#include <CGAL/Polynomial_traits_d.h>

CGAL_BEGIN_NAMESPACE

template <class T, int d>
struct Polynomial_type_generator
{
private:
  typedef typename Polynomial_type_generator<T,d-1>::Type Coeff; 
public:
  typedef CGAL::Polynomial<Coeff> Type;
};

template <class T>
struct Polynomial_type_generator<T,0>{ typedef T Type; };

CGAL_END_NAMESPACE

#endif // CGAL_POLYNOMIAL_GENERATOR_H
