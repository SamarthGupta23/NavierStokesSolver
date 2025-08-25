#include "grid.hpp"

// Define the global variables here
const int width = 256;
const int height = 256;
const double kinematicViscosity = 5;
const int diffusionIterations = 25;
const int projectionIterations = 20;
const int dx = 1;

void grid::init() {
    currentVelocities.resize(width, vector<Vec>(height, Vec(0, 0)));
    nextVelocities.resize(width, vector<Vec>(height, Vec(0, 0)));
    pressureForces.resize(width, vector<double>(height, 0.0));

    timeStep = 0.02;  // Smaller, more stable timestep
    this->alpha = kinematicViscosity * timeStep / (dx * dx);
}

void grid::forces() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Vec force;
            // Adjusted force region for smaller grid
            if (i < 140 && i >= 116) {
                force = Vec(2, 0);
            }
            else {
                force = Vec(0 , 0);
            }

            Vec toAdd(force.x * this->timeStep, force.y * this->timeStep);
            this->currentVelocities[i][j] = Vec::add(this->currentVelocities[i][j], toAdd);
        }
    }
    cout<<"forces applied"<<endl;
}

Vec grid::getBoundaryVelocity(int i, int j, const vector<vector<Vec>>& velocities) {
    int clamped_i = max(0, min(width - 1, i));
    int clamped_j = max(0, min(height - 1, j));
    return velocities[clamped_i][clamped_j];
}

double grid::getBoundaryPressure(int i, int j, const vector<vector<double> > pressureForces) {
    int clamped_i = max(0, min(width - 1, i));
    int clamped_j = max(0, min(height - 1, j));
    return pressureForces[clamped_i][clamped_j];
}

void grid::diffusion() {
    vector<vector<Vec>> before = currentVelocities;

    for (int iter = 0; iter < diffusionIterations; iter++) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                Vec left = getBoundaryVelocity(i - 1, j, currentVelocities);
                Vec right = getBoundaryVelocity(i + 1, j, currentVelocities);
                Vec up = getBoundaryVelocity(i, j - 1, currentVelocities);
                Vec down = getBoundaryVelocity(i, j + 1, currentVelocities);

                double denominator = 1 + 4 * alpha;
                nextVelocities[i][j].x = (before[i][j].x + alpha * (left.x + right.x + up.x + down.x)) / denominator;
                nextVelocities[i][j].y = (before[i][j].y + alpha * (left.y + right.y + up.y + down.y)) / denominator;
            }
        }
        currentVelocities = nextVelocities;
    }
    cout<<"diffusion applied"<<endl;
}

void grid::advection() {
    for (int i = 0 ; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int x = j;
            int y = height - i - 1;
            double x_new = max(min(x - currentVelocities[i][j].x * timeStep , (double)width - 1) , (double)0);
            double y_new = max(min(y - currentVelocities[i][j].y * timeStep , (double)height - 1) , (double)0);
            double s = x_new - floor(x_new);
            double t = y_new - floor(y_new);
            int lowX = floor(x_new);
            int lowY = floor(y_new);
            int store = lowY;
            lowY = lowX;
            lowX = height - 1 - store;
            Vec newVelocity;
            newVelocity.x = (1 - s) * (1 - t) * currentVelocities[lowX][lowY].x + s * (1 - t) * currentVelocities[
                                min(lowX + 1, width - 1)][lowY].x + (1 - s) * t * currentVelocities[lowX][
                                min(lowY + 1, height - 1)].x + s * t * currentVelocities[min(lowX + 1, width - 1)][min(
                                lowY + 1, height - 1)].x;
            newVelocity.y = (1 - s) * (1 - t) * currentVelocities[lowX][lowY].y + s * (1 - t) * currentVelocities[
                                min(lowX + 1, width - 1)][lowY].y + (1 - s) * t * currentVelocities[lowX][
                                min(lowY + 1, height - 1)].y + s * t * currentVelocities[min(lowX + 1, width - 1)][min(
                                lowY + 1, height - 1)].y;
            nextVelocities[i][j] = newVelocity;
        }
    }
    currentVelocities = nextVelocities;
    cout<<"advection applied"<<endl;
}

void grid::projection() {
    vector <vector <double>> divergence(height , vector<double>(width , 0));
    //computing divergence
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double u_right = getBoundaryVelocity(i , j + 1, currentVelocities).x;
            double u_left = getBoundaryVelocity(i , j - 1, currentVelocities).x;
            double v_up = getBoundaryVelocity(i - 1 , j , currentVelocities).y;
            double v_down = getBoundaryVelocity(i + 1 , j , currentVelocities).y;

            divergence[i][j] = -0.5 * ((u_right - u_left) + (v_up - v_down));
        }
    }
    //gauss seidel iterations to calculate pressure forces
    int iterations = projectionIterations;
    while (iterations--) {
        cout<<iterations<<endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                double p_left = getBoundaryPressure(i , j - 1, pressureForces);
                double p_right = getBoundaryPressure(i , j + 1, pressureForces);
                double p_up = getBoundaryPressure(i - 1, j, pressureForces);
                double p_down = getBoundaryPressure(i + 1, j, pressureForces);

                this->pressureForces[i][j] = (divergence[i][j] + p_right + p_left + p_up + p_down) / 4;
            }
        }
    }
    //correcting velocities
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double p_left = getBoundaryPressure(i , j - 1, pressureForces);
            double p_right = getBoundaryPressure(i , j + 1, pressureForces);
            double p_up = getBoundaryPressure(i - 1, j, pressureForces);
            double p_down = getBoundaryPressure(i + 1, j, pressureForces);

            double xGradient = (p_right - p_left) / 2;
            double yGradient = (p_up - p_down) / 2;
            currentVelocities[i][j].x -= xGradient;
            currentVelocities[i][j].y -= yGradient;
        }
    }
    cout << "projection applied" << endl;
}

void grid::renderNext() {
    this->forces();
    this->diffusion();
    this->advection();
    this->projection();
}
