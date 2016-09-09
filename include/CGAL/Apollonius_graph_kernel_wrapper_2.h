// Copyright (c) 2003  INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Apollonius_graph_2/include/CGAL/Apollonius_graph_kernel_wrapper_2.h,v $
// $Revision: 1.10 $ $Date: 2003/09/18 10:19:23 $
// $Name: current_submission $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_APOLLONIUS_GRAPH_KERNEL_WRAPPER_2_H
#define CGAL_APOLLONIUS_GRAPH_KERNEL_WRAPPER_2_H

#include <CGAL/Apollonius_graph_short_names_2.h>

#include <CGAL/Apollonius_site_2.h>
#include <CGAL/Cartesian_converter.h>

CGAL_BEGIN_NAMESPACE

template<class Kernel_base_2>
class Apollonius_graph_kernel_wrapper_2 : public Kernel_base_2
{
public:
  typedef CGAL::Apollonius_site_2<Kernel_base_2>  Site_2;
  typedef Kernel_base_2                           Base;

  struct Compare_x_2 : public Kernel_base_2
  {
    typedef Comparison_result   result_type;    
    typedef Arity_tag<2>        Arity;

    Comparison_result operator()(const Site_2& s1,
				 const Site_2& s2) const
    {
      return this->compare_x_2_object()(s1.point(), s2.point());
    }
  };

  struct Compare_y_2 : public Kernel_base_2
  {
    typedef Comparison_result   result_type;
    typedef Arity_tag<2>        Arity;

    Comparison_result operator()(const Site_2& s1,
				 const Site_2& s2) const
    {
      return this->compare_y_2_object()(s1.point(), s2.point());
    }
  };

  struct Orientation_2 : public Kernel_base_2
  {
    typedef Orientation     result_type;
    typedef Arity_tag<3>    Arity;

    Orientation operator()(const Site_2& s1,
			   const Site_2& s2,
			   const Site_2& s3) const
    {
      return this->orientation_2_object()(s1.point(),
					  s2.point(),
					  s3.point());
    }
  };

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
  bool
  operator()(const bool& b) const {
    return b;
  }

  K2_Point_2
  operator()(const typename K1::Point_2& p) const
  {
    return Base::operator()(p);
  }

  K2_Site_2
  operator()(const typename K1::Site_2& t) const
  {
    NT_converter nt_cv;

    return K2_Site_2( Base::operator()(t.point()),
		      nt_cv(t.weight())
		      );
  }
};


CGAL_END_NAMESPACE


#endif // CGAL_APOLLONIUS_GRAPH_KERNEL_WRAPPER_2_H
