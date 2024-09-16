#pragma once
#include "IsoscelesTriangle.h"

class Diamond
{
private:
	//members
	Vertex m_left,
		   m_up,
		   m_right,
		   m_down;

public:
	//constructors
	Diamond(const Vertex vertices[4]);
	Diamond(const IsoscelesTriangle& lower);

	//functions
	bool checkLegal(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3) const;

	Vertex getVertex(int index) const;
	double getWidth() const;
	double getHeight() const;

	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
};