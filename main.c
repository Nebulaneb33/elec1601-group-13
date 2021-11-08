#include "stdio.h"
#include "stdlib.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <sys/time.h>

#include "formulas.h"
#include "wall.h"
#include "robot.h"
#include "math.h"


int done = 0;
int colours[7][3] = {148, 0, 211, 75, 0, 130, 0, 0, 255, 0, 255, 0, 255, 255, 0, 255, 127, 0, 255, 0, 0};
int colour_counter = 0;
int counter = 0;
int r = 148;
int g = 0;
int b = 211;
int backr = 0;
int backg = 0;
int backb = 50;
int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, front_right_sensor, side_left_sensor, side_right_sensor=0;
    struct timeval start_time, end_time;
    gettimeofday(&start_time, 0);
    unsigned long msec;

// SETUP MAZE
// You can create your own maze here. line of code is adding a wall.
// You describe position of top left corner of wall (x, y), then width and height going down/to right
// Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
// But you can use absolute positions. 10 is used as the width, but you can change this.

//Default Maze
/*
 insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT/2, 10, OVERALL_WINDOW_HEIGHT/2);
 insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-100, OVERALL_WINDOW_HEIGHT/2+100, 10, OVERALL_WINDOW_HEIGHT/2-100);
 insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2+100, 150, 10);
 insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2, 150, 10);
 insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
 insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 10, 100);
 insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-250, OVERALL_WINDOW_HEIGHT/2-200, 450, 10);
 insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-150, OVERALL_WINDOW_HEIGHT/2-100, 250, 10);
 insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2-200, 10, 300);
 insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2-100, 10, 300);
 insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT/2+200, OVERALL_WINDOW_WIDTH/2-100, 10);
 insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+100, OVERALL_WINDOW_WIDTH/2-100, 10);
*/

//horrible maze by evil peers
//main.c
/*
    insertAndSetFirstWall(&head, 1,  OVERALL_WINDOW_WIDTH/2-40, OVERALL_WINDOW_HEIGHT/2-40, 10, 20);
    insertAndSetFirstWall(&head, 2,  OVERALL_WINDOW_WIDTH/2-40, OVERALL_WINDOW_HEIGHT/2-40, 100, 10);
    insertAndSetFirstWall(&head, 3,  OVERALL_WINDOW_WIDTH/2+60, OVERALL_WINDOW_HEIGHT/2-40, 10, 90);
    insertAndSetFirstWall(&head, 4,  OVERALL_WINDOW_WIDTH/2-40, OVERALL_WINDOW_HEIGHT/2+40, 100, 10);
    insertAndSetFirstWall(&head, 5,  OVERALL_WINDOW_WIDTH/2-40, OVERALL_WINDOW_HEIGHT/2+30, 10, 10);
    insertAndSetFirstWall(&head, 6,  OVERALL_WINDOW_WIDTH/2-140, OVERALL_WINDOW_HEIGHT/2-30, 100, 10);
    insertAndSetFirstWall(&head, 7,  OVERALL_WINDOW_WIDTH/2-140, OVERALL_WINDOW_HEIGHT/2-20, 10, 120);
    insertAndSetFirstWall(&head, 8,  OVERALL_WINDOW_WIDTH/2-140, OVERALL_WINDOW_HEIGHT/2+100, 320, 10);
    insertAndSetFirstWall(&head, 9,  OVERALL_WINDOW_WIDTH/2+180, OVERALL_WINDOW_HEIGHT/2-120, 10, 230);
    insertAndSetFirstWall(&head, 10,  OVERALL_WINDOW_WIDTH/2+240, OVERALL_WINDOW_HEIGHT/2-160, 10, 130);
    insertAndSetFirstWall(&head, 11,  OVERALL_WINDOW_WIDTH/2+240, OVERALL_WINDOW_HEIGHT/2-30, 40, 10);
    insertAndSetFirstWall(&head, 12,  OVERALL_WINDOW_WIDTH/2+200, OVERALL_WINDOW_HEIGHT/2+20, 20, 10);
    insertAndSetFirstWall(&head, 13,  OVERALL_WINDOW_WIDTH/2+220, OVERALL_WINDOW_HEIGHT/2+20, 10, 90);
    insertAndSetFirstWall(&head, 14,  OVERALL_WINDOW_WIDTH/2-140, OVERALL_WINDOW_HEIGHT/2-120, 320, 10);
    insertAndSetFirstWall(&head, 15,  OVERALL_WINDOW_WIDTH/2-140, OVERALL_WINDOW_HEIGHT/2-120, 10, 30);
    insertAndSetFirstWall(&head, 16,  0, OVERALL_WINDOW_HEIGHT/2-100, 30, 10);
    insertAndSetFirstWall(&head, 17,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2-100, 10, 260);
    insertAndSetFirstWall(&head, 18,  OVERALL_WINDOW_WIDTH/2-300, OVERALL_WINDOW_HEIGHT/2+160, 600, 10);
    insertAndSetFirstWall(&head, 19,  OVERALL_WINDOW_WIDTH/2+300, OVERALL_WINDOW_HEIGHT/2-200, 10, 370);
    insertAndSetFirstWall(&head, 20,  OVERALL_WINDOW_WIDTH/2-320, OVERALL_WINDOW_HEIGHT/2-200, 620, 10);
    insertAndSetFirstWall(&head, 21,  OVERALL_WINDOW_WIDTH/2-320, OVERALL_WINDOW_HEIGHT/2-200, 10, 40);
    insertAndSetFirstWall(&head, 22,  OVERALL_WINDOW_WIDTH/2+120, OVERALL_WINDOW_HEIGHT/2-80, 10, 110);
    insertAndSetFirstWall(&head, 23,  OVERALL_WINDOW_WIDTH/2-200, OVERALL_WINDOW_HEIGHT/2-140, 10, 160);
    insertAndSetFirstWall(&head, 24,  OVERALL_WINDOW_WIDTH/2-240, OVERALL_WINDOW_HEIGHT/2+60, 80, 10);
    insertAndSetFirstWall(&head, 25,  OVERALL_WINDOW_WIDTH/2-320, OVERALL_WINDOW_HEIGHT/2-160, 100, 10);
    insertAndSetFirstWall(&head, 26,  OVERALL_WINDOW_WIDTH/2+120, OVERALL_WINDOW_HEIGHT/2+20, 40, 10);

*/

