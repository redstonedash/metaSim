#version 400

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

// NOTE: Render size values must be passed from code
const float renderWidth = 800;
const float renderHeight = 450;

float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);
float time = 0;


//vec4 getPixel(int x, int y)
//{
//    return texture(texture0, fragTexCoord + vec2(x,y)/renderHeight);
//}
//
//bool isBlack()
//{
//
//}
//
//bool isBlue()
//{
//    
//}
//
//bool isGray()
//{
//    
//}
//
//bool isBarrier()
//{
//    
//}
//
void main()
{
    //if nothing special happens, stay me
    vec3 texelColor = texture(texture0, fragTexCoord + vec2(0,0)/renderHeight, 0.0).rgb;
    //if black is below and im blue, become black
    if(texture(texture0, fragTexCoord + vec2(0,0)/renderHeight).z > 0.78 && texture(texture0, fragTexCoord + vec2(0,-1)/renderHeight).z < 0.1){
        texelColor = vec3(0,0,0);
    }
    //if black and blue is above me become blue
    if(texture(texture0, fragTexCoord + vec2(0,0)/renderHeight).z < 0.1 && texture(texture0, fragTexCoord + vec2(0,1)/renderHeight).z > 0.78){
        texelColor = texture(texture0, fragTexCoord + vec2(0,1)/renderHeight, 0.0).rgb;
    }
    //if blue and barrier is underneath and their is a blankspot either to your left or right
    //if(){
    //    texelColor = vec3(0,0,0)
    //}

    if(texture(texture0, fragTexCoord + vec2(0,0)/renderHeight) == vec4(0,0,0,1)){
        //check for blue on your right with no barier underneath
        //if(texture(texture0, fragTexCoord + vec2(-1,0)/renderHeight).z > 0.78 && texture(texture0, fragTexCoord + vec2(-1,-1)/renderHeight).z < 0.1){
          //texelColor = vec3(1,0,0) ;     
        //}
    }
    finalColor = vec4(texelColor, 1.0);
}