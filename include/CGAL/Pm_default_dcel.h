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
// file          : include/CGAL/Pm_default_dcel.h
// package       : pm (1.12.3)
// source        :
// revision      :
// revision_date :
// author(s)     : Iddo Hanniel
//                 Eyal Flato
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_PM_DEFAULT_DCEL_H
#define CGAL_PM_DEFAULT_DCEL_H


#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_misc.h>
#endif


#include <assert.h>
#ifdef _WIN32
    #if (_MSC_VER  < 1100) 
    #include <list.h>
    #else // (_MSC_VER  < 1100) 
    #include <list>
    //using namespace std;
    #endif // (_MSC_VER  < 1100) 
#else // _WIN32
    #include <list.h>
#endif // _WIN32


template <class Traits>
class CGAL_Pm_default_dcel
{ 
public:
  typedef  CGAL_Planar_map_traits_wrap<Traits> Traits_wrap;
  
  class  Object;
  class  Vertex;
  class  Edge;
  class  Face;

  typedef  typename Traits::X_curve            Curve;
  typedef  typename Traits::Point              Point;


#if (_MSC_VER >= 1100)
    typedef  std::list<Vertex*>         vertices_list;
    typedef  std::list<Edge*>           edges_list;
    typedef  std::list<Face*>           faces_list;
#else
    typedef  list<Vertex*>              vertices_list;
    typedef  list<Edge*>                edges_list;
    typedef  list<Face*>                faces_list;
#endif

  typedef  typename vertices_list::iterator    vertex_iterator;
  typedef  typename edges_list::iterator       edge_iterator;
  typedef  typename faces_list::iterator       face_iterator;

//addition by iddo 22.2
  typedef  typename vertices_list::const_iterator    vertex_const_iterator;
  typedef  typename edges_list::const_iterator       edge_const_iterator;
  typedef  typename faces_list::const_iterator       face_const_iterator;


  typedef enum 
  { NONE_TYPE = 0, VERTEX_TYPE = 1, 
    EDGE_TYPE = 2, FACE_TYPE = 3 }	Object_type;

  /**************************************************************/
  /**************************************************************/
  /********************* O b j e c t ****************************/
  /**************************************************************/
  /**************************************************************/
  class Object
  {
  public:
    Object()
    {
      type = NONE_TYPE;
    }
        
    virtual ~Object() {}

    virtual Object_type get_type() const  
    {
      return type;
    }

  protected:
    Object_type type;
  };


  /**************************************************************/
  /**************************************************************/
  /********************* c c b **********************************/
  /**************************************************************/
  /**************************************************************/
  class ccb
  {
  private:
    bool   is_point_below_curr_edge( Traits  * traits, Vertex  & v )
      // return true if v is below edge. If edge is vertical it
      // returns false.
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      return ( (! edge->target()->is_x_equal( traits, v ) ) 
               &&  (traitsw->curve_get_point_status(edge->get_curve(), 
               v.get_point()) == Traits::UNDER_CURVE)     );
    }

  public:  
    ccb(Edge *e) 
    {
      prev = edge = e;
    }

    void change_ccb(Edge *e) 
    {
      prev = edge = e;
    }
    
    // may change the position
    bool is_on(Edge *e)
    {
      Edge *first = edge;
      do {
        if (e == edge) return true;
      } while (advance() != first);
      
      return false;
    }
    
    // may change the position
    bool is_on(Vertex *v)
    {
      Edge *first = edge;
      do { 
        if (edge->source() == v) 
          return true;
      } while (advance() != first);

      return false;
    }

    //    algorithm: count the intersections of a vertical ray from
    //            v (upward) with the ccb. v is inside iff it is ODD
    //            (may change the position)
    //    precond: v is not ON (the boundary of) this ccb
    bool is_vertex_in(Traits *traits, Vertex *v)
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      int count=0, left, right;
      
      Edge *prev_nv = advance_to_non_vertical_edge(traits);
      if (prev_nv == NULL)
        return false;
    
