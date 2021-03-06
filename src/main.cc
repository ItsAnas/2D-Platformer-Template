#include <vector>

#include "player.hh"
#include "raylib.h"
#include "raymath.h"
#include "world.hh"
#include "world_bloc.hh"

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

typedef struct EnvItem
{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

void UpdatePlayer(Player &player, World world, int envItemsLength, float delta);
void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player &player, float delta,
                                  int width, int height);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib 2D Platformer template");

    Player player(Vector2{ 400, 280 });

    World world({ { { 0, 0, 1000, 400 }, 0, LIGHTGRAY },
                  { { 0, 400, 1000, 200 }, 1, GRAY },
                  { { 300, 200, 400, 10 }, 1, GRAY },
                  { { 250, 300, 100, 10 }, 1, GRAY },
                  { { 650, 300, 100, 10 }, 1, GRAY } });

    int envItemsLength = world.CountBlocks();

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Store pointers to the multiple update camera functions
    void (*cameraUpdaters[])(Camera2D *, Player &, float, int,
                             int) = { UpdateCameraPlayerBoundsPush };

    int cameraOption = 0;
    int cameraUpdatersLength =
        sizeof(cameraUpdaters) / sizeof(cameraUpdaters[0]);

    char *cameraDescriptions[] = { (
        char *)"Player push camera on getting too close to screen edge" };

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        UpdatePlayer(player, world, envItemsLength, deltaTime);

        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f)
            camera.zoom = 0.25f;

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            player.position = Vector2{ 400, 280 };
        }

        if (IsKeyPressed(KEY_C))
            cameraOption = (cameraOption + 1) % cameraUpdatersLength;

        // Call update camera function by its pointer
        cameraUpdaters[cameraOption](&camera, player, deltaTime, screenWidth,
                                     screenHeight);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);

        world.Draw();

        Rectangle playerRect = { player.position.x - 20, player.position.y - 40,
                                 40, 40 };
        DrawRectangleRec(playerRect, RED);

        EndMode2D();

        DrawText("Controls:", 20, 20, 10, BLACK);
        DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
        DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
        DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10,
                 DARKGRAY);
        DrawText("Current camera mode:", 20, 120, 10, BLACK);
        DrawText(cameraDescriptions[cameraOption], 40, 140, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdatePlayer(Player &player, /*EnvItem */ /*envItems*/ World world,
                  int envItemsLength, float delta)
{
    if (IsKeyDown(KEY_LEFT))
        player.position.x -= PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_RIGHT))
        player.position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_SPACE) && player.canJump)
    {
        player.speed = -PLAYER_JUMP_SPD;
        player.canJump = false;
    }

    bool hitObstacle = world.CheckCollision(player, delta);

    if (!hitObstacle)
    {
        player.position.y += player.speed * delta;
        player.speed += G * delta;
        player.canJump = false;
    }
    else
        player.canJump = true;
}

void UpdateCameraPlayerBoundsPush(Camera2D *camera, Player &player, float delta,
                                  int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D(
        Vector2{ (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height },
        *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D(
        Vector2{ (1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height },
        *camera);
    camera->offset =
        Vector2{ (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height };

    if (player.position.x < bboxWorldMin.x)
        camera->target.x = player.position.x;
    if (player.position.y < bboxWorldMin.y)
        camera->target.y = player.position.y;
    if (player.position.x > bboxWorldMax.x)
        camera->target.x =
            bboxWorldMin.x + (player.position.x - bboxWorldMax.x);
    if (player.position.y > bboxWorldMax.y)
        camera->target.y =
            bboxWorldMin.y + (player.position.y - bboxWorldMax.y);
}