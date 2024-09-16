#include "Diamond.h"


//in the constructors, first we check if the values that we got are legal or not,
//then if they are legal we put these values in our members, if not then we keep
//the members with their initial values

//constructor that gets array of vertexes with 4 cells
//the first is left
//the second is up
//the third is right
//the fourth is down
Diamond::Diamond(const Vertex vertices[4]) : m_left(20, 20), m_up(25, 25), m_right(30, 20), m_down(25, 15)
{
	if (checkLegal(vertices[0].m_col, vertices[0].m_row, vertices[1].m_col, vertices[1].m_row, 
		vertices[2].m_col, vertices[2].m_row, vertices[3].m_col, vertices[3].m_row))
	{
		m_left = vertices[0];
		m_up= vertices[1];
		m_right = vertices[2];
		m_down = vertices[3];
	}
}

//constructor that gets a triangle with down head
Diamond::Diamond(const IsoscelesTriangle& lower) : m_left(20, 20), m_up(25, 25), m_right(30, 20), m_down(25, 15)
{
	Vertex top;
	top.m_col = lower.getVertex(1).m_col;
	top.m_row = lower.getVertex(1).m_row + 2 * lower.getHeight();

	if (checkLegal(lower.getVertex(0).m_col, lower.getVertex(0).m_row, top.m_col, top.m_row,
		lower.getVertex(2).m_col, lower.getVertex(2).m_row, lower.getVertex(1).m_col, lower.getVertex(1).m_row))
	{
		m_left = lower.getVertex(0);
		m_up = top;
		m_right = lower.getVertex(2);
		m_down = lower.getVertex(1);
	}
}

//function that checks if the values that the user inserted are legal
//if yes it returns true, if not it returns false
bool Diamond::checkLegal(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3) const
{
	Vertex first, second, third, fourth;
	
	first.m_col = x0;
	first.m_row = y0;
	second.m_col = x1;
	second.m_row = y1;
	third.m_col = x2;
	third.m_row = y2;
	fourth.m_col = x3;
	fourth.m_row = y3;
	Vertex arr1[3] = {first, second, third};
	Vertex arr2[3] = {first, fourth, third};

	IsoscelesTriangle upTrgl(arr1), downTrgl(arr2);
	
	if(upTrgl.checkLegal(x0, y0, x1, y1, x2, y2) && downTrgl.checkLegal(x0, y0, x3, y3, x2, y2)
		&& doubleEqual(y1 - y0, y0 - y3) && (second.isHigherThan(fourth) || sameRow(second, fourth)))
		return true;

	
	return false;
}

//function that returns a vertex according to the index
// 0 : left 
// 1 : up
// 2 : right
// 3 : down
Vertex Diamond::getVertex(int index) const
{
	Vertex wanted;

	if (index == 0)
	{
		wanted = m_left;
	}
	else if (index == 1)
	{
		wanted = m_up;
	}
	else if (index == 2)
	{
		wanted = m_right;
	}
	else if (index == 3)
	{
		wanted = m_down;
	}

	return wanted;
		
}

//function that returns the width of the diamond
double Diamond::getWidth() const
{
	return m_right.m_col - m_left.m_col;
}

//function that returns the height of the diamond
double Diamond::getHeight() const
{
	return m_up.m_row - m_down.m_row;
}

//function that draws the shape by drawing lines between two vertexes
void Diamond::draw(Board& board) const
{
	Vertex arr1[3] = { m_left, m_up, m_right };
	Vertex arr2[3] = { m_left, m_down, m_right };

	IsoscelesTriangle upTrgl(arr1), downTrgl(arr2);
	upTrgl.draw(board);
	downTrgl.draw(board);
}

//function that returns the bounding rectangle
Rectangle Diamond::getBoundingRectangle() const
{
	//we gave the rectangle values because all the constructors in the rectangle have parameters
    //but if we have a constructor that don't get any parameters then we should leave the object
    //rect without values.
	Rectangle rect(1.0, 2.0, 3.0, 4.0);
	rect.setBottomLeft(m_left.m_col, m_down.m_row);
	rect.setTopRight(m_right.m_col, m_up.m_row);

	return rect;
}

//function that returns the area of the diamond
double Diamond::getArea() const
{
	double height = getHeight();
	double width = getWidth();

	return 0.5 * height * width;

}

//function that returns the perimeter of the diamond
double Diamond::getPerimeter() const
{
	return 4 * distance(m_left, m_up);
}

//function that returns the center of the diamond
Vertex Diamond::getCenter() const
{
	Vertex center;
	center.m_col = (m_left.m_col + m_right.m_col) / 2;
	center.m_row = (m_up.m_row + m_down.m_row) / 2;

	return center;
}

//function that resizes the shape according to the factor.
//if the factor is not a positive number, it won't do anything and reurns false
//if after resizing the shape we get illegal values, then it won't do anything and returns false
bool Diamond::scale(double factor)
{
	if (factor <= 0)
		return false;
	Vertex center = getCenter();

	double leftX, rightX, upY, downY;

	leftX = center.m_col - factor * (center.m_col - m_left.m_col);
	rightX = center.m_col + factor * (m_right.m_col - center.m_col);
	upY = center.m_row + factor * (m_up.m_row - center.m_row);
	downY = center.m_row - factor * (center.m_row - m_down.m_row);

	//check if the new values are legal
	if (checkLegal(leftX, m_left.m_row, m_up.m_col, upY, rightX, m_right.m_row, m_down.m_col, downY))
	{
		m_left.m_col = leftX;
		m_right.m_col = rightX;
		m_up.m_row = upY;
		m_down.m_row = downY;

		return true;
	}

	return false;
}