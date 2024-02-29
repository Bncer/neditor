#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800
#define BTN_WIDTH 200
#define BTN_HEIGHT 60

int main() 
{

    const int screenWidthStart = SCREEN_WIDTH - (SCREEN_WIDTH * 0.2);
    const int screenWidthMid = screenWidthStart / 2.0f + (SCREEN_WIDTH * 0.2);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neditor");
    
    int btnState = 0; //Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED 
    bool btnAction = false;


    Rectangle btnBounds = {screenWidthMid - BTN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f- BTN_HEIGHT/2.0f , BTN_WIDTH, BTN_HEIGHT}; 

    while (!WindowShouldClose())
    {
        Vector2 mousePoint = GetMousePosition();
        btnAction = false;

        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
            else btnState = 1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
        }
        else btnState = 0;

        if (btnAction)
        {
            printf("Button has been pressed!");
            system("xdg-open ~");
        }

        BeginDrawing();

            DrawText("Folder", 15, 0, 15, GRAY);
            DrawRectangle(0, 20, SCREEN_WIDTH - (SCREEN_WIDTH * 0.805), SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.01), GRAY);


            DrawText("File", screenWidthMid, 0, 15, GRAY);
            DrawRectangle(SCREEN_WIDTH * 0.2, 20, screenWidthStart, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.01), GRAY);
        
            DrawRectangleRec(btnBounds, (btnState == 1) ? LIGHTGRAY : (btnState == 2) ? GRAY : WHITE);
            DrawRectangleLinesEx(btnBounds, 3, BLACK);
            DrawText("Choose project", screenWidthMid - 80.0f, SCREEN_HEIGHT/2.0f - 10.0f, 20, DARKBLUE);

        EndDrawing();
    } 

    CloseWindow();
}
