// Copyright (c) 1999  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/STL_Extension/include/CGAL/assertions_behaviour.h $
// $Id: assertions_behaviour.h 56667 2010-06-09 07:37:13Z sloriot $
//
//
// Author(s)     : Geert-Jan Giezeman and Sven Schoenherr

#include <CGAL/config.h>

#ifndef CGAL_ASSERTIONS_BEHAVIOUR_H
#define CGAL_ASSERTIONS_BEHAVIOUR_H

namespace CGAL {

enum Failure_behaviour { ABORT, EXIT, EXIT_WITH_SUCCESS, CONTINUE,
                         THROW_EXCEPTION };

// failure handler declarations
// ==========================
// failure handler
// ---------------
typedef
    void
    (*Failure_function)(
        const char*, const char*, const char*, int, const char*);

Failure_function
set_error_handler( Failure_function handler);

Failure_function
set_warning_handler( Failure_function handler);

// failure behaviour handler
// -------------------------
Failure_behaviour
set_error_behaviour(Failure_behaviour eb);

Failure_behaviour
set_warning_behaviour(Failure_behaviour eb);

} //namespace CGAL

#endif // CGAL_ASSERTIONS_BEHAVIOUR_H
