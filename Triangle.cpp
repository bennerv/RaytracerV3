#include "Triangle.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include "Material.hpp"

Triangle::Triangle(Vec3<float> * a, Vec3<float> * b, Vec3<float> * c, Material mat, Colors col) : color(col) {
	vertexA = Vec3<float>::vec3(a->x, a->y, a->z);
	vertexB = Vec3<float>::vec3(b->x, b->y, b->z);
	vertexC = Vec3<float>::vec3(c->x, c->y, c->z);
	material = mat;
}

Triangle::Triangle(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, Material mat, Colors col) : color(col) {
	vertexA = Vec3<float>::vec3(ax, ay, az);
	vertexB = Vec3<float>::vec3(bx, by, bz);
	vertexC = Vec3<float>::vec3(cx, cy, cz);
	material = mat;
}


Triangle::~Triangle() {
	delete vertexA;
	delete vertexB;
	delete vertexC;
}

void Triangle::setMaterial(Material mat) {
	material = mat;
}

float Triangle::intersect(Vec3<float> * ray, Vec3<float> * startingPos) {
	float A = vertexA->x - vertexB->x;
	float B = vertexA->y - vertexB->y;
	float C = vertexA->z - vertexB->z;
	float D = vertexA->x - vertexC->x;
	float E = vertexA->y - vertexC->y;
	float F = vertexA->z - vertexC->z;

	float G = ray->x;
	float H = ray->y;
	float I = ray->z;
	
	float J = vertexA->x - startingPos->x;
	float K = vertexA->y - startingPos->y;
	float L = vertexA->z - startingPos->z;

	float M = A * (E * I - H * F) + B * (G * F - D * I) + C * (D * H - E * G);
	float t = (-1 * (F * (A * K - J * B) + E * (J * C - A * L) + D * (B * L - K * C) ) ) / M;

	if( t < 0 ) {
		return -1.0;
	}
	float gamma = (I * (A * K - J * B) + H * (J * C - A * L) + G * (B * L - K * C)) / M;
	
	if( gamma < 0 || gamma > 1 ) {
		return -1.0;
	}
	float beta = (J * (E * I - H * F) + K * (G * F - D * I) + L * (D * H - E * G)) / M;
	
	if( beta < 0 || beta > 1 - gamma ) {
		return -1.0;
	}
	
	return t;
}