// OUR MAZE
/*
insertAndSetFirstWall(&head, 1, OVERALL_WINDOW_WIDTH/2, OVERALL_WINDOW_HEIGHT-150, 10, 150);
insertAndSetFirstWall(&head, 2, 100, OVERALL_WINDOW_HEIGHT-100, OVERALL_WINDOW_WIDTH/2-100, 10);
insertAndSetFirstWall(&head, 3, 0, OVERALL_WINDOW_HEIGHT-10, OVERALL_WINDOW_WIDTH/2, 10);
insertAndSetFirstWall(&head, 4, 0, 0, 10, OVERALL_WINDOW_HEIGHT);
insertAndSetFirstWall(&head, 5, 0, 0, OVERALL_WINDOW_WIDTH, 10);
insertAndSetFirstWall(&head, 6, OVERALL_WINDOW_WIDTH-10, 0, 10, OVERALL_WINDOW_HEIGHT);
insertAndSetFirstWall(&head, 7, OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT-10, OVERALL_WINDOW_WIDTH/2-100, 10);
insertAndSetFirstWall(&head, 8, 100, 100, 10, OVERALL_WINDOW_HEIGHT-300);
insertAndSetFirstWall(&head, 9, 100, 100, OVERALL_WINDOW_HEIGHT-300, 10);
insertAndSetFirstWall(&head, 10, 70, 150, 30, 10);
insertAndSetFirstWall(&head, 11, 0, 200, 40, 10);
insertAndSetFirstWall(&head, 12, OVERALL_WINDOW_HEIGHT-100, 100, 150, 10);
insertAndSetFirstWall(&head, 13, OVERALL_WINDOW_HEIGHT-50, 70, 10, 30);
insertAndSetFirstWall(&head, 14, OVERALL_WINDOW_HEIGHT, 0, 10, 40);
insertAndSetFirstWall(&head, 15, OVERALL_WINDOW_HEIGHT+50, 70, 10, 40);
insertAndSetFirstWall(&head, 16, 100, 50, 200, 10);

for (int i = 0; i < 181; i++) {
    insertAndSetFirstWall(&head, 17, 100 + i, OVERALL_WINDOW_HEIGHT-200 - i, 10, 10);
}

for (int i = 0; i < 280; i++) {
    insertAndSetFirstWall(&head, 18, 100 + i, OVERALL_WINDOW_HEIGHT-100 - i, 10, 10);
}

for (int i = 0; i < 160; i++) {
    insertAndSetFirstWall(&head, 19, OVERALL_WINDOW_HEIGHT-100+i, 200+i, 10, 10);
}

insertAndSetFirstWall(&head, 20, OVERALL_WINDOW_HEIGHT-100, 200, 170, 10);
insertAndSetFirstWall(&head, 21, OVERALL_WINDOW_WIDTH-100, 200, 10, 170);
insertAndSetFirstWall(&head, 22, OVERALL_WINDOW_WIDTH/2+100, OVERALL_WINDOW_HEIGHT-60, OVERALL_WINDOW_WIDTH/2-160, 10);
insertAndSetFirstWall(&head, 23, OVERALL_WINDOW_WIDTH-60, 150, 10, 10);
*/
//Maze 1/2
/*
 insertAndSetFirstWall(&head, 2,  220, 400, 10, 80);
 insertAndSetFirstWall(&head, 2,  20, 400, 200, 10);
 insertAndSetFirstWall(&head, 2,  20, 50, 10, 350);
 insertAndSetFirstWall(&head, 2,  20, 50, 280, 10);
 insertAndSetFirstWall(&head, 2,  300, 50, 10, 100);
 insertAndSetFirstWall(&head, 2,  300, 150, 110, 10);
 insertAndSetFirstWall(&head, 2,  400, 50, 10, 100);
 insertAndSetFirstWall(&head, 2,  400, 50, 220, 10);
 insertAndSetFirstWall(&head, 2,  620, 50, 10, 290);
 insertAndSetFirstWall(&head, 2,  620, 340, 20, 10);

 insertAndSetFirstWall(&head, 1,  320, 300, 10, 180);
 insertAndSetFirstWall(&head, 2,  120, 300, 200, 10);
 insertAndSetFirstWall(&head, 2,  120, 150, 10, 150);
 insertAndSetFirstWall(&head, 2,  120, 150, 80, 10);
 insertAndSetFirstWall(&head, 2,  200, 150, 10, 100);
 insertAndSetFirstWall(&head, 2,  200, 250, 310, 10);
 insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
 insertAndSetFirstWall(&head, 2,  500, 150, 10, 100);
 insertAndSetFirstWall(&head, 2,  500, 150, 20, 10);
 insertAndSetFirstWall(&head, 2,  520, 150, 10, 290);
 insertAndSetFirstWall(&head, 2,  520, 440, 120, 10);
*/

