//
//  smm_object.h
//  SMMarble object
//
//  Created by Juyeop Kim on 2023/11/05.
//

#ifndef smm_object_h
#define smm_object_h

/* node type :
    lecture,
    restaurant,
    laboratory,
    home,
    experiment,
    foodChance,
    festival
*/


/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/



//object generation
void smmObj_genNode(char* name, int type, int credit, int energy);

char* smmObj_getnodename(int node_nr);

int smmObj_getnodetype( int node_nr);

//member retrieving


//element to string



#endif /* smm_object_h */
