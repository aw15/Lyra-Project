#include "stdafx.h"




void convertDeviceXYOpneglXY(int x, int y, float * ox, float * oy)
{ // 윈도우좌표를 OpenGL좌표로 변환
	int w = WIDTH;
	int h = HEIGHT;
	*ox = (float)((x - (float)w / 2.0)*(float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0)*(float)(1.0 / (float)(h / 2.0)));
}

char * filetobuf(const char * file)
{
	FILE *fptr; long length; char *buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL; fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}

void Print(const glm::vec4 & param, string tag)
{
	std::cout << tag << param.x << " " << param.y << " " << param.z<< " " << param.w  << endl;
}

void Print(const glm::vec3 & param, string tag)
{
	std::cout << tag << param.x << " " << param.y <<" "<<param.z << endl;
}

void Print(const glm::vec2 & param, string tag)
{
	std::cout << tag << param.x << " " << param.y << endl;
}

void stringTokenize(vector<string>& result, string & s, char delim)
{
	string token;
	stringstream ss(s);

	while (getline(ss, token, delim)) {
		result.push_back(token);
	}
}


