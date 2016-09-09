#ifndef __DRAW_MAP_H
#define __DRAW_MAP_H

#ifndef CGAL_CARTESIAN_H
#include <CGAL/Cartesian.h>
#endif
#ifndef CGAL_PM_SEGMENT_EPSILON_TRAITS_H
#include <CGAL/Pm_segment_epsilon_traits.h>
#endif
#ifndef CGAL_PM_DEFAULT_DCEL_H
#include <CGAL/Pm_default_dcel.h>
#endif
#ifndef  CGAL_PLANAR_MAP_2_H
#include <CGAL/Planar_map_2.h>
#endif

#include <CGAL/IO/Window_stream.h>

typedef double                                          number_type; 
typedef CGAL_Cartesian<number_type>                     coord_t;
typedef CGAL_Pm_segment_epsilon_traits<coord_t>         pmtraits;
typedef CGAL_Pm_default_dcel<pmtraits>                  pmdcel;
typedef CGAL_Planar_map_2<pmdcel,pmtraits>              pmmap;

typedef typename pmmap::Halfedge                         pmedge;
typedef typename pmmap::Face                             pmface;
typedef typename pmmap::Ccb_halfedge_circulator          pmccbcirc;

typedef typename pmtraits::Point                         pmpoint;
typedef typename pmtraits::X_curve                       pmcurve; 

void enumerate_all (pmmap &pm);

int draw_pm (pmmap & pm , CGAL_Window_stream & W);

bool Init (char *filename , pmmap & pm) ;

void win_border( double &x0 , double &x1 , double &y0 ,const pmmap &pm);

#endif
