//Yam Chen Xi TP061635
#include "main.h"
#include "menu.h"

int main(){
	char cont;
	
	//Loop menu until user wants to end the program
	do {
		printf("Welcome to Automobile Parts Inventory Management System\n- - - - -\n");
		menu();

		printf("\nPress <enter> to continue OR 'X' to end: ");
		scanf("%c", &cont);
		system("cls");
	} while ((cont != 'x') && (cont != 'X'));

	printf("\nThank you and have a great day! \n");
	return 0;
}