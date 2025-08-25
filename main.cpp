#include "grid.hpp"
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

string getDirectionSymbol(double vx, double vy) {
    double threshold = 1e-5;
    if (fabs(vx) < threshold && fabs(vy) < threshold) return ".";

    double angle = atan2(vy, vx); // atan2(y, x)
    if (vx > 0 && fabs(vy) < 0.5*fabs(vx)) return "->"; // Right
    if (vx < 0 && fabs(vy) < 0.5*fabs(vx)) return "<-"; // Left
    if (vy < 0 && fabs(vx) < 0.5*fabs(vy)) return ",";  // Up
    if (vx > 0 && vy > 0) return "/"; // Down-right
    if (vx < 0 && vy > 0) return "\\"; // Down-left
    return "."; // For everything else
}

int main() {
    int totalFrames = 10;

    grid space;
    space.init();

    cout << "Starting fluid simulation..." << endl;
    cout << "Grid size: " << width << "x" << height << endl;
    cout << "Total frames: " << totalFrames << endl;
    cout << "Timestep: " << space.timeStep << endl;
    cout << "Kinematic viscosity: " << kinematicViscosity << endl;

    for (int frame = 0; frame < totalFrames; frame++) {
        space.renderNext();
        cout<<"frame generated "<<frame + 1<<endl;
    }

    // ASCII visualization of velocity field
    ofstream outFile("velocity_ascii.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening velocity_ascii.txt" << endl;
        return 1;
    }

    outFile << "# ASCII visualization of velocity field after " << totalFrames << " frames\n";
    outFile << "# -> : right, <- : left, , : up, / : down-right, \\ : down-left, . : still\n";

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            string symbol = getDirectionSymbol(space.currentVelocities[i][j].x, space.currentVelocities[i][j].y);
            outFile << symbol;
        }
        outFile << endl;
    }

    outFile.close();
    cout << "ASCII velocity field written to velocity_ascii.txt" << endl;
    return 0;
}
