#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(420, 530), "Minesweeper!");

    int w = 32;
    const int gridSize = 13; 
    int grid[gridSize][gridSize];
    int sgrid[gridSize][gridSize]; 

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    Font font;
    font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf"); // zmien na windows

    Text gameOverText;
    gameOverText.setFont(font); 
    gameOverText.setCharacterSize(24); 
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("Przegrales!"); 
    gameOverText.setPosition((app.getSize().x - gameOverText.getLocalBounds().width) / 2, app.getSize().y - 120); 

    RectangleShape gameOverBg(Vector2f(gameOverText.getLocalBounds().width + 40, 50));
    gameOverBg.setOrigin(gameOverText.getLocalBounds().width / 2 + 20, 25);
    gameOverBg.setPosition(app.getSize().x / 2, app.getSize().y - 110);
    gameOverBg.setFillColor(Color(192, 192, 192)); //szare przycisk tło

    RectangleShape resetButton(Vector2f(150, 50));
    resetButton.setOrigin(75, 25);
    resetButton.setPosition(app.getSize().x / 2, app.getSize().y - 50);
    resetButton.setFillColor(Color(192, 192, 192)); //szary przycisk
    resetButton.setOutlineThickness(2);
    resetButton.setOutlineColor(Color::Black);

    Text resetButtonText;
    resetButtonText.setFont(font);
    resetButtonText.setCharacterSize(20);
    resetButtonText.setFillColor(Color::Black);
    resetButtonText.setString("Zresetuj gre");
    resetButtonText.setPosition(resetButton.getPosition().x - resetButtonText.getLocalBounds().width / 2.0f, resetButton.getPosition().y - resetButtonText.getLocalBounds().height / 2.0f);

    bool gameLost = false;

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)
                grid[i][j] = 9;
            else
                grid[i][j] = 0;
        }
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            int n = 0;
            if (grid[i][j] == 9)
                continue;
            if (grid[i + 1][j] == 9)
                n++;
            if (grid[i][j + 1] == 9)
                n++;
            if (grid[i - 1][j] == 9)
                n++;
            if (grid[i][j - 1] == 9)
                n++;
            if (grid[i + 1][j + 1] == 9)
                n++;
            if (grid[i - 1][j - 1] == 9)
                n++;
            if (grid[i - 1][j + 1] == 9)
                n++;
            if (grid[i + 1][j - 1] == 9)
                n++;
            grid[i][j] = n;
        }
    }

    while (app.isOpen()) {
        Event e;
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();

            if (!gameLost && e.type == Event::MouseButtonPressed) {
                Vector2i pos = Mouse::getPosition(app);
                int x = pos.x / w;
                int y = pos.y / w;
                if (e.mouseButton.button == Mouse::Left) {
                    if (grid[x][y] == 9) { // juz nic nie zostlo tylko smierc
                        gameLost = true;
                        for (int i = 1; i <= 10; i++) {
                            for (int j = 1; j <= 10; j++) {
                                sgrid[i][j] = grid[i][j];
                            }
                        }
                    } else {
                        sgrid[x][y] = grid[x][y];
                    }
                } else if (e.mouseButton.button == Mouse::Right) {
                    sgrid[x][y] = 11; //falaga
                }
            }

            if (gameLost && e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
                Vector2i pos = Mouse::getPosition(app);
                int x = pos.x;
                int y = pos.y;
                if (x >= resetButton.getPosition().x - resetButton.getSize().x / 2 && x <= resetButton.getPosition().x + resetButton.getSize().x / 2 && y >= resetButton.getPosition().y - resetButton.getSize().y / 2 && y <= resetButton.getPosition().y + resetButton.getSize().y / 2) {
                    // Resut game
                    gameLost = false;
                    for (int i = 1; i <= 10; i++) {
                        for (int j = 1; j <= 10; j++) {
                            sgrid[i][j] = 10;
                            if (rand() % 5 == 0)
                                grid[i][j] = 9;
                            else
                                grid[i][j] = 0;
                        }
                    }

                    for (int i = 1; i <= 10; i++) {
                        for (int j = 1; j <= 10; j++) {
                            int n = 0;
                            if (grid[i][j] == 9)
                                continue;
                            if (grid[i + 1][j] == 9)
                                n++;
                            if (grid[i][j + 1] == 9)
                                n++;
                            if (grid[i - 1][j] == 9)
                                n++;
                            if (grid[i][j - 1] == 9)
                                n++;
                            if (grid[i + 1][j + 1] == 9)
                                n++;
                            if (grid[i - 1][j - 1] == 9)
                                n++;
                            if (grid[i - 1][j + 1] == 9)
                                n++;
                            if (grid[i + 1][j - 1] == 9)
                                n++;
                            grid[i][j] = n;
                        }
                    }
                }
            }
        }

        app.clear(Color(192, 192, 192)); 

        for (int i = 1; i <= 10; i++) {
            for (int j = 1; j <= 10; j++) {
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                app.draw(s);
            }
        }

        if (gameLost) {
            app.draw(gameOverBg);
            app.draw(gameOverText);
            app.draw(resetButton);
            app.draw(resetButtonText);
        }

        app.display();
    }

    return 0;
}
