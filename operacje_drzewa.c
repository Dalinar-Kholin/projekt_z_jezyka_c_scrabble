//
// Created by osado on 19.01.2023.
//
#include "dzewa_na_tablicach.h"

int ile_wynikow;
int max_buffor;
tree **slowo_wynikowe;
int wynik_ilosc_punktow;
int ilosc_posiadanych_liter;
int iel; //liczba iteracji/rekurencji całego prograrmu

wchar_t tablica_znakow_wchar[] = L"ąćęłńóśźżabcdefghijklmnopqrstuvwxyzĄĆĘŁŃÓŚŹŻABCDEFGHIJKLMNOPQRSTUVWXYZ";


int punktacja[] = {5, 6, 5, 3, 7, 5, 5, 9, 5, 1, 3, 2, 2, 1, 5, 3, 3, 1, 3, 2, 2, 2, 1, 1, 2, 0, 1, 1, 2, 3, 0, 1, 0, 2,
                   1};



tree *inicjacja(tree *root, int litera) {
    tree *zwrot = calloc(1, sizeof(tree));//calloc powoduje że wszsystkie gałęzie z bomby są null
    if (zwrot != NULL) {
        zwrot->poprzednie = root;
        zwrot->value = litera;
    }
    return zwrot;
}// inicjowanie lisci

short zliczanie_blankow(wint_t * slowo){
    int i=0;
    int wynik=0;
    while (slowo[i]!=L'\0'){
        if(slowo[i]==L'-'){wynik+=1;}
        i++;
    }
    return (short)wynik;
}

tree *inicjacja_ojca() {
    tree *zwrot = calloc(1, sizeof(tree));
    if (zwrot != NULL) {
        for (int i = 0; i < 35; i++) {
            zwrot->rodzina[i] = inicjacja(zwrot, i);// już lepiej stracic te 5 komorek pamieci niz ifowac dodawanie slow
        }
    }
    zwrot->ispapa = 1;
    return zwrot;
} // inicjowanie głównej gałęzi
int dl(char *slowo) {
    int i = 0;
    while (slowo[i] != '\0') { i++; }
    return i;
}

void bubble_sort(int *tab, int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (tab[j] < tab[j + 1]) {
                tab[j] += tab[j + 1];
                tab[j + 1] = tab[j] - tab[j + 1];
                tab[j] -= tab[j + 1];
            }
        }
    }

}//sortowanie

void bubble_sort_wskaznikow() {
    for (int i = 0; i < ile_wynikow; ++i) {
        for (int j = 0; j < ile_wynikow; ++j) {
            if (slowo_wynikowe[j] < slowo_wynikowe[j + 1]) {
                tree *par = slowo_wynikowe[j];
                slowo_wynikowe[j] = slowo_wynikowe[j + 1];
                slowo_wynikowe[j + 1] = par;
            }
        }
    }
} // mam nadzieje że policaj programistycz mnie za to nie będzie ganiać

int zmiana_litery_na_int(wchar_t literka) {
    if (literka == L'-') { return 100; }
    for (int i = 0; i < 70; ++i) {
        if (literka == tablica_znakow_wchar[i]) {
            if (i > 35) { return i - 35; }
            return i;
        }
    }
    return 404;
}// zwraca inta z zakresu 0-35 dla poprawnych liter z alfabetu, 100 dla blanka i 404 dla błędnych danych


void wyswietlanie_slow_wynikowych_pomoc(int *posiadane_litery, tree *wyswietlane_slowo) {
    int *ile_literek = (int *) calloc(100, sizeof(int));
    for (int i = 0; i < ilosc_posiadanych_liter; i++) {
        ile_literek[posiadane_litery[i]] += 1;
    }//dodac blanki
    wchar_t wynik[10];
    int i = 0;
    while (wyswietlane_slowo[0].ispapa != 1) {
        if (ile_literek[wyswietlane_slowo[0].value] <= 0) {
            wynik[i] = tablica_znakow_wchar[wyswietlane_slowo[0].value + 35];
        } else {
            ile_literek[wyswietlane_slowo[0].value]-=1;
            wynik[i] = tablica_znakow_wchar[wyswietlane_slowo[0].value];
        }
        wyswietlane_slowo = wyswietlane_slowo[0].poprzednie;
        i++;
    }
    i -= 1;
    for (; i >= 0; i--) {
        printf("%lc", wynik[i]);
    }
    putchar('\n');
    putchar('\n');
    free(ile_literek);
}
//ala
//9 12 9


