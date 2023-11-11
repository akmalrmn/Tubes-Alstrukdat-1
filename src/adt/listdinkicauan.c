#include <stdio.h>
#include<stdlib.h>
#include "listdinkicauan.h"



/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDinkicau(ListDinkicau *l, int cap)
/* I.S. l sembarang, capacity > 0 */
/* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
{
    BUFFER(*l) = (Kicau *) malloc(cap * sizeof(Kicau));
    CAPACITY(*l) = cap;
    NEFF(*l) = 0;
}

void dealocateListkicau(ListDinkicau *l)
/* I.S. l terdefinisi; */
/* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
{
    free(BUFFER(*l));
    CAPACITY(*l) = 0;
    NEFF(*l) = 0;
}

/* ********** OPERASI LAIN ********** */
void copyListkicau(ListDinkicau lIn, ListDinkicau *lOut)
/* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
/* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
/* Proses : Menyalin isi lIn ke lOut */ 
{
    IdxType i;

    /* ALGORITMA */
    CreateListDinkicau(lOut, CAPACITY(lIn));

    NEFF(*lOut) = lIn.neff;

    for (i = 0; i <= NEFF(lIn); i++) {
        ELMT(*lOut, i) = ELMT(lIn, i);
    }
}




/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLastkicau(ListDinkicau *l, Kicau newkicauan)
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
{
    ELMT(*l, NEFF(*l) + 1) = newkicauan;
    NEFF(*l)++;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteLastkicau(ListDinkicau *l, Kicau *kicauantemp)
/* Proses : Menghapus elemen terakhir list */
/* I.S. List tidak kosong */
/* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
/*      Banyaknya elemen list berkurang satu */
/*      List l mungkin menjadi kosong */
{
    *kicauantemp = ELMT(*l, NEFF(*l));
    NEFF(*l)--;
}

ListDinkicau *cariKicauan(ListDinkicau *l,int id)
{
    ListDinkicau *lKicau = NULL;

  
    for (int i = 0; i < NEFF(*l); i++) {
        if ((*l).buff[i].id == id) {
            lKicau = (ListDinkicau *)l->buff;
            break;
        }
    }

    return lKicau;
}