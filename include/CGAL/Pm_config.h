// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Pm_config.h
// package       : pm (3.07)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Oren Nechushtan
//                 Iddo Hanniel
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
/* temporary file, till CGAL_STD,STD_IO rules.*/
#ifndef CGAL_PM_CONFIG_H
#define CGAL_PM_CONFIG_H

#ifndef CGAL_CONFIG_H
#include <CGAL/config.h>
#endif


// handle egcs
#ifdef __GNUC__ //egcs g++ version older then 1.1(1.1 works fine without this)
#define CGAL_TEMPLATE_FRIEND_CLASS_FOR_NESTED_CLASS_BUG
#endif

// handle PC 
#ifdef _MSC_VER
#if _MSC_VER>=1100
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 ) //decorated name length exceeded, name was truncated
#else // (_MSC_VER  < 1100) 
#include <yvals.h>
#endif // (_MSC_VER  < 1100)
#endif // (_MSC_VER)

/*
//#if _MSC_VER>=1100
//#define CGAL_PM_SHORTCUTS
//#endif

//#ifdef __GNUC__ //for egcs++ on Sun long names problem
//#define CGAL_PM_SHORTCUTS
//#endif 

#ifdef  CGAL_PM_SHORTCUTS
// shortcuts ...
// representations
//#define Cartesian	       						_Car_
//#define Homogeneous       						_Hom_
// data structures
#define Pm_DAG									_DAG_
// Traits
//#define Point_2								_P2_
//#define Segment_2								_S2_
#define Planar_map_traits_wrap					_Tw_
#define Pm_segment_epsilon_traits  			_epT_
#define Pm_segment_exact_traits    			_exT_
// Topological map
#define Tpm_halfedge_base						_TpmHb_
#define Tpm_vertex_base						_TpmVb_
#define Tpm_face_base							_TpmFb_			
#define Topological_map						_TPM_
// Dcel
#define Pm_halfedge_base						_PmHb_
#define Pm_vertex_base							_PmVb_
#define Pm_face_base							_PmFb_
#define _Pm_Halfedge							_PmH_
#define _Pm_Vertex								_PmV_
#define _Pm_Face								_PmF_
#define Ccb_halfedge_circulator         			_CCB_
#define Halfedge_around_vertex_circulator          _HAVC_
#define Pm_default_dcel            			_DC2_
// Trapezoidal map
#define __X_trapezoid								_X_t_
#define Trapezoidal_map_2						_TM2_
//#define Locate_type									_Lt_
// Point location
#define Pm_default_point_location  			_PL_

// Planar map
//#define Halfedge		      	       				_He_
#define Planar_map_2      						_PM2_
//#define base_class_iterator							_bit_

#endif //CGAL_PM_SHORTCUTS
*/

#endif // CGAL_PM_CONFIG_H

/* technotes:
1. msvc5 doesn't compile well with min/max macros, 
(Bbox_2.h uses max(int))
2. Portability: These macros are defined in 
win95 <stdlib.h>,<minmax.h>
unix  <stddef.h>
3. template use of min/max is provided through
<algorithm> using the functions _MIN/_MAX
4. CGAL provides a min/max solution in <number_utils.h>
under the names Min,Max
5. The idea of #define <longname> <shortname>
is used already in cgal, see
<CGAL/In_place_list.h> 
#define CGAL__In_place_list_iterator             _Ipli
*/















