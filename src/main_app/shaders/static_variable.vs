#version 330 core

layout (location = 0) in vec2 aPos;
uniform mat4 projection;
uniform float translate_y;
uniform float translate_x;
void main() {
    gl_Position = projection * vec4(aPos.x, aPos.y - translate_y, 0.0, 1.0);
}