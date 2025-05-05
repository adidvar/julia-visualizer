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

    void main()
    {
        vec2 c = uniform_start_point;
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


        FragColor = vec4(value1+value2,value2*value3,value4,1.0);
    }

)";
