//------------------------------------------------------------------------------
// PA04-Helicopter-2_APP.cpp : app code for helicopter flight
// 
// Accepts commands U)p, D)own, F)orward, X)lands, Q)uit
//      - Up increases altitude by 100 feet
//      - Down decreases altitude by 101 feet
//      - Forward increases distance flown by 100 feet
//      - Land resets altitude to 0
//      - Quit terminates app
//------------------------------------------------------------------------------

#include "Helicopter.h"

#include <iostream>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cin;
using std::cout;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int ALTITUDE_GAIN = 100;
constexpr int ALTITUDE_DROP = 101;
constexpr int DISTANCE_GAIN = 100;

const string APP_MENU = "U)p, D)own, F)orward, X)lands, R)efuel, Q)uit ? ";
constexpr char CMD_UP = 'U';
constexpr char CMD_DOWN = 'D';
constexpr char CMD_FORWARD = 'F';
constexpr char CMD_LAND = 'X';
constexpr char CMD_REFUEL = 'R';
constexpr char CMD_QUIT = 'Q';

//------------------------------------------------------------------------------
// globals
//------------------------------------------------------------------------------
namespace flight {
    Helicopter helo;
    bool quit = false;
}

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void initFlight();
char getPilotCommand();
void doHeloCommand(char);
void heloUp();
void heloDown();
void heloForward();
void heloLand();
void heloRefuel();
void quitFlight();
void displayStatus();
int setPilotThrottle();

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    initFlight();

    do {
        char cmd = getPilotCommand();
        doHeloCommand(cmd);
        displayStatus();
    } while (flight::helo.getStatus() != HELO_CRASHED && !flight::quit);

    cout << "\nGoodbye!\n\n";
}

//------------------------------------------------------------------------------
// displays pilot instructions, initial status
//------------------------------------------------------------------------------
void initFlight() {

    cout << "\nWelcome, helo pilot! Your Huey awaits your commands.\n\n";
    cout << "U)p increases altitude by " << ALTITUDE_GAIN << " feet,\n";
    cout << "D)own decreases altitude by " << ALTITUDE_DROP << " feet,\n";
    cout << "F)orward flies " << DISTANCE_GAIN << " yards.\n";
    cout << "X)lands sets altitude to 0 but your Huey can fly again.\n";
    cout << "Q)uit when you're done flying.\n\n";

    cout << "Commands can be upper or lower case.\n\n";

    cout << "If you drop too much altitude or Q)uit in midair, ";
    cout << "your Huey may crash!\n\n";

    cout << "Starting helo flight simulation.\n\n";
    displayStatus();
}

//------------------------------------------------------------------------------
// returns user command in upper case
//------------------------------------------------------------------------------
char getPilotCommand() {
    cout << "U)p, D)own, F)orward, X)lands, R)efuel, Q)uit ? ";

    char cmd;
    cin >> cmd;
    return toupper(cmd);
}

//------------------------------------------------------------------------------
// executes passed command
//------------------------------------------------------------------------------
void doHeloCommand(char cmd) {

    switch (cmd) {
    case CMD_UP:        heloUp(); break;
    case CMD_DOWN:      heloDown(); break;
    case CMD_FORWARD:   heloForward(); break;
    case CMD_LAND:      heloLand(); break;
    case CMD_REFUEL:    heloRefuel(); break;
    case CMD_QUIT:      quitFlight(); break;
    }
}

//------------------------------------------------------------------------------
// goes up
//------------------------------------------------------------------------------
void heloUp() { flight::helo.goUp(ALTITUDE_GAIN); }

//------------------------------------------------------------------------------
// goes down
//------------------------------------------------------------------------------
void heloDown() {

    if (!flight::helo.getAltitude()) {
        cout << "You're already on the ground! ";
    }

    flight::helo.goDown(ALTITUDE_DROP);
}

//------------------------------------------------------------------------------
// goes forward
//------------------------------------------------------------------------------
void heloForward() {

    if (flight::helo.getAltitude() > 0) {

        int fuelLeft = setPilotThrottle();

        if (fuelLeft <= GAUGE_EMPTY) {
            cout << "You're out of fuel!\n";
            flight::helo.goCrash();
            return;
        }

        if (fuelLeft <= GAUGE_RESERVE) {
            cout << "You're very low on fuel! Land and re-fuel!\n";
        }
        else if (fuelLeft <= GAUGE_LOW) {
            cout << "You're low on fuel. Land and re-fuel soon!\n";
        }

        flight::helo.goForward(DISTANCE_GAIN);
    }
}

//------------------------------------------------------------------------------
// lands
//------------------------------------------------------------------------------
void heloLand() {

    // land anyway to clear possible hard landing status
    flight::helo.goLand();
}

//------------------------------------------------------------------------------
// refills tank if helo is on ground
//------------------------------------------------------------------------------
void heloRefuel() {

    if (flight::helo.getStatus() == HELO_ONGROUND) {
        cout << "Your helo's " << GAUGE_FULL << " gallon fuel tank took "
            << flight::helo.fillFuelTank()
            << " gallons to fill. You're good to go!\n";
    }
    else {
        cout << "You have to land before refueling.\n";
    }
}

//------------------------------------------------------------------------------
// - gets user speed command
// - returns false on quit command, true otherwise
//------------------------------------------------------------------------------
int setPilotThrottle() {

    do {
        cout << "S)low, M)edium, F)ast ? ";

        char cmd;
        cin >> cmd;

        switch (toupper(cmd)) {
        case 'S': return flight::helo.setThrottle(SPEED_SLOW);
        case 'M': return flight::helo.setThrottle(SPEED_MEDIUM);
        case 'F': return flight::helo.setThrottle(SPEED_FAST);
        }

    } while (true);

}

//------------------------------------------------------------------------------
// terminates flight with bumpy landing or crash
//------------------------------------------------------------------------------
void quitFlight() {
    int altitude = flight::helo.getAltitude();

    int drop = altitude / ALTITUDE_GAIN * ALTITUDE_DROP;
    flight::helo.goDown(drop);

    flight::quit = true;
}

//------------------------------------------------------------------------------
// displays helicopter status and position 
//------------------------------------------------------------------------------
void displayStatus() {

    // reference parameters
    int altitude, distance;
    HeloStatus status = flight::helo.getPosition(altitude, distance);

    if (status == HELO_CRASHED) {
        cout << "You ran out of fuel and crashed!\n";
    }
    else if (status == HELO_HARDLANDING) {
        cout << "Bumpy landing - you only missed by "
            << abs(altitude) << " feet\n";
        flight::helo.goLand();
    }
    else if (status == HELO_ONGROUND) {
        cout << "Helo on the ground\n";
    }
    else if (status == HELO_INAIR) {
        cout << "Altitude " << altitude << " feet\n";
        cout << "Cruising speed " << flight::helo.getMph() << " mph\n";
    }

    cout << "Distance flown " << distance << " yards\n";
    cout << "Fuel left " << flight::helo.getFuelLeft() << " gallons\n\n";
}
