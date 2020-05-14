#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>


class Figure {
public:
    virtual std::string Name() = 0;
    virtual float Perimeter() = 0;
    virtual float Area() = 0;
};

class Triangle : public Figure {
public:
    Triangle(const unsigned& a, const unsigned& b, const unsigned& c)
        : side_a_(a), side_b_(b), side_c_(c)
    {}
    std::string Name() override{
        return "TRIANGLE";
    }
    float Perimeter() override {
        return static_cast<float>(side_a_ + side_b_ + side_c_);
    }
    float Area() override {
        float p = this->Perimeter() * 0.5f;
        return std::sqrt(p * (p - static_cast<float>(side_a_)) * 
               (p - static_cast<float>(side_b_)) * 
               (p - static_cast<float>(side_c_)));
    }
private:
    const unsigned side_a_;
    const unsigned side_b_;
    const unsigned side_c_;

};

class Rect : public Figure {
public:
    Rect(const unsigned& width, const unsigned& height)
    : width_(width), height_(height)
    {}
    std::string Name() override {
        return "RECT";
    }
    float Perimeter() override {
        return static_cast<float>(2 * (width_ + height_));
    }
    float Area() override {
        return static_cast<float>(width_ * height_);
    }
private:
    const unsigned width_;
    const unsigned height_;
};

class Circle : public Figure {
public:
    Circle(const unsigned& radius) : radius_(radius) {}
    std::string Name() override {
        return "CIRCLE";
    }
    float Perimeter() override {
        return static_cast<float>(2 * pi_ * radius_);
    }
    float Area() override {
        return static_cast<float>(pi_ * radius_ * radius_);
    }
private:
    const double pi_ = 3.14;
    const unsigned radius_;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream& is) {
    std::string figure;
    is >> figure;
    if (figure == "TRIANGLE") {
        unsigned a, b, c;
        is >> a >> b >> c;
        return std::make_shared<Triangle>(a, b, c);
    }
    if (figure == "RECT") {
        unsigned width, height;
        is >> width >> height;
        return std::make_shared<Rect>(width, height);
    }
    if (figure == "CIRCLE") {
        unsigned radius;
        is >> radius;
        return std::make_shared<Circle>(radius);
    }
};

int main() {
    std::vector<std::shared_ptr<Figure>> figures;
    for (std::string line; std::getline(std::cin, line); ) {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                std::cout << std::fixed << std::setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << std::endl;
            }
        }
    }
    return 0;
}
