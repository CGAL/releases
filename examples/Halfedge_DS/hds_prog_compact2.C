/*  hds_prog_compact2.C              */
/*  ------------------------------- */
#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Point_3.h>
#include <CGAL/Halfedge_data_structure_bases.h>
#include <CGAL/Halfedge_data_structure_using_list.h>

typedef CGAL_Cartesian<double>                         R;
typedef CGAL_Point_3<R>                                Point;
typedef CGAL_Plane_3<R>                                Plane;

/* Define a new halfedge class. */
class My_halfedge {
protected:
    size_t  nxt;
    void*   v;
    void*   f;
public:
    typedef CGAL_Tag_false Supports_halfedge_prev;
    typedef CGAL_Tag_true  Supports_halfedge_vertex;
    typedef CGAL_Tag_true  Supports_halfedge_facet;

    My_halfedge() : f(NULL), nxt(0) {}

    void*       opposite()       {
        const size_t SIZE = sizeof( My_halfedge) + 
                            sizeof( CGAL_In_place_list_base<My_halfedge>);
        if ( nxt & 1)
            return (char*)this + SIZE;
        return (char*)this - SIZE;
    }
    const void* opposite() const {
        const size_t SIZE = sizeof( My_halfedge) + 
                            sizeof( CGAL_In_place_list_base<My_halfedge>);
        if ( nxt & 1)
            return (const char*)this + SIZE;
        return (const char*)this - SIZE;
    }
    void*       next()           { return (void*)(nxt & (~ size_t(1)));}
    const void* next() const     { return (void*)(nxt & (~ size_t(1)));}

    void*       vertex()         { return v;}
    const void* vertex() const   { return v;}

    void*       facet()          { return f;}
    const void* facet() const    { return f;}

    bool is_border() const       { return f == NULL;}

    void  set_opposite( void* g) {
        const size_t SIZE = sizeof( My_halfedge) + 
                            sizeof( CGAL_In_place_list_base<My_halfedge>);
        char* h = (char*)g;
        CGAL_assertion( abs( h - (char*)this) == SIZE);
        if ( h > (char*)this)
            nxt |= 1;
        else
            nxt &= (~ size_t(1));
    }
    void  set_next( void* h)     {
	CGAL_assertion( ((size_t)h & 1) == 0);
        nxt = ((size_t)(h)) | (nxt & 1);
    }
    void  set_vertex( void* _v)  { v = _v;}
    void  set_facet( void* _f)   { f = _f;}
};

typedef CGAL_Halfedge_data_structure_using_list <
            CGAL_Vertex_max_base< Point >,
            My_halfedge,
            CGAL_Facet_max_base >      HDS;
typedef HDS::Halfedge                  Halfedge;

int main() {
    HDS hds;
    Halfedge* h = hds.new_edge();
    return 0;
}
