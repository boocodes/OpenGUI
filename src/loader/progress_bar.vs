#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
out vec3 color;
uniform float progres;
void main()
{
	if(aPos.x < 0)
	{
		gl_Position = vec4(progres, aPos.y, aPos.z, 1.0);  
	}
	else
	{
		gl_Position = vec4(-progres, aPos.y, aPos.z, 1.0);  
	}
    color = aCol;
}