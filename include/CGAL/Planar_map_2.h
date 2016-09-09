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
// file          : include/CGAL/Planar_map_2.h
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
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef  CGAL_PLANAR_MAP_2_H
#define  CGAL_PLANAR_MAP_2_H

#ifndef   CGAL_PLANAR_MAP_MISC_H
        #include  <CGAL/Planar_map_misc.h>
#endif 


template <class Dcel ,class Traits>
class CGAL_Planar_map_2
{
public:
  
  typedef CGAL_Pm_default_dcel<Traits>				ddcel;
  //  typedef Dcel          ddcel;

  typedef typename ddcel::efv					defv;
  typedef typename ddcel::ccb					dccb;
  typedef typename ddcel::Object				dobject;
  typedef typename ddcel::Vertex				dvertex;
  typedef typename ddcel::Edge					dedge;
  typedef typename ddcel::Face					dface;
  
  typedef typename ddcel::Object_type			        Object_type;


  class Vertex;
  class Halfedge;
  class Face;
  class Ccb_halfedge_circulator;
  class Halfedge_around_vertex_circulator;
  
  
	
  // Traits_wrap is the extended interface class we use...
  typedef CGAL_Planar_map_traits_wrap<Traits>			Traits_wrap; 
  
  // map features iterators
  typedef base_class_iterator<typename ddcel::vertex_iterator, Vertex>  
    Vertex_iterator;
  
  typedef base_class_iterator<typename ddcel::edge_iterator, Halfedge>  
    Halfedge_iterator;
  
  typedef base_class_iterator</*typename*/ ddcel::face_iterator, Face>      
    Face_iterator;

  typedef base_class_iterator<typename ddcel::edge_iterator,
                              Ccb_halfedge_circulator> Holes_iterator;




  typedef enum { VERTEX = 1 , EDGE , FACE , UNBOUNDED_FACE } Locate_type ; 
  
 
  /**************************************************************/
  /**************************************************************/
  /********************* V e r t e x ****************************/
  /**************************************************************/
  /**************************************************************/
  class Vertex 
  {
  public:
    Vertex()
    {}
    
    Vertex(dvertex *v) 
    {
      dv=v;
    }
    
    Vertex(const Vertex &v)
    {
      dv=v.dv;
    }
    
    Vertex &operator=(const Vertex &v)
    { 
      dv = v.dv; 
      return *this; 
    }
    
    bool operator==(const Vertex &v) const
    {
      return dv == v.dv; 
    }
    
    //in some compilers this isn't defined automatically
    bool operator!=(const Vertex &v) const
    {
      return !(*this==v); 
    }
    
    bool is_null()
    {
      return (dv==NULL);
    }
    
    
    
    typename Traits::Point& point() const
    { 
      return dv->get_point(); 
    }
    
    
    
    typename Traits::Info_vertex & info() const
    { 
      return dv->get_info(); 
    }
    
    void set_info(typename Traits::Info_vertex &i)
    { 
      dv->set_info(i); 
    }
    
    bool is_incident_edge(const Halfedge &e) const
    {
      return (e.source() == *this) || (e.target() == *this);
    }
    
    bool is_incident_face(Face f) const
    {
      Halfedge_around_vertex_circulator ec(dv);
      Halfedge_around_vertex_circulator start = ec;
      do {
        if ((*ec).face() == f)
          return true;
        ++ec;
      } while (ec != start);
      
      return false;
    }
    
    int degree() const
    {
      defv e(dv);
      return e.get_num();
    }
    
    Halfedge_around_vertex_circulator incident_halfedges() const
    {
      return Halfedge_around_vertex_circulator(dv); 
    }
    
    const dvertex* get_dvertex() const
    {
      return dv;
    }
    
  protected:
    dvertex *dv;
    
  };
  
  /**************************************************************/
  /**************************************************************/
  /********************* E d g e ********************************/
  /**************************************************************/
  /**************************************************************/
  class Halfedge 
  {
  public:
    Halfedge()
    {}
    
    Halfedge(dedge *e)
    {
      de=e;
    }
    
    Halfedge(const Halfedge &e)
    {
      de=e.de;
    }
    
    
    Halfedge &operator=(const Halfedge &e)
    { 
      de = e.de; 
      return *this;
    }
    
    bool operator==(const Halfedge &e) const
    {
      return de == e.de; 
    }
    
