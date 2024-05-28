
#ifdef FRAG_SHADER_INCLUDE
const char* frag_shader_src = R"(


#version 330 core
out vec4 FragColor;
in vec3 position;

void main()
{
   FragColor = vec4(abs(position.x), abs(position.y), abs(position.z), 0.0f);
}


)";
#endif