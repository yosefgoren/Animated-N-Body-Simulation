#include "Space.h"
#include <string>

Matrix::VariableLengthsError::VariableLengthsError()
	: runtime_error("Expected all input lengths to be the same"){}

Matrix::Matrix(const vector<vector<double>>& src){
	*this = src;
}
Matrix::Matrix(const Matrix& mat){
	*this = mat;
}
Matrix::Matrix(size_t ncols, size_t nrows)
	:nrows(nrows), ncols(ncols), data(nrows, vector<double>(ncols, 0)){}

Matrix& Matrix::operator=(const vector<vector<double>>& src){
	if(!verifyColumnLengths(src)){
		throw VariableLengthsError();
	}
	data = src;
	ncols = data.size();
	if(nrows > 0)
		nrows = data[0].size();
	else
		nrows = 0;
	return *this;
}

double Matrix::operator()(int i, int j) const{
	return data[i][j];
}
double& Matrix::operator()(int i, int j){
	return data[i][j];
}

Matrix& Matrix::operator=(const Matrix& mat){
	data = mat.data;
	nrows = mat.nrows;
	ncols = mat.ncols;
	return *this;
}

//overload opeartor * for matrix multiplication:
Matrix Matrix::operator*(const Matrix& mat){
	if(ncols != mat.nrows){
		throw runtime_error("Matrix dimensions do not match");
	}
	Matrix result(mat.ncols, nrows);
	for(int i = 0; i < nrows; i++){
		for(int j = 0; j < mat.ncols; j++){
			for(int k = 0; k < ncols; k++){
				result(j, i) += this->operator()(k, i) * mat(j, k);//TODO: verify...
			}
		}
	}
	return result;
}

string Matrix::to_string() const{
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

Matrix Matrix::operator+(const Matrix& other) const{
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

Projector::Projector(double a[3])
    :Projector({a[0], a[1], a[2]}){}
Projector::Projector(double ax, double ay, double az)
	:Matrix({
	{cos(az)*cos(ax)-sin(az)*sin(ax)*sin(ay), cos(az)*sin(ax)*sin(ay)+sin(az)*cos(ax), -sin(az)*cos(ay)},
	{-cos(az)*sin(ax)-sin(az)*cos(ax)*sin(ay), cos(az)*cos(ax)*sin(ay)-sin(az)*sin(ax), cos(az)*cos(ay)}
}){}

Point2D::Point2D(double x, double y)
	:Matrix(vector<vector<double>>({{x}, {y}})){}
Point2D::Point2D(const Matrix& mat)
	:Matrix(mat){
	if(mat.ncols != 1 || mat.nrows != 2){
		throw runtime_error("Expected 2x1 matrix");
	}
}
void Point2D::draw(sf::RenderWindow& window, double radius, const sf::Color& color){
	sf::CircleShape shape(radius);
	shape.setFillColor(color);
	//shape.setOrigin((*this)(0, 0), (*this)(1, 0));
	shape.setPosition((*this)(0, 0), (*this)(1, 0));
	window.draw(shape);
}

void Point2D::draw(const Matrix& points, sf::RenderWindow& window, double radius, const sf::Color& color){
	for(int i = 0; i < points.ncols; i++){
		Point2D(points(0, i), points(1, i)).draw(window, radius, color);
	}
}

Point3D::Point3D(double x, double y, double z)
	:Matrix(vector<vector<double>>({{x}, {y}, {z}})){}
Point3D::Point3D(const Matrix& mat)
	:Matrix(mat){
	if(mat.ncols != 1 || mat.nrows != 3){
		throw runtime_error("Expected 3x1 matrix");
	}
}

