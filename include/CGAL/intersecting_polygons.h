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
// file          : include/CGAL/intersecting_polygons.h
// author(s)     :            Carl Van Geem 
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_INTERSECTING_POLYGONS_H
#define CGAL_INTERSECTING_POLYGONS_H

#include <list.h>
#include <vector.h>
#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif
#ifndef CGAL_SEGMENT_2_H
#include <CGAL/Segment_2.h>
#endif
#ifndef CGAL_POLYGON_2_H
#include <CGAL/Polygon_2.h>
#endif
#include <iostream.h>


#ifndef CGAL_NSQUARE_INTERSECTING_H
#include <CGAL/nsquare_intersecting.h>
#endif

  struct CGAL__intersecting_polygons_myhelpelement
    {
      int _endpointleft;
      int _endpointright;
      list<int> _cutpoints; 
    };


template < class R, class Container >
class CGAL__intersecting_polygons {
public:
  typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R>, Container> Polygon;
  typedef typename Polygon::Vertex_const_iterator Polygon_vertex_const_iterator;
  typedef list<CGAL_Intersectionresult<R> > Intersectionresult;
  typedef typename Intersectionresult::const_iterator Intersectionresult_iterator;
  typedef CGAL_Point_2<R> Point;
  typedef CGAL_Segment_2<R> Segment;
  typedef vector<Point> Point_list;
  typedef typename Point_list::iterator Point_list_iterator; 
  typedef list< pair<int,int> > Edge_list;
  typedef typename Edge_list::iterator Edge_list_iterator;

private:
  Polygon _polyA, _polyB;
  Intersectionresult  _intersection_result;
  
  
public:
  CGAL__intersecting_polygons () {}
  CGAL__intersecting_polygons (const Polygon& pA, const Polygon& pB) {

    CGAL_nsquareintersection<R, Container > nsquareintersection;
    _intersection_result=nsquareintersection(pA.edges_begin(), pA.edges_end(), 
					     pB.edges_begin(), pB.edges_end());
    _polyA = pA;
    _polyB = pB;
  }
  
  ~CGAL__intersecting_polygons() {}
  
  Polygon A() const { return _polyA;}
  Polygon B() const { return _polyB;}
  Intersectionresult intersection_result() const { 
    return _intersection_result;
  }
  
  
  int size() const { return _intersection_result.size(); }
  
  void get_graph_information(Point_list& a_ptlst,
			     Edge_list& an_edlst){
    get_graph_information_code(_intersection_result, _polyA, _polyB, 
			       a_ptlst, an_edlst);
  }
  
  
  list<CGAL_Point_2<R> > get_color_informationA() {
    return get_color_information_code( _intersection_result, _polyA, 1);
  }
  
  
  list<CGAL_Point_2<R> > get_color_informationB() {
    return get_color_information_code( _intersection_result, _polyB, 2);
  }

