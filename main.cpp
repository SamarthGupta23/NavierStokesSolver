#include "grid.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main() {
    int totalFrames = 100;
    // ASCII visualization of velocity field
    ofstream outFile("velocity_ascii.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening velocity_ascii.txt" << endl;
        return 1;
    }
    grid space;
    space.init();

    cout << "Starting fluid simulation..." << endl;
    cout << "Grid size: " << width << "x" << height << endl;
    cout << "Total frames: " << totalFrames << endl;
    cout << "Timestep: " << space.timeStep << endl;
    cout << "Kinematic viscosity: " << kinematicViscosity << endl;

    for (int frame = 0; frame < totalFrames; frame++) {
        space.renderNext();
        space.frames.push_back(space.currentVelocities);
        cout << "frame generated " << frame + 1 << endl;
    }
    cout << "frames calculated , beginning frame generation algorithm" << endl;

    //framegen algo
    space.frameGen();
    space.writeFramesToFile("finalframes.txt");
    return 0;
}
