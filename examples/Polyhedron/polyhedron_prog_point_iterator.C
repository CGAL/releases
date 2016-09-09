/*  polyhedron_prog_point_iterator.C   */
/*  ---------------------------------- */
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>

typedef CGAL_Cartesian<double>                               R;
typedef CGAL_Halfedge_data_structure_polyhedron_default_3<R> HDS;
typedef CGAL_Polyhedron_default_traits_3<R>                  Traits;
typedef CGAL_Polyhedron_3<Traits,HDS>                        Polyhedron;

/* The declaration of a point iterator -- given a Polyhedron */
#include <CGAL/Iterator_project.h>
#include <CGAL/function_objects.h>

typedef Polyhedron::Vertex                                   Vertex;
typedef Polyhedron::Vertex_iterator                          Vertex_iterator;
typedef Polyhedron::Point                                    Point;
typedef Polyhedron::Difference                               Difference;
typedef Polyhedron::iterator_category                        Iterator_category;
typedef CGAL_Project_point<Vertex>                           Project_point;
typedef CGAL_Iterator_project<Vertex_iterator, Project_point,
        Point&, Point*, Difference, Iterator_category>       Point_iterator;


int main() {
    Point p( 0.0, 0.0, 0.0);
    Point q( 1.0, 0.0, 0.0);
    Point r( 0.0, 1.0, 0.0);
    Point s( 0.0, 0.0, 1.0);

    Polyhedron P;
    P.make_tetrahedron( p, q, r, s);
    CGAL_set_ascii_mode( cout);
    Point_iterator begin = P.vertices_begin();
    for ( ; begin != P.vertices_end(); ++begin)
        cout << "(" << (*begin) << ") ";
    cout << endl;
    return 0;
}
