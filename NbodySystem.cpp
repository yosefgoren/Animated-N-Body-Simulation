#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>

#include "NBodySystem.h"

// #define NUM_THREADS 24

static void randomizeBodies_orig(float *data, int n) {
  for (int i = 0; i < n; i++) {
    data[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
  }
}

static void randomizeBodies(Bodies* data) {
	int bytes = N_BODIES*sizeof(Body);
	float *buf = (float*)malloc(bytes);
	Body *p = (Body*)buf;
	randomizeBodies_orig(buf, 6*N_BODIES);
	for(int i = 0; i < N_BODIES; ++i){
		data->positions[0][i] = p[i].x;
		data->positions[1][i] = p[i].y;
		data->positions[2][i] = p[i].z;
		data->velocities[0][i] = p[i].vx;
		data->velocities[1][i] = p[i].vy;
		data->velocities[2][i] = p[i].vz;
	}
	free(buf);
}

NBodySystem::NBodySystem() :n(n){
	srand(42);
	p = (Bodies*)malloc(sizeof(Bodies));
	randomizeBodies(p);
}

NBodySystem::~NBodySystem() {
	free(p);
}

Matrix NBodySystem::getPositions() const{
	//output dims are (N_BODIES, 3).
	Matrix positions(3, N_BODIES);
	for(int dim = 0; dim < N_DIMS; ++dim){
		for(int i = 0; i < N_BODIES; ++i){
			positions(dim, i) = p->positions[dim][i];
		}
	}
	return positions;
}

void NBodySystem::step(float dt){
	//#pragma omp parallel for schedule(guided)
	for(int effected = 0; effected < N_BODIES; ++effected){
		float force[N_DIMS] = {0.0f, 0.0f, 0.0f};
		
		for(int j = 0; j < N_BODIES; ++j){
			float delta[N_DIMS];
			delta[0] = p->positions[0][j] - p->positions[0][effected];
			delta[1] = p->positions[1][j] - p->positions[1][effected];
			delta[2] = p->positions[2][j] - p->positions[2][effected];
			float distSqr = delta[0]*delta[0]+delta[1]*delta[1]+delta[2]*delta[2] + SOFTENING;
			float invDist = 1.0f / sqrtf(distSqr);
			float invDist3 = invDist * invDist * invDist;
			force[0] += delta[0] * invDist3;
			force[1] += delta[1] * invDist3;
			force[2] += delta[2] * invDist3;
		}
		p->velocities[0][effected] += dt*force[0];
		p->velocities[1][effected] += dt*force[1];
		p->velocities[2][effected] += dt*force[2];
	}
	//#pragma omp parallel for schedule(guided)
	for(int effected = 0; effected < N_BODIES; ++effected){
		p->positions[0][effected] += p->velocities[0][effected] * dt;
		p->positions[1][effected] += p->velocities[1][effected] * dt;
		p->positions[2][effected] += p->velocities[2][effected] * dt;
	}
}

// int main(const int argc, const char** argv) {
// 	const float dt = 0.01f; // time step
// 	const int nIters = 10;  // simulation iterations
	
// 	//omp_set_num_threads(NUM_THREADS);
	
// 	double totalTime = 0.0;
// 	//double start_time = omp_get_wtime();
// 	for (int iter = 1; iter <= nIters; iter++) {
// 		//#pragma omp parallel for schedule(guided)
// 		for(int effected = 0; effected < N_BODIES; ++effected){
// 			float force[N_DIMS] = {0.0f, 0.0f, 0.0f};
			
// 			for(int j = 0; j < N_BODIES; ++j){
// 				float delta[N_DIMS];
// 				delta[0] = p->positions[0][j] - p->positions[0][effected];
// 				delta[1] = p->positions[1][j] - p->positions[1][effected];
// 				delta[2] = p->positions[2][j] - p->positions[2][effected];
// 				float distSqr = delta[0]*delta[0]+delta[1]*delta[1]+delta[2]*delta[2] + SOFTENING;
// 				float invDist = 1.0f / sqrtf(distSqr);
// 				float invDist3 = invDist * invDist * invDist;
// 				force[0] += delta[0] * invDist3;
// 				force[1] += delta[1] * invDist3;
// 				force[2] += delta[2] * invDist3;
// 			}
// 			p->velocities[0][effected] += dt*force[0];
// 			p->velocities[1][effected] += dt*force[1];
// 			p->velocities[2][effected] += dt*force[2];
// 		}
// 		//#pragma omp parallel for schedule(guided)
// 		for(int effected = 0; effected < N_BODIES; ++effected){
// 			p->positions[0][effected] += p->velocities[0][effected] * dt;
// 			p->positions[1][effected] += p->velocities[1][effected] * dt;
// 			p->positions[2][effected] += p->velocities[2][effected] * dt;
// 		}
// 	}
// 	//printf("Parallel Execution time: %f seconds with %d threads\n\n", omp_get_wtime()-start_time, NUM_THREADS);

// 	float res[3];
// 	for(int dim = 0; dim < N_DIMS; ++dim){
// 		res[dim] = p->positions[dim][0];
// 	}
// 	free(p);

// 	const float ref[3] = {102.497765, 107.869682, -2.093829};
// 	printf("Expecting to hardcoded: %f %f %f\n", ref[0], ref[1], ref[2]);
// 	printf("Got: %f %f %f\n", res[0], res[1], res[2]);
// 	int success = (fabs(res[0]-ref[0])<0.01f) && (fabs(res[1]-ref[1])<0.01f) && (fabs(res[2]-ref[2])<0.01f);
// 	printf("Test %s\n", (success) ? "PASSED" : "FAILED");
// }