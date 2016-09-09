// ============================================================================
//
// Copyright (c) 1998 The CGAL Consortium
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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ============================================================================
//
// release       : CGAL-1.0
// date          : 21 Apr 1998
//
// file          : include/CGAL/Constrained_triangulation_sweep.h
// author(s)     : Mariette Yvinec
//
// email         : cgal@cs.uu.nl
//
// ============================================================================


#ifndef CGAL_CONSTRAINED_TRIANGULATION_SWEEP_H
#define CGAL_CONSTRAINED_TRIANGULATION_SWEEP_H

#include <pair.h>
#include <list.h>
#include <map.h>
#include <assert.h>

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Constrained_triangulation_traits_2.h>

template < class Tr>
class CGAL_Constrained_triangulation_sweep
{
public:
    typedef Tr  Traits;
    typedef typename Tr::Point Point;
    typedef typename Tr::Segment Segment;
    
    typedef typename Tr::Vertex Vertex;
    typedef typename Tr::Face Face;
    typedef typename Vertex::Vertex_handle Vertex_handle;
    typedef typename Face::Face_handle Face_handle;
    
    typedef pair<Point,Point> Constraint;
    
    class Neighbor_list;
    class Chain;
    class Event_less;
    class Status_comp;
    
    typedef list<Point> Out_edges;
    typedef map<Point,Out_edges *,Event_less> Event_queue;
    typedef map<Constraint,void *, Status_comp> Sweep_status;
    // should be  typedef map<Constraint, Chain *, Status_comp> Sweep_status;
    typedef pair<Face_handle, int> Neighbor;
    
    class Event_less : binary_function<Point, Point, bool>
    {
    private:
      Traits t;
    public:
      Event_less() : t(Traits()) {};
      Event_less(const Traits& traits) : t(traits) {};
      bool operator() (const Point& p, const Point& q)
      {
        return(t.compare_x(p,q)== CGAL_SMALLER ||
               ( t.compare_x(p,q)== CGAL_EQUAL &&
                 t.compare_y(p,q) == CGAL_SMALLER ) );
      }
    };
    
    class Status_comp : binary_function<Constraint, Constraint, bool>
    {
    private:
      Traits t;
    public:
      Status_comp() : t(Traits()) {};
      Status_comp(const Traits& traits) : t(traits){}
      bool operator() (const Constraint& s1, const Constraint& s2)
      {
        Point p1= s1.first;
        Point p2= s2.first;
        Point q1= s1.second;
        Point q2= s2.second;
    
        // one of the constraint is degenerate
        if ( t.compare_x(p1,q1)  == CGAL_EQUAL &&
             t.compare_y(p1,q1)  == CGAL_EQUAL) {
          // p1==q1, then p2 has to be != q2
          // if p1==p2 or p1==q2 return true
          if ( t.compare_x(p1,p2)  == CGAL_EQUAL &&
               t.compare_y(p1,p2) == CGAL_EQUAL) {return true;}
          if ( t.compare_x(p1,q2)  == CGAL_EQUAL &&
               t.compare_y(p1,q2) == CGAL_EQUAL ) {return true;}
          // for vertical constraint (p2,q2)
          if  (t.compare_x(p2,q2) == CGAL_EQUAL) {
            return (t.compare_y(p1,p2) == CGAL_SMALLER);}
          // default case
          return( t.orientation(p2,q2,p1) == CGAL_RIGHTTURN);
        }
    
        else if ( t.compare_x(p2,q2) == CGAL_EQUAL &&
                  t.compare_y(p2,q2) == CGAL_EQUAL) {
          // p2==q2 && p1!=q1
          // if p2==p1 or p2==q1 return false
          if ( t.compare_x(p2,p1)  == CGAL_EQUAL &&
               t.compare_y(p2,p1)  == CGAL_EQUAL) {return false;}
          if ( t.compare_x(p2,q1)  == CGAL_EQUAL &&
               t.compare_y(p2,q1)  == CGAL_EQUAL) {return false;}
          //for vertical (p1,q1) constraints
          if (t.compare_x(p1,q1) == CGAL_EQUAL) {
            return ( t.compare_y(p1,p2) == CGAL_SMALLER);}
          // default case
          return (t.orientation(p1,q1,q2) == CGAL_LEFTTURN);
        }
    
        // comparison of two non degenerate constraints
        else {
          //neither of the constraints are points
          switch( t.compare_x(p1,p2)) {
          case CGAL_SMALLER:
            if ( t.compare_x(q1,p2)  == CGAL_EQUAL &&
                 t.compare_y(q1,p2)  == CGAL_EQUAL) {return true;}
            else return ( t.orientation(p1,q1,p2) == CGAL_LEFTTURN);
          case CGAL_LARGER :
            if ( t.compare_x(p1,q2)  == CGAL_EQUAL &&
                 t.compare_y(p1,q2)  == CGAL_EQUAL) {return false;}
            else return ( t.orientation(p2,q2,p1) == CGAL_RIGHTTURN);
          case CGAL_EQUAL :
            return ( t.compare_y(p1,p2) == CGAL_SMALLER ||
                     (t.compare_y(p1,p2) == CGAL_EQUAL &&
                      t.orientation(p1,q1,q2) == CGAL_LEFTTURN));
          }
        }
      }
    };
    