//Maze 3/4
/*
insertAndSetFirstWall(&head, 2,  640-10-220, 400, 10, 80);
insertAndSetFirstWall(&head, 2,  640-200-20, 400, 200, 10);
insertAndSetFirstWall(&head, 2,  640-10-20, 50, 10, 350);
insertAndSetFirstWall(&head, 2,  640-280-20, 50, 280, 10);
insertAndSetFirstWall(&head, 2,  640-10-300, 50, 10, 100);
insertAndSetFirstWall(&head, 2,  640-110-300, 150, 110, 10);
insertAndSetFirstWall(&head, 2,  640-10-400, 50, 10, 100);
insertAndSetFirstWall(&head, 2,  640-400-220, 50, 220, 10);
insertAndSetFirstWall(&head, 2,  640-10-620, 50, 10, 290);
insertAndSetFirstWall(&head, 2,  640-620-20, 340, 20, 10);


insertAndSetFirstWall(&head, 1,  640-10-320, 300, 10, 180);
insertAndSetFirstWall(&head, 2,  640-200-120, 300, 200, 10);
insertAndSetFirstWall(&head, 2,  640-10-120, 150, 10, 150);
insertAndSetFirstWall(&head, 2,  640-80-120, 150, 80, 10);
insertAndSetFirstWall(&head, 2,  640-10-200, 150, 10, 100);
insertAndSetFirstWall(&head, 2,  640-310-200, 250, 310, 10);
insertAndSetFirstWall(&head, 2,  640-10-500, 150, 10, 100);
insertAndSetFirstWall(&head, 2,  640-20-500, 150, 20, 10);
insertAndSetFirstWall(&head, 2,  640-10-520, 150, 10, 290);
insertAndSetFirstWall(&head, 2,  640-120-520, 440, 120, 10);
*/

