#include <stdio.h>
#include "../adt/wordmachine.c"
#include "../adt/charmachine.c"

Word bacakalimat() { // untuk baca input dari user yang ada spasinya
	STARTSENTENCE();
	return currentWord;
}

Word baca() { // untuk baca input dari user yang satu kata doang
	STARTWORD();
	return currentWord;
}

boolean cek(Word kata, char target[]) { // untuk ngecek kesamaan antara word dengan array of char
	boolean sama = true;
	for (int i = 0; i < kata.Length; i++) {
		if (kata.TabWord[i] != target[i]) {
			sama = false;
			break;
		}		
	}	
	return sama;
}

int pindahfungsi(Word kata) { // untuk pindah2 fungsi dari sini
	if (cek(kata, "DAFTAR")) {
		return 1;
	}
	else if (cek(kata, "MASUK")) {
		return 2;
	}
	else if (cek(kata, "KELUAR")) {
		return 3;
	}
	else if (cek(kata, "TUTUP_PROGRAM")) {
		return 4;
	}
}