    class Neighbor_list : public list<Neighbor>
    {
    public:
      Face_handle up_visit_without_test(Vertex_handle v, Face_handle last)
      {
        Face_handle newf;
        Face_handle fn; int in;
        while( !empty()){
          fn= front().first;
          in= front().second;
          pop_front();
          newf = (new Face(v,fn->vertex(fn->cw(in)),
                           fn->vertex(fn->ccw(in))))->handle();
          last->set_neighbor(2,newf); newf->set_neighbor(1,last);
          fn->set_neighbor(in, newf); newf->set_neighbor(0,fn);
          newf->set_constrained(1, last->is_constrained(2));
          newf->set_constrained(0, fn->is_constrained(in));
          // delete fn if flat and removable
          if (fn->is_removable()) { fn->remove_flat(); fn.Delete(); }
          last=newf;
        }
        return last;
      }
    
      Face_handle up_visit( Vertex_handle v, Face_handle last)
      {
        Traits t=Traits();
        Face_handle newf;
        Face_handle fn; int in;
        Vertex_handle cwin; Vertex_handle ccwin;
        while (!empty()) {
          fn= front().first;
          in= front().second;
          cwin = fn->vertex(fn->cw(in));
          ccwin = fn->vertex(fn->ccw(in));
          if ( t.orientation(ccwin->point(),cwin->point(),v->point()) ==
               CGAL_RIGHTTURN) {
            pop_front();
            newf = (new Face(v,cwin,ccwin))->handle();
            last->set_neighbor(2,newf); newf->set_neighbor(1,last);
            fn->set_neighbor(in, newf); newf->set_neighbor(0,fn);
            newf->set_constrained(1, last->is_constrained(2));
            newf->set_constrained(0, fn->is_constrained(in));
            // delete fn if flat and removable
            if (fn->is_removable()) { fn->remove_flat(); fn.Delete(); }
            last=newf;
          }
          else{break;}
        }
        return last;
      }
    
      Face_handle down_visit(Vertex_handle v, Face_handle first)
      {
        Traits t=Traits();
        Face_handle newf;
        Face_handle fn; int in;
        Vertex_handle cwin; Vertex_handle ccwin;
        while (!empty()) {
          fn= back().first;
          in= back().second;
          cwin = fn->vertex(fn->cw(in));
          ccwin = fn->vertex(fn->ccw(in));
          if ( t.orientation(ccwin->point(),cwin->point(),v->point()) ==
                                          CGAL_RIGHTTURN) {
            pop_back();
            newf = (new Face(v,cwin,ccwin))->handle();
            first->set_neighbor(1,newf); newf->set_neighbor(2,first);
            fn->set_neighbor(in, newf); newf->set_neighbor(0,fn);
            newf->set_constrained(2, first->is_constrained(1));
            newf->set_constrained(0, fn->is_constrained(in));
            // delete fn if flat and removable
            if (fn->is_removable()) { fn->remove_flat(); fn.Delete(); }
            first=newf;
          }
          else{break;}
        }
        return first;
      }
    
    };
    
    class Chain
    {
    private:
      Vertex_handle rm;
      Neighbor_list up;
      Neighbor_list down;
    
    public:
      Chain() : rm(NULL), up(), down() {}
      Vertex_handle right_most() { return rm;}
      Neighbor_list* up_list(){return &up;}
      Neighbor_list* down_list(){return &down;}
      void set_right_most(Vertex_handle v) { rm=v;}
    };
    
