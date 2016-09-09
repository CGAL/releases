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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/Pm_default_dcel.C
// package       : pm (1.12.3)
// source        :
// revision      :
// revision_date :
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//
// coordinator   : Tel-Aviv University (Dan Halperin)
// chapter       : Planar Map
//
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

/**************************************************************/
/**************************************************************/
/********************* D C E L functions **********************/
/**************************************************************/
/**************************************************************/
#ifndef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS


template <class Traits>
CGAL_Pm_default_dcel<Traits>::
CGAL_Pm_default_dcel(Traits* t)
    : vertices(), edges(), faces()
{
  traits = (Traits_wrap *)t;
  //assert(traits == NULL);
  
  unbounded_face = new Face;
  assert( unbounded_face != NULL );
  
  faces.push_back(unbounded_face);
}
  

template <class Traits>
CGAL_Pm_default_dcel<Traits>::
~CGAL_Pm_default_dcel()
{
  for (face_iterator fi = faces.begin(); fi != faces.end(); ++fi)
    if (*fi != NULL) 
      delete *fi;
  for (edge_iterator ei = edges.begin(); ei != edges.end(); ++ei)
    if (*ei != NULL) 
      delete *ei;
  for (vertex_iterator vi = vertices.begin(); vi != vertices.end(); ++vi)
    if (*vi != NULL) 
      delete *vi;
}

template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Vertex* 
CGAL_Pm_default_dcel<Traits>::
does_vertex_exist(Point& p)
  // returns a vertex pointer if there is a vertex on 
  // the point p, and NULL otherwise
{
  for (vertex_iterator i = vertices.begin();
       i != vertices.end(); ++i)
    if ( traits->point_is_same(p, (*i)->get_point()) ) 
      return (*i);
  
  return NULL;
}  



// precondition: p is not a vertex
template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
is_point_on_edge(Point& p)
{
  for (edge_iterator it = edges.begin(); it != edges.end(); ++it) 
    {
      if ( traits->is_point_on_curve((*it)->get_curve(), p) )  
        {
          return (*it);
        }
    }
  
  return NULL;
}



// ray shoot upwards
// precondition: p is not on an edge or a vertex
// the returned edge is the one that is of p's face ccbs
// NULL if none found
template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
vertical_ray_shoot( const Point &p, bool up /*= true*/ )
{
  Edge *closest_edge = NULL;
  bool first = false;
  typename Traits::Curve_point_status point_above_under;
  int curve_above_under;
  
  // set the flags for comparison acording to the ray 
  // direction (up/down)
  if (up) 
    {
      point_above_under = Traits::UNDER_CURVE;
      curve_above_under = CGAL_LARGER;
    } 
  else 
    {
      point_above_under = Traits::ABOVE_CURVE;
      curve_above_under = CGAL_SMALLER;
    }
  
  for (edge_iterator it = edges.begin(); it != edges.end(); ++it) 
    {
      if ( traits->curve_get_point_status((*it)->get_curve(), p) 
           == point_above_under ) 
        {
          if (!first) 
            {
              closest_edge = (*it);
              first = true;
            } 
          else 
            {
              if ( traits->curve_compare_at_x(
                                              closest_edge->get_curve(),
                                              (*it)->get_curve(), p) == curve_above_under) 
                {
                  closest_edge = (*it);
                }
            }
        }
    }
  
  // if we didn't find any edge above p then it is the empty face
  if (!first)
    return NULL;
  
  // if the closest point is a vertex then find the lowest 
  // edge from this point
  Vertex *v = NULL;
  if ( traits->is_x_equal(closest_edge->source()->get_point(), p) ) 
    {
      v = closest_edge->source();
    }
  
  if ( traits->is_x_equal( closest_edge->target()->get_point(), p) ) 
    {
      v = closest_edge->target();
    }
  
  //if (closest_is_vertex)
  if (v != NULL) 
    {
      efv u(v);
      if (up)    
        closest_edge = u.find_lowest(traits, false);
      else
        closest_edge = u.find_lowest(traits, true);
    }
  
  if (up) 
    {
      // return the edge that is going from right to left
      // such that p is to the left of this edge
      
      //if ( traits->is_x_larger( closest_edge->source()->get_point(),
      //                          closest_edge->target()->get_point()) )
      if  ( closest_edge->source()->is_x_larger( traits, 
                                                 *closest_edge->target() ) )
        return closest_edge;
      else
        return closest_edge->get_twin();
    } 
  else 
    {
      if ( closest_edge->source()->is_x_smaller( traits, 
                                                 *closest_edge->target() ) )
        return  closest_edge;
      else
        return  closest_edge->get_twin();
    }
}  



