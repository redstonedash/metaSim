#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    finalColor = fragTexCoord;
    gl_Position = pvm * position;
    vec4 texelColor = texture(texture0, fragTexCoord);
    
    // NOTE: Implement here your fragment shader code
    
    colorOut = vec4(texCoord, 0.0, 0.0);  
}