 protected:
  void get_graph_information_code(
      const Intersectionresult& lresult,   
      const Polygon& polyA,   
      const Polygon& polyB, 
      Point_list& ptlst, 
      Edge_list& edlst)
  {
  /* built up the graph (step 2 in README) */
  typedef CGAL__intersecting_polygons_myhelpelement myhelpelement;
  list<myhelpelement> myhelpstructure;
  myhelpelement edgetosplitel ;

  Intersectionresult_iterator lrit;
  Point pt;
  Segment sm;
  Segment edgetosplit;
  Point_list_iterator ptlstit, ptlstit2;
  pair<int,int> apair;
  pair<int,int> newpair;
  Edge_list_iterator edlstit, edlstit2, tobeerased;  
  int asize;
  Polygon_vertex_const_iterator ait;
  int minnr;
  int maxnr;
  int i;
  int j;
  int pointnr = 0;
  int count = 0;
  int sourceofedge = 0;
  int targetofedge = 0;
  int firstbpoint = 0;
  int nrofvertices = 0;
  bool inlist;
  bool inedgelist;
  bool added;
  list<myhelpelement> edgestosplitlst;
  list<myhelpelement>::iterator splitit;
  list<int>::iterator intit, intit2;
/* put vertices of A in, add all segments of A (step A in README) */
  asize = polyA.size();
  i=0;
  for (ait = polyA.vertices_begin(); ait != polyA.vertices_end(); ait++)
    {
      ptlst.push_back(*ait);
      sourceofedge = i;
      targetofedge = (i+1)%asize; 
      if (sourceofedge < targetofedge)
	edlst.push_back( make_pair(sourceofedge, targetofedge));
      else
	edlst.push_back( make_pair(targetofedge, sourceofedge));
      i++;
    }
/* put vertices of B in, except those that are already there,
   add all segments of B (step B in README) */
  //bsize = polyB.size();
  i=0;
  for (ait = polyB.vertices_begin(); ait != polyB.vertices_end(); ait++)
    {/* check whether or not polyB[i] is in the list */
      ptlstit = ptlst.begin();
      inlist = false;
      sourceofedge = targetofedge;
      for (j=0; j<asize; j++)
	{
	  if ((*ptlstit)==(*ait))
	    {
	      inlist = true;
	      if (i==0) 
		firstbpoint = j;
	      targetofedge = j;
	      j = asize;
	    }
	  ptlstit++;
	}
      if (!inlist) 
	{
	  targetofedge = ptlst.size();
	  ptlst.push_back(*ait);
	  if (i==0)
	    firstbpoint = targetofedge;
	}
      if (i!=0)
	{
	  if (sourceofedge < targetofedge)
	    newpair = make_pair(sourceofedge,targetofedge);
	  else
	    newpair = make_pair(targetofedge,sourceofedge);
	  /* pair already in the list? */
	  inedgelist = false;
	  for(edlstit2=edlst.begin(); edlstit2!=edlst.end(); edlstit2++) 
	    inedgelist = inedgelist || ((*edlstit2) == newpair);
	  if (!inedgelist) 
	    edlst.push_back(newpair);
	}
      i++;
    }
  if (targetofedge < firstbpoint)
    newpair = make_pair(targetofedge,firstbpoint);
  else
    newpair = make_pair(firstbpoint, targetofedge);
  /* pair already in the list? */
  inedgelist = false;
  for(edlstit2=edlst.begin(); edlstit2!=edlst.end(); edlstit2++) 
    inedgelist = inedgelist || ((*edlstit2) == newpair);
  if (!inedgelist) 
    edlst.push_back(newpair);
  nrofvertices = ptlst.size();

#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test:*/
 cout << "lresult length: " << lresult.size() << endl;
#endif /* end test */
  /* put intersection points in (step C in README) */
  for (lrit = lresult.begin(); lrit != lresult.end(); lrit++)
    {
      if(CGAL_assign(pt, (*lrit).intersection_object()))
	{
	  /* IT'S A POINT ! */
	  /* check whether or not pt is in the list */
	  inlist = false;
	  count = 0;
	  for(ptlstit=ptlst.begin(); (!inlist) && (ptlstit!=ptlst.end());
	      ++ptlstit)
	    {
	      if ((*ptlstit)==pt)
		{/* it's an old point, already in the list */
		  inlist = true;
		  pointnr = count;
		}
	      count++;
	    }
	  if (!inlist)
	    { 
	      pointnr = ptlst.size();
	      ptlst.push_back(pt);
	    }
	 if (!((*lrit).is_vertex_of_poly1()))
	   {/* do something with the one and only edge of poly1 on which
	       pt lies... */
	     if (((*lrit).segments_poly1()).size() > 1) {
#ifdef         CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test:*/
	       cout << "1: geometrical error, too many segments" << endl;
#endif         /* end test */
	     }
	     else {
		 edgetosplit = *((*lrit).segments_poly1()).begin();
		 ptlstit2 = ptlst.begin();
		 for (i=0; i<asize; i++)
		   {
		     if (edgetosplit.min() == *ptlstit2)
		       {
			 minnr = i;
		       }
		     if (edgetosplit.max() == *ptlstit2)
		       {
			 maxnr = i;
		       }
		     ptlstit2++;
		   }
		 /* add edge to the list of edges which have to be split */
		 added = false;
		 for(splitit=edgestosplitlst.begin();
		     ( !added )&&( splitit!=edgestosplitlst.end()); 
		     splitit++ )
		   {
		     if (  ((*splitit)._endpointleft == minnr)
			 &&((*splitit)._endpointright == maxnr) )
		       {
/*1*******/
			 intit = (*splitit)._cutpoints.begin();
			 while ( (intit!= (*splitit)._cutpoints.end())
				&& (CGAL_compare_lexicographically_xy(
                            ptlst[(*intit)], ptlst[pointnr]) == CGAL_SMALLER))
			   {
			     intit++;
			   }
			 (*splitit)._cutpoints.insert(intit,1,pointnr);
#ifdef                   CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
                         cout << "added:" << pointnr;
                         cout << "to:" << minnr << "," << maxnr << endl;
#endif                   /* end test */
			 added = true;
		       }
		   }
		 if (!added) 
		   {
		     edgetosplitel._endpointleft = minnr;
		     edgetosplitel._endpointright = maxnr;
		     edgetosplitel._cutpoints.push_back(pointnr);
		     edgestosplitlst.push_back(edgetosplitel);
		     added = true;
		     edgetosplitel._cutpoints.pop_back();
#ifdef               CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
                     cout << "added:" << pointnr;
                     cout << "to:" << minnr << "," << maxnr << endl;
#endif               /* end test */
		   }
	       }
           }
	  if (!((*lrit).is_vertex_of_poly2()))
	   {/* do something with the one and only edge of poly1 on which
	       pt lies... */
	     if ( ((*lrit).segments_poly2()).size() > 1) {
#ifdef         CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test:*/
	       cout << "2: geometrical error, too many segments" << endl;
#endif         /* end test */
	     }
	     else {
		 ptlstit2 = ptlst.begin();
		 edgetosplit = *(((*lrit).segments_poly2()).begin());
		 for (i=0; i< nrofvertices; i++)
		   {
		     if (edgetosplit.min() == *ptlstit2)
		       {
			 minnr = i;
		       }
		     if (edgetosplit.max() == *ptlstit2)
		       {
			 maxnr = i;
		       }
		     ptlstit2++;
		   }
		 /* add the edge to the list of edges which have to be split */
		 added = false;
		 for(splitit=edgestosplitlst.begin();
		     (!added) && ( splitit!=edgestosplitlst.end());  
		     splitit++ )
		   {
		     if (  ((*splitit)._endpointleft == minnr)
			 &&((*splitit)._endpointright == maxnr) )
		       {
/*2*/
			 intit = (*splitit)._cutpoints.begin();
			 while ( (intit!= (*splitit)._cutpoints.end())
				&& (CGAL_compare_lexicographically_xy(
                            ptlst[(*intit)], ptlst[pointnr]) == CGAL_SMALLER))
			   {
			     intit++;
			   }
			 (*splitit)._cutpoints.insert(intit,1,pointnr);
#ifdef                   CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
                         cout << "added:" << pointnr;
                         cout << "to:" << minnr << "," << maxnr << endl;
#endif                   /* end test */
			 added = true;
		       }
		   }
		 if (!added) 
		   {
		     edgetosplitel._endpointleft = minnr;
		     edgetosplitel._endpointright = maxnr;
		     edgetosplitel._cutpoints.push_back(pointnr);
		     edgestosplitlst.push_back(edgetosplitel);
		     added = true;
		     edgetosplitel._cutpoints.pop_back();
#ifdef               CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
                     cout << "added:" << pointnr;
                     cout << "to:" << minnr << "," << maxnr << endl;
#endif              /* end test */
		   }
	       }
	   }
	}
    }
  /* cut some segments into pieces now: (step D in README) */
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 for(splitit=edgestosplitlst.begin();
     splitit!=edgestosplitlst.end(); 
     splitit++ ) 
   {
     cout << "edge: " << (*splitit)._endpointleft << "'" 
       << (*splitit)._endpointright << endl;
     cout << "its cutpoints: ";
     for (intit = ((*splitit)._cutpoints).begin();
	  intit != ((*splitit)._cutpoints).end(); intit++)
       cout << (*intit) << "," << endl;
     cout << "." << endl;
   }
#endif /* end test */
  /* go through edgestosplitlst */
  for(splitit=edgestosplitlst.begin();
      splitit!=edgestosplitlst.end(); 
      splitit++ ) 
    {
      /* for each edge (a,b,...) in that list, look for edge (a,b)
	 and cut it into pieces */
      if ((*splitit)._endpointleft < (*splitit)._endpointright)
	apair = make_pair((*splitit)._endpointleft,(*splitit)._endpointright);
      else
	apair = make_pair((*splitit)._endpointright,(*splitit)._endpointleft);
      edlstit= edlst.begin();
      while(edlstit!= edlst.end())
	{
	  if ((*edlstit)==apair)
	    {
	      tobeerased = edlstit;
	      edlstit++;
#ifdef        CGAL__INTERSECTING_POLYGONS_DEBUG_ON /*test */
              cout << "added also:" << (*splitit)._endpointleft
              << "," << (*splitit)._endpointright << endl;
#endif        /* end test */
	      ((*splitit)._cutpoints).push_front((*splitit)._endpointleft);
	      ((*splitit)._cutpoints).push_back((*splitit)._endpointright);
	      if (((*splitit)._cutpoints).size() != 0)
		{
#ifdef            CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
                  cout << apair.first << "," << apair.second << "boe: " 
                  << ((*splitit)._cutpoints).size() << endl;
#endif            /* end test */
		  intit  = ((*splitit)._cutpoints).begin();
		  intit2 = --((*splitit)._cutpoints).end();
		  while(intit != intit2)
		    {
		      sourceofedge = *intit ;
		      targetofedge = *++intit ;
		      if (sourceofedge < targetofedge)
			newpair = make_pair(sourceofedge,targetofedge);
		      else
			newpair = make_pair(targetofedge,sourceofedge);
#ifdef                CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
                      cout << newpair.first << "," << newpair.second << endl;
#endif                /* end test */
		      /* pair already in the list? */
		      inlist = false;
		      for(edlstit2=edlst.begin(); edlstit2!=edlst.end(); edlstit2++) 
			inlist = inlist || ((*edlstit2) == newpair);
		      if (!inlist) 
			edlst.push_back(newpair);
		    }
		}
	      edlst.erase(tobeerased);
	    }
	  else
	    edlstit++;
	}
    }
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /*test */
  int k=0;
  for(ptlstit = ptlst.begin();ptlstit != ptlst.end(); ptlstit++)
    cout << "ptlst[" << k++ << "] = " << (*ptlstit).x() << "," 
      << (*ptlstit).y() << endl; 
  k=0;
  for(edlstit = edlst.begin();edlstit != edlst.end(); edlstit++)
    cout << "edlst[" << k++ << "] = " << (*edlstit).first << "," 
	<< (*edlstit).second << endl; 
#endif /* end test */
}




