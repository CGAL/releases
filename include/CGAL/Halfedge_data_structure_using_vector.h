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
// file          : include/CGAL/Halfedge_data_structure_using_vector.h
// author(s)     : Lutz Kettner  
//
// email         : cgal@cs.uu.nl
//
// ============================================================================

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_USING_VECTOR_H
#define CGAL_HALFEDGE_DATA_STRUCTURE_USING_VECTOR_H 1
// Includes also <CGAL/basic.h>, <stddef.h>.
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

#ifndef CGAL_PROTECT_ALGO_H
#include <algo.h>
#define CGAL_PROTECT_ALGO_H
#endif // CGAL_PROTECT_ALGO_H

#ifndef CGAL_PROTECT_VECTOR_H
#include <vector.h>
#define CGAL_PROTECT_VECTOR_H
#endif // CGAL_PROTECT_VECTOR_H

#ifndef CGAL_N_STEP_ADAPTOR_H
#include <CGAL/N_step_adaptor.h>
#endif

#ifndef CGAL_HALFEDGE_DATA_STRUCTURE_DECORATOR_H
#include <CGAL/Halfedge_data_structure_decorator.h>
#endif

// Define shorter names to please linker (g++/egcs)
#define CGAL__HDS_vector_vertex                    CGAL__Hvv
#define CGAL__HDS_vector_halfedge                  CGAL__Hvh
#define CGAL__HDS_vector_facet                     CGAL__Hvf


template <class V, class H, class F> class CGAL__HDS_vector_vertex;
template <class V, class H, class F> class CGAL__HDS_vector_halfedge;
template <class V, class H, class F> class CGAL__HDS_vector_facet;

template <class V, class H, class F>
class CGAL__HDS_vector_vertex : public V {
public:
    typedef V                                         Base;
    typedef CGAL__HDS_vector_vertex<V,H,F>             Vertex;
    typedef CGAL__HDS_vector_halfedge<V,H,F>           Halfedge;
    typedef CGAL__HDS_vector_facet<V,H,F>              Facet;

    // Point needed for Vertex constructor for efficiency reasons.
    typedef typename V::Point                         Point;

    CGAL__HDS_vector_vertex() {}
    CGAL__HDS_vector_vertex( const Point& p) : V(p) {}

    Halfedge*       halfedge()       {return (Halfedge*)(V::halfedge());}
    const Halfedge* halfedge() const {return (const Halfedge*)(V::halfedge());}
    void            set_halfedge( Halfedge* h) { V::set_halfedge(h);}
};

template <class V, class H, class F>
class CGAL__HDS_vector_halfedge : public H {
public:
    typedef H                                         Base;
    typedef CGAL__HDS_vector_vertex<V,H,F>             Vertex;
    typedef CGAL__HDS_vector_halfedge<V,H,F>           Halfedge;
    typedef CGAL__HDS_vector_facet<V,H,F>              Facet;

    Halfedge*       opposite()       {return (Halfedge*)(H::opposite());}
    Halfedge*       next()           {return (Halfedge*)(H::next());}
    Halfedge*       prev()           {return (Halfedge*)(H::prev());}
    Vertex*         vertex()         {return (Vertex*)(H::vertex());}
    Facet*          facet()          {return (Facet*)(H::facet());}

    const Halfedge* opposite() const {return (const Halfedge*)(H::opposite());}
    const Halfedge* next()     const {return (const Halfedge*)(H::next());}
    const Halfedge* prev()     const {return (const Halfedge*)(H::prev());}
    const Vertex*   vertex()   const {return (const Vertex*)(H::vertex());}
    const Facet*    facet()    const {return (const Facet*)(H::facet());}

    void  set_next( Halfedge* h)     { H::set_next(h);}
    void  set_prev( Halfedge* h)     { H::set_prev(h);}
    void  set_vertex( Vertex* ve)    { H::set_vertex(ve);}
    void  set_facet( Facet* facet)   { H::set_facet(facet);}

private:
    void  set_opposite( void* h)     { H::set_opposite(h);}
};


template <class V, class H, class F>
class CGAL__HDS_vector_facet : public F {
public:
    typedef F                                         Base;
    typedef CGAL__HDS_vector_vertex<V,H,F>             Vertex;
    typedef CGAL__HDS_vector_halfedge<V,H,F>           Halfedge;
    typedef CGAL__HDS_vector_facet<V,H,F>              Facet;

