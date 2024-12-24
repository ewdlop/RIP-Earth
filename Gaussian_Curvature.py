from sympy import symbols, diff, Matrix, simplify

# Define the variables
x, y = symbols('x y')

# Define the surface function z = f(x, y)
z = x**2 + y**2

# Calculate the first partial derivatives
z_x = diff(z, x)
z_y = diff(z, y)

# Calculate the second partial derivatives
z_xx = diff(z_x, x)
z_yy = diff(z_y, y)
z_xy = diff(z_x, y)

# First fundamental form coefficients
E = 1 + z_x**2
F = z_x * z_y
G = 1 + z_y**2

# Second fundamental form coefficients
L = z_xx
M = z_xy
N = z_yy

# Calculate the Gaussian curvature
numerator = L * N - M**2
denominator = E * G - F**2
K = simplify(numerator / denominator)

print(f'Gaussian Curvature: {K}')
