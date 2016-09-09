// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/min_sqr_distance.C
// author(s)     :       Wolfgang Freiseisen 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#ifndef CGAL_MIN_SQUARE_DISTANCE_H
#include <CGAL/min_square_distance.h>
#endif
#endif
#include <vector.h>
#include <multiset.h>
#include <algo.h>

template <class Point>
struct CGAL__Compare_point_x : public binary_function<Point,Point,bool> {
  bool operator()(const Point& p1, const Point& p2) const {
    return p1.x()  < p2.x();
  }
};


template <class Point>
struct CGAL__Compare_point_y : public binary_function<Point,Point,bool> {
  bool operator()(const Point& p1, const Point& p2) const {
    return p1.y() < p2.y();
  }
};



template <class ForwardIterator, class I>
double minimal_square_distance2(ForwardIterator first,
			        ForwardIterator last,
			        I& T)
/*
   ----------------------------------------------------------
   Calculates the minimal square distance of a set of points
   in O(n^2) time and returns the (double) result;
   ----------------------------------------------------------
*/
{
  typedef typename I::Point Point;
  ForwardIterator it= first;
  it++;
  double m, min_square_dist= T.double_squared_distance(*first, *it);
  ForwardIterator it1, it2;
  for( it1= first; it1 != last; it1++)
    for( it2= first; it2 != last; it2++)
      if( it1 != it2 ) {
	 m= T.double_squared_distance(*it1, *it2); 
	 if(m < min_square_dist) min_square_dist= m;
      }
  return min_square_dist;
}
 

template <class ForwardIterator, class I>
double minimal_square_distance(ForwardIterator first,
			       ForwardIterator last,
			       I& T)
/*
   ----------------------------------------------------------
   Calculates the minimal square distance of a set of points
   in O(n log(n)) time by doing a sweep-line algorithm and
   returns the (double) result;

   See:
     K.Hinrichs, J.Nievergelt, P.Schorn,
     "Plane-sweep solves the closest pair problem elegantly",
     Inform. Process. Lett., 26, 1988, p. 255-261.
   or
     Rolf Klein: "Algorithmische Geometrie", chapter 2.3.1
   ----------------------------------------------------------
*/
{
  typedef typename I::dPoint Point;
  typedef CGAL__Compare_point_x<Point> Compare_point_by_x;
  typedef CGAL__Compare_point_y<Point> Compare_point_by_y;

  /* initialize vector */
  long int size= 1;
  ForwardIterator it;
  for(it= first; it != last; it++) size++;
  //distance(first,last, size);
#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
  cout << "size: " << size << endl;
#endif  
  if( size < 3 ) { // trivial case 
    return size == 2 ? 
        T.squared_distance( T.to_dPoint(*first++), T.to_dPoint(*first)) : 0;
  }

  vector<Point> pts;
  pts.reserve(size);
  //copy(first, last, back_inserter(pts) );
  for(it= first; it != last; it++)
    pts.push_back( T.to_dPoint(*it) );
  //transform(first, last, pts.begin(), _to_double_Point);
#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
  showSequence( pts.begin(), pts.end());
#endif  

  /* sort vector */
  Compare_point_by_x compare_x;
  sort(pts.begin(), pts.end(), compare_x);
#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
  showSequence( pts.begin(), pts.end());
#endif

  /* initialize sweep status structure (sss) */
  typedef multiset<Point, Compare_point_by_y> Set;
  typedef typename Set::const_iterator const_set_iterator;
  Set  sss;
  vector<const_set_iterator> ind_sss(pts.size());
  
  ind_sss[0]= sss.insert( pts[0] );
  ind_sss[1]= sss.insert( pts[1] );
  

#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
  showSequence( sss.begin(), sss.end());
#endif
  double min_square_dist= T.squared_distance(pts[0], pts[1]);
#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
  cout << "min: " << min_square_dist << endl;
#endif

  int l= 0, r=2, s= pts.size()-1; 

  /* sweep */
  while(  r < s ) {
    if( min_square_dist < T.squared_distance_x(pts[l],pts[r]) ) {
      sss.erase(ind_sss[l++]);
    } else { /* insert new sweep - point */
      ind_sss[r]= sss.insert( pts[r++] );

      /* calculate new minimal distance */      
      /* calculates the minimal distance between point pt and
         the points in the sweep structure (SSS):
         dist(p,q):= square distance of the two points p and q.
         min_sss= min { dist(p,q) : p,q \in SSS \cup {pt} }
         return (double) min{ min_square_dist, min_sss }
      */
      double M= sqrt( min_square_dist );
      Point p_left= Point(pts[r].x(), pts[r].y() - M);
      const_set_iterator min_left= sss.lower_bound(p_left);
      Point p_right= Point(pts[r].x(), pts[r].y() + M);
      const_set_iterator min_right= sss.upper_bound(p_right);
      
      double m;
      for( const_set_iterator sit= min_left; sit != min_right; sit++) {
         m= T.squared_distance(pts[r], *sit); 
	 if( m <  min_square_dist) min_square_dist= m;
      }
     
#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
      cout << "min-neu: " << min_square_dist << endl;
#endif
    }
#ifdef CGAL__MIN_SQR_DISTANCE_DEBUG_ON
    showSequence( sss.begin(), sss.end());
#endif
  }

  return min_square_dist;
} 

