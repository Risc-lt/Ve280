#include "simulation.h"

/****************************************************************
    Before Simulation:
    Initialize the world and check every possible error.
****************************************************************/

bool initWorld(world_t &world, const string &speciesSummary, const string &worldFile){
    ifstream speciesFile(speciesSummary);
    ifstream creaturesFile(worldFile);

    // Check whether the species-summary and world-file is opened successfully.
    if(!speciesFile.is_open()){
        cout << "Error: Cannot open file " << speciesSummary << "!" << endl;
        return false;
    }
    if(!creaturesFile.is_open()){
        cout << "Error: Cannot open file " << worldFile << "!" << endl;
        return false;
    }

    // Get the directory name from the species-summary file.
    string directory;
    getline(speciesFile, directory);

    // Read the species-summary and world-file.
    string line;
    while(getline(speciesFile, line) && line != ""){
        if(world.numSpecies > MAXSPECIES)
            break;

        world.species[world.numSpecies].name = line;
        if(!getProgram(directory + "/" + line, world.species[world.numSpecies])){
            speciesFile.close(); // Close the speciesFile
            creaturesFile.close(); // Close the creaturesFile
            return false;
        }
        world.numSpecies++;
    }

    // Check whether the number of species is greater than MAXSPECIES.
    if(world.numSpecies > MAXSPECIES){
        cout << "Error: Too many species!" << endl;
        cout << "Maximal number of species is "<< MAXSPECIES <<"." << endl;
        speciesFile.close(); // Close the speciesFile
        creaturesFile.close(); // Close the creaturesFile
        return false;
    }

    // Initialize the height of the grid.
    getline(creaturesFile, line);
    world.grid.height = stoi(line);
    if(world.grid.height > MAXHEIGHT && world.grid.height < 1){
        cout << "Error: The grid height is illegal!" << endl;
        speciesFile.close(); // Close the speciesFile
        creaturesFile.close(); // Close the creaturesFile
        return false;
    }

    // Initialize the width of the grid.
    getline(creaturesFile, line);
    world.grid.width = stoi(line);
    if(world.grid.width > MAXWIDTH && world.grid.width < 1){
        cout << "Error: The grid width is illegal!" << endl;
        speciesFile.close(); // Close the speciesFile
        creaturesFile.close(); // Close the creaturesFile
        return false;
    } 

    while(getline(creaturesFile, line) && line != ""){
        if(world.numCreatures > MAXCREATURES)
            break;

        istringstream iss(line);
        string species;
        unsigned int r, c;
        string direction;
        iss >> species >> direction >> r >> c;

        // Check whether the species of the creature is found.
        world.creatures[world.numCreatures].species = findSpecies(species, world);
        if(world.creatures[world.numCreatures].species == NULL){
            cout << "Error: Species " << species <<" not found!" << endl;
            speciesFile.close(); // Close the speciesFile
            creaturesFile.close(); // Close the creaturesFile
            return false;
        }

        // Check whether the location of the creature is out of the grid.
        if(r < 0 || r >= world.grid.height || c < 0 || c >= world.grid.width){
            cout << "Error: Creature (" << species << " " << direction << " " << r << " " << c << ") is out of bound!" << endl;
            cout << "The grid size is " << world.grid.height << "-by-" << world.grid.width << "." << endl;
            // Close the speciesFile and creaturesFile before returning false.
            speciesFile.close(); 
            creaturesFile.close(); 
            return false;
        } else {
            world.creatures[world.numCreatures].location.r = r;
            world.creatures[world.numCreatures].location.c = c;
            
            // Check whether the location of the creature overlaps with another creature.
            if(world.grid.squares[r][c] != NULL){ 


                cout << "Error: Creature (" << species << " " << direction << " " << r << " " << c << ") overlaps with creature (" 
                << world.grid.squares[r][c]->species->name << " " << directName[world.grid.squares[r][c]->direction] << " " << r << " " << c << ")!" << endl;

                // Close the speciesFile and creaturesFile before returning false.
                speciesFile.close(); 
                creaturesFile.close(); 
                return false;
            } else 
                world.grid.squares[r][c] = &world.creatures[world.numCreatures];  
        }
        
        // Check whether the direction of the creature is legal.
        if(direction == "east")
            world.creatures[world.numCreatures].direction = EAST;
        else if(direction == "south")
            world.creatures[world.numCreatures].direction = SOUTH;
        else if(direction == "west")
            world.creatures[world.numCreatures].direction = WEST;
        else if(direction == "north")
            world.creatures[world.numCreatures].direction = NORTH;
        else {
            cout << "Error: Direction " << direction << " is not recognized!" << endl;
            // Close the speciesFile and creaturesFile before returning false.
            speciesFile.close(); 
            creaturesFile.close();
            return false;
        }

        world.creatures[world.numCreatures].programID = 1;
        world.numCreatures++;
    }

    // Check whether the number of creatures is greater than MAXCREATURES.
    if(world.numCreatures > MAXCREATURES){
        cout << "Error: Too many creatures!" << endl;
        cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
        // Close the speciesFile and creaturesFile before returning false.
        speciesFile.close(); 
        creaturesFile.close(); 
        return false;
    }

    // Close the speciesFile and creaturesFile before returning true.
    speciesFile.close();
    creaturesFile.close(); 

    return true;
}

