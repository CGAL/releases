// Copyright (c) 1999  INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Triangulation_3/include/CGAL/Triangulation_cell_base_3.h,v $
// $Revision: 1.28 $ $Date: 2003/10/17 08:49:16 $
// $Name: current_submission $
//
// Author(s)     : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>

// cell of a triangulation of any dimension <=3

#ifndef CGAL_TRIANGULATION_CELL_BASE_3_H
#define CGAL_TRIANGULATION_CELL_BASE_3_H

#include <CGAL/basic.h>
#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_3.h>
#include <CGAL/Triangulation_ds_cell_base_3.h>

CGAL_BEGIN_NAMESPACE

template < typename GT, typename Cb = Triangulation_ds_cell_base_3<> >
class Triangulation_cell_base_3
  : public Cb
{
public:
  typedef typename Cb::Vertex_handle                   Vertex_handle;
  typedef typename Cb::Cell_handle                     Cell_handle;

  typedef GT                                           Geom_traits;

  template < typename TDS2 >
  struct Rebind_TDS {
    typedef typename Cb::template Rebind_TDS<TDS2>::Other  Cb2;
    typedef Triangulation_cell_base_3<GT, Cb2>             Other;
  };

  Triangulation_cell_base_3()
    : Cb() {}

  Triangulation_cell_base_3(const Vertex_handle& v0, const Vertex_handle& v1,
                            const Vertex_handle& v2, const Vertex_handle& v3)
    : Cb(v0, v1, v2, v3) {}

  Triangulation_cell_base_3(const Vertex_handle& v0, const Vertex_handle& v1,
                            const Vertex_handle& v2, const Vertex_handle& v3,
                            const Cell_handle&   n0, const Cell_handle&   n1,
                            const Cell_handle&   n2, const Cell_handle&   n3)
    : Cb(v0, v1, v2, v3, n0, n1, n2, n3) {}
};

// The following should be useless.
#if 0
template < class GT, class Cb >
inline
std::istream&
operator>>(std::istream &is, Triangulation_cell_base_3<GT, Cb> &c)
  // non combinatorial information. Default = nothing
{
  return is >> static_cast<Cb&>(c);
}

template < class GT, class Cb >
inline
std::ostream&
operator<<(std::ostream &os, const Triangulation_cell_base_3<GT, Cb> &c)
  // non combinatorial information. Default = nothing
{
  return os << static_cast<const Cb&>(c);
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_TRIANGULATION_CELL_BASE_3_H
