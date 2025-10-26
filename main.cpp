#include "raylib.h"
#include "grid.hpp"
#include <math.h>
#include <iostream>

int main() {
    std::cout << "Initializing window..." << std::endl;
    InitWindow(256 * 3, 256 * 3, "Navier Stokes");
    SetTargetFPS(60);

    std::cout << "Creating grid..." << std::endl;
    grid space;

    std::cout << "Reading frames from file..." << std::endl;
    space.readFramesFromFile("C:/Users/samar/source/repos/NavierStokesSolver/NavierStokesSolver/finalframes_one.txt");

    std::cout << "Total frames loaded: " << space.generatedFrames.size() << std::endl;

    int currentFrame = 0;
    while (!WindowShouldClose()) {
        vector <vector<Vec>> toRender = space.generatedFrames[currentFrame % 1090];
        std::cout << "toRender size: " << toRender.size() << std::endl;
        if (toRender.size() > 0) {
            std::cout << "toRender[0] size: " << toRender[0].size() << std::endl;
        }
        currentFrame++;
        BeginDrawing();
        ClearBackground(BLACK);
        double maxVelocity = 0.0;
        vector <vector<double>> velocity(toRender.size(), vector<double>(toRender[0].size(), 0.0));
        for (int i = 0; i < toRender.size(); i++) {
            for (int j = 0; j < toRender[i].size(); j++) {
                velocity[i][j] = pow(pow(toRender[i][j].x , 2) + pow(toRender[i][j].y , 2) , 0.5 );
                maxVelocity = max(maxVelocity, velocity[i][j]);
            }
        }
        for (int i = 0 ; i < toRender.size(); i++) {
            for (int j = 0 ; j < toRender[i].size(); j++) {
                int red = (maxVelocity > 0) ? (int)(255 * velocity[i][j] / maxVelocity) : 0;
                DrawRectangle(i* 3 , j * 3 , 3 , 3 ,Color{(unsigned char)red, 0, 255, 255});
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
