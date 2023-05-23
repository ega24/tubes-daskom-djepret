// // // program tubes daskom djepret
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// buat variabel untuk roleplay sebagai admin(1)/pelanggan(2)
int mode;

struct Paket{
    char nama[100];
    int harga;
} paket[]; int jumlahPaket = 0;
// int jumlahPaket = sizeof(paket)/sizeof(paket[0]);

struct Pelanggan{
    char username[100];
    char password[100];
    char nama[100];
    int jumlahOrang;
    int bayar;
} pelanggan[]; int jumlahPelanggan = 0;

// fitur umum
void daftarFungsi(int);
int  gantiMode(int);
void login();
void pilihMenu();

// fitur admin;
void bikinFile();
void cariJadwal();
void editPaket();
void editStok();
void hapusPaket();
void lihatJadwal();
void lihatPaket();
void lihatStok();
void lihatIncome(int);
void tambahPaket();

// fitur pelanggan
void inputJadwal();

int main(){
  
    login(); 

    // printf("%d\n", mode);


    return 0;
}

void bikinFile(){
    // file pointer
    FILE *fptr;

    // ngebuka file
    fptr = fopen("data djepret.dat", "w");

    // ngecek filenya udah kebuat/kebuka
    if(fptr == NULL){
        printf("filenya gabisa kebuka\n");
        exit(0);
    } else{
        printf("filenya udah kebuat\n");
    }
}

void daftarFungsi(int mode){
    if(mode == 1){// admin
        printf("1. buat file\n");
        printf("2. buat file\n");
    }else if(mode == 2){ // pelanggan
        // pass
    }
    pilihMenu();
}

int gantiMode(int ganti){
    mode = ganti;
    return mode;
}

void login(){
    // variabel untuk menampung proses login
    char usernameInput[50], psswdInput[50];

    // // proses login
    // jumlah kesempatan dan kondisi berhasil
    int kesempatan = 3; 
    bool berhasil = false;

    // buat variabel untuk roleplay sebagai admin(1)/pelanggan(2)
    int mode;

    // looping login
    while(kesempatan >0 && berhasil==false){
        // masukan username dan password
        printf("masukan username : ");
        gets(usernameInput);
        printf("masukan password : ");
        gets(psswdInput);
        // getchar();
        printf("\n");

        // pengecekan username dan password
        if((strcmp(usernameInput, "admin")==0) && (strcmp(psswdInput, "admin")==0)){
            printf("login menjadi admin berhasil\n\n");
            berhasil = true; gantiMode(1);
        } else if((strcmp(usernameInput, "user")==0) && (strcmp(psswdInput, "user")==0)){
            printf("login menjadi pelanggan berhasil\n\n");
            berhasil = true; gantiMode(2);
        } else{
            // setiap login gagal maka jumlah kesempatan berkurang
            kesempatan--;
        }
    }
}

void pilihMenu(){
    int pilih;

    printf("pilih menu : ");
    scanf("%d", &pilih);

    if(mode == 1){
        switch (pilih){
            case 1:
                bikinFile();
                break;
            default:
                printf("maaf, pilihan kamu gaada di menu\n");
                break;
        }
    }else if(mode == 2){
        switch (pilih){
            case 1:
                // bikinFile();
                break;
            default:
                printf("maaf, pilihan kamu gaada di menu\n");
                break;
        }
    }else{
        printf("maaf kamu belum login\n"); 
    }
}



