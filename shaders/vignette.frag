#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;


void main()
{
    //O comando texture � da pr�pria GLSL, e busca a cor do fragmento com a coord de 
    //textura fornecida
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);

    vec4 colorMask = texture(ourTexture2, TexCoord);

    color = mix(color, colorMask, colorMask.a);

    color = vec4(color.rgb, 1.0);
}