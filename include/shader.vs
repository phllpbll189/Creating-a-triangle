#ifdef VERT_SHADER_INCLUDE
const char* vert_shader_src = R"(


#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 position;

void main()
{
   position = aPos;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}


)";
#endif