//
//  smm_database.h
//  infection Path
//
//


#define smm_database_h

#define LISTNO_NODE             0
#define LISTNO_FOODCARD         1
#define LISTNO_FESTCARD         2
#define LISTNO_OFFSET_GRADE     3

int smmdb_addTail(int list_nr, void* obj);          //add data to tail
int smmdb_deleteData(int list_nr, int index);       //delete data
int smmdb_len(int list_nr);                   //get database length
void* smmdb_getData(int list_nr, int index);        //get index'th data

#if 0
char smmdb_genNodeGrade(player, int subject){
	//get player, print subject, random grade 
	char dropKey;
	//printsubject
	
	smmdb_getSubjectBoard(dfdf);
	
	//drop?
	printf("Drop this subject %s or keep taking it? press'd' you wanna drop, or press other key to continue listening",subject);
	scanf("%c",&dropKey);
	if(dropKey=='d'){
		
		return 0;
	}
	else{
		//randomgrade
		const char *inputcharacters = "A B C";
		int gradeLength=strlen(inputCharacters);
		char randomGrade = smmdb_getRandomGrade(inputChararcters,length);
		
		printf("You got %s",randomGrade);
		
	}
	


}  
#endif

