/*  polyhedron_prog_simple.C        */
/*  ------------------------------- */
#include <CGAL/Cartesian.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL_Cartesian<double>                                R;
typedef CGAL_Halfedge_data_structure_polyhedron_default_3<R>  HDS;
typedef CGAL_Polyhedron_default_traits_3<R>                   Traits;
typedef CGAL_Polyhedron_3<Traits,HDS>                         Polyhedron;
typedef Polyhedron::Halfedge_handle                           Halfedge_handle;

int main() {
    Polyhedron P;
    Halfedge_handle h = P.make_tetrahedron();
    CGAL_assertion( P.is_tetrahedron( h));
    return 0;
}
