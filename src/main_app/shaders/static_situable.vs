#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
out vec3 color;
uniform int active_elem;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y - (0.19 * float(active_elem + 1)), aPos.z, 1.0);
   color = aCol;
}