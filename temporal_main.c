#include "project.c"

int main(int argc, char **argv) {
    CheckArguments(argc,argv);  

    struct RoadMap *mytrip = NULL;
    mytrip = addToRoadMap(mytrip, 0,0);
    mytrip = addToRoadMap(mytrip, 1,150);
    mytrip = addToRoadMap(mytrip, 2,280);

    printRoadMap(mytrip);

    mytrip = deleteAllRoadMap(mytrip);

    printRoadMap(mytrip);
}


