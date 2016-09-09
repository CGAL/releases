// Copyright (c) 2008 GeometryFactory, Sophia Antipolis (France)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/support/print_QT4_version.cpp $
// $Id: print_QT4_version.cpp 44263 2008-07-17 14:03:25Z fcacciola $

// Tests if QT4 is available and prints its version string.

#include <iostream>
#include <QtCore/QtGlobal>

int main()
{
    std::cout << "version=" << QT_VERSION_STR << std::endl;

    return 0;
}
