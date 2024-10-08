#include <iostream>
#include <string>
#include <string_view>
#include <array>

#include "macros.h"
#include "Vertex.h"
#include "Board.h"

#define RECTANGLE           0
#define ISOSCELESTRIANGLE   0
#define DIAMOND             0
#define WINDOW              0

#if RECTANGLE
#include "Rectangle.h"
void printInfo(const Rectangle&);
#endif

#if ISOSCELESTRIANGLE
#include "IsoscelesTriangle.h"
void printInfo(const IsoscelesTriangle&);
#endif

#if DIAMOND
#include "Diamond.h"
void printInfo(const Diamond&);
#endif

#if WINDOW
#include "Window.h"
void printInfo(const Window&);
#endif

void waitForEnter();
Vertex readVertex(std::string_view vertexName, std::string_view shapeName);

template <typename Shape>
void useShape(Shape& shape, std::string_view shapeName);

template <typename Shape>
void draw(const Shape& shape, Board&);

template <typename Shape>
void printGenericInfo(const Shape& shape, std::string_view shapeName);

int main()
{
#if RECTANGLE
    {
        static constexpr auto shapeName = std::string_view("rectangle");

        const auto vertices = std::array<Vertex, 2>
        {
            readVertex("bottom-left", shapeName),
            readVertex("top-right", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto rectangle = Rectangle(vertices.data());
        useShape(rectangle, shapeName);
    }
#endif // RECTANGLE

#if ISOSCELESTRIANGLE
    {
        static constexpr auto shapeName = std::string_view("isosceles triangle");

        const auto vertices = std::array<Vertex, 3>
        {
            readVertex("first", shapeName),
            readVertex("second", shapeName),
            readVertex("third", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto isoscelesTriangle = IsoscelesTriangle(vertices.data());
        useShape(isoscelesTriangle, shapeName);
    }
#endif // ISOSCELESTRIANGLE

#if DIAMOND
    {
        static constexpr auto shapeName = std::string_view("diamond");

        const auto vertices = std::array<Vertex, 4>
        {
            readVertex("first", shapeName),
            readVertex("second", shapeName),
            readVertex("third", shapeName),
            readVertex("fourth", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto diamond = Diamond(vertices.data());
        useShape(diamond, shapeName);
    }
#endif // DIAMOND

#if WINDOW
    {
        const auto readRectangle = [](std::string_view partOfShapeName)
        {
            auto vertices = std::array<Vertex, 2>();
            vertices[0] = readVertex("bottom-left", partOfShapeName);
            vertices[1] = readVertex("top-right", partOfShapeName);

            std::cin.ignore(); // ignore the enter

            return Rectangle(vertices.data());
        };

        static constexpr auto shapeName = std::string_view("window");

        const auto rectangle = readRectangle("rectangle of the " + std::string(shapeName));
        const auto innerVertex = readVertex("inner", shapeName);

        auto window = Window(rectangle, innerVertex);
        useShape(window, shapeName);
    }
#endif // WINDOW
}

#if RECTANGLE
void printInfo(const Rectangle& rectangle)
{
    static constexpr auto shapeName = std::string_view("rectangle");

    const auto printVertex = [](const Vertex& v, std::string_view vertexName)
    {
        std::cout << "The " << vertexName << " vertex of the " << shapeName
            << " is: " << v << '\n';
    };

    printVertex(rectangle.getBottomLeft(), "bottom-left");
    printVertex(rectangle.getTopRight(), "top-right");
}
#endif // RECTANGLE

#if ISOSCELESTRIANGLE
void printInfo(const IsoscelesTriangle& isoscelesTriangle)
{
    static constexpr auto shapeName = std::string_view("isosceles triangle");

    std::cout << "The vertices of the " << shapeName << " are:\n";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << isoscelesTriangle.getVertex(i) << '\n';
    }

    std::cout << "The length of the base of the " << shapeName << " is:\n";
    std::cout << isoscelesTriangle.getBaseLength() << '\n';

    std::cout << "The length of the legs of the " << shapeName << " is:\n";
    std::cout << isoscelesTriangle.getLegLength() << '\n';

    std::cout << "The height of the " << shapeName << " is:\n";
    std::cout << isoscelesTriangle.getHeight() << '\n';
}
#endif // ISOSCELESTRIANGLE

#if DIAMOND
void printInfo(const Diamond& diamond)
{
    static constexpr auto shapeName = std::string_view("diamond");

    std::cout << "The vertices of the " << shapeName << " are:\n";
    for (int i = 0; i < 4; ++i)
    {
        std::cout << diamond.getVertex(i) << '\n';
    }

    std::cout << "The width of the " << shapeName << " is: "
        << diamond.getWidth() << '\n';
    std::cout << "The height of the " << shapeName << " is: "
        << diamond.getHeight() << '\n';
}
#endif // DIAMOND

#if WINDOW
void printInfo(const Window& window)
{
    static constexpr auto shapeName = std::string_view("window");

    const auto printVertex = [](const Vertex& v, std::string_view vertexName)
    {
        std::cout << "The " << vertexName << " vertex of the " << shapeName
            << " is: " << v << '\n';
    };

    printVertex(window.getBottomLeft(), "bottom-left");
    printVertex(window.getTopRight(), "top-right");
    printVertex(window.getPoint(), "inner-point");

}
#endif // WINDOW

void waitForEnter()
{
    std::cout << "Press Enter to continue...\n";
    auto line = std::string();
    std::getline(std::cin, line);
}

Vertex readVertex(std::string_view vertexName, std::string_view shapeName)
{
    std::cout << "Please enter x and y coordinates for the " << vertexName
        << " vertex of the " << shapeName << ":\n";
    auto v = Vertex();
    std::cin >> v;
    return v;
}

template<typename Shape>
void useShape(Shape& shape, std::string_view shapeName)
{
    auto board = Board();
    auto print = [&]
    {
        draw(shape, board);
        printInfo(shape);
        printGenericInfo(shape, shapeName);
        waitForEnter();
    };

    print();

    board.clear();
    std::cout << "Now scaled by factor of 2:\n\n";
    if (shape.scale(2))
    {
        print();
    }
    else
    {
        std::cout << "Scaling failed!\n";
        waitForEnter();
    }
}

template<typename Shape>
void draw(const Shape& shape, Board& board)
{
    shape.draw(board);
    board.print();
    waitForEnter();

    std::cout << "Now with the bounding rectangle:\n";
    auto boundingRect = shape.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();
}

template<typename Shape>
void printGenericInfo(const Shape& shape, std::string_view shapeName)
{
    std::cout << "The perimeter of the " << shapeName << " is: " <<
        shape.getPerimeter() << '\n';

    std::cout << "The area of the " << shapeName << " is: " <<
        shape.getArea() << '\n';

    std::cout << "The center of the " << shapeName << " is: " <<
        shape.getCenter() << '\n';
}