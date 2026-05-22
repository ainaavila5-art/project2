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

void printTreeBFS(struct FamilyTreeNode *root);

// Allibera la memòria de l'arbre
void freeAncestorsTree(struct FamilyTreeNode *root);


/*IMPORTANT PER ENTENDRE LES DIFERENTS FUNCIONS

main diu: "Vinga, viatgem en DFS!". Crida a traverseTreeDFS().

traverseTreeDFS llegeix l'arbre i diu: "D'acord, estic a l'arrel (Barcelona) i el següent familiar és a París". Llavors crida a RouteSearch(Barcelona, Paris, road_map).

RouteSearch fa els seus càlculs a la matriu i s'adona que ha de passar per Madrid. Per guardar-ho, crida a addToRoadMap(Madrid, cost).

o sigui, primer creem aquest arbre i fem un traverse. Veu que ha d'anar a una ciutat però com que no ens volem gastar molts diners, mirem el RouteSearch quin és el millor camí i una vegada hem calculat el millor camí, crida a addToRoadMap



*/
//------------------------------------------------------------ NAVIGATION AND GRAPH IMPLEMENTATION
/*
Aquestes funcions recorren l'arbre creat (usant DFS o BFS) 
i van cridant a RouteSearch per cada salt entre familiars. calculen les rutes físiques i els costos acumulats
*/
struct RoadMap* traverseTreeDFS(struct FamilyTreeNode *root, struct RoadMap *road_map);
struct RoadMap* traverseTreeBFS(struct FamilyTreeNode *root, struct RoadMap *road_map);

/* Funció que busca el camí físic més curt a la matriu entre 
la ciutat origen i la ciutat destí (usant heurística o greedy).
*/
struct RoadMap* RouteSearch(int source_city_id, int destination_city_id, struct RoadMap *road_map);






//----------------------------------------------------------- CLOSING AND DEFINITION
int main(int argc, char **argv); // Utilitzem l'argv per poder passar els paràmetres per la terminal






