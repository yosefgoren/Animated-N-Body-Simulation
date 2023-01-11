#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

struct Matrix{
    struct VariableLengthsError : public runtime_error{
        VariableLengthsError();
    };

    Matrix(const vector<vector<double>>& src);
    Matrix(const Matrix& mat);
    Matrix(size_t nrows, size_t ncols, bool initialize = true);
    Matrix& operator=(const vector<vector<double>>& src);

    double operator()(int i, int j) const;
    double& operator()(int i, int j);

    Matrix& operator=(const Matrix& mat);
    //overload opeartor * for matrix multiplication:
    Matrix operator*(const Matrix& mat);
    string to_string() const;

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

    Matrix operator+(const Matrix& other) const;
    
    size_t nrows, ncols;
private:
    vector<vector<double>> data;
};

struct Projector : public Matrix{
    Projector(double a[3]);
    Projector(double ax = 0, double ay = 0, double az = 0);
}; 

struct Point2D : public Matrix{
    Point2D(double x = 0, double y = 0);
    Point2D(const Matrix& mat);
    void draw(sf::RenderWindow& window, double radius = 5, const sf::Color& color = sf::Color::Blue);
};
struct Point3D : public Matrix{
    Point3D(double x = 0, double y = 0, double z = 0);
    Point3D(const Matrix& mat);
};