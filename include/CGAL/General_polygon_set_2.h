// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Boolean_set_operations_2/include/CGAL/General_polygon_set_2.h $
// $Id: General_polygon_set_2.h 49788 2009-06-04 09:17:15Z eric $ $Date: 2009-06-04 11:17:15 +0200 (Thu, 04 Jun 2009) $
// 
//
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>
//                 Efi Fogel <efif@post.tau.ac.il>

#ifndef CGAL_GENERAL_POLYGON_SET_2_H
#define CGAL_GENERAL_POLYGON_SET_2_H

#include <CGAL/basic.h>

#include <CGAL/Boolean_set_operations_2/Gps_default_dcel.h>
#include <CGAL/General_polygon_set_on_surface_2.h>
#include <CGAL/Arrangement_2/Arr_default_planar_topology.h>

CGAL_BEGIN_NAMESPACE

// General_polygon_set_2
template <class Traits_, class Dcel_ = Gps_default_dcel<Traits_> >
class General_polygon_set_2 : public General_polygon_set_on_surface_2
  <Traits_, typename Default_planar_topology<Traits_, Dcel_ >::Traits>
{
public:
  typedef Traits_                                         Traits_2;
  typedef Dcel_                                           Dcel;

  typedef General_polygon_set_2< Traits_, Dcel_ >         Self;
  typedef General_polygon_set_on_surface_2 <Traits_2,
    typename Default_planar_topology<Traits_2, Dcel >::Traits>
                                                          Base;

  typedef typename Base::Arrangement_on_surface_2         Arrangement_2;

protected:
  typedef typename Base::Polygon_2                        Polygon_2;
  typedef typename Base::Polygon_with_holes_2             Polygon_with_holes_2;

public:

  // default costructor
  General_polygon_set_2() : Base()
  {}


  // constructor with traits object
  General_polygon_set_2(Traits_2& tr) : Base(tr)
  {}

  explicit General_polygon_set_2(const Polygon_2& pgn) : 
    Base(pgn)
  { }

  explicit General_polygon_set_2(const Polygon_with_holes_2& pgn_with_holes): 
   Base(pgn_with_holes) 
  { }

  // For some reason the below functions (the ones that we call "using" for)
  // are hidden by the function in this class and are not found in the parent's
  // class (General_polygon_set_on_surface_2) when they are called on an 
  // object of type General_polygon_set_2.
  // Check in the Vandervoorde / Stroustrup books what is the exact reason.
  // (There may be a better and more correct solution.)
  using Base::intersection;
  using Base::join;
  using Base::symmetric_difference;

  inline void intersection(const Self& ps1, const Self& ps2)
  {
    Base::intersection(static_cast<const Base&>(ps1),
                       static_cast<const Base&>(ps2));
  }

  inline void join(const Self& ps1, const Self& ps2)
  {
    Base::join(static_cast<const Base&>(ps1),
                       static_cast<const Base&>(ps2));
  }

  inline void symmetric_difference(const Self& ps1, const Self& ps2)
  {
    Base::symmetric_difference(static_cast<const Base&>(ps1),
                       static_cast<const Base&>(ps2));
  }

};

CGAL_END_NAMESPACE

#endif
