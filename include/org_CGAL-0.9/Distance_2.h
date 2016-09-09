/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/

 
#ifndef CGAL_DISTANCE_2_H
#define CGAL_DISTANCE_2_H

 
template <class I>
class CGAL_Distance_2{
public:
    typedef I::Point Point;
    CGAL_Distance_2(const I* impl = NULL)
    {}

    CGAL_Distance_2(const Point& p0,
                    const I* impl = NULL)
        : _p0(p0)
    {}


    CGAL_Distance_2(const Point& p0,
                    const Point& p1,
                    const I* impl = NULL)
        : _p0(p0), _p1(p1)
    {}


    CGAL_Distance_2(const Point& p0,
                    const Point& p1,
                    const Point& p2,
                    const I* impl = NULL)
        : _p0(p0), _p1(p1), _p2(p2)
    {}

    void
    set_point(int i, const Point& p)
    {
        CGAL_kernel_precondition(i == 0 || i == 1 || i == 2);
        switch(i){
        case 0:
            _p0 = p;
            break;
        case 1:
            _p1 = p;
            break;
        default:
            _p2 = p;
        }
    }

    Point
    get_point(int i) const
    {
      CGAL_kernel_precondition(i == 0 || i == 1 || i == 2);
      switch(i){
      case 0:
        return _p0;
      case 1:
        return _p1;
      }
      return _p2;
    }

    CGAL_Comparison_result
    compare() const
    {
        /*
        return CGAL_compare((I::Point::Arg::FT)CGAL_squared_distance(_p0, _p1),
                            (I::Point::Arg::FT)CGAL_squared_distance(_p0, _p2));
                            */
        return CGAL_SMALLER;
    }

private:
    Point _p0, _p1, _p2;
};
 


#endif // CGAL_DISTANCE_2_H
