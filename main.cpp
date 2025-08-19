#include "coords.hpp"
#include "grid.hpp"
#include <bits/stdc++.h>
using namespace std;
int main() {
    int x = 100;
    grid space;
    space.init();
    while (x--) {
        space.renderNext();
    }
    return 0;
}