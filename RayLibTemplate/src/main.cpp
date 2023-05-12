#include <raylib.h>
#include <map>
#include <string>

#define RAYGUI_IMPLEMENTATION

#include "extras/raygui.h"

using namespace std;

struct Box {
    Box() {}

    Box(string name, int value, int trigger, Vector2 position) {
        this->name = name;
        this->bought = false;
        this->value = value;
        this->timer = 0;
        this->trigger = trigger;
        this->size = {400, 120};
        this->position = position;
        this->boxColor = GRAY;
        this->textColor = RED;
    }

    void Buy(int &money) {
        if (money >= value) {
            money -= value;
            bought = true;
        }
    }

    void Click(int &money) {
        if (bought) {
            ++timer;
            if (timer % trigger == 0) {
                ++money;
            }
        }
    }

    string name;
    bool bought;
    int value;
    int timer;
    int trigger;
    Vector2 size;
    Vector2 position;
    Color boxColor;
    Color textColor;
};

void ChangeBoxColor(int &money, Box &a) {
    if (money >= a.value) {
        a.boxColor = BLUE;
        a.textColor = GREEN;
    }
}

int main() {
// Initialization
//--------------------------------------------------------------------------------------

    const int screenWidth = 1920;
    const int screenHeight = 1030;

    InitWindow(screenWidth, screenHeight, "Cookie Clicker");

    int money = 0;
    int rotation = 0;
    Vector2 WinBGPos = {0, -1080,};
    Vector2 WinTextPos = {0, -1080};

    Texture2D cookie = LoadTexture("cookie.png");

    Box finger = Box("Finger", 10, 400, {50, 50});
    Box robot = Box("Robot", 50, 250, {50, 220});
    Box machine = Box("Machine", 100, 200, {50, 390});
    Box team = Box("Team", 200, 150, {50, 560});
    Box farm = Box("Farm", 500, 100, {50, 730});
    Box factory = Box("Factory", 1000, 75, {1470, 50});
    Box company = Box("Company", 2000, 50, {1470, 220});
    Box country = Box("Country", 5000, 25, {1470, 390});
    Box planet = Box("Planet", 10000, 10, {1470, 560});
    Box win = Box("Win", 100000, 1, {1470, 730});

    map<int, Box> shop = {{0, finger},
                          {1, robot},
                          {2, machine},
                          {3, team},
                          {4, farm},
                          {5, factory},
                          {6, company},
                          {7, country},
                          {8, planet},
                          {9, win}};

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
//---------------------------------------------------------------------------------------

// Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
// Update
//----------------------------------------------------------------------------------

        Rectangle dest = {960, 515, 400, 400};
        ++rotation;

        if (win.bought) {
            WinBGPos = {0, 0};
            WinTextPos = {800, 445};
        }

        for (int i = 0; i < 10; ++i) {
            shop[i].Click(money);
        }

        for (int i = 0; i < 10; ++i) {
            shop[i].boxColor = GRAY;
            shop[i].textColor = RED;
        }

        for (int i = 0; i < 10; ++i) {
            if (!shop[i].bought) {
                ChangeBoxColor(money, shop[i]);
            }
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(GetMousePosition(), {750, 315, 400, 400})) {
                ++money;
                dest = {960, 515, 390, 390};
            }
            for (int i = 0; i < 10; ++i) {
                if (CheckCollisionPointRec(GetMousePosition(), {shop[i].position.x, shop[i].position.y, 400, 120})) {
                    shop[i].Buy(money);
                }
            }
        }

//----------------------------------------------------------------------------------



// Draw
//----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKBLUE);
        DrawTexturePro(cookie, {0, 0, 800, 800}, dest, {200, 200}, rotation, WHITE);
        for (int i = 0; i < 10; ++i) {
            DrawRectangleV(shop[i].position, shop[i].size, shop[i].boxColor);
            if (i != 9) {
                DrawText(TextFormat("%.01f clicks per second", 60.0 / shop[i].trigger), shop[i].position.x,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         BLACK);
            }
            if (i == 0) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 30,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (i == 1) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 40,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (i == 2) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 50,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (2 < i && i < 5) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 60,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (i == 5) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 70,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (5 < i && i < 8) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 75,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (i == 8) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 80,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            else if (i == 9) {
                DrawText(TextFormat("%01i", shop[i].value), shop[i].position.x + shop[i].size.x - 100,
                         shop[i].position.y + shop[i].size.y - 25, 30,
                         shop[i].textColor);
            }
            if (i == 9) {
                DrawText(shop[i].name.c_str(), shop[i].position.x, shop[i].position.y, 40, GOLD);
            } else {
                DrawText(shop[i].name.c_str(), shop[i].position.x, shop[i].position.y, 40, BLACK);
            }
            if (shop[i].bought) {
                DrawText("BOUGHT", shop[i].position.x + 25, shop[i].position.y + 25, 80, RED);
            }
        }
        DrawText(TextFormat("Money: %01i", money), 880, 30, 40, GREEN);
        DrawRectangleV(WinBGPos, {1920, 1050}, WHITE);
        DrawText("You win! :D", WinTextPos.x, WinTextPos.y, 70, BLACK);

        EndDrawing();
//----------------------------------------------------------------------------------
    }

// De-Initialization
//--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
//--------------------------------------------------------------------------------------

    return 0;
}