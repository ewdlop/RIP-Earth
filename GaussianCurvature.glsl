#version 330 core

in vec3 FragPos; // Position of the current fragment
in vec3 Normal;  // Normal at the current fragment

uniform sampler2D heightMap; // Height map texture
uniform vec2 texelSize;      // Size of a texel in texture coordinates

out vec4 FragColor;

float GaussianCurvature(vec3 pos, vec3 normal) {
    // Compute partial derivatives using central differences
    vec3 dx = vec3(texelSize.x, 0.0, 0.0);
    vec3 dy = vec3(0.0, texelSize.y, 0.0);

    float height = texture(heightMap, pos.xy).r;
    float height_x = texture(heightMap, pos.xy + dx.xy).r;
    float height_y = texture(heightMap, pos.xy + dy.xy).r;
    float height_xx = texture(heightMap, pos.xy + 2.0 * dx.xy).r;
    float height_yy = texture(heightMap, pos.xy + 2.0 * dy.xy).r;
    float height_xy = texture(heightMap, pos.xy + dx.xy + dy.xy).r;

    float E = 1.0 + dot(normal, dx);
    float F = dot(normal, dy);
    float G = 1.0 + dot(normal, dy);

    float L = height_xx;
    float M = height_xy;
    float N = height_yy;

    return (L * N - M * M) / (E * G - F * F);
}

void main() {
    float K = GaussianCurvature(FragPos, Normal);
    FragColor = vec4(vec3(K), 1.0); // Visualize the curvature
}
