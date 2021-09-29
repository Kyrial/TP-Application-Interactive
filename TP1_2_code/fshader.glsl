#version 140

uniform sampler2D texture;
uniform sampler2D textureGrass;
uniform sampler2D textureRock;
uniform sampler2D textureSnow;

in vec2 v_texcoord;
in vec3 v_position;
//! [0]
void main()
{
    // Set fragment color from texture
    //gl_FragColor = vec4(1., 1.,1.,1.)*texture2D(texture, v_texcoord);
//     gl_FragColor = vec4(v_position.z, 0.,0.,1.);//*texture2D(texture, v_texcoord);

    if(v_position.z<0.2)
        gl_FragColor = texture2D(textureGrass, v_texcoord);
    if(v_position.z<0.4)
        gl_FragColor = texture2D(textureRock, v_texcoord);
    else
        gl_FragColor = vec4(1., 1.,1.,1.)*texture2D(textureSnow, v_texcoord);

    float pierre = 1.;
    if(v_position.z<0.5)
        pierre = 0.5-v_position.z*1.1;
    else
        pierre = v_position.z*1.1-0.5;

    gl_FragColor = (v_position.z*1.2)*texture2D(textureSnow, v_texcoord)+
            (0.8-v_position.z*1.3)*texture2D(textureGrass, v_texcoord)+
            pierre*texture2D(textureRock, v_texcoord);





}
//! [0]

