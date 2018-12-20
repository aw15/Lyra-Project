#pragma once

#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#define MAX_TEXTURES 200

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void DrawSolidRect(Vector3D& pos, float size, Color& color, float level);
	void DrawSolidRectXY(Vector3D& pos, float width, float height, Color& color, float level);
	void DrawSolidRectGauge(Vector3D& pos, float width, float height, Color& color, float gauge, float level);
	void DrawTexturedRectXY(Vector3D& pos, float sizeX, float sizeY, Color& color, GLuint texID, float level);
	void DrawTexturedRectSeqXY(Vector3D& pos, float sizeX, float sizeY, Color& color, GLuint texID, int currSeqX, int currSeqY, int totalSeqX, int totalSeqY, float level);
	void DrawTexturedRect(Vector3D& pos, float size, Color& color, GLuint texID, float level);
	void DrawTexturedRectSeq(Vector3D& pos, float size, Color& color, GLuint texID, int currSeqX, int currSeqY, int totalSeqX, int totalSeqY, float level);
	void DrawParticle(Vector3D& pos, float size, Color& color, float gDirX, float gDirY, GLuint texID, float timeInSeconds, float level);
	void DrawParticleClimate(Vector3D& pos, float size, Color& color, float gDirX, float gDirY, GLuint texID, float timeInSeconds, float level);
	void DrawText(Vector2D& pos, void* font, Color& color, char* text);

	void SetSceneTransform(Vector2D& pos, float scaleX, float scaleY);
	void DrawBorderXY(float x, float y, float z, float width, float height, float r, float g, float b, float a, float level);

	unsigned char * loadBMPRaw(const char * imagepath, unsigned int& outWidth, unsigned int& outHeight, bool flipY);

	void CreatePngTexture(char * filePath, const char* name);
	GLuint CreateBmpTexture(char * filePath, const char* name);
	GLuint GetTexture(const char* name);

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void CreateParticleVBO();
	void CreateParticleCloudVBO();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void ReleaseAllResources();

	bool m_Initialized = false;

	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_VBORectTex = 0;
	GLuint m_VBORectBorder = 0;
	GLuint m_VBOParticles = 0;
	GLuint m_VBOParticleCloud = 0;

	GLuint m_SolidRectShader = 0;
	GLuint m_SolidRectGaugeShader = 0;
	GLuint m_SolidRectXYShader = 0;
	GLuint m_SolidRectWithTextureShader = 0;
	GLuint m_SolidRectWithTextureSeqShader = 0;
	GLuint m_ParticleWithTextureShader = 0;

	float m_sceneTransX = 0;
	float m_sceneTransY = 0;
	float m_sceneScaleX = 1;
	float m_sceneScaleY = 1;

	//GLuint m_textureList[MAX_TEXTURES];
	unordered_map<string, GLuint> m_textureList;


	int m_ParticleCount;
	int m_ParticleVertexCount;
	int m_ParticleCloudCount;
	int m_ParticleCloudVertexCount;
};

