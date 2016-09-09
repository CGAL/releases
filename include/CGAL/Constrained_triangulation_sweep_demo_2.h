// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
//
// release       : CGAL-2.2
// release_date  : 2000, September 30
//
// file          : include/CGAL/Constrained_triangulation_sweep_demo_2.h
// package       : Triangulation (4.69)
// source        : $RCSfile: Constrained_triangulation_sweep_demo_2.h,v $
// revision      : $Revision: 1.4 $
// revision_date : $Date: 1999/10/04 09:58:24 $
// author(s)     : Mariette Yvinec
//
// coordinator   : Mariette Yvinec
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONSTRAINED_TRIANGULATION_SWEEP_DEMO_H
#define CGAL_CONSTRAINED_TRIANGULATION_SWEEP_DEMO_H

// #include <CGAL/Constrained_triangulation_traits_2.h>
#include <CGAL/Constrained_triangulation_sweep_2.h>
#include <CGAL/IO/Window_stream.h>

CGAL_BEGIN_NAMESPACE

template < class Gt, class Tds>
class Constrained_triangulation_sweep_demo_2
  : public Constrained_triangulation_sweep_2<Gt,Tds>
{
public:
  typedef typename Gt::Segment Segment;
  typedef Window_stream Window_stream;

  typedef Constrained_triangulation_sweep_2<Gt,Tds> Sweep;
  typedef typename Sweep::Out_edges Out_edges;
  typedef typename Sweep::Event_queue Event_queue;
  typedef typename Sweep::Sweep_status Sweep_status;


Constrained_triangulation_sweep_demo_2() {}

Constrained_triangulation_sweep_demo_2(Window_stream& W,
				       std::list<Constraint>& lc, const Gt& t=Gt())
  : Constrained_triangulation_sweep_2<Gt,Tds>()
  {
    _t = t ; 
    _lc = &lc;
    event_less= Event_less();
    queue = Event_queue(event_less);
    status_comp = Status_comp();
    status= Sweep_status(status_comp);
    upper_chain=Chain();
    make_event_queue();
    demo_build_triangulation(W);
  }



private:
void 
demo_build_triangulation(Window_stream& W);

void 
draw_face(Face_handle f, Window_stream& W)
  {
    for(int i =0; i<3; i++){
      W << Segment((f->vertex(i))->point(), (f->vertex(f->cw(i)))->point());
    }
  return;
  }

void 
draw_new_faces(Vertex_handle v, Window_stream& W)
{
   drawing_mode dm=W.set_mode(leda_src_mode);
   W << BLUE;
   Face_handle f = v->face();
   if (f.is_null()) { return;} //first point, no face
   draw_face(f,W);
   while( ! f->neighbor(1).is_null()) {
     f = f->neighbor(1);
     draw_face(f,W);
   }
}

void 
draw_chain(Chain * pc,Window_stream& W)
{
   Neighbor_list::iterator nit;
   Face_handle f;
   int i;
   nit = (pc->down_list())->begin();
   while (nit != (pc-> down_list())->end()) {
     f = (*nit).first;
     i = (*nit).second;
     W << Segment(f->vertex(f->cw(i))->point(), 
		  f->vertex(f->ccw(i))->point());
     nit++;
   }
   nit = (pc->up_list())->begin();	 
   while (nit != (pc->up_list())->end()) {
     f = (*nit).first;
     i = (*nit).second;
     W << Segment(f->vertex(f->cw(i))->point(), 
		    f->vertex(f->ccw(i))->point());
     nit++;
   }
   return;
}

void 
draw_status_chains(Window_stream& W)
{
  drawing_mode dm=W.set_mode(leda_src_mode);
  W << GREEN;

  Chain * pc;
  typename Sweep_status::iterator status_it=status.begin();
  while ( status_it != status.end()) {
    pc = (Chain *) ((*status_it).second);
    draw_chain(pc,W);
    status_it ++;
  }
  pc = & upper_chain;
  draw_chain(pc,W);
  return;
}
  
void 
draw_constraints(Window_stream& W)
{
  drawing_mode dm=W.set_mode(leda_src_mode);
  W << RED;

  std::list<Constraint>::iterator cit=_lc->begin();
  while(cit != _lc->end()){
    W << Segment((*cit).first,(*cit).second);
    cit++;
  }
  return;
}


void 
draw_next_event(Window_stream& W)
{
  return;
}

void 
any_button(Window_stream& W)
{
  double x, y;
  cerr << "Press any button to continue" << std::endl;
  W.read_mouse(x,y);
}

};


template<class Gt, class Tds>
void
Constrained_triangulation_sweep_demo_2<Gt,Tds>::
demo_build_triangulation(Window_stream& W)
{
  Point p; 
  Vertex_handle v;
  Out_edges * out;
  typename Event_queue::iterator event;
  int count =0;

  while (! queue.empty()) {
    count++;
    event = queue.begin();
             
    // locate (p,p) dans status
    p = (*event).first;
    out = (*event).second;
    typename Sweep_status::iterator loc=status.lower_bound(Constraint(p,p));
    // deal with the contraints finishing at p
    v = treat_in_edges(event,loc);
    // insert constraint beginning at p
    treat_out_edges(event,loc);

    draw_new_faces(v,W);
    draw_constraints(W);
    draw_status_chains(W);
    draw_next_event(W);
    any_button(W);
	
	
    // delete event from event_queue
    out= (*event).second;
    assert( (*out).empty());
    delete out;
    queue.erase(event);
    //delete la liste out
  }
  // make inifinite vertex, infinite faces 
  // at this stage status is empty
  // and the lists of upper_chain correspond to the convex hull
  assert( status.empty());
  the_vertex = set_infinite_faces();

  return;
}

CGAL_END_NAMESPACE


#endif //CONSTRAINED_TRIANGULATION_SWEEP_DEMO_2_H