    bool operator!=(const Halfedge &e) const
    {
      return !(*this==e); 
    }
    
    bool is_null()
    {
      return (de==NULL);
    }
    
    const typename Traits::X_curve &curve() const
    { 
      return de->get_curve(); 
    }
    
    typename Traits::Info_edge &info()	const
    { 
      return de->get_info(); 
    }
    
    void set_info(typename Traits::Info_edge &i)
    {
      de->set_info(i); 
    }
    
    Vertex source() const
    {
      return Vertex(de->source()); 
    }
    
    Vertex target()	const
    {
      return Vertex(de->target()); 
    }
    
    Face face() const
    {
      return Face(de->get_face()); 
    }
    
    Halfedge twin() const
    {
      return Halfedge(de->get_twin()); 
    }
    
    Halfedge next_halfedge() const
    { 
      return Halfedge(de->get_next()); 
    }
    
    Ccb_halfedge_circulator ccb() const
    { 
      return Ccb_halfedge_circulator(de); 
    }
    
    
    //bug fix for circulators instead of get_obj
    const dedge* get_dedge() const
    {
      return de;
    }
    
  protected:
    dedge *de;
    };
  
  /**************************************************************/
  /**************************************************************/
  /********************* F a c e ********************************/
  /**************************************************************/
  /**************************************************************/
  class Face 
  {
  public:
    
    Face()
    {}
    
    Face(dface *f)
    {
      df=f;
    }
    
    Face(const Face &f)
    {
      df=f.df;
    }
    
    Face &operator=(const Face &f)
    {
      df = f.df; 
      return *this;
    }
    
    bool operator==(const Face &f) const
    {
      return df == f.df; 
    }
    
    bool operator!=(const Face &f) const
    {
      return !(*this==f); 
    }
    
    bool is_null()
    {
      return (df==NULL);
    }
    
    typename Traits::Info_face &info() const
    {
      return (df->get_info()); 
    }
    
    void set_info(typename Traits::Info_face &i)
    {
      df->set_info(i); 
    }
    
    
    bool is_unbounded() const
    {
      // face is not bounded iff it has no outer boundary
      return df->get_outer_ccb_edge() == NULL;
    }
    
    Holes_iterator holes_begin() const
    {
      return Holes_iterator(df->inner_ccb_begin());
    }
    
    Holes_iterator holes_end() const
    {
      return Holes_iterator(df->inner_ccb_end()); 
    }
    
    bool is_halfedge_on_inner_ccb(const Halfedge &e) const
    {
      typename ddcel::ccb c((dedge *)e.get_dedge());
      return df->is_inner_ccb(c);
    }
    
    bool is_halfedge_on_outer_ccb(const Halfedge &e) const
    {
      typename ddcel::ccb c((dedge*)e.get_dedge());
      return df->is_outer_ccb(c);
    }
    
    bool is_outer_ccb_exist() const
    {
      return df->get_outer_ccb_edge() != NULL;
    }
    
    Halfedge halfedge_on_outer_ccb() const
    {
      return Halfedge(df->get_outer_ccb_edge());
    }
    
    //addition after comment by herve
    Ccb_halfedge_circulator outer_ccb() const
    {
      return (halfedge_on_outer_ccb()).ccb();
    }
    


    
    const dface* get_dface() const
    {
      return df;
    }
    
  protected:
    dface * df;
    
  };
  
  
  /**************************************************************/
  /**************************************************************/
  /********************* Ccb_halfedge_circulator ********************/
  /**************************************************************/
  /**************************************************************/
  class Ccb_halfedge_circulator
  {
  public:
    Ccb_halfedge_circulator()
      : c(NULL)
    {}
    
    Ccb_halfedge_circulator(const typename ddcel::ccb &ccb1)
      : c(ccb1.get_edge()) 
    {}
    
    Ccb_halfedge_circulator(const Halfedge &e)
      : c((dedge*)e.get_dedge())
    {}
    
    Ccb_halfedge_circulator(dedge *e)
      : c(e)
    {}
    
    Ccb_halfedge_circulator(const Ccb_halfedge_circulator &cc)
      : c(cc.c.get_edge())
    {}
    
    Ccb_halfedge_circulator &operator=(const Ccb_halfedge_circulator &cc)
    {
      c.change_ccb(cc.c.get_edge()); 
      return *this; 
    }
    
    Ccb_halfedge_circulator &operator++()
    { 
      c.advance(); 
      return *this; 
    }
    
