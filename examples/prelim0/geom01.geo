SetFactory("OpenCASCADE");

L = 2;   // m
D = 0.5; // m
W = 0.1; // m

h = 0.1;

Point(1) = {0, 0, 0, h};
Point(2) = {0, W, 0, h};
Point(3) = {D, 0, 0, h};
Point(4) = {D, W, 0, h};

Line(1) = {4, 2};
Line(2) = {2, 1};
Line(3) = {1, 3};
Line(4) = {3, 4};

Curve Loop(1) = {3, 4, 1, 2};
Plane Surface(1) = {1};

Transfinite Line{1, 3} = 10;
Transfinite Line{2, 4} = 10;
Transfinite Surface{1};
Recombine Surface{1};

Extrude {0, 0, 1} {
  Surface{1}; 
  Layers{20};
  Recombine;
}

Physical Surface("base") = {1};
Physical Surface("top") = {6};
Physical Surface("front") = {5};
Physical Surface("back") = {3};
Physical Surface("sideL") = {4};
Physical Surface("sideR") = {2};

Physical Volume("vol") = {1};
