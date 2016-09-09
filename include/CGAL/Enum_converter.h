// Copyright (c) 2003  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kernel_23/include/CGAL/Enum_converter.h $
// $Id: Enum_converter.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef CGAL_ENUM_CONVERTER_H
#define CGAL_ENUM_CONVERTER_H

#include <CGAL/basic.h>
#include <CGAL/enum.h>

namespace CGAL {

struct Enum_converter
{
  bool              operator()(bool b) const { return b; }

  Sign              operator()(Sign s) const { return s; }

  Bounded_side      operator()(Bounded_side bs) const { return bs; }

  Angle operator()(Angle a) const { return a; }
};


} //namespace CGAL


#endif // CGAL_ENUM_CONVERTER_H
