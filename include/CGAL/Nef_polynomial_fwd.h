// Copyright (c) 1999,2003,2004,2005 Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Nef_2/include/CGAL/Nef_polynomial_fwd.h $
// $Id: Nef_polynomial_fwd.h 36878 2007-03-07 12:04:40Z spion $
// 
//
// Author(s)     : Andreas Fabri, Stefan Schirra, Sylvain Pion

#ifndef CGAL_NEF_POLYNOMIAL_FWD_H
#define CGAL_NEF_POLYNOMIAL_FWD_H

// Forward declarations of functions over Polynomial and Nef_polynomial

CGAL_BEGIN_NAMESPACE

namespace Nef { 
template <typename> class Polynomial;

template <typename ET> double to_double(const Polynomial<ET> &);

//template <typename ET>
//std::pair<double,double> to_interval(const Polynomial<ET> &);

template <typename ET>
Sign sign(const Polynomial<ET> &);

template <typename ET>
Polynomial<ET> abs(const Polynomial<ET> &);

template <typename ET>
Polynomial<ET> gcd(const Polynomial<ET> &, const Polynomial<ET> &);

}
// Nef_polynomial

template <typename> class Nef_polynomial;


CGAL_END_NAMESPACE

#endif // CGAL_NEF_POLYNOMIAL_FWD_H
