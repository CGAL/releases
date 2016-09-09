/*  hds_prog_graph.C                */
/*  ------------------------------- */
#include <CGAL/Halfedge_data_structure_bases.h>
#include <CGAL/Halfedge_data_structure_using_list.h>
#include <CGAL/Halfedge_data_structure_decorator.h>

typedef CGAL_Halfedge_data_structure_using_list <
            CGAL_Vertex_min_base, 
            CGAL_Halfedge_min_base, 
            CGAL_Facet_min_base >                    HDS;
typedef CGAL_Halfedge_data_structure_decorator<HDS>  Decorator;

int main() {
    HDS hds;
    Decorator decorator;
    decorator.create_loop( hds);
    CGAL_assertion( decorator.is_valid( hds));
    return 0;
}