// c1 is left-low part and c2 the rest
// splits the edge and add a vertex 
// in the splitting point;
// 1 vertex is added
// 2 edges are added
// 0 faces are added
// the edges e and e->twin are changed
template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
split_edge(Edge *e, Curve& c1, Curve& c2)
{
  if (!traits->point_is_left_low(e->source()->get_point(), 
                                 e->target()->get_point()) )
    {
      e = e->get_twin();
    }
  
  Vertex *vn = new Vertex(traits->curve_target(c1));
  assert( vn != NULL );
  
  vn->set_incident_edge(e->get_twin());
  vertices.push_back(vn);
    
  Edge *en0 = new Edge(c2),
    *en1 = new Edge(c2);
  assert( en0 != NULL  &&  en1 != NULL );
  
  edges.push_back(en0);   
  edges.push_back(en1);
  
  if (e->get_next() == e->get_twin()) 
    {
      // special case
      en0->set_source(vn);
      en0->set_next(en1); 
      en0->set_twin(en1);
      en0->set_face(e->get_face());
      
      en1->set_source(e->target());            
      en1->set_next(e->get_twin());            
      en1->set_twin(en0); 
      en1->set_face(e->get_twin()->get_face());
      
      e->target()->set_incident_edge(en1);
      
      e->set_next(en0);
      e->get_twin()->set_source(vn);
      e->set_curve(c1);
      e->get_twin()->set_curve(c1);
    }
  else
    {
      Edge *twin_prev = e->get_twin()->get_prev();
      
      en0->set_source(vn);
      en0->set_next(e->get_next());   
      en0->set_twin(en1);             
      en0->set_face(e->get_face());   
      
      en1->set_source(e->target());            
      en1->set_next(e->get_twin());            
      en1->set_twin(en0);                      
      en1->set_face(e->get_twin()->get_face());
      
      e->target()->set_incident_edge(en1);
      twin_prev->set_next(en1);
        
      e->set_next(en0);
      e->get_twin()->set_source(vn);
      e->set_curve(c1);
      e->get_twin()->set_curve(c1);
    }
    
  return e;
}
  
  
  
  
// assuming vx have exactly TWO neighbours v1 and v2,
// remove vx and let hcv be the new curve between v1 and v2
// after this action pointers to the map will be no longer valid
template <class Traits>
bool
CGAL_Pm_default_dcel<Traits>::
delete_vertex(Vertex *vx, Curve cv)
{
  efv neighbours(vx);
  Edge *e1 = neighbours.get_edge();
  Vertex *v1 = e1->target();
  Edge *e2 = neighbours.advance_cw();
  Vertex *v2 = e2->target();
  Vertex *v3 = neighbours.advance_cw()->target();
  
  // check if vx have exactly two neigbours
  if ((v3 != v1) || (v2 == v1))
    return false;
  
  // check if cv have v1 as endpoint
  if ( !(traits->point_is_same(traits->curve_target(cv), v1->get_point())) &&
       !(traits->point_is_same(traits->curve_source(cv), v1->get_point())) )
    return false;
  
  // check if cv have v2 as endpoint
  if ( !(traits->point_is_same(traits->curve_target(cv), v2->get_point())) &&
       !(traits->point_is_same(traits->curve_source(cv), v2->get_point())) )
    return false;
  
  Edge *e1t = e1->get_twin();
  Edge *e2t = e2->get_twin();
  
  e1t->set_next(e2->get_next());
  e1->set_source(v2);
  v2->set_incident_edge(e1);
  e2t->get_prev()->set_next(e1);
    
  e1->set_curve(cv);
  e1t->set_curve(cv);
    
  //bug fix ( iddo )
  // michal
  // the problem is that when we delete an edge
  // that represents one its neighbor face's out_ccb or inner ccb 
  
    
  Face *f = e2->get_face();
  edge_iterator e_it;
  
  // checking if e2 is on the outer ccb
  if (f->get_outer_ccb_edge() == e2)
    {
      f->set_outer_ccb_edge(e2->get_next());
    }
  
  // checking if e2 is on some inner ccb
  e_it = f->inner_ccb_begin();
  bool flag = true;
  while (flag)
    {
      if (e_it == f->inner_ccb_end())
        flag = false;
      else
        {
          if (*e_it == e2)
            {
              f->remove_inner_ccb(e2);
              f->add_inner_ccb_edge(e2->get_next());
              flag = false;
            }
          else
            ++e_it;
        }
    }
  
  f = e2t->get_face();
  // checking if e2t is the outer ccb
  if (f->get_outer_ccb_edge() == e2t)
    {
      f->set_outer_ccb_edge(e2t->get_next());
    }
  
  // checking if e2t is on some inner ccb
  e_it = f->inner_ccb_begin();
  flag = true;
  while (flag)
    {
      if (e_it == f->inner_ccb_end())
        flag = false;
      else
        {
          if (*e_it == e2t)
            {
              f->remove_inner_ccb(e2t);
              f->add_inner_ccb_edge(e2t->get_next());
              flag = false;
            }
          else
            ++e_it;
        }
    }
  

  // end michal
  // end bug fix    


  edges.remove(e2);
  edges.remove(e2t);
  vertices.remove(vx);
  
  return true;
}



  
// suppose that cv containaed in the interior of f
// (no vertex of cv meets any vertex on the map)
template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
insert_in_face_interior(const Curve &cv, Face *f)
{
  Point p0 = traits->curve_source(cv);
  Point p1 = traits->curve_target(cv);
  
  if (f == NULL) 
    {
      return NULL;
    }
  
  Vertex *v0 = new Vertex(p0), 
    *v1 = new Vertex(p1);
  
  
  assert( v0 != NULL  &&  v1 != NULL );
  
  vertices.push_back(v0);
  vertices.push_back(v1);
  
  Edge *e0 = new Edge(cv),
    *e1 = new Edge(cv);
  assert( e0 != NULL  &&  e1 != NULL );
  
  edges.push_back(e0);
  edges.push_back(e1);
  
  e0->set_source(v0);
  e1->set_source(v1);
  e0->set_next(e1);
  e1->set_next(e0);
  e0->set_twin(e1);
  e1->set_twin(e0);
  e0->set_face(f);
  e1->set_face(f);
    
  v0->set_incident_edge(e0); // e0 has v0 as origin
  v1->set_incident_edge(e1); // e1 has v1 as origin
  
  f->add_inner_ccb_edge(e0);        // cv is now a hole in f
  
  return e0;
}
  
