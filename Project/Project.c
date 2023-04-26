#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

struct MainFile{			// structure to store name, id and file name for a person
	char name[90];
	char id[11];
	char file[90];
};

int Search_ID(char line[], char find[]){			// function to separate id from string 'line' to compare with the argument entered by user to validate if he is the customer

	char temporary[10];					// initializing needed char arrays / strings and integers
	char temp;
	
	int i,j, compare;			
	int length = strlen(line);
	
	for (i = 0;i < length;i++){			// loop for going through every char in string 'line'
		temp = line[i];					// character on i index of line will be put in temp
		if (temp == '\t'){				// will check if the value in temp is '\t', it is the following will run
			i++;								// i increased to access the next character in 'line'
			for (j = 0;j < 7;j++){				
				temporary[j] = line[i];			// the next 7 characters in line after '\t' will be the id for the person, which will be stored in temporary
				i++;			// i increased to access the next character in 'line'
			}
			break;				// when the id is taken in string 'temporary', the loop will end using 'break' statement
		}
	}
	
	compare = strcmp(temporary, find);				// comparing the id entered by user and the id extracted from 'line', if its same, the strcmp function will return 0, if not, it will return a non-zero value 

	return compare;				// return the value returned by strcmp
}


float Gold(){							// Function for calculating zakat on gold
	
	FILE *f_ptr;										// Every day's gold rate will be taken from a file 'market rates' and the zakat will be calculated according to that
	f_ptr = fopen("Files/market rates.txt","r");
	char line[20], temporary[10], temp;
	float rate;
	int i, length;
	
	fgets(line,20,f_ptr);			// scanning a line from file into a string 'line'
	
	length = strlen(line);			
		
	for (i = 7 ;i < length;i++){			// loop for taking the price of gold from 'line'
		temporary[i-7] = line[i];
	}
		
	rate = atof(temporary);			// converting string to float
	
	fclose(f_ptr);
	
	float zakat, x;
	
	printf("Enter the amount of gold (in grams) you have: ");			// taking input how much gold user has and comparing it with nisaab
	scanf("%f", &x);
	
	if (x > 87.47){
		zakat = (x * rate) * 0.025;				// zakat will only be applied when they have more than 87.47 grams
		return zakat;
	}
	else{
		printf("\t\tYour amount of gold is less than 87.47 gm. Zakat is not applicable on your gold\n");
		return 0;
	}
}

float Silver(){					// Function for calculating zakat on silver
	
	FILE *f_ptr;
	f_ptr = fopen("Files/market rates.txt","r");			// Every day's silver rate will be taken from a file 'market rates' and the zakat will be calculated according to that
	char line[20], temporary[10], temp;
	float rate;
	int i, length;
	
	fgets(line,20,f_ptr);				// scanning the second line from file into a string 'line'
	fgets(line,20,f_ptr);

	length = strlen(line);			// loop for taking the price of silver from 'line'
		
	for (i = 10;i < length;i++){			// loop for taking the price of silver from 'line'
		temporary[i-7] = line[i];
	}
		
	rate = atof(temporary);		// converting string to float
	
	fclose(f_ptr);
	
	float zakat, x;
	
	printf("Enter the amount of silver (in grams) you have: ");			// taking input how much gold user has and comparing it with nisaab
	scanf("%f", &x);
	
	if (x > 612.35){				// zakat will only be applied when they have more than 612.35 grams
		zakat = (x * rate) * 0.025;
		return zakat;
	}
	else{
		printf("\t\tYour amount of silver is less than 612.35 gm. Zakat is not applicable on your silver\n"); //if silver is less than the limit no zakat will be applied
		return 0;
	}
}

float Personal(){ //Function on Calculating Zakat Of Personal Wealth/Cash/Money
	
	float zakat, x;
	
	printf("Enter the amount of personal wealth / cash (in rupees) you have: ");//taking input of the amount to calculate zakat
	scanf("%f", &x);
	
	if (x >= 100000){
        zakat = (x * 0.025);//calculating zakat if the amount is above Rs.100000/-
		return zakat;
	}
	else{
		printf("\tAmount is Less that 100000 Rs. Zakat not Applicable on your Personal Wealth.\n");//if amount is less than 100000 no zakat would be applied
		return 0;
	}
}

