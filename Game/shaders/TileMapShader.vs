#version 430

layout(location=0) in vec3 position;
layout(location=1) in vec2 coords;

uniform mat4x4 mvp;
uniform vec2 block_size;
uniform int width;

out vec2 Coords;
out flat int id;

void main(){
	vec3 pos=vec3(position.x+block_size.x*float(gl_InstanceID % width), position.y-block_size.y*float(gl_InstanceID / width), 0.0);
	gl_Position=mvp*vec4(pos,1.0);
	Coords=coords;
	id=gl_InstanceID;
}