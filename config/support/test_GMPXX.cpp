// Copyright (c) 2004  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/support/test_GMPXX.cpp $
// $Id: test_GMPXX.cpp 38994 2007-06-08 13:49:17Z spion $
// 
//
// Author(s)     : Sylvain Pion

// Tests if GMPXX is available.

#include <iostream>
#include <cstring> // needed by GMP 4.1.4 since <gmpxx.h> misses it.
#include <gmpxx.h>

int main()
{
    mpz_class a = 1;
    mpq_class b = 2/a;

    std::cout << a << std::endl; // test ABI of libgmpxx

    std::cout << "version=" << __GNU_MP_VERSION << "."
                            << __GNU_MP_VERSION_MINOR << "."
                            << __GNU_MP_VERSION_PATCHLEVEL << std::endl;

    return 0;
}
