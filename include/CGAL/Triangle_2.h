// Source: Triangle_2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_TRIANGLE_2_H
#define CGAL_TRIANGLE_2_H


#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/TriangleH2.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/TriangleC2.h>
#endif // CGAL_CARTESIAN_H

#include <CGAL/Point_2.h>

template <class R >
  class CGAL_Triangle_2 : public R::Triangle_2
{
public:
    CGAL_Triangle_2()
      : R::Triangle_2()
    {}

    CGAL_Triangle_2(const CGAL_Triangle_2<R> &t)
      : R::Triangle_2((R::Triangle_2&)t)
    {}

    CGAL_Triangle_2(const R::Triangle_2 &t)
      : R::Triangle_2(t)
    {}

    CGAL_Triangle_2(const CGAL_Point_2<R> &p,
                    const CGAL_Point_2<R> &q,
                    const CGAL_Point_2<R> &r)
      : R::Triangle_2(p,q,r)
    {}


  CGAL_Triangle_2<R>  &operator=(const CGAL_Triangle_2<R> &t)
    {
      R::Triangle_2::operator=(t);
      return *this;
    }

  bool                operator==(const CGAL_Triangle_2<R> &t) const
    {
      return R::Triangle_2::operator==(t);
    }

  bool                operator!=(const CGAL_Triangle_2<R> &t) const
    {
      return !(*this == t);
    }

  bool                identical(const CGAL_Triangle_2<R> &t) const
    {
      return ( PTR == t.PTR );
    }


  CGAL_Point_2<R>     vertex(int i) const
    {
      return R::Triangle_2::vertex(i);
    }

  CGAL_Point_2<R>     operator[](int i) const
    {
      return vertex(i);
    }


  CGAL_Triangle_2<R>  transform(const CGAL_Aff_transformation_2<R> &t) const
  {
    return  R::Triangle_2::transform(t);
  }

  CGAL_Triangle_2<R>  opposite() const
  {
    return  CGAL_Triangle_2<R>(vertex(0), vertex(2), vertex(1));
  }


  CGAL_Side           where_is(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::where_is(p);
    }

  bool                is_on(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::is_on(p);
    }

  bool                is_inside(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::is_inside(p);
    }

  bool                is_outside(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::is_outside(p);
    }


  bool                is_in_bounded_region(const CGAL_Point_2<R> &p) const
    {
      return R::Triangle_2::is_in_bounded_region(p);
    }

  bool                is_degenerate() const
    {
      return R::Triangle_2::is_degenerate();
    }

  CGAL_Bbox_2           bbox() const
    {
      return vertex(0).bbox() + vertex(1).bbox() + vertex(2).bbox();
    }
};



#endif
