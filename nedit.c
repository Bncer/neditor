#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "raylib.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 800

int main() 
{
    const int screenWidthStart = SCREEN_WIDTH - (SCREEN_WIDTH * 0.2);
    const int screenWidthMid = screenWidthStart / 2.0f + (SCREEN_WIDTH * 0.2);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Neditor");

    DIR *folder;
    struct dirent *entry;

    while (!WindowShouldClose())
    {

        folder = opendir(".");
        if (folder == NULL)
        {
            puts("Unable to read directory");
            return(1);
        } 

        int currentProcess = 0;
        int mouseHoverRec = -1;

        int files = 0;
        char **processText = NULL;

        while ((entry = readdir(folder)))
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                processText = realloc(processText, (files + 1) * sizeof(char*));
                processText[files] = malloc(strlen(entry->d_name) + 1);

                strcpy(processText[files], entry->d_name);
                files++;
            }
        }
        int num_processes = files;

        Rectangle *toggleRecs = NULL;

        for (int i = 0; i < num_processes; i++)
        {
            toggleRecs = realloc(toggleRecs, (files + 1) * sizeof(Rectangle));

            toggleRecs[i].x = 30.0f;
            toggleRecs[i].y = (float)(50 + 32*i);
            toggleRecs[i].width = 250.0f;
            toggleRecs[i].height = 30.0f;
        }

        for (int i = 0; i < num_processes; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i]))
            {
                mouseHoverRec = i;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    currentProcess = i;
                }
                break;
            }
            else mouseHoverRec = -1;
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Folder", 15, 0, 15, GRAY);
            DrawRectangle(0, 20, SCREEN_WIDTH - (SCREEN_WIDTH * 0.805), SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.01), GRAY);

            DrawText("File", screenWidthMid, 0, 15, GRAY);
            DrawRectangle(SCREEN_WIDTH * 0.2, 20, screenWidthStart, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.01), GRAY);

            for (int i = 0; i < num_processes; i++)
            {
                DrawRectangleRec(toggleRecs[i], ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY);
                DrawRectangleLines((int)toggleRecs[i].x, (int) toggleRecs[i].y, (int) toggleRecs[i].width, (int) toggleRecs[i].height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
                DrawText( processText[i], (int)( toggleRecs[i].x + toggleRecs[i].width/2 - MeasureText(processText[i], 10)/2), (int) toggleRecs[i].y + 11, 10, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
            }
            for (int i = 0; i < files; i++) {
                free(processText[i]);
            }
            free(processText);
            closedir(folder);
        EndDrawing();
    } 

    CloseWindow();
}
