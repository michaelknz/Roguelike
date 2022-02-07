#version 430

in vec2 Coords;
in flat int id;
uniform vec2 offsets[1000];
uniform sampler2D Texture;

out vec4 FragColor;

void main(){
    vec2 tex=vec2(Coords.x+offsets[id].x,1.0-(Coords.y+offsets[id].y));
    FragColor=texture(Texture, tex);
}