    CGAL_Constrained_triangulation_sweep( Tr& t = Tr())
      : _t(t), _lc(NULL)
    {
    }
    
    CGAL_Constrained_triangulation_sweep( list<Constraint>& lc,
                                               Tr& t = Tr())
      : _t(t), _lc(&lc)
    {
      event_less= Event_less(_t);
      queue = Event_queue(event_less);
      status_comp = Status_comp(_t);
      status= Sweep_status(status_comp);
      upper_chain=Chain();
      make_event_queue();
      build_triangulation();
    }
    Traits  traits() { return _t; }
    Event_less  xy_less() {return event_less;}
    Vertex_handle vertex() {return the_vertex; }
    

    // friend class Chain;
    // friend class Event_less;
    // friend class Status_comp;
    friend class Neighbor_list;

protected:
    Traits _t;
    list<Constraint>* _lc;
    Event_less event_less;
    Event_queue queue;
    Status_comp status_comp;
    Sweep_status status;
    Chain upper_chain;
    Vertex_handle the_vertex;
    

public:
    void make_event_queue();
    void build_triangulation();
    Vertex_handle treat_in_edges(const Event_queue::iterator & event,
                                 Sweep_status::iterator & loc);
    void treat_out_edges(const Event_queue::iterator & event,
                         Sweep_status::iterator & loc);
    Vertex_handle set_infinite_faces();
    // bool is_removable(Face_handle f); // put into class Face
    // void remove_flat(Face_handle f);  // put into class Face
    bool do_intersect(const Constraint& c1, const Constraint& c2 );
    
};


template<class Tr>
void
CGAL_Constrained_triangulation_sweep<Tr>::
make_event_queue()
{
  if ( ! queue.empty()) {return;} // queue already done
  list<Constraint>::iterator sit=_lc->begin();
  list<Constraint>::iterator sdone=_lc->end();
  Constraint s;
  Point p,q;
  Event_queue::iterator look_up;
    while (sit != sdone) {
      s=*sit++;
      if (event_less(s.first,s.second)) { p=s.first; q = s.second;}
      else { p=s.second; q = s.first;}
      // p is xy_less or equal to q
      look_up = queue.lower_bound(p);
      if (look_up == queue.end() ||
          event_less(p,(*look_up).first) ) {
        // the event p does not yet exists
        Out_edges* out= new Out_edges();
        Event_queue::value_type event(p,out);
        look_up=queue.insert(look_up,event);
      }

      if(event_less(p,q)) {
        ((*look_up).second)->push_front(q); //insert q in out_edges(p);
        // Degenerate constraints (p==q) are not inserted in Out_egdes list.
        // A duplicate constraint
        // will be inserted twice in the Out_egdes list of its first
        // point. The second copy will be discarded when
        // insertion in status takes place

        look_up = queue.lower_bound(q);
        if (look_up == queue.end() ||
           event_less(q,(*look_up).first)){
        // the event q does not yet exists
        Out_edges* out= new Out_edges();
        Event_queue::value_type  event(q,out);
        look_up=queue.insert(look_up,event);
        }
      }
    }
    return;
}

template<class Tr>
void
CGAL_Constrained_triangulation_sweep<Tr>::
build_triangulation()
{
  Point p;
  Vertex_handle v;
  Out_edges* out;
  Event_queue::iterator event;
   while (! queue.empty()) {
        event = queue.begin();

    // locate (p,p) dans status
    p = (*event).first;
    out = (*event).second;
    Sweep_status::iterator loc=status.lower_bound(Constraint(p,p));
    // deal with the contraints finishing at p
    v = treat_in_edges(event,loc);
    // insert constraint beginning at p
    treat_out_edges(event,loc);

    // delete event from event_queue
    out= (*event).second;
    assert( (*out).empty());
    delete out; //delete la liste out
    queue.erase(event);

  }
  // make inifinite vertex, infinite faces
  // at this stage status is empty
  // and the lists of upper_chain correspond to the convex hull
  assert( status.empty());
  the_vertex = set_infinite_faces();
  return;
}

