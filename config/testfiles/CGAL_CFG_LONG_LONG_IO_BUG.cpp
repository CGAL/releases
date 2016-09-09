// Copyright (c) 2007  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/testfiles/CGAL_CFG_LONG_LONG_IO_BUG.cpp $
// $Id: CGAL_CFG_LONG_LONG_IO_BUG.cpp 37704 2007-03-30 08:39:31Z spion $
//
// Author(s)     : Sylvain Pion

// ---------------------------------------------------------------------
// A short test program to evaluate a machine architecture.
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| Tests if the input stream operator<< is correct with long long.
//| pgCC 6.2 has this bug.

#include <sstream>

int main() {
    long long x = 12;
    long long tmp;
    std::ostringstream os;
    os << x;
    std::istringstream is(os.str());
    is >> tmp;

    if (x != tmp)
      return 1;

    return 0;
}
