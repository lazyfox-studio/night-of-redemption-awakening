#include "Screen.h"
#include "Controls.h"
#include "Corners.h"

int Screen::w = 1280;
int Screen::h = 720;

bool Keyboard::W = false;
bool Keyboard::A = false;
bool Keyboard::S = false;
bool Keyboard::D = false;
bool Keyboard::Q = false;
bool Keyboard::E = false;
bool Keyboard::R = false;
bool Keyboard::LShift = false;
bool Keyboard::Escape = false;

bool Mouse::Left = false;
bool Mouse::Right = false;
bool Mouse::Middle = false;
float Mouse::x;
float Mouse::y;
unsigned long long Mouse::flood_control[2] = { 0 };

CornerPoint Corners::top_left;
CornerPoint Corners::top_right;
CornerPoint Corners::bottom_left;
CornerPoint Corners::bottom_right;