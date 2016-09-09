// Copyright (c) 2006  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/support/test_OPENGL.cpp $
// $Id: test_OPENGL.cpp 36141 2007-02-09 11:11:40Z afabri $
// 
//
// Author(s)     : Sylvain Pion

// Tests if OPEN GL and GLU are available.

#if defined(_MSC_VER)
#include <wtypes.h>
#include <wingdi.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

// The following global variable is needed otherwise GCC removes the body of 
// the if() blocks which removes its purpose of link check.
bool execute = false;

int main()
{
    if (execute) {
      // This needs an active GL context, so not executed, but serves
      // as a link test.
      (void) glGetString(GL_VERSION);
      (void) gluGetString(GLU_VERSION);
    }

    std::cout << "version=" <<
#if   defined GL_VERSION_2_1
    "2.1"
#elif defined GL_VERSION_2_0
    "2.0"
#elif defined GL_VERSION_1_5
    "1.5"
#elif defined GL_VERSION_1_4
    "1.4"
#elif defined GL_VERSION_1_3
    "1.3"
#elif defined GL_VERSION_1_2
    "1.2"
#elif defined GL_VERSION_1_1
    "1.1"
#elif defined GL_VERSION_1_0
    "1.0"
#else
    "unknown"
#endif
    << std::endl;

    return 0;
}
