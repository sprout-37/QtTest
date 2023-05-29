#include "generatemesh.h"
#include "gmsh.h"
#include <set>

GenerateMesh::GenerateMesh(QWidget *parent)
    : QWidget{parent}
{

}

void GenerateMesh::generateMesh()
{
    // Before using any functions in the C++ API, Gmsh must be initialized:
    gmsh::initialize();

    gmsh::model::add("t1");

    double lc = 1e-2;
    gmsh::model::geo::addPoint(0, 0, 0, lc, 1);


    gmsh::model::geo::addPoint(.1, 0, 0, lc, 2);
    gmsh::model::geo::addPoint(.1, .3, 0, lc, 3);

    // If the tag is not provided explicitly, a new tag is automatically created,
    // and returned by the function:
    int p4 = gmsh::model::geo::addPoint(0, .3, 0, lc);


    gmsh::model::geo::addLine(1, 2, 1);
    gmsh::model::geo::addLine(3, 2, 2);
    gmsh::model::geo::addLine(3, p4, 3);
    gmsh::model::geo::addLine(4, 1, p4);


    gmsh::model::geo::addCurveLoop({4, 1, -2, 3}, 1);

    gmsh::model::geo::addPlaneSurface({1}, 1);

    gmsh::model::geo::synchronize();

    // with name "My surface" (with an automatic tag) containing the geometrical
    // surface 1:
    gmsh::model::addPhysicalGroup(1, {1, 2, 4}, 5);
    gmsh::model::addPhysicalGroup(2, {1}, -1, "My surface");

    // We can then generate a 2D mesh...
    gmsh::model::mesh::generate(2);

    // ... and save it to disk
    gmsh::write("t1.msh");


    gmsh::finalize();
}