    Halfedge*       halfedge()       {return (Halfedge*)(F::halfedge());}
    const Halfedge* halfedge() const {return (const Halfedge*)(F::halfedge());}
    void            set_halfedge( Halfedge* h) { F::set_halfedge(h);}
};


// A Halfedge Data Structure Using Vectors
// -------------------------------------------
//
// DEFINITION
//
// The class CGAL_Halfedge_data_structure_using_vector<Vertex,Halfedge,Facet>
// is a halfedge data structure parameterized with vertex, halfedge,
// and facet types. The base classes defined in the previous subsection
// could be used therefore. It is sufficient for the parameter classes to
// implement the pointers as `void*'. They do not have to know the types
// of their relatives.

template < class V, class H, class F>
class CGAL_Halfedge_data_structure_using_vector {
public:
    typedef CGAL_Halfedge_data_structure_using_vector<V,H,F>   Self;
    typedef CGAL__HDS_vector_vertex<V,H,F>           Vertex;
    typedef CGAL__HDS_vector_halfedge<V,H,F>         Halfedge;
    typedef CGAL__HDS_vector_facet<V,H,F>            Facet;

    // Point needed for Vertex constructor for efficiency reasons.
    typedef typename Vertex::Point                  Point;
    typedef typename Facet::Normal                  Normal;
    typedef typename Facet::Plane                   Plane;

protected:
    // Three vectors for the elements.
    typedef vector<Vertex>                          Vertex_vector;
    typedef vector<Halfedge>                        Halfedge_vector;
    typedef vector<Facet>                           Facet_vector;
public:
    typedef typename Halfedge_vector::size_type     Size;
    // typedef typename Halfedge_vector::size_type     size_type;
    typedef typename Halfedge_vector::difference_type
                                                    Difference;
protected:
    Vertex_vector    vertices;
    Halfedge_vector  halfedges;
    Facet_vector     facets;
    Size             nb_border_halfedges;
    Size             nb_border_edges;
    Halfedge*        border_halfedges;

public:
    typedef typename Vertex::Supports_vertex_halfedge Supports_vertex_halfedge;
    typedef typename Halfedge::Supports_halfedge_prev Supports_halfedge_prev;
    typedef typename Halfedge::Supports_halfedge_vertex
                                                      Supports_halfedge_vertex;
    typedef typename Halfedge::Supports_halfedge_facet
                                                      Supports_halfedge_facet;
    typedef typename Facet::Supports_facet_halfedge   Supports_facet_halfedge;

    typedef typename Vertex::Supports_vertex_point    Supports_vertex_point;
    typedef typename Facet::Supports_facet_plane      Supports_facet_plane;
    typedef typename Facet::Supports_facet_normal     Supports_facet_normal;

    typedef CGAL_Tag_false                            Supports_removal;
    typedef random_access_iterator_tag              iterator_category;

    typedef typename Vertex_vector::iterator        Vertex_iterator;
    typedef typename Halfedge_vector::iterator      Halfedge_iterator;
    typedef typename Facet_vector::iterator         Facet_iterator;
    typedef CGAL_N_step_adaptor< Halfedge_iterator,
                                2,
                                Halfedge&,
                                Halfedge*,
                                Halfedge,
                                ptrdiff_t,
                                iterator_category>  Edge_iterator;

    typedef typename Vertex_vector::const_iterator    Vertex_const_iterator;
    typedef typename Halfedge_vector::const_iterator  Halfedge_const_iterator;
    typedef typename Facet_vector::const_iterator     Facet_const_iterator;
    typedef CGAL_N_step_adaptor< Halfedge_const_iterator,
                                2,
                                const Halfedge&,
                                const Halfedge*,
                                Halfedge,
                                ptrdiff_t,
                                iterator_category>  Edge_const_iterator;

// CREATION

private:
    void pointer_update( const Vertex*   v_old,
                         const Halfedge* h_old,
                         const Facet*    f_old);
        // Update own pointers assuming that they lived previously
        // in a halfedge data structure with vector starting addresses
        // as given as parameters v_old, h_old, f_old.

public:
    CGAL_Halfedge_data_structure_using_vector()
        : nb_border_halfedges(0), nb_border_edges(0), border_halfedges(NULL) {}
        // the empty polyhedron `P'.

