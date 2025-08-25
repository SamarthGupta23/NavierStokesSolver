#include "coords.hpp"
#include <bits/stdc++.h>
#include <vector>
extern const int width;
extern const int height;
extern const double kinematicViscosity;
extern const int diffusionIterations;
extern const int projectionIterations;
extern const int dx;
using namespace std;

class grid {
public:
    vector <vector <Vec>> currentVelocities;
    vector <vector <Vec>> nextVelocities;
    vector <vector <double>> pressureForces;
    double timeStep;
    double alpha;


    //core logic
    void forces();
    void diffusion();
    void projection();
    void advection();


    //helper functions
    void renderNext();
    void init();
    Vec getBoundaryVelocity(int i, int j, const vector<vector<Vec>>& velocities);  //Neumann Zero Derivative assumption
    double getBoundaryPressure(int i, int j, const vector<vector<double>> pressureForces);
};
