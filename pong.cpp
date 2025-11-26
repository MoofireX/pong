#include <raylib.h>
#include <string>
using namespace std;

int settings(int current_state){
    while(!WindowShouldClose()){

        if (IsKeyPressed(KEY_UP)){
            if (state < 2){
                state+=1;
            }
            else{
                state = 0;
            }
        }

        if (IsKeyPressed(KEY_DOWN)){
            if (state > 0){
                state-=1;
            }
            else{
                state = 2;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("SETTINGS", 100, 100, 100, RAYWHITE);
        if (state == 0){
            DrawText("Speed: 2", 100, 300, 100, RAYWHITE);
        }
        else if (state == 1){
            DrawText("Speed: 5", 100, 300, 100, RAYWHITE);
        }
        else{
            DrawText("Speed: 8", 100, 300, 100, RAYWHITE);
        }
        EndDrawing();
    }
    return state;
}

int main() {
    InitWindow(800, 600, "Pong");
    SetTargetFPS(120);
    int state = 0;
    int p1_score = 0;
    int p2_score = 0;
    int paddle1_y = 275;
    int paddle2_y = 275;
    int ball_x = 400;
    int ball_y = 300;
    int ball_x_speed = 2;
    int ball_y_speed = 1;
    while (!WindowShouldClose() || p1_score > 15 || p2_score > 15){

        ball_x += ball_x_speed;
        ball_y += ball_y_speed;
        double slope = float(ball_y_speed) / float(ball_x_speed);
        double b = float(ball_y) - slope*float(ball_x);

        if (ball_y <= 0 || ball_y >= 600){
            ball_y_speed*=-1;
        }

        if (ball_x <= 10 ){
            p2_score++;
            ball_x = 400;
            ball_y = 300;
            ball_x_speed = 2;
            ball_y_speed = 1;
        }
        else if (ball_x >= 770){
            p1_score++;
            ball_x = 400;
            ball_y = 300;
            ball_x_speed = -2;
            ball_y_speed = 1;
        }

        if (ball_x_speed < 0 && CheckCollisionCircleRec({float(ball_x),float(ball_y)}, 10, {10, float(paddle1_y), 20, 100})){
            ball_x_speed*=-1;
        }

        if (ball_x_speed > 0 && CheckCollisionCircleRec({float(ball_x),float(ball_y)}, 10, {770, float(paddle2_y), 20, 100})){
            ball_x_speed*=-1;
        }

        if (IsKeyDown(KEY_W) && paddle1_y >=0){
            paddle1_y-=5;
        }
        if (IsKeyDown(KEY_S) && paddle1_y <=500){
            paddle1_y+=5;
        }

        int paddle2_y_pos = slope*770 + b;
        int movement = paddle2_y_pos - paddle2_y;
        float step = movement / 5.0f;
        
        paddle2_y += step;
        if (paddle2_y < 0){
            paddle2_y = 0;
        }
        if (paddle2_y > 500){
            paddle2_y = 500;
        }

        if (IsKeyPressed(KEY_M)){
            int state = settings(state);
            if (state == 0){
                ball_x_speed = 2;
                ball_y_speed = 1;
            }
            else if (state == 1){
                ball_x_speed = 5;
                ball_y_speed = 3;
            }
            else{
                ball_x_speed = 8;
                ball_y_speed = 5;
            }
        }
    
        BeginDrawing();
        ClearBackground(BLUE);
        DrawLine(400,0,400,600,RAYWHITE);
        string p1 = to_string(p1_score);
        string p2 = to_string(p2_score);
        DrawText(p1.c_str(), 150, 50, 100, RAYWHITE);
        DrawText(p2.c_str(), 550, 50, 100, RAYWHITE);
        DrawCircle(ball_x, ball_y, 10, RED);
        DrawRectangle(10, paddle1_y, 20, 100, PURPLE);
        DrawRectangle(770, paddle2_y, 20, 100, ORANGE);
        EndDrawing();

    }
    CloseWindow();
}
