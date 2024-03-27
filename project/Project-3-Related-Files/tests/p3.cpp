#include "simulation.h"
using namespace std;

int main(int argc, char *argv[])
{ 
    // Check whether the number of arguments is less than three.
    if(argc < 3){
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> [v|verbose]" << endl;
        return 1;
    }

    // Check whether the value <rounds> supplied by the user is negative.
    unsigned int rounds = stoi(argv[3]);
    if(rounds < 0){
        cout << "Error: Number of rounds is negative!" << endl;
        return 1;
    }
    
    // Other arguments from user.
    string verbose = "None";
    if(argc == 5)
        verbose = argv[4];

    // Initialize the world.
    world_t world;
    world.numSpecies = 0;
    world.numCreatures = 0;
    // Set the square of grid to NULL.
    for(unsigned int i = 0; i < MAXHEIGHT; i++){
        for(unsigned int j = 0; j < MAXWIDTH; j++){
            world.grid.squares[i][j] = NULL;
        }
    }

    // Exit the program if the world is not initialized successfully.
    if(!initWorld(world, argv[1], argv[2])) 
        return 0; 

    // Print the initial world.
    cout << "Initial state" << endl;
    printGrid(world);

    // Run the simulation and print the world during each round.
    unsigned int i = 1;
    while(i <= rounds){
        cout << "Round " << i << endl;
        simulateCreature(world, verbose);
        i++;
    }

    return 0;
}