#pragma once
#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"


class ResourceManager
{
public:
    // 资源存储
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    // 加载着色器
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // 检索已经储存的着色器
    static Shader    GetShader(std::string name);
    // 加载纹理
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(std::string name);
    // 重新分配所有加载的资源
    static void Clear();
private:
    ResourceManager() { }
    // 从文件中加载并生成一个着色器
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // 从文件中加载纹理
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

