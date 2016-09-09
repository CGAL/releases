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


// Source: nsquare_intersecting.h
// Author: Carl Van Geem


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

#ifdef __GNUC__
#include <typeinfo>
#endif

#include <list.h>
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Object.h>
#include <CGAL/Segment_2_Segment_2_intersection.h>
#include <CGAL/Polygon_2.h>


template < class R >
class CGAL_Intersectionresult
{
 private:
  CGAL_Object                    _intersection_object;
  list< CGAL_Segment_2<R> >      _segments_poly1;
  list< CGAL_Segment_2<R> >      _segments_poly2;
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
  CGAL_Intersectionresult (const CGAL_Point_2<R> &iobj,
                           const CGAL_Segment_2<R> &iseg1,
                           const CGAL_Segment_2<R> &iseg2,
                           const bool &i_is_vertex_of_poly1,
                           const bool &i_is_vertex_of_poly2,
                           const bool &i_is_edge_of_poly1,
                           const bool &i_is_edge_of_poly2,
                           const bool &i_is_vertex_vertex_intersection,
                           const bool &i_is_vertex_edge_intersection,
                           const bool &i_is_edge_edge_intersection) ;
  CGAL_Intersectionresult (const CGAL_Segment_2<R> &iobj,
                           const CGAL_Segment_2<R> &iseg1,
                           const CGAL_Segment_2<R> &iseg2,
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
  list< CGAL_Segment_2<R> >  segments_poly1() const { return _segments_poly1;}
  list< CGAL_Segment_2<R> >& segments_poly1() { return _segments_poly1;}
  list< CGAL_Segment_2<R> >  segments_poly2() const { return _segments_poly2;}
  list< CGAL_Segment_2<R> >& segments_poly2() { return _segments_poly2;}
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
   void add( const CGAL_Point_2<R> &iobj,
             const CGAL_Segment_2<R> &iseg1,
             const CGAL_Segment_2<R> &iseg2,
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


   void add( const CGAL_Segment_2<R> &iobj,
             const CGAL_Segment_2<R> &iseg1,
             const CGAL_Segment_2<R> &iseg2,
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
  CGAL_nsquareintersection() {}
  list <CGAL_Intersectionresult<R> > operator()(
                          list<CGAL_Segment_2<R> >::iterator beginpoly1,
                          list<CGAL_Segment_2<R> >::iterator endpoly1,
                          list<CGAL_Segment_2<R> >::iterator beginpoly2,
                          list<CGAL_Segment_2<R> >::iterator endpoly2) 
 {
  CGAL_List_of_intersections<R> tobereturned;
  list<CGAL_Intersectionresult<R> >::iterator it;
  list<CGAL_Segment_2<R> >::iterator it1;
  list<CGAL_Segment_2<R> >::iterator it2;
  CGAL_Object    result;
  CGAL_Point_2<R> ipoint;

  CGAL_Segment_2<R> isegment;
  CGAL_Point_2<R> acgalpoint;
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
         CGAL_Polygon_2<R, Container >::Edge_const_iterator beginpoly1,
         CGAL_Polygon_2<R, Container >::Edge_const_iterator endpoly1,
         CGAL_Polygon_2<R, Container >::Edge_const_iterator beginpoly2,
         CGAL_Polygon_2<R, Container >::Edge_const_iterator endpoly2)
 {
  CGAL_List_of_intersections<R> tobereturned;
  list<CGAL_Intersectionresult<R> >::iterator it;
  CGAL_Polygon_2<R, Container >::Edge_const_iterator it1;
  CGAL_Polygon_2<R, Container >::Edge_const_iterator it2;
  CGAL_Object    result;
  CGAL_Point_2<R> ipoint;

  CGAL_Segment_2<R> isegment;
  CGAL_Point_2<R> acgalpoint;
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

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
#include "nsquare_intersecting.C"
#endif

#endif //  CGAL_NSQUARE_INTERSECTING_H
