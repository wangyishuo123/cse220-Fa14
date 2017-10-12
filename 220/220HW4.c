//Yishuo Wang

#include <stdio.h>
#include <stdlib.h>
int MAXPlayers=5;
int MINPlayers=2;
int numPlayers=0;
int flagP=1;//flag for DecidePlayer
int flagR=1;//flag for DecideRound
int total_round;//total round
int current_round=0;//current round
int current_player=0;//each player
int SEED;
int earn_point;//the points that winner get in each ground
int min_id = 1;//the player who has has smallest point in each ground
int max_id = 1;//the player who has max point in each ground
int leader=0;//the points of the leader
int leader_point=0;
//int Number_Die=2;
char choose;//choose R,H T
int a[5];//for each dies points
int b[5]={0,0,0,0,0};//for the sum of each player's dies points for each
int p[5]={0,0,0,0,0};//the points for each player

void printTOTALSCORETable(void){
	int i=0;
	int j=0;
	int k=0;
	GetLeader(p);
	printf("Round: %d\n", current_round);
	printf("Round Winner: Player %d, Points = %d\n", min_id , earn_point); 
	printf("%-10s","Player: ");
	for(i=0;i<numPlayers;i++){
		printf("%-5d", i+1);///////////////////////////////////
	}
	printf("\n============================================\n");
	printf("%-10s","Round: ");
	for(j=0;j<numPlayers;j++){
		if(b[j]==0){
			printf("%-5c",'-');
		}
		else
			printf("%-5d",b[j]);
	}
	printf("\n%-10s","Total: ");
	for(k=0;k<numPlayers;k++){
		if(p[k]==0){
			printf("%-5c",'-');
		}
		else
			printf("%-5d",p[k]);
	}
	printf("\n");
	printf("Player %d is the leader.\n", leader);
}


void printRoundTable(void){
	int i=0;
	int j=0;
	int k=0;
	printf("Round: %d\n",current_round);
	printf("%-10s","Player: ");
	for(i=0;i<numPlayers;i++){
		printf("%-5d",i+1);//////////////////////////////////
	}
	printf("\n============================================\n");
	printf("%-10s","Round: ");
	for(j=0;j<numPlayers;j++){
		if(b[j]==0){
			printf("%-5c",'-');
		}
		else
			printf("%-5d",b[j]);
	}
	printf("\n%-10s","Total: ");
	for(k=0;k<numPlayers;k++){
		if(p[k]==0){
			printf("%-5c",'-');
		}
		else
			printf("%-5d",p[k]);
	}
	printf("\n");

}


void drawDice(int a[], int n){
	int i=0,p = 0;
	for (i = 0; i < n; i++) {
		printf("- - - - -  ");
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("|   %d   |  ",a[i]);
	}
	printf("\n");
	for (i = 0,p=0; i < n; i++) {
		printf("- - - - -  ");
		p+=a[i];
	}
	b[current_player - 1]=p;
	printf("\n\nSum: %d\n",b[current_player-1]);
}

int WinnerForRound(int a[]){
	int i;
	int j;
	int min=50;
	int max=0;
	//get min
	for(i=0;i<numPlayers;i++){
		if(min>b[i]){
			min=b[i];
			min_id = i+1;//in each round, player i is the winter who has the smallest point
		}
	}
	//get max
	for(j=0;j<numPlayers;j++){
		if(max<b[j]){
			max=b[j];
			max_id = i+1;
		}
	}
	earn_point=max-min;
	return p[min_id-1]+=earn_point;
}
int GetLeader(int a[]){
	int k=0;
	leader_point=0;//make sure can get into if
	for(k=0;k<numPlayers;k++){
		if(leader_point <p[k]){
			leader_point=p[k];
			leader=k+1;
		}
	}
}


int rollDie(void){
	return 1 + (int) (6.0 * rand() / (RAND_MAX + 1.0));
}

void player_action(int id){
	int i=0;
	int h=0;
	int j=0;
	int Number_Die = 2;
	while(1) {
		choose = getchar();
		if (choose == 'R' && Number_Die < 5){
			Number_Die++;
			for(i=0;i<Number_Die;i++){
				a[i]=rollDie();
			}
			drawDice(a,Number_Die);
			printf("Player %d Enter \"R\" to roll again, \"H\" to hold, or \"T\" for round\n", current_player );		
			if (Number_Die==5) {
				for (j=0; j < Number_Die; j++) {
					h+=a[j];
				}
				b[id-1]=h;
				return;
			}
		}
		else if (choose=='T'){
			printRoundTable();
			printf("Player %d Enter \"R\" to roll again, \"H\" to hold, or \"T\" for round\n",  current_player );
		}
		else if(choose=='H'){
			for (j=0; j < Number_Die ; j++) {
				h+=a[j];
			}
			b[id-1]=h;
			return;
		}		
	}
}

int main(void){
	char Play_Quit='P';
	printf("Enter SEED: ");
	 scanf("%d", &SEED);
	srand(SEED);
	
	
	//system("pause");
	//number of players
	while(Play_Quit=='P'){
		int g=0;
		int f=0;
		for (f=0;f<5;f++){
				p[f]=0;
		}
		while(flagP){
			printf("Enter the number of players (2-5): ");
			 scanf("%d", &numPlayers);
			 //getchar(); 
			if(numPlayers >= MINPlayers && numPlayers <= MAXPlayers)
				flagP=0;
			else
				printf("%d players can not play this game.\n", numPlayers);
		}
		//number of rounds
		while(flagR){
			printf("Enter the number of Rounds to play(1-10): ");
			 scanf("%d", &total_round);
			 //getchar(); 
			if(total_round>=1 && total_round<=10) 
				flagR=0;
			else 
				printf("%d rounds can not happen.\n", total_round);
		}

		for (current_round = 1; current_round <= total_round; current_round++) {
			printf("Round %d\n",current_round);
			for (g=0;g<5;g++){
				b[g]=0;
			}
			for (current_player = 1; current_player <= numPlayers; current_player++) {
				printf("Player %d Enter \"R\" to roll the dice: ",current_player);
				player_action(current_player);
			}
			
			WinnerForRound(b);
			printTOTALSCORETable();
		
		}
		printf("CONGRATULATIONS Player %d YOU WIN!\n", leader);
		
		
		Play_Quit='A';//just for get into the while below 
		while( Play_Quit!='P' && Play_Quit!='Q'){
			printf("Enter \"P\" to Play again or \"Q\" to Quit: ");
			getchar();
			Play_Quit = getchar();
			if(Play_Quit=='Q'){
				printf("\nGame Finish...\n");
			}
			else if(Play_Quit!='P'){
				printf("The %c is not command.\n", Play_Quit);
			}
			
		}

	}

}

