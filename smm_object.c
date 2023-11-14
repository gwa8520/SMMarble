//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODE  		100
#define MAX_NODETYPE    7
#define MAX_GRADE       9

static char smmObj_name[MAX_NODE][MAX_CHARNAME];   			//배열로 코딩하지 마라..?  
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_nollode=0;



//object generation
void smmObj_genNode(char* name, int type, int credit, int energy)
{
    strcpy (smmObj_name[smmObj_nollode],name);
    smmObj_type[smmObj_nollode]= type;
    smmObj_credit[smmObj_nollode]= credit;
    smmObj_energy[smmObj_nollode]= energy;
    
    smmObj_noNode++;
    
}

char* smmObj_getnodename(int node_nr){
	
	return smmObj_name[smmObj_noNode];
}

int smmObj_getnodetype( int node_nr){
	
	return smmObj_type[node_nr];
}


//member retrieving



//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

