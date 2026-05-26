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

//DATE: 21/05/2026. This function adds every city chosen to the end of the linked list
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

//DATE: 21/05/2026. This function prints the list of the cities in the linked list
void printRoadMap(struct RoadMap *head){
    struct RoadMap *current = head;
    while (current != NULL){
        printf(" -> %s (Cost: %d)\n", citiesInfo[current->city_id].city_name, current->total_cost);
        current = current -> next;
    }
}

//DATE: 21/05/2026. This function deletes all the linked list containing the cities
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

//------------------------------------------------------------ ANCESTOR'S TREE CONSTRUCTION
/*DATE: 22/05/2026. This function logically assembles the family relationships using the
civil registry data
*/
struct FamilyTreeNode* buildAncestorsTree(int root_city_id){
     if (root_city_id == -1){ //Base case: if the ancestor's doesn't exist (leaf), return NULL
        return NULL;
     }
     struct FamilyTreeNode *new_node = (struct FamilyTreeNode*)malloc(sizeof(struct FamilyTreeNode));

     new_node -> city_id = root_city_id;
     strcpy(new_node-> motherName, citiesInfo[root_city_id].mother_name);
     strcpy(new_node-> fatherName, citiesInfo[root_city_id].father_name);

     new_node -> mother_parents = buildAncestorsTree(citiesInfo[root_city_id].mother_parents_city_id);
     new_node -> father_parents = buildAncestorsTree(citiesInfo[root_city_id].father_parents_city_id);

     return new_node;

     /*
     PASSOS PER ENTENDRE LA RECURSIVITAT
     Crea el node del fill.
     S'atura i crida a la funció per crear el node de la mare.
     A dins de la mare, s'atura i crida a la funció per crear el node de l'àvia... i així successivament fins que xoca amb un -1 (que significa que no hi ha més dades d'aquell llinatge).
     Quan troba el -1, el famós Cas Base que vam fer abans retorna NULL.
     Com que retorna NULL, l'ordinador entén que la branca ha acabat, "despausa" la funció anterior, l'enganxa al punter, i passa a la següent línia per fer exactament el mateix amb la branca del pare (father_parents).
     */

}

//DATE: 22/05/2026. This function prints the tree using the DFS strategy.
void printTreeDFS(struct FamilyTreeNode *root, int level){
    if (root == NULL){
        return;
    }
    for (int i = 0; i < level; i++){
        printf("->");
    }

    printf("%s and %s (%s)\n", root->motherName, root->fatherName, citiesInfo[root->city_id].city_name);

    printTreeDFS(root->mother_parents, level +1); // Recursion for the mother's tree
    printTreeDFS(root->father_parents, level +1); // Recursion for the father's tree

}
//DATE: 25/05/2026. This function prints the tree using the BFS strategy.
void printTreeBFS(struct FamilyTreeNode *root){
    if (root == NULL){
        return;
    }
    struct FamilyTreeNode **queue = (struct FamilyTreeNode**)malloc(NUMBER_CITIES * sizeof(struct FamilyTreeNode*));
    int *level_queue = (int*)malloc(NUMBER_CITIES * sizeof(int));
    int front = 0;
    int rear = 0;
    queue[rear] = root;
    level_queue[rear] = 0;
    rear++;
    
    if (queue ==NULL || level_queue == NULL){
        printf("ERROR");
        exit(1);
    }
    while (front < rear){
        struct FamilyTreeNode *current = queue[front];
        int current_level = level_queue[front];
        front ++;
        for (int i = 0; i < current_level; i++){
            printf("->");
        }
        printf("%s and %s (%s)\n", current->motherName, current->fatherName, citiesInfo[current->city_id].city_name);
        //We add the childs to the queue
        if (current->mother_parents != NULL){
            queue[rear] = current->mother_parents;
            level_queue[rear] = current_level + 1;
            rear++;
        }
        if (current ->father_parents != NULL){
            queue[rear] = current ->father_parents;
            level_queue[rear] = current_level + 1;
            rear++;
        }
    }
    free(queue);
    free(level_queue);
}

