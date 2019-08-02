H = 10;
lc = 1;

Point(1) = {0, 0, 0, lc};
Point(2) = {H, 0, 0, lc};
Point(3) = {0, H, 0, lc};
Point(4) = {H, H, 0, lc};

// front bottom
Line(1) = {2, 1};
// front left
Line(2) = {1, 3};
// front top
Line(3) = {3, 4};
// front right
Line(4) = {4, 2};
//+
Physical Curve("top") = {3};
//+
Physical Curve("bottom") = {1};
//+
Curve Loop(1) = {3, 4, 1, 2};
//+
Plane Surface(1) = {1};
//+
Physical Surface("square") = {1};
