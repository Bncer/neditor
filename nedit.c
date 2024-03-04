#include <stdio.h>
#include <string.h>
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
    int files = 0;



    while (!WindowShouldClose())
    {

        folder = opendir(".");
        if (folder == NULL)
        {
            puts("Unable to read directory");
            return(1);
        } 

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Folder", 15, 0, 15, GRAY);
            DrawRectangle(0, 20, SCREEN_WIDTH - (SCREEN_WIDTH * 0.805), SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.01), GRAY);

            DrawText("File", screenWidthMid, 0, 15, GRAY);
            DrawRectangle(SCREEN_WIDTH * 0.2, 20, screenWidthStart, SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.01), GRAY);

            files = 0;
            while ((entry = readdir(folder)))
            {
                files++;
                /* printf("File %3d: %s\n", files, entry->d_name); */

                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    DrawRectangle(10, 30 + 20 * files, 200, 20, Fade(BLACK, 0.5f));
                    DrawText(entry->d_name, 35, 36 + 20 * files, 10, WHITE);
                }
            }
            closedir(folder);
        EndDrawing();
    } 

    CloseWindow();
}
