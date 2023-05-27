// // // program tubes daskom djepret
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// buat variabel untuk roleplay sebagai admin(1)/pelanggan(2)
int mode = 0;
// int modePtr = *mode;
int totalIncome = 0;

// variabel untuk menampung indeks pelanggan dan pesanan
int indexPelanggan = -1;
int indexPesanan = -1;

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
    int jumlahPesan;
    int indeksPesanan[100];
} pelanggan[]; int jumlahPelanggan = 0;

struct Pesanan{
    char nama[100];
    char alamat[100];
    int jumlahOrang;
    char paket[100];
    char frame[100];
    int totalBayar;
    int jadwalFoto;
} pesanan[]; int jumlahPesanan = 0;

void bacaDataPelanggan(struct Pelanggan *, int *);
void bayar(int);
void bikinFile();
void cekSaldo(int);
void daftarFungsi(int);
int  gantiMode(int);
void hapusPaket();
void inputJadwal();
void jadwalTersedia();
int  kurangStokFrame(char *);
void lihatPaket();
void lihatIncome(int);
void login();
void pesenPesanan(int);
int  pilihJadwal(int);
void pilihMenu();
void regisPelanggan();
void simpanDataPelanggan(struct Pelanggan *, int);
int  tagihan(int);
void tambahPaket();
void tambahFrame();
void topUpWallet(int);
void updateHargaPaket();
void updateJadwal(int);
void updateJumlahOrangPaket();
void updateStokFrame();

int main(){
    // system("cls");
    bikinFile();
    
    bool keluar = false;

    // regisPelanggan();
    // login();
    
    while(keluar != true){
        system("cls");    
        daftarFungsi(mode);
        system("pause");
    }
    // updateJadwal(pilihJadwal());
    
    return 0;
}

void bacaDataPelanggan(struct Pelanggan pelanggan[], int *jumlahPelanggan) {
    FILE *fptr;
    fptr = fopen("data_pelanggan.dat", "rb");
    if (fptr == NULL) {
        printf("Gagal membuka file data_pelanggan.dat\n");
        return;
    }

    fread(jumlahPelanggan, sizeof(int), 1, fptr);
    fread(pelanggan, sizeof(struct Pelanggan), *jumlahPelanggan, fptr);

    fclose(fptr);
}

void bayar(int indeks){
    if(pelanggan[indeks].wallet < tagihan(indeks)){
        printf("maaf, saldo kamu tidak cukup\n\n");
    } else{
        pelanggan[indeks].wallet -= tagihan(indeks);
        
        for(int i = 0; i < pelanggan[indeks].jumlahPesan; i++){
            for(int j = pelanggan[indeks].indeksPesanan[i]; j < jumlahPesanan; j++){
                pesanan[j] = pesanan[j+1];
            }

            jumlahPesanan--;
        }
    }
}

void bikinFile(){
    // file pointer
    FILE *fptr;

    // ngebuka file
    fptr = fopen("data_pelanggan.dat", "w");

    // ngecek filenya udah kebuat/kebuka
    if(fptr == NULL){
        printf("filenya gabisa kebuka\n");
        // exit(0);
    } else{
        printf("filenya udah kebuat\n");
    }

    fclose(fptr);
}

void cekSaldo(int indeks){
    printf("saldo kamu : ");
    printf("%d\n\n", pelanggan[indeks].wallet);
}

