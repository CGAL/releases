#ifndef SCENE_COMBINATORIAL_MAP_ITEM_H
#define SCENE_COMBINATORIAL_MAP_ITEM_H

//=========
#include <CGAL/internal/corefinement/Combinatorial_map_for_corefinement.h>
#include "Scene_combinatorial_map_item_config.h"
#include <iostream>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "Polyhedron_type.h"
#include  <CGAL/Three/Scene_item.h>
typedef CGAL::internal_IOP::Item_with_points_and_volume_info<Kernel,Polyhedron> Items;
typedef CGAL::Combinatorial_map<3,Items> Combinatorial_map_3;
//=========

class QMenu;
class QAction;
namespace CGAL { namespace Three{
class Scene_interface;
}}
class Scene_polyhedron_item;
class Viewer_interface;

class SCENE_COMBINATORIAL_MAP_ITEM_EXPORT Scene_combinatorial_map_item
        : public CGAL::Three::Scene_item
{
    Q_OBJECT
public:  
    Scene_combinatorial_map_item(CGAL::Three::Scene_interface*,void* ad_A=NULL);
    ~Scene_combinatorial_map_item();

    Scene_combinatorial_map_item* clone() const;
    // Function to override the context menu
    QMenu* contextMenu();

    //  bool load(std::istream& in);
    //  void load(Scene_polyhedron_item*);
    //  bool save(std::ostream& out) const;

    QString toolTip() const;

    // Indicate if rendering mode is supported
    virtual bool supportsRenderingMode(RenderingMode m) const { return (m != Gouraud && m!=PointsPlusNormals && m!=Splatting); } // CHECK THIS!
    //Event handling
    virtual bool keyPressEvent(QKeyEvent*);
    //drawing of the scene
    virtual void draw_edges(CGAL::Three::Viewer_interface* viewer) const;
    virtual void draw_points(CGAL::Three::Viewer_interface*) const;
    virtual void draw(CGAL::Three::Viewer_interface*) const;

    bool isFinite() const { return true; }
    bool is_from_corefinement() const {return address_of_A!=NULL;}
    bool isEmpty() const;
    void compute_bbox() const;

    const Combinatorial_map_3& combinatorial_map() const
    {
        return *m_combinatorial_map;
    }

    Combinatorial_map_3& combinatorial_map()
    {
        return *m_combinatorial_map;
    }

    Combinatorial_map_3* m_combinatorial_map;

private:
    Kernel::Vector_3 compute_face_normal(Combinatorial_map_3::Dart_const_handle adart) const;
    CGAL::Three::Scene_interface* last_known_scene;
    std::size_t volume_to_display;
    QAction* exportSelectedVolume;
    void* address_of_A;
    template <class Predicate> void export_as_polyhedron(Predicate,const QString&) const;

   enum VAOs {
       Edges = 0,
       Points,
       Facets,
       NbOfVaos = Facets +1
   };
   enum VBOs {
       Edges_vertices = 0,
       Points_vertices,
       Facets_vertices,
       Facets_normals,
       NbOfVbos = Facets_normals +1
   };

   mutable std::vector<double> positions_lines;
   mutable std::vector<double> positions_points;
   mutable std::vector<double> positions_facets;
   mutable std::vector<double> normals;
   mutable std::size_t nb_lines;
   mutable std::size_t nb_points;
   mutable std::size_t nb_facets;

    mutable QOpenGLShaderProgram *program;

    using CGAL::Three::Scene_item::initialize_buffers;
    void initialize_buffers(CGAL::Three::Viewer_interface *viewer) const;

    using CGAL::Three::Scene_item::compute_elements;
    void compute_elements(void) const;

public Q_SLOTS:
    void set_next_volume();
    void export_current_volume_as_polyhedron() const;
    void export_union_as_polyhedron() const;
    void export_intersection_as_polyhedron() const;
    void export_A_minus_B_as_polyhedron() const;
    void export_B_minus_A_as_polyhedron() const;

}; // end class Scene_combinatorial_map_item

#endif // SCENE_COMBINATORIAL_MAP_ITEM_H
