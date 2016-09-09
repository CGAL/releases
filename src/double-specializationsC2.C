//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: double-specializationsC2.C
// Author: Andreas.Fabri@sophia.inria.fr

#include <CGAL/Cartesian.h>
#include <CGAL/Triangle_2.h>
#include <CGAL/Parabola_arc_2.h>
#include <CGAL/Iso_rectangle_2.h>
#include <CGAL/Aff_transformation_2.h>

static void dummy();


static void dummy()
{
  // lets go into recursion to mention this symbol;
  // this avoids a warning from intelligent compilers.

  dummy();

  CGAL_Point_2< CGAL_Cartesian<double> > p;
  CGAL_Vector_2< CGAL_Cartesian<double> > v;
  CGAL_Direction_2< CGAL_Cartesian<double> > d;
  CGAL_Segment_2< CGAL_Cartesian<double> > s;
  CGAL_Ray_2< CGAL_Cartesian<double> > r;
  CGAL_Line_2< CGAL_Cartesian<double> > l;
  CGAL_Parabola_2< CGAL_Cartesian<double> > par;
  CGAL_Parabola_arc_2< CGAL_Cartesian<double> > arc;
  CGAL_Triangle_2< CGAL_Cartesian<double> > t;
  CGAL_Iso_rectangle_2< CGAL_Cartesian<double> > ir;
  CGAL_Aff_transformation_2< CGAL_Cartesian<double> > aff;
  p.x();
  v.x();
  d.dx();
  s.source();
  r.source();
  l.a();
  par.base();
  arc.source();
  t.vertex(0);
  ir.vertex(0);
  aff.is_even();

}


