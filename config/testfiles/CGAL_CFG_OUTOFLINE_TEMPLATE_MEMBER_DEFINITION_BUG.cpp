// Copyright (c) 2003  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/testfiles/CGAL_CFG_OUTOFLINE_TEMPLATE_MEMBER_DEFINITION_BUG.cpp $
// $Id: CGAL_CFG_OUTOFLINE_TEMPLATE_MEMBER_DEFINITION_BUG.cpp 37704 2007-03-30 08:39:31Z spion $
// 
//
// Author(s)     : Radu Ursu

// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| The flag CGAL_CFG_OUTOFLINE_TEMPLATE_MEMBER_DEFINITION_BUG is set,
//| if a compiler does not support the definition of member templates
//| out of line, i.e. outside class scope. The solution is to put the
//| definition inside the class. This is a feature of SunPro 5.5.

template <class A>
class B {
public:
  typedef typename A::D Res;

  template<class C>
  Res fct(C *i);
};

template<class A>
template<class C>  //syntax error
typename B<A>::Res
B<A>::fct(C *i)
{
  typedef typename B<A>::Res R;
  return R();
}

int main()
{
  return 0;
}
