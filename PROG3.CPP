/*This program allows the user to play the dice game Yahtzee         */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 10

void tie (int,int,int[],char *[],int);
void reroll2 (int[],int,int);
 
/*This function takes the names of the players and enters them into  */
/*an array.                                                          */
int names (int n, char *player[])
{
    int x,i;
    char name[MAX];
    if (n>0 && n<=5)
    {
	printf("Player names can be up to 10 characters long.\n");
	for (i=0;i<n;i=i+1)
	{
	    x=i+1;
	    printf ("Enter the name of player %d.",x);
	    scanf ("%s",name);
	    player[i]=calloc(strlen(name)+1,sizeof(char));
	    strcpy (player[i],name);
	    printf("\n");
	}
    return (0);
    }
    else
    {
    printf("Invalid choice!\nHow many players?(1-5)");
    return (1);
    }
}

/*This function simulates rolling a die and return's the value.      */
int roll ()
{
    int die;
    die = 1+(rand()%6);
    return (die);
}

/*This function finds the maximum integer value in an array.         */
int maxv (int roll1[], int f, int s)
{
    int i, y;
    y=s;
    for (i=s; i<=f; i=i+1)
    {
	if (roll1[i] > roll1[y])
	{
	    y=i;
	}
    }
    return (y);
}

/*This function swaps two string values in an array.                 */
void swap(char *player[],int x,int y)
{ 
    char *t
    emp;
    temp=player[x];
    player[x] = player[y];
    player[y]=temp;
}

/*This function swaps two integer values in an array.                */
void intswap(int roll1[],int x,int y)
{
    int temp;
    temp=roll1[x];
    roll1[x]=roll1[y];
    roll1[y]=temp;
}

/*This function breaks threeway or more ties.                        */
int rolltie (int roll1[],int ss,char *player[],int n)
{
    int m;
    int es, i;
    char c;
    es=ss;
    printf("A tie has occurred! We will now have a roll off!\n"); 
    for (i=ss;i<n;i=i+1)
    {
	if (roll1[i]==roll1[i+1])
	{
	    es = es+1;
	}
    }
    printf("%d %d \n",ss,es);
    for (i=ss;i<=es;i=i+1)
    {
	printf("%s: Press return to roll the dice.",player[i]);
	c=getchar();
	printf("\n");
	roll1[i]=roll();
	printf("You rolled a %d.\n",roll1[i]);
    }
    for (i=es;i>=ss;i=i-1);
    {
	m=maxv (roll1,es,ss);    
	intswap (roll1,m,i);
	swap (player,m,i);
    }
    tie(ss,es,roll1,player,n);
    return (ss+es-ss+1);
}

/*This function breaks two way ties by flipping a coin.              */
void cointie(int ss,int roll1[],char *player[])
{
    char *temp;
    char c;
    int es,coin,i;
    printf("A tie has occurred! We will flip a coin to break it!\n");
    coin=(rand()%2);
    if (coin==1)
    {
	temp = player[ss];
	player[ss]=player[ss+1];
	player[ss+1]=temp;
    }               
    printf("%s won the toss.\n",player[ss]);
}

/*This function breaks any ties that occur in the first roll.        */
void tie (int s,int e,int roll1[], char *player[],int n)
{
    int i;
    for (i=s;i<e;i=i+1)
    {
	int x, num, ss, z, c;
	if (roll1[i]==roll1[i+1])
	{
	    if (roll1[i]==roll1[i+2])
	    {
		z=rolltie(roll1,i,player,n);
		i=i+z;
	    }
	    else
	    {
		cointie(i,roll1,player);
	    }
	}
    }
}        

/*This function determines the order that the players will go in.    */
void order (int n,char *player[])
{
    char c;
    int i, x, y, z;
    int roll1[6];
    printf ("We will now roll to see who goes first.\n\n");
    for (i=0;i<n;i=i+1)
    {
	printf ("%s: Press return to roll the die.",player[i]);
	c = getchar();
	roll1[i] = roll();
	printf("\nYou rolled a %d.\n",roll1[i]);
    }
    for (i=0; i<n; i=i+1)
    {
	z=n-1;
	x=maxv (roll1, z, i);
	intswap (roll1, x, i);
	swap (player, x, i);
    }
    x=n-1;
    z=0;
    tie (z,x,roll1,player,n);
}

/*This function displays the numbers on the dice after each roll.    */
void outmen (int roll2[])
{
    int y;
    printf("die 1   die 2   die 3   die 4   die 5\n");
    printf("-------------------------------------\n  ");
    for (y=0;y<5;y=y+1)
    {
	printf("%d       ",roll2[y]);
    }
}

