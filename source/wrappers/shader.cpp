#include "shader.hpp"

const char* ShaderProgram::k_vertex_shader_text_ = R"(

    #version 420 core
    layout (location = 0) in vec3 aPos;

    out vec2 Coord;

    uniform mat4 uniform_transform_matrix;

    void main()
    {
        vec4 cord = uniform_transform_matrix * vec4(aPos, 1.0f);
        gl_Position = vec4(aPos, 1.0f);
        Coord = vec2(cord.x,cord.y);
    }

)";

const char* ShaderProgram::k_fragment_shader_text_ = R"(

    #version 420 core

    out vec4 FragColor;

    in vec2 Coord;

    uniform vec2 uniform_start_point;
    uniform int uniform_iterations;

    void main()
    {
        vec2 c = uniform_start_point;
        vec2 p = vec2(Coord.xy);

        for(int i = 0 ; i < uniform_iterations ; i++){
            p = vec2(p.x*p.x -p.y*p.y, 2.0*p.x*p.y);
            p+=c;
        }

        float value = distance(p,vec2(0,0));

        value = clamp(value,0.0,1.0);

        FragColor = vec4(value,value,value,1.0);
    }

)";
