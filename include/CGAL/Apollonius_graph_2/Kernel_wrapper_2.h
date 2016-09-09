// Copyright (c) 2003,2004,2006  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Apollonius_graph_2/include/CGAL/Apollonius_graph_2/Kernel_wrapper_2.h $
// $Id: Kernel_wrapper_2.h 41739 2008-01-20 23:09:58Z spion $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_APOLLONIUS_GRAPH_2_KERNEL_WRAPPER_2_H
#define CGAL_APOLLONIUS_GRAPH_2_KERNEL_WRAPPER_2_H

#include <CGAL/Apollonius_graph_2/basic.h>

#include <CGAL/Apollonius_site_2.h>
//#include <CGAL/Cartesian_converter.h>

CGAL_BEGIN_NAMESPACE

CGAL_APOLLONIUS_GRAPH_2_BEGIN_NAMESPACE

template<class Kernel_base_2>
class Apollonius_graph_kernel_wrapper_2 : public Kernel_base_2
{
public:
  typedef CGAL::Apollonius_site_2<Kernel_base_2>  Site_2;
  typedef Kernel_base_2                           Base;
};


template<class K1, class K2, class Converter >
class Apollonius_graph_cartesian_converter
  : public Converter
{
private:
  typedef typename K2::Site_2                         K2_Site_2;
  typedef typename K2::Point_2                        K2_Point_2;
  typedef Converter                                   Base;
  typedef typename Converter::Number_type_converter   NT_converter;


public:
#if defined(_MSC_VER)
  bool operator()(bool b) const {
    return Base::operator()(b);
  }

  K2_Point_2
  operator()(const typename K1::Point_2& p) const
  {
    return Base::operator()(p);
  }
#else
  using Base::operator();
#endif

  K2_Site_2
  operator()(const typename K1::Site_2& t) const
  {
    NT_converter nt_cv;

    return K2_Site_2( Base::operator()(t.point()),
		      nt_cv(t.weight())
		      );
  }
};


CGAL_APOLLONIUS_GRAPH_2_END_NAMESPACE

CGAL_END_NAMESPACE


#endif // CGAL_APOLLONIUS_GRAPH_2_KERNEL_WRAPPER_2_H