species_t *findSpecies(string species, world_t &world){
    for(unsigned int i = 0; i < world.numSpecies; i++){
        if(world.species[i].name == species)
            return &world.species[i];
    }
    return NULL;
}

bool getProgram(const string &path, species_t &species){
    ifstream speciesFile(path);

    // Check whether the speciesFile is opened successfully.
    if(!speciesFile.is_open()){
        cout << "Error: Cannot open file " << path << "!" << endl;
        return false;
    }

    // Get the instructions from the specific file.
    string line;
    species.programSize = 1;
    while(getline(speciesFile, line) && line != ""){
        if(species.programSize > MAXPROGRAM)
            break;

        istringstream iss(line);
        string instruction;
        iss >> instruction;
        if(instruction == "hop")
            species.program[species.programSize].op = HOP;
        else if(instruction == "left")
            species.program[species.programSize].op = LEFT;
        else if(instruction == "right")
            species.program[species.programSize].op = RIGHT;
        else if(instruction == "infect")
            species.program[species.programSize].op = INFECT;
        else if(instruction == "ifempty"){
            species.program[species.programSize].op = IFEMPTY;
            iss >> species.program[species.programSize].address;
        } else if(instruction == "ifwall"){
            species.program[species.programSize].op = IFWALL;
            iss >> species.program[species.programSize].address;
        } else if(instruction == "ifsame"){
            species.program[species.programSize].op = IFSAME;
            iss >> species.program[species.programSize].address;
        } else if(instruction == "ifenemy"){
            species.program[species.programSize].op = IFENEMY;
            iss >> species.program[species.programSize].address;
        } else if(instruction == "go"){
            species.program[species.programSize].op = GO;
            iss >> species.program[species.programSize].address;
        } else {
            cout << "Error: Instruction " << instruction << " is not recognized!" << endl;
            speciesFile.close();
            return false;
        }

        species.programSize++;
    }
    // Check whether the number of instructions is greater than MAXPROGRAM.
    if(species.programSize > MAXPROGRAM){
        cout << "Error: Too many instructions for species " << species.name << "!" << endl;
        cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
        speciesFile.close();
        return false;
    }
    
    // Close the speciesFile before returning true.
    speciesFile.close();
    return true;
}

/****************************************************************
    End of Initialization.
****************************************************************/
/****************************************************************
    Simulation:
    Run the simulation and print the world during each round.
****************************************************************/

