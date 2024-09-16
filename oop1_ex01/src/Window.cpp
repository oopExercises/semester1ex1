#include "Window.h"

//in the constructors, first we check if the values that we got are legal or not,
//then if they are legal we put these values in our members, if not then we keep
//the members with their initial values

//constructor that gets a rectangle and an internal point
Window::Window(const Rectangle& rectangle, const Vertex& point) : m_bottomLeft(20,10), m_topRight(30,20), m_internalPoint(25,15)
{
	double downLeftX = rectangle.getBottomLeft().m_col;
	double downLeftY = rectangle.getBottomLeft().m_row;
	double upRightX = rectangle.getTopRight().m_col;
	double upRightY = rectangle.getTopRight().m_row;

	if (checkLegal(downLeftX, downLeftY, upRightX, upRightY, point.m_col, point.m_row))
	{
		m_bottomLeft.m_col = downLeftX;
		m_bottomLeft.m_row = downLeftY;
		m_topRight.m_col = upRightX;
		m_topRight.m_row = upRightY;
		m_internalPoint = point;
	}
}

//constructor that gets the bottom left of the rectangle, its width and height, an internal point
Window::Window(const Vertex& start, double width, double height, const Vertex& point) : m_bottomLeft(20, 10), m_topRight(30, 20), m_internalPoint(25, 15)
{

	if (checkLegal(start.m_col, start.m_row, start.m_col + width, start.m_row + height, point.m_col, point.m_row))
	{
		m_bottomLeft = start;
		m_topRight = start;
		m_internalPoint = point;
	}
}

//function that checks if the values that the user inserted are legal
//if yes it returns true, if not it returns false
bool Window::checkLegal(double x0, double y0, double x1, double y1, double x2, double y2) const
{
	Vertex first, second, third;
	first.m_col = x0;
	first.m_row = y0;
	second.m_col = x1;
	second.m_row = y1;
	third.m_col = x2;
	third.m_row = y2;

	if (first.isValid() && second.isValid() && third.isValid())
	{
		if ((second.isToTheRightOf(first) || sameCol(first, second)) && (second.isHigherThan(first) || sameRow(first, second)))
		{
			if ((third.isToTheRightOf(first) || sameCol(first, third)) && (second.isToTheRightOf(third) || sameCol(second, third)))
			{
				if ((third.isHigherThan(first) || sameRow(first, third)) && (second.isHigherThan(third) || sameRow(second, third)))
				{
					return true;
				}

			}

		}
	}
	return false;
}

//function that returns the bottom left 
Vertex Window::getBottomLeft() const
{
	return m_bottomLeft;
}

//function that returns the top right
Vertex Window::getTopRight() const
{
	return m_topRight;
}

//function that returns the internal point
Vertex Window::getPoint() const 
{
	return m_internalPoint;
}

//function that draws the shape by drawing lines between two vertexes
void Window::draw(Board& board) const
{
	//these variables are for the lines that cross the internal point
	Vertex left, up, right, down;

	Rectangle rect(m_bottomLeft, m_topRight);
	rect.draw(board);

	left.m_col = m_bottomLeft.m_col;
	left.m_row = m_internalPoint.m_row;

	up.m_col = m_internalPoint.m_col;
	up.m_row = m_topRight.m_row;

	right.m_col = m_topRight.m_col;
	right.m_row = m_internalPoint.m_row;

	down.m_col = m_internalPoint.m_col;
	down.m_row = m_bottomLeft.m_row;

	board.drawLine(left, right);
	board.drawLine(up, down);
}

//function that returns the bounding rectangle, in this case it returns the rectangle itself without the point
Rectangle Window::getBoundingRectangle() const
{
	Rectangle rect(m_bottomLeft.m_col, m_bottomLeft.m_row, m_topRight.m_col, m_topRight.m_row);
	return rect;
}

//function that returns the area of the window
double Window::getArea() const
{
	return (m_topRight.m_col - m_bottomLeft.m_col) * (m_topRight.m_row - m_bottomLeft.m_row);
}

//function that returns the perimeter of the window
double Window::getPerimeter() const
{
	return 2 * ((m_topRight.m_col - m_bottomLeft.m_col) + (m_topRight.m_row - m_bottomLeft.m_row));
}

//function that returns the center of the window
Vertex Window::getCenter() const
{
	Vertex center;
	center.m_col = (m_bottomLeft.m_col + m_topRight.m_col) / 2;
	center.m_row = (m_bottomLeft.m_row + m_topRight.m_row) / 2;

	return center;
}

//function that resizes the shape according to the factor.
//if the factor is not a positive number it won't do anything and reurns false
//if after resizing the shape we get illegal values, then it won't do anything and returns false
bool Window::scale(double factor)
{
	if (factor <= 0)
		return false;

	Vertex center = getCenter();

	//scale the corners of the window
	/*double leftDownX, leftDownY, rightUpX, rightUpY;*/

	Rectangle rect(m_bottomLeft, m_topRight);
	rect.scale(factor);
	m_bottomLeft = rect.getBottomLeft();
	m_topRight = rect.getTopRight();
	
	//scale the internal point
	double pointX, pointY, Xdif, Ydif;
	Xdif = abs(center.m_col - m_internalPoint.m_col);
	Ydif = abs(center.m_row - m_internalPoint.m_row);
	
	//first quarter 
	if ((m_internalPoint.isHigherThan(center) || sameRow(m_internalPoint, center)) &&
		(m_internalPoint.isToTheRightOf(center) || sameCol(center, m_internalPoint)))
	{
		pointX = center.m_col + factor * Xdif;
		pointY = center.m_row + factor * Ydif;
	}

	//second quarter
	else if (m_internalPoint.isHigherThan(center) && center.isToTheRightOf(m_internalPoint))
	{
		pointX = center.m_col - factor * Xdif;
		pointY = center.m_row + factor * Ydif;
	}

	//third quarter
	else if ((center.isHigherThan(m_internalPoint) || sameRow(m_internalPoint, center))&& 
		(center.isToTheRightOf(m_internalPoint) || sameCol(center, m_internalPoint)))
	{
		pointX = center.m_col - factor * Xdif;
		pointY = center.m_row - factor * Ydif;
	}

	//fourth quarter
	else if (center.isHigherThan(m_internalPoint) && m_internalPoint.isToTheRightOf(center))
	{
		pointX = center.m_col + factor * Xdif;
		pointY = center.m_row - factor * Ydif;
	}

		m_internalPoint.m_col = pointX;
		m_internalPoint.m_row = pointY;

	if (!rect.checkLegal(m_bottomLeft.m_col, m_bottomLeft.m_row, m_topRight.m_col, m_topRight.m_row))
		return false;

	return true;
}
