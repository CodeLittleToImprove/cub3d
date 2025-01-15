#include <stdio.h>
#include <math.h>

// Beispielkarte (0 = leer, 1 = Wand)
int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

// Funktion zum Zeichnen der Karte mit aktueller Strahlposition
void drawMap(int map[8][8], int playerX, int playerY, int rayX, int rayY) {
    printf("\nAktuelle Karte:\n");
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (x == playerX && y == playerY)
                printf("P "); // Spielerposition
            else if (x == rayX && y == rayY)
                printf("* "); // Aktuelle Strahlposition
            else if (map[y][x] == 1)
                printf("# "); // Wand
            else
                printf(". "); // Leer
        }
        printf("\n");
    }
}

int main() {
    // Spielerposition
    double posX = 3.5, posY = 3.5;

    // Strahlrichtung
    double rayDirX = 1.0, rayDirY = 0.5;

    // Aktuelle Zelle
    int mapX = (int)posX;
    int mapY = (int)posY;

    // Schrittweite berechnen
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    // Schritt und initiale Seiten-Distanz berechnen
    int stepX, stepY;
    double sideDistX, sideDistY;

    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }

    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    // DDA-Loop
    int hit = 0;
    int side;
    printf("Start des DDA-Algorithmus:\n");
    while (hit == 0) {
        // Karte zeichnen
        drawMap(map, (int)posX, (int)posY, mapX, mapY);

        // Bewege den Strahl zur nächsten Zelle
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // Wand auf x-Achse
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // Wand auf y-Achse
        }

        // Überprüfen, ob eine Wand getroffen wurde
        if (map[mapY][mapX] > 0) {
            hit = 1;
            printf("\nWand getroffen bei (%d, %d)\n", mapX, mapY);
        }
    }

    // Distanz zur Wand berechnen
    double perpWallDist;
    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

    // Endausgabe
    printf("Distanz zur Wand: %f\n", perpWallDist);

    return 0;
}
