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


// Source: intersecting_polygons.h
// Author: Carl Van Geem

#ifndef CGAL_INTERSECTING_POLYGONS_H
#define CGAL_INTERSECTING_POLYGONS_H

#ifdef __GNUC__
#include <std/typeinfo.h>
#endif

#include <list.h>
#include <deque.h>
#include <CGAL/Polygon_2.h>
#include <iostream.h>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>

#include <CGAL/nsquare_intersecting.h>
  struct CGAL__intersecting_polygons_myhelpelement
    {
      int _endpointleft;
      int _endpointright;
      list<int> _cutpoints; 
    };

template < class R, class Container >
class CGAL__intersecting_polygons {  
 private:
  CGAL_Polygon_2<R, Container>                 _polyA;
  CGAL_Polygon_2<R, Container>                 _polyB;
  list<CGAL_Intersectionresult<R> >       _intersection_result;
  
  
 public:
  CGAL__intersecting_polygons () {}
  CGAL__intersecting_polygons (const CGAL_Polygon_2<R, Container>& pA, 
			       const CGAL_Polygon_2<R, Container>& pB) {

    CGAL_nsquareintersection<R, Container > nsquareintersection;
    _intersection_result=nsquareintersection(pA.edges_begin(), pA.edges_end(), 
					     pB.edges_begin(), pB.edges_end());
    _polyA = pA;
    _polyB = pB;}
  
  ~CGAL__intersecting_polygons() {}
  
  CGAL_Polygon_2<R, Container>   A() { return _polyA;}
  CGAL_Polygon_2<R, Container>   B() { return _polyB;}
  list<CGAL_Intersectionresult<R> >   intersection_result() { 
    return _intersection_result;}
  
  
  int size() const { return _intersection_result.size(); }
  
  void get_graph_information(deque< CGAL_Point_2<R> >& a_ptlst,
			     list< pair<int,int> >& an_edlst){
    get_graph_information_code(_intersection_result, _polyA, _polyB, 
			       a_ptlst, an_edlst);}
  
  
  list<CGAL_Point_2<R> > get_color_informationA() {
    return get_color_information_code( _intersection_result, _polyA, 1);}
  
  
  list<CGAL_Point_2<R> > get_color_informationB() {
    return get_color_information_code( _intersection_result, _polyB, 2);}

 protected:
  void get_graph_information_code(
      const list<CGAL_Intersectionresult<R> >& lresult,   
      const CGAL_Polygon_2<R, Container>& polyA,   
      const CGAL_Polygon_2<R, Container>& polyB, 
      deque< CGAL_Point_2<R> >	        &ptlst, 
      list< pair<int,int> >             &edlst){
  /* built up the graph (step 2 in README) */
typedef CGAL__intersecting_polygons_myhelpelement myhelpelement;
/* old code:
  struct myhelpelement
    {
      int _endpointleft;
      int _endpointright;
      list<int> _cutpoints; 
    };
end of old code */
  list<myhelpelement> myhelpstructure;
  myhelpelement edgetosplitel ;

  list<CGAL_Intersectionresult<R> >::const_iterator lrit;
  CGAL_Point_2<R> pt;
  CGAL_Segment_2<R> sm;
  CGAL_Segment_2<R> edgetosplit;
  deque< CGAL_Point_2<R> >::iterator ptlstit;
  deque< CGAL_Point_2<R> >::iterator ptlstit2;
  pair<int,int> apair;
  pair<int,int> newpair;
  list< pair<int,int> >::iterator edlstit;  
  list< pair<int,int> >::iterator edlstit2;
  list< pair<int,int> >::iterator tobeerased;
  int asize;
  int bsize;
  CGAL_Polygon_2<R, Container>::Vertex_const_iterator ait;
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
  list<int>::iterator intit;
  list<int>::iterator intit2;
/* put vertices of A in, add all segments of A (step A in README) */
/* old code, using vector for CONTAINER:
  asize = polyA.size();
  for (i=0; i<asize; i++)
    {
      ptlst.push_back(polyA[i]);
      sourceofedge = i;
      targetofedge = (i+1)%asize; 
      if (sourceofedge < targetofedge)
	edlst.push_back( make_pair(sourceofedge, targetofedge));
      else
	edlst.push_back( make_pair(targetofedge, sourceofedge));
    }
End of old code */
/* begin of new code */
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
/* end of new code */
/* put vertices of B in, except those that are already there,
   add all segments of B (step B in README) */
  bsize = polyB.size();
/* old code for CONTAINER == vector
  for (i=0; i<bsize; i++)
    {
      ptlstit = ptlst.begin();
      inlist = false;
      sourceofedge = targetofedge;
      for (j=0; j<asize; j++)
	{
	  if ((*ptlstit)==polyB[i])
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
	  ptlst.push_back(polyB[i]);
	  if (i==0)
	    firstbpoint = targetofedge;
	}
      if (i!=0)
	{
	  if (sourceofedge < targetofedge)
	    edlst.push_back( make_pair(sourceofedge, targetofedge));
	  else
	    edlst.push_back( make_pair(targetofedge, sourceofedge));
	}
    }
End of old code */
/* begin of new code */
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
	  for(edlstit2=edlst.begin();
	      edlstit2!=edlst.end();
	      edlstit2++) 
	    inedgelist = inedgelist || ((*edlstit2) == newpair);
	  if (!inedgelist) 
	    edlst.push_back(newpair);
	}
      i++;
    }