/*This function allows the player to reroll any or all of the dice   */
/*rolled during regular play.                                        */
void reroll(int roll2[])
{
    int dice[5];
    int num,z,i,x;
    printf("How many of the dice would you like to roll again?");
    z=0;
    while (z==0)
    {
	scanf("%d",&num);
	if (num>0 && num<=5)
	{
	    z=1;
	}
    }
    x=0;
    while (x==0)
    {
	x=1;
	printf("\nWhich dice will it be?");
	for (z=0;z<num;z=z+1)
	{
	    scanf ("%d",dice[z]);
	}
	for (z=0;z<num-1;z=z+1)
	{
	    for (i=z+1;i<num;i=i+1)    
	    {
		if (dice[z]==dice[i])
		{
		    x=0;
		}
	    }
	}
    }
    for (z=0;z<num;z=z+1)
    {
	roll2[dice[z]]=roll();
    }
    printf("\n\n");
    outmen(roll2);
}

/*This function is used to sort the array roll2 when necessary.      */
void sort(int roll2[])
{
    int val,i;
    for (i=0;i<4;i=i+1)
    {
	val=maxv(roll2,4,i);
	intswap (roll2,val,i);
    }
}

/*This function prints a score sheet and heading.                    */
void ssheet(int score[][13],char *player[],int n,int total3[])
{
    char c;
    int i,x,bonus[5]={0},total1[5]={0},total2[5]={0};
    printf("\n\n\nScores for this round:\n");
    printf("upper section     ");
    for (i=0;i<n;i=i+1)
    {
	printf("%10s ",player[i]);
    }
    printf("\n");
    printf("-----------------------------------------------------------------------\n");
    printf("aces:          "); 
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][0]);
    }
    printf("\n");
    printf("twos:          ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][1]);
    }
    printf("\n");
    printf("threes:        ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][2]);
    }
    printf("\n");
    printf("fours:         ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][3]);
    }
    printf("\n");
    printf("fives:         ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][4]);
    }
    printf("\n");
    printf("sixes:         ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][5]);
    }
    printf("\n");
    printf("total score:   ");
    for (i=0;i<n;i=i+1)
    {
	for (x=0;x<=5;x=x+1)
	{
	    total1[i]=total1[i]+score[i][x];
	}
    }
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",total1[i]);
    }
    printf("\n");
    printf("bonus:         ");
    for (i=0;i<n;i=i+1)
    {
	if (total1[i]>=63)
	{
	    bonus[i]=35;
	}
	else
	{
	    bonus[i]=0;
	}
	printf("        %3d",bonus[i]);
    }
    printf("\n");
    printf("total:         ");
    for (i=0;i<n;i=i+1)
    {
	total1[i]=total1[i]+bonus[i];
	printf("        %3d",total1[i]);
    }
    printf("\n");
    printf("lower section\n");                                      
    printf("-----------------------------------------------------------------------\n");
    printf("3 of a kind:   ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][6]);
    }
    printf("\n");
    printf("4 of a kind:   ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][7]);
    }
    printf("\n");
    printf("full house:    ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][8]);
    }
    printf("\n");
    printf("small straight:");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][9]);
    }
    printf("\n");
    printf("large straight:");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][10]);
    }
    printf("\n");
    printf("yahtzee:       ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][11]);
    }
    printf("\n");
    printf("chance:        ");
    for (i=0;i<n;i=i+1)
    {
	printf("        %3d",score[i][12]);
    }
    printf("\n");
    printf("total:         ");
    for (i=0;i<n;i=i+1)
    {
	for (x=6;x<=12;x=x+1)
	{
	    total2[i]=score[i][x]+total2[i];
	}
	printf("        %3d",total2[i]);
    }
    printf("\n");
    printf("grand total:   ");
    for (i=0;i<n;i=i+1)
    {
	total3[i]=total1[i]+total2[i];
	printf("        %3d",total3[i]);
    }
    printf("\n\n");
    printf("press return to continue\n");
    c=getchar();
}