//DATE: 25/05/2026. This function eliminates the tree created 
void freeAncestorsTree(struct FamilyTreeNode *root){
    if (root == NULL){
        return;
    }
    freeAncestorsTree(root->mother_parents);
    freeAncestorsTree(root->father_parents);
    free(root);
}


/*IMPORTANT PER ENTENDRE LES DIFERENTS FUNCIONS

main diu: "Vinga, viatgem en DFS!". Crida a traverseTreeDFS().

traverseTreeDFS llegeix l'arbre i diu: "D'acord, estic a l'arrel (Barcelona) i el següent familiar és a París". Llavors crida a RouteSearch(Barcelona, Paris, road_map).

RouteSearch fa els seus càlculs a la matriu i s'adona que ha de passar per Madrid. Per guardar-ho, crida a addToRoadMap(Madrid, cost).

o sigui, primer creem aquest arbre i fem un traverse. Veu que ha d'anar a una ciutat però com que no ens volem gastar molts diners, mirem el RouteSearch quin és el millor camí i una vegada hem calculat el millor camí, crida a addToRoadMap



*/
//------------------------------------------------------------ NAVIGATION AND GRAPH IMPLEMENTATION

// DATE 25/05/2026: This function searches the best route between two cities using a greedy heuristic. 
/* We use a 2-step rule at each city: 
    1. If there is a direct edge to the destination, we take it immediately. 
    2. Otherwise, move to the cheapest unvisited neigbour(gready best-first step)
*/

struct RoadMap* RouteSearch(int source_city_id, int destination_city_id, struct RoadMap *road_map){
    int visited[NUMBER_CITIES];
    for (int i=0; i<NUMBER_CITIES; i++){
        visited[i]=0;
    }
    int current = source_city_id;
    int leg_cost = 0;

    int base_cost= 0;
    if (road_map != NULL){
        struct RoadMap*tail = road_map;
        while (tail->next != NULL){
            tail= tail->next;
        }
        base_cost = tail->total_cost;
    }
 
    if (road_map == NULL){
        road_map= addToRoadMap(road_map, current, 0);
    }
    visited[current] = 1; 

    while (current != destination_city_id){
        //Step 1: Is a direct edge destination?
        if (adjacency_matrix[current][destination_city_id]!=0){
            leg_cost+= adjacency_matrix[current][destination_city_id];
            current = destination_city_id;
            road_map = addToRoadMap(road_map, current, base_cost + leg_cost);
            break;
        
        }

        //Step 2: Greedy -pick the cheapest unvisited neighbour
        int best_city = -1;
        int best_cost= 999999;
        for ( int i=0; i<NUMBER_CITIES; i++){
            if (!visited[i] && adjacency_matrix[current][i] != 0) {
                if(adjacency_matrix[current][i]<best_cost){
                    best_cost= adjacency_matrix[current][i];
                    best_city=i;
                }
            }
        }
    
    // Dead end: the huristic got stuck(should not heppen with a connected graph)
    if (best_city == -1){
        printf("Wearning: no path found from %s to %s\n", 
            citiesInfo[source_city_id].city_name, 
            citiesInfo[destination_city_id].city_name);
        return road_map;
    }

    leg_cost += best_cost;
    current = best_city;
    visited[current]=1;
    road_map= addToRoadMap(road_map, current, base_cost + leg_cost);

}

return road_map;
}

//DATE 25/05/2026: This functions traverse the ancestrors tree already build using DFS
/*It will compute the full mother branch before father branch and calls RouteSearch for each 
hop between cities, building the complete road map as a side effect. */

struct RoadMap* traverseTreeDFS(struct FamilyTreeNode *root, struct RoadMap *road_map, int *current_city){
    if (root == NULL){
        return road_map;
    }

    // Go deep on the mother side first (DFS rule)
    if (root->mother_parents != NULL){
        int destination = root -> mother_parents -> city_id;
        printf("Travelling: %s -> %s\n", 
            citiesInfo[*current_city].city_name,
            citiesInfo[destination].city_name);
        
        road_map = RouteSearch(*current_city, destination, road_map);
        *current_city= destination;
        printf("Partial road map so far: \n");
        printRoadMap(road_map);
        road_map= traverseTreeDFS(root->mother_parents, road_map, current_city);   
    }
    // Only after the full mother branch is done, go to the father side
    if (root->father_parents != NULL){
        int destination = root->father_parents -> city_id;
        printf("Traveling: %s -> %s",
            citiesInfo[*current_city].city_name,
            citiesInfo[destination].city_name);

        road_map = RouteSearch(*current_city, destination, road_map);
        *current_city= destination;
        printf("Partial road map so far:\n");
        printRoadMap(road_map);
        road_map=traverseTreeDFS(root->father_parents, road_map, current_city);
    }
    return road_map;
}

