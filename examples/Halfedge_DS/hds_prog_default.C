/*  hds_prog_default.C              */
/*  ------------------------------- */
#include <CGAL/Halfedge_data_structure_default.h>
#include <CGAL/Halfedge_data_structure_decorator.h>

typedef int                                          Point;
typedef CGAL_Halfedge_data_structure_default<Point>  HDS;
typedef CGAL_Halfedge_data_structure_decorator<HDS>  Decorator;

int main() {
    HDS hds;
    Decorator decorator;
    decorator.create_loop( hds);
    CGAL_assertion( decorator.is_valid( hds));
    return 0;
}
