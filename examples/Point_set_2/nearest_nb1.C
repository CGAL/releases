// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation is part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation is provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.de). 
// - Commercial users may apply for an evaluation license by writing to
//   Algorithmic Solutions (contact@algorithmic-solutions.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.1
// release_date  : 2000, January 11
//
// file          : examples/Point_set_2/nearest_nb1.C
// revision      : 1.1.8
// revision_date : 21 December 1999
// author(s)     : Kurt Mehlhorn, Stefan Naeher, Matthias Baesken
//
// coordinator   :  Matthias Baesken, Halle  (<baesken>)
// email         : cgal@cs.uu.nl
//
// ======================================================================

#include <CGAL/config.h>

#include <list>
#include <vector>

#include <CGAL/Point_set_2.h>
#include <CGAL/leda_rational.h>

using namespace CGAL;
using namespace std;

typedef Cartesian<leda_rational> REP;
typedef point_set_traits_2<REP> TRAITS;
typedef Point_set_2<TRAITS>::Edge    Edge;
typedef Point_set_2<TRAITS>::Vertex  Vertex;

Point_set_2<TRAITS> PSet;

Point_2<REP> ar1[5];

int check1(std::list<Vertex> L)
{
  cout << "check 1!\n";
  if (L.size() != 5) return 1;
  std::list<Vertex>::const_iterator it = L.begin();
  int i=0;
  int w=0;
  
  for(; it != L.end();it++){
    if (ar1[i] != PSet.pos(*it)) w=1;
    i++;
  }
  return w;
}

int main()
{
  std::list<Point_2<REP> > Lr;
  
  int w1,w2;
  
  Point_2<REP> p1(12,14,1);
  Point_2<REP> p2(-12,14,1);  
  Point_2<REP> p3(2,11,1);
  Point_2<REP> p4(5,6,1);
  Point_2<REP> p5(67,38,10);
  Point_2<REP> p6(11,20,1);
  Point_2<REP> p7(-5,6,1);  
  Point_2<REP> p8(12,0,1);
  Point_2<REP> p9(4,31,1);
  Point_2<REP> p10(-10,-10,1); 
  
  Lr.push_back(p1); Lr.push_back(p2); Lr.push_back(p3);
  Lr.push_back(p4); Lr.push_back(p5); Lr.push_back(p6);
  Lr.push_back(p7); Lr.push_back(p8); Lr.push_back(p9);
  Lr.push_back(p10); 
  
  PSet.init(Lr.begin(),Lr.end()); 
  
   // init 
  ar1[0]=p4; ar1[1]=p5; ar1[2]=p3; ar1[3]=p7; ar1[4]=p8; 

  Point_2<REP> actual(30,45,10);

  // nearest neighbor ...  
  Vertex v = PSet.nearest_neighbor(actual);
  cout << "Nearest neighbor:" << PSet.pos(v) << "\n";
  
  if (PSet.pos(v) == p4) w1=0; else w1=1;
  
  // k nearest neighbors ...
  std::list<Vertex> L;
  std::list<Vertex>::const_iterator it;

  PSet.nearest_neighbors(actual,5,back_inserter(L));
  cout << "actual point: " << actual << "\n";
    
  for (it=L.begin();it != L.end(); it++)
      cout << PSet.pos(*it) << "\n";
     
   w2=check1(L);

  if (w1==0 && w2==0) return 0;
  else return 1;
}

