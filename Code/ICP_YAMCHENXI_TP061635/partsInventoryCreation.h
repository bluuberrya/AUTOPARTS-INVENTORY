#ifndef partInventoryCreation_Header
#define partInventoryCreation_Header

typedef struct PARTSINVENTORY_ST{
	char partID[10], 
		sectionCode[5], 
		partName[20], 
		quantity[5], 
		linefeed;
} partsInventory;

void partsInventoryCreation();
void printInventoryData(partsInventory* inv);
int isInteger(char* checkData);

#endif