    Ccb_halfedge_circulator operator++(int)
    { 
      Ccb_halfedge_circulator tmp = *this;
      ++*this;
      return tmp;
    }
    
    bool operator==(const Ccb_halfedge_circulator &cc) const
    {
      return (c.get_edge() == cc.c.get_edge());
    }
    
    bool operator!=(const Ccb_halfedge_circulator &cc) const
    {
      return !(*this == cc); 
    }
    
    Halfedge operator*() const
    { 
      return Halfedge(c.get_edge()); 
    }
    
    typename ddcel::ccb &get_ccb()   
    {
      return c;
    }
    
  private:
    typename ddcel::ccb  c;
  };
  


  /**************************************************************/
  /**************************************************************/
  /********************  Halfedge_around_vertex_circulator ******/
  /**************************************************************/
  /**************************************************************/
  class Halfedge_around_vertex_circulator 
  {
  public:
    Halfedge_around_vertex_circulator()
      : a(NULL)
    {}
    
    Halfedge_around_vertex_circulator(defv &e)
      : a(e.get_vertex())
    {}
    
    Halfedge_around_vertex_circulator(const Vertex &v)
      : a((dvertex*)(v.get_dvertex()))
    {}
    
    
    Halfedge_around_vertex_circulator(dvertex *v)
      : a(v)
    {}
    
    Halfedge_around_vertex_circulator
      (const Halfedge_around_vertex_circulator& ec)
      : a(ec.a.get_vertex())
    {}
    
    Halfedge_around_vertex_circulator &operator=
      (const Halfedge_around_vertex_circulator &ec)
    {
      a.change_efv(ec.a.get_vertex()); 
      return *this; 
    }
    
    Halfedge_around_vertex_circulator &operator++()
    { 
      a.advance_cw(); 
      return *this; 
    }
    
    Halfedge_around_vertex_circulator operator++(int)
    { 
      Halfedge_around_vertex_circulator tmp = *this;
      ++*this;
      return tmp;
    }
    
    bool operator==(const Halfedge_around_vertex_circulator &ec) const
    { 
      return (a.get_edge() == ec.a.get_edge()) && 
        (a.get_vertex() == ec.a.get_vertex()); 
    }
    
    bool operator!=(const Halfedge_around_vertex_circulator &ec)
    {
      return !(*this == ec); 
    }
    
    Halfedge operator*() const
    {
      //      return Halfedge(a.get_edge()); 
      return Halfedge( (*(a.get_edge())).get_twin() ); 
    }
    
  private:
    defv a;
  };

  /**************************************************************/
  /**************************************************************/
  /********************* CGAL_Planar_map_2 **********************/
  /**************************************************************/
  /**************************************************************/

/*
#if (_MSC_VER >= 1100)
	typedef std::list<Traits::X_curve> X_curves_list;
#else
	typedef list<Traits::X_curve> X_curves_list;
#endif
*/
  CGAL_Planar_map_2()
    : traits(), d(&traits)
  {}
  
  /*
    CGAL_Planar_map_2(X_curves_list &l)
    : traits(), d(&traits)
    {
    insert(l); 
    }
    */
  
  Halfedge  insert( const typename Traits::X_curve  & cv ) 
  {
    return Halfedge(d.insert( cv ));
  }
  
  /*
    void  insert( X_curves_list  & l )
    {
    typename X_curves_list::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    insert(*it);
    }
    */
  
  Halfedge insert_at_vertices( const typename Traits::X_curve  & cv, 
                               Vertex v1, Vertex v2 )
    {
      return Halfedge(d.insert_at_vertices(cv, (dvertex*)v1.get_dvertex(), 
                                           (dvertex*)v2.get_dvertex()) );
    }
  
  Halfedge insert_from_vertex( const typename Traits::X_curve  & cv, 
                               Vertex v1, bool source)
  {
    return Halfedge( d.insert_from_vertex(cv, (dvertex*)v1.get_dvertex(), 
                                          source) );
  }
  
  Halfedge insert_in_face_interior( const typename Traits::X_curve  & cv, 
                                    Face f)
  {
    return( d.insert_in_face_interior(cv,(dface*)f.get_dface()) );
  }  
  
  
  // doron
  
