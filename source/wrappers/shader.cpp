#include "shader.hpp"

const char* ShaderProgram::k_vertex_shader_text_ = R"(

    #version 330 core
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

    #version 330 core

   out vec4 FragColor;

in vec2 Coord;

uniform int uniform_iterations;
uniform vec2 uniform_start_point;
uniform vec3 uniform_back_color;
uniform vec3 uniform_front_color;
uniform float uniform_radius;

float min_radius = 1.0/uniform_radius;

void main()
{
   vec2 c = uniform_start_point;
   vec2 p = vec2(Coord.xy);

   int it = 0;
    for(;;it++){
        p = vec2(p.x*p.x -p.y*p.y, 2.0*p.x*p.y);
        p+=c;

       if(distance(p,vec2(0,0)) > uniform_radius || distance(p,vec2(0,0)) < min_radius || uniform_iterations < it) {
           break;
       }
    }

    float value = distance(p,vec2(Coord.xy));

    value = clamp(log(value),0.0,1.0);

    vec3 color = mix(uniform_back_color, uniform_front_color, value);

    FragColor = vec4(color,1.0);
}

)";
