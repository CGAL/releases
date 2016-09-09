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
// $Source: /CVSROOT/CGAL/Packages/Spatial_searching/include/CGAL/Weighted_Minkowski_distance.h,v $
// $Revision: 1.23 $ $Date: 2003/09/25 14:01:06 $
// $Name: current_submission $
//
// Authors       : Hans Tangelder (<hanst@cs.uu.nl>)

// Note: Use p=0 to denote the weighted Linf-distance 
// For 0<p<1 Lp is not a metric

#ifndef CGAL_WEIGHTED_MINKOWSKI_DISTANCE_H
#define CGAL_WEIGHTED_MINKOWSKI_DISTANCE_H
#include <math.h>
#include <CGAL/Kd_tree_rectangle.h>

namespace CGAL {

  template <class Point>
  class Weighted_Minkowski_distance {

    public:

    typedef typename Kernel_traits<Point>::Kernel::FT NT;
    typedef std::vector<NT> Weight_vector;

    private:

    NT power; 

    unsigned int the_dimension;

    Weight_vector *the_weights;

    public:

    // default constructor
    Weighted_Minkowski_distance(): power(2) 
    { 
       Point p;
       the_dimension=p.dimension();  the_weights = new Weight_vector(the_dimension);
       for (unsigned int i = 0; i < the_dimension; ++i) (*the_weights)[i]=NT(1);
       assert(the_dimension>0);
    }

    Weighted_Minkowski_distance(const int d) : power(2), the_dimension(d) 
    {
       the_weights = new Weight_vector(the_dimension);
       for (unsigned int i = 0; i < the_dimension; ++i) (*the_weights)[i]=NT(1);
    }

    //copy constructor
    Weighted_Minkowski_distance(const Weighted_Minkowski_distance& wmd) :
	power(wmd.power), the_dimension(wmd.the_dimension) {
		the_weights = new Weight_vector(the_dimension);
	 	for (unsigned int i = 0; i < the_dimension; ++i) 
		(*the_weights)[i]=(*(wmd.the_weights))[i];
	}

    	Weighted_Minkowski_distance (NT pow, int dim,
		Weight_vector weights) : power(pow), the_dimension(dim)
	{
		assert(power >= NT(0));
		assert(the_dimension==weights.size());
		for (unsigned int i = 0; i < the_dimension; ++i)
                assert(weights[i]>=NT(0));
		the_weights = new Weight_vector(the_dimension);
		for (unsigned int i = 0; i < the_dimension; ++i) 
		(*the_weights)[i]=weights[i];
    	}

   	~Weighted_Minkowski_distance() {
		delete the_weights;		
	};

	inline NT distance(const Point& q, const Point& p) {
	        NT distance = NT(0);
		if (power == NT(0)) {
			for (unsigned int i = 0; i < the_dimension; ++i)
			if ((*the_weights)[i] * fabs(q[i] - p[i]) > distance)
			distance = (*the_weights)[i] * fabs(q[i]-p[i]);
		}
		else
			for (unsigned int i = 0; i < the_dimension; ++i)
				distance += 
				(*the_weights)[i] * pow(fabs(q[i]-p[i]),power);
        return distance;
	}


	inline NT min_distance_to_queryitem(const Point& q,
					    const Kd_tree_rectangle<NT>& r) const {
		NT distance = NT(0);
		if (power == NT(0))
		{
		    for (unsigned int i = 0; i < the_dimension; ++i) {
			if ((*the_weights)[i]*(r.min_coord(i) - 
				q[i]) > distance)
				distance = (*the_weights)[i] * (r.min_coord(i)-
				q[i]);
			if ((*the_weights)[i] * (q[i] - r.max_coord(i)) > 
				distance)
				distance = (*the_weights)[i] * 
				(q[i]-r.max_coord(i));
			}
		}
		else
		{
			for (unsigned int i = 0; i < the_dimension; ++i) {
				if (q[i] < r.min_coord(i))
					distance += (*the_weights)[i] * 
					pow(r.min_coord(i)-q[i],power);
				if (q[i] > r.max_coord(i))
					distance += (*the_weights)[i] * 
					pow(q[i]-r.max_coord(i),power);
			}
		};
		return distance;
	}

	inline NT max_distance_to_queryitem(const Point& q,
					      const Kd_tree_rectangle<NT>& r) const {
		NT distance=NT(0);
		if (power == NT(0))
		{
			for (unsigned int i = 0; i < the_dimension; ++i) {
				if (q[i] >= (r.min_coord(i) + 
						r.max_coord(i))/NT(2.0))
				if ((*the_weights)[i] * (q[i] - 
					r.min_coord(i)) > distance)
					distance = (*the_weights)[i] * 
					(q[i]-r.min_coord(i));
				else
					if ((*the_weights)[i] * 
					(r.max_coord(i) - q[i]) > distance)
					distance = (*the_weights)[i] * 
					( r.max_coord(i)-q[i]);
			}
		}
		else
		{
			for (unsigned int i = 0; i < the_dimension; ++i) {
				if (q[i] <= (r.min_coord(i)+r.max_coord(i))/NT(2.0))
					distance += (*the_weights)[i] * pow(r.max_coord(i)-q[i],power);
				else
					distance += (*the_weights)[i] * pow(q[i]-r.min_coord(i),power);
			}
		};
		return distance;
	}

	inline NT new_distance(NT dist, NT old_off, NT new_off,
			int cutting_dimension)  const {
		NT new_dist;
		if (power == NT(0))
		{
			if ((*the_weights)[cutting_dimension]*fabs(new_off) 
				> dist) 
			new_dist= 
			(*the_weights)[cutting_dimension]*fabs(new_off);
			else new_dist=dist;
		}
		else
		{
			new_dist = dist + (*the_weights)[cutting_dimension] * 
				(pow(fabs(new_off),power)-pow(fabs(old_off),power));
		}
                return new_dist;
	}

  inline NT transformed_distance(NT d) const {

		if (power <= NT(0)) return d;
		else return pow(d,power);

	}

  inline NT inverse_of_transformed_distance(NT d) const {

		if (power <= NT(0)) return d;
		else return pow(d,1/power);

	}

  }; // class Weighted_Minkowski_distance

} // namespace CGAL
#endif // WEIGHTED_MINKOWSKI_DISTANCE_H
