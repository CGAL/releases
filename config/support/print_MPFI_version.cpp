// Copyright (c) 2010 Inria Lorraine (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/Installation/config/support/print_MPFI_version.cpp $
// $Id: print_MPFI_version.cpp 61901 2011-03-22 08:07:15Z penarand $
//
// Author: Luis Peñaranda <luis.penaranda@gmx.com>

#include <iostream>
#include <string>
#include <mpfi.h>

int main(){
    std::cout<<"version="<<std::string(mpfi_get_version())<<std::endl;
    return 0;
}
