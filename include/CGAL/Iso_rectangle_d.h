// Copyright (c) 2002  Utrecht University (The Netherlands).
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
// $Source: /CVSROOT/CGAL/Packages/Spatial_searching/include/CGAL/Iso_rectangle_d.h,v $
// $Revision: 1.10 $ $Date: 2003/09/18 10:25:42 $
// $Name: CGAL_3_0_1  $
//
// Authors       : Hans Tangelder (<hanst@cs.uu.nl>)

#ifndef CGAL_ISO_RECTANGLE_D_H
#define CGAL_ISO_RECTANGLE_D_H
#include <functional>
#include <algorithm>
#include <new>
#include <cassert>

namespace CGAL {
  
  template <class R> class Iso_rectangle_d {
  public:
    typedef typename R::FT NT;
    typedef typename R::Point_d Point_d;

  private:

    int dim;
    NT *lower;
    NT *upper;
    
  public:

    Iso_rectangle_d(const Point_d& p, const Point_d& q)
    { assert(p.dimension() == q.dimension());
      dim = p.dimension();
      lower = new NT[dim];
      upper = new NT[dim];
      for (int i = 0; i < dim; ++i) {
	  if (p[i] <= q[i]) {
		lower[i]=p[i]; 
                upper[i]=q[i];
	  }
	  else {
		lower[i]=q[i]; 
                upper[i]=p[i];
	  }
     }	  
    }
  
  // copy constructor
  Iso_rectangle_d(const Iso_rectangle_d& b) : dim(b.dim) {
      lower = new NT[dim];
      upper = new NT[dim];
      for (int i = 0; i < dim; ++i) {
		lower[i]=b.lower[i]; 
                upper[i]=b.upper[i];
      }
  }

  
  bool has_on_bounded_side(const Point_d& p) const
  {
    NT h;
    for (int i = 0; i < dimension(); ++i) {
        h=p[i];
        if ( (h < lower[i]) || (h > upper[i]) ) return 0;
    }
    return 1;
  } 

    inline int dimension() const { return dim;}
    
    inline NT min_coord(int i) const {
      return lower[i];
    }

    inline NT max_coord(int i) const {
      return upper[i];
    }

  }; // end of class

} // namespace CGAL
#endif // CGAL_ISO_RECTANGLE_D_H

