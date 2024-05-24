
#ifdef FRAG_SHADER_INCLUDE
const char* frag_shader_src = R"(


#version 330 core
out vec4 FragColor;

uniform vec4 inputColor;

void main()
{
   FragColor = inputColor;
}


)";
#endif