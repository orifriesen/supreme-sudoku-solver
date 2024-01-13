#include <iostream>
#include<SFML/Graphics.hpp>
#include<string>

using namespace std;
using namespace sf;

#define N 9
/* This function returns a number based on which number the user enters*/
int numberPicking() {
    int number = 0, waitCounter = 0;
    while(number >= 0) {
        if(Keyboard::isKeyPressed(Keyboard::Return) or Mouse::isButtonPressed(Mouse::Left)) {
            return -1;
        }
        if(Keyboard::isKeyPressed(Keyboard::BackSpace)) {
            return 0;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num1)) {
            return 1;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num2)) {
            return 2;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num3)) {
            return 3;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num4)) {
            return 4;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num5)) {
            return 5;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num6)) {
            return 6;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num7)) {
            return 7;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num8)) {
            return 8;
        }
        if(Keyboard::isKeyPressed(Keyboard::Num9)) {
            return 9;
        }

        /* Do something to avoid crashing */
        waitCounter++;
    }
}

/* This is for turning a number into a string to put into the array for displaying in SFML*/
string numberPickingString(int numberSelected) {
    if (numberSelected == 0) {
        return "";
    }
    if (numberSelected == 1) {
        return "1";
    }
    if (numberSelected == 2) {
        return "2";
    }
    if (numberSelected == 3) {
        return "3";
    }
    if (numberSelected == 4) {
        return "4";
    }
    if (numberSelected == 5) {
        return "5";
    }
    if (numberSelected == 6) {
        return "6";
    }
    if (numberSelected == 7) {
        return "7";
    }
    if (numberSelected == 8) {
        return "8";
    }
    if (numberSelected == 9) {
        return "9";
    }
}

bool FindUnassignedLocation(int grid[N][N], int &row, int &column);
bool isLegal(int grid[N][N], int row, int column, int numberSelected);

/* This assigns values to all the unassigned spots in the Sudoku grid */
bool SolveSudoku(int grid[N][N])
{
    int row, column;
    if (!FindUnassignedLocation(grid, row, column))
       return true;
    for (int numberSelected = 1; numberSelected <= 9; numberSelected++)
    {
        if (isLegal(grid, row, column, numberSelected))
        {
            grid[row][column] = numberSelected;
            if (SolveSudoku(grid))
                return true;
            grid[row][column] = 0;
        }
    }
    return false;
}

/* This searches the grid to find unassigned locations */
bool FindUnassignedLocation(int grid[N][N], int &row, int &column)
{
    for (row = 0; row < N; row++)
        for (column = 0; column < N; column++)
            if (grid[row][column] == 0)
                return true;
    return false;
}

/* This finds out if the numberSelected is legal in its row. It returns if any matches the numberSelected or if they do not */
bool UsedInRow(int grid[N][N], int row, int numberSelected)
{
    for (int column = 0; column < N; column++)
    if (grid[row][column] == numberSelected)
        return true;
    return false;
}

/* This finds out if the numberSelected is legal in its column. It returns if any matches the numberSelected or if they do not */
bool UsedInColumn(int grid[N][N], int column, int numberSelected)
{
    for (int row = 0; row < N; row++)
        if (grid[row][column] == numberSelected)
            return true;
    return false;
}

/* This finds out if the numberSelected is legal in its specified 3x3 box. It returns if any matches the numberSelected or if they do not */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartcolumn, int numberSelected)
{
    for (int row = 0; row < 3; row++)
        for (int column = 0; column < 3; column++)
            if (grid[row+boxStartRow][column+boxStartcolumn] == numberSelected)
                return true;
    return false;
}

/* This figures out if numberSelected is legal to put it into the row, column position in the grid */
bool isLegal(int grid[N][N], int row, int column, int numberSelected)
{
    return !UsedInRow(grid, row, numberSelected) && !UsedInColumn(grid, column, numberSelected) &&
       !UsedInBox(grid, row - row % 3 , column - column % 3, numberSelected);
}

