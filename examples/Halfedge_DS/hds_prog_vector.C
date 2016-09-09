/*  hds_prog_simple.C               */
/*  ------------------------------- */
#include <CGAL/Halfedge_data_structure_bases.h>
#include <CGAL/Halfedge_data_structure_using_vector.h>
#include <CGAL/Halfedge_data_structure_decorator.h>

typedef int                                          Point;
typedef CGAL_Halfedge_data_structure_using_vector <
            CGAL_Vertex_max_base< Point >, 
            CGAL_Halfedge_max_base, 
            CGAL_Facet_max_base >                    HDS;
typedef CGAL_Halfedge_data_structure_decorator<HDS>  Decorator;

int main() {
    HDS hds(1,2,2);
    Decorator decorator;
    decorator.create_loop( hds);
    CGAL_assertion( decorator.is_valid( hds));
    return 0;
}
