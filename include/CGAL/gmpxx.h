// Copyright (c) 2002,2003  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Number_types/include/CGAL/gmpxx.h $
// $Id: gmpxx.h 44360 2008-07-23 14:36:49Z hoffmann $
//
//
// Author(s)     : Sylvain Pion

// This file gathers the necessary adaptors so that the following
// C++ number types that come with GMP can be used by CGAL :
// - mpz_class (see #include <CGAL/mpz_class.h>)
// - mpq_class (see #include <CGAL/mpq_class.h>)

// - mpf_class support is commented out until to_interval() is implemented.
//   It is probably not very useful with CGAL anyway.

// Note that GMP++ use the expression template mechanism, which makes things
// a little bit complicated in order to make square(x+y) work for example.
// Reading gmpxx.h shows that ::__gmp_expr<T, T> is the mp[zqf]_class proper,
// while ::__gmp_expr<T, U> is the others "expressions".

#ifndef CGAL_GMPXX_H
#define CGAL_GMPXX_H

#include <CGAL/number_type_basic.h>

#include <cstring> // needed by GMP 4.1.4 since <gmpxx.h> misses it.
#include <gmpxx.h>
#include <utility>

#include <CGAL/mpz_class.h>
#include <CGAL/mpq_class.h>
#include <CGAL/gmpxx_coercion_traits.h>

CGAL_BEGIN_NAMESPACE


template < typename T, typename U >
class Algebraic_structure_traits< ::__gmp_expr<T,U> >
    : public Algebraic_structure_traits< ::__gmp_expr<T,T> >{};

template < typename T, typename U >
class Real_embeddable_traits< ::__gmp_expr<T,U> >
    : public Real_embeddable_traits< ::__gmp_expr<T,T> >{};

CGAL_END_NAMESPACE

#endif // CGAL_GMPXX_H
