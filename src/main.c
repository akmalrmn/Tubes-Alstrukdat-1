#include <stdio.h>
#include <stdlib.h>
#include "adt/pengguna.h"
#include "feat/io.h"
#include "feat/operational.h"
#include "feat/savenload.h"
#include "adt/kicauan.h"
#include "adt/pertemanan.h"
#include "adt/teman.h"
#include "adt/utas.h"
#include "adt/balasan.h"

int main() {
	Word opt, configfolder, currentUser;
	UserDB user;
	ListUtas utas;
	ListDinkicau kicauan;
	Graf teman;
	ListTreeBalasan balasan;
	int move;	
	FILE *fptr;
	int idkicau, indexParam;
	ListStack sl;
	prioqueuefren permintaanTeman;

	CreateListDinkicau(&kicauan, 1);
	CreateListDinStack(&sl, 20);

	printlogo();
	printf("\nSelamat datang di BurBir!\n");
	printf("Silahkan masukkan nama folder konfigurasi: ");
	configfolder = baca();
	Word location = concat("../cfg/", configfolder.TabWord);
	fptr = fopen(location.TabWord, "r");
	if (fptr == NULL) {
		printf("\nYah folder konfigurasi tidak ditemukan :(\n");
		return 0;
	}
	fclose(fptr);
	bacaconfig(&user, &utas, &kicauan, &teman, &permintaanTeman, &balasan , &sl, configfolder);
	printf("\nFile konfigurasi berhasil dimuat! Selamat menggunakan aplikasi BurBir!\n");
	printf("Ketik \';\' untuk melanjutkan\n\n");
	bacakalimat();

	emptyuser(&currentUser);
	
	boolean start = true;

	while (start) {
		printlogo();
		printf("\nMasukkan perintah");
		printf("\n>> ");
		opt = baca();
		move = pindahfungsi(opt); // cek realisasi fungsinya di operational.c untuk tau kode angkanya
		switch(move) {
			case 1:
				daftar(&user, &currentUser);
				break;
			case 2:
				masuk(&user, &currentUser);
				break;
			case 3:
				keluar(&currentUser);
				break;
			case 4:
				printf("\nAnda telah keluar dari program BurBir. Sampai jumpa di penjelajahan berikutnya.\n\n");
				start = false;
				break;
			case 5:
				if (belumlogin(currentUser)) {
					printf("\nAnda belum login. Silahkan login terlebih dahulu untuk mengganti profil.\n");
					break;
				}
				for (int a = 0; a < user.Neff; a++) {
					if(ceksama(currentUser, user.db[a].nama)) {
						gantiProfil(&user.db[a]);
						break;
					}
				}
			case 6:
				Word nama;
				boolean flag = false;
				if (belumlogin(currentUser)) {
					printf("\nAnda belum login. Silahkan login terlebih dahulu untuk melihat profil.\n");
					break;
				}				
				nama = bacakalimat();
				for (int a = 0; a < user.Neff; a++) {
					if(ceksama(currentUser, user.db[a].nama)) {
						for (int b = 0; b < user.Neff; b++) {
							if(ceksama(nama, user.db[b].nama)) {
								LihatProfil(user.db[a], user.db[b], &user, &teman);
								flag = true;
								break;
							}
						}
					}
				}
				if (!flag) {
					printf("\nTidak ada akun dengan nama ");
					PrintWord(nama);
					printf(".\n");
					break;
				}
			case 7:
				if (belumlogin(currentUser)) {
					printf("\nAnda belum login. Silahkan login terlebih dahulu untuk mengatur jenis akun.\n");
					break;
				}
				for (int a = 0; a < user.Neff; a++) {
					if(ceksama(currentUser, user.db[a].nama)) {
						aturJenisAkun(&user.db[a]);
						break;
					}
				}			
			case 8:
				if (belumlogin(currentUser)) {
					printf("\nAnda belum login. Silahkan login terlebih dahulu untuk mengubah foto profil.\n");
					break;
				}
				for (int a = 0; a < user.Neff; a++) {
					if(ceksama(currentUser, user.db[a].nama)) {
						ubahFotoProfil(&user.db[a]);
						break;
					}
				}
			case 9:
				kicau(&user, &kicauan, &currentUser);
				break;
			case 10:
				displayallkicauan(user, kicauan, teman, currentUser);	
				break;
			case 11:
				idkicau = wtoi(baca());
				suka_kicauan(user, &kicauan, teman, idkicau, currentUser);
				break;
			case 12:
				idkicau = wtoi(baca());
				isiUtas(&utas, currentUser, kicauan, idkicau);
				break;
			case 13:
				idkicau = wtoi(baca());
				indexParam = wtoi(baca());
				sambungUtas(&utas, idkicau, indexParam, currentUser);
				break;
			case 14:
				idkicau = wtoi(baca());
				indexParam = wtoi(baca());
				hapusUtas(&utas, idkicau, indexParam, currentUser);				
				break;
			case 15:
				idkicau = wtoi(baca());
				cetakUtas(utas, kicauan, user, teman, idkicau, currentUser);	
				break;
			case 16:
				daftarteman(currentUser, &user, teman);
				break;
			case 17:
				hapusteman(currentUser, &user, &teman);
				break;
			// case 18:
			// 	idkicau = wtoi(baca());
			// 	indexParam = wtoi(baca());
			// 	Balas(user, currentUser, kicauan, &ltree, teman, idkicau, indexParam);
			// 	break;
			// case 19:
			// 	idkicau = wtoi(baca());
			// 	Balasan(user, currentUser, kicauan, ltree, teman, idkicau);
			// 	break;
			// case 20:
			// 	idkicau = wtoi(baca());
			// 	indexParam = wtoi(baca());
			// 	Hapus_Balasan(user, currentUser, kicauan, &ltree, idkicau, indexParam);
			// 	break;
			case 21:
				BUAT_DRAFT(&user, &currentUser, &kicauan, &sl);
				break;
			case 22:
				LIHAT_DRAFT(&user, &currentUser, &kicauan, &sl);
				break;
			case 23:
				tambahteman(currentUser, &user, teman, &permintaanTeman);
				break;
			case 24:
				daftarpermintaanteman(currentUser, &user, &permintaanTeman);
				break;
			case 25:
				setujuipermintaanteman(currentUser, &user, &teman, &permintaanTeman);
				break;
			case 99:
				simpan(&user, &utas, &kicauan, &teman, &permintaanTeman, &balasan , &sl);
				break;
			case -1:
				printf("Perintah tidak ditemukan.\n");
				break;
		}	
		if (start) {
			printf("\nKetik \';\' untuk melanjutkan\n\n");
			bacakalimat();
		}
	}
}