  list<CGAL_Point_2<R> > get_color_information_code( 
      const Intersectionresult& lresult, 
      const Polygon& polyA,
      int   nr_of_poly ){

  bool added;
  Intersectionresult_iterator lrit;
  Point pt, edgevertex1, edgevertex2;
  list<Point> pts_on_A;
  list<Point>::iterator end1, end2;

  /* put vertices of A in */
  copy(polyA.vertices_begin(), polyA.vertices_end(), back_inserter(pts_on_A));
  pts_on_A.push_back(*(polyA.vertices_begin()));

  /* add intersection points */
  for (lrit = lresult.begin(); lrit != lresult.end(); lrit++) {
      if(CGAL_assign(pt, (*lrit).intersection_object())) {
	  /* IT'S A POINT ! */
	  /* treat poly1, i.e. A */
	  if (( (nr_of_poly == 1) && !((*lrit).is_vertex_of_poly1() )) ||
	      ( (nr_of_poly == 2) && !((*lrit).is_vertex_of_poly2() ))   )
	    {
	      if ( (*lrit).segments_poly1().size() > 1) {
#ifdef          CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test:*/
		cout << "3: geometrical error, too many segments" << endl;
#endif          /* end test */
	      }
	      else
		{
		  if (nr_of_poly == 1)
		    {
		      edgevertex1=
			(*((*lrit).segments_poly1()).begin()).source();
		      edgevertex2=
			(*((*lrit).segments_poly1()).begin()).target();
		    }
		  else
		    {
		      edgevertex1=
			(*((*lrit).segments_poly2()).begin()).source();
		      edgevertex2=
			(*((*lrit).segments_poly2()).begin()).target();
		    }
/* look for vertices in the list of A and add intersection point in between */
/* if source and target are not consecutive entries in the list, then we 
   have to work harder: CGAL_collinear_between or so */
		  end1 = find(pts_on_A.begin(),pts_on_A.end(),edgevertex1);
		  end2 = end1;
		  end2++;
#ifdef            CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test */
                  cout << "end1 enzo" << endl;
                  list<CGAL_Point_2<R> >::iterator pts_on_A_it;

for (pts_on_A_it =pts_on_A.begin() ;
     pts_on_A_it !=pts_on_A.end();pts_on_A_it++)
  cout << "(" << (*pts_on_A_it).x() << "," << (*pts_on_A_it).y() << "),";
cout << endl;
cout << "end1 =" << (*end1).x()  << "," << (*end1).y()  << endl;
cout << "end2 =" << (*end2).x()  << "," << (*end2).y()  << endl;
cout << "edgevertex1 =" << edgevertex1.x() << ","  << edgevertex1.y() << endl;
cout << "edgevertex2 =" << edgevertex2.x() << ","  << edgevertex2.y() << endl;
cout << "pt = " << pt.x() << "," << pt.y() << endl;
#endif            /* end test */
		  if((*end2) == edgevertex2)
		    pts_on_A.insert(end2,1,pt);
		  else
		    {
		      added = false;
		      while( (!added) && ((*end1)!=edgevertex2) )
			{
			  if (CGAL_collinear_are_ordered_along_line((*end1),pt,(*end2)))
			    {
			      pts_on_A.insert(end2,1,pt);
			      added = true;
			    }
			  else
			    {
			      end1++;
			      end2++;
			    }
			}
#ifdef                CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test:*/
		      if (!added) 
			cout << "error: intersection point not inserted"
			  << " in color list for A" << endl;
#endif                /* end test */
		    }
		}
	    }
	}
    }
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test of step PI*/
cout << "the vectors for dcel.color: " << endl;
int i=0;
for (end1 = pts_on_A.begin(); end1 != pts_on_A.end(); end1++)
  cout << "A["<< i++ << "]=" << (*end1).x() << "," << (*end1).y() << endl;
#endif /* end of test*/
  if(pts_on_A.size() > 0)  
    pts_on_A.pop_back();
  return pts_on_A;
  }
};



#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif


#endif //  CGAL_INTERSECTING_POLYGONS_H