  Halfedge  vertical_ray_shoot(const typename Traits::Point & p,  
                               Locate_type &locate_type , bool up )
  {
    dedge *e = d.vertical_ray_shoot(p, up);
    if (e == NULL)
        {
          locate_type=UNBOUNDED_FACE;
          return Halfedge(NULL);
        }
    
    typename Traits::Point source = e->source()->get_point();
    typename Traits::Point target = e->target()->get_point();
    typename Traits::X_curve curve = e->get_curve();
    
    if( source == p || target == p )
      locate_type = VERTEX;
    else
      locate_type = EDGE;
    
    return Halfedge(e);
  }
  // end doron
  
  
  // splits the edge and add a vertex in the splitting point;
  
  Halfedge split_edge (Halfedge e , typename Traits::X_curve  & c1 , 
                       typename Traits::X_curve  & c2)
  {
    
    return (Halfedge( d.split_edge((dedge*)e.get_dedge(),c1,c2) ));
  }

  
  
  //changes according to INRIA proposal .
  //auxilary functions
  Vertex does_vertex_exist(const typename Traits::Point& p)
  {
    Vertex_iterator vi;
    for (vi = vertices_begin(); vi != vertices_end(); ++vi)
      { 
        typename Traits::Point q = (*vi).point(); 
        if (traits.compare_x(p,q)==CGAL_EQUAL && 
            traits.compare_y(p,q)==CGAL_EQUAL )
          {
            return (*vi);
          }
      }
    return Vertex(NULL);
  }
  
  Halfedge is_point_on_halfedge(const typename Traits::Point& p)
  {
    Halfedge_iterator hi;
    for (hi = halfedges_begin(); hi != halfedges_end(); ++hi)
      { 
        typename Traits::X_curve c = (*hi).curve(); 
        if (traits.is_point_on_curve(c,p))   
          {
            return (*hi);
          }
      }
    return Halfedge(NULL);
  }
  
  

  Halfedge locate(const typename Traits::Point& p , Locate_type &lt )
  {
    
    Vertex v = does_vertex_exist(p); 
    if (!v.is_null() )  
      {
        lt = VERTEX;  //located on a vertex 
        return ( *(v.incident_halfedges()) );
        
        //a halfedge with the vertex as its source 
      }
    
    Halfedge e= is_point_on_halfedge(p); 
    if (!e.is_null())
      {
        lt = EDGE ; //located on edge
        return e;
      }
    
    
    lt=UNBOUNDED_FACE;
    Locate_type temp;
    Halfedge h = vertical_ray_shoot(p,temp,true);
    if( temp==UNBOUNDED_FACE ) 
      {
        //find an edge on unbounded face
        Face unbounded=unbounded_face();
        Ccb_halfedge_circulator c=*(unbounded.holes_begin());
        return (*c);
      }
    else
      {
        if ( !(h.face()).is_unbounded() ) 
          lt=FACE;
        return h;
      }
    
  }
  
  
  
  
  
  Face unbounded_face()
  {
    return Face(d.get_unbounded_face());
  }
  

  
  Face_iterator faces_begin() const
  { 
//   typename ddcel::faces_list::const_iterator k = d.faces.begin();
    typename ddcel::face_const_iterator k=d.faces.begin();              //solution for egcs
    return Face_iterator(*((typename ddcel::face_iterator*)(&k)));
  }
  
  Face_iterator faces_end() const
  { 
//    typename ddcel::faces_list::const_iterator k = d.faces.end();
    typename ddcel::face_const_iterator k = d.faces.end();
    return Face_iterator(*((typename ddcel::face_iterator*)(&k)));
  }
  
  Halfedge_iterator halfedges_begin() const
  {
//        typename ddcel::edges_list::const_iterator k = d.edges.begin();
        typename ddcel::edge_const_iterator k = d.edges.begin();
        return Halfedge_iterator(*((typename ddcel::edge_iterator*)(&k)));
  }
  
  Halfedge_iterator halfedges_end() const
  { 
//    typename ddcel::edges_list::const_iterator k = d.edges.end();
    typename ddcel::edge_const_iterator k = d.edges.end();
    return Halfedge_iterator(*((typename ddcel::edge_iterator*)(&k)));
  }
  
  Vertex_iterator vertices_begin() const
  { 
//    typename ddcel::vertices_list::const_iterator k = d.vertices.begin();
    typename ddcel::vertex_const_iterator k = d.vertices.begin();
    return Vertex_iterator(*((typename ddcel::vertex_iterator*)(&k)));
  }
  
