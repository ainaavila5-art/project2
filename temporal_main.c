#include "project.c"

int main(int argc, char **argv) {
    CheckArguments(argc,argv);  

    int root_city_id = 0;
    struct FamilyTreeNode *my_family_tree = buildAncestorsTree(root_city_id);

    printTreeBFS(my_family_tree);

    freeAncestorsTree(my_family_tree);
    printTreeBFS(my_family_tree);
    return 0;

}







