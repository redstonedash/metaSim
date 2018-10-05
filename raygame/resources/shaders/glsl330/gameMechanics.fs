#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec2 gl_FragCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables
uniform vec2 mb1;
uniform vec2 mb2;
uniform vec2 mb3;
uniform vec2 mb4;
uniform vec2 mb5;
uniform vec2 mb6;
uniform vec2 mb7;
uniform vec2 mb8;
vec2 metaArr[8] = vec2[8](mb1,mb2,mb3,mb4,mb5,mb6,mb7,mb8);
// NOTE: Render size values must be passed from code
const float renderWidth = 800;
const float renderHeight = 450;
vec2 screenResolution = vec2(renderWidth,renderHeight);
float time = 0;


vec4 getPixelRelative(int x, int y)
{
    return texture(texture0, fragTexCoord + vec2(x/renderWidth,y/renderHeight));
}

vec4 getPixelAt(int x, int y)
{
    return texture(texture0, vec2(x/renderWidth,y/renderHeight));
}

float inverseDistance(vec2 a, vec2 b)
{
    return 1/(distance(a*screenResolution,b*screenResolution)/5);
}

void main()
{
    float brightness = 0.0f;
    for(int i = 0; i<8; i++)
    {
        brightness += inverseDistance(metaArr[i],fragTexCoord);
    }
    if(brightness>0.25){
        brightness=1;
    } else {
        brightness = 0;
    }
    finalColor = getPixelAt(1,1);
    finalColor = vec4(brightness*0.1,brightness*0.6,brightness,1.0f);
}