void wyswietlanie_slow_wynikowych(int *posiadane_litery) {
    if (wynik_ilosc_punktow == 0) {
        printf("nic sie nie udalo znalezc\n");
        return;
    }

    bubble_sort_wskaznikow(); // po to aby mieć pewnosc że slowa nie bedą poprzeplatane
    printf("wartosc podannych słów: %d\nnajbardziej punktowanie slowa z poddanych liter:\n\n", wynik_ilosc_punktow);
    printf("----------------------------------------\n\n");
    for (int i = 0; i < ile_wynikow - 1; ++i) {
        if (slowo_wynikowe[i] != slowo_wynikowe[i + 1]) {
            wyswietlanie_slow_wynikowych_pomoc(posiadane_litery, slowo_wynikowe[i]);
        }
    }
    wyswietlanie_slow_wynikowych_pomoc(posiadane_litery, slowo_wynikowe[ile_wynikow - 1]);

    max_buffor = 0;
}// razem z funkcja wyswietlanie_slow_wynikowych_pomoc wyswietla wszystkie wyniki


void szukanie_najbardziej_punktowanego_slowa(tree *root, int tab[], int dlugosc, int blank, int punkty) {
    if (blank != 1 && root->ispapa == 0) { punkty += punktacja[root->value]; }
    if ((punkty >= wynik_ilosc_punktow) && (root->ile != 0) && (punkty != 0)) {
        if (punkty > wynik_ilosc_punktow) {
            ile_wynikow = 0;
            wynik_ilosc_punktow = punkty;
        }
        slowo_wynikowe[ile_wynikow] = root;
        ile_wynikow += 1;
        if (ile_wynikow == max_buffor - 2) { slowo_wynikowe = realloc(slowo_wynikowe, (sizeof(tree)) * (max_buffor *= 2)); }
    } //dodawanie do wyniku
    for (int i = 0; i < dlugosc; ++i) {
        if (tab[i] != 100 && root->rodzina[tab[i]] == NULL) { continue; }
        int kopia_bez_litery_ojca[dlugosc - 1];
        int par = 0;
        for (int j = 0; j < dlugosc; j++) {
            if (j == i) { continue; }
            kopia_bez_litery_ojca[par] = tab[j];
            par++;
        }
        if (tab[i] == 100) {
            for (int j = 0; j < 35; ++j) {
                if (root->rodzina[j] != NULL) {
                    szukanie_najbardziej_punktowanego_slowa(root->rodzina[j], kopia_bez_litery_ojca, dlugosc - 1, 1,
                                                            punkty);
                }
            }
        } else {
            szukanie_najbardziej_punktowanego_slowa(root->rodzina[tab[i]], kopia_bez_litery_ojca, dlugosc - 1, 0,
                                                    punkty);
        }
    }
    iel += 1;
}

void dodanie_slowa(tree *root, int tab[], int dlugosc) {
    for (int i = 0; i < dlugosc - 1; i++) {// o dziwo szlaczki jak najbardziej sa alfabetem
        if (root->rodzina[tab[i]] == NULL) {
            root->rodzina[tab[i]] = inicjacja(root, tab[i]);
        }
        root = root->rodzina[tab[i]];
    }
    root->ile += 1;
}//dodanie slowa do drzewa

void czyszczenie_pamieci_drzewa(tree *root) {
    for (int i = 0; i < 35; i++) {
        if (root->rodzina[i] != NULL) czyszczenie_pamieci_drzewa(root->rodzina[i]);
    }
    free(root);
}//czyszczenie pamieci drzewa