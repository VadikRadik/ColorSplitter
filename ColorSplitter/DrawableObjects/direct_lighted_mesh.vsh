#version 330 core

in vec3 pos3d;
in vec3 normal;
in vec3 color;

uniform vec3 lightDir;
uniform mat4 pvm;

out vec4 colors;

void main(void){
   gl_Position = pvm * vec4(pos3d.x, pos3d.y, pos3d.z, 1.0);
   float diff = max(dot(normal, lightDir), 0.0);
   colors = vec4(color*diff,1.0);
}