    CGAL_Halfedge_data_structure_using_vector( Size v, Size h, Size f)
        : nb_border_halfedges(0), nb_border_edges(0), border_halfedges(NULL) {
        // a polyhedron `P' with storage reserved for v vertices, h
        // halfedges, and f facets. The reservation sizes are a hint for
        // optimizing storage allocation. They are not used here.
        vertices.reserve(v);
        halfedges.reserve(h);
        facets.reserve(f);
    }

    void reserve( Size v, Size h, Size f) {
        // reserve storage for v vertices, h halfedges, and f facets. The
        // reservation sizes are a hint for optimizing storage allocation.
        // If the `capacity' is already greater than the requested size
        // nothing happens. If the `capacity' changes all iterators and
        // circulators invalidates. Function is void here.
        Vertex*   v_old = vertices.begin();
        Halfedge* h_old = halfedges.begin();
        Facet*    f_old = facets.begin();
        if ( CGAL_check_tag( Supports_halfedge_vertex()))
            vertices.reserve(v);
        halfedges.reserve(h);
        if ( CGAL_check_tag( Supports_halfedge_facet()))
            facets.reserve(f);
        pointer_update( v_old, h_old, f_old);
    }

    CGAL_Halfedge_data_structure_using_vector( const Self& hds)
    :  vertices( hds.vertices),
       halfedges( hds.halfedges),
       facets( hds.facets),
       nb_border_halfedges( hds.nb_border_halfedges),
       nb_border_edges( hds.nb_border_edges),
       border_halfedges( hds.border_halfedges)
    {
        pointer_update( hds.vertices.begin(),
                        hds.halfedges.begin(),
                        hds.facets.begin());
    }

    Self& operator=( const Self& hds) {
        if ( this != &hds) {
            delete_all();
            vertices            = hds.vertices;
            halfedges           = hds.halfedges;
            facets              = hds.facets;
            nb_border_halfedges = hds.nb_border_halfedges;
            nb_border_edges     = hds.nb_border_edges;
            border_halfedges    = hds.border_halfedges;
            pointer_update( hds.vertices.begin(),
                            hds.halfedges.begin(),
                            hds.facets.begin());
        }
        return *this;
    }


// Access Member Functions

    Size size_of_vertices() const  { return vertices.size();}
    Size size_of_halfedges() const { return halfedges.size();}
        // number of all halfedges (including border halfedges).
    Size size_of_facets() const    { return facets.size();}

    Size capacity_of_vertices() const    { return vertices.capacity();}
    Size capacity_of_halfedges() const   { return halfedges.capacity();}
    Size capacity_of_facets() const      { return facets.capacity();}

    size_t bytes() const {
        return sizeof(Self)
               + vertices.size()  * sizeof( Vertex)
               + halfedges.size() * sizeof( Halfedge)
               + facets.size()    * sizeof( Facet);
    }
    size_t bytes_reserved() const {
        return sizeof(Self)
               + vertices.capacity()  * sizeof( Vertex)
               + halfedges.capacity() * sizeof( Halfedge)
               + facets.capacity()    * sizeof( Facet);
    }

    Vertex_iterator   vertices_begin()   { return vertices.begin();}
    Vertex_iterator   vertices_end()     { return vertices.end();}
    Halfedge_iterator halfedges_begin()  { return halfedges.begin();}
    Halfedge_iterator halfedges_end()    { return halfedges.end();}
    Facet_iterator    facets_begin()     { return facets.begin();}
    Facet_iterator    facets_end()       { return facets.end();}

    Edge_iterator edges_begin() { return Edge_iterator(halfedges_begin());}
        // iterator over all edges. The iterator refers to halfedges, but
        // enumerates only one of the two corresponding opposite
        // halfedges.

    Edge_iterator edges_end() { return Edge_iterator(halfedges_end());}
        // end of the range over all edges.

    // The constant iterators and circulators.

    Vertex_const_iterator   vertices_begin()  const{ return vertices.begin();}
    Vertex_const_iterator   vertices_end()    const{ return vertices.end();}
    Halfedge_const_iterator halfedges_begin() const{ return halfedges.begin();}
    Halfedge_const_iterator halfedges_end()   const{ return halfedges.end();}
    Facet_const_iterator    facets_begin()    const{ return facets.begin();}
    Facet_const_iterator    facets_end()      const{ return facets.end();}