float Agriculture(){			//Creating a function of Agricultural Wealth (Profit)
	
	float zakat, x;
	int choice;
	
	printf("Enter the total earning from Agriculture this year: ");
    scanf("%f", &x);			//input the total profit of the year through agriculture
	if(x>0){
		
		printf("\tPress 1 for Canal Irrigation\n\tPress 2 for Rain Water Irrigation\n\tPress 3 for Both\n\tChoice: ");
		scanf("%d", &choice);				//due to different type of zakat rates asking for the type of irrigation performed on the agriculture.
		
		switch (choice){
			case 1:
				zakat = x * 0.05;			//rate of canal irrigation and calculating zakat
				return zakat;
			case 2:
				zakat = x * 0.1;			//rate of Rain Water irrigation and calculating zakat
				return zakat;
			case 3:
				zakat = x * 0.075;				//rate of Both  irrigation involved and calculating zakat
				return zakat;
		}							//made 3 cases for the zakat to be calculated
	}
	else{
		printf("\tZakat is not applicable on your Agriculture\n");
		return 0;						//if there is no earning or no agricultural land so no zakat would be applied
	}
}

float Others(){								//making a function of other belonging and equvalant for zakat to be calculated in precision.
	
	float zakat, x;
	char choice;
	
	printf("Do you have any other things on which Zakat is applicable? Press Y for Y or N for No\n\tChoice: ");					//asking the user that does he/she has any other belonging in his/her possession on which zakat is applicable if yes then entering the amount equivalent for it else returning zero for it.
	fflush(stdin);
	scanf("%c", &choice);
	
	if ((choice == 'Y') || (choice == 'y')){
		printf("\tEnter the equivalent amount of other goods you have: ");
		scanf("%f", &x);
		zakat = x * 0.025;				//if there is some equivalent zakat so the rate is applied on the equivalent amount and the zakat is return through the function
		return zakat;	
	}
	else if ((choice == 'N') || (choice == 'n')){
		return 0;												//if no Other items so return 0;
	}
}


