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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Installation/config/testfiles/CGAL_CFG_NO_CPP0X_STATIC_ASSERT.cpp $
// $Id: CGAL_CFG_NO_CPP0X_STATIC_ASSERT.cpp 63457 2011-05-11 10:14:02Z glisse $
//
// Author(s)     : Marc Glisse

//| If a compiler does not support static_assert (from C++0x)
//| CGAL_CFG_NO_CPP0X_STATIC_ASSERT is set. 

int main(){
	static_assert(true,"Everything is fine");
}
