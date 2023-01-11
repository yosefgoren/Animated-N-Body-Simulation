#include "Space.h"

#define N_BODIES 20000
#define N_DIMS 3
#define SOFTENING 1e-9f

typedef struct { float x, y, z, vx, vy, vz; } Body;

typedef struct { float positions[N_DIMS][N_BODIES], velocities[N_DIMS][N_BODIES]; } Bodies;

class NBodySystem {
	NBodySystem();
	~NBodySystem();

	Matrix getPositions() const;
	void step(float dt);

	Bodies *p;
	unsigned int n;
};