/*This function controls the main portion of the game.               */
void playloop(char *player[],int roll2[],int n,int total3[])
{
    int score[5][13]={0};
    int ct,i,x,y,z,a,val;
    char c;
    for (i=1;i<=12;i=i+1)
    {
	for (x=0;x<n;x=x+1)
	{
	   printf("%s: Press return to roll the dice.",player[x]);
	   c = getchar();
	   printf("\n");
	   for (y=0;y<5;y=y+1)
	   {
	       roll2[y]=roll();
	   }
	   outmen (roll2);
	   z=0;
	   ct=0;
	   while (z==0)
	   {
	    printf("\n\nWould you like to roll any of the die again?"); 
	    printf("(y/n)");
            y=0;
	    while (y==0)
	    {
		c = getchar();
		switch (c)
		{
		    case 'y': case 'Y':
		    {
			ct=ct+1;
			reroll (roll2);
			y=1;
			break;
		    }
		    case 'n': case 'N':
		    {  
			z=1;
			y=1;
			break;
		    }
		}
	    }
	    if (ct==2)
	    {
		z=1;
	    }
	   }
       a=0;
       while (a==0)
       {
	printf("\n\nHow would you like to score your roll?\n");
	printf("1. Aces: 1 point for every 1.\n");
	printf("2. Twos: 2 points for every 2.\n");
	printf("3. Threes: 3 points for every 3.\n");
	printf("4. Fours: 4 points for every 4.\n");
	printf("5. Fives: 5 points for every 5.\n");
	printf("6. Sixes: 6 points for every 6.\n");
	printf("7. 3 of a kind: points = total of all dice.\n");
	printf("8. 4 of a kind: points = total of all dice.\n");
	printf("9. Full house (3 of a kind + 4 of a kind): ");
	printf("25 points.\n");
	printf("10. Small straight (sequence of 4 consecutive numbers): ");
	printf("30 points.\n");
	printf("11. Large straight (sequence of 5 consecutive numbers): ");
	printf("40 points.\n");
	printf("12. Yahtzee (5 of a kind): 50 points.\n");
	printf("13. Chance: points = total of all dice.\n");
	scanf("%d",&z);
	if (z>0 && z<14)
	{
	    a=1;
	}
       }
	switch (z)
	{
	    case 1:case 2:case 3:case 4:case 5:case 6:
	    {
		ct = 0;
		for (y=0;y<5;y=y+1)
		{
		    if (roll2[y]==z)
		    {
			ct=ct+1;
		    }
		}
		score[x][z-1]=z*ct;
		break;
	    }
	    case 7:
	    {   
		sort(roll2);
		ct=0;
		for (a=0;a<3;a=a+1)
		{
		    if (roll2[a]==roll2[a+1])
		    {
			if (roll2[a]==roll2[a+2])
			{
			    ct=1;
			}
		    }
		}
		if (ct>0)
		{
		    score[x][z-1]=roll2[0]+roll2[1]+roll2[2]+roll2[3]+roll2[4];
		}
		break;
	    }
	    case 8:
	    {
		ct=0;
		sort(roll2);
		for (a=0;a<2;a=a+1)
		{
		    if (roll2[a]==roll2[a+1] && roll2[a]==roll2[a+2])
		    {
			if (roll2[a]==roll2[a+3])
			{
			    ct=1;
			}
		    }
		}
		if (ct>0)
		{
		    score[x][z-1]=roll2[0]+roll2[1]+roll2[2]+roll2[3]+roll2[4];
		}
		break;
	    }
	    case 9:
	    {
		sort(roll2);
		val=0;
		ct=0;
		sort (roll2);
		for(0;a<4;a=a+1)
		{
		    if (roll2[a]==roll2[a+1])
		    {
			ct=ct+1;
		    }
		    if (a<3)
		    {
			if (roll2[a]==roll2[a+2])      
			{
			    val=1;
			}
		    }
		} 
		if (a>2 && val==1)
		{
		    score[x][z-1]=25;
		}
		break;
	    }
	    case 10:
	    {
		ct=0;
		sort (roll2);
		for (a=0;a<2;a=a+1)
		{
		    if (roll2[a]==roll2[a+1]+1 && roll2[a]==roll2[a+2]+2)
		    {
			if (roll2[a]==roll2[a+3]+3)
			{
			    ct=1;
			}
		    }
		}
		if (ct>0)
		{
		    score[x][z-1]=30;
		}
		break;
	    }    
	    case 11:
	    {
		ct=0;
		sort(roll2);
		if (roll2[0]==roll2[1]+1 && roll2[0]==roll2[2]+2)
		{
		    if (roll2[0]==roll2[3]+3 && roll2[0]==roll2[4]+4)
		    {
			score[x][z-1]=40;
		    }
		}
		break;
	    }
	    case 12:
	    {
		if (roll2[0]==roll2[1] && roll2[0]==roll2[2])
		{
		    if (roll2[0]==roll2[3] && roll2[0]==roll2[4])
		    {
			score[x][z-1]=50;
		    }
		}
		break;
	    }
	    case 13:
	    {
		score[x][z-1]=roll2[0]+roll2[1]+roll2[2]+roll2[3]+roll2[4];
		break;
	    }
            default:
            {
                break;
            }
	}
       }
    ssheet(score,player,n,total3);
    }
}

/*This function sorts the players names with respect to their total   */
/*score.                                                              */
void rank(char *player[],int total3[],int n)
{
    int x,i;
    for (i=0;i<=n;i=i+1)
    {
        x=maxv(total3,n-1,0);
        intswap(total3,x,i);
        swap(player,x,i);
    }
    printf("\n\nHere are the results of the game!\n");
    for (i=0;i<n;i=i+1)
    {
        printf("%d: %s\n",total3[i],player[i]);
    }
} 

main ()
{
    int n, rerun;
    char *player[6];
    int x,roll2[5],total3[5]={0};
    srand(time(NULL));
    printf("Welcome to YAHTZEE!\nHow many players?");
    rerun = 1;
    while (rerun==1)
    { 
	scanf ("%d",&n);
	printf("\n");            
	rerun=names (n, player);
    }
    order (n,player);
    printf("The order of play will be as follows:\n"); 
    for (x=0;x<n;x=x+1)
    {
	printf("%s\n",player[x]);
    }
    printf("\n");
    playloop (player,roll2,n,total3);
    rank (player,total3,n);
    return;
}

  

