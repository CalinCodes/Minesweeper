#include<SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace sf;
bool ok;
int grid_width = 10, grid_height = 10, grid[12][12], sgrid[12][12];
void reset()
{
    ok = 1;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)  grid[i][j] = 9;
            else grid[i][j] = 0;
        }
    }


    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            grid[i][j] = n;
        }
    }
}
void show_tile(int i, int j)
{
    if (i >= 1 && i <= grid_height && j >= 1 && j <= grid_width && sgrid[i][j] >= 10)
    {
        sgrid[i][j] = grid[i][j];
        if (grid[i][j] == 9)
        {
            ok = 0;
        }

        if (grid[i][j] == 0)
        {
            show_tile(i+1, j);
            show_tile(i-1, j);
            show_tile(i, j+1);
            show_tile(i, j-1);
            show_tile(i+1, j+1);
            show_tile(i-1, j+1);
            show_tile(i+1, j-1);
            show_tile(i-1, j-1);
        }
    }
}
int main()
{
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    
    ok = 1;
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");
    app.setFramerateLimit(60);
    int w = 32;

    Texture t;
    t.loadFromFile("tiles.jpg");
    Sprite s(t);

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)  grid[i][j] = 9;
            else grid[i][j] = 0;
        }
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            grid[i][j] = n;
        }
    }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        int x = pos.x / w;
        int y = pos.y / w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed && ok==1)
            {
                if (e.key.code == Mouse::Left) show_tile(x, y);
                else if (e.key.code == Mouse::Right && sgrid[x][y]>=10)
                {
                    if (sgrid[x][y] == 11) sgrid[x][y] = 10;
                    else sgrid[x][y] = 11;
                }
            }

            if (e.type == Event::KeyPressed)
            {
                if (e.key.scancode == Keyboard::Scan::R)
                {
                    reset();
                }
            }
        }

        app.clear(Color::White);

        for (int i = 1; i <= 10; i++)
        {
            for (int j = 1; j <= 10; j++)
            {
                if (ok == 0)
                {
                    sgrid[i][j] = grid[i][j];
                }
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                app.draw(s);
            }
        }

        app.display();
    }

    return 0;
}