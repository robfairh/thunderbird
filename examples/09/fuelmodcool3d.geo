//+
Point(1) = {0, 0, 0, 1.0};
//+
Point(2) = {1, 0, 0, 1.0};
//+
Point(3) = {2, 0, 0, 1.0};
//+
Point(4) = {3, 0, 0, 1.0};
//+
Point(5) = {0, 10, 0, 1.0};
//+
Point(6) = {1, 10, 0, 1.0};
//+
Point(7) = {2, 10, 0, 1.0};
//+
Point(8) = {3, 10, 0, 1.0};
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
Extrude {0, 0, 1} {
  Surface{1}; Surface{2}; Surface{3}; 
}
//+
Physical Surface("fuel_top") = {23};
//+
Physical Surface("moderator_top") = {45};
//+
Physical Surface("coolant_top") = {63};
//+
Physical Surface("fuel_bottom") = {31};
//+
Physical Surface("moderator_bottom") = {53};
//+
Physical Surface("coolant_bottom") = {71};
//+
Physical Volume("fuel") = {1};
//+
Physical Volume("moderator") = {2};
//+
Physical Volume("coolant") = {3};
