#include "include/raylib.h"
#include "vector"
#include <iostream>

Texture2D UP;
Texture2D RIGHT;
Texture2D LEFT;
Texture2D DOWN;
Texture2D UP_LEFT;
Texture2D UP_RIGHT;
Texture2D DOWN_RIGHT;
Texture2D DOWN_LEFT;
Texture2D BULLET;

std::vector<Vector2> bullets_pos;
std::vector<Vector2> bullets_dir;
const int MAXIMUM_BULLETS = 20;

void MovePlayer(Vector2& pos, int speed, int width, int height) {
    float vcorrere = (float)speed;
    // Modifica la velocità in quella di corsa se SHIFT è premuto
    if (IsKeyDown(KEY_LEFT_SHIFT)){
        vcorrere = (float)speed * 1.5f;
    }
    // Muove il personaggio in base ai tasti WASD premuti
    if (IsKeyDown(KEY_D)){
        pos.x += vcorrere;
    }
    if (IsKeyDown(KEY_A) ){
        pos.x -= vcorrere;
    }
    if (IsKeyDown(KEY_W)){
        pos.y -= vcorrere;
    }
    if(IsKeyDown(KEY_S)){
        pos.y += vcorrere;
    }
    // Resetta la posizione al centro dello schermo se il player esce dai limiti
    if (pos.y > height || pos.y < 0 || pos.x < 0 || pos.x > width){
        pos.x = (float)width / 2;
        pos.y = (float)height / 2;
    }
}

void RotatePlayer(Vector2& dir) {
    if (dir.x != 0 || dir.y != 0) {
        if (IsKeyDown(KEY_UP)) {
            dir.y = -1;
        } else if (IsKeyDown(KEY_DOWN)) {
            dir.y = 1;
        } else {
            dir.y = 0;
        }

        if (IsKeyDown(KEY_LEFT)) {
            dir.x = -1;
        } else if (IsKeyDown(KEY_RIGHT)) {
            dir.x = 1;
        } else {
            dir.x = 0;
        }
    }
}

Texture2D current_texture;
void DrawPlayer(Vector2 dir, Vector2 pos) {
    if(current_texture.id <= 0) {
        current_texture = UP;
    } else if (dir.y == -1 && dir.x == -1) {
        current_texture = UP_LEFT;
    } else if (dir.y == -1 && dir.x == 1) {
        current_texture = UP_RIGHT;

    } else if (dir.y == 1 && dir.x == -1){
        current_texture = DOWN_LEFT;

    }else if (dir.y == 1 && dir.x == 1){
        current_texture = DOWN_RIGHT;

    }else if (dir.y == -1){
        current_texture = UP;
    }
    else if (dir.x == 1){
        current_texture = RIGHT;

    }
    else if (dir.x == -1){
        current_texture = LEFT;

    }
    else if (dir.y == 1){
        current_texture = DOWN;

    }
    DrawTextureEx(current_texture, pos, 0, 2, WHITE);
}

void PlayerShoot(Vector2 dir, Vector2 pos) {
    if (IsKeyPressed(KEY_SPACE)) {
        if (bullets_pos.size() < MAXIMUM_BULLETS) {
            bullets_pos.push_back(pos);
            bullets_dir.push_back(dir);
        } else {
            bullets_pos.erase(bullets_pos.begin());
            bullets_dir.erase(bullets_dir.begin());
        }
    }
}

void MoveBullets(float speed) {
    int erased_bullets = 0;
    for (int i = 0; i < bullets_dir.size(); i++) {
        Vector2 dir = bullets_dir[i];
        Vector2& pos = bullets_pos[i];

        if (i > bullets_dir.size() - erased_bullets) {
            break;
        }

        if (dir.y == -1 && dir.x == -1) {
            pos.x -= speed;
            pos.y -= speed;
        } else if (dir.y == -1 && dir.x == 1) {
            pos.x += speed;
            pos.y -= speed;
        } else if (dir.y == 1 && dir.x == -1){
            pos.x -= speed;
            pos.y += speed;
        }else if (dir.y == 1 && dir.x == 1){
            pos.x += speed;
            pos.y += speed;
        }else if (dir.y == -1){
            pos.y -= speed;
        }
        else if (dir.x == 1){
            pos.x += speed;
            std::cout << "Movin'";
        }
        else if (dir.x == -1){
            pos.x -= speed;
        }
        else if (dir.y == 1){
            pos.y += speed;
        }

    }
}

void DrawBullets() {
    for (int i = 0; i < bullets_pos.size(); i++) {
        Vector2 pos = bullets_pos[i];
        DrawTexture(BULLET, (int)pos.x, (int)pos.y, WHITE);
    }
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1980;
    const int screenHeight = 1080;

    Vector2 player_pos;
    player_pos.x = 400;
    player_pos.y = 400;
    Vector2 player_dir;
    player_dir.y = 1;
    player_dir.x = 0;
    const int speed = 2;

    InitWindow(screenWidth, screenHeight, "Diller");

    UP = LoadTexture("../Assets/su.png");
    DOWN = LoadTexture("../Assets/giu.png");
    LEFT = LoadTexture("../Assets/sinistra.png");
    RIGHT = LoadTexture("../Assets/destra.png");
    UP_LEFT = LoadTexture("../Assets/susinistra.png");
    UP_RIGHT = LoadTexture("../Assets/sudestra.png");
    DOWN_LEFT = LoadTexture("../Assets/giuleft.png");
    DOWN_RIGHT = LoadTexture("../Assets/giudestra.png");
    BULLET = LoadTexture("../Assets/bullet.png");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------d
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Logica Player
        MovePlayer(player_pos, speed, GetScreenWidth(), GetScreenHeight());
        RotatePlayer(player_dir);
        PlayerShoot(player_dir, player_pos);

        // Logica proiettili
        MoveBullets(speed * 4);

        BeginDrawing();

        DrawBullets();
        DrawPlayer(player_dir, player_pos);

        ClearBackground(GRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}