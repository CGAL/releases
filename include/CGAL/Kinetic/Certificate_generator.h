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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Kinetic_data_structures/include/CGAL/Kinetic/Certificate_generator.h $
// $Id: Certificate_generator.h 36638 2007-02-27 22:45:58Z drussel $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_KINETIC_IO_KERNEL_CERTIFICATE_GENERATOR_H
#define CGAL_KINETIC_IO_KERNEL_CERTIFICATE_GENERATOR_H
#include <CGAL/Kinetic/basic.h>
//#include <CGAL/Kinetic/internal/Kernel/Certificate.h>
CGAL_KINETIC_BEGIN_NAMESPACE
template <class KK_t, class Generator>
struct Certificate_generator {
  typedef typename KK_t::Certificate result_type;
  typedef typename KK_t::Function_kernel::Root Time;
  Certificate_generator(typename KK_t::Function_kernel fk): fk_(fk){}
  Certificate_generator(){}
  

  template <class A, class B, class C, class D, class E>
  result_type operator()(const A &a, const B &b, const C &c, const D &d, const E &e, const Time &begin, const Time &end) const {
    return result_type(gen_(a, b, c, d, e), fk_, begin, end);
  }
  template <class A, class B, class C, class D>
  result_type operator()(const A &a, const B &b, const C &c, const D &d, const Time &begin, const Time &end) const {
    return result_type(gen_(a, b, c, d), fk_, begin, end);
  }
  template <class A, class B, class C>
  result_type operator()(const A &a, const B &b, const C &c, const Time &begin, const Time &end) const {
    return result_type(gen_(a, b, c), fk_, begin, end);
  }
  template <class A, class B>
  result_type operator()(const A &a, const B &b, const Time &begin, const Time &end) const {
    return result_type(gen_(a, b), fk_, begin, end);
  }
  template <class A>
  result_type operator()(const A &a, const Time &begin, const Time &end) const {
    return result_type(gen_(a), fk_,begin,end);
  }


  template <class A, class B, class C, class D, class E>
  CGAL::Sign operator()(const A &a, const B &b, const C &c, const D &d, const E &e, const Time &begin, bool after=false) const {
    if (after) {
      return sign_after(gen_(a, b, c, d, e), begin);
    } else {
      return sign_at(gen_(a,b,c,d,e), begin);
    }
  }
  template <class A, class B, class C, class D>
  CGAL::Sign operator()(const A &a, const B &b, const C &c, const D &d, const Time &begin, bool after=false) const {
    if (after) {
      return sign_after(gen_(a, b, c, d), begin);
    } else {
      return sign_at(gen_(a,b,c,d), begin);
    }
  }
  template <class A, class B, class C>
  CGAL::Sign operator()(const A &a, const B &b, const C &c, const Time &begin, bool after=false) const {
    if (after) {
      return sign_after(gen_(a, b, c), begin);
    } else {
      return sign_at(gen_(a,b,c), begin);
    }
  }
  template <class A, class B>
  CGAL::Sign operator()(const A &a, const B &b, const Time &begin, bool after=false) const {
    if (after) {
      return sign_after(gen_(a, b), begin);
    } else {
      return sign_at(gen_(a, b), begin);
    }
  }
  template <class A>
  CGAL::Sign operator()(const A &a, const Time &begin, bool after=false) const {
    if (after) {
      return sign_after(gen_(a), begin);
    } else {
      return sign_at(gen_(a), begin);
    }
  }

protected:
  CGAL::Sign sign_after(const typename KK_t::Function_kernel::Function &f,
			const Time &t) const {
    return fk_.sign_after_object()(f,t);
  }
  CGAL::Sign sign_at(const typename KK_t::Function_kernel::Function &f,
			const Time &t) const {
    return fk_.sign_at_object()(f,t);
  }
  
  Generator gen_;
  typename KK_t::Function_kernel fk_;
};

CGAL_KINETIC_END_NAMESPACE

#endif
