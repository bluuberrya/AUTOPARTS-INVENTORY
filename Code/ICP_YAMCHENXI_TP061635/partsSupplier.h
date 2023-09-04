#ifndef partSupplier_Header
#define partSupplier_Header

typedef struct {
	char supplierID[10], 
		supplierName[20], 
		location[16], 
		partID[10], 
		partName[20], 
		linefeed1;
} partsSupplier;

void printSupplierData(partsSupplier* sup);
void partsSupplierCreation();

#endif