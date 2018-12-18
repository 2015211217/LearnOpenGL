attribute vec4 position;
attribute vec2 textCoordinate;

varying lowp vec2 varyTextCoord;
varying lowp vec2 varyOtherPostion;

// 着色器语言
void main()
{
    varyTextCoord = textCoordinate;
    varyOtherPostion = position.xy;
    
    gl_Position = position;
}
