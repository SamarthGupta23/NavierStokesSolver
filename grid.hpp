#include "coords.hpp"
#include <bits/stdc++.h>
#include <vector>
const int width = 502;
const int height = 502;
double kinematicViscosity = 100;
const int diffusionIterations = 40;
using namespace std;

class grid {
    public:
    vector <vector <Vec>> currentVelocities;
    vector <vector <Vec>> nextVelocities;
    double timeStep;
    double alpha;


    //core logic
    void forces(Vec force);
    void diffusion();
    void projection();
    void advection();


    //helper functions
    void renderNext();
    void init();
};
