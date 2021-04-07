#version 330 core
in vec3 pos;
out vec4 FragColor;

void main()
{
    float d = sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    FragColor = vec4(
        (0.2f * pos.x + 0.3f) * d,
        (0.5f * pos.y + 0.3f) * d,
        (0.1f * pos.z + 0.3f) * d,
        1.0f
    );
}