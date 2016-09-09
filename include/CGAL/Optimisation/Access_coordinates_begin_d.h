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
// $Source: /CVSROOT/CGAL/Packages/Optimisation_basic/include/CGAL/Optimisation/Access_coordinates_begin_d.h,v $
// $Revision: 1.7 $ $Date: 2003/10/21 12:22:01 $
// $Name: current_submission $
//
// Author(s)     : Sven Sch�nherr <sven@inf.ethz.ch>

#ifndef CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H
#define CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H

// includes
#  include <CGAL/Kernel_d/Interface_classes.h>
#  include <CGAL/Kernel_d/Point_d.h>

CGAL_BEGIN_NAMESPACE

// Class declaration
// =================
template < class R_ >
class Access_coordinates_begin_d;

// Class interface
// ===============
template < class R_ >
class Access_coordinates_begin_d {
  public:
    // self
    typedef  R_                         R;
    typedef  Access_coordinates_begin_d<R>
                                        Self;

    // types
    typedef  typename R::Point_d        Point;
    typedef  const typename R::RT *     Coordinate_iterator;

    // unary function class types
    typedef  Coordinate_iterator        result_type;
    typedef  Point                      argument_type;

    // creation
    Access_coordinates_begin_d( ) { }

    // operations
private:
    Coordinate_iterator
    access( const Point& p, Cartesian_tag) const 
    { return p.cartesian_begin(); }
  
    Coordinate_iterator
    access( const Point& p, Homogeneous_tag) const 
    { return p.homogeneous_begin(); }
  
  
public:
    Coordinate_iterator
    operator() ( const Point& p) const { 
      typename R::Rep_tag tag;
#if defined(__sun) && defined(__SUNPRO_CC)
    // to avoid a warning "tag has not yet been assigned a value"
    typedef typename R::Rep_tag Rep_tag;
    tag = Rep_tag();
#endif // SUNPRO
      return access(p, tag);
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_OPTIMISATION_ACCESS_COORDINATES_BEGIN_D_H

// ===== EOF ==================================================================
