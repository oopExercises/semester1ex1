#pragma once
#include "Rectangle.h"

class IsoscelesTriangle
{
private:
	//members
	Vertex m_left,
		   m_right,
		   m_head;

public:
	//constructors
	IsoscelesTriangle(const Vertex vertices[3]);
	IsoscelesTriangle(const Vertex& left, const Vertex& right, double height);

	//functions
	bool checkLegal(double x0, double y0, double x1, double y1, double x2, double y2) const;

	Vertex getVertex(int index) const;
	double getBaseLength() const;
	double getLegLength() const;
	double getHeight() const;
	
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
};