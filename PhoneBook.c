#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
HANDLE hOut;

struct kontakt_t {
	char name[40];
	char lastname[40];
	char email[40];
	int phone_nr;
	struct {
		int day;
		int month;
		int year;
	};
	struct {
		char street_name[40];
		int street_number;
		char city[40];

	};
};
void thankYouForPatience();
void menu(int i, struct kontakt_t data[], int counter);
void menu_expanded(int i, struct kontakt_t data[], int counter);
void enter_data(struct kontakt_t data[], int i);
void save_data(struct kontakt_t data[], int i, int counter);
void load_data(struct kontakt_t data[], int i, int counter);

int main() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	struct kontakt_t data[100];
	int i = 0;
	int counter = 0;
	int choice = 0;


	
	FILE *pFile = fopen("phone_book.txt", "rt");
	if (pFile == NULL) {
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("Couldn't find phone_book.txt file. Creating new one...\n");
		system("pause");
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		FILE *pFile2 = fopen("phone_book.txt", "at");
		fprintf(pFile2, "0\n");
		for (i = 0; i <100; i++) {
			fprintf(pFile2, "--- ", data[i].name);
			fprintf(pFile2, "--- ", data[i].lastname);
			fprintf(pFile2, "--- ", data[i].email);
			fprintf(pFile2, "0 ", data[i].phone_nr);
			fprintf(pFile2, "0 ", data[i].day);
			fprintf(pFile2, "0 ", data[i].month);
			fprintf(pFile2, "0 ", data[i].year);
			fprintf(pFile2, "--- ", data[i].street_name);
			fprintf(pFile2, "0 ", data[i].street_number);
			fprintf(pFile2, "---\n", data[i].city);
		}
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		system("CLS");
		printf("File created! :)\n");
		thankYouForPatience();
		printf("\nPlease restart the program!\n\n");
		fclose(pFile2);
		exit(1);
	}

	load_data(data, i, counter);
	fscanf(pFile, "%d", &counter);
	do {
		menu(i, data, counter);
		while (scanf("%d", &choice) != 1)
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("Error, try again: ");
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
		switch (choice) {
		case 1: {
			if (i >= 99) {
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("It's the last record, u can't go further.");
				_getch(); //_getch() bo #include <conio.h> 
			}
			else i++; }break;
		case 2: {
			if (i == 0) {
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("No previous record. It's the first one.");
				_getch();
			}
			else i--; }break;
		case 3: {menu_expanded(i, data, counter); }break;
		case 4: {
			if (data[i].day == 0 && data[i].month == 0 && data[i].year == 0) {
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("This record is empty.\n");
			}
			else {
				strcpy(data[i].name, "---");
				strcpy(data[i].lastname, "---");
				strcpy(data[i].email, "---");
				data[i].phone_nr = 0;
				data[i].day = 0;
				data[i].month = 0;
				data[i].year = 0;
				strcpy(data[i].street_name, "---");
				data[i].street_number = 0;
				strcpy(data[i].city, "---");
				counter--;
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				printf("Record deleted.\n");
			}
			system("pause");
		} break;
		case 5: {enter_data(data, i); counter++; }break;
		case 6: {
			int teleportation = 0;
			printf("Teleport to: ");
			while (scanf("%d", &teleportation) != 1)
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
				printf("\nError, try again: ");
				int c;
				while ((c = getchar()) != '\n' && c != EOF);
			}
			if (teleportation > 99 || teleportation<0) {
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			printf("You can teleport only to record 0-99");
			_getch(); //_getch() bo #include <conio.h> 
			}else i = teleportation; }break;
		default: {
			save_data(data, i, counter);
			system("CLS");
			printf("\n\n\n\n\t\t\t\tGOOD BYE!\n\n\n\n\t\t\t");
			exit(1);
		}break;
			return 0;
		}
	} while (choice != 0);
}

