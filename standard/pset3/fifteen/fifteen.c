/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// macro to print the tiles, '_' on empty tile
#define EMPTY 0
#define PRINT_TILES(i,j)    board[i][j] == EMPTY ? printf(" _ ") : printf("%2d ", board[i][j]);

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// tiles values mapped to position
int tile_position[MAX*MAX][2];

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int eucDistance(int x[], int y[]);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(100000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // TODO
    int tile_value = (d * d) - 1;
    board[d-1][d-1] = EMPTY;

    // fill the tiles in descending order
    for (int i = 0; i < d; i++)
        for (int j = 0; j < d; j++)
            board[i][j] = tile_value--;

    // save the tiles locations
    tile_value = (d * d) - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            tile_position[tile_value][0] = i;
            tile_position[tile_value][1] = j;
            tile_value--;
        }
    }

    // if the board has an odd number of tiles
    if(d % 2 == 0)
    {
        // Swap values 1 and 2
        int temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;

        // Swap positions
        int val1[] = {tile_position[1][0], tile_position[1][1]};
        int val2[] = {tile_position[2][0], tile_position[2][1]};
        tile_position[1][0] = val2[0];
        tile_position[1][1] = val2[1];
        tile_position[2][0] = val1[0];
        tile_position[2][1] = val1[1];
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
            PRINT_TILES(i,j)
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO
    if (tile > 0 && tile < (d*d))
    {
        int x[] = {tile_position[tile][0], tile_position[tile][1]};
        int y[] = {tile_position[EMPTY][0], tile_position[EMPTY][1]};

        if(eucDistance(x,y) == 1)
        {
            // Swap tile and empty values
            int temp = board[x[0]][x[1]];
            board[x[0]][x[1]] = board[y[0]][y[1]];
            board[y[0]][y[1]] = temp;

            // Update position
            tile_position[tile][0] = y[0];
            tile_position[tile][1] = y[1];
            tile_position[EMPTY][0] = x[0];
            tile_position[EMPTY][1] = x[1];
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

/**
 * Returns the euclidean distance of a pair of vectors
 */
int eucDistance(int x[], int y[])
{
    int a = x[0] - y[0];
    int b = x[1] - y[1];
    return (a*a + b*b);
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // TODO

    int tile_value = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            int x[] = {tile_position[tile_value % (d*d)][0], tile_position[tile_value % (d*d)][1]};
            int y[] = {i, j};
            if (eucDistance(x,y) == 0)
                tile_value++;
            else
                break;
        }
    }

    printf("%10d\n", tile_value );
    if (tile_value == (d*d)+1)
        return true;
    else
        return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
