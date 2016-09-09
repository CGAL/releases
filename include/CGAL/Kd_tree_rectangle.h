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
// $Source: /CVSROOT/CGAL/Packages/Spatial_searching/include/CGAL/Kd_tree_rectangle.h,v $
// $Revision: 1.16 $ $Date: 2003/09/18 10:25:43 $
// $Name: current_submission $
//
// Authors       : Hans Tangelder (<hanst@cs.uu.nl>)

#ifndef CGAL_KD_TREE_RECTANGLE_H
#define CGAL_KD_TREE_RECTANGLE_H
#include <functional>
#include <algorithm>
#include <new>
#include <cassert>

namespace CGAL {

  template <class Point, class T>
  struct set_bounds : public std::unary_function<Point&, void> {
    int dim;
    T *lower;
    T *upper;
    set_bounds(int d, T *l, T *u) : dim(d), lower(l), upper(u) {}
    void operator() (Point& p) {
		T h;
		for (int i = 0; i < dim; ++i) {
			h=p[i]; 
			if (h < lower[i]) lower[i] = h;
 			if (h > upper[i]) upper[i] = h;
		}
    }
  };

  template <class P, class T>
  struct set_bounds_from_pointer : public std::unary_function<P, void> {
    int dim;
    T *lower;
    T *upper;
    set_bounds_from_pointer(int d, T *l, T *u) :
	dim(d), lower(l), upper(u) {}
    void operator() (P p) {
		T h;
		for (int i = 0; i < dim; ++i) {
			h=(*p)[i];
			if (h < lower[i]) lower[i] = h;
			if (h > upper[i]) upper[i] = h;
		}
    }
  };


  template <class T> class Kd_tree_rectangle {
  public:
    typedef T NT;

  private:

    int dim;
    T *lower_;
    T *upper_;
    int max_span_coord_;

  public:

    inline void set_upper_bound(const int i, const NT x) {
      assert(i >= 0 && i < dim);
      assert(x >= lower_[i]);
      upper_[i] = x;
      set_max_span();
    }

    inline void set_lower_bound(const int i, const NT x) {
      assert(i >= 0 && i < dim);
      assert(x <= upper_[i]);
      lower_[i] = x;
      set_max_span();
    }

    inline void set_max_span() {
      NT span = upper_[0]-lower_[0];
      max_span_coord_ = 0;
      for (int i = 1; i < dim; ++i) {
	NT tmp = upper_[i] - lower_[i];
	if (span < tmp) {
	  span = tmp;
	  max_span_coord_ = i;
	}
      }
    }
    
    Kd_tree_rectangle(const int d) : 
    dim(d), lower_(new NT[d]), upper_(new NT[d])
    {
      std::fill(lower_, lower_ + dim, 0);
      std::fill(upper_, upper_ + dim, 0);
      set_max_span();
    }

    Kd_tree_rectangle() : dim(0), lower_(0), upper_(0) {}

    
    explicit Kd_tree_rectangle(const Kd_tree_rectangle<NT>& r) : dim(r.dim),
      lower_(new NT[dim]), upper_(new NT[dim]) {
        std::copy(r.lower_, r.lower_+dim, lower_);
	std::copy(r.upper_, r.upper_+dim, upper_);
	set_max_span();
    }

    template <class PointIter>
    Kd_tree_rectangle(const int d,  PointIter begin,  PointIter end)
      : dim(d), lower_(new NT[d]), upper_(new NT[d]) {
	  // initialize with values of first point
	  for (int i=0; i < dim; ++i)
	  {
	    lower_[i]=(*begin)[i]; upper_[i]=lower_[i];
	  }
	  begin++;
      typedef typename std::iterator_traits<PointIter>::value_type P;
      std::for_each(begin, end, set_bounds<P,T>(dim, lower_, upper_));
      set_max_span();
    }

    template <class PointPointerIter>
    void update_from_point_pointers(PointPointerIter begin, 
                                    PointPointerIter end, bool empty) {
		if (empty) { // no points
		  for (int i=0; i < dim; ++i)
		  {
			lower_[i]= NT(1); upper_[i]= NT(-1);
		  }
		} else {
          // initialize with values of first point
	      for (int i=0; i < dim; ++i)
		  {
	        lower_[i]= (*(*begin))[i]; upper_[i]=lower_[i];
		  }
	      begin++;
          typedef typename 
	  std::iterator_traits<PointPointerIter>::value_type P;
          std::for_each(begin, end,
		    set_bounds_from_pointer<P,T>(dim, lower_, upper_));
		}
        set_max_span();
    }

    inline int max_span_coord() const { return max_span_coord_; }

    inline NT max_span() const {
      return upper_[max_span_coord_] - lower_[max_span_coord_];
    }

    inline NT min_coord(int i) const {
      return lower_[i];
    }

    inline NT max_coord(int i) const {
      return upper_[i];
    }

    std::ostream& print(std::ostream& s) {
      s << "Rectangle dimension = " << dim;
      s << "\n lower: ";
      for (int i=0; i < dim; ++i)
      s << lower_[i] << " ";
      // std::copy(lower_, lower_ + dim,
      // 	      std::ostream_iterator<NT>(s," "));
      s << "\n upper: ";
      for (int j=0; j < dim; ++j)
      s << upper_[j] << " ";
      // std::copy(upper_, upper_ + dim,
      //	      std::ostream_iterator<NT>(s," "));
      s << "\n maximum span " << max_span() <<
      " at coordinate " << max_span_coord() << std::endl;
      return s;
    }

    // Splits rectangle by modifying itself to lower half 
    // and returns upper half
    Kd_tree_rectangle* split(int d, NT value) {
		// assert(d >= 0 && d < dim);
		// assert(lower_[d] <= value && value <= upper_[d]);
                
		Kd_tree_rectangle* r = new Kd_tree_rectangle(*this);
		upper_[d]=value;
                r->lower_[d]=value;
		return r;
    }
                      

    ~Kd_tree_rectangle() {
      if (dim) {
	if (lower_) delete [] lower_;
	if (upper_) delete [] upper_;
      }
    }

    int dimension() const {return dim;}

 
    Kd_tree_rectangle<NT>& operator= (const Kd_tree_rectangle<NT>& r) {
      
      if (this != &r) {
        std::copy(r.lower_, r.lower_+dim, lower_);
	std::copy(r.upper_, r.upper_+dim, upper_);
	set_max_span();
      }
      return *this;
    }

  

}; // of class Kd_tree_rectangle

  template <class NT>
    std::ostream& operator<< (std::ostream& s, Kd_tree_rectangle<NT>& r) {
    return r.print(s);
  }

  
} // namespace CGAL
#endif // CGAL_KD_TREE_RECTANGLE_H