void menu(int i, struct kontakt_t data[], int counter) {
	system("CLS");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("       MENU\n");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("Actual record:   #%d\n", i);
	printf("Name:             %s\n", data[i].name);
	printf("Lastname:         %s\n", data[i].lastname);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("------------------------------------------------\n");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	printf("Record counter:   %d\n", counter);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("------------------------------------------------\n");
	printf("1|Next record     W\n");
	printf("2|Previous record W\n");
	printf("3|Expand record   W\n");
	printf("4|Delete record   W\n");
	printf("5|Add/Edit record W\n");
	printf("6|Jump to record  W\n");
	printf("0|Exit            W\n");
	printf(">>> ");
}
void menu_expanded(int i, struct kontakt_t data[], int counter) {
	system("CLS");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("       MENU EXPANDED\n");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("Actual record:   #%d\n", i);
	printf("Name:             %s\n", data[i].name);
	printf("Lastname:         %s\n", data[i].lastname);
	printf("Email:            %s\n", data[i].email);
	printf("Phone number:     %d\n", data[i].phone_nr);
	printf("Birth date:       %d.%d.%d\n", data[i].day, data[i].month, data[i].year);
	printf("Accomodation:     %s %d %s\n", data[i].street_name, data[i].street_number, data[i].city);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("------------------------------------------------\n");
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	printf("Record counter:   %d\n\n", counter);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	//printf("------------------------------------------------\n");
	//printf("1|Next record     NW\n");
	//printf("2|Previous record NW\n");
	//printf("3|Fold record     NW\n");
	//printf("4|Delete record   NW\n");
	//printf("5|Add record      NW\n");
	//printf("0|Exit            NW\n");
	//printf(">>> ");
	system("pause");
}
void enter_data(struct kontakt_t data[], int i)
{
	system("CLS");
	printf("Name: ");
	scanf("%s", data[i].name);
	printf("Lastname:  ");
	scanf("%s", data[i].lastname);
	printf("Email: ");
	scanf("%s", data[i].email);
	printf("Phone number: ");
	scanf("%d", &data[i].phone_nr);
	printf("Birth date(example: 13 06 1996): ");
	scanf("%d %d %d", &data[i].day, &data[i].month, &data[i].year);
	printf("Accomodation(example: Dluga 125 Zgierz): ");
	scanf("%s %d %s", data[i].street_name, &data[i].street_number, data[i].city);
	return;
}
void save_data(struct kontakt_t data[], int i, int counter) {
	FILE *pFile = fopen("phone_book.txt", "w+");
	if (pFile == NULL) {
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		perror("Couldn't open the phone_book.txt file");
		system("pause");
		return;
	}
	fprintf(pFile, "%d\n", counter);
	for (i = 0; i <100; i++) {
		fprintf(pFile, "%s ", data[i].name);
		fprintf(pFile, "%s ", data[i].lastname);
		fprintf(pFile, "%s ", data[i].email);
		fprintf(pFile, "%d ", data[i].phone_nr);
		fprintf(pFile, "%d ", data[i].day);
		fprintf(pFile, "%d ", data[i].month);
		fprintf(pFile, "%d ", data[i].year);
		fprintf(pFile, "%s ", data[i].street_name);
		fprintf(pFile, "%d ", data[i].street_number);
		fprintf(pFile, "%s\n", data[i].city);
	}
	printf("Save completed.\n");
	system("pause");
	fclose(pFile);
}
void load_data(struct kontakt_t data[], int i, int counter) {
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	FILE *pFile = fopen("phone_book.txt", "rt");
	if (pFile == NULL) {
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		perror("Couldn't open the phone_book.txt file");
		system("pause");
		return;
	}
	fscanf(pFile, "%d", &counter);
	for (i = 0; i < 100; i++) {
		fscanf(pFile, "%s", &data[i].name);
		fscanf(pFile, "%s", &data[i].lastname);
		fscanf(pFile, "%s", &data[i].email);
		fscanf(pFile, "%d", &data[i].phone_nr);
		fscanf(pFile, "%d", &data[i].day);
		fscanf(pFile, "%d", &data[i].month);
		fscanf(pFile, "%d", &data[i].year);
		fscanf(pFile, "%s", &data[i].street_name);
		fscanf(pFile, "%d", &data[i].street_number);
		fscanf(pFile, "%s", &data[i].city);
	}
	printf("\n\n\n\n\t\t\t\tLoad completed.\n\n\n\n\t\t\t");
	system("pause");
	fclose(pFile);
}
void thankYouForPatience() {
	
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("___________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$"); 
	printf("_______");
	printf("$$");
	printf("_");
	printf("$\n");//1
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("____________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY); 
	printf("$$$");
	printf("__");
	printf("$");
	printf("_");
	printf("$$$$\n");//2
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("____________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$");
	printf("__");
	printf("$$");
	printf("_____");
	printf("$\n"); //3
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("___________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$");
	printf("_");
	printf("$");
	printf("__");
	printf("$");
	printf("_____");
	printf("$\n"); //4
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("__________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$");
	printf("_____");
	printf("$$");
	printf("___");
	printf("$$$$$$\n");//5 
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("_________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$");
	printf("______");
	printf("$$");
	printf("_");
	printf("$");
	printf("______");
	printf("$$\n"); //6 
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$");
	printf("_______");
	printf("$$");
	printf("________");
	printf("$");
	printf("_");
	printf("$$\n"); //7 
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$");
	printf("_______");
	printf("$");
	printf("_______");
	printf("$\n");//8
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$$");
	printf("_____");
	printf("$");
	printf("_______");
	printf("$\n"); //9 
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("_________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$$");
	printf("____");
	printf("$");
	printf("______");
	printf("$\n");//10
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("__________");
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$$$$");
	printf("_______");
	printf("$\n");//11 
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("__");
	printf("$$$");
	printf("_________"); 
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("$$$$$$$");
	printf("_");
	printf("$$\n");//12
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("$$$$$$$_________$$$\n_$$$$$$$_________$\n__$$$$$$_________$$\n___$$$___$_______$$\n___________$_____$__$\n_______$$$$_$___$\n_____$$$$$$__$_$$\n____$$$$$$$___$$\n____$$$$$______$\n____$$$________$\n____$__________$\n_____________$_$\n______________$$\n______________$\n______________$\n______________$\n______________$\n______________$");
};

