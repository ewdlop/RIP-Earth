import sympy as sp

# Define coordinates
x, y = sp.symbols('x y')

# Define the surface function
z = x**2 + y**2

# Calculate first derivatives
z_x = sp.diff(z, x)
z_y = sp.diff(z, y)

# Calculate second derivatives
z_xx = sp.diff(z_x, x)
z_yy = sp.diff(z_y, y)
z_xy = sp.diff(z_x, y)

# First fundamental form coefficients
E = 1 + z_x**2
F = z_x * z_y
G = 1 + z_y**2

# Second fundamental form coefficients
L = z_xx
M = z_xy
N = z_yy

# Principal curvatures
H = sp.simplify((L + N) / 2)
K = sp.simplify((L * N - M**2) / (E * G - F**2))

# Output the results
print(f"Mean Curvature: {H}")
print(f"Gaussian Curvature (Scalar Curvature): {K}")
