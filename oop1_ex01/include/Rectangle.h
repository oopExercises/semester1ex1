#pragma once

#include "Vertex.h"
#include "Board.h"
#include "macros.h"
#include "Utilities.h"

class Rectangle
{
private:
	//members
	Vertex m_bottomLeft,
		   m_topRight;

public:
	//constructors
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
	Rectangle(const Vertex vertices[2]);
	Rectangle(double x0, double y0, double x1, double y1);
	Rectangle(const Vertex& start, double width, double height);

	//functions
	bool checkLegal(double x0, double y0, double x1, double y1) const;
	void setBottomLeft(double x, double y);
	void setTopRight(double x, double y);
	
	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	double getWidth() const;
	double getHeight() const;

	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
};
