#include <stdio.h>
#include <raylib.h>

#define Width 5
#define Height 3



struct FluidGrid{
    // Drei Gids erstellen um ein "MAC GRID"/Staggered Grid zu erstellen 

    // Druck wird in der "Zellmitte" gespeichert
    float pressure[Width * Height];
    // X Geschwindigkeit wird an den linken und rechten Wänden 4 deswegen muss das grid eins breiter sein, wenn es 3 Zellen gibt, gibt es 4 wände von links nach rechts
    float velocity_x[(Width + 1) * Height];
    // Y Geschwindigkeit wird an den Wänden Oben und UNten gespeichert, deswegen muss das grid eins höher sein, wenn es 3 Zellen gibt, gibt es 4 wände von unten nach oben
    float velocity_y[Width * (Height + 1)];
};




#define Cell_Size 1.0f //Temporär

// FUnktion zum Errechnen der Divergenz einer Zelle
float divergenceOfCell(struct FluidGrid *grid, int x, int y){

    // Indexe für X Achse Berechnen
    int index_left = y * (Width + 1) + x;
    int index_right = y * (Width + 1) + (x + 1);
    // Indexe für Y Achse Berechnen
    int index_bottom = y * Width + x;
    int index_top = ((y + 1) * Width) + x;

    // Velocities auslesen
    float vel_left = grid->velocity_x[index_left];
    float vel_right = grid->velocity_x[index_right];
    float vel_bottom = grid->velocity_y[index_bottom];
    float vel_top = grid->velocity_y[index_top];

    //Gradienten Berechen
    float gradient_x = (vel_right - vel_left) / Cell_Size;
    float gradient_y = (vel_top - vel_bottom) / Cell_Size;

    //Gesamte Divergenz returnen
    float div = gradient_x + gradient_y;
    return div;
}


void solvePressure(struct FluidGrid *grid, int x, int y){
    float sum_pressure = 0.0f;
    int valid_neighbourCells = 0;
    //Checken ob seiten Valide Cells sind zum druckausgleich
    //Links
    if (x - 1 >= 0){
        sum_pressure += grid->pressure[y * Width + (x - 1)];
        valid_neighbourCells++;
    }
    //Rechts
    if (x + 1 < Width){
        sum_pressure += grid->pressure[y * Width + (x + 1)];
        valid_neighbourCells++;
    }
    //Unten
    if (y - 1 >= 0){
        sum_pressure += grid->pressure[(y - 1) * Width + x];
        valid_neighbourCells++;
    }
    //Oben
    if (y + 1 < Height){
        sum_pressure += grid->pressure[(y + 1) * Width + x];
        valid_neighbourCells++;
    }

    float divergence = divergenceOfCell(grid, x, y);

    float new_pressure = (sum_pressure - divergence) / valid_neighbourCells;

    grid->pressure[y * Width + x] = new_pressure;

}








int main(){
    // initialisieren und Clearen
    struct FluidGrid grid;

    for (int i = 0; i < Width * Height; i++){
        grid.pressure[i] = 0.0f;
    }

    for (int i = 0; i < (Width +1) * Height; i++){
        grid.velocity_x[i] = 0.0f;
    }

    for (int i = 0; i < Width * (Height + 1); i++){
        grid.velocity_y[i] = 0.0f;
    }

    
    








    printf("bliblablub\n");


    return 0;
}