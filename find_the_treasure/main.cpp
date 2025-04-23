#include "include/raylib.h"
#include "iostream"
#include "vector"
#include "chrono"
#include "thread"


struct Person{
    int x;
    int y;
    int columns = 0;
    int rows = 0;
    bool isMoving = false;
};
struct Treasure{
    int x;
    int y;
    bool collected = false;
};
struct Key{
    int x;
    int y;
    bool collected= false;
};
float update_tile_animation(float & x_tile){
    if (x_tile == 7.5){
        x_tile=0;
    } else {
        x_tile+=1.5;
    }
    std::cout<<x_tile;
    std::this_thread::sleep_for(std::chrono::milliseconds(35));
    return x_tile;
}

void draw_tile_static(Texture2D t,int x, int y,float & x_tile, const std::string& direction) {
    Rectangle source = {
            (float)(32 * 0),
            (float)(64 * 0),
            32,
            64
    };
    std::cout<< direction;
    if(direction == "NORTH"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 3);
    }if(direction == "SOUTH"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 0);
    }if(direction == "WEST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 1);
    }if(direction == "EAST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 5);
    }if(direction == "NORTHWEST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 2);
    }if(direction == "SOUTHWEST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 1);
    }if(direction == "NORTHEAST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 4);
    }if(direction == "SOUTHEAST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 5);
    }

    const int scale = 5;
    Rectangle dest = {
            (float)x,
            (float)y,
            32*scale,
            64*scale,
    };
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(t, source, dest, origin, 0, WHITE);
}

void draw_tile_dynamic(Texture2D t,int x, int y,float & x_tile, const std::string& direction) {
    Rectangle source = {
            (float)(32 * 0),
            (float)(64 * 0),
            32,
            64
    };
    std::cout<< direction;
    if(direction == "NORTH"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 3);
    }if(direction == "SOUTH"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 0);
    }if(direction == "WEST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 1);
    }if(direction == "EAST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 5);
    }if(direction == "NORTHWEST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 2);
    }if(direction == "SOUTHWEST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 1);
    }if(direction == "NORTHEAST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 4);
    }if(direction == "SOUTHEAST"){
        source.x=(float)(32 * update_tile_animation(x_tile));
        source.y=(float)(64 * 5);
    }

    const int scale = 5;
    Rectangle dest = {
            (float)x,
            (float)y,
            32*scale,
            64*scale,
    };
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(t, source, dest, origin, 0, WHITE);
}

