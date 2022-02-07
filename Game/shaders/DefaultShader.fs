#version 430

in vec2 Coords;
uniform sampler2D Texture;
uniform vec2 anim_offset;
out vec4 FragColor;

void main(){
    vec2 cord=vec2(Coords.x,1.0 - Coords.y);
    cord+=anim_offset;
    FragColor=texture(Texture,cord);
}