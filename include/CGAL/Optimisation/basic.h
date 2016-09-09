// Copyright (c) 1997-2001  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Optimisation_basic/include/CGAL/Optimisation/basic.h,v $
// $Revision: 1.7 $ $Date: 2003/10/21 12:22:04 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>

#ifndef CGAL_OPTIMISATION_BASIC_H
#define CGAL_OPTIMISATION_BASIC_H

// includes
#ifndef CGAL_BASIC_H
#  include <CGAL/basic.h>
#endif
#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#  include <CGAL/Optimisation/assertions.h>
#endif
#ifndef CGAL_OPTIMISATION_DEBUG_H
#  include <CGAL/Optimisation/debug.h>
#endif
#ifndef CGAL_IO_VERBOSE_OSTREAM_H
#  include <CGAL/IO/Verbose_ostream.h>
#endif

CGAL_BEGIN_NAMESPACE

// Function declarations
// =====================

// is_valid failure function
// -------------------------
bool
_optimisation_is_valid_fail( CGAL::Verbose_ostream& verr,
                             const char*            message);

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_BASIC_H

// ===== EOF ==================================================================
