// Copyright (c) 1997-2007  ETH Zurich (Switzerland).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/QP_solver/include/CGAL/QP_solver/debug.h $
// $Id: debug.h 38453 2007-04-27 00:34:44Z gaertner $
// 
//
// Author(s)     : Sven Schoenherr
//                 Bernd Gaertner <gaertner@inf.ethz.ch>
//                 Franz Wessendorp 
//                 Kaspar Fischer 

#ifndef CGAL_QP_DEBUG_H
#define CGAL_QP_DEBUG_H

// macro definitions
// =================

// debug
// -----
#if (    defined( CGAL_QP_NO_DEBUG)\
      || defined( CGAL_QP_NO_ASSERTIONS)\
      || defined( CGAL_NO_ASSERTIONS)\
      || defined( CGAL_NO_DEBUG) || defined( NDEBUG))
#  define  CGAL_qpe_debug  if ( 0)
#else
#  define  CGAL_qpe_debug  if ( 1)
#endif // qpe debug

#endif // CGAL_QP_DEBUG_H

// ===== EOF ==================================================================
