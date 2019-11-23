#pragma once



class Physics
{
public:
	Physics();
	~Physics();

	void CohenSutherlandClip(double x1, double y1, double x2, double y2, vector<glm::vec3>& ret, int& clipDir);
	void SetCohenSutherlandTarget(glm::vec3 min, glm::vec3 max);

private:
	int computeCode(double x, double y);
	// Defining region codes 
	const int INSIDE = 0; // 0000 
	const int LEFT = 1;   // 0001 
	const int RIGHT = 2;  // 0010 
	const int BOTTOM = 4; // 0100 
	const int TOP = 8;    // 1000 

	float x_min;
	float x_max;
	float y_min;
	float y_max;

};