int main(){
	
	int choice, choice2;
		
	printf("------------ WELCOME TO ZAKAT CALCULATOR ------------\n\nEnter\n1: if you are an old customer\n2: if you want to sign up\nChoice: ");
	scanf("%d", &choice);
	
	FILE *ptr;								//file pointer
	
	int flag = 0, length;						//declaring all the variables required to be initailized
	char userfile[20] = "Files/";
	float total_zakat;
	char name[90], id[7], line[90];
	char s[2] = "\t";
	char *token, c;
	struct MainFile line_division;
	
	time_t t;  
    time(&t);

	switch(choice) {		 //using a switch case to check that is that user is an old customer or he/she is signing up as a new customer.
            					//if he is an old customer case 1 / if he is a new customer case 2 implies.
		
		case 1:			//if the user is an old customer the case checks the data present in the text files and reads to confirm his/her identity to show his old data or the last zakat paid amount .
//			ptr = fopen("Files/customers.txt","r");									//opening the text file to read
			
			printf("\nEnter your name: ");					//taking name as input to check the text files
			fflush(stdin);
			gets(name);
			printf("Enter your id: ");								//taking ID as an input to verify the old customer
			fflush(stdin);
			gets(id);
			
			while(1){
				ptr = fopen("Files/customers.txt","r");				//opening the text file to read
				while (!feof(ptr)){							// will continue till the file has not ended
					fgets(line, 90, ptr);						
					token = strtok(line, s);
//					printf("\nTOKEN A: %s", token);
					strcpy(line_division.name,token);
					token = strtok(NULL, s);
//					printf("\nTOKEN B: %s", token);
					strcpy(line_division.id,token);
					token = strtok(NULL, s);
//					printf("\nTOKEN C: %s", token);
					strcpy(line_division.file,token);
					c = fgetc(ptr);
					if (c == EOF){
						break;
					}
					else{
						fseek(ptr, -1, SEEK_CUR);
					}
					if (!(strcmp(name,line_division.name)) && !(strcmp(id,line_division.id))){
						flag = 1;						// flag = 1 if the name and id from the user matches in file
						break;
					}
				}
				fclose(ptr);
				
				if (flag == 1){
					
					strncat(userfile,line_division.file,11);
					
					printf("\nLogin Successful!!\n\n");				//if the user name and id matches so operation is successfull and user can calculate and store his/her zakat
					
					
					printf("Choose from the following. Enter:\n1. for Calculating new Zakat\n2. for priniting previous records\n\tChoice: ");
					scanf("%d", &choice2);		
					switch (choice2){
						case 1:
							ptr = fopen(userfile,"a");							//opening the text file to append so that the new zakat calculated is added to the users history
							printf("\nStarting Calculator...\n\n");
							
							total_zakat = Gold() + Silver() + Personal() + Agriculture() + Others();					//calculating zakat through the declared functions
							
							printf("\nZakat calculated for these values is Rs.%.2lf", total_zakat);
							fprintf(ptr, "Zakat calculated is Rs.%.2lf on %s",  total_zakat, ctime(&t));			//printing the total zakat and displaying the date & time at which calculated
							fclose(ptr);
							break;
						case 2:
							ptr = fopen(userfile,"r");
							printf("\nYour history with us:\n");
							do{
								c = fgetc(ptr);
								printf("%c", c);
							} while(c != EOF);
					}		
							
					break;
				}
				if (flag == 0){
					printf("ID not found! Enter your details again. \n\tName: ");				//if the user entered wrong credentials id so an error is displayed to re-write the name and id again
					fflush(stdin);
					gets(name);
					printf("\tID: ");				
					fflush(stdin);
					gets(id);
				}
			}
			break;
			
		case 2:
			
			printf("\nEnter your name: ");							//taking users name as input to store/create his/her new id in the data base
			fflush(stdin);
			gets(name);			
			
			printf("Enter a 7 digit id for yourself: ");							//entering a unique id  for the user so that he/she can access it later
			fflush(stdin);
			gets(id);
            length = strlen(id);
                        
            while (length != 7){
                printf("ID should be of 7 digits. Enter id again: ");				//validation of getting a 7 digit id else entering it again in the correct format
                fflush(stdin);
                gets(id);
                length = strlen(id);
			}
			
			while(1){
				ptr = fopen("Files/customers.txt","r");								//opening the file to read and search the id ,(is it available or not)
				flag = 0;
				while(!feof(ptr)){
					fgets(line, 90, ptr);
					if (Search_ID(line, id) == 0){
						flag = 1;
						break;
					}
				}
				fclose(ptr);
				
				if (flag == 1){								//checking that is the ID that user desired to choose is available or taken
					printf("\tID already taken. Enter a different 7 digit ID: ");
					fflush(stdin);
					gets(id);
				}
				else{
					printf("\nSign up Complete!!\nStarting the calculator...\n\n");							//displaying user that signup is complete
					ptr = fopen("Files/customers.txt","a");							//opening the file to append the data
					fprintf(ptr,"%s\t%s\t%s.txt\n", name, id, id);			//appending the data, adding the user in data
					fclose(ptr);											//closing the file
					break;
				}
		}

			strcat(userfile,id);
			strcat(userfile,".txt");
			ptr = fopen(userfile,"w");

			total_zakat = Gold() + Silver() + Personal() + Agriculture() + Others();				//calculating zakat through the declared functions
            //Calculating the total zakat for the person
			
			fprintf(ptr, "Zakat calculated is Rs.%.2lf on %s",  total_zakat, ctime(&t));
            												//printing the total zakat and displaying the date & time at which calculated
			printf("\n\nZakat calculated for these values is Rs.%.2lf", total_zakat);
			fclose(ptr);
			
	}
	
	//printing the suggestions where the Zakat can be given
	printf("\n\nYour Zakat can be given to the folowing:\n1.	The poor (al-fuqara'), meaning low-income or indigent.\n2.	The needy (al-masakin), meaning someone who is in difficulty.\n3.	Zakat administrators.\n4.	Those whose hearts are to be reconciled, meaning new Muslims and friends of the Muslim community.\n5.	Those in bondage (slaves and captives).\n6.	The debt-ridden.\n7.	In the cause of God.\n8.	The wayfarer, meaning those who are stranded or traveling with few resources.");
   
   	printf("\n\n******END OF PROGRAM******");
}
