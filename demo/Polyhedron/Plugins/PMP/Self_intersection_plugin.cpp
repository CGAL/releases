#include <QApplication>
#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include "opengl_tools.h"
#include "Kernel_type.h"
#include "Polyhedron_type.h"
#include "Scene_polyhedron_item.h"
#include "Scene_polyhedron_selection_item.h"

#include <CGAL/Three/Polyhedron_demo_plugin_helper.h>
#include <CGAL/Three/Polyhedron_demo_plugin_interface.h>

#include <CGAL/intersections.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/box_intersection_d.h>

#include <CGAL/Polygon_mesh_processing/self_intersections.h>
#include <CGAL/Make_triangle_soup.h>

typedef Kernel::Triangle_3 Triangle;
using namespace CGAL::Three;
class Polyhedron_demo_self_intersection_plugin : 
  public QObject,
  public Polyhedron_demo_plugin_helper
{
  Q_OBJECT
  Q_INTERFACES(CGAL::Three::Polyhedron_demo_plugin_interface)
  Q_PLUGIN_METADATA(IID "com.geometryfactory.PolyhedronDemo.PluginInterface/1.0")

public:
  // used by Polyhedron_demo_plugin_helper
  QStringList actionsNames() const {
    return QStringList() << "actionSelfIntersection";
  }

  void init(QMainWindow* mainWindow,
            Scene_interface* scene_interface)
  {
      mw = mainWindow;
      scene = scene_interface;
      actions_map["actionSelfIntersection"] = getActionFromMainWindow(mw, "actionSelfIntersection");
      actions_map["actionSelfIntersection"]->setProperty("subMenuName", "Polygon Mesh Processing");
      autoConnectActions();

  }

  bool applicable(QAction*) const { 
    return qobject_cast<Scene_polyhedron_item*>(scene->item(scene->mainSelectionIndex()));
  }

public Q_SLOTS:
  void on_actionSelfIntersection_triggered();

}; // end Polyhedron_demo_self_intersection_plugin

void Polyhedron_demo_self_intersection_plugin::on_actionSelfIntersection_triggered()
{
  CGAL::Three::Scene_interface::Item_id index = scene->mainSelectionIndex();
  
  Scene_polyhedron_item* item = 
    qobject_cast<Scene_polyhedron_item*>(scene->item(index));

  if(item)
  {
    Polyhedron* pMesh = item->polyhedron();

    // compute self-intersections

    typedef Polyhedron::Facet_handle Facet_handle;
    std::vector<std::pair<Facet_handle, Facet_handle> > facets;
    CGAL::Polygon_mesh_processing::self_intersections
      (*pMesh, std::back_inserter(facets),
      CGAL::Polygon_mesh_processing::parameters::vertex_point_map(get(CGAL::vertex_point, *pMesh)));

    std::cout << "ok (" << facets.size() << " triangle pair(s))" << std::endl;

    // add intersecting triangles as a new polyhedron, i.e., a triangle soup.
    if(!facets.empty())
    {
      Scene_polyhedron_selection_item* selection_item = new Scene_polyhedron_selection_item(item, mw);
      for(std::vector<std::pair<Facet_handle, Facet_handle> >::iterator fb = facets.begin();
        fb != facets.end(); ++fb) {
        selection_item->selected_facets.insert(fb->first);
        selection_item->selected_facets.insert(fb->second);
      }
      selection_item->invalidateOpenGLBuffers();
      selection_item->setName(tr("%1 (selection) (intersecting triangles)").arg(item->name()));
      item->setRenderingMode(Wireframe);
      scene->addItem(selection_item);
      scene->itemChanged(item);
      scene->itemChanged(selection_item);
    }
    else 
      QMessageBox::information(mw, tr("No self intersection"),
                               tr("The polyhedron \"%1\" does not self-intersect.").
                               arg(item->name()));
  }
}

#include "Self_intersection_plugin.moc"
