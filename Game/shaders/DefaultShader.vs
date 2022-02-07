#version 430

layout(location=0) in vec3 position;
layout(location=1) in vec2 coords;
uniform mat4 mvp;

out vec2 Coords;

void main(){
	gl_Position=mvp*vec4(position,1.0);
	Coords=coords;
}