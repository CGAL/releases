// Copyright (c) 2014
// INRIA Saclay-Ile de France (France)
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-5.0-beta1/NewKernel_d/include/CGAL/Epeck_d.h $
// $Id: Epeck_d.h 730cfdc %aI Marc Glisse
// SPDX-License-Identifier: LGPL-3.0+
//
// Author(s)     : Marc Glisse

#ifndef CGAL_EPECK_D_H
#define CGAL_EPECK_D_H

#include <CGAL/disable_warnings.h>

#include <CGAL/NewKernel_d/Cartesian_base.h>
#include <CGAL/NewKernel_d/Wrapper/Cartesian_wrap.h>
#include <CGAL/NewKernel_d/Kernel_d_interface.h>
#include <CGAL/NewKernel_d/Lazy_cartesian.h>
#include <CGAL/NewKernel_d/KernelD_converter.h>
#include <CGAL/internal/Exact_type_selector.h>
#include <CGAL/NewKernel_d/Types/Weighted_point.h>

// TODO: add static filters somewhere
namespace CGAL {
#define CGAL_KA Cartesian_base_d<Interval_nt_advanced,Dim>
#define CGAL_KE Cartesian_base_d<internal::Exact_field_selector<double>::Type, Dim>
template<class Dim> using Epeck_d_help1 = Lazy_cartesian<CGAL_KE, CGAL_KA, KernelD_converter<CGAL_KE, CGAL_KA>>;
#undef CGAL_KE
#undef CGAL_KA
#undef CGAL_BASE
#define CGAL_BASE \
  Kernel_d_interface< \
    Cartesian_wrap< \
      Epeck_d_help1<Dim>, \
      Epeck_d<Dim> > >
template<class Dim>
struct Epeck_d
: CGAL_BASE
{
  constexpr Epeck_d(){}
  constexpr Epeck_d(int d):CGAL_BASE(d){}
};
#undef CGAL_BASE
}

#include <CGAL/enable_warnings.h>

#endif
