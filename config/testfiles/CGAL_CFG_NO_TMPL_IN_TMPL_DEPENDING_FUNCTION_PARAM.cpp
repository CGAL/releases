// Copyright (c) 1998  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/testfiles/CGAL_CFG_NO_TMPL_IN_TMPL_DEPENDING_FUNCTION_PARAM.cpp $
// $Id: CGAL_CFG_NO_TMPL_IN_TMPL_DEPENDING_FUNCTION_PARAM.cpp 37704 2007-03-30 08:39:31Z spion $
// 
//
// Author(s)     : various

// ---------------------------------------------------------------------
// A short test program to evaluate a C++ compiler.
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| G++ 2.95.2 has problems with member functions implemented outside of
//| the class body if this member function has a parameter type that is
//| dependant on a template in the template parameter list of the class. A
//| workaround would be to implement the member function inline in the class.
//| The following definition is set if this error error occurs.

template < template < class T> class T_HDS>
struct Container {
    typedef T_HDS<int>           HDS;
    typedef typename HDS::Handle Handle;
    void foo( Handle h);
    //void foo( Handle h) {} // workaround: implement foo inline.
};

template < template < class T> class T_HDS >
void Container<T_HDS>::foo( Handle ) {}

template <class T>
struct A {
    typedef int* Handle;
};

int main() {
    Container<A> c;
    c.foo(0);
    return 0;
}
