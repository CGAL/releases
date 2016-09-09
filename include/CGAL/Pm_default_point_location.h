// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Pm_default_point_location.h
// package       : pm (3.07)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 Iddo Hanniel
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_DEFAULT_POINT_LOCATION_H
#define CGAL_PM_DEFAULT_POINT_LOCATION_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#ifndef CGAL_PM_POINT_LOCATION_BASE_H
#include <CGAL/Pm_point_location_base.h>
#endif


#ifndef CGAL_TRAPEZOIDAL_MAP_2_H
#include <CGAL/Trapezoidal_map_2.h>
#endif



CGAL_BEGIN_NAMESPACE


////////////////////////////////////////////////////////////////////
//DEFAULT STRATEGY
///////////////////////////////////////////////////////////////////

//to solve the internal compiler errors egcs is having when dealing
//with nested classes we moved it outside
template <class Planar_map>
class _X_curve_plus: public Planar_map::Traits::X_curve
{
public:
  //typedefs from point location
  typedef typename Planar_map::Traits Traits;
  typedef typename Planar_map::Locate_type Locate_type;
  typedef typename Planar_map::Halfedge_handle Halfedge_handle;
  
  // begin oren corrections
  //error C2086: '<Unknown>' : redefinition
  //typedef typename Traits::X_curve X_curve;
  
  typedef typename Traits::X_curve curve;
  typedef typename Traits::Point Point;
  


  _X_curve_plus() : curve(),parent() {};
  _X_curve_plus(const Point& p,const Point& q) : curve(p,q),parent() {};
  _X_curve_plus(const curve &cv,const Halfedge_handle& p) : curve(cv),parent(p){}
  _X_curve_plus(const Halfedge_handle& p) : curve(p->curve()),parent(p){}
  // used when no Halfedge_handle is supplied.
  _X_curve_plus(const curve &cv) : curve(cv),parent() {};
  _X_curve_plus(const _X_curve_plus &cv) : curve(cv),parent(cv.parent){}
  ~_X_curve_plus(){}
  _X_curve_plus& operator=(const _X_curve_plus &cv)
  {
    curve::operator=(cv);
    parent=cv.get_parent();
    return *this;
  }
  Halfedge_handle get_parent() const
  {
    return parent;
  }
protected:
  Halfedge_handle parent;
};



//------------------------------------------------------------------


template <class Planar_map>
class Pm_default_point_location : public Pm_point_location_base<Planar_map> {

protected:
 
  typedef _X_curve_plus<Planar_map> X_curve_plus;
  

  typedef typename Planar_map::Traits_wrap Traits_wrap;
  typedef Trapezoidal_map_2<Traits_wrap,X_curve_plus> TM;
  typedef Planar_map PM;


public:
  Pm_default_point_location(bool preprocess=false) 
    {tm.set_needs_update(preprocess);}
  


  void init(Planar_map& pmp, Traits& tr) {
    pm = &pmp;
    traits = (Traits_wrap*)&tr;
    tm.init_traits(traits);
  }
  ~Pm_default_point_location() {}
  /* 
     Postcondition:
     h->curve() with a reference back to h
     is inserted into TM.
  */
  
  
  
  void insert(Halfedge_handle h
              //additions by iddo for arrangement
              ,const X_curve& cv
              //end additions
              )
    {
      //	tm.insert(X_curve_plus(h));
      tm.insert(X_curve_plus(cv,h));
    }
  
