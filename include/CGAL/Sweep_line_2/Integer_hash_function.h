// Copyright (c) 1997  Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Arrangement_2/include/CGAL/Sweep_line_2/Integer_hash_function.h $
// $Id: Integer_hash_function.h 32056 2006-06-23 17:01:20Z lsaboret $
// 
//
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>

#ifndef CGAL_INTEGER_HASH_FUNCTION
#define CGAL_INTEGER_HASH_FUNCTION

#include <CGAL/basic.h>
#include <cstddef>

CGAL_BEGIN_NAMESPACE

struct Integer_hash_function 
{
    typedef std::size_t result_type;

    std::size_t operator() (unsigned int i) const 
    { 
        return i;
    } 
};

CGAL_END_NAMESPACE

#endif
