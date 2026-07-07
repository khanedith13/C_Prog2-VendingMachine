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

// INSTANT SINGLE ITEM RUNTIME UPDATE: Combines external text file state with immediate choices
void mergeAndCommitProductToInventoryFile(char* store, char* product, int qty, float total, float startingCash, float change) {
    InventoryItem items[MAX_INVENTORY_ITEMS];
    
    // Step 1: Read whatever is written on the file right now (even if manually changed mid-transaction)
    int itemCount = runtimeLoadInventoryFile(items);

    // Step 2: Search and merge this specific target transaction purchase
    int duplicateIndex = -1;
    for (int j = 0; j < itemCount; j++) {
        if (strcmp(items[j].productName, product) == 0 &&
            strcmp(items[j].storeName, store) == 0) {
            duplicateIndex = j;
            break;
        }
    }

    if (duplicateIndex != -1) {
        items[duplicateIndex].quantity += qty;
        items[duplicateIndex].total += total;
        // Clean up if a cancellation hits absolute zero tracking thresholds
        if(items[duplicateIndex].quantity <= 0) {
            for(int k = duplicateIndex; k < itemCount - 1; k++) {
                items[k] = items[k+1];
            }
            itemCount--;
        }
    } else if (qty > 0) {
        if (itemCount < MAX_INVENTORY_ITEMS) {
            strcpy(items[itemCount].productName, product);
            strcpy(items[itemCount].storeName, store);
            items[itemCount].quantity = qty;
            items[itemCount].total = total;
            itemCount++;
        }
    }

    // Step 3: Completely output the unified tables back into storage text files
    FILE *fp = fopen("inventory.txt", "w");
    if (fp == NULL) return;

    fprintf(fp, "\n=====================================================================\n");
    // CHANGED: Overwritten files now use the updated header label
    fprintf(fp, "                            INVENTORY\n"); 
    fprintf(fp, "=====================================================================\n");
    fprintf(fp, "%-5s %-20s %-20s %-10s %-10s\n", "No.", "Product", "Store", "Qty", "Total");
    fprintf(fp, "---------------------------------------------------------------------\n");

    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%-5d %-20.20s %-20.20s %-10d PHP %-10.2f\n",
                i + 1,
                items[i].productName,
                items[i].storeName,
                items[i].quantity,
                items[i].total);
    }

    fprintf(fp, "=====================================================================\n");
    fprintf(fp, "%-20s PHP %.2f\n", "Starting Cash:", startingCash);
    fprintf(fp, "%-20s PHP %.2f\n", "Change:", change);
    fprintf(fp, "=====================================================================\n");
    fclose(fp);
}

// RELOAD PRODUCTS
void reloadProducts(Store stores[],int *storeCount){
    FILE *fp=fopen("products.txt","r");

    if(fp==NULL){
        printf("\nproducts.txt not found!\n");
        return;
    }

    *storeCount=0; 
    char line[200];
    int currentStore=-1;

    while(fgets(line,sizeof(line),fp)){
        line[strcspn(line,"\n")]='\0';

        if(strlen(line)==0){
            continue;
        }

        if(strstr(line,"=====")){
            currentStore++;
            (*storeCount)++;
            stores[currentStore].productCount=0;
            sscanf(line,
                    "===== %[^=] =====",
                    stores[currentStore].storeName);
            
            int len = strlen(stores[currentStore].storeName);
            while(len > 0 && stores[currentStore].storeName[len-1] == ' ') {
                stores[currentStore].storeName[len-1] = '\0';
                len--;
            }
            continue;
        }

        Product temp;
        if(sscanf(line,
                "%d | %[^|] | PHP %f | Stock: %d",
                &temp.id,
                temp.name,
                &temp.price,
                &temp.stock)==4){

            int len = strlen(temp.name);
            while(len > 0 && temp.name[len-1] == ' ') {
                temp.name[len-1] = '\0';
                len--;
            }

            stores[currentStore].products[stores[currentStore].productCount++] = temp;
        }
    }
    fclose(fp);
}

