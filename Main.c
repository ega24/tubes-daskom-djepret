// // // program tubes daskom djepret
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// buat variabel untuk roleplay sebagai admin(1)/pelanggan(2)
int mode;

// variabel untuk menampung indeks pelanggan
int indexPelanggan = -1;

struct Paket{
    char nama[100];
    int harga;
    int stok;
    int jumlahOrang;
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
void editJumlahOrangPaket();
void editStokPaket();
void hapusPaket();
void lihatJadwal();
void lihatPaket();
void lihatStok();
void lihatIncome(int);
void tambahPaket();

// fitur pelanggan
void inputJadwal();
void regisPelanggan();

int main(){
    
    login(); 
    printf("mode : %d\n", mode);
    printf("indeks pelanggan : %d\n", indexPelanggan);

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

void editJumlahOrangPaket(){
    char namaPaket[100];
    int indexPaket = -1;

    // input paket yang akan dicari
    printf("masukan nama paket : ");
    gets(namaPaket);

    // mencari paket
    for(int i = 0; i < jumlahPaket; i++){
        if(strcmp(namaPaket,paket[i].nama) == 0){
            indexPaket = i;
            break;
        }
    }

    // pesan apabila paket tidak ditemukan
    if(indexPaket == -1){
        printf("paket tidak ditemukan\n\n");
        return;
    }

    // masukan jumlah orang dalam paket yang baru
    printf("masukan jumlah orang : ");
    scanf("%d", &paket[indexPaket].jumlahOrang);

    printf("jumlah orang telah diupdate!\n\n");
}

void editStokPaket(){
    char namaPaket[100];
    int indexPaket = -1;

    // input paket yang akan dicari
    printf("masukan nama paket : ");
    gets(namaPaket);

    // mencari paket
    for(int i = 0; i < jumlahPaket; i++){
        if(strcmp(namaPaket,paket[i].nama) == 0){
            indexPaket = i;
            break;
        }
    }

    // pesan apabila paket tidak ditemukan
    if(indexPaket == -1){
        printf("paket tidak ditemukan\n\n");
        return;
    }

    // masukan stok paket yang baru
    printf("masukan stok paket : ");
    scanf("%d", &paket[indexPaket].stok);

    printf("stok paket telah diupdate!\n\n");
}

int gantiMode(int ganti){
    mode = ganti;
    return mode;
}

void hapusPaket(){
    char namaPaket[100];
    int indexPaket = -1;

    // input paket yang akan dicari
    printf("masukan nama paket : ");
    gets(namaPaket);

    // mencari paket
    for(int i = 0; i < jumlahPaket; i++){
        if(strcmp(namaPaket,paket[i].nama) == 0){
            indexPaket = i;
            break;
        }
    }

    // pesan apabila paket tidak ditemukan
    if(indexPaket == -1){
        printf("paket tidak ditemukan\n\n");
        return;
    }

    // update urutan paket
    for(int i = indexPaket; i < jumlahPaket -1; i++){
        paket[i] = paket[i+1];
    }

    // update jumlah paket
    jumlahPaket--;
}

void lihatPaket(){
    // pengecekan ketersediaan paket
    if(jumlahPaket == 0){
        printf("belum ada paket\n\n");
    }else{
        printf("\ndaftar paket :\n");
        for (int i = 0; i < jumlahPaket; i++){
            printf("%d. ", i+1);
            printf("Nama : %s\n", paket[i].nama);
            printf("   Harga : %d\n", paket[i].harga);
        }
    }
}

void login(){
    // variabel untuk menampung proses login
    char usernameInput[50], psswdInput[50];

    // // proses login
    // jumlah kesempatan dan kondisi berhasil
    int kesempatan = 3; 
    bool berhasil = false;

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
        } else{
            // mengecek username
            for(int i = 0; i < jumlahPelanggan; i++){
                if(strcmp(usernameInput, pelanggan[i].username) == 0){
                    if(strcmp(psswdInput, pelanggan[i].password) == 0){
                        printf("login menjadi pelanggan berhasil\n\n");
                        berhasil = true; gantiMode(2); 
                        indexPelanggan = i;
                        break;
                    }
                }
            }

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

void regisPelanggan(){
    char userPelanggan[100];
    
    // masukan username
    printf("masukan username : ");
    gets(userPelanggan);
    // gets(pelanggan[jumlahPelanggan].username);

    // mengecek username
    for(int i = 0; i < jumlahPelanggan; i++){
        if(strcmp(userPelanggan, pelanggan[i].username) == 0){
            printf("username telah terpakai\n\n");
            return;
        }
    }
    
    strcpy(pelanggan[jumlahPelanggan].username, userPelanggan);
    // pelanggan[jumlahPelanggan].username = userPelanggan;

    printf("masukan password : ");
    gets(pelanggan[jumlahPelanggan].password);

    // update jumlah pelanggan 
    jumlahPelanggan++;

    printf("registrasi berhasil!\n\n");
}

void tambahPaket(){
    // input nama dan harga paket
    printf("nama paket  : ");
    gets(paket[jumlahPaket].nama);
    printf("harga paket : ");
    scanf("%d", &paket[jumlahPaket].harga);

    // update jumlah paket
    jumlahPaket++;

    printf("paket telah ditambahkan!\n\n");
}

