// Copyright (c) 2007  INRIA Sophia Antipolis (France)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/support/test_BOOST_BIMAP.cpp $
// $Id: test_BOOST_BIMAP.cpp 37377 2007-03-22 14:57:55Z lrineau $
// 
//
// Author(s)     : Laurent Rineau

// Tests if Boost.Bimap is available.

#include <iostream>
#include <boost/bimap/bimap.hpp>

using boost::bimap::bimap;
using boost::bimap::set_of;

int main()
{
  bimap<set_of<int,    std::less<int>    >,
        set_of<double, std::less<double> >
    > function;

  function.left[1] = 2.;

  if( function.right[2.] == 1 )
  {
    std::cout << "ok for Boost.Bimap\n";
    return 0;
  }
  else
    return 1;
}
