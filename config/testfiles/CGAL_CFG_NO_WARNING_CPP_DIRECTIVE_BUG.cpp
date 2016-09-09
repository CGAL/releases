// Copyright (c) 2010  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Installation/config/testfiles/CGAL_CFG_NO_WARNING_CPP_DIRECTIVE_BUG.cpp $
// $Id: CGAL_CFG_NO_WARNING_CPP_DIRECTIVE_BUG.cpp 56118 2010-05-11 10:08:08Z lrineau $
//
// Author(s)     : Laurent Rineau

//| If a compiler does not support the #warning preprocessor directive.
//| CGAL_CFG_NO_WARNING_CPP_DIRECTIVE_BUG is set. 
//| This is not strictly a "bug", as the C++ standard does not speak about
//| this directive.

#warning "Hello world"

int main()
{
  return 0;
}
