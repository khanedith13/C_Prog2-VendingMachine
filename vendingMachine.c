#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STORES 50
#define MAX_PRODUCTS 100
#define MAX_CART 100
#define MAX_INVENTORY_ITEMS 500

typedef struct{
  int id;
  char name[50];
  float price;
  int stock;
}Product;

typedef struct{
    char storeName[50];
    Product products[MAX_PRODUCTS];
    int productCount;
}Store;

typedef struct{
    char storeName[50];
    char productName[50];
    int productID;
    int quantity;
    float price;
    float total;
}Cart;

typedef struct {
    char storeName[50];
    char productName[50];
    int quantity;
    float total;
}InventoryItem;

// SAVE CASH
void saveCash(float cash){
    FILE *fp=fopen("cash.txt","w");
    if(fp==NULL){
        printf("\nError Saving Cash!\n");
        return;
    }
    fprintf(fp,"%.2f",cash);
    fclose(fp);
}

// LOAD CASH
float loadCash(){
    FILE *fp;
    float cash=500;
    fp=fopen("cash.txt","r");

    if(fp==NULL){
        fp=fopen("cash.txt","w");
        if(fp!=NULL){
            fprintf(fp,"500");
            fclose(fp);
        }
        return 500;
    }

    if(fscanf(fp,"%f",&cash)!=1){
        fclose(fp);
        saveCash(500);
        return 500;
    }

    fclose(fp);
    return cash;
}

// FIND PRODUCT
int findProduct(Store stores[],int storeIndex,int productID){
    for(int i=0;i<stores[storeIndex].productCount;i++){
        if(stores[storeIndex].products[i].id==productID){
            return i;
        }
    }
    return -1;
}

// DISPLAY PRODUCTS
void displayProducts(Store stores[],int storeIndex){
    printf("\n=====================================================================\n");
    printf("                            %s\n",stores[storeIndex].storeName);
    printf("=====================================================================\n");
    printf("%-5s %-20s %-15s %-10s\n",
            "ID",
            "Product",
            "Price",
            "Stock");
    printf("---------------------------------------------------------------------\n");

    for(int i=0;i<stores[storeIndex].productCount;i++){
        printf("%-5d %-20.20s PHP %-10.2f %-10d\n",
                stores[storeIndex].products[i].id,
                stores[storeIndex].products[i].name,
                stores[storeIndex].products[i].price,
                stores[storeIndex].products[i].stock);
    }
    printf("=====================================================================\n");
    printf("\nEnter 0 To Go Back\n");
}

// SAVE PRODUCTS
void saveProducts(Store stores[],int storeCount){
    FILE *fp=fopen("products.txt","w");

    if(fp==NULL){
        printf("\nError Saving Products!\n");
        return;
    }

    for(int i=0;i<storeCount;i++){
        fprintf(fp,"===== %s =====\n",stores[i].storeName);
        for(int j=0;j<stores[i].productCount;j++){
            fprintf(fp,"%d | %s | PHP %.2f | Stock: %d\n",
                    stores[i].products[j].id,
                    stores[i].products[j].name,
                    stores[i].products[j].price,
                    stores[i].products[j].stock);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

// HELPER FUNCTION: Removes column spacing blank paddings left by formatted file printing
void trimTrailingSpace(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r' || str[len - 1] == '\n')) {
        str[len - 1] = '\0';
        len--;
    }
}

// RUNTIME LOADING: Parses inventory.txt fresh from disk to capture all external manual modifications
int runtimeLoadInventoryFile(InventoryItem items[]) {
    int itemCount = 0;
    FILE *fp = fopen("inventory.txt", "r");
    if (fp == NULL) return 0; // If file is missing or cleared entirely, returns 0 entries

    char line[250];
    int dataSection = 0;

    while (fgets(line, sizeof(line), fp)) {
        // CHANGED: Parsed files now identify the data block via the updated "INVENTORY" header string
        if (strstr(line, "INVENTORY") || strstr(line, "No.   Product")) {
            dataSection = 1;
            continue;
        }
        if (strstr(line, "Starting Cash:") || strstr(line, "Change:") || strstr(line, "=======")) {
            if (strstr(line, "Starting Cash:") || strstr(line, "Change:")) {
                dataSection = 0;
            }
            continue;
        }

        if (dataSection && strlen(line) > 10) {
            int no;
            char prod[50], store[50];
            int qty;
            float total;

            if (sscanf(line, "%d", &no) == 1) {
                snprintf(prod, 21, "%s", line + 6);
                snprintf(store, 21, "%s", line + 27);
                trimTrailingSpace(prod);
                trimTrailingSpace(store);

                char *cashPtr = strstr(line, "PHP");
                if (cashPtr != NULL && sscanf(cashPtr, "PHP %f", &total) == 1 && sscanf(line + 48, "%d", &qty) == 1) {
                    if (itemCount < MAX_INVENTORY_ITEMS) {
                        strcpy(items[itemCount].productName, prod);
                        strcpy(items[itemCount].storeName, store);
                        items[itemCount].quantity = qty;
                        items[itemCount].total = total;
                        itemCount++;
                    }
                }
            }
        }
    }
    fclose(fp);
    return itemCount;
}

int main() {




  return 0;  
}
