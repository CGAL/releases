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
// $Source: /CVSROOT/CGAL/Packages/Apollonius_graph_2/include/CGAL/Hyperbola_ray_2.h,v $
// $Revision: 1.11 $ $Date: 2003/09/18 10:19:26 $
// $Name: current_submission $
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_HYPERBOLA_RAY_2_H
#define CGAL_HYPERBOLA_RAY_2_H

#include <CGAL/Hyperbola_segment_2.h>

#ifdef CGAL_USE_QT
#include <CGAL/IO/Qt_widget.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class Gt >
class Hyperbola_ray_2 : public Hyperbola_segment_2< Gt >
{
public:
  typedef Sign                             Hyperbola_direction;
  typedef CGAL::Hyperbola_segment_2<Gt>    Base;
  typedef typename Base::Site_2            Site_2;
  typedef typename Base::Point_2           Point_2;
  typedef typename Base::Segment_2         Segment_2;
  typedef typename Gt::Ray_2               Ray_2;
  typedef typename Base::FT                FT;
  //  typedef typename R::RT         FT;
  //  typedef double                                 FT;
  //  typedef CGAL::Point_2< Cartesian<double> >     Point_2;
  //  typedef CGAL::Segment_2< Cartesian<double> >   Segment_2;
  //  typedef CGAL::Ray_2< Cartesian<double> >       Ray_2;

protected:
  static const FT OFFSET;

  template< class Stream >
  inline
  void draw_ray(Stream &W) const
  {
    W << Ray_2(this->p1, this->p2);
  }

  Site_2 _f1, _f2;
  Point_2 _p;
  Hyperbola_direction _dir;

public:
  Hyperbola_ray_2() : Hyperbola_segment_2< Gt >() {}


  Hyperbola_ray_2(const Site_2 &f1, const Site_2 &f2,
		  const Point_2 &p,
		  const Hyperbola_direction& direction) :
    Hyperbola_segment_2< Gt >(f1, f2, p, p),
    _f1(f1), _f2(f2), _p(p), _dir(direction)
  {
    FT t1 = t(this->p1);
    if ( direction == POSITIVE ) {
      this->p2 = f(t1 + this->STEP * OFFSET);
    } else {
      this->p2 = f(t1 - this->STEP * OFFSET);
    }
  }


#if defined CGAL_QT_WIDGET_H
  void draw_qt(Qt_widget& s)
  {
    if ( CGAL::is_zero(r) ) {
      draw_ray(s);
      return;
    }

    double width = s.x_max() - s.x_min();
    double height = s.y_max() - s.y_min();

    if ( width > height ) {
      STEP = height / 100.0;
    } else {
      STEP = width / 100.0;
    }

    FT t1 = t(this->p1);
    if ( _dir == POSITIVE ) {
      this->p2 = f(t1 + STEP * OFFSET);
    } else {
      this->p2 = f(t1 - STEP * OFFSET);
    }
    
    Hyperbola_segment_2< Gt >::draw(s);
  }
#endif

  template< class Stream >
  inline
  void draw(Stream& s) const
  {
    if ( CGAL::is_zero(this->r) ) {
      draw_ray(s);
      return;
    }

    Hyperbola_segment_2< Gt >::draw(s);
  }
  
};

template < class Gt >
const typename Hyperbola_ray_2<Gt>::FT
Hyperbola_ray_2<Gt>::OFFSET = 10000;



template< class Stream, class Gt >
inline
Stream& operator<<(Stream &s, const Hyperbola_ray_2<Gt> &H)
{
  H.draw(s);
  return s;
}

#if defined CGAL_QT_WIDGET_H
template< class Gt >
inline
Qt_widget& operator<<(Qt_widget &s, Hyperbola_ray_2<Gt> &H)
{
  H.draw_qt(s);
  return s;
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_HYPERBOLA_RAY_2_H
