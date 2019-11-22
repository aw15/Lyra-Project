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


float x_intersect(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4)
{
	float num = (x1*y2 - y1 * x2) * (x3 - x4) -
		(x1 - x2) * (x3*y4 - y3 * x4);
	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

// Returns y-value of point of intersectipn of 
// two lines 
float y_intersect(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4)
{
	float num = (x1*y2 - y1 * x2) * (y3 - y4) -
		(y1 - y2) * (x3*y4 - y3 * x4);
	float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	return num / den;
}

// This functions clips all the edges w.r.t one clip 
// edge of clipping area 
void clip(vector<glm::vec2>& poly_points, int& poly_size,
	float x1, float y1, float x2, float y2)
{
	float new_points[20][2];
	int new_poly_size = 0;

	// (ix,iy),(kx,ky) are the co-ordinate values of 
	// the points 
	for (int i = 0; i < poly_size; i++)
	{
		// i and k form a line in polygon 
		int k = (i + 1) % poly_size;
		float ix = poly_points[i][0], iy = poly_points[i][1];
		float kx = poly_points[k][0], ky = poly_points[k][1];

		// Calculating position of first point 
		// w.r.t. clipper line 
		float i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);

		// Calculating position of second point 
		// w.r.t. clipper line 
		float k_pos = (x2 - x1) * (ky - y1) - (y2 - y1) * (kx - x1);

		// Case 1 : When both points are inside 
		if (i_pos < 0 && k_pos < 0)
		{
			//Only second point is added 
			new_points[new_poly_size][0] = kx;
			new_points[new_poly_size][1] = ky;
			new_poly_size++;
		}

		// Case 2: When only first point is outside 
		else if (i_pos >= 0 && k_pos < 0)
		{
			// Point of intersection with edge 
			// and the second point is added 
			new_points[new_poly_size][0] = x_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky);
			new_points[new_poly_size][1] = y_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky);
			new_poly_size++;

			new_points[new_poly_size][0] = kx;
			new_points[new_poly_size][1] = ky;
			new_poly_size++;
		}

		// Case 3: When only second point is outside 
		else if (i_pos < 0 && k_pos >= 0)
		{
			//Only point of intersection with edge is added 
			new_points[new_poly_size][0] = x_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky);
			new_points[new_poly_size][1] = y_intersect(x1,
				y1, x2, y2, ix, iy, kx, ky);
			new_poly_size++;
		}

		// Case 4: When both points are outside 
		else
		{
			//No points are added 
		}
	}


	// Copying new points into original array 
	// and changing the no. of vertices 
	poly_size = new_poly_size;
	for (int i = 0; i < poly_size; i++)
	{
		poly_points[i][0] = new_points[i][0];
		poly_points[i][1] = new_points[i][1];
	}
}

// Implements Sutherland–Hodgman algorithm 
void suthHodgClip(vector<glm::vec2> poly_points, int poly_size,
	vector<glm::vec2>& clipper_points, int clipper_size)
{
	poly_points.resize(20);
	//i and k are two consecutive indexes 
	for (int i = 0; i < clipper_size; i++)
	{
		int k = (i + 1) % clipper_size;

		// We pass the current array of vertices, it's size 
		// and the end points of the selected clipper line 
		clip(poly_points, poly_size, clipper_points[i][0],
			clipper_points[i][1], clipper_points[k][0],
			clipper_points[k][1]);
	}

	// Printing vertices of clipped polygon 
	for (int i = 0; i < poly_size; i++)
		cout << '(' << poly_points[i][0] <<
		", " << poly_points[i][1] << ") ";
}



// Function to calculate the max from a vector of floats 
float max(vector<float> t)
{
	float maximum = INT_MIN;
	for (int i = 0; i < t.size(); i++)
		if (t[i] > maximum)
			maximum = t[i];
	return maximum;
}

// Function to calculate the min from a vector of floats 
float min(vector<float> t)
{
	float minimum = INT_MAX;
	for (int i = 0; i < t.size(); i++)
		if (t[i] < minimum)
			minimum = t[i];
	return minimum;
}

// Cyrus Beck function, returns a pair of values 
// that are then displayed as a line 
bool CyrusBeck(glm::vec2 vertices[],
	glm::vec2 line[], int n, vector<glm::vec2>& result)
{

	// Temporary holder value that will be returned 
	glm::vec2* newPair = new glm::vec2[2];

	// Normals initialized dynamically(can do it statically also, doesn't matter) 
	glm::vec2* normal = new glm::vec2[n];

	// Calculating the normals 
	for (int i = 0; i < n; i++) {
		normal[i].y = vertices[(i + 1) % n].x - vertices[i].x;
		normal[i].x = vertices[i].y - vertices[(i + 1) % n].y;
	}

	// Calculating P1 - P0 
	glm::vec2 P1_P0 = { line[1].x - line[0].x,
			line[1].y - line[0].y};

	// Initializing all values of P0 - PEi 
	glm::vec2* P0_PEi = new glm::vec2[n];

	// Calculating the values of P0 - PEi for all edges 
	for (int i = 0; i < n; i++) {

		// Calculating PEi - P0, so that the 
		// denominator won't have to multiply by -1 
		P0_PEi[i].x
			= vertices[i].x - line[0].y;

		// while calculating 't' 
		P0_PEi[i].y = vertices[i].y - line[0].y;
	}

	int *numerator = new int[n], *denominator = new int[n];

	// Calculating the numerator and denominators 
	// using the dot function 
	for (int i = 0; i < n; i++) {
		numerator[i] = dot(normal[i], P0_PEi[i]);
		denominator[i] = dot(normal[i], P1_P0);
	}

	// Initializing the 't' values dynamically 
	float* t = new float[n];

	// Making two vectors called 't entering' 
	// and 't leaving' to group the 't's 
	// according to their denominators 
	vector<float> tE, tL;

	// Calculating 't' and grouping them accordingly 
	for (int i = 0; i < n; i++) {

		t[i] = (float)(numerator[i]) / (float)(denominator[i]);

		if (denominator[i] > 0)
			tE.push_back(t[i]);
		else
			tL.push_back(t[i]);
	}

	// Initializing the final two values of 't' 
	float temp[2];

	// Taking the max of all 'tE' and 0, so pushing 0 
	tE.push_back(0.f);
	temp[0] = max(tE);

	// Taking the min of all 'tL' and 1, so pushing 1 
	tL.push_back(1.f);
	temp[1] = min(tL);

	// Entering 't' value cannot be 
	// greater than exiting 't' value, 
	// hence, this is the case when the line 
	// is completely outside 
	if (temp[0] > temp[1]) {
		return false;
	}

	// Calculating the coordinates in terms of x and y 
	newPair[0].x
		= (float)line[0].x
		+ (float)P1_P0.x * (float)temp[0];
	newPair[0].y
		= (float)line[0].y
		+ (float)P1_P0.y * (float)temp[0];
	newPair[1].x
		= (float)line[0].x
		+ (float)P1_P0.x * (float)temp[1];
	newPair[1].y
		= (float)line[0].y
		+ (float)P1_P0.y * (float)temp[1];
	cout << '(' << newPair[0].x << ", "
		<< newPair[0].y << ") ("
		<< newPair[1].x << ", "
		<< newPair[1].y << ")";


	delete t;
	delete normal;
	delete newPair;
	delete P0_PEi;

	return true;
}