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

int main() {




  return 0;  
}
