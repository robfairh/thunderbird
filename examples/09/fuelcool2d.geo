//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {2, 0, 0, 1.0};
//+
Point(4) = {0, 10, 0, 1.0};
//+
Point(5) = {1, 10, 0, 1.0};
//+
Point(6) = {2, 10, 0, 1.0};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {4, 5};
//+
Line(4) = {5, 6};
//+
Line(5) = {1, 4};
//+
Line(6) = {2, 5};
//+
Line(7) = {3, 6};
//+
Curve Loop(1) = {5, 3, -6, -1};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {6, 4, -7, -2};
//+
Plane Surface(2) = {2};
//+
Physical Surface('fuel') = {1};
//+
Physical Surface('coolant') = {2};
//+
Physical Curve("fuel_top") = {3};
//+
Physical Curve("fuel_bottom") = {1};
//+
Physical Curve("coolant_top") = {4};
//+
Physical Curve("coolant_bottom") = {2};
