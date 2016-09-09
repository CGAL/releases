// Copyright (c) 2006 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Apollonius_graph_2/include/CGAL/Apollonius_graph_2/Delage_traits/Orientation_2.h $
// $Id: Orientation_2.h 44317 2008-07-22 12:29:01Z spion $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@tem.uoc.gr>
//                 Christophe Delage <Christophe.Delage@sophia.inria.fr>
//                 David Millman <dlm336@cs.nyu.edu>

#ifndef CGAL_APOLLONIUS_GRAPH_2_ORIENTATION_NEW_2_H
#define CGAL_APOLLONIUS_GRAPH_2_ORIENTATION_NEW_2_H


#include <CGAL/Apollonius_graph_2/Orientation_2.h>

CGAL_BEGIN_NAMESPACE

CGAL_APOLLONIUS_GRAPH_2_BEGIN_NAMESPACE


template <class K, class MTag>
class Orientation_new_2 : public Orientation_2<K, MTag>
{
private:
  typedef Orientation_2<K, MTag>       Base;
public:
  typedef K                            Kernel;
  typedef typename K::RT               RT;
  typedef typename K::Site_2           Site_2;
  typedef typename K::Point_2          Point_2;

  typedef typename Base::Orientation   Orientation;
  typedef Orientation                  result_type;
  typedef Site_2                       argument_type;

    Orientation operator() (const Site_2 &s0, const Site_2 &s1,
			    const Site_2 &s2, const Point_2 &q) const
    {
      RT x1 = s1.x() - s0.x();
      RT y1 = s1.y() - s0.y();
      RT w1 = s1.weight() - s0.weight();

      RT x2 = s2.x() - s0.x();
      RT y2 = s2.y() - s0.y();
      RT w2 = s2.weight() - s0.weight();

      RT xq =  q.x() - s0.x();
      RT yq =  q.y() - s0.y();

      RT a1 = CGAL::square(x1) + CGAL::square(y1) - CGAL::square(w1);
      RT a2 = CGAL::square(x2) + CGAL::square(y2) - CGAL::square(w2);
        
      CGAL_assertion (CGAL::sign(a1) == POSITIVE);
      CGAL_assertion (CGAL::sign(a2) == POSITIVE);

      RT x = a1 * x2 - a2 * x1;
      RT y = a1 * y2 - a2 * y1;
      RT w = a1 * w2 - a2 * w1;
      RT s = x * xq + y * yq;

      Sign W = CGAL::sign (w);
      Sign S = CGAL::sign (s);

      if (W == ZERO) { return -S; }

      RT o = x * yq - y * xq;
        
      Sign O = CGAL::sign(o);

      if (S == 0) { return O * W; }
	
      if (W * S * O != POSITIVE) { return -S; }

      RT i = CGAL::square(w) * (CGAL::square(xq) + CGAL::square(yq))
	- CGAL::square(s);

      Sign I = CGAL::sign(i);
        
      return S * I;
    }
};

CGAL_APOLLONIUS_GRAPH_2_END_NAMESPACE

CGAL_END_NAMESPACE

#endif // CGAL_APOLLONIUS_GRAPH_2_ORIENTATION_NEW_2_H
