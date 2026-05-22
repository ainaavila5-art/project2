#include "project.c"

int main(int argc, char **argv) {
    CheckArguments(argc,argv);  

    int root_city_id = 0;
    struct FamilyTreeNode *my_family_tree = buildAncestorsTree(root_city_id);

    printTreeDFS(my_family_tree,0);
    return 0;

}







