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
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/IO/triangulation_Window_stream.h
// package       : Triangulation (2.10)
// source        : web/Triangulation_2.fw
// revision      : $Revision: 1.3.2.2 $
// revision_date : $Date: 1999/01/14 10:56:04 $
// author(s)     : Olivier Devillers
//                 Andreas Fabri
//                 Monique Teillaud
//                 Mariette Yvinec
//
// coordinator   : Herve Bronnimann
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifdef CGAL_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_TRIANGULATION_2_H

template < class Gt, class Tds>
CGAL_Window_stream&
operator<<(CGAL_Window_stream& os,
           const CGAL_Triangulation_2<Gt, Tds> &T)
{
    CGAL_Triangulation_2<Gt, Tds>::Edge_iterator it = T.edges_begin();

    while(it != T.edges_end()){
        os << T.segment(it);
        ++it;
    }

    return os;
}
#endif // CGAL_WINDOW_STREAM_TRIANGULATION_2_H
#endif // CGAL_TRIANGULATION_2_H

#ifdef CGAL_DELAUNAY_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_DELAUNAY_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_DELAUNAY_TRIANGULATION_2_H
template < class Gt, class Tds >
CGAL_Window_stream&
operator<<(CGAL_Window_stream& os,
           const CGAL_Delaunay_triangulation_2<Gt,Tds> &T)
{
  return (os << (CGAL_Triangulation_2<Gt, Tds>) T);
  // c'est pas une bonne idee parceque le cast
  // utilise le createur 
  //CGAL_Triangulation_2(const CGAL_Triangulation_2<Gt,Tds> &tr)
  //qui recopie toute les faces 

//   CGAL_Delaunay_triangulation_2<Gt,Tds>::Edge_iterator it = T.edges_begin();
// 
//     while(it != T.edges_end()){
//         os << T.segment(it);
//         ++it;
//     }
//   
//     return os;
}
#endif // CGAL_WINDOW_STREAM_DELAUNAY_TRIANGULATION_2_H
#endif // CGAL_DELAUNAY_TRIANGULATION_2_H

#ifdef CGAL_CONSTRAINED_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_CONSTRAINED_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_CONSTRAINED_TRIANGULATION_2_H
template < class Gt, class Tds>
CGAL_Window_stream&
operator<<(CGAL_Window_stream& os,
           const CGAL_Constrained_triangulation_2<Gt,Tds> &T)
{

  //return (os << (CGAL_Triangulation_2<Gt, Tds>) T);
  
  CGAL_Constrained_triangulation_2<Gt,Tds>::Edge_iterator it = T.edges_begin();

    while(it != T.edges_end()){
        os << T.segment(it);
        ++it;
    }
   return os;
}

#endif // CGAL_WINDOW_STREAM_CONSTRAINED_TRIANGULATION_2_H
#endif // CGAL_CONSTRAINED_TRIANGULATION_2_H


#ifdef CGAL_WEIGHTED_POINT_2_H
#ifndef CGAL_WINDOW_STREAM_WEIGHTED_POINT_2_H
#define CGAL_WINDOW_STREAM_WEIGHTED_POINT_2_H

template < class Point, class We >
CGAL_Window_stream&
operator<<(CGAL_Window_stream& os,
           const CGAL_Weighted_point_2< Point, We > &p)
{
  double cx = CGAL_to_double(p.point().x()),
         cy = CGAL_to_double(p.point().y()),
         r = CGAL_to_double(p.weight());

  os<<p.point();
  os.draw_circle(cx, cy , /*sqrt*/(r));
  return os;
}

template < class Point, class We >
CGAL_Window_stream& operator>>(CGAL_Window_stream &os,
                               CGAL_Weighted_point_2< Point, We > &wp)
{
  double cx, cy, x1, y1;
  os.read_mouse(cx,cy);
  os.read_mouse_circle(cx,cy, x1, y1);
  Point center(cx, cy);

  We sr = We (sqrt( (cx-x1)*(cx-x1)+(cy-y1)*(cy-y1) ) );

  os.draw_circle(cx, cy , sr );
  wp = CGAL_Weighted_point_2< Point, We >(center, sr);
  return os;
}

#endif // CGAL_WINDOW_STREAM_WEIGHTED_POINT_2_H
#endif // CGAL_WEIGHTED_POINT_2_H





#ifdef CGAL_REGULAR_TRIANGULATION_2_H
#ifndef CGAL_WINDOW_STREAM_REGULAR_TRIANGULATION_2_H
#define CGAL_WINDOW_STREAM_REGULAR_TRIANGULATION_2_H
template < class Gt, class Tds >
CGAL_Window_stream&
operator<<(CGAL_Window_stream& os,
           /*const*/ CGAL_Regular_triangulation_2<Gt,Tds> &T)
{
	CGAL_Regular_triangulation_2<Gt,Tds>::Edge_iterator 
	  it = T.edges_begin();

	while(it != T.edges_end())
	  {	os << CGAL_GREEN<<T.segment(it);
		++it;
	}

	if (T.number_of_vertices()>1 )
	{	
	  CGAL_Regular_triangulation_2<Gt,Tds>::Vertex_iterator 
	    v_i=T.vertices_begin(),
	    done=T.vertices_end();

		while(v_i != done)
		{
			os<< CGAL_RED<<(v_i->point());
			++v_i;
		}
	}else if (T.number_of_vertices()==1)
	{
		os<<CGAL_RED<<T.finite_vertex()->point();
	}

	typedef typename Gt::Point    Point;
	typedef list<Point> Point_list;
	
	if( T.number_of_vertices() < 2) {return os;}

	CGAL_Regular_triangulation_2<Gt,Tds>::Face_iterator fit;
	for(fit=T.faces_begin(); fit != T.faces_end(); ++fit){
	  Point_list::iterator plit;
	 for(plit=fit->point_list().begin(); 
	     plit!=fit->point_list().end(); ++plit) {
	    os<<CGAL_BLUE<< *plit;}
	}

	
	CGAL_Regular_triangulation_2<Gt,Tds>::Face_circulator 
	  fc = T.infinite_vertex()->incident_faces(),done(fc);
	do {
	  Point_list::iterator plit;
	  for(plit=fc->point_list().begin(); 
	     plit!=fc->point_list().end(); ++plit) {
	    os<<CGAL_BLUE<< *plit;}
	}while(++fc != done); 
 
    return os;
}
#endif // CGAL_WINDOW_STREAM_REGULAR_TRIANGULATION_2_H
#endif // CGAL_REGULAR_TRIANGULATION_2_H

