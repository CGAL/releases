/*  hds_prog_color.C                */
/*  ------------------------------- */
#include <CGAL/basic.h>
#include <CGAL/IO/Color.h>
#include <CGAL/Halfedge_data_structure_bases.h>
#include <CGAL/Halfedge_data_structure_using_list.h>

/* A facet with a color member variable. */
class My_facet : public CGAL_Facet_max_base {
public:
    CGAL_Color color;
};

typedef int                                          Point;
typedef CGAL_Halfedge_data_structure_using_list <
            CGAL_Vertex_max_base< Point >, 
            CGAL_Halfedge_max_base, 
            My_facet >                               HDS;

int main() {
    HDS hds;
    My_facet* f = hds.new_facet();
    f->color = CGAL_RED;
    return 0;
}

    