    Edge_const_iterator edges_begin() const {
        return Edge_const_iterator(halfedges_begin());
    }
    Edge_const_iterator edges_end() const {
        return Edge_const_iterator(halfedges_end());
    }

// Insertion
//
// The following operations simply allocate a new element of that type.
// Halfedges are always allocated in pairs of opposite halfedges. The
// opposite pointers are automatically set.

    Vertex* new_vertex() {
                CGAL_assertion( vertices.size() < vertices.capacity());
                vertices.push_back( Vertex());
                return & (vertices.back());
    }

    Vertex* new_vertex( const Vertex* v) {
                CGAL_assertion( vertices.size() < vertices.capacity());
                vertices.push_back( *v);
                return & (vertices.back());
    }

    Vertex* new_vertex( const Point& p) {
                CGAL_assertion( vertices.size() < vertices.capacity());
                vertices.push_back( Vertex(p));
                return & (vertices.back());
    }

    Halfedge* new_edge() {
                CGAL_assertion( halfedges.size() + 1 < halfedges.capacity());
                // creates a new pair of opposite border halfedges.
                halfedges.push_back( Halfedge());
                Halfedge* h = & (halfedges.back());
                halfedges.push_back( Halfedge());
                Halfedge* g = & (halfedges.back());
                CGAL_assertion( h + 1 == g);
                CGAL_assertion( (char*)g - (char*)h == sizeof( Halfedge));
                h->H::set_opposite(g);
                g->H::set_opposite(h);
                return h;
    }

    Halfedge* new_edge( const Halfedge* he) {
                CGAL_assertion( halfedges.size() + 1 < halfedges.capacity());
                // creates a new pair of opposite border halfedges.
                halfedges.push_back( *he);
                Halfedge* h = & (halfedges.back());
                halfedges.push_back( *(he->opposite()));
                Halfedge* g = & (halfedges.back());
                h->H::set_opposite(g);
                g->H::set_opposite(h);
                return h;
    }

    Facet* new_facet(){
                CGAL_assertion( facets.size() < facets.capacity());
                facets.push_back( Facet());
                return & (facets.back());
    }

    Facet* new_facet( const Facet* f) {
                facets.push_back( *f);
                return & (facets.back());
    }

// Removal
//
// The following operations erase an element referenced by a pointer.
// Halfedges are always deallocated in pairs of opposite halfedges. Erase
// of single elements is optional. The deletion of all is mandatory.

    void delete_all() {
                vertices.erase(  vertices.begin(),  vertices.end());
                halfedges.erase( halfedges.begin(), halfedges.end());
                facets.erase(    facets.begin(),    facets.end());
                nb_border_halfedges = 0;
                nb_border_edges = 0;
                border_halfedges = NULL;
    }

    void vertex_pop_back() { vertices.pop_back(); }

    void edge_pop_back()   {
                halfedges.pop_back();
                halfedges.pop_back();
    }

    void facet_pop_back()  { facets.pop_back(); }

// Special Operations on Polyhedral Surfaces
protected:
    void update_opposite( Halfedge* h) {
                Halfedge* g = h + 1;
                h->H::set_opposite(g);
                g->H::set_opposite(h);
    }

    void update_prev( Halfedge*, Halfedge*, vector<Halfedge*>, CGAL_Tag_false){}
    void update_prev( Halfedge* h, Halfedge* base, vector<Halfedge*> inv,
                      CGAL_Tag_true){
        h->set_prev( inv[ h->prev() - base]);
    }
    void update_vertex( Halfedge*  , CGAL_Tag_false, CGAL_Tag_false){}
    void update_vertex( Halfedge*  , CGAL_Tag_true,  CGAL_Tag_false){}
    void update_vertex( Halfedge*  , CGAL_Tag_false, CGAL_Tag_true){}
    void update_vertex( Halfedge* h, CGAL_Tag_true,  CGAL_Tag_true){
        h->vertex()->set_halfedge(h);
    }
    void update_facet( Halfedge*  , CGAL_Tag_false, CGAL_Tag_false){}
    void update_facet( Halfedge*  , CGAL_Tag_true,  CGAL_Tag_false){}
    void update_facet( Halfedge*  , CGAL_Tag_false, CGAL_Tag_true){}
    void update_facet( Halfedge* h, CGAL_Tag_true,  CGAL_Tag_true){
        h->facet()->set_halfedge(h);
    }

public:
// Operations with Border Halfedges