int main()
{
    /* The first array is the basis of the physical board */
    RectangleShape boardBoxArray[N][N];
    /* This array is what displays the numbers on the board */
    Text boardBoxArrayText[N][N];

    /* These are the x and y values where the board starts */
    int boxPosX = 50;
    int boxPosY = 50;

    bool buttonDown = true;
    bool clickedOnBox = false;
    bool solveBool = false;
    Font font;
    int rowNumber = 0;
    int columnNumber = 0;
    int numberSelected;
    string numberSelectedString;
    string null = " ";

    /* This array is for the inserted values by the user */
    int gridInserted[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    /* This is the array that is used in the algorithm to be solved */
    int grid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    /* Loads font file */
    if (!font.loadFromFile("supreme.ttf")) {
        cout << "Failed to load font" << endl;
    }
    /* Creates the button to solve the puzzle */
    RectangleShape goButton;
    Text goButtonText;
    goButtonText.setFont(font);
    goButton.setSize(Vector2f(150, 50));
    goButton.setPosition(Vector2f(55, 575));
    goButton.setFillColor(Color::Green);
    goButtonText.setString("Solve!");
    goButtonText.setPosition(Vector2f(85, 580));

    /* Creates the button to reset the board */
    RectangleShape resetButton;
    Text resetButtonText;
    resetButtonText.setFont(font);
    resetButton.setSize(Vector2f(150, 50));
    resetButton.setPosition(Vector2f(395, 575));
    resetButton.setFillColor(Color::Red);
    resetButtonText.setString("Clear");
    resetButtonText.setPosition(Vector2f(430, 580));

    /* Creates the button to unsolve the board */
    RectangleShape unsolveButton;
    Text unsolveButtonText;
    unsolveButtonText.setFont(font);
    unsolveButton.setSize(Vector2f(150, 50));
    unsolveButton.setPosition(Vector2f(225, 575));
    unsolveButton.setFillColor(Color::Yellow);
    unsolveButtonText.setString("Unsolve");
    unsolveButtonText.setPosition(Vector2f(240, 580));

    /* Creates the text that prompts for user action */
    Text promptText;
    promptText.setFont(font);
    promptText.setString("Sudoku Solver");
    promptText.setFillColor(Color(255, 255, 255));
    promptText.setPosition(Vector2f(50, 8));

    /* This for loop creates the board using SFML. There is some math involved to do the spacing for the boxes*/
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            boardBoxArray[j][i].setFillColor(Color::White);
            boardBoxArray[j][i].setSize(Vector2f(50, 50));
            boardBoxArray[j][i].setPosition(Vector2f(boxPosX, boxPosY));

            boardBoxArrayText[j][i].setFillColor(Color::Black);
            boardBoxArrayText[j][i].setFont(font);
            boardBoxArrayText[j][i].setCharacterSize(48);
            boardBoxArrayText[j][i].setPosition(Vector2f(boxPosX + 10, boxPosY - 5));

            boxPosX += 55;
            if (j == 8) {
                boxPosX = 50;
            }
            if ((j - 8) % 3 == 0) {
                boxPosX += 5;
            }
        }
        boxPosY += 55;
        boxPosX = 50;
        if ((i + 1) % 3 == 0) {
            boxPosY += 5;
        }
    }

    /* Sets window specifications */
    RenderWindow window(VideoMode(600, 650), "sudoku-solver");
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
            /* Determine when the mouse is released and reset button colors */
            if(event.type == Event::MouseButtonReleased) {
                buttonDown = false;
                goButton.setFillColor(Color::Green);
                goButtonText.setColor(Color::White);
                resetButton.setFillColor(Color::Red);
                resetButtonText.setColor(Color::White);
                unsolveButton.setFillColor(Color::Yellow);
                unsolveButtonText.setColor(Color::White);
            }

        }

        /* If a box is clicked, this initiates the function to choose a number */
        if(clickedOnBox == true and !Mouse::isButtonPressed(Mouse::Left)) {
            int entry = numberPicking();
            if(entry == -1) {
                boardBoxArray[rowNumber][columnNumber].setFillColor(Color(255, 255, 255));
                clickedOnBox = false;
            }
            else {
                numberSelected = entry;
            }
            boardBoxArrayText[rowNumber][columnNumber].setString(numberPickingString(numberSelected));
            gridInserted[columnNumber][rowNumber] = numberSelected;
        }

        /* This detects which box is clicked on and sets clickedOnBox to true so the above if statement runs */
        if(Mouse::isButtonPressed(Mouse::Left) and buttonDown == false) {
            int xPos = Mouse::getPosition(window).x;
            int yPos = Mouse::getPosition(window).y;

            for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                    if(boardBoxArray[j][i].getGlobalBounds().contains(xPos, yPos)) {
                        boardBoxArray[j][i].setFillColor(Color(255, 255, 255, 200));
                        clickedOnBox = true;
                        if(rowNumber != j or columnNumber !=i) {
                            rowNumber = j;
                            columnNumber = i;
                            numberSelected = 0;
                        }
                    }
                }
            }
            /* This detects if the user clicked on the goButton */
            if (goButton.getGlobalBounds().contains(xPos, yPos)) {
                goButton.setFillColor(Color(0, 255, 0, 80));
                goButtonText.setFillColor(Color(255, 255, 255, 80));
                solveBool = true;
            }
            /* This detects if the user clicked on the resetButton */
            if (resetButton.getGlobalBounds().contains(xPos, yPos)) {
                resetButton.setFillColor(Color(255, 0, 0, 80));
                resetButtonText.setFillColor(Color(255, 255, 255, 80));
                for(int i = 0; i < 9; i++) {
                    for(int j = 0; j < 9; j++) {
                        gridInserted[j][i] = 0;
                        boardBoxArrayText[j][i].setString("");
                    }
                }
                solveBool = false;
            }
            /* This detects if the user clicked on the unsolveButton */
            if (unsolveButton.getGlobalBounds().contains(xPos, yPos)) {
                unsolveButton.setFillColor(Color(255, 255, 0, 80));
                unsolveButtonText.setFillColor(Color(255, 255, 255, 80));
                for(int i = 0; i < 9; i++) {
                    for(int j = 0; j < 9; j++) {
                        grid[j][i] = gridInserted[j][i];
                        if(gridInserted[j][i] == 0) {
                            boardBoxArrayText[i][j].setString("");
                        }
                        else {
                            boardBoxArrayText[i][j].setString(numberPickingString(gridInserted[j][i]));
                        }
                    }
                }
                solveBool = false;
            }

            buttonDown = true;
        }

        window.clear(Color::Black);
        window.draw(goButton);
        window.draw(goButtonText);
        window.draw(resetButton);
        window.draw(resetButtonText);
        window.draw(unsolveButton);
        window.draw(unsolveButtonText);
        window.draw(promptText);

        /* This draws the board in the window */
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                window.draw(boardBoxArray[j][i]);
                window.draw(boardBoxArrayText[j][i]);
            }
        }

        /* Shows instructional text when a box is clicked */
        if (clickedOnBox == true) {
            promptText.setString("Enter a number");
        }
        else if (solveBool == false) {
            promptText.setString("Sudoku Solver");
        }

        window.display();

        /* This detects if the goButton was pressed and turns the inserted numbers into the grid that is going to be solved */
        if (solveBool == true) {
            for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                    grid[j][i] = gridInserted[j][i];
                }
            }
        }

        /* This sees if there is a solution, if there is one, it turns the numbers into the strings on the board or displays if there is no solution */
        if (SolveSudoku(grid) == true and solveBool == true) {
            solveBool = false;
            for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                    boardBoxArrayText[j][i].setString(numberPickingString(grid[i][j]));
                }
            }
        }
        else if (solveBool == true){
            promptText.setString("No Solution Found");
        }
    }
}

