// Copyright (c) 2006  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Envelope_2/include/CGAL/Env_default_diagram_1.h $
// $Id: Env_default_diagram_1.h 61401 2011-02-24 11:20:04Z efif $
//
// Author(s)     : Ron Wein   <wein@post.tau.ac.il>

#include <CGAL/basic.h>

#ifndef CGAL_ENV_DEFAULT_DIAGRAM_1_H
#define CGAL_ENV_DEFAULT_DIAGRAM_1_H

#if (defined __GNUC__)
  #if !(defined __STRICT_ANSI__)
  #warning "Env_default_diagram.h is DEPRECATED, please include Envelope_diagram_1.h instead."
  #endif
#elif (defined _MSC_VER)
  #pragma message("Env_default_diagram.h is DEPRECATED, please include Envelope_diagram_1.h instead")
#endif

#include <CGAL/Envelope_diagram_1.h>

namespace CGAL {

template <class Traits_, class Allocator = CGAL_ALLOCATOR(int)>
class Env_default_diagram_1 : public Envelope_diagram_1<Traits_, Allocator>{};

} //namespace CGAL

#endif