    Size size_of_border_halfedges() const { return nb_border_halfedges;}
        // number of border halfedges. An edge with no incident facet
        // counts as two border halfedges. Precondition: `normalize_border()'
        // has been called and no halfedge insertion or removal and no
        // change in border status of the halfedges have occured since
        // then.

    Size size_of_border_edges() const { return nb_border_edges;}
        // number of border edges. If `size_of_border_edges() ==
        // size_of_border_halfedges()' all border edges are incident to a
        // facet on one side and to a hole on the other side.
        // Precondition: `normalize_border()' has been called and no
        // halfedge insertion or removal and no change in border status of
        // the halfedges have occured since then.

    Halfedge_iterator border_halfedges_begin() {
        // halfedge iterator starting with the border edges. The range [
        // `halfedges_begin(), border_halfedges_begin()') denotes all
        // non-border edges. The range [`border_halfedges_begin(),
        // halfedges_end()') denotes all border edges. Precondition:
        // `normalize_border()' has been called and no halfedge insertion
        // or removal and no change in border status of the halfedges have
        // occured since then.
        return Halfedge_iterator( border_halfedges);
    }

    Edge_iterator border_edges_begin()  {
        // ... trial to make Edge_iterator obsolete.
        return Edge_iterator(border_halfedges_begin());
    }

    Halfedge_const_iterator border_halfedges_begin() const {
        CGAL_assertion( border_halfedges);
        return Halfedge_const_iterator( border_halfedges);
    }

    Edge_const_iterator border_edges_begin()  const {
        return Edge_const_iterator(border_halfedges_begin());
    }

    void normalize_border();
        // sorts halfedges such that the non-border edges precedes the
        // border edges. For each border edge that is incident to a facet
        // the halfedge iterator will reference the halfedge incident to
        // the facet right before the halfedge incident to the hole.
};

#define V_UPDATE(v) (v_new + ((v) - v_old))
#define H_UPDATE(h) (h_new + ((h) - h_old))
#define F_UPDATE(f) (f_new + ((f) - f_old))

template < class V, class H, class F>
void
CGAL_Halfedge_data_structure_using_vector<V,H,F>::
pointer_update( const Vertex*   v_old,
                const Halfedge* h_old,
                const Facet*    f_old) {
    // Update own pointers assuming that they lived previously
    // in a halfedge data structure with vector starting addresses
    // as given as parameters v_old, h_old, f_old.
    CGAL_Halfedge_data_structure_decorator<Self> D;
    Vertex*   v_new = vertices.begin();
    Halfedge* h_new = halfedges.begin();
    Facet*    f_new = facets.begin();
    for ( Halfedge_iterator h = halfedges.begin(); h != halfedges.end(); ++h) {
        h->set_next( H_UPDATE( h->next()));
        h->H::set_opposite( H_UPDATE( h->opposite()));
        D.set_prev( h, H_UPDATE( D.get_prev(h)));
        D.set_vertex( h, V_UPDATE( D.get_vertex(h)));
        D.set_vertex_halfedge( h);
        D.set_facet( h, F_UPDATE( D.get_facet(h)));
        if ( ! h->is_border())
            D.set_facet_halfedge( h);
    }
    border_halfedges = H_UPDATE( border_halfedges);
}
#undef V_UPDATE
#undef H_UPDATE
#undef F_UPDATE

