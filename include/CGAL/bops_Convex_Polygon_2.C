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
// file          : include/CGAL/bops_Convex_Polygon_2.C
// package       : bops (1.0.5)
// source        : include/CGAL/bops_Convex_Polygon_2.C
// revision      : $Revision: 1.0.5 $
// revision_date : $Date: Tue Jun 30 19:04:34 MET DST 1998  $
// author(s)     :        Wolfgang Freiseisen
//
// coordinator   : RISC Linz
//  (Wolfgang Freiseisen)
//
// 
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_BOPS_CONVEX_POLYGON_2_C
#define CGAL_BOPS_CONVEX_POLYGON_2_C

#include <CGAL/bops_Convex_Polygon_2.h>

template <class R_type, class Container>
CGAL_Polygon_2<CGAL_Polygon_traits_2<R_type>, Container>
CGAL_Convex_Intersection(
           CGAL_Polygon_2<CGAL_Polygon_traits_2<R_type>, Container> P,
           CGAL_Polygon_2<CGAL_Polygon_traits_2<R_type>, Container> Q
)
{
   typedef CGAL_Polygon_2<CGAL_Polygon_traits_2<R_type>,Container> My_Polygon;
   typedef CGAL_Point_2<R_type> My_Point;
   typedef CGAL_Segment_2<R_type> My_Segment;
   typedef CGAL_Vector_2<R_type> My_Vector;
   typedef typename R_type::FT FT;

   enum tInFlag {unknown, Pin, Qin};  

   int pSize, qSize;                  // size of polygons
   int aAdv, bAdv;                    // number of iterations over each polygon
   My_Point ipoint,targ;              // variables for intersection
   My_Polygon::Vertex_circulator pCir, qCir, pCir1, qCir1;
                                      // circulators over polygons 
   CGAL_Orientation bHA, aHB; // orientation of polygons
   FT cross;         // cross product
   tInFlag inflag;                    // which polygon is inside
   My_Vector aVec, bVec;              // vectors for computation
   My_Segment s1,s2,iseg;             // segments to check intersection
   CGAL_Object result;                // result of intersection of s1 and s2
   list<My_Point> pt_list;            // points forming solution-polynom
   int lastaAdv, lastbAdv;            // variables to avoid endless loop

   //check correct orientation for algorithm
   if (!(P.orientation()==CGAL_COUNTERCLOCKWISE)) P.reverse_orientation();
   if (!(Q.orientation()==CGAL_COUNTERCLOCKWISE)) Q.reverse_orientation(); 

   // initialize variables
   lastaAdv = lastbAdv = 0;
   aAdv = bAdv = 0;
   pSize = P.size(); qSize = Q.size();
   inflag = unknown;
   pCir = pCir1 = P.vertices_circulator ();
   qCir = qCir1 = Q.vertices_circulator ();
   pCir1 = pCir; qCir1 = qCir;
   pCir1--; qCir1--;   

   do
     {
       // create vectors
       aVec = *pCir-*pCir1; bVec=*qCir-*qCir1;
       // calculate 'cross-product'
       cross = aVec[0]*bVec[1]-aVec[1]*bVec[0];
       // get orientation
       bHA = CGAL_orientation(*pCir1, *pCir, *qCir);
       aHB = CGAL_orientation(*qCir1, *qCir, *pCir);
       // create segments for intersection
       CGAL_Segment_2<R_type> s1(*pCir1,*pCir);
       CGAL_Segment_2<R_type> s2(*qCir1,*qCir);
       //check for intersection
       if (CGAL_do_intersect(s1,s2))
	 {
	   // get type of intersection
	   result = CGAL_intersection(s1,s2);
	   // if result is a point, insert in result-polynom
	   if (CGAL_assign(ipoint, result))
	     {
	       // if first intersection start algorithm
	       if (inflag == unknown) aAdv=bAdv=0;
	       if (aHB==CGAL_LEFTTURN) {inflag=Pin;}
	       else if (aHB==CGAL_RIGHTTURN) {inflag=Qin;}
	       else
		 {
       		   // aHB is collinear
		   if (*pCir == *qCir)
		     {
		         //the endpoints of the segments are the same
		         //check which polynom is inside
			 if (CGAL_orientation(*pCir,*(qCir++),*(pCir++))==CGAL_RIGHTTURN) {inflag = Qin;}
			 else
			   {inflag=Pin;}
                         pCir--;qCir--;
		       } // end of pCir==qCir
		   else if (ipoint == *pCir)
		       {
			 //intersection-point is end of P, i.e. it lies on Q 
			 if (CGAL_orientation(ipoint,*(pCir++),*qCir)==CGAL_RIGHTTURN)
			   {inflag=Pin;}
			 else  
                           {inflag = Qin;}
			 pCir--;
		       } // end of ipoint==pCir
		   else    
		       {
                          
			 //point of intersection is end of Q, i.e. it lies on P
                         if (CGAL_orientation(ipoint,*pCir,*(qCir++))==CGAL_LEFTTURN)
			     {inflag=Qin;}
			 else
			     {inflag=Pin;}  
			 qCir--;
		       } // end of default      
		 } //end of else
	       if (!pt_list.empty())
		   {if ((pt_list.back()!=ipoint)&&(pt_list.front()!=ipoint)) pt_list.push_back(ipoint);}
	       else
		 pt_list.push_back(ipoint);

	     } // end of point intersection
	   else
	     {
	       // segment intersection              
               if (CGAL_assign(iseg,result))
		 {
		   // make sure that pCir or qCir is target
                   if ((iseg.source()==*pCir) || (iseg.source()==*qCir))
		     {
		      targ=iseg.source();
                     }
		   else
		     {targ=iseg.target();}
		   // if P and Q have the same endpoint
		   if (*pCir == *qCir)
		     {
		       if (CGAL_orientation(*pCir,*(qCir++),*(pCir++))==CGAL_RIGHTTURN)
		         { inflag = Qin;}
		       else
		         { inflag = Pin;}
		       pCir--;qCir--;
		     } // end of if (*pCir == *qCir)
		   else if (targ==*pCir)
		     {
		       // segment of intersection is on end of P
                       if ((pt_list.back()!=targ)&&(pt_list.front()!=targ)) pt_list.push_back(targ);
		       inflag = Pin;
		     } //end of else if
		   else
		     {
     		       if ((pt_list.back()!=targ)&&(pt_list.front()!=targ)) pt_list.push_back(targ);
		       inflag = Qin;
		     } // end of else
               } //end of segment intersection
	     } //end of else for intersection
	 } //end of intersection
       
       if (cross >= FT(0))
	 {
	   if (bHA == CGAL_LEFTTURN)
 	     {
	       if ((inflag == Pin)&&(pt_list.back()!=*pCir)&&(pt_list.front()!=*pCir)) pt_list.push_back(*pCir);
	       aAdv++; pCir++; pCir1++;
	       // abortion check
	       lastaAdv++; lastbAdv=0;
	     }
	   else
	     { 
	       if ((inflag == Qin)&&(pt_list.back()!=*qCir)&&(pt_list.front()!=*qCir)) pt_list.push_back(*qCir);
	       bAdv++; qCir++; qCir1++;
	       // abortion check
	       lastbAdv++; lastaAdv=0;
	     }
	 }
       else
	 {
	   if (aHB == CGAL_LEFTTURN)
	     {
	       if ((inflag == Qin)&&(pt_list.back()!=*qCir)&&(pt_list.front()!=*qCir)) pt_list.push_back(*qCir);
	       bAdv++; qCir++; qCir1++;
	       // abortion check
	       lastbAdv++; lastaAdv=0;

	     }
	   else
	     {  
	       if ((inflag == Pin)&&(pt_list.back()!=*pCir)&&(pt_list.front()!=*pCir)) pt_list.push_back(*pCir);
	       aAdv++; pCir++; pCir1++;
	       // abortion check
	       lastaAdv++; lastbAdv=0;
	     }
	 }
     } //end of do-loop
   while (((aAdv < pSize) || (bAdv < qSize))&&(lastaAdv <= pSize)&&(lastbAdv<=qSize));
   //create result polygon
   My_Polygon final(pt_list.begin(),pt_list.end());

   if (inflag == unknown)
     {
       //polygons do not intersect
       if (P.bounded_side(*qCir)==CGAL_ON_BOUNDED_SIDE) return Q;
       else if (Q.bounded_side(*pCir)==CGAL_ON_BOUNDED_SIDE) return P;
       else return final;
     }
   else
     {
       return final;
     }
}
 
#endif // CGAL_BOPS_CONVEX_POLYGON_2_C