template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
insert_from_vertex(const Curve &cv, Vertex *vx, bool source)
{
  Point p[2];
  p[0] = traits->curve_source(cv);
  p[1] = traits->curve_target(cv);
  
  // the first point (p[0]) will be of the vertex that exist in the map
  
  if (!source)
    swap(p[0],p[1]);
  
  // find the face
  Edge *edge_before;
  Face *fc;
  fc = vx->find_face_of_curve(traits, cv, edge_before);
  // cv is contained in fc and the edge edge_before 
  // is the edge of the boundary of fc that its
  // destination is vertex-vx[0] and is the closest (ccw)
  // to cv
  
  //create new objects
  Vertex *v0 = vx, 
    *v1 = new Vertex(p[1]);
  assert( v1 != NULL );
  vertices.push_back(v1);
  
  Edge *e0 = new Edge(cv),
    *e1 = new Edge(cv);
  assert( e0 != NULL  &&  e1 != NULL );
  
  edges.push_back(e0);
  edges.push_back(e1);
  
  // set new objects data
  // e0 and e1 are now part of a ccb of fc
  e0->set_source(v0);
  e1->set_source(v1);
  e0->set_next(e1);
  e0->set_face(fc);
  e1->set_face(fc);
  e0->set_twin(e1);
  e1->set_twin(e0);
  
  v1->set_incident_edge(e1);
  
  // put e0->next in place on v0
  e1->set_next(edge_before->get_next());
  edge_before->set_next(e0);
  
  return e0;
  
}

