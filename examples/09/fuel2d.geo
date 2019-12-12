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
Physical Surface('fuel') = {1};
//+
Physical Curve("fuel_bottom") = {1};
//+
Physical Curve("fuel_top") = {2};
