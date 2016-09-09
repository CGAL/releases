// Copyright (c) 2006  GeometryFactory (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/config/testfiles/CGAL_CFG_ISTREAM_INT_BUG.cpp $
// $Id: CGAL_CFG_ISTREAM_INT_BUG.cpp 37704 2007-03-30 08:39:31Z spion $
// 
//
// Author(s)     : Andreas Fabri

// ---------------------------------------------------------------------
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| This flag is set, if the executable does not properly parse an int followed by a comma
//| Can you believe it!!!

#include <iostream>
#include <sstream>

int main()
{
  int i;
  std::string one = "7812,"; 
  std::istringstream is(one);
  is >> i;
  std::cout << i << std::endl;
  if(i != 7812){ // bad luck if there is garbage that equals 7812. 
    return 1;
  }
  return 0;

}
