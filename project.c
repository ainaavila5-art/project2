/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming II
Practical project: 2
Students and NIUS:
    Nerea Soria: 1792863
    Aina Àvila: 1789192

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//posar la configuració de #ifdef per poder canviar lo dels headers

//------------------------------------------------------------ Preparation and environment setup
// Afegeix una ciutat
struct RoadMap* addToRoadMap(struct RoadMap *head, int city_id, int total_cost);

// Imprimeix la llista
void printRoadMap(struct RoadMap *head);

// Esborra tota la llista i retorna NULL perquè puguis actualitzar el punter original
struct RoadMap* deleteAllRoadMap(struct RoadMap *head);




//------------------------------------------------------------ Navigation and graph implementation
// Cerca la ruta
int RouteSearch(int source_city_id, int destination_city_id, struct RoadMap *road_map);



//------------------------------------------------------------ Ancestor's tree construction
// Construeix l'arbre DFS
struct TreeNode* createTreeDFS(int current_city_id, struct RoadMap *road_map);

// Construeix l'arbre BFS
struct TreeNode* createTreeBFS(int root_city_id, struct RoadMap *road_map);

//Mostra l'arbre per pantalla
void printTree(struct TreeNode *root, int level);

// Allibera la memòria de l'arbre
void freeFamilyTree(struct TreeNode *root);



//----------------------------------------------------------- Closing and definition
int main(int argc, char **argv); // Utilitzem l'argv per poder passar els paràmetres per la terminal






