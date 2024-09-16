#include "IsoscelesTriangle.h"
#include <cmath>

//in the constructors, first we check if the values that we got are legal or not,
//then if they are legal we put these values in our members, if not then we keep
//the members with their initial values

//constructor that gets an array that has 3 vertexes in its cells
//the first vertex is for the left 
//the second vertex is for the head
//the third vertex is for the right
IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3]) : m_left(20, 20), m_head(25, 25), m_right(30, 20)
{
	if (checkLegal(vertices[0].m_col, vertices[0].m_row, vertices[1].m_col, vertices[1].m_row, vertices[2].m_col, vertices[2].m_row))
	{
		m_left = vertices[0];
		m_head = vertices[1];
		m_right = vertices[2];
	}
}

//constructor that gets two vertexes and the hight of the triangle
//the first vertex is for the left
//the second vertex is for the right
//the hight helps us to know the vertex of the head
IsoscelesTriangle::IsoscelesTriangle(const Vertex& left, const Vertex& right, double height) : m_left(20, 20), m_head(25, 25), m_right(30, 20)
{
	Vertex top;
	top.m_col = (left.m_col + right.m_col) / 2;
	top.m_row = left.m_row + height;

	if (checkLegal(left.m_col, left.m_row, top.m_col, top.m_row, right.m_col, right.m_row))
	{
		m_left = left;
		m_head = top;
		m_right = right;
	}

}

//function that checks if the values that the user inserted are legal
//if yes it returns true, if not it returns false
bool IsoscelesTriangle::checkLegal(double x0, double y0, double x1, double y1, double x2, double y2) const
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
		if ((second.isToTheRightOf(first) || sameCol(first, second)) && (third.isToTheRightOf(second) || sameCol(second, third)))
		{
			if (sameRow(first, third))
			{
				double middle = ((x0 + x2) / 2);
				if (doubleEqual(middle, x1))
					return true;
			}

		}
	}

	return false;
}

//function that returns a vertex according to the index
// 0 : the left 
// 1 : the head
// 2 : the right
Vertex IsoscelesTriangle::getVertex(int index) const
{
	Vertex point;

	if (index == 0)
	{
		point = m_left;
	}
	else if (index == 1)
	{
		point = m_head;
	}
	else if (index == 2)
	{
		point = m_right;
	}
	return point;
}

//function that returns the base length
double IsoscelesTriangle::getBaseLength() const
{
	return m_right.m_col - m_left.m_col;
}

//function that returns the leg length
double IsoscelesTriangle::getLegLength() const
{
	return distance(m_head, m_left);
}

//function that returns the height
double IsoscelesTriangle::getHeight() const
{
	return abs(m_head.m_row - m_left.m_row);
}

//function that draws the shape by drawing lines between two vertexes
void IsoscelesTriangle::draw(Board& board) const
{
	board.drawLine(m_left, m_right);
	board.drawLine(m_right, m_head);
	board.drawLine(m_head, m_left);
}

//function that returns the bounding rectangle
Rectangle IsoscelesTriangle::getBoundingRectangle() const
{
	//we gave the rectangle values because all the constructors in the rectangle have parameters
	//but if we have a constructor that don't get any parameters then we should leave the object
	//rect without values.
	Rectangle rect(1.0, 2.0, 3.0, 4.0);

	//check if the head is up
	if (m_head.isHigherThan(m_left) || sameRow(m_head, m_left))
	{
		rect.setBottomLeft(m_left.m_col, m_left.m_row);
		rect.setTopRight(m_right.m_col, m_head.m_row);
	}

	//check if the head is down
	else if (m_left.isHigherThan(m_head))
	{
		rect.setBottomLeft(m_left.m_col, m_head.m_row);
		rect.setTopRight(m_right.m_col, m_right.m_row);
	}
	return rect;
}

//function that returns the area of the triangle
double IsoscelesTriangle::getArea() const
{
	return (0.5 * (m_right.m_col - m_left.m_col) * abs(m_head.m_row - m_left.m_row));
}

//function that returns the perimeter of the triangle
double IsoscelesTriangle::getPerimeter() const
{
	double length;
	length = getLegLength();

	return ((m_right.m_col - m_left.m_col) + 2 * length);
}

//function that returns the center of the triangle
Vertex IsoscelesTriangle::getCenter() const
{
	Vertex center;
	center.m_col = (m_left.m_col + m_right.m_col + m_head.m_col) / 3;
	center.m_row = (m_left.m_row + m_right.m_row + m_head.m_row) / 3;

	return center;
}

//function that resizes the shape according to the factor.
//if the factor is not a positive number it won't do anything and reurns false
//if after resizing the shape we get illegal values, then it won't do anything and returns false
bool IsoscelesTriangle::scale(double factor)
{
	if (factor <= 0)
		return false;

	Vertex center = getCenter();

	double leftX, headX, rightX,
		leftY, headY, rightY;


	 
	if (m_head.isHigherThan(m_left) || sameRow(m_head, m_left)) //if the head is up or on the base
	{
		leftX = center.m_col - factor * (center.m_col - m_left.m_col);
		leftY = center.m_row - factor * (center.m_row - m_left.m_row);
		headX = m_head.m_col;
		headY = center.m_row + factor * (m_head.m_row - center.m_row);
		rightX = center.m_col + factor * (m_right.m_col - center.m_col);
		rightY = center.m_row - factor * (center.m_row - m_right.m_row);
	}

	else if (m_left.isHigherThan(m_head))//if the head is down
	{
		leftX = center.m_col - factor * (center.m_col - m_left.m_col);
		leftY = center.m_row + factor * (m_left.m_row - center.m_row);
		headX = m_head.m_col;
		headY = center.m_row - factor * (center.m_row - m_head.m_row);
		rightX = center.m_col + factor * (m_right.m_col - center.m_col);
		rightY = center.m_row + factor * (m_right.m_row - center.m_row);
	}

	if (checkLegal(leftX, leftY, headX, headY, rightX, rightY))//if the new values are legal
	{
		m_left.m_col = leftX;
		m_left.m_row = leftY;
		m_head.m_col = headX;
		m_head.m_row = headY;
		m_right.m_col = rightX;
		m_right.m_row = rightY;

		return true;
	}

	return false;
}