void printGrid(const world_t &world){
    // Retrieve the grid from the world.
    for(unsigned int i = 0; i < world.grid.height; i++){ 
        for(unsigned int j = 0; j < world.grid.width; j++){
            bool isCreature = false;

            // Check whether the current position has a creature.
            if(world.grid.squares[i][j] != NULL){
                isCreature = true;
                cout << (world.grid.squares[i][j]->species->name).substr(0, 2) << "_" << directShortName[world.grid.squares[i][j]->direction] << " ";
            }

            if(!isCreature)
                cout << "____ ";
        }
        cout << endl;
    }
}

void simulateCreature(world_t &world, const string &verbose){    
    // Run the simulation.
    for(unsigned int i = 0; i < world.numCreatures; i++){

        grid_t &grid = world.grid;
        
        // Get the arguments from current creature.
        creature_t &creature = world.creatures[i];         
        instruction_t &instruction = creature.species->program[creature.programID];       
        point_t &location = creature.location;        
        direction_t &direction = creature.direction;        

        // Print the creature's action if verbose.
        if(verbose == "v" || verbose == "verbose"){
            cout << "Creature (" << creature.species->name << " " << directName[direction] << " " << location.r << " " << location.c << ") takes action:" << endl;
        }

        // Take the corresponding action.
        TakeAction(instruction, creature, grid, verbose);

        // Print the world after each creature if verbose.
        if(verbose == "v" || verbose == "verbose"){
            printGrid(world);
        } else if(i == world.numCreatures - 1){
            printGrid(world);
        }
    }
}

void TakeAction(instruction_t &instruction, creature_t &creature, grid_t &grid, const string &verbose){
    // Switch the instruction and take the corresponding action.
    switch(instruction.op){
        case HOP:
            if(verbose == "v" || verbose == "verbose"){
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << endl;
            } else{
                cout << "Creature (" << creature.species->name << " " << directName[creature.direction] << " " << creature.location.r << " " << creature.location.c << ") takes action: hop" << endl;
            }
            Hop(creature, grid);            
            creature.programID++;            
            break;
        case LEFT:
            if(verbose == "v" || verbose == "verbose"){
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << endl;
            } else{
                cout << "Creature (" << creature.species->name << " " << directName[creature.direction] << " " << creature.location.r << " " << creature.location.c << ") takes action: left" << endl;
            }
            Left(creature);
            creature.programID++;
            break;
        case RIGHT:
            if(verbose == "v" || verbose == "verbose"){
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << endl;
            } else{
                cout << "Creature (" << creature.species->name << " " << directName[creature.direction] << " " << creature.location.r << " " << creature.location.c << ") takes action: right" << endl;
            }
            Right(creature);
            creature.programID++;
            break;
        case INFECT:
            if(verbose == "v" || verbose == "verbose"){
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << endl;
            } else{
                cout << "Creature (" << creature.species->name << " " << directName[creature.direction] << " " << creature.location.r << " " << creature.location.c << ") takes action: infect" << endl;
            }
            Infect(creature, grid);
            creature.programID++;
            break;
        case IFEMPTY:
            if(verbose == "v" || verbose == "verbose")
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << " " << instruction.address << endl;
            IfEmpty(instruction, creature, grid);
            TakeAction(creature.species->program[creature.programID], creature, grid, verbose);
            break;
        case IFWALL:
            if(verbose == "v" || verbose == "verbose")
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << " " << instruction.address << endl;
            IfWall(instruction, creature, grid);
            TakeAction(creature.species->program[creature.programID], creature, grid, verbose);
            break;
        case IFSAME:
            if(verbose == "v" || verbose == "verbose")
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << " " << instruction.address << endl;
            IfSame(instruction, creature, grid);
            TakeAction(creature.species->program[creature.programID], creature, grid, verbose);
            break;
        case IFENEMY:
            if(verbose == "v" || verbose == "verbose")
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << " " << instruction.address << endl;
            IfEnemy(instruction, creature, grid);
            TakeAction(creature.species->program[creature.programID], creature, grid, verbose);
            break;
        case GO:
            if(verbose == "v" || verbose == "verbose")
                cout << "Instruction "<< creature.programID << ": " << opName[instruction.op] << " " << instruction.address << endl;
            Go(instruction, creature);
            TakeAction(creature.species->program[creature.programID], creature, grid, verbose);
            break;
    }
}