template<class Tr>
CGAL_Constrained_triangulation_sweep<Tr>::Vertex_handle
CGAL_Constrained_triangulation_sweep<Tr>::
treat_in_edges(const Event_queue::iterator & event,
               Sweep_status::iterator & loc)
{
  // loc is assumed to point to the first constraint in status
  // not less than [p,p];
  Vertex_handle  v = (new Vertex((*event).first))->handle();
  Chain* pch;
  Sweep_status::iterator loc_start=loc;

  if (loc == status.end()) { pch = &upper_chain;}
  else { pch = (Chain*)((*loc).second);}
  Vertex_handle w = pch->right_most();
  if (w==NULL) { // first event is treated
    pch->set_right_most(v);
    return v;
  }
  Face_handle newf= (new Face(v,w,w))->handle();
  // test if the edge vw is a constraint
  // this is not possible if loc == status.end()
  if ( loc != status.end() &&
       w->point() == ((*loc).first).first  &&
       v->point() == ((*loc).first).second ) {
    // vw is a constraint
    newf->set_constrained(true,true,true);
  }
  Neighbor_list* nl = pch->down_list();
  Face_handle first;
  first= nl->down_visit(v,newf);

  Face_handle last = newf;
  while( loc!= status.end() && ((*event).first == ((*loc).first).second ) ) {
  nl= pch->up_list();
  last = nl->up_visit_without_test(v,last);
  last->set_constrained(2,true);
  loc++;
  if (loc == status.end()) { pch = &upper_chain;}
  else { pch = (Chain *)((*loc).second);}
  nl= pch->down_list();
  last = nl->up_visit_without_test(v,last);
  }

  nl=pch->up_list();
  last= nl->up_visit(v,last);

  //delete flat newf if possible
  // i. e. if at least one of its neighbor is not NULL
  if (newf->neighbor(2) != NULL || newf->neighbor(1) != NULL) {
    if (first == newf ) { // means newf->neighbor(1) == NULL
       first  = newf->neighbor(2);}
    if (last == newf) { // means newf->neighbor(2) == NULL
      last = newf->neighbor(1);}
    newf->remove_flat(); newf.Delete();
  }

  // set face pointer of vertex v.
  // if no face is created except the flat one
  // the pointer is set to this face.
  // Thus the face pointer of f->vertex(0)  has to be reset
  //  when the flat face f is removed through f->remove_flat()
  v->set_face(last);

  // update the chain of loc and status;
  //update the up list of *loc
  nl->push_front(Neighbor(last,2));
  pch->set_right_most(v);
  // update the down list of *loc
  // splicing in the remaining downlist of *loc_start
  // then adding Neighbor(first,1)
  nl = pch->down_list();
  if (loc_start != loc) {
    pch = (Chain *)((*loc_start).second);
    nl->splice(nl->end(), *(pch->down_list()));
  }
  nl->push_back(Neighbor(first,1));
  //update status
  while (loc_start != loc) {
     pch = (Chain *)((*loc_start).second);
     delete pch;
     status.erase(loc_start++);
   }

  // test for intersection the newly adjacent constraints
  if(loc_start != status.end() && loc_start != status.begin()){
    CGAL_triangulation_assertion( ! do_intersect( (*loc_start).first,
                                                (*(--loc_start)).first ) );
  }

 return v;
}

template<class Tr>
void
CGAL_Constrained_triangulation_sweep<Tr>::
treat_out_edges(const Event_queue::iterator & event,
                Sweep_status::iterator & loc)
{
  Point p = (*event).first;
  Out_edges* out = (*event).second;
  Out_edges::iterator outit= (*out).begin();
  Chain* newpc;
  Chain* pc_up;
  Constraint c;

  const Constraint* c_plus=NULL;
  const Constraint* c_minus=NULL;
  if(loc != status.end()) {  c_plus= &((*loc).first);}
  if(loc != status.begin()) {c_minus = &((*(--loc)).first); ++loc;}
  // c_plus  points  to the constraint in status following
  // the last constraint through  p if there is one.
  // c_minus points  to the constraint in status preceeding
  // the first constraint through p if there is one.
  // These two constraints are to be tested for intersection
  // when inserting the constraint through p;

  if (loc == status.end()) {pc_up = & upper_chain;}
  else {   pc_up = (Chain*)((*loc).second);}
  Vertex_handle v = pc_up->right_most();
  //assert (v->point() == p);
  //c= Constraint(p,p);
  //Sweep_status::iterator loc_bis = status.lower_bound(Constraint(p,p));
  //assert( loc == loc_bis);

  while( outit != (*out).end()){
    c = Constraint(p,*outit);
    // test for intersection
    if (c_plus != NULL){
      CGAL_triangulation_assertion( ! do_intersect( (*c_plus), c));
    }
    if (c_minus != NULL){
      CGAL_triangulation_assertion( ! do_intersect( (*c_minus), c));
    }
    //insert
    // if the constraint of *out are sorted (with out_comp())
    // loc should be always equal to status.lower_bound(c)
    // and  status-insert should be constant time
    newpc = new Chain;
    newpc->set_right_most(v);
    loc = status.insert(loc,
                        pair<const Constraint, void*>(c, (void*)newpc ));
    loc++;
    if (loc == status.end()) {pc_up = & upper_chain;}
    else {   pc_up = (Chain*)((*loc).second);}
    (newpc->down_list())->splice((newpc->down_list())->end(),
                                 *(pc_up->down_list()) );
    (*out).erase(outit++);
    }
  return;
}

