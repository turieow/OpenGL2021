#version 450 \n"
layout(location=0) in vec4 inColor;
layout(location=1) in vec2 inTexcoord;
out vec4 fragColor; 
layout(binding=0) uniform sampler2D texColor;
void main() {
  vec4 tc = texture(texColor, inTexcoord); 
  fragColor = inColor * tc; 
} 