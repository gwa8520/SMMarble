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

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME]= {

		"강의",
		"실험실",
		"식당",
		"집",
		"축제",
		"음식찬스",
		"실험실로이동"
};

char* smmObj_getTypeName(int type){
	
	return	(char*)smmNodeName[type];
}

static char smmObj_name[MAX_NODE][MAX_CHARNAME];   			//배열로 코딩하지 마라..?  
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode=0;



//object generation
void smmObj_getNode(char* name, int type, int credit, int energy)
{
    strcpy (smmObj_name[smmObj_noNode],name);
    smmObj_type[smmObj_noNode]= type;
    smmObj_credit[smmObj_noNode]= credit;
    smmObj_energy[smmObj_noNode]= energy;
    
    smmObj_noNode++;
    
}

char* smmObj_getnodename(int node_nr){
	
	return smmObj_name[node_nr];
}

int smmObj_getnodetype( int node_nr){
	
	return smmObj_type[node_nr];
}


//member retrieving


#if 0
//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}
#endif