// Maze 5/6
/*
int i;
insertAndSetFirstWall(&head, 12,  120, 450, 10, 30);
insertAndSetFirstWall(&head, 12,  220, 450, 10, 30);
for (i = 0; i < 100; i++){
     insertAndSetFirstWall(&head, i,  20 + i , 350 + i, 10, 10); //1
     insertAndSetFirstWall(&head, i,  20 +100 + i , 350 + i, 10, 10); //1
 }
 insertAndSetFirstWall(&head, 12,  20, 280, 10, 70);
 insertAndSetFirstWall(&head, 12,  120, 280, 10, 70);
 for (i = 0; i < 180; i++){
     insertAndSetFirstWall(&head, i,  20 +190 - i/2 , 100 + i, 10, 10); //1
 }
 for (i = 0; i < 105; i++){
     insertAndSetFirstWall(&head, i,  20 +105/2 - i/2 , 175 + i, 10, 10); //1
 }
 insertAndSetFirstWall(&head, 2,  20, 175, 105/2, 10);
 insertAndSetFirstWall(&head, 2,  20, 20, 10, 155);
 insertAndSetFirstWall(&head, 2,  20, 20, 300, 10);
 insertAndSetFirstWall(&head, 2,  320, 20, 10, 60);
 insertAndSetFirstWall(&head, 2,  80, 100, 130, 10);
 insertAndSetFirstWall(&head, 2,  80, 80, 10, 20);
 insertAndSetFirstWall(&head, 2,  80, 80, 160, 10);

 double j;
 for (i = 0; i < 50; i++){
     j = i;
     insertAndSetFirstWall(&head, i+1,
                           // the most important bit is below.
                           // increase the 20 for a tighter bend
                           // descrease for a more meandering flow
                           320 + 30*sin(10*j * M_PI/180),
                           // increase the 5 for a spacier curve
                           (i * 5)+80,
                           10, 10);
 }
 for (i = 0; i < 75; i++){
     j = i;
     insertAndSetFirstWall(&head, i+1,
                           // the most important bit is below.
                           // increase the 20 for a tighter bend
                           // descrease for a more meandering flow
                           240 + 30*sin(10*j * M_PI/180),
                           // increase the 5 for a spacier curve
                           (i * 5)+80,
                           10, 10);
 }
 insertAndSetFirstWall(&head, 2,  345, 330, 105, 10);
 insertAndSetFirstWall(&head, 2,  450, 190, 10, 150);
 insertAndSetFirstWall(&head, 2,  380, 190, 70, 10);
 insertAndSetFirstWall(&head, 2,  380, 20, 10, 170);
 insertAndSetFirstWall(&head, 2,  380, 20, 260, 10);

 insertAndSetFirstWall(&head, 2,  255, 455, 345, 10);
 insertAndSetFirstWall(&head, 2,  600, 100, 10, 365);
 insertAndSetFirstWall(&head, 2,  530, 100, 70, 10);
 insertAndSetFirstWall(&head, 2,  530, 80, 10, 20);
 insertAndSetFirstWall(&head, 2,  530, 80, 110, 10);
*/

//MAZE 7/ Maze 8
 int i;
 insertAndSetFirstWall(&head, 12,  640-10-120, 450, 10, 30);
 insertAndSetFirstWall(&head, 12,  640-10-220, 450, 10, 30);

 for (i = 0; i < 100; i++){
     insertAndSetFirstWall(&head, i,  640-10-(20 + i) , 350 + i, 10, 10); //1
     insertAndSetFirstWall(&head, i,  640-10-(20 +100 + i) , 350 + i, 10, 10); //1
 }
 insertAndSetFirstWall(&head, 12,  640-10-20, 280, 10, 70);
 insertAndSetFirstWall(&head, 12,  640-10-120, 280, 10, 70);

 for (i = 0; i < 180; i++){
     insertAndSetFirstWall(&head, i,  640-10-(20 +190 - i/2) , 100 + i, 10, 10); //1
 }
 for (i = 0; i < 105; i++){
     insertAndSetFirstWall(&head, i,  640-10-(20 +105/2 - i/2) , 175 + i, 10, 10); //1
 }


 insertAndSetFirstWall(&head, 2,  640-105/2-20, 175, 105/2, 10);
 insertAndSetFirstWall(&head, 2,  640-10-20, 20, 10, 155);
 insertAndSetFirstWall(&head, 2,  640-300-20, 20, 300, 10);
 insertAndSetFirstWall(&head, 2,  640-10-320, 20, 10, 60);
 insertAndSetFirstWall(&head, 2,  640-130-80, 100, 130, 10);
 insertAndSetFirstWall(&head, 2,  640-10-80, 80, 10, 20);
 insertAndSetFirstWall(&head, 2,  640-160-80, 80, 160, 10);


 double j;
 for (i = 0; i < 50; i++){
     j = i;
     insertAndSetFirstWall(&head, i+1,
                           // the most important bit is below.
                           // increase the 20 for a tighter bend
                           // descrease for a more meandering flow
                           640-10-(320 + 30*sin(10*j * M_PI/180)),
                           // increase the 5 for a spacier curve
                           (i * 5)+80,
                           10, 10);
 }
 for (i = 0; i < 75; i++){
     j = i;
     insertAndSetFirstWall(&head, i+1,
                           // the most important bit is below.
                           // increase the 20 for a tighter bend
                           // descrease for a more meandering flow
                           640-10-(240 + 30*sin(10*j * M_PI/180)),
                           // increase the 5 for a spacier curve
                           (i * 5)+80,
                           10, 10);
 }

 insertAndSetFirstWall(&head, 2,  640-105-345, 330, 105, 10);
 insertAndSetFirstWall(&head, 2,  640-10-450, 190, 10, 150);
 insertAndSetFirstWall(&head, 2,  640-70-380, 190, 70, 10);
 insertAndSetFirstWall(&head, 2,  640-10-380, 20, 10, 170);
 insertAndSetFirstWall(&head, 2,  640-260-380, 20, 260, 10);

 insertAndSetFirstWall(&head, 2,  640-345-255, 455, 345, 10);
 insertAndSetFirstWall(&head, 2,  640-10-600, 100, 10, 365);
 insertAndSetFirstWall(&head, 2,  640-70-530, 100, 70, 10);
 insertAndSetFirstWall(&head, 2,  640-10-530, 80, 10, 20);
 insertAndSetFirstWall(&head, 2,  640-110-530, 80, 110, 10);