template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
insert_at_vertices(const Curve &cv, Vertex *vx0, Vertex *vx1)
  // cv is between the vertices vx0 & vx1
{
  Point p[2];
  Vertex* vx[2];
  Edge *edge_before0, *edge_before1;
  Face *fc;
  
  p[0] = traits->curve_source(cv);
  p[1] = traits->curve_target(cv);
  vx[0]=vx0;
  vx[1]=vx1;
  
  // find the face
  fc = vx[0]->find_face_of_curve(traits, cv, edge_before0);
  vx[1]->find_face_of_curve(traits, cv, edge_before1);
  // cv is contained in fc and the edge edge_before0/1 
  // is the edge of the boundary of fc that its
  // destination is vertex-vx[0/1] and is the closest (ccw)
  // to cv
  
  ccb ccb0(edge_before0), ccb1(edge_before1);
  // both ccb0 and ccb1 are ccbs of fc
  // therefore if a ccb (0/1) is not inner - it is outer.
  
  bool ccb0inner = fc->is_inner_ccb(ccb0), 
    //ccb1inner = fc->is_inner_ccb(ccb1), Sariel : This is not used. why?
    ccbsequal = (ccb0 == ccb1);
  
  Vertex *v0 = vx[0], *v1 = vx[1];
  
  Edge *e0 = new Edge(cv),
    *e1 = new Edge(cv);
  assert( e0 != NULL  &&  e1 != NULL );
  
  // set new objects data
  e0->set_source(v0);
  e1->set_source(v1);
  e0->set_twin(e1);
  e1->set_twin(e0);
  
  // insert e0 and e1 to the appropriate ccbs
  e1->set_next(edge_before0->get_next());
  edge_before0->set_next(e0);
  
  e0->set_next(edge_before1->get_next());
  edge_before1->set_next(e1);
  
  // insert e0 and e1 to the edges list
  edges.push_back(e0);
  edges.push_back(e1);
  
  // Cases: **************************************
  
  // a. ccb0 != ccb1 (==> at least one of them is inner ccb)
  //    no face is added
  if (!ccbsequal)
    {
      // no new face is created
      e0->set_face(fc);
      e1->set_face(fc);
      
      // remove ONE inner ccb from fc
      if (ccb0inner)
        // ccb0 becomes part of ccb1
        fc->remove_inner_ccb(ccb0.get_edge());
      else
        // ccb1 becomes part of ccb0
        fc->remove_inner_ccb(ccb1.get_edge());
      
      return e0 ;
    }
    
  // b. ccb0 == ccb1
    
  // new face is created
  Face *new_face = new Face;
  assert( new_face != NULL );
  
  faces.push_back(new_face);
  
  ccb new_ccb(e0);
    
  // b.1. the ccb is outer
  if (!ccb0inner) 
    {
      // detrmine arbitrarily that e1 is on fc and e0 on new_face
      e1->set_face(fc);
      e0->set_face(new_face);
      
      fc->set_outer_ccb_edge(e1);
      new_face->set_outer_ccb_edge(e0);
      
      // set the face pointer for all e0 ccb 
      new_ccb.change_ccb(e0);
      new_ccb.set_face(new_face);
    } 
  else 
    {
      // b.2. the ccb is inner
      // check if e0 or e1 are in the new face
      // e0 xor e1 are on an hole
      ccb check_hole0(e0);
      if (check_hole0.is_hole(traits)) 
        {
          // e1 is the outer ccb of the new face
          new_face->set_outer_ccb_edge(e1);
          e1->set_face(new_face);
          e0->set_face(fc);
          
          // remove the old ccb we are handleing
          // and insert a new one - all in the outer face - fc
          fc->remove_inner_ccb(e0);
          fc->remove_inner_ccb(e1);
          fc->add_inner_ccb_edge(e0);
          
          // change the face pointer of the edges on the
          // new outer ccb
          new_ccb.change_ccb(e1);
        } 
      else 
        {
          // e0 is the outer ccb of the new face
          new_face->set_outer_ccb_edge(e0);
          e0->set_face(new_face);
          e1->set_face(fc);
          
          // remove the old ccb we are handleing
          // and insert a new one - all in the outer face - fc
          fc->remove_inner_ccb(e0);
          fc->remove_inner_ccb(e1);
          fc->add_inner_ccb_edge(e1);
          
          // change the face pointer of the edges on the
          // new outer ccb
          new_ccb.change_ccb(e0);
        }
        
      new_ccb.set_face(new_face);
    }
  
  // decide which inner ccbs go where (for both b.1 and b.2)
  
  ccb change_face(e0);
  
  // copy inner ccbs from fc to new_face - if necessary
  edge_iterator it;
  for ( it = fc->inner_ccb_begin(); it != fc->inner_ccb_end(); ++it) 
    {
      if ( !(new_ccb.is_on((*it)->source())) ) 
        {
          if ( new_ccb.is_vertex_in(traits, (*it)->source()) ) 
            {
              new_face->add_inner_ccb_edge(*it);
              change_face.change_ccb(*it);
              change_face.set_face(new_face);
            }
        }
    }
  
  // remove ccbs that were copied
  for (it = new_face->inner_ccb_begin();
       it != new_face->inner_ccb_end(); ++it) 
    {
      fc->remove_inner_ccb(*it);
    }
  
  return e0;
}

  
// f should be the face in which cv lies - if
// cv have no own vx in the map
template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Edge* 
CGAL_Pm_default_dcel<Traits>::
insert(const Curve &cv)
{   
  Point p[2];
  p[0] = traits->curve_source(cv);
  p[1] = traits->curve_target(cv);
  
  Vertex* vx[2];
  vx[0] = does_vertex_exist(p[0]);
  vx[1] = does_vertex_exist(p[1]);
  
  // 1. both vertices are not in the map - use f
  //    2 vertices are added
  //    2 edges are added (an edge and its twin)
  //    0 faces are added
  if ((vx[0] == NULL) && (vx[1] == NULL)) 
    {
      Edge *e = vertical_ray_shoot(traits->curve_source(cv), true);
      Face *f;
      Edge*  f_res;
      
      if (e == NULL) 
        f = unbounded_face;
      else 
        f = e->get_face();
      
      f_res = insert_in_face_interior(cv, f);
      
      return  f_res;
    }
  
  // 2. one vertex is in the map and the other is not
  //    1 vertex is added
  //    2 edges are added (an edge and its twin)
  //    0 faces are added
  if (((vx[0] == NULL) && (vx[1] != NULL)) || 
      ((vx[0] != NULL) && (vx[1] == NULL)) ) 
    {
      if (vx[0] != NULL)
        return insert_from_vertex(cv, vx[0], true);
      else
        return insert_from_vertex(cv, vx[1], false);
    }
  
  // 3. both vertices are on the map
  //    0 vertices are added
  //    2 edges are added (an edge and its twin)
  //    0 or 1 face is added
  if ((vx[0] != NULL) && (vx[1] != NULL)) 
    {
      return insert_at_vertices(cv, vx[0], vx[1]);
    }
  return NULL;
}

template <class Traits>
typename CGAL_Pm_default_dcel<Traits>::Face*
CGAL_Pm_default_dcel<Traits>::get_unbounded_face()
{
  return unbounded_face;
}

template <class Traits>
void
CGAL_Pm_default_dcel<Traits>::
clear()
{
  for (face_iterator fi = faces.begin(); fi != faces.end(); ++fi)
    if (*fi != NULL) 
      delete *fi;
  faces.erase(faces.begin(), faces.end());
  

  for (edge_iterator ei = edges.begin(); ei != edges.end(); ++ei)
    if (*ei != NULL) 
      delete *ei;
  edges.erase(edges.begin(), edges.end());
  
  for (vertex_iterator vi = vertices.begin(); vi != vertices.end(); ++vi)
    if (*vi != NULL) 
      delete *vi;
  vertices.erase(vertices.begin(), vertices.end());
  
  
  unbounded_face = new Face;
  assert( unbounded_face != NULL );
    
  faces.push_back(unbounded_face);
    
}


#endif //ifndef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS












