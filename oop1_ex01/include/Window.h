#include "Rectangle.h"

class Window
{
private:
	//members
	Vertex m_bottomLeft,
	       m_topRight,
		   m_internalPoint;

public:
	//constructors
	Window(const Rectangle& rectangle, const Vertex& point);
	Window(const Vertex& start, double width, double height, const Vertex& point);

	//functions
	bool checkLegal(double x0, double y0, double x1, double y1, double x2, double y2) const;

	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	Vertex getPoint() const;

	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	double getArea() const;
	double getPerimeter() const;
	Vertex getCenter() const;
	bool scale(double factor);
};