template<class Tr>
CGAL_Constrained_triangulation_sweep<Tr>::Vertex_handle
CGAL_Constrained_triangulation_sweep<Tr>::
set_infinite_faces()
{
  Vertex_handle infinite= (new Vertex)->handle();
  // Triangulation may be empty;
  if (upper_chain.right_most() == NULL) {return(infinite);}

  Neighbor_list* upper_list= upper_chain.up_list();
  Neighbor_list* lower_list= upper_chain.down_list();
//Triangulation may have only one vertex
  if (upper_list->empty() || lower_list->empty()) {return upper_chain.right_most();}

//Triangulation has now at least two vertices
  lower_list->splice(lower_list->end(), *upper_list);
  // * lower_list now describes the convex-hull ccw
  Face_handle first, last;
  Face_handle newf, fn;
  int in;

  fn = (*(lower_list->begin())).first;
  in = (*(lower_list->begin())).second;
  lower_list->pop_front();
  newf = (new Face( infinite, fn->vertex(fn->cw(in)),
                   fn->vertex(fn->ccw(in))))->handle();
  fn->set_neighbor(in,newf); newf->set_neighbor(0,fn);
  newf->set_constrained(0, fn->is_constrained(in));
  if (fn->is_removable()) { fn->remove_flat(); fn.Delete(); }
  first = last = newf;

  while ( ! lower_list->empty()){
    fn =(* (lower_list->begin())).first;
    in =(* (lower_list->begin())).second;
    lower_list->pop_front();
    newf= (new Face( infinite, fn->vertex(fn->cw(in)),
                    fn->vertex(fn->ccw(in))))->handle();
    fn->set_neighbor(in,newf); newf->set_neighbor(0,fn);
    last->set_neighbor(2,newf);newf->set_neighbor(1,last);
    newf->set_constrained(0, fn->is_constrained(in));
    if (fn->is_removable()) { fn->remove_flat(); fn.Delete(); }
    (newf->vertex(2))->set_face(newf->neighbor(0));
    last=newf;
  }
  last->set_neighbor(2,first);first->set_neighbor(1,last);
  (first->vertex(2))->set_face(first->neighbor(0)); //cannot be done before
  infinite->set_face(last);
  return(infinite);
}


template<class Tr>
bool
CGAL_Constrained_triangulation_sweep<Tr>::
do_intersect(const Constraint& c1, const Constraint& c2 )
{
  // The constraints are known to be  non degenerate
  // ordered (c.first Lexicographic less than c.second)
  // and to span some common y-value.
  // They do not have the same first point but they can share the same
  // endpoint.
   if ( (!event_less(c1.second, c2.second)) &&
        (!event_less(c2.second, c1.second)) ) {return false;}
   else{
   CGAL_Orientation t1 = _t.orientation(c1.first,c1.second,c2.first);
   CGAL_Orientation t2 = _t.orientation(c1.first,c1.second,c2.second);
   if (t1 == CGAL_COLLINEAR && t2 == CGAL_COLLINEAR) {return true;}

    return ( t1 != t2 &&
             (_t.orientation(c2.first,c2.second,c1.first) !=
              _t.orientation(c2.first,c2.second,c1.second)));
  }
    return false;
}


#endif //CGAL_CONSTRAINED_TRIANGULATION_SWEEP_H

