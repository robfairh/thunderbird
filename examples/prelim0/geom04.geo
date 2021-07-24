SetFactory("OpenCASCADE");

h = 0.5;

Point(1) = {0, 0, 0, h};
Point(2) = {5, 0, 0, h};
Point(3) = {0, 5, 0, h};
Point(4) = {5, 5, 0, h};

Line(1) = {1, 2};
Line(2) = {2, 4};
Line(3) = {4, 3};
Line(4) = {3, 1};

Circle(5) = {2.5, 2.5, 0, 0.5, 0, 2*Pi};

Curve Loop(1) = {1, 2, 3, 4};
Curve Loop(2) = {5};
Plane Surface(1) = {1, 2};

Physical Surface("room") = {1};
Physical Curve("bottom") = {1};
Physical Curve("top") = {3};
Physical Curve("right") = {2};
Physical Curve("left") = {4};
Physical Curve("source_wall") = {5};
Physical Point("corner") = {1};

Mesh.CharacteristicLengthFactor = 0.25;
Mesh.CharacteristicLengthExtendFromBoundary = 2;
Mesh.CharacteristicLengthFromCurvature = 1;

Transfinite Line{1, 2, 4} = 10;
Transfinite Line{3} = 20;
