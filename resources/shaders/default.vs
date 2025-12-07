#version 330 core
layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为0
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;
uniform mat4 projection;
uniform mat4 view;

void main()
{   
    // 应用矩阵
    gl_Position = projection * view * vec4(aPos, 1.0);

    // 传递纹理坐标
    texCoord = aTexCoord;
}