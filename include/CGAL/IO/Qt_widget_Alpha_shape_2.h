// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// Copyright (c) 2002 ENS de Paris
//
// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// The Qt widget we provide for CGAL is distributed under the QPL,
// which is Trolltech's open source license. For more information see 
//     http://www.trolltech.com/developer/licensing/qpl.html
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_widget_Alpha_shape_2.h
// package       : Qt_widget (1.2.30)
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_QT_WIDGET_ALPHA_SHAPE_2_H
#define CGAL_QT_WIDGET_ALPHA_SHAPE_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Alpha_shape_2.h>
namespace CGAL{

template< class Dt >
Qt_widget&
operator << ( Qt_widget& ws, const CGAL::Alpha_shape_2<Dt>& As)
{
  //return As.op_window(ws);
  typedef typename Alpha_shape_2<Dt>::Alpha_shape_edges_iterator 
                    Edges_iterator;
  typedef typename Alpha_shape_2<Dt>::Segment Segment_2;
  if (As.get_mode() == Alpha_shape_2<Dt>::REGULARIZED) 
  { 
    for (Edges_iterator edge_alpha_it = As.alpha_shape_edges_begin();
         edge_alpha_it != As.alpha_shape_edges_end(); edge_alpha_it++)
    {
      ws << As.segment(*edge_alpha_it);
    }//endfor

  } else {
    for (Edges_iterator edge_alpha_it = As.alpha_shape_edges_begin();
         edge_alpha_it != As.alpha_shape_edges_end(); edge_alpha_it++)
    {
      ws << As.segment(*edge_alpha_it);
    }//endfor
  }
      return ws;
}

}//end namespace CGAL

#endif
