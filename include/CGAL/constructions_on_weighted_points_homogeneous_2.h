// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
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
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/constructions_on_weighted_points_homogeneous_2.h
// package       : Triangulation_2 (7.32)
// source        : $RCSfile: constructions_on_weighted_points_homogeneous_2.h,v $
// revision      : $Revision: 1.4 $
// revision_date : $Date: 2000/12/26 09:18:52 $
// author(s)     : Julia Flototto, Mariette Yvinec
//
// coordinator   : Mariette Yvinec 
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CONSTRUCTIONS_ON_WEIGHTED_POINTS_HOMOGENEOUS_2_H
#define CGAL_CONSTRUCTIONS_ON_WEIGHTED_POINTS_HOMOGENEOUS_2_H

CGAL_BEGIN_NAMESPACE

template < class RT, class We>
void
weighted_circumcenterH2( const RT &phx, const RT &phy, const RT &phw, 
			 const We &pwt,
			 const RT &qhx, const RT &qhy, const RT &qhw, 
			 const We &qwt,
			 const RT &rhx, const RT &rhy, const RT &rhw, 
			 const We &rwt,
			 RT &vvx, RT &vvy, RT &vvw )
{

//   RT qx_px = ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
//   RT qy_py = ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
//   RT rx_px = ( rhx*rhw*phw*phw - phx*phw*rhw*rhw );
//   RT ry_py = ( rhy*rhw*phw*phw - phy*phw*rhw*rhw );

//    //intersection of the two radical axis of (qp) and (rp)
//   RT px2_py2_rx2_ry_2 =
//     phx*phx*rhw*rhw + phy*phy*rhw*rhw - rhx*rhx*phw*phw -
//     rhy*rhy*phw*phw - RT(pwt*pwt) + RT(rwt*rwt);
//   RT px2_py2_qx2_qy_2 =
//     phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw -
//     qhy*qhy*phw*phw - RT(pwt*pwt) + RT(qwt*qwt);
  
//   vvx = qy_py * px2_py2_rx2_ry_2 - ry_py * px2_py2_qx2_qy_2;
//   vvy = rx_px * px2_py2_qx2_qy_2 - qx_px * px2_py2_rx2_ry_2;
//   vvw = RT(2) * ( qx_px * ry_py - rx_px * qy_py );

  RT a1, b1, c1;
  RT a2, b2, c2;
  radical_axisH2(phx,phy,phw,pwt,qhx,qhy,qhw,qwt,a1,b1,c1);
  radical_axisH2(phx,phy,phw,pwt,rhx,rhy,rhw,rwt,a2,b2,c2);
  vvx = b1*c2 - c1*b2;
  vvy = c1*a2 - c2*a1;
  vvw = a1*b2 - a2*b1;
}


template < class RT , class We>
void
radical_axisH2(const RT &phx, const RT &phy, const RT &phw, const We &pwt,
	       const RT &qhx, const RT &qhy, const RT &qhw, const We &qwt,
	       RT &a, RT &b, RT &c )
{
//   a = RT(2) * ( qhx*qhw*phw*phw - phx*phw*qhw*qhw );
//   b = RT(2) * ( qhy*qhw*phw*phw - phy*phw*qhw*qhw );
//   c = phx*phx*qhw*qhw + phy*phy*qhw*qhw - qhx*qhx*phw*phw 
//     - qhy*qhy*phw*phw- RT(pwt*pwt) + RT(qwt*qwt); 

  a =  RT(2) * ( phx*phw*qhw*qhw - qhx*qhw*phw*phw );
  b =  RT(2) * ( phy*phw*qhw*qhw - qhy*qhw*phw*phw );
  c = - phx*phx*qhw*qhw - phy*phy*qhw*qhw 
      + qhx*qhx*phw*phw + qhy*qhy*phw*phw 
      + RT(pwt)*phw*phw*qhw*qhw - RT(qwt)*phw*phw*qhw*qhw; 

}




CGAL_END_NAMESPACE
#endif //CGAL_CONSTRUCTIONS_ON_WEIGHTED_POINTS_HOMOGENEOUS_2_H
