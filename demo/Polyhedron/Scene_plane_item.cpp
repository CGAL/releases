#include "Scene_plane_item.h"



void Scene_plane_item::initialize_buffers(CGAL::Three::Viewer_interface *viewer) const
{
    program = getShaderProgram(PROGRAM_WITHOUT_LIGHT, viewer);
    program->bind();
    vaos[Facets]->bind();

    buffers[Facets_vertices].bind();
    buffers[Facets_vertices].allocate(positions_quad.data(),
                        static_cast<int>(positions_quad.size()*sizeof(float)));
    program->enableAttributeArray("vertex");
    program->setAttributeBuffer("vertex",GL_FLOAT,0,3);
    buffers[Facets_vertices].release();
    vaos[Facets]->release();


    vaos[Edges]->bind();
    buffers[Edges_vertices].bind();
    buffers[Edges_vertices].allocate(positions_lines.data(),
                        static_cast<int>(positions_lines.size()*sizeof(float)));
    program->enableAttributeArray("vertex");
    program->setAttributeBuffer("vertex",GL_FLOAT,0,3);
    buffers[Edges_vertices].release();
    vaos[Edges]->release();

    program->release();
    are_buffers_filled = true;

}

void Scene_plane_item::compute_normals_and_vertices(void)
{
    positions_quad.resize(0);
    positions_lines.resize(0);

    const double diag = scene_diag();
    //The quad
    {

    positions_quad.push_back(-diag);
    positions_quad.push_back(-diag);
    positions_quad.push_back(0.0);
    positions_quad.push_back(-diag);
    positions_quad.push_back(diag);
    positions_quad.push_back(0.0);
    positions_quad.push_back(diag);
    positions_quad.push_back(-diag);
    positions_quad.push_back(0.0);

    positions_quad.push_back(-diag);
    positions_quad.push_back(diag);
    positions_quad.push_back(0.0);
    positions_quad.push_back(diag);
    positions_quad.push_back(-diag);
    positions_quad.push_back(0.0);
    positions_quad.push_back(diag);
    positions_quad.push_back(diag);
    positions_quad.push_back(0.0);

}
    //The grid
    float x = (2*diag)/10.0;
    float y = (2*diag)/10.0;
    {
        for(int u = 0; u < 11; u++)
        {

            positions_lines.push_back(-diag + x* u);
            positions_lines.push_back(-diag);
            positions_lines.push_back(0.0);

            positions_lines.push_back(-diag + x* u);
            positions_lines.push_back(diag);
            positions_lines.push_back(0.0);
        }
        for(int v=0; v<11; v++)
        {

            positions_lines.push_back(-diag);
            positions_lines.push_back(-diag + v * y);
            positions_lines.push_back(0.0);

            positions_lines.push_back(diag);
            positions_lines.push_back(-diag + v * y);
            positions_lines.push_back(0.0);
        }

    }
}

void Scene_plane_item::draw(CGAL::Three::Viewer_interface* viewer)const
{
    if(!are_buffers_filled)
        initialize_buffers(viewer);
    vaos[Facets]->bind();
    program = getShaderProgram(PROGRAM_WITHOUT_LIGHT);
    attrib_buffers(viewer, PROGRAM_WITHOUT_LIGHT);
    QMatrix4x4 f_matrix;
    for(int i=0; i<16; i++)
        f_matrix.data()[i] = (float)frame->matrix()[i];
    program->bind();
    program->setUniformValue("f_matrix", f_matrix);
    program->setAttributeValue("colors",this->color());
    program->setUniformValue("is_selected", false);
    viewer->glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions_quad.size()/3));
    program->release();
    vaos[Facets]->release();

}

void Scene_plane_item::draw_edges(CGAL::Three::Viewer_interface* viewer)const
{
    if(!are_buffers_filled)
        initialize_buffers(viewer);
    vaos[Edges]->bind();
    program = getShaderProgram(PROGRAM_WITHOUT_LIGHT);
    attrib_buffers(viewer, PROGRAM_WITHOUT_LIGHT);
    QMatrix4x4 f_matrix;
    for(int i=0; i<16; i++)
        f_matrix.data()[i] = (float)frame->matrix()[i];
    program->bind();
    program->setUniformValue("f_matrix", f_matrix);
    program->setAttributeValue("colors",QVector3D(0,0,0));
    viewer->glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(positions_lines.size()/3));
    program->release();
    vaos[Edges]->release();
}
