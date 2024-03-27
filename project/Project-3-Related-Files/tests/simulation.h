#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include "world_type.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
using namespace std;

// Initialization
bool initWorld(world_t &world, const string &speciesSummary, const string &worldFile);
species_t *findSpecies(string species, world_t &world);
bool getProgram(const string &path, species_t &species);

// Simulation
void simulateCreature(world_t &world, const string &verbose);
void printGrid(const world_t &world);
void TakeAction(instruction_t &instruction, creature_t &creature, grid_t &grid, const string &verbose);

// Actions
void Hop(creature_t &creature, grid_t &grid);
void Left(creature_t &creature);
void Right(creature_t &creature);
void Infect(creature_t &creature, grid_t &grid);
void IfEmpty(instruction_t &instruction, creature_t &creature, grid_t &grid);
void IfWall(instruction_t &instruction, creature_t &creature, grid_t &grid);
void IfSame(instruction_t &instruction, creature_t &creature, grid_t &grid);
void IfEnemy(instruction_t &instruction, creature_t &creature, grid_t &grid);
void Go(instruction_t &instruction, creature_t &creature);

#endif // _SIMULATION_H_