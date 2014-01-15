//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// the window is divided in a grid to help place all alements,
// each cell is squared
#define CELL_WIDTH      10
#define CELL_HEIGHT     CELL_WIDTH

// padding
#define WIN_PADDING     CELL_WIDTH
#define OBJ_PADDING     2

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// size of bricks
#define BRICK_WIDTH     (WIDTH - (2*CELL_WIDTH)) / COLS
#define BRICK_HEIGHT    2*CELL_HEIGHT

// paddle properties
#define PADDLE_WIDTH    3*BRICK_WIDTH
#define PADDLE_HEIGHT   CELL_HEIGHT
#define PADDLE_X        (WIDTH/2) - (PADDLE_WIDTH/2) - OBJ_PADDING
#define PADDLE_Y        HEIGHT - (2*WIN_PADDING) + OBJ_PADDING

// ball properties
#define BALL_DX         0.03
#define BALL_VEL        BALL_DX*BALL_DX*2           // Pithagoras theorem
#define BALL_DY(dx)     (sqrt(BALL_VEL - (dx*dx)))  //  h = ball linear velocity

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);


int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    double bdx = BALL_DX;
    double bdy = BALL_DY(BALL_DX);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;
    // GRect brick[bricks];

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    //
    GObject collisionObject;

    // Wait for the user to click to star the game
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        // Move paddle
        GEvent eMouse = getNextEvent(MOUSE_EVENT);
        if (eMouse != NULL)
        {
            if (getEventType(eMouse) == MOUSE_MOVED)
            {
                double x = getX(eMouse) - getWidth(paddle) / 2;
                setLocation(paddle, x, PADDLE_Y);
            }
        }

        // Move ball
        move(ball,bdx,bdy);
        // bounce off edges
        // left or right
        if ((getX(ball) + getWidth(ball) >= WIDTH) || getX(ball) <= 0)
            bdx *= -1;
        // top
        else if ( getY(ball) <= 0)
            bdy *= -1;
        // bottom: loose a life, reset positions
        else if ((getY(ball) + getHeight(ball) >= HEIGHT))
        {
            lives--;
            setLocation(ball, (WIDTH / 2) - RADIUS,(HEIGHT / 2) - RADIUS);
            setLocation(paddle, PADDLE_X, PADDLE_Y);
            bdx = BALL_DX;
            bdy = BALL_DY(BALL_DX);
            // updateScoreboard(window, label, points);
            waitForClick();
        }

        // Detect collisions
        collisionObject = detectCollision(window, ball);

        if (collisionObject != NULL && strcmp(getType(collisionObject), "GRect") == 0)
        {
            bdy *= -1;
            if (collisionObject != paddle)
            {
                removeGWindow(window, collisionObject);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
                printf("bricks: %d points: %d\n", bricks, points);
            }
        }

    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO

    // brick colors by row
    string brickColors[] = {"RED","ORANGE","YELLOW","BLUE","GREEN"};
    int colorIndex = 0;

    // Last brick positions
    int lastX = (BRICK_WIDTH * (COLS - 1)) + WIN_PADDING;
    int lastY = (BRICK_HEIGHT * (ROWS - 1)) + WIN_PADDING;
    // draw bricks
    for (int y = WIN_PADDING; y <= lastY; y += BRICK_HEIGHT)
    {
        for (int x = WIN_PADDING; x <= lastX; x += BRICK_WIDTH)
        {
            GRect brick = newGRect(x+OBJ_PADDING,y+OBJ_PADDING,BRICK_WIDTH-(2*OBJ_PADDING), BRICK_HEIGHT-(2*OBJ_PADDING));
            setColor(brick,brickColors[colorIndex]);
            setFilled(brick, true);
            add(window, brick);
        }
        colorIndex++;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO

    int x = (WIDTH / 2) - RADIUS;
    int y = (HEIGHT / 2) - RADIUS;
    GOval ball = newGOval(x, y, RADIUS*2, RADIUS*2);
    setFilled(ball, true);

    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO

    GRect paddle = newGRect(PADDLE_X, PADDLE_Y, PADDLE_WIDTH, PADDLE_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");

    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
    setFont(label,"DejaVuSansMono-40");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    setColor(label, "GRAY");

    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
