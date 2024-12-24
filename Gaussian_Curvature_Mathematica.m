(* Define the variables *)
x = Symbol["x"];
y = Symbol["y"];

(* Define the surface function *)
z = x^2 + y^2;

(* Calculate the first partial derivatives *)
z_x = D[z, x];
z_y = D[z, y];

(* Calculate the second partial derivatives *)
z_xx = D[z_x, x];
z_yy = D[z_y, y];
z_xy = D[z_x, y];

(* First fundamental form coefficients *)
E = 1 + z_x^2;
F = z_x * z_y;
G = 1 + z_y^2;

(* Second fundamental form coefficients *)
L = z_xx;
M = z_xy;
N = z_yy;

(* Calculate the Gaussian curvature *)
K = Simplify[(L * N - M^2) / (E * G - F^2)];

Print["Gaussian Curvature: ", K];