void Hop(creature_t &creature, grid_t &grid){
    point_t &location = creature.location;
    direction_t &direction = creature.direction;

    if(direction == EAST){
        if((uint)location.c + 1 < grid.width && grid.squares[location.r][location.c + 1] == NULL){
            grid.squares[location.r][location.c + 1] = &creature;
            grid.squares[location.r][location.c] = NULL;
            location.c++;
        }
    } else if(direction == SOUTH){
        if((uint)location.r + 1 < grid.height && grid.squares[location.r + 1][location.c] == NULL){
            grid.squares[location.r + 1][location.c] = &creature;
            grid.squares[location.r][location.c] = NULL;
            location.r++;
        }
    } else if(direction == WEST){
        if(location.c - 1 >= 0 && grid.squares[location.r][location.c - 1] == NULL){
            grid.squares[location.r][location.c - 1] = &creature;
            grid.squares[location.r][location.c] = NULL;
            location.c--;
        }
    } else if(direction == NORTH){
        if(location.r - 1 >= 0 && grid.squares[location.r - 1][location.c] == NULL){
            grid.squares[location.r - 1][location.c] = &creature;
            grid.squares[location.r][location.c] = NULL;
            location.r--;
        }
    }
}

void Left(creature_t &creature){
    direction_t &direction = creature.direction;
    if(direction == EAST)
        direction = NORTH;
    else if(direction == SOUTH)
        direction = EAST;
    else if(direction == WEST)
        direction = SOUTH;
    else if(direction == NORTH)
        direction = WEST;
}

void Right(creature_t &creature){
    direction_t &direction = creature.direction;
    if(direction == EAST)
        direction = SOUTH;
    else if(direction == SOUTH)
        direction = WEST;
    else if(direction == WEST)
        direction = NORTH;
    else if(direction == NORTH)
        direction = EAST;
}

void Infect(creature_t &creature, grid_t &grid){
    point_t &location = creature.location;
    direction_t &direction = creature.direction;
    if(direction == EAST){
        if((uint)location.c + 1 < grid.width && grid.squares[location.r][location.c + 1] != NULL){
            if(grid.squares[location.r][location.c + 1]->species != creature.species){
                grid.squares[location.r][location.c + 1]->species = creature.species;
                grid.squares[location.r][location.c + 1]->programID = 1;
            }
        }
    } else if(direction == SOUTH){
        if((uint)location.r + 1 < grid.height && grid.squares[location.r + 1][location.c] != NULL){
            if(grid.squares[location.r + 1][location.c]->species != creature.species){
                grid.squares[location.r + 1][location.c]->species = creature.species;
                grid.squares[location.r + 1][location.c]->programID = 1;
            }
        }
    } else if(direction == WEST){
        if(location.c - 1 >= 0 && grid.squares[location.r][location.c - 1] != NULL){
            if(grid.squares[location.r][location.c - 1]->species != creature.species){
                grid.squares[location.r][location.c - 1]->species = creature.species;
                grid.squares[location.r][location.c - 1]->programID = 1;
            }
        }
    } else if(direction == NORTH){
        if(location.r - 1 >= 0 && grid.squares[location.r - 1][location.c] != NULL){
            if(grid.squares[location.r - 1][location.c]->species != creature.species){
                grid.squares[location.r - 1][location.c]->species = creature.species;
                grid.squares[location.r - 1][location.c]->programID = 1;
            }
        }
    }
}