      Edge *first = edge; // and it is not vertical (first == prev) now
      do {
        if ( is_point_below_curr_edge( traits, *v ) ) 
          { 
            // v is in the range of [source, target)
            // and edge is above v
            
            // if v has the same x as edge->source (& prev->source)
            if ( traitsw->is_x_equal(edge->source()->get_point(), 
                                     v->get_point()) ) 
              {
                // if prev and edge are on the same side of the 
                // vertical line from v - we are staying as before
                // otherwise count one more intersection
                left = right = 0;
                
                if  ( edge->target()->is_x_larger( traits, *v ) )
                  right++;
                else
                  left++;
                
                if  ( prev_nv->source()->is_x_larger( traits, *v ) )
                  right++;
                else
                  left++;
                
                if ( (left == 1) && (right == 1) )
                  count++;
              } 
            else 
              {
                // is this totally unnecessary???
                if (traitsw->curve_get_point_status(edge->get_curve(), v->get_point()) 
                    == Traits::UNDER_CURVE ) 
                  {
                    count++;
                  }
              }
          }
        
        prev_nv = edge;
      } while (advance_to_non_vertical_edge(traits) != first);
      
      return ((count % 2) != 0);
    }
    


    Edge *advance_to_non_vertical_edge(Traits *traits)
      // NULL if this is a vertical ccb
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      advance(); // start checking from the next edge
      
      Edge *first = edge;
      do {
        if ( !traitsw->curve_is_vertical(edge->get_curve()) )
          return edge;
      } while (advance() != first);
      
      return NULL;
    }
        
    // get current edge
    Edge *get_edge() const
    { 
      return edge;
    }

    // get the next edge and change the inner status
    Edge *advance()
    {
      // * next edge on ccb is the closest (cw) edge with its
      // origin == edge->dest and both should have the same face
      // * i suppose that for edge e, e->next is the first(cw)
      // edge with its origin == e.dest
      prev = edge;
      edge = edge->get_next();
      return edge;
    }

    // does not change the position
    Edge *get_succ() const
    { 
      return edge->get_next();
    }
    
    // does not change the position
    Edge *get_prev() const
    { 
      return prev;
    }
    
    // set the f to be the incident face for all edges on this ccb
    void set_face(Face *f)
    {
      Edge *first = edge;
      do {
        edge->set_face(f);
      } while (advance() != first);
    }
    

    ccb &operator++()
    { 
      advance();
      
      return *this;
    }
    
    Edge *operator*() const
    { 
      return edge;
    }
    
    bool operator==(const ccb &c) const
    {
      ccb ccb1(edge);
      
      return ccb1.is_on( c.edge ); /*Sariel??*/
    }

    bool operator==( ccb &c)
    {
      return c.is_on(edge);
    }

    bool is_degenerate(Edge *e)
      //   TRUE if the e->twin is also in this ccb
      //   precondition: e is in the ccb
    {
      if ( (is_on(e)) && (is_on(e->get_twin())) )
        return true;
      else
        return false;
    }
    
    // return (and proceed the ccb) the edge that its 
    // origin or target is the leftmost-lowest in this ccb
    // and the edge is the lowest among the edges incident
    // to this vertex
    Edge *advance_to_lower_left_edge(Traits *traits)
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      Edge *left_edge = edge;
      Point left = edge->source()->get_point();
      bool b;
      
      Edge *first = edge;
      do {
        // source
        b = false;
        if (traitsw->is_x_smaller(edge->source()->get_point(), left)) 
          b = true;
        
        if (traitsw->point_is_same(edge->source()->get_point(), left)) 
          {
            if (traitsw->curve_compare_at_x_right(edge->get_curve(),
                                                  left_edge->get_curve(), left)
                == CGAL_SMALLER) 
              b = true;
            if ( (traitsw->curve_is_vertical(edge->get_curve()))
                &&(traitsw->point_is_lower(edge->target()->get_point(), left)))
              b = true;
          }
        
        if (b) 
          {
            left = edge->source()->get_point();
            left_edge = edge;
          }
        
        
        // target
        b = false;
        if (traitsw->is_x_smaller(edge->target()->get_point(), left)) 
          b = true;
        
        if (traitsw->point_is_same(edge->target()->get_point(), left)) 
          {
            if ((!traitsw->curve_is_vertical(edge->get_curve())) &&
                (!traitsw->curve_is_vertical(left_edge->get_curve())) ) 
              {
                // both are not vertical - there is a reason to compare
                if (traitsw->curve_compare_at_x_right(edge->get_curve(),
                                            left_edge->get_curve(), left) 
                    == CGAL_SMALLER) 
                  b = true;
              }
            
            if ( (traitsw->curve_is_vertical(edge->get_curve())) &&
                 (traitsw->point_is_lower(edge->source()->get_point(),
                                          left)))
              b = true;
          }
        
        if (b) 
          {
            left = edge->target()->get_point();
            left_edge = edge;
          }
      } while (advance() != first);
      
      // if degenerate
      ccb same_ccb(left_edge);
      if (same_ccb.is_degenerate(left_edge)) 
        {
          if (traitsw->point_is_same(left_edge->source()->get_point(), left))
            left_edge = left_edge->get_twin();
        }
      
      return left_edge;
    }
    
    
    bool is_hole(Traits *traits)
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      Edge *e = advance_to_lower_left_edge(traits);
      
      if (traitsw->curve_is_vertical(e->get_curve())) 
        {
          if ( traitsw->point_is_lower(e->source()->get_point(), 
                                       e->target()->get_point()) )
            return true;
          else
            return false;
        }
      
      return  ( ! e->source()->is_x_smaller( traits, *(e->target()) ) );
    }
    
  private:
    Edge *edge;
    Edge *prev;
  };
  
  
  /**************************************************************/
  /**************************************************************/
  /********************* e f v **********************************/
  /**************************************************************/
  /**************************************************************/
  //edges-from-vertex circulator
  class efv   
  {
  public:
    
    efv(Vertex *v)
    { 
      vertex = v;
      edge = v->get_incident_edge();
      advance_cw();
    }
    
    void change_efv(Vertex *v)
    {
      vertex = v;
      edge = v->get_incident_edge();
      advance_cw();
    }
    
    Vertex *get_vertex() const
    { 
      return vertex;
    }
    
    // get current edge
    Edge *get_edge() const
    {
      return edge;
    }
    
    Edge *get_prev() const
    {
      return prev;
    }
    
    // get the next cw edge and change the inner status
    Edge *advance_cw()
    {
      // assuming edge->next is always the closest cw edge
      prev = edge;
      edge = edge->get_twin()->get_next();
      return edge;
    }
    
    efv &operator++()
    {
      advance_cw();
      return *this;
    }
    
    Edge *operator*() const
    { 
      return edge;
    }
    
    bool is_between_cw(Traits *traits, const Curve &cv)
      // TRUE if cv is between prev and edge in cw direction
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      if (prev == edge)
        return true;
      
      return traitsw->curve_is_between_cw( cv, prev->get_curve(), 
                                           edge->get_curve(), 
                                           vertex->get_point());
    }
    
    Edge *find_lowest(Traits *traits, bool highest)
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      Edge *lowest_left = NULL;
      Edge *lowest_right = NULL;
      Edge *first = edge;
      
      int comp_val;
      if (highest)    
        comp_val = CGAL_LARGER; // for finding the highest
			else 
                          comp_val = CGAL_SMALLER; // for finding the lowest
      
      do {
        if ( edge->target()->is_x_smaller( traits, *vertex ) ) 
          {
            if (lowest_left == NULL)
              lowest_left = edge;
            
            if (traitsw->curve_compare_at_x_left(edge->get_curve(),
                                                 lowest_left->get_curve(), 
                                                 vertex->get_point())==comp_val)
              lowest_left = edge;
          }
        
        //        if ( traits->is_x_larger(edge->target()->get_point(), 
        //               vertex->get_point()) ) 
        if  ( edge->target()->is_x_larger( traits, *vertex ) ) 
          {
            if (lowest_right == NULL)
              lowest_right = edge;
            
            if (traitsw->curve_compare_at_x_right(edge->get_curve(),
                                                  lowest_right->get_curve(), 
                                                  vertex->get_point())==comp_val)
              lowest_right = edge;
          }
      } while (advance_cw() != first);
      
      //assert((lowest_left != NULL) || (lowest_right != NULL))
      
      if (lowest_left!= NULL) 
        return lowest_left;
      else 
        return lowest_right;
    }
    
    
    int get_num()
    {
      int n = 0;
      Edge *first = edge;
      do {
        n++;
      } while (advance_cw() != first);
      return n;
    }
    
  private:
    Vertex *vertex;
    Edge *edge, *prev;
  };
  
  
  /**************************************************************/
  /**************************************************************/
  /********************* V e r t e x ****************************/
  /**************************************************************/
  /**************************************************************/
  class Vertex : public  Object
  {
  public:
    Vertex(const Point&  q) : p(q) 
    { 
      type = VERTEX_TYPE;
    }
    
    
    
    Point & get_point() 
    {
      return p;
    }
    
    
    
    typename Traits::Info_vertex &get_info() 
    {
      return info;
    }
  
    void set_info(typename Traits::Info_vertex& i) 
    {
      info = i;
    }
    
    Edge *get_incident_edge() 
    { 
      return incident_edge;
    }
    
    void set_incident_edge(Edge *e) 
    {
            incident_edge = e;
    }
    
    
    Face *find_face_of_curve( Traits *traits, const Curve &cv, 
                              Edge* &edge_before )
    {
      efv vit(this);
      
      while ( !(vit.is_between_cw(traits, cv)) ) 
        {
          vit.advance_cw();
        }
      
      edge_before = vit.get_prev()->get_twin();
      
      return edge_before->get_face();
    }
    
    bool  is_x_smaller( Traits  * traits, const Vertex  & v ) const
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      return  traitsw->is_x_smaller( p, v.p );
    }
    
    bool  is_x_larger( Traits  * traits, const Vertex  & v ) const
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      return  traitsw->is_x_larger( p, v.p );
    }
    
    bool  is_x_equal( Traits  * traits, const Vertex  & v ) const
    {
      Traits_wrap *traitsw = (Traits_wrap *)traits;
      return  traitsw->is_x_equal( p, v.p );
    }
    
  private:
    
    Point p;
    typename Traits::Info_vertex info;
    Edge *incident_edge;
  };
  


  /**************************************************************/
  /**************************************************************/
  /********************* E d g e ********************************/
  /**************************************************************/
  /**************************************************************/
  class Edge : public Object
  {
  public: 
    Edge(const Curve &cv) : curve(cv) //checkout iddo
    { 
      type = EDGE_TYPE;
    }
    
    Curve &get_curve()
    { 
      return curve;
    }
    

    void set_curve(const Curve &cv) 
    {
      curve = cv;
    }
    
    typename Traits::Info_edge &get_info() 
    {
      return info;
    }
    void set_info(typename Traits::Info_edge& i) 
    {
      info = i;
    }
    
    Vertex *source() 
    {
      return origin;
    }
    void set_source(Vertex *o)  
    { 
      origin = o;
    }
    
    Vertex *target() 
    {
      return get_twin()->source();
    }
    
    Edge *get_twin() 
    {
      return twin;
    }
    void set_twin(Edge *t)  
    { 
      twin = t;
    }
    
    Edge *get_next() 
    {
      return next;
    }
    
    void set_next(Edge *n) 
    { 
      next = n;
    }
    
    Face *get_face()
    {
      return face;
    }
    
    void set_face(Face *f)  
    { 
      face = f;
    }
    
    Edge *get_prev()
      // not constant time - O(|CCB(this)|)
    {
      ccb b(this);
      
      while (b.advance() != this);
      
      return b.get_prev();
    }
    
  private:
    
    Curve curve;
    typename Traits::Info_edge info;
    Edge *twin;
    Vertex *origin;
    Edge *next;
    Face *face;
  };
  
    
  /**************************************************************/
  /**************************************************************/
  /********************* F a c e ********************************/
  /**************************************************************/
  /**************************************************************/
  class Face : public Object
  {
  public:
    Face() 
    {
      type = FACE_TYPE;
      outer_ccb_edge = NULL;
    }
    
    typename Traits::Info_face &get_info() 
    {
      return info;
    }
    void set_info(typename Traits::Info_face& i) 
    {
      info = i;
    }
    
    edge_iterator inner_ccb_begin()
    {
      return inner_ccb_edges.begin();
    }
    
    edge_iterator inner_ccb_end()
    {
      return inner_ccb_edges.end();
    }
    
    bool is_outer_ccb( ccb &c) 
    { 
      ccb outer(outer_ccb_edge);
      return (outer == c);
    }
    
    void set_outer_ccb_edge(Edge *e)
    {
      outer_ccb_edge = e;
    }
    
    Edge *get_outer_ccb_edge()
    {
      return outer_ccb_edge;
    }

    void add_inner_ccb_edge(Edge *e)
    {
      inner_ccb_edges.push_back(e);
    }
    
    // removes the inner ccb that contains e (if exist)
    void remove_inner_ccb(Edge *e)
    {
      ccb inner(e);
      ccb c(e);
      // walk on all inner ccbs and find if c equals to one of them
      for  (edge_iterator i = inner_ccb_begin(); i != inner_ccb_end(); ++i) 
        {
          inner.change_ccb(*i);
          if (inner == c) 
            {
              inner_ccb_edges.remove(*i);
              return;
            }
        }
      
      // no inner ccb contains e
    }
    
    bool is_inner_ccb( ccb &c)
    {
      ccb inner(NULL);
      // walk on all inner ccbs and find if c equals to one of them
      for  (edge_iterator i = inner_ccb_begin(); i!= inner_ccb_end(); ++i) 
        {
          inner.change_ccb(*i);
          if (inner == c)
            return true;
        }
      
      return false;
    }
    
  private:
    Edge *outer_ccb_edge;
    edges_list inner_ccb_edges;
    typename Traits::Info_face info;
  };


  /**************************************************************/
  /**************************************************************/
  /********************* D C E L functions **********************/
  /**************************************************************/
  /**************************************************************/


