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

    double lc = 10;
    double u = 1;
    double l_contact = 10;

    // definition of point
    gmsh::model::geo::addPoint(109.75 *u, 240.849 *u, 0 *u, lc, 64);
    gmsh::model::geo::addPoint(109.75 *u, 201.98 *u, 0 *u, lc, 10);
    gmsh::model::geo::addPoint(109.75 *u, 132.905 *u, 0 *u, lc, 63);
    gmsh::model::geo::addPoint(109.75 *u, 131.595 *u, 0 *u, lc, 11);
    gmsh::model::geo::addPoint(109.75 *u, 4.10229 *u, 0 *u, lc, 13);
    gmsh::model::geo::addPoint(109.75 *u, -66.2823 *u, 0 *u, lc, 12);
    gmsh::model::geo::addPoint(103.779 *u, 131.849 *u, 0 *u, lc, 1);
    gmsh::model::geo::addPoint(103.779 *u, 3.84862 *u, 0 *u, lc, 4);
    gmsh::model::geo::addPoint(91.4581 *u, 239.849 *u, 0 *u, lc, 32);
    gmsh::model::geo::addPoint(91.4581 *u, 231.208 *u, 0 *u, lc, 33);
    gmsh::model::geo::addPoint(90.4581 *u, 240.849 *u, 0 *u, lc, 31);
    gmsh::model::geo::addPoint(88.7786 *u, 221.208 *u, 0 *u, lc, 35);
    gmsh::model::geo::addPoint(85.2231 *u, 240.849 *u, 0 *u, lc, 30);
    gmsh::model::geo::addPoint(85.2231 *u, 237.846 *u, 0 *u, lc, 29);
    gmsh::model::geo::addPoint(82.2205 *u, 237.846 *u, 0 *u, lc, 28);
    gmsh::model::geo::addPoint(82.2205 *u, 229.849 *u, 0 *u, lc, 27);
    gmsh::model::geo::addPoint(79.7038 *u, 205.49 *u, 0 *u, lc, 36);
    gmsh::model::geo::addPoint(79.541 *u, 221.208 *u, 0 *u, lc, 25);
    gmsh::model::geo::addPoint(73.8479 *u, 211.347 *u, 0 *u, lc, 24);
    gmsh::model::geo::addPoint(73.7667 *u, 170.999 *u, 0 *u, lc, 59);
    gmsh::model::geo::addPoint(73.7675 *u, 149.693 *u, 0 *u, lc, 41);
    gmsh::model::geo::addPoint(73.7675 *u, 135.905 *u, 0 *u, l_contact, 40);
    gmsh::model::geo::addPoint(72.3823 *u, 198.171 *u, 0 *u, lc, 15);
    gmsh::model::geo::addPoint(71.4581 *u, 231.208 *u, 0 *u, lc, 34);
    gmsh::model::geo::addPoint(70.7745 *u, 135.898 *u, 0 *u, lc, 58);
    gmsh::model::geo::addPoint(70.7815 *u, 132.905 *u, 0 *u, l_contact, 57);
    gmsh::model::geo::addPoint(70.2497 *u, 151.309 *u, 0 *u, lc, 60);
    gmsh::model::geo::addPoint(68.8946 *u, 143.723 *u, 0 *u, lc, 62);
    gmsh::model::geo::addPoint(68.3549 *u, 178.999 *u, 0 *u, lc, 61);
    gmsh::model::geo::addPoint(62.3833 *u, 215.49 *u, 0 *u, lc, 37);
    gmsh::model::geo::addPoint(61.2665 *u, 191.753 *u, 0 *u, lc, 14);
    gmsh::model::geo::addPoint(61.1942 *u, 231.633 *u, 0 *u, lc, 26);
    gmsh::model::geo::addPoint(60.8606 *u, 218.845 *u, 0 *u, lc, 23);
    gmsh::model::geo::addPoint(60.8606 *u, 203.849 *u, 0 *u, lc, 22);
    gmsh::model::geo::addPoint(59.7675 *u, 215.849 *u, 0 *u, lc, 20);
    gmsh::model::geo::addPoint(59.7675 *u, 203.849 *u, 0 *u, lc, 21);
    gmsh::model::geo::addPoint(53.7655 *u, 178.761 *u, 0 *u, lc, 39);
    gmsh::model::geo::addPoint(53.7655 *u, 170.999 *u, 0 *u, lc, 38);
    gmsh::model::geo::addPoint(47.7675 *u, 229.849 *u, 0 *u, lc, 18);
    gmsh::model::geo::addPoint(47.7675 *u, 215.849 *u, 0 *u, lc, 19);
    gmsh::model::geo::addPoint(19.75 *u, 229.348 *u, 0 *u, lc, 17);
    gmsh::model::geo::addPoint(18.5317 *u, 194.461 *u, 0 *u, lc, 16);
    gmsh::model::geo::addPoint(16.6231 *u, 182.417 *u, 0 *u, lc, 53);
    gmsh::model::geo::addPoint(9.26749 *u, 131.849 *u, 0 *u, l_contact, 2);
    gmsh::model::geo::addPoint(9.26749 *u, 3.84862 *u, 0 *u, lc, 3);
    gmsh::model::geo::addPoint(7.17018 *u, 149.47 *u, 0 *u, lc, 54);
    gmsh::model::geo::addPoint(6.96495 *u, 131.443 *u, 0 *u, lc, 5);
    gmsh::model::geo::addPoint(6.96495 *u, 4.25462 *u, 0 *u, lc, 6);
    gmsh::model::geo::addPoint(6.76749 *u, 135.599 *u, 0 *u, lc, 42);
    gmsh::model::geo::addPoint(6.76749 *u, 132.849 *u, 0 *u, lc, 43);
    gmsh::model::geo::addPoint(6.76749 *u, 130.9 *u, 0 *u, lc, 7);
    gmsh::model::geo::addPoint(6.76749 *u, 67.8486 *u, 0 *u, lc, 9);
    gmsh::model::geo::addPoint(6.76749 *u, 4.79715 *u, 0 *u, lc, 8);
    gmsh::model::geo::addPoint(6.51749 *u, 135.849 *u, 0 *u, lc, 45);
    gmsh::model::geo::addPoint(6.51749 *u, 135.599 *u, 0 *u, lc, 44);
    gmsh::model::geo::addPoint(3.81749 *u, 135.849 *u, 0 *u, lc, 46);
    gmsh::model::geo::addPoint(3.81749 *u, 135.599 *u, 0 *u, lc, 47);
    gmsh::model::geo::addPoint(3.56749 *u, 135.599 *u, 0 *u, lc, 48);
    gmsh::model::geo::addPoint(3.56749 *u, 133.099 *u, 0 *u, lc, 49);
    gmsh::model::geo::addPoint(2.36408 *u, 150.849 *u, 0 *u, lc, 56);
    gmsh::model::geo::addPoint(2.36408 *u, 145.849 *u, 0 *u, lc, 52);
    gmsh::model::geo::addPoint(-1.23251 *u, 145.849 *u, 0 *u, lc, 51);
    gmsh::model::geo::addPoint(-1.23251 *u, 133.099 *u, 0 *u, lc, 50);
    gmsh::model::geo::addPoint(-31.4378 *u, 196.206 *u, 0 *u, lc, 55);

    // definition of Line
    gmsh::model::geo::addLine(1, 2, 1);
    gmsh::model::geo::addLine(3, 4, 2);
    gmsh::model::geo::addLine(2, 5, 3);
    gmsh::model::geo::addLine(6, 3, 4);
    gmsh::model::geo::addLine(5, 7, 5);
    gmsh::model::geo::addLine(8, 6, 6);
    gmsh::model::geo::addLine(9, 7, 7);
    gmsh::model::geo::addLine(8, 9, 8);
    gmsh::model::geo::addLine(14, 15, 11);
    gmsh::model::geo::addLine(16, 17, 12);
    gmsh::model::geo::addLine(17, 18, 13);
    gmsh::model::geo::addLine(19, 18, 14);
    gmsh::model::geo::addLine(21, 22, 16);
    gmsh::model::geo::addLine(24, 25, 18);
    gmsh::model::geo::addLine(27, 28, 20);
    gmsh::model::geo::addLine(30, 31, 22);
    gmsh::model::geo::addLine(31, 32, 23);
    gmsh::model::geo::addLine(33, 32, 24);
    gmsh::model::geo::addLine(36, 35, 26);
    gmsh::model::geo::addLine(38, 39, 28);
    gmsh::model::geo::addLine(40, 41, 29);
    gmsh::model::geo::addLine(42, 43, 30);
    gmsh::model::geo::addLine(46, 45, 32);
    gmsh::model::geo::addLine(49, 48, 34);
    gmsh::model::geo::addLine(50, 49, 35);
    gmsh::model::geo::addLine(51, 50, 36);
    gmsh::model::geo::addLine(51, 52, 37);
    gmsh::model::geo::addLine(53, 54, 38);
    gmsh::model::geo::addLine(43, 57, 41);
    gmsh::model::geo::addLine(11, 13, 46);
    gmsh::model::geo::addLine(18, 27, 47);
    gmsh::model::geo::addLine(57, 63, 48);
    gmsh::model::geo::addLine(31, 64, 49);
    gmsh::model::geo::addLine(63, 64, 50);

    // definition of circle
    gmsh::model::geo::addCircleArc(1, 10, 11, 9);
    gmsh::model::geo::addCircleArc(13, 12, 4, 10);
    gmsh::model::geo::addCircleArc(19, 20, 21, 15);
    gmsh::model::geo::addCircleArc(22, 23, 24, 17);
    gmsh::model::geo::addCircleArc(25, 26, 27, 19);
    gmsh::model::geo::addCircleArc(30, 29, 28, 21);
    gmsh::model::geo::addCircleArc(35, 34, 33, 25);
    gmsh::model::geo::addCircleArc(15, 37, 36, 27);
    gmsh::model::geo::addCircleArc(42, 44, 45, 31);
    gmsh::model::geo::addCircleArc(46, 47, 48, 33);
    gmsh::model::geo::addCircleArc(53, 55, 16, 39);
    gmsh::model::geo::addCircleArc(52, 56, 54, 40);
    gmsh::model::geo::addCircleArc(57, 58, 40, 42);
    gmsh::model::geo::addCircleArc(38, 59, 60, 43);
    gmsh::model::geo::addCircleArc(14, 61, 39, 44);
    gmsh::model::geo::addCircleArc(41, 62, 60, 45);


    // add curve loop
    gmsh::model::geo::addCurveLoop({7, -5, -3, -1, 9, 46, 10, -2, -4, -6, 8}, 1);
    // add plane surface
    gmsh::model::geo::addPlaneSurface({1}, 1);

    gmsh::model::geo::addCurveLoop({38, -40, -37, 36, 35, 34, -33, 32, -31, 30, 41, 42, 29, 45, -43, 28, -44,
                                    11, 27, 26, 25, 24, -23, -22, 21, -20, -19, -18, -17, -16, -15, 14, -13, -12, -39}, 2);

    gmsh::model::geo::addPlaneSurface({2}, 2);

    gmsh::model::geo::addCurveLoop({47, -19, -18, -17, -16, -15, 14}, 3);

    gmsh::model::geo::addPlaneSurface({3}, 3);

    gmsh::model::geo::addCurveLoop({50, -49, 23, -24, -25, -26, -27, -11, 44, -28, 43, -45, -29, -42, 48}, 4);

    gmsh::model::geo::addPlaneSurface({4}, 4);

    // Create relevant Gmsh data structures,CAD entities must be synchronized with the Gmsh model
    gmsh::model::geo::synchronize();

    // Add Physical Properties of Line Segments
    gmsh::model::addPhysicalGroup(1, {13}, 51, "piston_top");
    gmsh::model::addPhysicalGroup(1, {41, 42}, 52, "piston_bottom");
    gmsh::model::addPhysicalGroup(1, {2}, 53, "pin_bottom");
    gmsh::model::addPhysicalGroup(1, {46}, 54, "pin_center");
    gmsh::model::addPhysicalGroup(1, {50}, 55, "piston_center");
    gmsh::model::addPhysicalGroup(1, {1, 3, 5}, 56, "pin_top");
    gmsh::model::addPhysicalGroup(1, {47, 20, 21, 22, 49}, 59, "piston_top1");

    // Add physical properties to faces
    gmsh::model::addPhysicalGroup(2, {2, 4, 3}, 57, "piston");
    gmsh::model::addPhysicalGroup(2, {1}, 58, "pin");

    // Apply Curve Slicing Constraints
    gmsh::model::geo::mesh::setTransfiniteCurve(41, 35, "Progression", 1);
    gmsh::model::geo::mesh::setTransfiniteCurve(1, 50, "Progression", 1);
    gmsh::model::geo::mesh::setTransfiniteCurve(3, 1, "Progression", 1);
    gmsh::model::geo::mesh::setTransfiniteCurve(5, 1, "Progression", 1);

    // generate a quadrilateral mesh
    gmsh::option::setNumber("Mesh.RecombineAll", 1); // 对应于Recombine all triangular meshes选项
    gmsh::option::setNumber("Mesh.RecombinationAlgorithm", 1); // 对应于2D recombination algorithm 的Blossoom
    gmsh::option::setNumber("Mesh.SubdivisionAlgorithm", 1); // 对应于 subdivision algorithm 的 All Quads
    gmsh::option::setNumber("Mesh.Algorithm", 8); // 对应于2D algptithm 的Frontal-Delaunay for quads

    gmsh::model::geo::synchronize();

    // We can then generate a 2D mesh...
    gmsh::model::mesh::generate(2);

    // ... and save it to disk
    gmsh::write("t1.msh");

    gmsh::finalize();
}
