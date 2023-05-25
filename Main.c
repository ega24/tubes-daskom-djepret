// // // program tubes daskom djepret
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// buat variabel untuk roleplay sebagai admin(1)/pelanggan(2)
int mode;

// variabel untuk menampung indeks pelanggan
int indexPelanggan = -1;

struct Frame{
    char nama[100];
    int harga;
    int stok;
} frame[]; int jumlahFrame = 0;

struct Paket{
    char nama[100];
    int harga;
    int stok;
    int jumlahOrang;
} paket[]; int jumlahPaket = 0;
// int jumlahPaket = sizeof(paket)/sizeof(paket[0]);

struct Fotografer{
    int jam;
    char hari[100];
} fotografer[5] = {
    {2, "senin"}, {4, "senin"}, {4, "rabu"}, {2, "kamis"}, {2, "jumat"}
}; int jadwalFoto = 5;

struct Pelanggan{
    char username[100];
    char password[100];
    char nama[100];
    int jumlahOrang;
    int bayar;
    int wallet;
} pelanggan[]; int jumlahPelanggan = 0;

// fitur umum
void daftarFungsi(int);
int  gantiMode(int);
void login();
void pilihMenu();

// fitur admin;
void bikinFile();
void hapusPaket();
void jadwalTersedia();
void lihatJadwal();
void lihatPaket();
void lihatIncome(int);
int  pilihJadwal();
void tambahPaket();
void tambahFrame();
void updateHargaPaket();
void updateJadwal(int);
void updateJumlahOrangPaket();
void updateStokFrame();

// fitur pelanggan
void inputJadwal();
void regisPelanggan();
void topUpWallet();

int main(){
    
    bool keluar = false;

    login();
    
    while(keluar != true){
        daftarFungsi(mode);
        pilihMenu();
    }
    // updateJadwal(pilihJadwal());
    
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
        // exit(0);
    } else{
        printf("filenya udah kebuat\n");
    }
}

void daftarFungsi(int mode){
    if(mode == 1){// admin
        printf("1. lihat paket studio\n");
        printf("2. buat paket stduio\n");
        printf("3. hapus paket studio\n");
        printf("4. update harga paket studio\n");
        printf("5. update jumlah orang paket studio\n");
        printf("6. lihat stok frame\n");
        printf("7. update stok frame\n");
        printf("99. logout\n");
        printf("999. stop program\n\n");
        // pass
    }else if(mode == 2){ // pelanggan
        // pass
    }
    pilihMenu();
}

int  gantiMode(int ganti){
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

void jadwalTersedia(){
    if(jadwalFoto == 0){
        printf("tidak ada jadwal kosong\n\n");
    }else{
        printf("\njadwal kosong :\n");
        for (int i = 0; i < jadwalFoto; i++){
            printf("%d. ", i+1);
            printf("Hari : %s\n", fotografer[i].hari);
            printf("   Jam : %d\n", fotografer[i].jam);
        }
    }
}

void lihatStokFrame(){
    // pengecekan ketersediaan frame
    if(jumlahFrame == 0){
        printf("belum ada paket\n\n");
    }else{
        printf("\ndaftar paket :\n");
        for (int i = 0; i < jumlahFrame; i++){
            printf("%d. ", i+1);
            printf("Nama : %s\n", frame[i].nama);
            printf("   Harga : %d\n", frame[i].harga);
            printf("   Stok : %d\n", frame[i].stok);
        }
    }
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

int  pilihJadwal(){
    int indeksJadwal;
    printf("masukan jadwal yang diinginkan : ");
    scanf("%d", &indeksJadwal);

    if(indeksJadwal<0 || indeksJadwal>jadwalFoto){
        printf("jadwal tidak ditemukan\n\n");
        return;
    }

    return indeksJadwal;
}

void pilihMenu(){
    int pilih;

    printf("pilih menu : ");
    scanf("%d", &pilih);

    if(mode == 1){
        switch (pilih){
            case 1:
                lihatPaket();
                break;
            case 2:
                tambahPaket();
                break;
            case 3:
                hapusPaket();
                break;
            case 4:
                updateHargaPaket();
                break;
            case 5:
                updateJumlahOrangPaket();
                break;
            case 6: 
                lihatStokFrame();
                break;
            case 7:
                updateStokFrame();
            case 99:
                login();
            case 999:
                exit(0);
            default:
                printf("maaf, pilihan kamu gaada di menu\n\n");
                break;
        }
    }else if(mode == 2){
        switch (pilih){
            case 1:
                // bikinFile();
                break;
            default:
                printf("maaf, pilihan kamu gaada di menu\n\n");
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

void tambahFrame(){
    // input nama, harga dan stok frame
    printf("nama paket  : ");
    gets(paket[jumlahPaket].nama);
    printf("harga paket : ");
    scanf("%d", &paket[jumlahPaket].harga);
    printf("stok paket : ");
    scanf("%d", &paket[jumlahPaket].stok);

    // update jumlah frame
    jumlahFrame++;

    printf("frame telah ditambahkan!\n\n");
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

void topUpWallet(){
    // variabel untuk menampung jumlah topup
    int jumlahTopup;

    printf("masukan jumlah topup : ");
    scanf("%d", &jumlahTopup);

    // update jumlah uang 
    pelanggan[indexPelanggan].wallet += jumlahTopup;

    printf("topup berhasil\n\n");
}

void updateHargaPaket(){
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

    // masukan harga paket yang baru
    printf("masukan harga paket : ");
    scanf("%d", &paket[indexPaket].harga);

    printf("harga paket telah diupdate!\n\n");
}

void updateJadwal(int indeks){
    // update urutan paket
    for(int i = indeks; i < jadwalFoto-1; i++){
        fotografer[i] = fotografer[i+1];
    }

    // update sisa jadwal
    jadwalFoto--;

    printf("jadwal telah dipilih\n\n");
}

void updateJumlahOrangPaket(){
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

void updateStokFrame(){
    char namaFrame[100];
    int indexFrame = -1;

    // input paket yang akan dicari
    printf("masukan nama paket : ");
    gets(namaFrame);

    // mencari paket
    for(int i = 0; i < jumlahPaket; i++){
        if(strcmp(namaFrame,frame[i].nama) == 0){
            indexFrame = i;
            break;
        }
    }

    // pesan apabila paket tidak ditemukan
    if(indexFrame == -1){
        printf("paket tidak ditemukan\n\n");
        return;
    }

    // masukan stok paket yang baru
    printf("masukan stok paket : ");
    scanf("%d", &frame[indexFrame].stok);

    printf("stok frame telah diupdate!\n\n");
}