#ifndef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS 

  CGAL_Pm_default_dcel(Traits* t);

  ~CGAL_Pm_default_dcel();

  Vertex* does_vertex_exist(Point& p);

  Edge* is_point_on_edge(Point& p);
  
  Edge* vertical_ray_shoot( const Point &p, bool up );

  Edge* split_edge(Edge *e, Curve& c1, Curve& c2);

  bool delete_vertex(Vertex *vx, Curve cv);

  Edge* insert_in_face_interior(const Curve &cv, Face *f);
  
  Edge* insert_from_vertex(const Curve &cv, Vertex *vx, bool source);
  
  Edge* insert_at_vertices(const Curve &cv, Vertex *vx0, Vertex *vx1);

  Edge* insert(const Curve &cv);
  
  Face *get_unbounded_face();

  void clear();




#else //CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS is defined
//g++ compiler doesn't allow definitions for these functions outside the class!  

  //  CGAL_Dcel_2(Traits *t) 
  CGAL_Pm_default_dcel(Traits* t)
    : vertices(), edges(), faces()
  {
    traits = (Traits_wrap *)t;
    //assert(traits == NULL);
    
    unbounded_face = new Face;
    assert( unbounded_face != NULL );
    
    faces.push_back(unbounded_face);
  }
  
  //  ~CGAL_Dcel_2()
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
  

  Vertex* does_vertex_exist(Point& p)
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
  Edge* is_point_on_edge(Point& p)
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
  
  Edge* vertical_ray_shoot( const Point &p, bool up /*= true*/ )
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
                if ( traits->curve_compare_at_x(closest_edge->get_curve(),
                                                (*it)->get_curve(), p) 
                     == curve_above_under) 
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

  Edge* split_edge(Edge *e, Curve& c1, Curve& c2)
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

  bool delete_vertex(Vertex *vx, Curve cv)
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

  Edge* insert_in_face_interior(const Curve &cv, Face *f)
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
  
  
  Edge* insert_from_vertex(const Curve &cv, Vertex *vx, bool source)
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
  
  
  Edge* insert_at_vertices(const Curve &cv, Vertex *vx0, Vertex *vx1)
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

  Edge* insert(const Curve &cv)
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
  
  
  Face *get_unbounded_face()
  {
    return unbounded_face;
  }
  

  void clear()
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

#endif //CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS



  vertices_list vertices;
  edges_list edges;
  faces_list faces;
  
private:
  Face  *unbounded_face;
  Traits_wrap *traits;
};


#ifndef CGAL_CFG_NO_SCOPE_MEMBER_FUNCTION_PARAMETERS

//#ifdef CGAL_INCLUDE_TEMPLATE_CODE    //changed in version I-06
//#include <CGAL/Pm_default_dcel.C>
//#endif // CGAL_INCLUDE_TEMPLATE_CODE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/Pm_default_dcel.C>
#endif

#endif





#else   //CGAL_PM_DEFAULT_DCEL_H 
#error  Header file Pm_Default_dcel.h included twice
#endif  //CGAL_PM_DEFAULT_DCEL_H

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * Pm_default_dcel.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/