void draw_doors (Texture2D t, int max, int Player_columns, int Player_rows){
    Rectangle top = {
            (float)(32 * 0),
            (float)(32 * 2),
            32,
            32
    };
    Rectangle bottom = {
            (float)(32 * 0),
            (float)(32 * 3),
            32,
            32
    };
    Rectangle leftD = {
            (float)(32 * 0),
            (float)(32 * 0),
            32,
            32
    };
    Rectangle rightD = {
            (float)(32 * 0),
            (float)(32 * 1),
            32,
            32
    };
    const int scale = 5;
    Rectangle dest = {
            (float)0,
            (float)0,
            32*scale,
            32*scale,
    };

    Vector2 left = {40.0f, -460.0f};
    Vector2 right = {-1800.0f, -460.0f};
    Vector2 up = {-880.0f, 40.0f};
    Vector2 down = {-880.0f, -955.0f};

    if (Player_rows == 0 && Player_columns == 0) {
        DrawTexturePro(t, rightD, dest, right, 0, WHITE);
        DrawTexturePro(t, bottom, dest, down, 0, WHITE);
    }
    if(Player_rows==0 && Player_columns == max-1){
        DrawTexturePro(t, bottom, dest, down, 0, WHITE);
        DrawTexturePro(t, leftD, dest, left, 0, WHITE);
    }
    if (Player_rows == max-1 && Player_columns == 0) {
        DrawTexturePro(t, top, dest, up, 0, WHITE);
        DrawTexturePro(t, rightD, dest, right, 0, WHITE);
    }
    if (Player_rows == max-1 && Player_columns == max-1) {
        DrawTexturePro(t, top, dest, up, 0, WHITE);
        DrawTexturePro(t, leftD, dest, left, 0, WHITE);
    }
    if (Player_rows == 0 && Player_columns > 0 && Player_columns < max-1){
        DrawTexturePro(t, bottom, dest, down, 0, WHITE);
        DrawTexturePro(t, rightD, dest, right, 0, WHITE);
        DrawTexturePro(t, leftD, dest, left, 0, WHITE);
    }
    if (Player_rows == max-1 && Player_columns > 0 && Player_columns < max-1){
        DrawTexturePro(t, top, dest, up, 0, WHITE);
        DrawTexturePro(t, rightD, dest, right, 0, WHITE);
        DrawTexturePro(t, leftD, dest, left, 0, WHITE);
    }
    if (Player_columns == 0 && Player_rows > 0 && Player_rows < max-1){
        DrawTexturePro(t, bottom, dest, down, 0, WHITE);
        DrawTexturePro(t, rightD, dest, right, 0, WHITE);
        DrawTexturePro(t, top, dest, up, 0, WHITE);
    }
    if (Player_columns == max-1 && Player_rows > 0 && Player_rows < max-1){
        DrawTexturePro(t, top, dest, up, 0, WHITE);
        DrawTexturePro(t, bottom, dest, down, 0, WHITE);
        DrawTexturePro(t, leftD, dest, left, 0, WHITE);
    }
    if (Player_columns > 0 && Player_columns < max-1 && Player_rows > 0 && Player_rows < max-1){
        DrawTexturePro(t, top, dest, up, 0, WHITE);
        DrawTexturePro(t, bottom, dest, down, 0, WHITE);
        DrawTexturePro(t, leftD, dest, left, 0, WHITE);
        DrawTexturePro(t, rightD, dest, right, 0, WHITE);
    }
}
void draw_treasure(Texture2D t,int room_x, int room_y, int Player_columns, int Player_rows, bool &collected) {
    Rectangle source = {
            (float)(32 * 4),
            (float)(32 * 0),
            32,
            32
    };
    const int scale = 6;
    Rectangle dest = {
            (float)870,
            (float)420,
            32*scale,
            32*scale,
    };
    Vector2 origin = {0.0f, 0.0f};
    if (room_x == Player_rows && room_y == Player_columns && collected == false) {
        DrawTexturePro(t, source, dest, origin, 0, WHITE);
    }
}
void draw_keys(Texture2D t,std::vector <Key> key,int Player_columns, int Player_rows){
    Rectangle source = {
            (float)(16 * 1),
            (float)(16 * 0),
            16,
            16
    };
    const int scale = 2;
    Rectangle dest = {
            (float)935,
            (float)515,
            32*scale,
            32*scale,
    };
    Vector2 origin = {0.0f, 0.0f};
    for (int i = 0; i < key.size(); ++i) {
        if (key.at(i).x==Player_rows && key.at(i).y == Player_columns){
            if (key.at(i).collected == false){
                DrawTexturePro(t, source, dest, origin, 0, WHITE);
            }
        }
    }
}
void collect_keys (std::vector <Key> & key,int Player_columns, int Player_rows, int Player_x, int Player_y, int &keys){
    for (int i = 0; i < key.size(); ++i) {
        if (key.at(i).x==Player_rows && key.at(i).y == Player_columns){
            if (Player_x >= 930 && Player_x <= 990 && Player_y >= 510 && Player_y <= 570 && key.at(i).collected == false) {
                key.at(i).collected=true;
                keys++;
            }
        }
    }
}
void collect_treasure (int Player_x, int Player_y, bool &collected) {
    if (Player_x >= 870 && Player_x <= 1062 && Player_y >= 420 && Player_y <= 612 && !collected) {
        collected = true;
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    int max = 3;
    float anim=0;
    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "TEST");



    std::vector<Key> v;

    while (v.size() < max) {
        bool add = true;
        Key key {
            rand() % max,
            rand() % max,
        };

        if (key.x == 0 && key.y == 0) {
            add = false;
        }

        for (int i = 0; i < v.size() && add; i++) {
            if (key.x == v.at(i).x && key.y == v.at(i).y) {
                add = false;
            }
        }
        if (add) {
            v.push_back(key);
        }
    }

    for (int i = 0; i < max; ++i) {
        std::cout<<v.at(i).x<<v.at(i).y<<std::endl;
    }



    Person Player;
    Player.y=screenHeight/2;
    Player.x=screenWidth/2;
    Player.columns = 0;
    Player.rows = 0;
    Player.isMoving = false;

    Texture2D playerTexture1 = LoadTextureFromImage(LoadImage("../res/idle.png"));
    Texture2D playerTexture2 = LoadTextureFromImage(LoadImage("../res/walk.png"));
    Texture2D keyTexture = LoadTextureFromImage(LoadImage("../res/key.png"));
    Texture2D chestTexture = LoadTextureFromImage(LoadImage("../res/Treasure.png"));
    Texture2D mapTexture = LoadTextureFromImage(LoadImage("../res/Map.png"));
    Texture2D doors = LoadTextureFromImage(LoadImage("../res/Doors.png"));
    Texture2D bckgnd1 = LoadTextureFromImage(LoadImage("../res/Background1.png"));
    Texture2D bckgnd2 = LoadTextureFromImage(LoadImage("../res/Background2.png"));

    int rany=rand()%max;
    int ranx=rand()%max;

    bool compatible=false;
    int check=0;

    while(compatible == false){

        for (int i = 0; i < v.size(); ++i) {
            if (ranx == v.at(i).x && rany == v.at(i).y || ranx ==0 && rany ==0){
                check++;
            }
        }

        std::cout<<ranx<<rany<<std::endl;

        if (check==0){
            compatible=true;
        }

        else{
            ranx=rand()%max;
            rany=rand()%max;
            check=0;
        }
    }

    int keys_collected=0;



    Treasure rooms;


    rooms.x=ranx;
    rooms.y=rany;
    std::string currentDirection = "NONE";
    int fase=1;

    SetTargetFPS(60);
                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) {
            Player.x += 15;
            Player.y += 15;
            currentDirection = "SOUTHEAST";
            Player.isMoving = true;
        }
        else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) {
            Player.x += 15;
            Player.y -= 15;
            currentDirection = "NORTHEAST";
            Player.isMoving = true;
        }
        else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) {
            Player.x -= 15;
            Player.y -= 15;
            currentDirection = "NORTHWEST";
            Player.isMoving = true;
        }
        else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_S)) {
            Player.x -= 15;
            Player.y += 15;
            currentDirection = "SOUTHWEST";
            Player.isMoving = true;
        }else if (IsKeyDown(KEY_W) && Player.y >= 50) {
            Player.y -= 15;
            currentDirection = "NORTH";
            Player.isMoving = true;
        }
        else if (IsKeyDown(KEY_A) && Player.x >= 50) {
            Player.x -= 15;
            currentDirection = "WEST";
            Player.isMoving = true;
        }
        else if (IsKeyDown(KEY_S) && Player.y <= 1030) {
            Player.y += 15;
            currentDirection = "SOUTH";
            Player.isMoving = true;
        }
        else if (IsKeyDown(KEY_D) && Player.x <= 1870) {
            Player.x += 15;
            currentDirection = "EAST";
            Player.isMoving = true;
        }else{
            Player.isMoving= false;
        }
        if (IsKeyPressed(KEY_F11)){
            ToggleFullscreen();
        }


        if (Player.x >= 885 && Player.x <= 1035 && Player.y >= 1030) {

            if (Player.rows < max-1) {
                Player.rows += 1;
                Player.x = 960;
                Player.y = 75;
            }
        }
        if (Player.x >= 885 && Player.x <= 1035 && Player.y <= 50) {

            if (Player.rows > 0) {
                Player.rows -= 1;
                Player.x = 960;
                Player.y = 1005;
            }
        }
        if (Player.y >= 465 && Player.y <= 615 && Player.x >= 1870) {

            if (Player.columns < max-1) {
                Player.columns += 1;
                Player.x = 75;
                Player.y = 540;
            }
        }
        if (Player.y >= 465 && Player.y <= 615 && Player.x <= 50) {

            if (Player.columns > 0) {
                Player.columns -= 1;
                Player.x = 1845;
                Player.y = 540;
            }
        }

        collect_keys(v,Player.columns,Player.rows,Player.x,Player.y,keys_collected);
        if (keys_collected == max && rooms.x == Player.rows && rooms.y == Player.columns){
            collect_treasure(Player.x, Player.y, rooms.collected);
        }



        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);


        if (fase == 1){
            DrawTexture(bckgnd1,0,0,WHITE);
            if (IsKeyPressed(KEY_ENTER)) {
                fase = 2;
            }
        }if(fase == 2){
            DrawTexture(mapTexture,0,0,WHITE);

            draw_doors(doors,max, Player.columns, Player.rows);

            draw_keys(keyTexture,v,Player.columns,Player.rows);

            draw_treasure(chestTexture,rooms.x, rooms.y, Player.columns, Player.rows, rooms.collected);

            if (Player.isMoving){
                draw_tile_dynamic(playerTexture2, Player.x-120, Player.y-160, anim, currentDirection);
            }else{
                draw_tile_static(playerTexture1, Player.x-120, Player.y-160,anim, currentDirection);
            }

            if (rooms.collected){
                fase = 3;
            }

        }
        if (fase == 3){
            DrawTexture(bckgnd2,0,0,WHITE);

            if (IsKeyPressed(KEY_R)) {
                rooms.collected = false;
                keys_collected = 0;

                Player.x = screenWidth / 2;
                Player.y = screenHeight / 2;
                Player.columns = 0;
                Player.rows = 0;

                v.clear();
                while (v.size() < max) {
                    bool add = true;
                    Key key {
                            rand() % max,
                            rand() % max
                    };

                    if (key.x == 0 && key.y == 0) {
                        add = false;
                    }

                    for (int i = 0; i < v.size() && add; i++) {
                        if (key.x == v.at(i).x && key.y == v.at(i).y) {
                            add = false;
                        }
                    }
                    if (add) {
                        v.push_back(key);
                    }
                }

                rooms.x = rand() % max;
                rooms.y = rand() % max;

                fase=1;
            }

        }



        std::cout<<keys_collected<<std::endl;





        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

