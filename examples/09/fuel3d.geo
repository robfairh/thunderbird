//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {0, 10, 0, 1.0};
//+
Point(4) = {1, 10, 0, 1.0};
//+
Line(1) = {1, 2};
//+
Line(2) = {3, 4};
//+
Line(3) = {1, 3};
//+
Line(4) = {2, 4};
//+
Curve Loop(1) = {3, 2, -4, -1};
//+
Plane Surface(1) = {1};
//+
Extrude {0, 0, 1} {
  Surface{1}; Layers{2}; Recombine;
}
//+
Physical Surface("fuel_top") = {17};
//+
Physical Surface("fuel_bottom") = {25};
//+
Physical Volume("fuel") = {1};