  Vertex_iterator vertices_end() const
  {
//    typename ddcel::vertices_list::const_iterator k = d.vertices.end();
    typename ddcel::vertex_const_iterator k = d.vertices.end();
    return Vertex_iterator(*((typename ddcel::vertex_iterator*)(&k)));
  }
  

  void clear()
  {
    d.clear();
  }


  
  /**************************************************************/
  /**************************************************************/
  /*********** CGAL_Planar_map_2  - validity checks *************/
  /**************************************************************/
  /**************************************************************/
  bool is_valid(Vertex v)
  {
    bool valid = true;
    
    // check if every edge from v has v as its (origin) target (changed by iddo)
    Halfedge_around_vertex_circulator ec = v.incident_halfedges();
    Halfedge_around_vertex_circulator start = ec;
    do {
      //      if ((*ec).source() != v)
      if ((*ec).target() != v)
        {
          valid = false;
        }
      ++ec;
    } while (ec != start);
    
    return valid;
  }
  
  bool is_valid(Halfedge e)
  {
    bool valid = true;
    
    // check if source and target match the curve source and target
    if ( (e.source().point() != traits.curve_source(e.curve())) &&
         (e.source().point() != traits.curve_target(e.curve())) )
      valid = false;
    if ( (e.target().point() != traits.curve_source(e.curve())) &&
         (e.target().point() != traits.curve_target(e.curve())) )
      valid = false;  
    
    // check if twin has the same curve and appropriate endpoints
    if (e.curve() != e.twin().curve())
      valid = false;
    if ( (e.target() != e.twin().source()) ||
         (e.source() != e.twin().target()) )
      valid = false;
    
    //check relations with next
    if (e.target() != e.next_halfedge().source())
      valid = false;
    
    return valid;
  }
  
  bool is_valid(Ccb_halfedge_circulator start, Face f)
  {
    bool valid = true;
    Ccb_halfedge_circulator circ = start;
    
    do {
      if ((*circ).face() != f)
        valid = false;
      ++circ;
    } while (circ != start);
    
    return valid;
  }
  
  bool is_valid(Face f)
  {
    bool valid = true;
    
    // check if all edges of f (on all ccb's) refer to f (as their face)

    //  typename Face::Holes_iterator iccbit;
    //CHECK
    Holes_iterator iccbit;
    Ccb_halfedge_circulator ccb_circ;
    
    if (f.is_outer_ccb_exist())
      {
        ccb_circ = f.halfedge_on_outer_ccb().ccb();
        if (!is_valid(ccb_circ, f))
          valid = false;
      }
    
    for (iccbit = f.holes_begin(); iccbit != f.holes_end(); ++iccbit)
      {
        ccb_circ = *iccbit;
        if (!is_valid(ccb_circ, f))
          valid = false;
      }
    
    return valid;
  }
  
  bool is_valid()
  {
    bool valid = true;
    
    Vertex_iterator vi;
    for (vi = vertices_begin(); vi != vertices_end(); ++vi)
      {
        if (!is_valid(*vi))
          valid = false;
      }
    
    Halfedge_iterator ei;
    for (ei = halfedges_begin(); ei != halfedges_end(); ++ei)
      {
        if (!is_valid(*ei))
          valid = false;
      }	
    
    Face_iterator fi;
    for (fi = faces_begin(); fi != faces_end(); ++fi)
      {
        if (!is_valid(*fi))
          valid = false;
      }
    
    return valid;
  }
  

  /******************************************************************/
  /*********************   counting functions ***********************/
  /******************************************************************/

  long number_of_faces()
  {
    long num = 0;
    for (Face_iterator fi=faces_begin(); fi!=faces_end(); ++fi,++num);
    return num;
  }
   

  //counts every halfedge (i.e always even)
  long number_of_halfedges()
  {
    long num = 0;
    for (Halfedge_iterator ei=halfedges_begin(); ei!=halfedges_end(); 
         ++ei,++num);
    return num;
  }
   
  long number_of_vertices()
  {
    long num = 0;
    for (Vertex_iterator vi=vertices_begin(); vi!=vertices_end(); ++vi,++num);
    return num;
  }
   
  
   

  
  /******************************************************************/
  /*************************stream functions ************************/
  /******************************************************************/
  
public:
  
#if (_MSC_VER >= 1100)
  typedef ::ostream ostream;
#endif
  
