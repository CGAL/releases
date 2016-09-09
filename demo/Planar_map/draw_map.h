#ifndef __DRAW_MAP_H
#define __DRAW_MAP_H

#include <CGAL/Cartesian.h>
#include <CGAL/squared_distance_2.h>  
#include <CGAL/Point_2.h>
#include <CGAL/predicates_on_points_2.h>
#include <CGAL/Segment_2.h>

#ifdef USE_RATIONAL
#include <CGAL/Pm_segment_exact_traits.h>
#include <CGAL/leda_rational.h>
#else
#include <CGAL/Pm_segment_epsilon_traits.h>
#endif

#include <CGAL/Pm_default_dcel.h>
#include <CGAL/Planar_map_2.h>

#include <CGAL/IO/Window_stream.h>

//#define CGAL_PM_DEBUG
#ifdef CGAL_PM_DEBUG
#include <CGAL/IO/Planar_map_iostream.h>
#endif

#ifdef PM_TIMER
#include <CGAL/Timer.h>
#endif

#ifdef USE_RATIONAL
typedef leda_rational                          number_type;
#else
typedef double                                 number_type; 
#endif

typedef CGAL::Cartesian<number_type>            Rep;

#ifndef USE_RATIONAL
typedef CGAL::Pm_segment_epsilon_traits<Rep>    Traits;
#else
typedef CGAL::Pm_segment_exact_traits<Rep>      Traits;
#endif

typedef CGAL::Pm_default_dcel<Traits>           Dcel;
typedef CGAL::Planar_map_2<Dcel,Traits>         Planar_map;

typedef Planar_map::Vertex                     Vertex;
typedef Planar_map::Halfedge                   Halfedge;
typedef Planar_map::Face                       Face;

typedef Planar_map::Vertex_handle              Vertex_handle;
typedef Planar_map::Halfedge_handle            Halfedge_handle;
typedef Planar_map::Face_handle                Face_handle;

typedef Planar_map::Vertex_iterator            Vertex_iterator;
typedef Planar_map::Halfedge_iterator          Halfedge_iterator;

typedef Planar_map::Ccb_halfedge_circulator    Ccb_halfedge_circulator;

typedef Traits::Point                          Pm_point;
typedef Traits::X_curve                        Pm_curve; 


// extern "C" to makes VC happy
extern "C" int draw_pm (Planar_map & pm , CGAL::Window_stream & W);

extern "C" bool Init (char *filename , Planar_map & pm) ;

extern "C" void win_border( double &x0 , double &x1 , double &y0 ,
                            Planar_map &pm);

extern "C" CGAL::Window_stream& operator<<(CGAL::Window_stream& os,
                                          Planar_map &M);

extern "C" void window_input(Planar_map & M, CGAL::Window_stream &W );

#ifdef PM_TIMER
extern CGAL::Timer t_total,t_construction,t_insert,t_remove,t_locate,t_vertical;
extern int n_total,n_insert,n_remove,n_locate,n_vertical;
#endif

#endif
















