 #include <stdio.h>
 
 struct Cell {
        float pressure;
        float vx;
        float vy;
        float density; //actually bewegte "Masse" 0.0 = Nichts; 1.0 = Voll mit Rauch [Advektion]
    };



int main(){
    // beide Gitter Erstellen
    struct Cell grid_A[100*100];
    struct Cell grid_B[100*100];
    struct Cell* current_grid = grid_A;
    struct Cell* next_grid = grid_B;
    
    

    // Clearen, damit keine Random Restwerte drinne sind
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            grid_A[i * 100 + j].pressure = 0.0f;
            grid_A[i * 100 + j].vx = 0.0f;
            grid_A[i * 100 + j].vy = 0.0f;
            grid_A[i * 100 + j].density = 0.0f;

            grid_B[i * 100 + j].pressure = 0.0f;
            grid_B[i * 100 + j].vx = 0.0f;
            grid_B[i * 100 + j].vy = 0.0f;
            grid_B[i * 100 + j].density = 0.0f;
        }
    }

    current_grid[50 * 100 + 50].pressure = 10.0f; // Druck im Zentrum setzen

    // Testing
    int frame = 0;
    while (frame < 5){
        
        printf("------ FRAME %d ------\n", frame);
        printf("Druck im Zentrum: %f\n", current_grid[50 * 100 + 50].pressure);

        //Bald Physik dingsbums
        for (int y = 1; y < 99; y++){
            for (int x = 1; x < 99; x++){
                int current_index = y * 100 + x;

                int index_up = (y-1) * 100 + x;
                int index_down = (y+1) * 100 + x;
                int index_left = y * 100 + (x-1);
                int index_right = y * 100 + (x+1);

                float new_Pressure = (current_grid[current_index].pressure + 
                                      current_grid[index_up].pressure + 
                                      current_grid[index_down].pressure + 
                                      current_grid[index_left].pressure + 
                                      current_grid[index_right].pressure) / 5.0f;
                next_grid[current_index].pressure = new_Pressure;

                float new_vx = current_grid[index_left].pressure - current_grid[index_right].pressure;
                float new_vy = current_grid[index_up].pressure - current_grid[index_down].pressure;

                next_grid[current_index].vx = new_vx;
                next_grid[current_index].vy = new_vy;

                int source_x = (int)(x - current_grid[current_index].vx);
                int source_y = (int)(y - current_grid[current_index].vy);

                // Clamping, damit werte nicht über Array hinausschießen
                if (source_x < 1) source_x = 1;
                if (source_x > 98) source_x = 98;
                if (source_y < 1) source_y = 1;
                if (source_y > 98) source_y = 98;

                


            }
        }


        // Kopieren der Werte
        struct Cell* temp = current_grid;
        current_grid = next_grid;
        next_grid = temp;

        frame++;
    }
    



    return 0;
}
