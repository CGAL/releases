/*  polyhedron_prog_off.C           */
/*  ------------------------------- */
#include <CGAL/Cartesian.h>
#include <iostream.h>
#include <CGAL/Halfedge_data_structure_polyhedron_default_3.h>
#include <CGAL/Polyhedron_default_traits_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Iterator_project.h>
#include <CGAL/function_objects.h>

typedef CGAL_Cartesian<double>                               R;
typedef CGAL_Halfedge_data_structure_polyhedron_default_3<R> HDS;
typedef CGAL_Polyhedron_default_traits_3<R>                  Traits;
typedef CGAL_Polyhedron_3<Traits,HDS>                        Polyhedron;
typedef Polyhedron::Difference                               Difference;
typedef Polyhedron::iterator_category                        Iterator_category;
typedef Polyhedron::Point                                    Point;
typedef Polyhedron::Vertex                                   Vertex;
typedef Polyhedron::Vertex_iterator                          Vertex_iterator;
typedef Polyhedron::Facet_iterator                           Facet_iterator;
typedef Polyhedron::Halfedge_around_facet_circulator
                                            Halfedge_around_facet_circulator;

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

    /* Write polyhedron on Object File Format (OFF). */
    CGAL_set_ascii_mode( cout);
    cout << "OFF" << endl;
    cout << P.size_of_vertices() << ' ' << P.size_of_facets() << " 0" << endl;
    copy( Point_iterator( P.vertices_begin()), 
	  Point_iterator( P.vertices_end()), 
	  ostream_iterator<Point>(cout,"\n"));
    Facet_iterator i = P.facets_begin();
    for ( ; i != P.facets_end(); ++i) {
        Halfedge_around_facet_circulator j = i->facet_begin();
        /* Facets in polyhedral surfaces are at least triangles. */
        CGAL_assertion( CGAL_circulator_size(j) >= 3);
        cout << CGAL_circulator_size(j) << " ";
        do {
            size_t d = 0;
            distance( P.vertices_begin(), j->vertex(), d);
            cout << " " << d;
        } while ( ++j != i->facet_begin());
        cout << endl;
    }
    return 0;
}
