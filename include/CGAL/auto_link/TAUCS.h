// Copyright (c) 1997-2004  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Installation/include/CGAL/auto_link/TAUCS.h $
// $Id: TAUCS.h 58207 2010-08-20 16:28:49Z lrineau $
//
// Author(s)     : Laurent Saboret

#ifndef CGAL_AUTO_LINK_TAUCS_H
#define CGAL_AUTO_LINK_TAUCS_H

// Skip the whole file if auto-link is off
#if !defined(CGAL_NO_AUTOLINK_TAUCS) && !defined(CGAL_NO_AUTOLINK)

#  if defined(_WIN32) || defined(_WIN64) 

#    define CGAL_LIB_NAME libtaucs
#    define CGAL_AUTO_LINK_NOMANGLE
#    include <CGAL/auto_link/auto_link.h>

#    define CGAL_LIB_NAME libmetis
#    define CGAL_AUTO_LINK_NOMANGLE
#    include <CGAL/auto_link/auto_link.h>

// Link with LAPACK, BLAS and F2C
#    include <CGAL/auto_link/LAPACK.h>

#  endif // Win32|Win64

#endif // CGAL_NO_AUTOLINK_TAUCS && CGAL_NO_AUTOLINK

#endif // CGAL_AUTO_LINK_TAUCS_H
