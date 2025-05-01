#include "shader.hpp"
#include <iostream>

const static char * fragment = R"(

    #version 420 core

    out vec4 FragColor;

    in vec2 Coord;

    uniform vec2 delta;

    void main()
    {
        vec2 c = delta;
        vec2 p = vec2(Coord.xy);

        for(int i = 0 ; i <6 ; i++){
            p = vec2(p.x*p.x -p.y*p.y, 2.0*p.x*p.y);
            p+=c;
        }
        vec2 p1 = p;

        for(int i = 0 ; i <6 ; i++){
            p = vec2(p.x*p.x -p.y*p.y, 2.0*p.x*p.y);
            p+=c;
        }
	vec2 p2 = p;

        for(int i = 0 ; i <6 ; i++){
            p = vec2(p.x*p.x -p.y*p.y, 2.0*p.x*p.y);
            p+=c;
        }
	vec2 p3 = p;
        for(int i = 0 ; i <6 ; i++){
            p = vec2(p.x*p.x -p.y*p.y, 2.0*p.x*p.y);
            p+=c;
        }
	vec2 p4 = p;

        //float value = ((p.x*p.x + p.y*p.y) <= 1) ? 0 : log(p.x*p.x + p.y*p.y);
        float value1 = distance(p1,vec2(0,0));
        float value2 = distance(p2,vec2(0,0));
        float value3 = distance(p3,vec2(0,0));
        float value4 = distance(p4,vec2(0,0));

        value1 = clamp(value1,0.0,1.0);
        value2 = clamp(value2,0.0,1.0);
        value3 = clamp(value3,0.0,1.0);
        value4 = clamp(value4,0.0,1.0);


        gl_FragColor = vec4(value1+value2,value2*value3,value4,1.0);
    }

)";

const static char * vertex = R"(

    #version 420 core
    layout (location = 0) in vec3 aPos;

    out vec2 Coord;

    uniform mat4 transform;


    void main()
    {
        vec4 cord = transform * vec4(aPos, 1.0f);
        gl_Position = vec4(aPos, 1.0f);
        Coord = vec2(cord.x,cord.y);
    }

)";

auto init_shaders() -> GLuint{

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &fragment, NULL);
    glCompileShader(vertex_shader);
    int  success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &vertex, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    auto m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::LINKERROR\n" << info_log << std::endl;
    }

    glUseProgram(m_id);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return m_id;
}
