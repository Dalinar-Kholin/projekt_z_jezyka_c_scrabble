#include <string.h>
#include "operacje_drzewa.c"
#include <wchar.h>
#include "locale.h"


int main(int argc, char **argv) {
    setlocale(LC_ALL, "en_US.utf8");
    FILE *f = fopen("./pop.txt", "r");
    for(int i = 1;i<argc;i++){// mozliwosc dodania wiecej blankow aby sprawdzic jak bedzie sie zachowywal program
        int dlugosc=dl(argv[i]);
        if(dlugosc<6 || dlugosc>7) continue;
        if(argv[i][0]=='-' && argv[i][1]=='p' && argv[i][2]=='o' && argv[i][3]=='i' && argv[i][4]=='n' && argv[i][5]=='t' && argv[i][6]=='s') {
            FILE *p = fopen(argv[i + 1], "r");
            if (p == NULL) { fprintf(stderr, "cos nie poszlo wczytanie punktow\n"); }
            wint_t c;
            wint_t tab[10];//zakładam że nie będzie punktacji większej niż milion
            int par = 0;
            for (;;) {
                c = (wint_t) fgetwc(p);
                if (c == WEOF) {
                    break;
                }
                if (c == '\n') {
                    int wynik=0;
                    for (int j = 2; j < par-1; ++j) {
                        wynik*=10;
                        wynik+=(tab[j]-L'0');
                    }
                    if(zmiana_litery_na_int(tab[0])>35){par=0;continue;}
                    punktacja[zmiana_litery_na_int(tab[0])] = wynik;
                    par = 0;
                    continue;
                }
                tab[par] = c;
                par++;
            }
        }
        if(argv[i][0]=='-' && argv[i][1]=='c' && argv[i][2]=='o' && argv[i][3]=='r' && argv[i][4]=='p' && argv[i][5]=='s'){
            f = fopen(argv[i+1], "r");
        }
    }// flagi wywolania funkcji dzialaja
    int *slowo = (int *) calloc(30, sizeof(int));
    if (f == NULL) {
        fprintf(stderr, "ayayyaya cos poszlo nie tak\n");
        return 1;
    }
    int par = 0;
    wint_t c;
    tree *kamien = inicjacja_ojca();
    for (int i = 0;; i++) {
        c = (wint_t) fgetwc(f);
        if ( c == WEOF) {
            if (par <= 9) {
                dodanie_slowa(kamien, slowo, par);
            }
            break;
        }
        if (c == L'\n') {
            if (par <= 9) {
                dodanie_slowa(kamien, slowo, par);
            }
            par = 0;
            continue;//pomija \n
        }
        slowo[par] = zmiana_litery_na_int(c);
        par += 1;
    }
    free(slowo);
    printf("type any number to stop\n");
    slowo_wynikowe = (tree **) calloc(10, sizeof(tree));
    max_buffor=10;
    while (1) {

        wynik_ilosc_punktow = 0;
        printf("\n========================\n");
        printf("Prosze podac litery: \n\n");
        ile_wynikow=0;
        iel = 0;//ilosc iteracji aby zac zlozonosc tak mniej wiecej
        wchar_t slowo_do_wczytania_wc[100];
        for (int i = 0; i < 100; ++i) {
            slowo_do_wczytania_wc[i]=25;
        }
        if (fgetws(slowo_do_wczytania_wc, 100, stdin)==NULL){ fprintf(stderr,"niepoprawne dane \n");return -1;}
        int litery[10];
        ilosc_posiadanych_liter = 0;
        while (slowo_do_wczytania_wc[ilosc_posiadanych_liter] != L'\n') {
            litery[ilosc_posiadanych_liter] = zmiana_litery_na_int(slowo_do_wczytania_wc[ilosc_posiadanych_liter]);
            ilosc_posiadanych_liter++;
        }
        bubble_sort(litery, ilosc_posiadanych_liter);
        for (int i = 0; i < ilosc_posiadanych_liter; i++) {
            if (slowo_do_wczytania_wc[i] >= L'0' && slowo_do_wczytania_wc[i] <= L'9') {
                printf("dziękujemy za skorzystanie z naszych usług :))\n");
                czyszczenie_pamieci_drzewa(kamien);
                return 0;
            }
        }//wyjscie z programu
        while (sprawdzenie_pooprawnosci_podanych_liter(litery)) {
            printf("prosimy o podanie prawidlowych danych\n\n");
            if (fgetws(slowo_do_wczytania_wc, 100, stdin)==NULL){ fprintf(stderr,"nie udało się wczytać\n");return -1;}
            ilosc_posiadanych_liter=0;
            while (slowo_do_wczytania_wc[ilosc_posiadanych_liter] != L'\n') {
                litery[ilosc_posiadanych_liter] = zmiana_litery_na_int(slowo_do_wczytania_wc[ilosc_posiadanych_liter]);
                ilosc_posiadanych_liter++;
            }
            bubble_sort(litery,ilosc_posiadanych_liter);
            for (int i = 0; i < ilosc_posiadanych_liter; i++) {
                if (slowo_do_wczytania_wc[i] >= L'0' && slowo_do_wczytania_wc[i] <= L'9') {
                    printf("dziękujemy za skorzystanie z naszych usług :))\n");
                    czyszczenie_pamieci_drzewa(kamien);
                    return 0;
                }
            }
        }


        if(ilosc_posiadanych_liter>8){printf("prosze podac poprawne litery\n\n");continue;}
        printf("\n----------------------------------------\n");
        szukanie_najbardziej_punktowanego_slowa(kamien, litery, ilosc_posiadanych_liter, 0, 0);
        wyswietlanie_slow_wynikowych(litery);//wyswietlanie slowa
        //a musze je tam wstawic aby nie było powidoków po poprzednich zestawach liter
        printf("ile iteracji: %d\n", iel);
        printf("\n========================\n");
    }
}