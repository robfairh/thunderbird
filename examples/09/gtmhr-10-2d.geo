f=0.01;
H=80*f;
//+
Point(1) = {0*f, 0, 0, 1.0*f};
//+
Point(2) = {1*f, 0, 0, 1.0*f};
//+
Point(3) = {2*f, 0, 0, 1.0*f};
//+
Point(4) = {3*f, 0, 0, 1.0*f};
//+
Point(5) = {0*f, H, 0, 1.0*f};
//+
Point(6) = {1*f, H, 0, 1.0*f};
//+
Point(7) = {2*f, H, 0, 1.0*f};
//+
Point(8) = {3*f, H, 0, 1.0*f};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {5, 6};
//+
Line(5) = {6, 7};
//+
Line(6) = {7, 8};
//+
Line(7) = {1, 5};
//+
Line(8) = {2, 6};
//+
Line(9) = {3, 7};
//+
Line(10) = {4, 8};
//+
Curve Loop(1) = {7, 4, -8, -1};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {8, 5, -9, -2};
//+
Plane Surface(2) = {2};
//+
Curve Loop(3) = {6, -10, -3, 9};
//+
Plane Surface(3) = {3};
//+
Physical Surface("fuel") = {1};
//+
Physical Surface("moderator") = {2};
//+
Physical Surface("coolant") = {3};
//+
Physical Curve("fuel_bottom") = {1};
//+
Physical Curve("moderator_bottom") = {2};
//+
Physical Curve("coolant_bottom") = {3};
//+
Physical Curve("fuel_top") = {4};
//+
Physical Curve("moderator_top") = {5};
//+
Physical Curve("coolant_top") = {6};
