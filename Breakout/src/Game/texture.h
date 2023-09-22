#pragma once

#include <glad/glad.h>


class Texture2D
{
public:
    GLuint ID;
    GLuint Width, Height;
    GLuint Internal_Format;// 格式
    GLuint Image_Format;
    GLuint Wrap_S;// 环绕方式 
    GLuint Wrap_T; 
    GLuint Filter_Min;// 过滤器
    GLuint Filter_Max; 
    Texture2D();
    // 生成纹理
    void Generate(GLuint width, GLuint height, unsigned char* data);
    // 绑定
    void Bind() const;
};
