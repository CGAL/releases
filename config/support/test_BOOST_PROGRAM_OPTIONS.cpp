// Copyright (c) 2006, 2007  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/support/test_BOOST_PROGRAM_OPTIONS.cpp $
// $Id: test_BOOST_PROGRAM_OPTIONS.cpp 37323 2007-03-20 19:14:02Z reichel $
// 
//
// Author(s)     : Daniel Russel

// Tests if BOOST_PROGRAM_OPTIONS is available.

#include <iostream>
#include <boost/program_options.hpp>

int main(int ac, char *av[])
{
  std::cout << "version=" << BOOST_VERSION/100000 << "."
            << ((BOOST_VERSION / 100) % 100) << "."
            << BOOST_VERSION % 100 << std::endl;

  boost::program_options::options_description desc("Allowed options");
  desc.add_options()
    ("help", "produce help message")
    ;

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(ac, av, desc), vm);
  boost::program_options::notify(vm);    

  if (vm.count("help")) {
    std::cout << "Help" << "\n";
    return 1;
  }
  return 0;
}
