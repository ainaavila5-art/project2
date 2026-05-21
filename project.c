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

//------------------------------------------------------------ PREPARATION AND ENVIRONMENT SETUP

//DATE: 20/05/2026. With the #ifdef directive we can dyamically load different civil registry datasets
#define SMALL
#ifdef SMALL
    #include "small.h"
#elif defined(MEDIUM)
    #include "medium.h"
#elif defined(LARGE)
    #include "large.h"
#else
    #error "Incorrect definition. You should choose between these options: SMALL, MEDIUM LARGE"
#endif

/*DATE: 21/05/2026. This function checks if the input introduced by the user is correct
by using a series of conditionals
*/
void CheckArguments (int argc, char **argv){
    if (argc != 2){
        printf("Error: Incorrect number of arguments.\n");
        printf("Usage: %s", argv[0]);
        exit(1);
    }
    if (strcmp(argv[1], "dfs") != 0 && strcmp(argv[1], "bfs") != 0) {
        printf("Error: The argument must be strictly 'dfs' or 'bfs'. \n");
        exit(1);
    }
}

//DATE: 21/05/2026. This function adds every city chosen to the end of an array
struct RoadMap* addToRoadMap(struct RoadMap *head, int city_id, int total_cost){
    struct RoadMap *new_city = (struct RoadMap*)malloc(sizeof(struct RoadMap));
    new_city -> city_id = city_id;
    new_city -> total_cost = total_cost;
    new_city -> next = NULL;

    if (head == NULL){
        return new_city;
    }
    struct RoadMap *current = head;
    while (current -> next != NULL){
        current = current -> next;
    }
    current -> next = new_city;
    return head;
}

//DATE: 21/05/2026. This function prints the list of the cities in the array
void printRoadMap(struct RoadMap *head){
    struct RoadMap *current = head;
    while (current != NULL){
        printf(" -> %s (Cost: %d)\n", citiesInfo[current->city_id].city_name, current->total_cost);
        current = current -> next;
    }
}

//DATE: 21/05/2026. This function deletes all the array containing the cities
struct RoadMap *deleteAllRoadMap(struct RoadMap *head){
    struct RoadMap *current = head;
    struct RoadMap *temp;

    while (current != NULL){
        temp = current;
        current = current -> next;
        free(temp);
    }
    head = NULL;
    return head;
}


//------------------------------------------------------------ NAVIGATION AND GRAPH IMPLEMENTATION
// Cerca la ruta
int RouteSearch(int source_city_id, int destination_city_id, struct RoadMap *road_map);



//------------------------------------------------------------ ANCESTOR'S TREE CONSTRUCTION
// Construeix l'arbre DFS
struct TreeNode* createTreeDFS(int current_city_id, struct RoadMap *road_map);

// Construeix l'arbre BFS
struct TreeNode* createTreeBFS(int root_city_id, struct RoadMap *road_map);

//Mostra l'arbre per pantalla
void printTree(struct TreeNode *root, int level);

// Allibera la memòria de l'arbre
void freeFamilyTree(struct TreeNode *root);



//----------------------------------------------------------- CLOSING AND DEFINITION
int main(int argc, char **argv); // Utilitzem l'argv per poder passar els paràmetres per la terminal