void daftarFungsi(int mode){
    if(mode == 1){// admin
        printf("1. lihat paket studio\n");
        printf("2. buat paket stduio\n");
        printf("3. hapus paket studio\n");
        printf("4. update harga paket studio\n");
        printf("5. update jumlah orang paket studio\n");
        printf("6. lihat stok frame\n");
        printf("7. tambah frame\n");
        printf("8. update stok frame\n");
        printf("99. logout\n");
        printf("999. stop program\n\n");
        // pass
    }else if(mode == 2){ // pelanggan
        printf("1. lihat paket studio\n");
        printf("2. pesan paket\n");
        printf("3. lihat saldo\n");
        printf("4. topup saldo\n");
        printf("5. bayar\n");
        printf("99. logout\n");
        printf("999. stop program\n\n");
        // pass
    }else{
        printf("1. regsitrasi\n");
        printf("2. login\n");
        printf("999. stop program\n\n");
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

    getchar();

    // input paket yang akan dicari
    printf("masukan nama paket : ");
    gets(namaPaket); getchar();

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

int  kurangStokFrame(char namaFrame[]){
    int indexFrame = -1;

    getchar();

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
        return 0;
    }

    // update stok 
    frame[indexFrame].stok--;

    return frame[indexFrame].harga;
}

void lihatStokFrame(){
    // pengecekan ketersediaan frame
    if(jumlahFrame == 0){
        printf("belum ada frame\n\n");
    }else{
        printf("\ndaftar frame :\n");
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

        printf("\n");
    }
}

void login(){
    // variabel untuk menampung proses login
    char usernameInput[50], psswdInput[50];

    // // proses login
    // jumlah kesempatan dan kondisi berhasil
    int kesempatan = 3; 
    bool berhasil = false;

    bacaDataPelanggan(pelanggan, &jumlahPelanggan);

    getchar();

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
            for (int i = 0; i < jumlahPelanggan; i++) {
                if (strcmp(usernameInput, pelanggan[i].username) == 0 && strcmp(psswdInput, pelanggan[i].password) == 0) {
                    indexPelanggan = i;
                    break;
                }
            }

            // tampilkan pesan berhasil
            if (indexPelanggan != -1) {
                printf("Berhasil login sebagai %s\n", pelanggan[indexPelanggan].nama);
            }

            // setiap login gagal maka jumlah kesempatan berkurang
            kesempatan--;
        }
    }
}

void pesenPesanan(int indeks){
    // tampilkan daftar paket
    lihatPaket();

    getchar();

    // masukan paket
    printf("masukan nama paket : ");
    gets(pesanan[jumlahPesanan].nama);

    int indexPaket;

    // mencari paket
    for(int i = 0; i < jumlahPaket; i++){
        if(strcmp(pesanan[jumlahPesanan].nama, paket[i].nama) == 0){
            
            indexPaket = i;
            indexPesanan = jumlahPesanan;
            break;
        }
    }

    // pesan apabila paket tidak ditemukan
    if(indexPaket == -1){
        printf("paket tidak ditemukan\n\n");
        return;
    }

    printf("masukan nama pemesan : ");
    gets(pesanan[indexPesanan].nama);
    printf("masukan alamat : ");
    gets(pesanan[indexPesanan].alamat);
    printf("masukan jumlah orang : "); // getchar();
    scanf("%d", &pesanan[indexPesanan].jumlahOrang);

    // perlihatkan jadwal
    jadwalTersedia();

    printf("pilih jadwal foto : ");
    scanf("%d", &pesanan[indexPesanan].jadwalFoto); getchar();

    // update jadwal
    updateJadwal(pilihJadwal(pesanan[indexPesanan].jadwalFoto));

    // perlihatkan frame
    lihatStokFrame();

    printf("pilih frame foto : ");
    gets(pesanan[indexPesanan].frame);

    // hitung total biaya dan update stok frame
    pesanan[indexPesanan].totalBayar = paket[indexPaket].harga + kurangStokFrame(pesanan[indexPesanan].frame);

    // update total
    totalIncome += pesanan[indexPesanan].totalBayar;

    // simpan pesanan
    pelanggan[indeks].indeksPesanan[pelanggan[indeks].jumlahPesan] = indexPesanan;

    // update jumlah pesanan
    jumlahPesanan++;

    printf("pesanan berhasil\n\n");
}

