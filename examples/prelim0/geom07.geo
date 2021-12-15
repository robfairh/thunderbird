SetFactory("OpenCASCADE");

h = 0.5;

Point(1) = {0, 0, 0, h};
Point(2) = {5, 0, 0, h};
Point(3) = {0, 5, 0, h};
Point(4) = {5, 5, 0, h};

Point(5) = {2.3, 0., 0, h};
Point(6) = {2.7, 0., 0, h};
Point(7) = {2.3, 0.5, 0, h};
Point(8) = {2.7, 0.5, 0, h};
Point(9) = {2.3, 1., 0, h};
Point(10) = {2.7, 1., 0, h};
Point(11) = {2.3, 1.5, 0, h};
Point(12) = {2.7, 1.5, 0, h};
Point(13) = {2.3, 2., 0, h};
Point(14) = {2.7, 2., 0, h};

Line(1) = {5, 6};
Line(2) = {6, 8};
Line(3) = {8, 10};
Line(4) = {10, 12};
Line(5) = {12, 14};
Line(6) = {14, 13};
Line(7) = {13, 11};
Line(8) = {11, 9};
Line(9) = {9, 7};
Line(10) = {7, 5};
Line(11) = {7, 8};
Line(12) = {9, 10};
Line(13) = {11, 12};
Line(14) = {6, 2};
Line(15) = {2, 4};
Line(16) = {4, 3};
Line(17) = {3, 1};
Line(18) = {1, 5};

Curve Loop(1) = {10, 1, 2, -11};
Plane Surface(1) = {1};
Curve Loop(2) = {9, 11, 3, -12};
Plane Surface(2) = {2};
Curve Loop(3) = {8, 12, 4, -13};
Plane Surface(3) = {3};
Curve Loop(4) = {7, 13, 5, 6};
Plane Surface(4) = {4};
Curve Loop(5) = {14, 15, 16, 17, 18, -10, -9, -8, -7, -6, -5, -4, -3, -2};
Plane Surface(5) = {5};

Physical Surface("source_0") = {1};
Physical Surface("source_1") = {2};
Physical Surface("source_2") = {3};
Physical Surface("source_3") = {4};
Physical Surface("room") = {5};
Physical Curve("floor") = {18, 14};
Physical Curve("source_floor") = {1};
Physical Curve("left") = {17};
Physical Curve("right") = {15};
Physical Curve("top") = {16};
Physical Curve("source_wall") = {10, 9, 8, 7, 6, 5, 4, 3, 2};
Physical Point("corner") = {1};

// Mesh.CharacteristicLengthFactor = 0.25;
// Mesh.CharacteristicLengthExtendFromBoundary = 2;
// Mesh.CharacteristicLengthFromCurvature = 1;

Transfinite Line{14, 18} = 6;
Transfinite Line{17, 15} = 10;
Transfinite Line{16} = 10;
Transfinite Line{2, 3, 4, 5, 7, 8, 9, 10} = 10;
Transfinite Line{1, 11, 12, 13, 6} = 4;
