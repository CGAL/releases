#include "tutorial.h"
#include <CGAL/Point_2.h>
#include <CGAL/Circle_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/point_generators_2.h>
#include <iostream>

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Face  Face;
typedef Triangulation::Edge  Edge;
typedef Triangulation::Vertex  Vertex;
typedef Face::Face_handle Face_handle;
typedef Vertex::Vertex_handle Vertex_handle;

main()
{
    const int numPoints = 50;
    CGAL::Random_points_in_square_2<Point> g(100.0);  // random points generator
    Triangulation tr;                                // empty triangulation

    // construct a triangulation
    for (int i=0; i<numPoints; ++i) {
        tr.insert( *g++ );                             // take next point from generator
    }

    Edge_iterator it = tr.edges_begin(),               // initialize with begin value
                      beyond = tr.edges_end();         // past the end value

    while (it != beyond) {
       Edge edge = *it;                                // take `edge'
       ++it;                                           // advance iterator

       Face_handle face = edge.first;                  // take the face
       int nbIndex = edge.second;
       Face_handle neighbor = face->neighbor(nbIndex); // take neighbor

       Vertex_handle edgev1 = face->vertex(face->cw(nbIndex));  // edges vertices
       Vertex_handle edgev2 = face->vertex(face->ccw(nbIndex));

       // two opposite vertices of adjacent face
       Vertex_handle opposite1 = face->vertex(nbIndex);
       Vertex_handle opposite2 = neighbor->vertex(neighbor->index(face));

       // smallest circle through edge vertices
       Circle circle(edgev1->point(), edgev2->point());

       if ( ! tr.is_infinite(opposite1) ) {            // opposite1 infinite?
          if (circle.has_on_bounded_side(opposite1->point()) ) {
             // opposite vertex 1 lies inside circle, continue with next edge
             continue;
          }
       }
       if ( ! tr.is_infinite(opposite2)) {             // opposite2 infinite?
          if (circle.has_on_bounded_side(opposite2->point()) ) {
             // opposite vertex 2 inside circle, continue with next edge
             continue;
          }
       }

       // opposite vertex 1 and 2 not inside circle, output edge as segment
       std::cout << Segment(edgev1->point(), edgev2->point()) << endl;
    }
}
