// Copyright (c) 2003,2006  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Apollonius_graph_2/include/CGAL/Apollonius_graph_2/Traits_wrapper_2.h $
// $Id: Traits_wrapper_2.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_APOLLONIUS_GRAPH_2_TRAITS_WRAPPER_2_H
#define CGAL_APOLLONIUS_GRAPH_2_TRAITS_WRAPPER_2_H


#include <CGAL/Apollonius_graph_2/basic.h>



namespace CGAL {

namespace ApolloniusGraph_2 {


template<class Gt_base>
class Apollonius_graph_traits_wrapper_2 : public Gt_base
{
public:
  //  struct Segment_2  {};
  struct Triangle_2 {};

  Apollonius_graph_traits_wrapper_2() {}
  Apollonius_graph_traits_wrapper_2(const Gt_base& gtb)
    : Gt_base(gtb) {}

};


} //namespace ApolloniusGraph_2

} //namespace CGAL


#endif // CGAL_APOLLONIUS_GRAPH_2_TRAITS_WRAPPER_2_H
