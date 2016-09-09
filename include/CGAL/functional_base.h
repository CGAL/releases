// Copyright (c) 1997-2002  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Kernel_23/include/CGAL/functional_base.h,v $
// $Revision: 1.8 $ $Date: 2003/10/21 12:18:22 $
// $Name: current_submission $
//
// Author(s)     : Michael Hoffmann <hoffmann@inf.ethz.ch>
//                 Lutz Kettner

// Basics for CGAL Functors.

#ifndef CGAL_FUNCTIONAL_BASE_H
#define CGAL_FUNCTIONAL_BASE_H

#include <functional>

CGAL_BEGIN_NAMESPACE

// +----------------------------------------------------------------------+
// | Defining a Functors Arity (== #arguments)
// +----------------------------------------------------------------------+

template < int i > struct Arity_tag { enum { arity = i }; };

// use to deduce arity of functors --> allows binding std functors
#if !defined(_MSC_VER) || (_MSC_VER > 1300)

template < class T >
struct Arity_traits {
  typedef typename T::Arity Arity;
};

#else
// for VC7+ we do not have fixed the functors in stlport...

CGAL_END_NAMESPACE
#include <climits>
CGAL_BEGIN_NAMESPACE

namespace CGALi {

  template < class T >
  class First_argument_check {
    struct Big { char i[INT_MAX]; }; // hmm...
    typedef Big argument_type;
    struct Internal : public T {
      enum { s1 = sizeof(argument_type) };
    };
  public:
    enum { test = (Internal::s1 != sizeof(argument_type)) };
  };
  
  template < class T >
  class Second_argument_check {
    struct Big { char i[INT_MAX]; }; // hmm...
    typedef Big second_argument_type;
    struct Internal : public T {
      enum { s1 = sizeof(second_argument_type) };
    };
  public:
    enum { test = (Internal::s1 != sizeof(second_argument_type)) };
  };
  
  template < bool b1, bool b2> 
  struct Switch { 
    template < class F >
    struct Arity_tmp {
      typedef typename F::Arity Arity;
    };
  };
  
  template <> 
  struct Switch< true, false > { 
    template < class F >
    struct Arity_tmp {
      typedef Arity_tag< 1 > Arity; 
    };
  };
  
  template <> 
  struct Switch< false, true > { 
    template < class F >
    struct Arity_tmp {
      typedef Arity_tag< 2 > Arity; 
    };
  };
  
} // namespace CGALi

template < class F >
struct Arity_traits {
  typedef CGALi::Switch< CGALi::First_argument_check< F >::test, 
                         CGALi::Second_argument_check< F >::test >
  Switcher;
  typedef typename Switcher::template Arity_tmp< F >::Arity Arity;
};

#endif // !defined(_MSC_VER) || (_MSC_VER > 1300)

#ifndef CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION

// --------------------------------------------------------------------
// specializations for std functors:
//

template < class T >
struct Arity_traits< std::plus< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::minus< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::multiplies< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::divides< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::modulus< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::negate< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::equal_to< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::not_equal_to< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::greater< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::less< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::greater_equal< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::less_equal< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::logical_and< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::logical_or< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::logical_not< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::unary_negate< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::binary_negate< T > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T >
struct Arity_traits< std::binder1st< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T >
struct Arity_traits< std::binder2nd< T > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::pointer_to_unary_function< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::pointer_to_binary_function< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::mem_fun_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::mem_fun1_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::mem_fun_ref_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::mem_fun1_ref_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::const_mem_fun_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::const_mem_fun1_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};
template < class T1, class T2 >
struct Arity_traits< std::const_mem_fun_ref_t< T1, T2 > > {
  typedef Arity_tag< 1 > Arity;
};
template < class T1, class T2, class T3 >
struct Arity_traits< std::const_mem_fun1_ref_t< T1, T2, T3 > > {
  typedef Arity_tag< 2 > Arity;
};

#endif // ! CGAL_CFG_NO_PARTIAL_CLASS_TEMPLATE_SPECIALISATION

CGAL_END_NAMESPACE

#endif // CGAL_FUNCTIONAL_BASE_H