int  pilihJadwal(int indeksJadwal){
    // int indeksJadwal;
    // printf("masukan jadwal yang diinginkan : ");
    // scanf("%d", &indeksJadwal);

    if(indeksJadwal<0 || indeksJadwal>jadwalFoto){
        printf("jadwal tidak ditemukan\n\n");
        return 0;
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
                tambahFrame();
                break;
            case 8:
                updateStokFrame();
                break;
            case 99:
                gantiMode(0);
                break;
            case 999:
                exit(0);
            default:
                printf("maaf, pilihan kamu gaada di menu\n\n");
                break;
        }
    }else if(mode == 2){
        switch (pilih){
            case 1:
                lihatPaket();
                break;
            case 2:
                pesenPesanan(indexPelanggan);
                break;
            case 3:
                cekSaldo(indexPelanggan);
                break;
            case 4:
                topUpWallet(indexPelanggan);
                break;
            case 5:
                tagihan(indexPelanggan);
                bayar(indexPelanggan);
                break;
            case 99:
                gantiMode(0);
                // login();
                break;
            case 999:
                exit(0);
            default:
                printf("maaf, pilihan kamu gaada di menu\n\n");
                break;
        }
    }else{
        switch (pilih){
            case 1:
                regisPelanggan();
                break;
            case 2:
                login();
                break;
            case 999:
                exit(0);
            default:
                printf("maaf, pilihan kamu gaada di menu\n\n");
                break;
        }
        // printf("maaf kamu belum login\n"); 
    }
}

void regisPelanggan(){
    // char userPelanggan[100];

    bacaDataPelanggan(pelanggan, &jumlahPelanggan);
    
    getchar();
    
    // Input data pelanggan baru
    printf("masukan username: ");
    scanf("%s", pelanggan[jumlahPelanggan].username);
    printf("masukan password: ");
    scanf("%s", pelanggan[jumlahPelanggan].password);
    printf("masukan nama: ");
    scanf("%s", pelanggan[jumlahPelanggan].nama);
    printf("masukan jumlah orang: ");
    scanf("%d", &pelanggan[jumlahPelanggan].jumlahOrang);
    pelanggan[jumlahPelanggan].bayar = 0;
    pelanggan[jumlahPelanggan].wallet = 0;
    pelanggan[jumlahPelanggan].jumlahPesan = 0;

    // update jumlah pelanggan 
    jumlahPelanggan++;

    // Simpan data pelanggan ke file
    simpanDataPelanggan(pelanggan, jumlahPelanggan);

    printf("registrasi berhasil!\n\n");
}

void simpanDataPelanggan(struct Pelanggan pelanggan[], int jumlahPelanggan) {
    FILE *fptr;
    fptr = fopen("data_pelanggan.dat", "wb");
    if (fptr == NULL) {
        printf("Gagal membuka file data_pelanggan.dat\n");
        return;
    }

    fwrite(&jumlahPelanggan, sizeof(int), 1, fptr);
    fwrite(pelanggan, sizeof(struct Pelanggan), jumlahPelanggan, fptr);

    fclose(fptr);
}

int  tagihan(int indeks){
    int totalTagihan = 0;

    for(int i = 0; i < pelanggan[indeks].jumlahPesan; i++){
        totalTagihan += pesanan[pelanggan[indeks].indeksPesanan[i]].totalBayar;
    }

    printf("total tagihan kamu : %d\n\n", totalTagihan);

    // printf("saldo kamu : ");
    cekSaldo(indeks);

    return totalTagihan;
}

void tambahFrame(){
    getchar();

    // input nama, harga dan stok frame
    printf("nama frame  : ");
    gets(frame[jumlahFrame].nama);
    printf("harga frame : ");
    scanf("%d", &frame[jumlahFrame].harga);
    printf("stok frame : ");
    scanf("%d", &frame[jumlahFrame].stok);

    // update jumlah frame
    jumlahFrame++;

    printf("frame telah ditambahkan!\n\n");
}

void tambahPaket(){
    getchar();

    // input nama dan harga paket
    printf("nama paket  : ");
    gets(paket[jumlahPaket].nama);
    printf("harga paket : ");
    scanf("%d", &paket[jumlahPaket].harga);

    // update jumlah paket
    jumlahPaket++;

    printf("paket telah ditambahkan!\n\n");
}

void topUpWallet(int indeks){
    // variabel untuk menampung jumlah topup
    int jumlahTopup;

    printf("masukan jumlah topup : ");
    scanf("%d", &jumlahTopup);

    // update jumlah uang 
    pelanggan[indeks].wallet += jumlahTopup;

    printf("topup berhasil\n\n");
}

void updateHargaPaket(){
    char namaPaket[100];
    int indexPaket = -1;

    getchar();

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