/* end of new code */
  if (targetofedge < firstbpoint)
    newpair = make_pair(targetofedge,firstbpoint);
  else
    newpair = make_pair(firstbpoint, targetofedge);
  /* pair already in the list? */
  inedgelist = false;
  for(edlstit2=edlst.begin();
      edlstit2!=edlst.end();
      edlstit2++) 
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
	     if (((*lrit).segments_poly1()).size() > 1) 
	       cout << "geometrical error, too many segments" << endl;
	     else
	       {
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 cout << "added:" << pointnr;
 cout << "to:" << minnr << "," << maxnr << endl;
#endif /* end test */
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 cout << "added:" << pointnr;
 cout << "to:" << minnr << "," << maxnr << endl;
#endif /* end test */
		   }
	       }
           }
	  if (!((*lrit).is_vertex_of_poly2()))
	   {/* do something with the one and only edge of poly1 on which
	       pt lies... */
	     if ( ((*lrit).segments_poly2()).size() > 1) 
	       cout << "geometrical error, too many segments" << endl;
	     else
	       {
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 cout << "added:" << pointnr;
 cout << "to:" << minnr << "," << maxnr << endl;
#endif /* end test */
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 cout << "added:" << pointnr;
 cout << "to:" << minnr << "," << maxnr << endl;
#endif /* end test */
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /*test */
 cout << "added also:" << (*splitit)._endpointleft << 
   "," << (*splitit)._endpointright << endl;
#endif /* end test */
	      ((*splitit)._cutpoints).push_front((*splitit)._endpointleft);
	      ((*splitit)._cutpoints).push_back((*splitit)._endpointright);
	      if (((*splitit)._cutpoints).size() != 0)
		{
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 cout << apair.first << "," << apair.second << "boe: " 
   << ((*splitit)._cutpoints).size() << endl;
#endif /* end test */
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test: */
 cout << newpair.first << "," << newpair.second << endl;
#endif /* end test */
		      /* pair already in the list? */
		      inlist = false;
		      for(edlstit2=edlst.begin();
			  edlstit2!=edlst.end();
			  edlstit2++) 
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
      const list<CGAL_Intersectionresult<R> >& lresult, 
      const CGAL_Polygon_2<R, Container>& polyA,
      int                               nr_of_poly ){


  int asize;
  CGAL_Polygon_2<R, Container>::Vertex_const_iterator ait;
/* begin of old code for CONTAINER == vector
  int i;
End of old code */
  bool added;
  list<CGAL_Intersectionresult<R> >::const_iterator lrit;
  CGAL_Point_2<R> pt;
  CGAL_Point_2<R> edgevertex1;
  CGAL_Point_2<R> edgevertex2;
  list<CGAL_Point_2<R> > pts_on_A;
  list<CGAL_Point_2<R> >::iterator end1;
  list<CGAL_Point_2<R> >::iterator end2;
  /* put vertices of A in */
  asize = polyA.size();
/* begin of old code for CONTAINER == vector 
  for (i=0; i<asize; i++)
    {
      pts_on_A.push_back(polyA[i]);
    }
  pts_on_A.push_back(polyA[0]);
End of old code */
/* begin of new code */
  for (ait = polyA.vertices_begin(); ait != polyA.vertices_end(); ait++)
    {
      pts_on_A.push_back(*ait);
    }
  pts_on_A.push_back(*(polyA.vertices_begin()));
/* end of new code */
  /* add intersection points */
  for (lrit = lresult.begin(); lrit != lresult.end(); lrit++)
    {
      if(CGAL_assign(pt, (*lrit).intersection_object()))
	{
	  /* IT'S A POINT ! */
	  /* treat poly1, i.e. A */
	  if (( (nr_of_poly == 1) && !((*lrit).is_vertex_of_poly1() )) ||
	      ( (nr_of_poly == 2) && !((*lrit).is_vertex_of_poly2() ))   )
	    {
	      if (((*lrit).segments_poly1()).size() > 1) 
		cout << "geometrical error, too many segments" << endl;
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
#ifdef CGAL__INTERSECTING_POLYGONS_DEBUG_ON /* test */
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
#endif /* end test */
		  if((*end2) == edgevertex2)
		    pts_on_A.insert(end2,1,pt);
		  else
		    {
		      added = false;
		      while( (!added) && ((*end1)!=edgevertex2) )
			{
                          // for Wieger: uncomment the suitable line
			  //if (CGAL_collinear_between((*end1),pt,(*end2)))
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

		      if (!added) 
			cout << "error: intersection point not inserted"
			  << " in color list for A" << endl;
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

#ifdef CGAL_INCLUDE_TEMPLATE_CODE
//#include "get_graph_information.C"
//#include "get_color_information.C"
#endif


#endif //  CGAL_INTERSECTING_POLYGONS_H





