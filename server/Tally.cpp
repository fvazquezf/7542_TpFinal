#include "Tally.h"

Tally::Tally(){
    
}

void Tally::placeInTeam(int id, bool team){
    if (team){
        ctSide.push_back(id);
    } else {
        ttSide.push_back(id);
    }
}