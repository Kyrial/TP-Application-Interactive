#version 140

uniform mat4 mvp_matrix;
uniform mat4  transform_Matrix;
in vec4 a_position;
in vec2 a_texcoord;

out vec2 v_texcoord;
out vec3 v_position;

uniform sampler2D texture;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    vec4 color = texture2D(texture, a_texcoord);
    gl_Position = mvp_matrix* transform_Matrix * vec4(a_position.xy, color.x*0.7+a_position.z,1.) ;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    v_position = vec3(a_position.xy, color.x*1.2);
}
//! [0]
