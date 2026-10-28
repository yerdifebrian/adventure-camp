#include <stdio.h>
#include <stdlib.h>

#define N 5      /* jumlah jenis alat */
#define MAX 10   /* kapasitas riwayat */

const char *alat[N] = {"Tenda Kapasitas 4 Orang", "Sleeping Bag", "Kompor Portable", "Matras Camping", "Lampu Camping"};
const int harga[N] = {50000, 15000, 20000, 10000, 12000};

char rNama[MAX][50];
int rAlat[MAX], rJumlah[MAX], rLama[MAX];
long long rTotal[MAX];
int jml = 0;

void garis(char c) { for (int i = 0; i < 40; i++) putchar(c); putchar('\n'); }

int bacaInt(const char *teks, int min, int max) {
    int x, ok, c;
    while (1) {
        printf("%s", teks);
        ok = scanf("%d", &x);
        if (ok == EOF) exit(0);
        while ((c = getchar()) != '\n' && c != EOF);
        if (ok == 1 && x >= min && x <= max) return x;
        printf("Input tidak valid! Masukkan angka %d-%d.\n", min, max);
    }
}

int persenDiskon(int lama) {
    if (lama >= 5) return 15;
    if (lama >= 3) return 10;
    return 0;
}

void tampilDaftar(void) {
    garis('=');
    printf("No. Peralatan                 Harga/Hari\n");
    garis('-');
    for (int i = 0; i < N; i++)
        printf("%-3d %-25s Rp%d\n", i + 1, alat[i], harga[i]);
    garis('=');
}

int sewa(void) {
    char nama[50], yt;
    int pilih, jumlah, lama, p;
    long long sub, dis, total;

    if (jml >= MAX) { printf("Kapasitas transaksi penuh, transaksi baru ditolak.\n"); return 1; }

    printf("Nama penyewa : ");
    scanf(" %49[^\n]", nama);                       
    tampilDaftar();
    pilih  = bacaInt("Pilih peralatan [1-5] : ", 1, N) - 1;
    jumlah = bacaInt("Jumlah unit           : ", 1, 1000);
    lama   = bacaInt("Lama sewa (hari)      : ", 1, 1000);

    p = persenDiskon(lama);
    sub = (long long)harga[pilih] * jumlah * lama;
    dis = sub * p / 100;
    total = sub - dis;

    snprintf(rNama[jml], 50, "%s", nama);
    rAlat[jml] = pilih; rJumlah[jml] = jumlah; rLama[jml] = lama; rTotal[jml] = total;
    jml++;

    garis('=');
    printf("          ADVENTURE CAMP\n          STRUK PENYEWAAN\n");
    garis('=');
    printf("Nama Penyewa   : %s\nPeralatan      : %s\nHarga per Hari : Rp%d\n", nama, alat[pilih], harga[pilih]);
    printf("Jumlah Unit    : %d\nLama Sewa      : %d hari\n", jumlah, lama);
    garis('-');
    printf("Subtotal       : Rp%lld\nDiskon (%d%%)   : Rp%lld\n", sub, p, dis);
    garis('-');
    printf("TOTAL BAYAR    : Rp%lld\n", total);
    garis('=');
    printf("Terima kasih telah menggunakan\nlayanan Adventure Camp!\n\n");

    do {
        printf("Kembali ke menu utama? (Y/T): ");
        scanf(" %c", &yt);
    } while (yt != 'Y' && yt != 'y' && yt != 'T' && yt != 't');
    return (yt == 'Y' || yt == 'y');
}

void tampilRiwayat(void) {
    long long pendapatan = 0;
    garis('=');
    printf("        RIWAYAT TRANSAKSI\n");
    garis('=');
    if (jml == 0) { printf("Belum ada transaksi penyewaan.\n"); return; }
    printf("No  %-12s %-25s Total\n", "Nama", "Peralatan");
    garis('-');
    for (int i = 0; i < jml; i++) {
        printf("%-3d %-12s %-25s Rp%lld\n", i + 1, rNama[i], alat[rAlat[i]], rTotal[i]);
        pendapatan += rTotal[i];
    }
    garis('-');
    printf("Jumlah Transaksi : %d\nTotal Pendapatan : Rp%lld\n", jml, pendapatan);
    garis('=');
}

int main(void) {
    int jalan = 1;
    while (jalan) {
        garis('=');
        printf("          ADVENTURE CAMP\n     SISTEM PENYEWAAN PERALATAN\n");
        garis('=');
        printf("1. Lihat Daftar Peralatan\n2. Sewa Peralatan\n3. Lihat Riwayat Transaksi\n4. Keluar\n");
        garis('=');
        switch (bacaInt("Pilih menu [1-4]: ", 1, 4)) {
            case 1: tampilDaftar();   break;
            case 2: jalan = sewa();   break;
            case 3: tampilRiwayat();  break;
            case 4: jalan = 0;        break;
        }
    }
    printf("\nTerima kasih telah menggunakan layanan Adventure Camp!\n");
    return 0;
}
