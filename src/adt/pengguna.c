#include <stdio.h>
#include "pengguna.h"
#include "../feat/operational.c"

void daftar() {
    Word temp;
    Word passWord;

    if (user.db[0].status == true) {
        printf("Anda sudah masuk. Keluar terlebih dahulu untuk melakukan daftar.\n");
        return;
    }

    // Mengecek apakah nama sudah ada
    printf("Masukkan nama:\n"); 
    temp = baca();
    while (temp.Length > 20) {
        printf("Nama terlalu panjang.\n");{
            for (int i = 0; i < jumlah_pengguna; i++) {
                if (cek(temp, user.db[i].nama.TabWord)) {
                printf("Wah, sayang sekali nama tersebut telah diambil.\n");
                return;
                }
            }

            printf("Masukkan kata sandi:\n"); 

            // Mendaftarkan pengguna baru
            strcpy(user.db[jumlah_pengguna].nama.TabWord, currentWord.TabWord); //nunggu fungsi masukin ke config
            strcpy(user.db[jumlah_pengguna].pass.TabWord, passWord.TabWord); //nunggu fungsi masukin data ke config
            jumlah_pengguna++;

            // Menulis data ke file config
            FILE *fp = fopen("cfg/pengguna.config", "a");
            fprintf(fp, "%s,%s\n", user.db[jumlah_pengguna - 1].nama.TabWord, user.db[jumlah_pengguna - 1].pass.TabWord);
            fclose(fp);

            printf("Pengguna telah berhasil terdaftar. Masuk untuk menikmati fitur-fitur BurBir.\n");
            return;
        }

        CopyWord();
    }
}


void masuk() {
    Word tempnama;
    Word temppass;
    // Mengecek apakah pengguna sudah login
    if (user.db[0].status == true) {
        printf("Wah Anda sudah masuk. Keluar dulu yuk!\n");
        return;
    }

    // Tidak ada pengguna aktif
    printf("Anda belum login. Silakan login terlebih dahulu.\n");

    // memasukkan nama dan kata sandi
    char nama[20], pass[20];
    printf("Masukkan nama: ");
    tempnama = baca();
    printf("Masukkan kata sandi: ");
    temppass = baca();

    // Mencari pengguna dengan nama dan kata sandi sesuai yang diinput
    int found = 0; // boolean untuk menandai jika pengguna ditemukan
    for (int i = 0; i < jumlah_pengguna; i++) {
        if (cek(tempnama, user.db[i].nama.TabWord)) {
            if (cek(temppass, user.db[i].pass.TabWord)) {
                // Pengguna ditemukan
                user.db[i].status = 1;
                printf("Anda telah berhasil masuk dengan nama pengguna %s. Mari menjelajahi BurBir bersama Ande-Ande Lumut!\n", nama);
                return;
            } else {
                // Kata sandi tidak cocok
                printf("Wah, kata sandi yang Anda masukkan belum tepat. Periksa kembali kata sandi Anda!\n");
                return;
            }
                found = 1; //pengguna ditemukan
            }
        }

    // Pengguna tidak ditemukan
    if (!found) {
        printf("Wah, nama yang Anda cari tidak ada. Masukkan nama lain!\n");
    }

}

void keluar() {
    // Mengecek apakah pengguna sudah login
    if (user.db[0].status == false) {
        printf("Anda belum login! Masuk terlebih dahulu untuk menikmati layanan BurBir.\n");
        return;
    }

    // Mengubah status login pengguna menjadi 0
    user.db[0].status = false;
    printf("Anda berhasil logout. Sampai jumpa di pertemuan berikutnya!\n");
}