setup_robot(&robot);
updateAllWalls(head, renderer, r, g, b);

    SDL_Event event;
    while(!done){
        if (counter < 8) {
            counter++;
        }
        else if (counter == 8) {
            counter = 0;
            colour_counter++;
            if (colour_counter == 7) {
                colour_counter = 0;
            }
        }

        r = colours[colour_counter][0];
        g = colours[colour_counter][1];
        b = colours[colour_counter][2];

        SDL_SetRenderDrawColor(renderer, backr, backg, backb, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands
        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, side_left_sensor, side_right_sensor);
        robotMotorMove(&robot);


        //Check if robot reaches endpoint. and check sensor values
        //if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT/2+100, 10, 100)){ //Default Maze
        //if (checkRobotReachedEnd(&robot, 0, 0, 10, 1000)){ //horrible maze
        //if (checkRobotReachedEnd(&robot, OVERALL_WINDOW_WIDTH/2+10, OVERALL_WINDOW_HEIGHT, 10, 200)){ //Our Maze
        //if (checkRobotReachedEnd(&robot, 640, 340, 10, 100)){ //Maze 1
        // if (checkRobotReachedEnd(&robot, 220, 480, 100, 10)){ //Maze 2
        // if (checkRobotReachedEnd(&robot, 0, 340, 10, 100)){ // Maze 3
        //if (checkRobotReachedEnd(&robot, 640-10-320, 480, 100, 10)){ //Maze 4
         //if (checkRobotReachedEnd(&robot, 640, 20, 10, 60)){ //Maze 5
        // if (checkRobotReachedEnd(&robot, 120, 480, 100, 10)){ //Maze 6
         if (checkRobotReachedEnd(&robot, 0, 20, 10, 60)){ //Maze 7
        // if (checkRobotReachedEnd(&robot, 640-10-220, 480, 100, 10)){ //Maze 8


            gettimeofday(&end_time, 0);
            msec = ((end_time.tv_sec - start_time.tv_sec)*1000)+(end_time.tv_usec - start_time.tv_usec)/1000;
            robotSuccess(&robot, msec);
            backr = 218;
            backg = 165;
            backb = 32;
            colour_counter = 9;
            counter = 9;
            r = 255;
            g = 255;
            b = 255;
        }

        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0)
                printf("Getting close on the front left. Score = %d\n", front_left_sensor);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0)
                printf("Getting close on the front right. Score = %d\n", front_right_sensor);

            side_left_sensor = checkRobotSensorSideLeftAllWalls(&robot, head);
            if (side_left_sensor>0)
                printf("Getting close on the left side. Score = %d\n", side_left_sensor);

            side_right_sensor = checkRobotSensorSideRightAllWalls(&robot, head);
            if (side_right_sensor>0)
                printf("Getting close on the right side. Score = %d\n", side_right_sensor);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer, r, g, b);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                gettimeofday(&start_time, 0);

            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
