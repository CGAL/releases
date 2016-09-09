//  -*- Mode: c++ -*-
// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/nsquare_intersecting.h
// package       : bops (1.0.5)
// source        : include/CGAL/nsquare_intersecting.h
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:34 MET DST 1998  $
// author(s)     :        Carl Van Geem
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
// email         : cgal@cs.uu.nl
//
// ======================================================================

/*
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   An n^2 algorithm for the computation of the intersections 
    of segments belonging to two differents lists. It's the 
    first step in the computation of Boolean Operations on 
    simple polygons in 2D.

   Last changes: 26.Mar.1997
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef CGAL_NSQUARE_INTERSECTING_H
#define CGAL_NSQUARE_INTERSECTING_H

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#include <list.h>

#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif
#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif
#ifndef CGAL_OBJECT_H
#include <CGAL/Object.h>
#endif

#ifndef CGAL_SEGMENT_2_SEGMENT_2_INTERSECTION_H
#include <CGAL/Segment_2_Segment_2_intersection.h>
#endif
#ifndef CGAL_POLYGON_2_H
#include <CGAL/Polygon_2.h>
#endif

#include <iostream.h>


template < class R >
class CGAL_Intersectionresult
{
  typedef CGAL_Point_2<R> Point;
  typedef CGAL_Segment_2<R> Segment;
  typedef list<Segment> Segment_list;
  //typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container > Polygon;
  //typedef typename Polygon::Edge_const_iterator edge_iterator;

 private:
  CGAL_Object                    _intersection_object;
  Segment_list      _segments_poly1;
  Segment_list      _segments_poly2;
  bool                           _is_vertex_of_poly1;
  bool                           _is_vertex_of_poly2;
  bool                           _is_edge_of_poly1;
  bool                           _is_edge_of_poly2;
  bool                           _is_vertex_vertex_intersection;
  bool                           _is_vertex_edge_intersection;
  bool                           _is_edge_edge_intersection;
 public:
  CGAL_Intersectionresult() ;
  CGAL_Intersectionresult (const CGAL_Intersectionresult<R> &ires ) ;
  CGAL_Intersectionresult (const Point &iobj,
                           const Segment &iseg1,
                           const Segment &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) ;
  CGAL_Intersectionresult (const Segment &iobj,
                           const Segment &iseg1,
                           const Segment &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) ;
  CGAL_Intersectionresult<R>  &operator=(const CGAL_Intersectionresult<R> 
                                                                   &ires) ; 
  ~CGAL_Intersectionresult() ;


  CGAL_Object     intersection_object() const { return _intersection_object;}
  CGAL_Object&    intersection_object() { return _intersection_object;}
  Segment_list  segments_poly1() const { return _segments_poly1;}
  Segment_list& segments_poly1() { return _segments_poly1;}
  Segment_list  segments_poly2() const { return _segments_poly2;}
  Segment_list& segments_poly2() { return _segments_poly2;}
  bool   is_vertex_of_poly1() const { return _is_vertex_of_poly1;}
  bool&  is_vertex_of_poly1() { return _is_vertex_of_poly1;}
  bool   is_vertex_of_poly2() const { return _is_vertex_of_poly2;}
  bool&  is_vertex_of_poly2() { return _is_vertex_of_poly2;}
  bool   is_edge_of_poly1()   const { return _is_edge_of_poly1;}
  bool&  is_edge_of_poly1()   { return _is_edge_of_poly1;}
  bool   is_edge_of_poly2()   const { return _is_edge_of_poly2;}
  bool&  is_edge_of_poly2()   { return _is_edge_of_poly2;}
  bool   is_vertex_vertex_intersection() const
           { return _is_vertex_vertex_intersection;}
  bool&  is_vertex_vertex_intersection() 
           { return _is_vertex_vertex_intersection;}
  bool   is_vertex_edge_intersection()   const  
           { return _is_vertex_edge_intersection;}
  bool&  is_vertex_edge_intersection()   
           { return _is_vertex_edge_intersection;}
  bool   is_edge_edge_intersection()     const  
           { return _is_edge_edge_intersection;}
  bool&  is_edge_edge_intersection()     
           { return _is_edge_edge_intersection;}


};






template < class R > 
class CGAL_List_of_intersections
{
 public:
  typedef CGAL_Point_2<R> Point;
  typedef CGAL_Segment_2<R> Segment;
  typedef list<Segment> Segment_list;
  //typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container > Polygon;
  //typedef typename Polygon::Edge_const_iterator edge_iterator;

 private:
   list<CGAL_Intersectionresult<R> >    _list_of_intersections;
 public:
   CGAL_List_of_intersections() ;
   CGAL_List_of_intersections(const CGAL_List_of_intersections<R> &ilist) ;
   CGAL_List_of_intersections<R> &operator=(
                              const CGAL_List_of_intersections<R> &ilist) ;
   ~CGAL_List_of_intersections() ;


   list<CGAL_Intersectionresult<R> >  list_of_intersections() const {
                                   return _list_of_intersections; }
   list<CGAL_Intersectionresult<R> >&  list_of_intersections() {
                                   return _list_of_intersections; }
   void add( const Point &iobj,
             const Segment &iseg1,
             const Segment &iseg2,
             const bool &i_is_vertex_of_poly1,
             const bool &i_is_vertex_of_poly2,
             const bool &i_is_edge_of_poly1,
             const bool &i_is_edge_of_poly2,
             const bool &i_is_vertex_vertex_intersection,
             const bool &i_is_vertex_edge_intersection,
             const bool &i_is_edge_edge_intersection) 
      {
       CGAL_Intersectionresult<R> ires( 
            iobj,
            iseg1,
            iseg2,
            i_is_vertex_of_poly1,
            i_is_vertex_of_poly2,
            i_is_edge_of_poly1,
            i_is_edge_of_poly2,
            i_is_vertex_vertex_intersection,
            i_is_vertex_edge_intersection,
            i_is_edge_edge_intersection);

       _list_of_intersections.push_back(ires); 
      }


   void add( const Segment &iobj,
             const Segment &iseg1,
             const Segment &iseg2,
             const bool &i_is_vertex_of_poly1,
             const bool &i_is_vertex_of_poly2,
             const bool &i_is_edge_of_poly1,
             const bool &i_is_edge_of_poly2,
             const bool &i_is_vertex_vertex_intersection,
             const bool &i_is_vertex_edge_intersection,
             const bool &i_is_edge_edge_intersection) 
      {
       CGAL_Intersectionresult<R> ires( 
            iobj,
            iseg1,
            iseg2,
            i_is_vertex_of_poly1,
            i_is_vertex_of_poly2,
            i_is_edge_of_poly1,
            i_is_edge_of_poly2,
            i_is_vertex_vertex_intersection,
            i_is_vertex_edge_intersection,
            i_is_edge_edge_intersection);

       _list_of_intersections.push_back(ires); 
      }

 };



template < class R, class Container >
class CGAL_nsquareintersection {
 public:
  typedef CGAL_Point_2<R> Point;
  typedef CGAL_Segment_2<R> Segment;
  typedef list<Segment> Segment_list;
  typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container > Polygon;
  typedef typename Polygon::Edge_const_iterator edge_iterator;
  typedef typename Segment_list::iterator segment_iterator;

  CGAL_nsquareintersection() {}
  list <CGAL_Intersectionresult<R> > operator()(
                          segment_iterator beginpoly1,
                          segment_iterator endpoly1,
                          segment_iterator beginpoly2,
                          segment_iterator endpoly2) 
 {
  CGAL_List_of_intersections<R> tobereturned;
  list<CGAL_Intersectionresult<R> >::iterator it;
  segment_iterator it1;
  segment_iterator it2;
  CGAL_Object    result;
  Point ipoint;

  Segment isegment;
  Point acgalpoint;
  bool notfound;
  bool i_is_vertex_of_poly1;
  bool i_is_vertex_of_poly2;
  bool i_is_edge_of_poly1;
  bool i_is_edge_of_poly2;
  bool i_is_vertex_vertex_intersection;
  bool i_is_vertex_edge_intersection;
  bool i_is_edge_edge_intersection;

  for(it1 = beginpoly1; it1 != endpoly1; it1++ )
   {
    for(it2 = beginpoly2; it2 != endpoly2; it2++ )
     {
      if ( CGAL_do_intersect(*it1, *it2) )
       {
        result = CGAL_intersection(*it1, *it2);
        if ( CGAL_assign(ipoint, result) )
         {/* report intersection */
          it = tobereturned.list_of_intersections().begin();
          notfound = true;
          while ((it != tobereturned.list_of_intersections().end())
                  && (notfound) )
            {
             if ( ( CGAL_assign(acgalpoint, (*it).intersection_object()) )
              &&  ( acgalpoint == ipoint ) )
               {
                notfound = false;
                /* adapt the information in *it */
                (*it).segments_poly1().push_back(*it1);
                (*it).segments_poly2().push_back(*it2);
/*              (*it).is_edge_of_poly1() = false;
                (*it).is_edge_of_poly2() = false;

                (*it).is_edge_edge_intersection() = false; */

                if ((ipoint == (*it1).min())||(ipoint == (*it1).max()))
                  {  (*it).is_vertex_of_poly1() = true; }
                if ((ipoint == (*it2).min())||(ipoint == (*it2).max()))
                  {  (*it).is_vertex_of_poly2() = true; }

                if (  ((*it).is_vertex_of_poly1())
                    &&((*it).is_vertex_of_poly2()))
                  {  (*it).is_vertex_vertex_intersection() = true; }
                 else
                  {
                   (*it).is_vertex_vertex_intersection() = false;
                   if ( ((*it).is_vertex_of_poly1())
                     || ((*it).is_vertex_of_poly2()))
                     { (*it).is_vertex_edge_intersection() = true; 
		       if ( ( (*it).is_vertex_of_poly1() ) &&
			    ( (*it).segments_poly2().size() > 1 ) )
			 (*it).segments_poly2().pop_back();
		       if ( ( (*it).is_vertex_of_poly2() ) &&
			    ( (*it).segments_poly1().size() > 1 ) )
			 (*it).segments_poly1().pop_back();
		     }
                    else
                     { (*it).is_vertex_edge_intersection() = false;}
                  }
               }
              it++;
            }
          if (notfound)

           {/* add this intersection point to the list */
            i_is_vertex_of_poly1 =
               ((ipoint == (*it1).min())||(ipoint == (*it1).max()));
            i_is_vertex_of_poly2 =
               ((ipoint == (*it2).min())||(ipoint == (*it2).max()));
            i_is_vertex_vertex_intersection =
               ( i_is_vertex_of_poly1 && i_is_vertex_of_poly2 );
            i_is_vertex_edge_intersection =
               ( (( i_is_vertex_of_poly1)&&(!i_is_vertex_of_poly2)) ||
                 ((!i_is_vertex_of_poly1)&&( i_is_vertex_of_poly2)) ) ;
            i_is_edge_edge_intersection = !i_is_vertex_edge_intersection;

            tobereturned.add(ipoint,*it1,*it2, i_is_vertex_of_poly1,
                         i_is_vertex_of_poly2,false,false,
                         i_is_vertex_vertex_intersection,
                         i_is_vertex_edge_intersection,
                         i_is_edge_edge_intersection) ;
           }
         }
        else if ( CGAL_assign(isegment, result) )
         {/* report intersection */
          i_is_edge_of_poly1 = (isegment == *it1) ;
          i_is_edge_of_poly2 = (isegment == *it2) ;

          tobereturned.add(isegment,*it1,*it2,false,false,
                                         i_is_edge_of_poly1,
                                         i_is_edge_of_poly2,
                                         false,false,true );
         }
       }
     }
   }
  return tobereturned.list_of_intersections();
 }

  list <CGAL_Intersectionresult<R> > operator()(
         edge_iterator beginpoly1,
         edge_iterator endpoly1,
         edge_iterator beginpoly2,
         edge_iterator endpoly2)
 {
  CGAL_List_of_intersections<R> tobereturned;
  list<CGAL_Intersectionresult<R> >::iterator it;
  edge_iterator it1;
  edge_iterator it2;
  CGAL_Object    result;
  Point ipoint;

  Segment isegment;
  Point acgalpoint;
  bool notfound;
  bool i_is_vertex_of_poly1;
  bool i_is_vertex_of_poly2;
  bool i_is_edge_of_poly1;
  bool i_is_edge_of_poly2;
  bool i_is_vertex_vertex_intersection;
  bool i_is_vertex_edge_intersection;
  bool i_is_edge_edge_intersection;
 
  for(it1 = beginpoly1; it1 != endpoly1; ++it1 )
   {
    for(it2 = beginpoly2; it2 != endpoly2; ++it2 )
     {
      if ( CGAL_do_intersect(*it1, *it2) )
       {
        result = CGAL_intersection(*it1, *it2);
        if ( CGAL_assign(ipoint, result) )
         {/* report intersection */
          it = tobereturned.list_of_intersections().begin();
          notfound = true;
          while ((it != tobereturned.list_of_intersections().end())
                  && (notfound) )
            {
             if ( ( CGAL_assign(acgalpoint, (*it).intersection_object()) )
              &&  ( acgalpoint == ipoint ) )
               {
                notfound = false;
                /* adapt the information in *it */
                (*it).segments_poly1().push_back(*it1);
                (*it).segments_poly2().push_back(*it2);
/*              (*it).is_edge_of_poly1() = false;
                (*it).is_edge_of_poly2() = false;

                (*it).is_edge_edge_intersection() = false; */

                if ((ipoint == (*it1).min())||(ipoint == (*it1).max()))
                  {  (*it).is_vertex_of_poly1() = true; }
                if ((ipoint == (*it2).min())||(ipoint == (*it2).max()))
                  {  (*it).is_vertex_of_poly2() = true; }

                if (  ((*it).is_vertex_of_poly1())
                    &&((*it).is_vertex_of_poly2()))
                  {  (*it).is_vertex_vertex_intersection() = true; }
                 else
                  {
                   (*it).is_vertex_vertex_intersection() = false;
                   if ( ((*it).is_vertex_of_poly1())
                     || ((*it).is_vertex_of_poly2()))
                     { (*it).is_vertex_edge_intersection() = true; 
		       if ( ( (*it).is_vertex_of_poly1() ) &&
			    ( (*it).segments_poly2().size() > 1 ) )
			 (*it).segments_poly2().pop_back();
		       if ( ( (*it).is_vertex_of_poly2() ) &&
			    ( (*it).segments_poly1().size() > 1 ) )
			 (*it).segments_poly1().pop_back();
		     }
                    else
                     { (*it).is_vertex_edge_intersection() = false;}
                  }
               }
              it++;
            }
          if (notfound)

           {/* add this intersection point to the list */
            i_is_vertex_of_poly1 =
               ((ipoint == (*it1).min())||(ipoint == (*it1).max()));
            i_is_vertex_of_poly2 =
               ((ipoint == (*it2).min())||(ipoint == (*it2).max()));
            i_is_vertex_vertex_intersection =
               ( i_is_vertex_of_poly1 && i_is_vertex_of_poly2 );
            i_is_vertex_edge_intersection =
               ( (( i_is_vertex_of_poly1)&&(!i_is_vertex_of_poly2)) ||
                 ((!i_is_vertex_of_poly1)&&( i_is_vertex_of_poly2)) ) ;
            i_is_edge_edge_intersection = !i_is_vertex_edge_intersection;

            tobereturned.add(ipoint,*it1,*it2, i_is_vertex_of_poly1,
                         i_is_vertex_of_poly2,false,false,
                         i_is_vertex_vertex_intersection,
                         i_is_vertex_edge_intersection,
                         i_is_edge_edge_intersection) ;
           }
         }
        else if ( CGAL_assign(isegment, result) )
         {/* report intersection */
          i_is_edge_of_poly1 = (isegment == *it1) ;
          i_is_edge_of_poly2 = (isegment == *it2) ;

          tobereturned.add(isegment,*it1,*it2,false,false,
                                         i_is_edge_of_poly1,
                                         i_is_edge_of_poly2,
                                         false,false,true );
         }
       }
     }
   }
  return tobereturned.list_of_intersections();
 }


};

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/nsquare_intersecting.C>
#endif

#endif //  CGAL_NSQUARE_INTERSECTING_H