  /* postconditions:
     The output Halfedge_handle represents a 
     planar map subdivision region that contains the 
     input Point in its interior or equal to it.
     The input Locate_type is equal to the type 
     of this region.
  */
  Halfedge_handle locate(const Point& p, Locate_type& lt) //const
    {
      //there are different internal compiler errors if we
      // typedef the Locate_type
      typename TM::Locate_type tm_lt; 
      
      const X_curve_plus& cv = tm.locate(p,tm_lt).top();
      // treat special case, where trapezoid is unbounded.
      //	for then get_parent() is not defined
      if (tm_lt==TM::UNBOUNDED_TRAPEZOID)
	{
          lt=PM::UNBOUNDED_FACE;
          return halfedge_representing_unbounded_face();
	}
      Halfedge_handle h = cv.get_parent();
      lt=convert(p,tm_lt,h);
      return h;
    }
  /* postconditions:
     The output Halfedge_handle represents a planar map 
     subdivision region that contains the first Point 
     on the closed vertical ray eminating from the input 
     Point in upward or downward direction depending on 
     the input bool in its interior or equal to it.
     The input Locate_type is equal to the type 
     of this region.
  */
  Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, bool up) // const
    {
      //trying to workaround internal compiler error
      typename TM::Locate_type tm_lt;
      
      X_curve_plus cv = tm.vertical_ray_shoot(p,tm_lt,up);
      // treat special case, where trapezoid is unbounded.
      //	for then get_parent() is not defined
      if (tm_lt==TM::UNBOUNDED_TRAPEZOID)
	{
          lt=PM::UNBOUNDED_FACE;
          return halfedge_representing_unbounded_face();
	}
      Halfedge_handle h=cv.get_parent();
      lt=convert(p,tm_lt,h,up);
      return h;
    }
  
  //the function is called after the combinatoric split
  //we want O(1) is it possible?? no!
  void split_edge(const X_curve &cv,
                  Halfedge_handle e1,
                  Halfedge_handle e2
                  //additions by iddo for arrangement
                  ,const X_curve& cv1, const X_curve& cv2
                  //end additions
                  )
    {
      //	  tm.split_edge(X_curve_plus(cv),X_curve_plus(e1),X_curve_plus(e2));
     tm.split_edge(X_curve_plus(cv),X_curve_plus(cv1,e1),X_curve_plus(cv2,e2));
    }
  
  /*
    called after combinatoric merge
    e is the new edge cv1,cv2 are the original curves
  */
  void merge_edge(const X_curve &cv1,
                  const X_curve &cv2,
                  Halfedge_handle e 
                  //additions by iddo for arrangement
                  ,const X_curve& cv
                  //end additions
                  )
    {
      tm.merge_edge(
                    X_curve_plus(cv1),
                    X_curve_plus(cv2),
                    //		X_curve_plus(e)
                    X_curve_plus(cv,e)
                    );
    }
  
  //called before combinatoric deletion
  void remove_edge(Halfedge_handle e)
    {
      tm.remove(X_curve_plus(e));
    }
  
#ifndef CGAL_PM_DEFAULT_POINT_LOCATION_DEBUG
  
protected:
  TM tm;
private:
  
#else
  
public:
  void debug()
    {
      tm.debug();
    }

  TM tm;
  
#endif
  
  Planar_map* pm;
  Traits_wrap* traits;

  bool halfedge_represents_point(const Halfedge_handle& h,const Point& p) const
    {
      Point 
	source=h->source()->point(),
	target=h->target()->point();
      return !(!traits->point_is_same_x(target,p)||
               traits->point_is_same_x(source,p)&&
               (traits->point_is_higher(p,target)&&
                traits->point_is_lower(target,source)||
                traits->point_is_lower(p,target)&&
                traits->point_is_higher(target,source)
                ));
    }
  /* 
     description:
     returns if the point is located in the 
     open halfplane on the right side of the
     input curve
     (considering the halfedge orientation)
     preconditions:
     the input curve is not vertical,
     p is in its x range but not on its closure
  */
  bool halfedge_represents_point_inside_face(const Halfedge_handle& h,
                                             const Point& p) const 
    {
      return (traits->curve_get_point_status(h->curve(),p)==Traits::ABOVE_CURVE)==traits->point_is_left(h->source()->point(),h->target()->point());
    }
  Halfedge_handle halfedge_representing_unbounded_face() const
    {
      CGAL_assertion(pm);
      if (pm->unbounded_face()->holes_begin()!=pm->unbounded_face()->holes_end()) {
        // case PM is not empty
        //return *(pm->unbounded_face()->holes_begin());
        typename Planar_map::Holes_iterator hot=pm->unbounded_face()->holes_begin();
        return (*hot);
      }
      else
        // case PM is empty
        return pm->halfedges_end();
    }
  
  //use the latter
  //to workaround internal compiler error in egcs1.1
  //	Locate_type convert(const Point& p,const typename TM::Locate_type& lt,Halfedge_handle& h,bool up=true) const	
  Locate_type convert(const Point& p,const int& lt,Halfedge_handle& h,bool up=true) const
    {
      switch(lt)
        {
          // h->target() should represent p
        case TM::POINT:
          if (!halfedge_represents_point(h,p)) h=h->twin();
          return PM::VERTEX;
        case TM::CURVE:
          /* special case:
             h->source()->point(),p,h->target()->point() have same x
             coardinates.
             return value should be h(no h->twin()).
          */
          // orientation of h
          if (up==traits->point_is_left(h->source()->point(),h->target()->point())) h=h->twin();
          return PM::EDGE;
        case TM::TRAPEZOID:
          if (!halfedge_represents_point_inside_face(h,p)) h=h->twin();
          CGAL_postcondition(halfedge_represents_point_inside_face(h,p));
          if (!h->face()->is_unbounded())
            return PM::FACE;
          // otherwise pass to UNBOUNDED_TRAPEZOID case
        case TM::UNBOUNDED_TRAPEZOID:
          h=halfedge_representing_unbounded_face();
          CGAL_postcondition(h->face()->is_unbounded());
          return PM::UNBOUNDED_FACE;
        default:
          CGAL_assertion(lt==TM::POINT||lt==TM::CURVE||lt==TM::TRAPEZOID||lt==TM::UNBOUNDED_TRAPEZOID);
        }
      return Locate_type();
    }
  
  
};


CGAL_END_NAMESPACE

#endif












