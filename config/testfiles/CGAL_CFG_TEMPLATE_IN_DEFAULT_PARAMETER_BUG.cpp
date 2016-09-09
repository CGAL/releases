// Copyright (c) 2011  INRIA Saclay (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Installation/config/testfiles/CGAL_CFG_TEMPLATE_IN_DEFAULT_PARAMETER_BUG.cpp $
// $Id: CGAL_CFG_TEMPLATE_IN_DEFAULT_PARAMETER_BUG.cpp 63062 2011-04-20 13:56:23Z lrineau $
//
// Author(s)     : Marc Glisse

//| If a compiler wants us to remove the template keyword in default
//| parameters, CGAL_CFG_TEMPLATE_IN_DEFAULT_PARAMETER_BUG is set. 
//| Bug found in sunCC 5.11.

template < typename A, typename B, typename C =
  typename A :: template T < B > :: type >
//                here
struct S {};

int main(){}