template < class V, class H, class F>
void
CGAL_Halfedge_data_structure_using_vector<V,H,F>::normalize_border() {
    nb_border_halfedges = 0;
    nb_border_edges = 0;
    border_halfedges = &*(halfedges_end());
    // Lets run one partition step over the array of halfedges.
    // First find a pivot -- that means a border edge.
    Edge_iterator ll = edges_begin();
    while ( ll != edges_end() && (! (*ll).is_border()) &&
            (!(*ll).opposite()->is_border() ))
        ++ll;
    if ( ll == edges_end())
        // Done. No border edges found.
        return;

    // An array of pointers to update the changed halfedge pointers.
    typedef vector<Halfedge*> HVector;
    HVector hvector;
    hvector.reserve( halfedges.size());
    // Initialize it.
    for ( Halfedge_iterator i = halfedges_begin(); i!=halfedges_end();++i){
        hvector.push_back( &*i);
    }
    CGAL_assertion( hvector.size() == halfedges.size());
    typename HVector::iterator llhv = hvector.begin()+2*(ll-edges_begin());
    // Start with the partitioning.
    Edge_iterator rr = edges_end();
    --rr;
    typename HVector::iterator rrhv = hvector.end();
    --rrhv;
    --rrhv;
                          // Pivot is in *ll
                          // Elements in [rr+1..end) >= pivot (border)
                          // Elements in [begin..ll) <  pivot (non border)
    while (ll < rr) {
                          // Pivot is in *ll, ll <= rr.
        while ( rr > ll && ((*rr).is_border() ||
                            (*rr).opposite()->is_border())) {
            if ( ! (*rr).opposite()->is_border()) {
                swap( *rr, *((*rr).opposite()));
                update_opposite( &*rr);
                swap( *rrhv, *(rrhv+1));
            }
            --rr;
            --rrhv;
            --rrhv;
        }
                          // Elements in [rr+1..end) >= pivot (border)
                          // *rr <= pivot, ll <= rr.
        swap( *((*ll).opposite()), *((*rr).opposite()));
        swap( *ll, *rr);
        update_opposite( &*ll);
        update_opposite( &*rr);
        swap( *(llhv+1), *(rrhv+1));
        swap( *llhv, *rrhv);
                          // Elements in [begin..ll) < pivot
                          // Pivot is in *rr, ll <= rr.
        while ( !(*ll).is_border() && !(*ll).opposite()->is_border()) {
            ++ll;
            ++llhv;
            ++llhv;
        }
                          // Elements in [begin..ll) < pivot
                          // *ll >= pivot
                          // ll <= rr (since *rr is pivot.)
        CGAL_assertion( ll <= rr);
        CGAL_assertion( llhv <= rrhv);
        swap( *((*ll).opposite()), *((*rr).opposite()));
        swap( *ll, *rr);
        update_opposite( &*ll);
        update_opposite( &*rr);
        swap( *(llhv+1), *(rrhv+1));
        swap( *llhv, *rrhv);
        if ( ! (*rr).opposite()->is_border()) {
            swap( *rr, *((*rr).opposite()));
            update_opposite( &*rr);
            swap( *rrhv, *(rrhv+1));
        }
        --rr;
        --rrhv;
        --rrhv;
                          // Elements in [rr+1..end) >= pivot
                          // Pivot is in *ll
    }
    CGAL_assertion( llhv >= rrhv);
                          // rr + 1 >= ll >= rr
                          // Elements in [rr+1..end) >= pivot
                          // Elemente in [begin..ll) <  pivot
                          // Pivot is in a[ll]
    if ( ll == rr) {
        // Check for the possibly missed swap.
        if ( (*rr).is_border() && ! ((*rr).opposite()->is_border())) {
            swap( *rr, *((*rr).opposite()));
            update_opposite( &*rr);
            swap( *rrhv, *(rrhv+1));
        }
    }
    CGAL_assertion( (*ll).opposite()->is_border());
    CGAL_assertion( ll == edges_begin() || ! (*(ll-1)).is_border());
    CGAL_assertion( ll == edges_begin() ||
               ! (*(ll-1)).opposite()->is_border());
    border_halfedges = &*ll;
    nb_border_edges = (edges_end() - ll);
    nb_border_halfedges = 0;

    HVector inv_vector( halfedges.size());
    // Initialize inverse index.
    for ( typename HVector::iterator k = hvector.begin();
          k != hvector.end(); ++k){
        inv_vector[*k - halfedges_begin()] =
            halfedges_begin() + (k - hvector.begin());
    }

    // Update halfedge pointers.
    for (Halfedge_iterator h =halfedges_begin(); h != halfedges_end();++h){
        (*h).set_next( inv_vector[ (*h).next() - &(halfedges.front())]);
        update_prev(   &*h, &(halfedges.front()), inv_vector,
                            Supports_halfedge_prev());
        update_vertex( &*h, Supports_halfedge_vertex(),
                            Supports_vertex_halfedge());
        if ( (*h).is_border())
            nb_border_halfedges++;
        else
            update_facet(  &*h, Supports_halfedge_facet(),
                                Supports_facet_halfedge());
    }
}

// Undef shorter names (g++/egcs)
#undef CGAL__HDS_vector_vertex
#undef CGAL__HDS_vector_halfedge
#undef CGAL__HDS_vector_facet
#endif // CGAL_HALFEDGE_DATA_STRUCTURE_USING_VECTOR_H //
// EOF //
