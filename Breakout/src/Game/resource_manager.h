#pragma once
#include <map>
#include <string>

#include <glad/glad.h>

#include "texture.h"
#include "shader.h"


class ResourceManager
{
public:
    // ��Դ�洢
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    // ������ɫ��
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // �����Ѿ��������ɫ��
    static Shader    GetShader(std::string name);
    // ��������
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(std::string name);
    // ���·������м��ص���Դ
    static void Clear();
private:
    ResourceManager() { }
    // ���ļ��м��ز�����һ����ɫ��
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    // ���ļ��м�������
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

