// Copyright (c) 2003,2004,2005  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Apollonius_graph_2/demo/Apollonius_graph_2/typedefs.h $
// $Id: typedefs.h 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>

#ifndef _MK___TYPEDEFS_H
#define _MK___TYPEDEFS_H

#include <CGAL/basic.h>

#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float  exact_type;
//#include <CGAL/leda_real.h>
//typedef leda_real  exact_type;

#include <CGAL/Simple_cartesian.h>

typedef CGAL::Simple_cartesian<double>        Rep;


#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_hierarchy_2.h>
#include <CGAL/Apollonius_graph_filtered_traits_2.h>


typedef CGAL::Apollonius_graph_filtered_traits_2<Rep,CGAL::Integral_domain_without_division_tag>  Gt;

typedef Gt::Point_2                           Point_2;
typedef Rep::Circle_2                         Circle_2;
typedef Gt::Site_2                            Apollonius_site_2;
typedef Gt::Site_2::Weight                    Weight;

//typedef CGAL::Apollonius_graph_2<Gt> AG_2;
typedef CGAL::Apollonius_graph_hierarchy_2<Gt> AG_2;


typedef AG_2::Vertex_handle                 Vertex_handle;



#endif  // _MK___TYPEDEFS_H
