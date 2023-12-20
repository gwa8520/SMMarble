
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"



//board configuration parameters
static int board_nr; 
static int food_nr;
static int festival_nr;

static int player_nr;

typedef struct player{
	
	int energy;
	int position;
	char name[MAX_CHARNAME];
	int accumCredit;
	int flag_graduate;

} player_t;

static player_t *cur_player;
//static player_t cur_player[MAX_PLAYER];

#if 0
static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME];
#endif

//function prototypes

#if 0
int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif

void printGrades(int player){
	
	int i;
	void*gradeptr;
 
	for(i=0;i<smmdb_len(LISTNO_OFFSET_GRADE+player);i++){
		
			gradeptr= smmdb_getData(LISTNO_OFFSET_GRADE+player, i);
			//printf("%s: %i\n",smmObj_getNodeName(gradeptr),smmObj_genNodeGrade);
	}

}


void printPlayerStatus(void){
	
	int i;
	
	for(i=0;i<player_nr;i++){
		
		printf("%s: credit %i, energy %f, position %i\n",
				cur_player[i].name,
				cur_player[i].accumCredit,
				cur_player[i].energy,
				cur_player[i].position);
	}

}


void generatePlayers(int n, int initEnergy){
	//n time loop
	
	int i;
	for(i=0;i<n;i++){
	
	// 이름 받기  
		printf("Input player %i's name: ",i);
		scanf("%s",cur_player[i].name); 
		fflush(stdin);
	
	//포지션
	//player_position[i]=0;
		cur_player[i].position=0;
	
	//에너지  
		//player_energy[i]=initEnergy;
	    cur_player[i].energy=initEnergy;	
		cur_player[i].accumCredit=0;
		cur_player[i].flag_graduate=0;	    
	    
	}
}

int rolldie(int player)
{
    char c;
    printf(" Press any key to roll the dice (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    
#if 0
    if (c == 'g')
        printGrades(player);
#endif
    
    return (rand()%MAX_DIE + 1);
}


//action code when a player stays at a node
void actionNode(int player)
{
	void*boardptr= smmdb_getData(LISTNO_NODE, cur_player[player].position);
	//int type = smmObj_getNodeType(cur_player[player].position);
	int type=smmObj_getNodeType(boardptr);  
	void*gradeptr;
	char *name=smmObj_getNodeName(gradeptr);
    
	switch(type)
    {
    	
        //case lecture:
        case SMMNODE_TYPE_LECTURE:
         if
		 (cur_player[player].accumCredit += smmObj_getNodeCredit(boardptr));
		(cur_player[player].energy -= smmObj_getNodeEnergy(boardptr));
		
		//grade
		gradeptr= smmObj_genObject(name, smmObjType_grade,0,smmObj_getNodeCredit(boardptr),0,0); 
    	smmdb_addTail(LISTNO_OFFSET_GRADE+player , gradeptr); 
		
		break;	
			
        default:
            break;
    }
}

void goForward(int player, int step){
	
	void*boardptr;
	cur_player[player].position += step;
	
	boardptr= smmdb_getData(LISTNO_NODE, cur_player[player].position);
	
	printf("%s go to node %i (name: %s)\n",
			(cur_player[player].name,cur_player[player].position),
			smmObj_getNodeName(boardptr)); 
}


int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn=0;
    int foodName;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1; 
    }
    
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i" ,name, &type, &credit, &energy) == 4 ) //read a node parameter set
    {
    	void *boardObj= smmObj_genObject(name, smmObjType_board, type,credit,energy,0); 
    	smmdb_addTail(LISTNO_NODE, boardObj); 
	
    	
    	if (type == SMMNODE_TYPE_HOME)
    		initEnergy = energy;
    	board_nr++;
    	
        //store the parameter set
    }

	
    fclose(fp); 
 	printf("Total number of board nodes : %i\n", board_nr);
    
    for(i=0;i<board_nr;i++){
    	
    	void*boardObj=smmdb_getData(LISTNO_NODE, i); 
    	printf("node %i : %s, %i(%s),credit %i, energy %i\n",
		 i, smmObj_getNodeName(boardObj), smmObj_getNodeType(boardObj), smmObj_getTypeName(smmObj_getNodeType(boardObj)),
				smmObj_getNodeCredit(boardObj), smmObj_getNodeEnergy(boardObj));
	} 
    
    //printf("(%s)",smmObj_getTypeName(SMMNODE_TYPE_LECTURE));
    
    
    #if 0
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    
    while (fscanf(fp, "%s %i" ,foodName, &energy) == 2) //read a food parameter set
    {
    	void *boardObj= smmObj_genObject(foodName,smmObjType_t, type, credit, energy, 0); 
    	smmdb_addTail(LISTNO_NODE, boardObj); 
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    
    
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s" ,name) == 1) //read a festival card string
    {
    	void *boardObj= smmObj_genObject(name, smmObjType_board, type,credit,energy,0); 
    	smmdb_addTail(LISTNO_NODE, boardObj); 
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    #endif
    
    
    
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr
        printf("input player no.:");
    	scanf("%d",&player_nr); 
    	fflush(stdin);
    }
    while (player_nr<0 || player_nr>MAX_PLAYER);
    
    cur_player= (player_t*)malloc(player_nr*sizeof(player_t));

    
    generatePlayers(player_nr,initEnergy);
	
    
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        printPlayerStatus();
        
        //4-2. die rolling (if not in experiment) 
        die_result = rolldie(turn);
        
        
        //4-3. go forward
        goForward(turn,die_result);

		//4-4. take action at the destination node of the board
        actionNode(turn);
        
        
        //4-5. next turn
        turn=(turn+1)%player_nr;
        
    }
    
    free(cur_player);
    system("PAUSE");
    return 0;
}
