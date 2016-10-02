#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;

int calcSpeed(int x, int y, int lastX, int lastY) {
    int dx = x - lastX;
    int dy = y - lastY;
    return hypot(dx, dy);
}

enum State
{
    STATE_START,       // Lead foot to get up to speed
    STATE_FLAT,        // Open it up
    STATE_CORNER,      // Slow into the corner
    STATE_EXIT_TURN, // Begin accelerating out of the apex of the turn
    STATE_BOOST,       // Use booster then cooldown
};

int main() {
    // inputs
    int x, y;
    int nextCheckpointX, nextCheckpointY; // positions of the next checkpoint
    int nextCheckpointDist; // distance to the next checkpoint
    int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
    int opponentX, opponentY;

    // outputs
    int thrust, headingX, headingY;

    // the previous game tick's x and y for calculating speed
    int lastX = 0;
    int lastY = 0;
    int speed;

    State state = STATE_START;
    while (1) {
        cerr << "state: " << state;

        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        cin >> opponentX >> opponentY; cin.ignore();

        speed = calcSpeed(x, y, lastX, lastY);
        cerr << "positions " << x << " " << y << " " << " " << lastX << " " << lastY << endl;
        cerr << "speed: " << calcSpeed(x, y, lastX, lastY) << endl;
        cerr << "dist out: " << nextCheckpointDist << endl;

        // Set up previous position variables for speed calculations
        lastX = x;
        lastY = y;

        // Always use the same heading regardless of state for now
        headingX = nextCheckpointX;
        headingY = nextCheckpointY;

        switch (state) {
            case STATE_START:
            case STATE_FLAT:
                thrust = 100;
                if (nextCheckpointDist < 1000)
                    state = STATE_CORNER;
                    state = STATE_CORNER;
                break;
            case STATE_CORNER:
                // Slow into corner if we're going fast
                if (speed > 500) {
                    thrust = 0;
                } else {
                    thrust = 60;
                }

                if (abs(nextCheckpointAngle) > 90)
                    state = STATE_EXIT_TURN;
                break;
            case STATE_EXIT_TURN:
                thrust = 0;
                if (abs(nextCheckpointAngle) <= 90)
                    state = STATE_FLAT;
                break;
            case STATE_BOOST:
                break;
            default:
                cerr << "Bad state" << endl;
        }

        cout << headingX << " " << headingY << " " << thrust << endl;
    }
}
