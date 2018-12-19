attribute vec4 position;
attribute vec2 textCoordinate;
uniform mat4 rotateMatrix;

varying lowp vec2 varyTextCoord;

void main()
{
    
    // 这里的shader是什么意思呢？？
    varyTextCoord = textCoordinate;
    
    vec4 vPos = position;
    
    vPos = vPos * rotateMatrix;
    
    gl_Position = vPos;
}
