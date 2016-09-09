/*  polyhedron_prog_tetra.C         */
/*  ------------------------------- */
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL_Cartesian<double>                                R;
typedef CGAL_Halfedge_data_structure_polyhedron_default_3<R>  HDS;
typedef CGAL_Polyhedron_default_traits_3<R>                   Traits;
typedef CGAL_Polyhedron_3<Traits,HDS>                         Polyhedron;
typedef Polyhedron::Point                                     Point;
typedef Polyhedron::Vertex_iterator                           Vertex_iterator;

int main() {
    Point p( 1.0, 0.0, 0.0);
    Point q( 0.0, 1.0, 0.0);
    Point r( 0.0, 0.0, 1.0);
    Point s( 0.0, 0.0, 0.0);

    Polyhedron P;
    P.make_tetrahedron( p, q, r, s);
    CGAL_set_ascii_mode( cout);
    Vertex_iterator begin = P.vertices_begin();
    for ( ; begin != P.vertices_end(); ++begin)
        cout << "(" << begin->point() << ") ";
    cout << endl;
    return 0;
}