// DATE 25/05/2026: This fucntion traverse the acestrors tree using BFS.
/*All nodes are at level N before any node at level N+1, mother side before
father side within each level, and calls RouteSearch for the hop, building the road map.*/ 


struct RoadMap* traverseTreeBFS(struct FamilyTreeNode *root, struct RoadMap *road_map, int *current_city){
    if (root == NULL){
        return road_map;
    }

    // Queue of tree node pointers for BFS traversal
    struct FamilyTreeNode **queue = (struct FamilyTreeNode**)malloc(NUMBER_CITIES *sizeof(struct FamilyTreeNode*));
    if (queue == NULL){
        printf("Error: malloc failed in traverseTreeBFS\n");
        exit(1);
    }

    int front = 0;
    int rear = 0;
    // Initialize the queue with the root's children (mother first, then father -> BFS level order)
    if (root -> mother_parents != NULL){
        queue[rear++]= root->mother_parents;
    }

    if (root ->father_parents != NULL){
        queue[rear++] = root-> father_parents;
    }

    while (front < rear){
        struct FamilyTreeNode *current_node = queue[front++];
        int destination = current_node->city_id;

        // Travel from where we are now to this ancestror's city 
        printf("Traveling: %s -> %s\n",
            citiesInfo[*current_city].city_name,
            citiesInfo[destination].city_name);
        road_map = RouteSearch (*current_city, destination, road_map);
        *current_city= destination;
        printf("Partial road map so far: \n");
        printRoadMap(road_map);

        if (current_node->mother_parents != NULL){
            queue[rear++]= current_node->mother_parents;
        }
        if (current_node->father_parents != NULL){
            queue[rear++] = current_node->father_parents;
        }
    }
    free(queue);
    return road_map;
}

//----------------------------------------------------------- CLOSING AND DEFINITION

/*DATE 25/05/2026: Main function. Recives "DFS" or "BFS as argument and:"
    1. Builds the acestrors tree from the civil registry data.
    2. Traverses it with the chosen strategy, building the road map. 
    3. Prints the final tree and the full road map with total cost 
    4. Frees all the dynamic memory before exiting
*/ 
// We will use argv to be able to pass the parameters through the terminal 

int main(int argc, char **argv){
    CheckArguments(argc, argv);

    #ifdef LARGE 
        printf("This is a large case of the program\n");
    #elif defined(MEDIUM)
        printf("This is a medium case of the program\n");
    #else
        printf("This is a small case of the program\n");
    #endif

    int root_city =0; //Starting city: Barcelona (index 0 in citiesInfo)

    struct FamilyTreeNode *tree = buildAncestorsTree(root_city);

    struct RoadMap *road_map = NULL;
    int current_city = root_city;

    road_map= addToRoadMap(road_map, root_city, 0);

    printf("Ancestrors' tree:\n");
    printf("%s ->Names:\n", argv[1]);
    printf("Partial road map (step by step):");

    if (strcmp(argv[1], "dfs") == 0){
        road_map = traverseTreeDFS(tree, road_map, &current_city);      
    }else{
        road_map = traverseTreeBFS(tree, road_map, &current_city);
    }

    printf("_____Final ancestrors tree (%s order)_____\n", argv[1]);
    if (strcmp(argv[1], "dfs")== 0 ) {
        printTreeDFS(tree, 0);
    } else{
        printTreeBFS(tree);
    }

    printf("___Total road map___\n");
    printRoadMap(road_map);

    struct RoadMap *tail = road_map;
    while (tail->next != NULL) tail= tail->next;
    printf("Total cost: %d\n", tail->total_cost);

    road_map = deleteAllRoadMap(road_map);
    freeAncestorsTree(tree);

    return 0; 

} 






