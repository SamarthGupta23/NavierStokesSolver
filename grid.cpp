#include "grid.hpp"
void grid::init() {
    for (int i = 0 ; i < 502 ; i++) {
        vector <Vec> tempVelocities (502 , Vec(0,0));
        this->currentVelocities.push_back(tempVelocities);
        this->nextVelocities.push_back(tempVelocities);
    }

    //init timestep
    this->alpha = kinematicViscosity * timeStep * width * width;
}

void grid::forces(Vec force) {
    for (int i = 0 ;  i < 502 ; i++) {
        for (int j = 0 ; j < 502 ; j++) {
            Vec toAdd (force.x * this->timeStep , force.y * this->timeStep);
            add(this->currentVelocities[i][j] , toAdd);
        }
    }
}

void grid::diffusion() {
    vector <vector<Vec>> before = currentVelocities;
    int loop = diffusionIterations;
    while (loop--) {
        for (int i = 1 ; i < 501 ; i++) {
            for (int j = 1 ; j < 501 ; j++) {
                nextVelocities[i][j].x = before[i][j].x + alpha *(currentVelocities[i - 1][j].x + currentVelocities[i + 1][j].x + currentVelocities[i][j + 1].x + currentVelocities[i][j - 1].x) / (1 + 4 * alpha);
                nextVelocities[i][j].y = before[i][j].y + alpha * (currentVelocities[i - 1][j].y + currentVelocities[i + 1][j].y + currentVelocities[i][j - 1].y + currentVelocities[i][j + 1].y) / (1 + 4 * alpha);
            }
        }
    }
    this->currentVelocities = this->nextVelocities;
}

void advection() {
    for (int i = 1 ; i < 501 ; i++) {
        for (int j = 1 ; j < 501 ; j++) {

        }
    }
}

void grid::renderNext() {
    this->forces(force);
    this->diffusion();
    this->projection();
    this->advection();
    this->projection();
}
