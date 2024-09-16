#include "Rectangle.h"


//in the constructors, first we check if the values that we got are legal or not,
//then if they are legal we put these values in our members, if not then we keep
//the members with their initial values

//constructor that gets two vertexes
//the first vertex is for the bottom left
//the second vertex is for the top right
Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight) : m_bottomLeft(20, 10), m_topRight(30, 20)
{
	if (checkLegal(bottomLeft.m_col, bottomLeft.m_row, topRight.m_col, topRight.m_row))
	{
		m_bottomLeft = bottomLeft;
		m_topRight = topRight;
	}
}

//constructor that gets an array that has two vertexes in its cells
//the first cell has the bottom left vertex, the second has the top right vertex
Rectangle::Rectangle(const Vertex vertices[2]) : m_bottomLeft(20, 10), m_topRight(30, 20)
{
	if (checkLegal(vertices[0].m_col, vertices[0].m_row, vertices[1].m_col, vertices[1].m_row))
	{
		m_bottomLeft = vertices[0];
		m_topRight = vertices[1];
	}
}

//constructor that gets four double numbers
//(x0, y0) the vertex for the bottom left
//(x1, y1) the vertex for the top right
Rectangle::Rectangle(double x0, double y0, double x1, double y1) : m_bottomLeft(20, 10), m_topRight(30, 20)
{
	if (checkLegal(x0, y0, x1, y1))
	{
		m_bottomLeft.m_col = x0;
		m_bottomLeft.m_row = y0;
		m_topRight.m_col = x1;
		m_topRight.m_row = y1;
	}
}

//constructor that gets vertex, the width and the hight of the rectangle
Rectangle::Rectangle(const Vertex& start, double width, double height) : m_bottomLeft(20, 10), m_topRight(30, 20)
{
	if (checkLegal(start.m_col, start.m_row,start.m_col + width, start.m_row + height))
	{
		m_bottomLeft = start;
		m_topRight.m_col = m_bottomLeft.m_col + width;
		m_topRight.m_row = m_bottomLeft.m_row + height;
	}
}

//function that checks if the values that the user inserted are legal
//if yes it returns true, if not it returns false
bool Rectangle::checkLegal(double x0, double y0, double x1, double y1) const
{
	Vertex first, second;
	first.m_col = x0;
	first.m_row = y0;
	second.m_col = x1;
	second.m_row = y1;

	if (first.isValid() && second.isValid()) 
	{
		if ((second.isHigherThan(first) || sameRow(first, second)) && (second.isToTheRightOf(first) || sameCol(first, second)))
		{
			return true;
		}
	}
	return false;

}

//function that sets the vertex of the bottom left
void Rectangle::setBottomLeft(double x, double y)
{
	m_bottomLeft.m_col = x;
	m_bottomLeft.m_row = y;
}

//function that sets the vertex of the top right
void Rectangle::setTopRight(double x, double y)
{
	m_topRight.m_col = x;
	m_topRight.m_row = y;
}

//function that returns the vertex of the bottom left
Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}

//function that returns the vertex of the top right
Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}

//function that returns the width of the rectangle
double Rectangle::getWidth() const
{
	return m_topRight.m_col - m_bottomLeft.m_col;
}

//function that returns the height of the rectangle
double Rectangle::getHeight() const
{
	return m_topRight.m_row - m_bottomLeft.m_row;
}

//function that draws the shape by drawing lines between two vertexes
void Rectangle::draw(Board& board) const
{
	Vertex bottomRight;
	bottomRight.m_col = m_topRight.m_col;
	bottomRight.m_row = m_bottomLeft.m_row;


	Vertex topLeft;
	topLeft.m_col = m_bottomLeft.m_col;
	topLeft.m_row = m_topRight.m_row;

	board.drawLine(m_bottomLeft, bottomRight);
	board.drawLine(bottomRight, m_topRight);
	board.drawLine(m_topRight, topLeft);
	board.drawLine(topLeft, m_bottomLeft);
}

//function that returns the bounding rectangle, in this case it returns the rectangle itself
Rectangle Rectangle::getBoundingRectangle() const
{
	return *this;
}

//function that returns the area of the rectangle
double Rectangle::getArea() const
{
	return (m_topRight.m_col - m_bottomLeft.m_col) * (m_topRight.m_row - m_bottomLeft.m_row);
}

//function that returns the perimeter of the rectangle
double Rectangle::getPerimeter() const
{
	return 2 * ((m_topRight.m_col - m_bottomLeft.m_col) + (m_topRight.m_row - m_bottomLeft.m_row));
}

//function that returns the center of the rectangle
Vertex Rectangle::getCenter() const
{
	Vertex center;
	center.m_col = (m_bottomLeft.m_col + m_topRight.m_col) / 2;
	center.m_row = (m_bottomLeft.m_row + m_topRight.m_row) / 2;

	return center;
}

//function that resizes the shape according to the factor.
//if the factor is not a positive number it won't do anything and reurns false
//if after resizing the shape we get illegal values, then it won't do anything and returns false
bool Rectangle::scale(double factor)
{
	if (factor <= 0)
		return false;

	Vertex center = getCenter();

	double leftDownX, leftDownY, rightUpX, rightUpY;

	leftDownX = center.m_col - factor * (center.m_col - m_bottomLeft.m_col);
	leftDownY = center.m_row - factor * (center.m_row - m_bottomLeft.m_row);
	rightUpX = center.m_col + factor * (m_topRight.m_col - center.m_col);
	rightUpY = center.m_row + factor * (m_topRight.m_row - center.m_row);

	//to check if the new values are legal
	if (!checkLegal(leftDownX, leftDownY, rightUpX, rightUpY))
		return false;
	else
	{
		m_bottomLeft.m_col = leftDownX;
		m_bottomLeft.m_row = leftDownY;
		m_topRight.m_col = rightUpX;
		m_topRight.m_row = rightUpY;

		return true;
	}
}