void IfEmpty(instruction_t &instruction, creature_t &creature, grid_t &grid){
    point_t &location = creature.location;
    direction_t &direction = creature.direction;
    
    if(direction == EAST){
        if((uint)location.c + 1 < grid.width && grid.squares[location.r][location.c + 1] == NULL)
            creature.programID = instruction.address;
        else 
            creature.programID++;
    } else if(direction == SOUTH){
        if((uint)location.r + 1 < grid.height && grid.squares[location.r + 1][location.c] == NULL)
            creature.programID = instruction.address;
        else    
            creature.programID++;
    } else if(direction == WEST){
        if(location.c - 1 >= 0 && grid.squares[location.r][location.c - 1] == NULL)
            creature.programID = instruction.address;
        else
            creature.programID++;
    } else if(direction == NORTH){
        if(location.r - 1 >= 0 && grid.squares[location.r - 1][location.c] == NULL)
            creature.programID = instruction.address;
        else    
            creature.programID++;
    }
}

void IfWall(instruction_t &instruction, creature_t &creature, grid_t &grid){
    point_t &location = creature.location;
    direction_t &direction = creature.direction;
    
    if(direction == EAST){
        if((uint)location.c + 1 >= grid.width)
            creature.programID = instruction.address;
        else 
            creature.programID++;
    } else if(direction == SOUTH){
        if((uint)location.r + 1 >= grid.height)
            creature.programID = instruction.address;
        else
            creature.programID++;
    } else if(direction == WEST){
        if(location.c - 1 < 0)
            creature.programID = instruction.address;
        else
            creature.programID++;
    } else if(direction == NORTH){
        if(location.r - 1 < 0)
            creature.programID = instruction.address;
        else
            creature.programID++;
    }
}

void IfSame(instruction_t &instruction, creature_t &creature, grid_t &grid){
    point_t &location = creature.location;
    direction_t &direction = creature.direction;
    
    if(direction == EAST){
        if((uint)location.c + 1 < grid.width && grid.squares[location.r][location.c + 1] != NULL && grid.squares[location.r][location.c + 1]->species == creature.species)
            creature.programID = instruction.address;
        else 
            creature.programID++;
    } else if(direction == SOUTH){
        if((uint)location.r + 1 < grid.height && grid.squares[location.r + 1][location.c] != NULL && grid.squares[location.r + 1][location.c]->species == creature.species)
            creature.programID = instruction.address;
        else    
            creature.programID++;
    } else if(direction == WEST){
        if(location.c - 1 >= 0 && grid.squares[location.r][location.c - 1] != NULL && grid.squares[location.r][location.c - 1]->species == creature.species)
            creature.programID = instruction.address;
        else
            creature.programID++;
    } else if(direction == NORTH){
        if(location.r - 1 >= 0 && grid.squares[location.r - 1][location.c] != NULL && grid.squares[location.r - 1][location.c]->species == creature.species)
            creature.programID = instruction.address;
        else    
            creature.programID++;
    } 
}

void IfEnemy(instruction_t &instruction, creature_t &creature, grid_t &grid){
    point_t &location = creature.location;
    direction_t &direction = creature.direction;
    
    if(direction == EAST){
        if((uint)location.c + 1 < grid.width && grid.squares[location.r][location.c + 1] != NULL && grid.squares[location.r][location.c + 1]->species != creature.species)
            creature.programID = instruction.address;
        else 
            creature.programID++;
    } else if(direction == SOUTH){
        if((uint)location.r + 1 < grid.height && grid.squares[location.r + 1][location.c] != NULL && grid.squares[location.r + 1][location.c]->species != creature.species)
            creature.programID = instruction.address;
        else 
            creature.programID++;
    } else if(direction == WEST){
        if(location.c - 1 >= 0 && grid.squares[location.r][location.c - 1] != NULL && grid.squares[location.r][location.c - 1]->species != creature.species)
            creature.programID = instruction.address;
        else 
            creature.programID++;
    } else if(direction == NORTH){
        if(location.r - 1 >= 0 && grid.squares[location.r - 1][location.c] != NULL && grid.squares[location.r - 1][location.c]->species != creature.species)
            creature.programID = instruction.address;
        else
            creature.programID++;
    } 
}

void Go(instruction_t &instruction, creature_t &creature){
    creature.programID = instruction.address;
}

/****************************************************************
    End of Simulation.
****************************************************************/