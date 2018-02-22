//
//  math.cpp
//  graphics-lab-1
//
//  Created by Daniel Shiposha on 21/02/2018.
//

#include "math.hpp"
#include <iostream>

using namespace ginseng;

math::Vector2D bisectors_intersection_point(const graphics::Triangle &triangle)
{
    auto side_1_length = (triangle.second_point() - triangle.first_point()).length();
    auto side_2_length = (triangle.third_point() - triangle.second_point()).length();
    auto side_3_length = (triangle.first_point() - triangle.third_point()).length();
    double side_sum = side_1_length + side_2_length + side_3_length;
    
    double x =
         (
            side_2_length*triangle.first_point().x()
          + side_3_length*triangle.second_point().x()
          + side_1_length*triangle.third_point().x()
         ) / side_sum;
    
    double y =
        (
            side_2_length*triangle.first_point().y()
          + side_3_length*triangle.second_point().y()
          + side_1_length*triangle.third_point().y()
        ) / side_sum;
    
    return math::Vector2D(x, y);
}

std::tuple<graphics::Line, graphics::Line, graphics::Line>
bisectors(const ginseng::graphics::Triangle &triangle)
{
    math::Line side_1(triangle.first_point(),  triangle.second_point() - triangle.first_point());
    math::Line side_2(triangle.second_point(), triangle.third_point()  - triangle.second_point());
    math::Line side_3(triangle.third_point(),  triangle.first_point()  - triangle.third_point());
    
    auto bisects_intersection = bisectors_intersection_point(triangle);
    
    math::Line bisect_1(triangle.first_point(),  triangle.first_point()  - bisects_intersection);
    math::Line bisect_2(triangle.second_point(), triangle.second_point() - bisects_intersection);
    math::Line bisect_3(triangle.third_point(),  triangle.third_point()  - bisects_intersection);
    
    auto bisect_1_end = math::lines_intersection_point(bisect_1, side_2);
    
    auto bisect_2_end = math::lines_intersection_point(bisect_2, side_3);
    auto bisect_3_end = math::lines_intersection_point(bisect_3, side_1);
    
    return std::make_tuple
    (
        graphics::Line(triangle.first_point(),  bisect_1_end),
        graphics::Line(triangle.second_point(), bisect_2_end),
        graphics::Line(triangle.third_point(),  bisect_3_end)
    );
}

//std::tuple<double, double, double> get_line_qs(const Vector3D &a, const Vector3D &b)
//{
//    double A = b.y() - a.y();
//    double B = a.x() - b.x();
//    double C = b.x()*a.y() - b.y()*a.x();
//
//    return std::make_tuple(A, B, C);
//}
//
//graphics::Line get_triangle_max_height(const ginseng::graphics::Triangle &triangle)
//{
//    double h1 = 0.0, h2 = 0.0, h3 = 0.0;
//
//    // A, B, C - коэф-ты уравнения прямой для каждой стороны
//
//    // Первая сторона
//    auto [A1, B1, C1] = get_line_qs(triangle.first_point(), triangle.second_point());
//    h1 = std::abs(A1*triangle.third_point().x()*B1*triangle.third_point().y() + C1) / sqrt(A1*A1 + B1*B1);
//
//    // Вторая сторона
//    auto [A2, B2, C2] = get_line_qs(triangle.second_point(), triangle.third_point());
//    h2 = std::abs(A2*triangle.first_point().x()*B2*triangle.first_point().y() + C2) / sqrt(A2*A2 + B2*B2);
//
//    // Третья сторона
//    auto [A3, B3, C3] = get_line_qs(triangle.first_point(), triangle.third_point());
//    h3 = std::abs(A3*triangle.second_point().x()*B3*triangle.second_point().y() + C3) / sqrt(A3*A3 + B3*B3);
//
//
//    double max = std::max(h1, std::max(h2, h3));
//    double px = 0., py = 0.;
//
//    auto set_px_py = [&px, &py](const Vector3D &vector, double A, double B, double C)
//    {
//        py = ( B*C/A + B*vector.x() - A*vector.y()) / (-B*B/A - A);
//        px = (-B*py - C) / A;
//    };
//
//    if(h1 == max)
//    {
//        set_px_py(triangle.third_point(), A1, B1, C1);
//        return Line(triangle.third_point(), {px, py, 0.});
//    }
//    else if(h2 == max)
//    {
//        set_px_py(triangle.first_point(), A2, B2, C2);
//        return Line(triangle.first_point(), {px, py, 0.});
//    }
//    else if(h3 == max)
//    {
//        set_px_py(triangle.second_point(), A3, B3, C3);
//        return Line(triangle.second_point(), {px, py, 0.});
//    }
//}