  //new stream functions without info
  
  friend ostream &operator<<
  (ostream &o, const typename CGAL_Planar_map_2<Dcel,Traits>::Vertex &v)
  {
    o << "("<< v.point() << ")" ;
    return o;
  }
  
  friend ostream &operator<<
  (ostream &o, const typename CGAL_Planar_map_2<Dcel,Traits>::Halfedge &e)
  {
    o << "{" << e.source() ;
    o << "->" << e.target() << "}";
    return o;
    
  }
  
  
  friend ostream &operator<<(ostream &o, 
    const typename CGAL_Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator &b)
  {
    typename CGAL_Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator first = b,
      iter = b;
    
    o << "[";
    do
      {
        o << (*iter).source() << "-";
        ++iter;
      } while (iter != first);
    o << (*first).source() << "]" ;
    return o;
  }


  friend ostream &operator<<(ostream &o, 
  const typename CGAL_Planar_map_2<Dcel,Traits>::Halfedge_around_vertex_circulator &b)
  {
    typename CGAL_Planar_map_2<Dcel,Traits>::Halfedge_around_vertex_circulator 
      first = b, iter = b;
    
    o << "[";
    do
      {
        o << *iter << " ";
        ++iter;
      } while (iter != first);
    o << "]" ;
    return o;
  }



  
  friend ostream &operator<<
    (ostream &o, const typename CGAL_Planar_map_2<Dcel,Traits>::Face &f)
  {
    if (f.is_unbounded())
      {
        o << "Unbounded" ;
        return o;
      }
    
    o << f.halfedge_on_outer_ccb().ccb() ;
    
    return o;
  }
  
  
  friend ostream &operator<<
    (ostream &o, const CGAL_Planar_map_2<Dcel,Traits> &pm)
  {
    o << "Vertices ---------------" << endl;
    typename CGAL_Planar_map_2<Dcel,Traits>::Vertex_iterator vi;
    for (vi = pm.vertices_begin(); vi != pm.vertices_end(); ++vi)
      {
        o << (*vi) << endl;
      }
    
    o << "Halfedges ------------------" << endl;
    typename CGAL_Planar_map_2<Dcel,Traits>::Halfedge_iterator ei;
    for (ei = pm.halfedges_begin(); ei != pm.halfedges_end(); ++ei)
      {
        o << (*ei) << endl;
      }	
    
    o << "Faces ------------------" << endl;
    typename CGAL_Planar_map_2<Dcel,Traits>::Face_iterator fi;

    typename CGAL_Planar_map_2<Dcel,Traits>::Holes_iterator iccbit;


    typename CGAL_Planar_map_2<Dcel,Traits>::Ccb_halfedge_circulator ccb_circ;
    int ck;
    int fc_counter;
    for (fc_counter=0,fi = pm.faces_begin(); fi != pm.faces_end(); 
         ++fi,fc_counter++)
      {
        o << "Face " << fc_counter << " :\n";
        //			o << (*fi) << endl;
        
        o << "outer ccb: " ;
        
        if ((*fi).is_outer_ccb_exist())
          {
            //				o << "outer ccb: " ;
            ccb_circ = (*fi).halfedge_on_outer_ccb().ccb();
            o << ccb_circ;  
          }
        else 
          {
            o << "UNBOUNDED" <<endl ;
          }
        
        for (ck=0, iccbit = (*fi).holes_begin(); iccbit != (*fi).holes_end();
             ++iccbit, ck++)
          {
            o << "inner ccb " << ck << ": " ;
            ccb_circ = (*iccbit);
            o << ccb_circ;
          }
        o << endl;
      }
    return o;
  }
  
  /*commented out because of problems with egcs-1.0.2
  friend ostream &operator<<(ostream &o, const Locate_type &lt)
  {
    switch ( lt ) {
    case VERTEX:
      o << "VERTEX";
      break;
    case EDGE:
      o << "EDGE";
      break;
    case FACE:
      o << "FACE";
      break;
    case UNBOUNDED_FACE:
      o << "UNBOUNDED_FACE";
      break;
    }
    return o;
  }
  */	
	
protected:
  Traits_wrap  traits;

  ddcel d;
};




#else   /* CGAL_PLANAR_MAP_2_H */
#error  Header file Planar_map_2.h included twice
#endif  /* CGAL_PLANAR_MAP_2_H */

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * Planar_map_2.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/









