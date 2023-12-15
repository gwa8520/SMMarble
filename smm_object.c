//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>
#include <time.h>

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


//1.구조체 형식 정의  

//2. 구조체 배열 변수 정의
//static smmObject_t smm_node[MAX_NODE]; 
//static int smmObj_noNode=0;
  
  
//3.관련 함수 변경  



//object generation
void* smmObj_genObject(char* name,smmObjType_t objtype, int type, int credit, int energy,smmObjGrade_e grade)
{
	smmObject_t* ptr;
	
	ptr=(smmObject_t*)malloc(sizeof(smmObject_t));
	
    strcpy(ptr->name,name);
    ptr->objtype = objtype;
    ptr->type=type;
    ptr->credit=credit;
    ptr->energy=energy;
    ptr->grade=grade;
    
    return ptr;
    
}

char* smmObj_getNodeName(void* obj){
	
	smmObject_t* ptr=(smmObject_t*)obj;
	return ptr->name;
}

int smmObj_getNodeType(void* obj){ 	//나머지도 마저 정의  
	
	smmObject_t* ptr=(smmObject_t*)obj;
	return ptr->type;
}

//element to string
int smmObj_getNodeCredit(void* obj)
{
	smmObject_t* ptr=(smmObject_t*)obj;
    return ptr->credit;
}

int smmObj_getNodeEnergy(void* obj)
{
	smmObject_t* ptr=(smmObject_t*)obj;
    return ptr->energy;
}

