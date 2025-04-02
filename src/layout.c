#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "vendor/cJSON.h"
#include "json_helper.h"
#include "raylib.h"
#include "vendor/raylib/include/raylib.h"

struct Rect {
    int x, y, width, height;
    char* name;
    Color color;
    struct Rect* next;
};

struct Rect* ComputeLayout(cJSON* json, int width, int height)
{
    cJSON* spec = GetObject(json, "specification");
    int rows = GetInt(spec, "rows");
    int cols = GetInt(spec, "cols");

    int grid_width = width / cols;
    int grid_height = height / rows;

    const char* navbarColour = GetString(spec, "navbar_colour");
    printf("rows: %d, cols: %d\n", rows, cols);
    printf("navbar_colour: %s\n", navbarColour);
    
    printf("\n");

    cJSON* tabs = GetArray(spec, "tabs");

    cJSON* system_tab = cJSON_GetArrayItem(tabs, 0);
    assert(system_tab);
    assert(cJSON_IsObject(system_tab));

    const char* system_tab_label = GetString(system_tab, "label");
    printf("Tab: %s\n", system_tab_label);
    
    cJSON* components = GetArray(system_tab, "components");
    cJSON* component = NULL;

    int color_idx = 0;
    Color color_arr[] = {
        RED,
        ORANGE,
        BLUE
    };

    struct Rect* head = NULL;
    struct Rect** cur = &head;
    cJSON_ArrayForEach(component, components) {
        const char* name = GetString(component, "name");
        printf("Component: %s\n", name);

        cJSON* layout = GetObject(component, "layout");

        int row_start = GetInt(layout,  "row_start");
        int row_end   = GetInt(layout,    "row_end");
        int col_start = GetInt(layout,  "col_start");
        int col_end   = GetInt(layout,    "col_end");

        int y = (row_start - 1) * grid_height;
        int x = (col_start - 1) * grid_width;

        int rect_width = ((col_end - col_start) + 1) * grid_width;
        int rect_height = ((row_end - row_start) + 1) * grid_height;

        // Color color = GetColor(color_arr[color_idx++]);

        printf("X: %d, Y: %d, WIDTH: %d, HEIGHT: %d, COLOR: %d\n", x, y, rect_width, rect_height, color_idx);
        *cur = malloc(sizeof(struct Rect));
        **cur = (struct Rect){.x = x, .y = y, .width = rect_width, .height = rect_height, .color = color_arr[color_idx++ % 3], .next = NULL, .name = name};
        cur = &(*cur)->next;
    }

    return head;
}

void DrawLayout(struct Rect* head)
{
    // DrawRectangle(0, 0, 500, 500, BLUE);
    for (struct Rect* cur = head; cur; cur = cur->next)
    {
        DrawRectangle(cur->x, cur->y, cur->width, cur->height, cur->color);
        DrawText(cur->name, cur->x, cur->y, 50, BLACK);
    }
}

int main(void)
{
    ChangeDirectory(GetApplicationDirectory());
    cJSON* json = open_json("resources/test.json");
    const int scale = 1;
    const int screenWidth = 1920 * scale;
    const int screenHeight = 1080 * scale;
    struct Rect* layout = ComputeLayout(json, screenWidth, screenHeight);

    printf("HELLO ______________\n");
    printf("X: %d, Y: %d, WIDTH: %d, HEIGHT: %d\n", layout->x, layout->y, layout->width, layout->height);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            layout = ComputeLayout(json, GetScreenWidth(), GetScreenHeight());
        BeginDrawing();
            ClearBackground(RAYWHITE);
            // DrawRectangle(0, 0, 960, 540, RED);
            DrawLayout(layout);
        EndDrawing();
    }

    CloseWindow();
    cJSON_free(json);
    return 0;
}