int main() {
    Store stores[MAX_STORES];
    int storeCount=0;

    reloadProducts(stores,&storeCount);

    float cash=loadCash();
    float startingCash;
    char extra = '\0';

    system("cls");
    cash=loadCash();
    startingCash=cash;
    Cart cart[MAX_CART];
    int cartSize=0;
    float finalTotal=0;

    char again='y';
    char cancelAgain='n';

    SHOPPING:
    system("cls");
    
    reloadProducts(stores,&storeCount);

    do{
        int storeChoice;
        while(1){
            reloadProducts(stores,&storeCount);
            cash=loadCash();

            printf("===============================================================\n");
            printf("                     VENDING MACHINE\n");
            printf("===============================================================\n");
            printf("\nRemaining Cash: PHP %.2f\n",cash);
            printf("\nAVAILABLE STORES\n");

            for(int i=0;i<storeCount;i++){
                printf("%d. %s\n",i+1,stores[i].storeName);
            }

            printf("0. View Inventory\n");
            printf("-1. Exit Program (Done Transaction)\n");

            printf("\nChoose Menu Option: ");
            if(scanf("%d%c",&storeChoice,&extra)!=2 || extra!='\n'){
                while(getchar()!='\n');
                system("cls");
                printf("Invalid Input! Numbers Only.\n");
                continue;
            }

            if(storeChoice==-1){
                system("cls");
                if(cartSize==0){
                    printf("No Products Purchased!\n");
                    return 0;
                }
                goto RECEIPT;
            }

            if(storeChoice==0){
                system("cls");
                
                // Dynamically read inventory.txt at this exact frame execution
                InventoryItem runtimeItems[MAX_INVENTORY_ITEMS];
                int runtimeCount = runtimeLoadInventoryFile(runtimeItems);

                if(runtimeCount == 0){
                    printf("No Inventory Records Found (File Empty or Deleted Manually)!\n\n");
                }else{
                    printf("=====================================================================\n");
                    // CHANGED: Screen display title text updated to "INVENTORY"
                    printf("                            INVENTORY\n");
                    printf("=====================================================================\n");
                    printf("%-5s %-20s %-20s %-10s %-10s\n",
                            "No.",
                            "Product",
                            "Store",
                            "Qty",
                            "Total");
                    printf("---------------------------------------------------------------------\n");
                    for(int i=0; i<runtimeCount; i++){
                        printf("%-5d %-20.20s %-20.20s %-10d PHP %-10.2f\n",
                                i+1,
                                runtimeItems[i].productName,
                                runtimeItems[i].storeName,
                                runtimeItems[i].quantity,
                                runtimeItems[i].total);
                    }
                    printf("=====================================================================\n");
                }

                int historyChoice;
                while(1){
                    printf("\n0. Return to Main Menu\n");
                    printf("\nChoose Option: ");
        
                    if(scanf("%d%c",&historyChoice,&extra)!=2 || extra!='\n'){
                        while(getchar()!='\n');
                        system("cls");
                        printf("Invalid Input! Numbers Only.\n");
                        continue;
                    }
                    if(historyChoice==0){
                        system("cls");
                        break;
                    }
                    system("cls");
                    printf("Invalid Choice!\n");
                }
                continue;
            }
            if(storeChoice>=1 && storeChoice<=storeCount){
                break;
            }
            system("cls");
            printf("Invalid Store Choice!\n");
        }

        storeChoice--;
        int productChoice;
        int quantity;
        int productIndex;
        int goBack=0;

        system("cls");
        while(1){
            reloadProducts(stores,&storeCount);
            cash=loadCash();

            printf("\nRemaining Cash: PHP %.2f\n",cash);
            displayProducts(stores,storeChoice);
            printf("\nChoose Product ID: ");

            if(scanf("%d%c",&productChoice,&extra)!=2 || extra!='\n'){
                while(getchar()!='\n');
                system("cls");
                printf("Invalid Input! Numbers Only.\n");
                continue;
            }

            if(productChoice==0){
                goBack=1;
                system("cls");
                break;
            }

            productIndex=findProduct(stores,
                                    storeChoice,
                                    productChoice);

            if(productIndex==-1){
                system("cls");
                printf("Invalid Product ID!\n");
                continue;
            }

            if(stores[storeChoice].products[productIndex].stock==0){
                system("cls");
                printf("Product Out Of Stock!\n");
                continue;
            }

            while(1){
                printf("\nSelected Product: %s\n", stores[storeChoice].products[productIndex].name);
                printf("Enter Quantity: ");

                if(scanf("%d%c",&quantity,&extra)!=2 || extra!='\n'){
                    while(getchar()!='\n');
                    system("cls");
                    printf("Invalid Input! Numbers Only.\n");
                    printf("\nRemaining Cash: PHP %.2f\n",cash);
                    displayProducts(stores,storeChoice);
                    continue;
                }
                if(quantity<=0){
                    system("cls");
                    printf("Invalid Quantity!\n");
                    printf("\nRemaining Cash: PHP %.2f\n",cash);
                    displayProducts(stores,storeChoice);
                    continue;
                }

                reloadProducts(stores,&storeCount);

                if(quantity > stores[storeChoice].products[productIndex].stock){
                    system("cls");
                    printf("Not Enough Stock!\n");
                    printf("\nAvailable Stock: %d\n", stores[storeChoice].products[productIndex].stock);
                    printf("\nRemaining Cash: PHP %.2f\n",cash);
                    displayProducts(stores,storeChoice);
                    continue;
                }
                break;
            }

            float total = stores[storeChoice].products[productIndex].price * quantity;
            cash=loadCash();

            if(total>cash){
                system("cls");
                printf("Not Enough Remaining Cash!\n");
                continue;
            }

            cash-=total;
            saveCash(cash);
            finalTotal+=total;

            stores[storeChoice].products[productIndex].stock -= quantity;
            saveProducts(stores,storeCount);

            // Maintain local cart storage for receipts / cancellations
            int duplicate=-1;
            for(int i=0;i<cartSize;i++){
                if(strcmp(cart[i].productName, stores[storeChoice].products[productIndex].name)==0 &&
                    strcmp(cart[i].storeName, stores[storeChoice].storeName) == 0){
                    duplicate=i;
                    break;
                }
            }

            if(duplicate!=-1){
                cart[duplicate].quantity+=quantity;
                cart[duplicate].total+=total;
            }else{
                strcpy(cart[cartSize].storeName, stores[storeChoice].storeName);
                strcpy(cart[cartSize].productName, stores[storeChoice].products[productIndex].name);
                cart[cartSize].productID = stores[storeChoice].products[productIndex].id;
                cart[cartSize].quantity=quantity;
                cart[cartSize].price = stores[storeChoice].products[productIndex].price;
                cart[cartSize].total=total;
                cartSize++;
            }

            // Instantly merge live selections directly into current file logs
            mergeAndCommitProductToInventoryFile(stores[storeChoice].storeName, 
                                                stores[storeChoice].products[productIndex].name, 
                                                quantity, 
                                                total, 
                                                startingCash, 
                                                cash);

            printf("\nProduct Added Successfully!\n");
            printf("Updated Cash: PHP %.2f\n",cash);
            break;
        }

        if(goBack==1){
            system("cls");
            again='y';
            continue;
        }

        while(1){
            printf("\nBuy Again? (y/n): ");
            if(scanf(" %c",&again)!=1){
                while(getchar()!='\n');
                system("cls");
                printf("Invalid Choice!\n");
                continue;
            }

            while(getchar()!='\n');
            if(again=='y' || again=='Y' || again=='n' || again=='N'){
                system("cls");
                break;
            }
            system("cls");
            printf("Invalid Choice!\n");
        }
    }while(again=='y' || again=='Y');

    return 0;  
}
