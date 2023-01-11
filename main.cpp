#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Matrix{
    struct VariableLengthsError : public runtime_error{
        VariableLengthsError()
            : runtime_error("Expected all input lengths to be the same"){}
    };

    Matrix(const vector<vector<double>>& src){
        *this = src;
    }
    Matrix(const Matrix& mat){
        *this = mat;
    }
    Matrix(size_t nrows, size_t ncols)
        :nrows(nrows), ncols(ncols), data(nrows, vector<double>(ncols, 0)){}

    Matrix& operator=(const vector<vector<double>>& src){
        if(!verifyColumnLengths(src)){
            throw VariableLengthsError();
        }
        data = src;
        nrows = data.size();
        if(nrows > 0)
            ncols = data[0].size();
        else
            ncols = 0;
        return *this;
    }

    double operator()(int i, int j) const{
        return data[i][j];
    }
    double& operator()(int i, int j){
        return data[i][j];
    }

    Matrix& operator=(const Matrix& mat){
        data = mat.data;
        nrows = mat.nrows;
        ncols = mat.ncols;
        return *this;
    }

    //overload opeartor * for matrix multiplication:
    Matrix operator*(const Matrix& mat){
        if(ncols != mat.nrows){
            throw runtime_error("Matrix dimensions do not match");
        }
        Matrix result(nrows, mat.ncols);
        for(int i = 0; i < nrows; i++){
            for(int j = 0; j < mat.ncols; j++){
                for(int k = 0; k < ncols; k++){
                    result(i, j) += this->operator()(i, k) * mat(k, j);
                }
            }
        }
        return result;
    }

    string to_string() const{
        string res;
        for(int i = 0; i < nrows; i++){
            for(int j = 0; j < ncols; j++){
                res += std::to_string(data[i][j]) + " ";
            }
            res += "\n";
        }
        res += "\n";
        return res;
    }

    template <typename T>
    static bool verifyColumnLengths(const vector<vector<T>>& data){
        if(data.size() > 0){
            int ncols = data[0].size();
            for(const vector<T>& row: data){
                if(row.size() != ncols){
                    return false;
                }
            }
        }
        return true;
    }

    Matrix operator+(const Matrix& other) const{
        if(nrows != other.nrows || ncols != other.ncols){
            throw runtime_error("Matrix dimensions do not match");
        }
        Matrix result(nrows, ncols);
        for(int i = 0; i < nrows; i++){
            for(int j = 0; j < ncols; j++){
                result(i, j) = this->operator()(i, j) + other(i, j);
            }
        }
        return result;
    }

    size_t nrows, ncols;
    vector<vector<double>> data;
};

struct Projector : public Matrix{
    Projector(double a[3])
        :Projector({a[0], a[1], a[2]}){}
    Projector(double ax = 0, double ay = 0, double az = 0)
        :Matrix({
            {cos(az)*cos(ax)-sin(az)*sin(ax)*sin(ay), cos(az)*sin(ax)*sin(ay)+sin(az)*cos(ax), -sin(az)*cos(ay)},
            {-cos(az)*sin(ax)-sin(az)*cos(ax)*sin(ay), cos(az)*cos(ax)*sin(ay)-sin(az)*sin(ax), cos(az)*cos(ay)}
        }){}
}; 

struct Point2D : public Matrix{
    Point2D(double x = 0, double y = 0)
        :Matrix(vector<vector<double>>({{x}, {y}})){}
    Point2D(const Matrix& mat)
        :Matrix(mat){
        if(mat.ncols != 1 || mat.nrows != 2){
            throw runtime_error("Expected 2x1 matrix");
        }
    }
    void draw(sf::RenderWindow& window, double radius = 5, const sf::Color& color = sf::Color::Blue){
        sf::CircleShape shape(radius);
        shape.setFillColor(color);
        //shape.setOrigin((*this)(0, 0), (*this)(1, 0));
        shape.setPosition((*this)(0, 0), (*this)(1, 0));
        window.draw(shape);
    }
};
struct Point3D : public Matrix{
    Point3D(double x = 0, double y = 0, double z = 0)
        :Matrix(vector<vector<double>>({{x}, {y}, {z}})){}
    Point3D(const Matrix& mat)
        :Matrix(mat){
        if(mat.ncols != 1 || mat.nrows != 3){
            throw runtime_error("Expected 3x1 matrix");
        }
    }
};

int main(int, char**) {
    std::cout << "Hello, world!\n";
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");
    
    vector<Point3D> points3;
    for(int i = 200; i < 600; i+=100){
        for(int j = 200; j < 600; j+=100){
            for(int k = 0; k < 600; k+=100){
                points3.push_back(Point3D(i, j, k));
            }
        }
    }
    vector<Point2D> points2;

    Point2D center(256, 0);
    double ax = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::sleep(sf::seconds(0.05));
        auto projector = Projector(ax, 3.14/4);
        ax += 0.01;

        points2.clear();
        for(auto& p : points3){
            points2.push_back(center + projector*p);
        }

        window.clear();
        for(auto& v : points2)
            v.draw(window);
        window.display();
    }
    std::cout << "done\n";
}
