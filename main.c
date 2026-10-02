/**
 * \file main.c
 *
 * \brief Konzolna aplikacija za upravljanje rent-a-car sistemom.
 *
 * Aplikacija omogucava dodavanje, brisanje, iznajmljivanje i vracanje
 * automobila, kao i pregled istorije iznajmljivanja.
 *
 * Ovaj fajl sadrzi samo glavnu petlju programa (izbor opcije iz menija).
 * Sva poslovna logika (validacija, racunanje, parsiranje)
 * nalazi se u rent_a_car_logic.h / rent_a_car_logic.c i moze se testirati
 * nezavisno od ovog fajla. Globalno stanje i pomocne funkcije nad njim
 * nalaze se u rent_a_car_stanje.h / rent_a_car_stanje.c, ispis tabela u
 * rent_a_car_prikaz.h / .c, rad sa fajlovima u rent_a_car_fajlovi.h / .c,
 * a akcije menija u rent_a_car_akcije.h / .c.
 */

#include <stdio.h>
#include <stdlib.h>
#include "rent_a_car_logic.h"
#include "rent_a_car_stanje.h"   /* globalni nizovi, MAX_* konstante i pomocne funkcije */
#include "rent_a_car_prikaz.h"   /* ispis menija i tabela */
#include "rent_a_car_fajlovi.h"  /* ucitavanje i cuvanje podataka u fajlovima */
#include "rent_a_car_akcije.h"   /* akcije menija (dodavanje, brisanje, iznajmljivanje, vracanje) */

#define CARS_FILE     "cars.txt"     /**< Naziv fajla u kojem se cuvaju podaci o automobilima. */
#define RENTALS_FILE  "rentals.txt"  /**< Naziv fajla u kojem se cuvaju podaci o iznajmljivanjima. */

 /**
  * \brief Ulazna tacka programa.
  *
  * Ucitava postojece podatke iz fajlova \ref CARS_FILE i \ref RENTALS_FILE,
  * zatim u petlji prikazuje glavni meni i poziva odgovarajucu funkciju na
  * osnovu izbora korisnika, sve dok korisnik ne izabere opciju za izlaz (0).
  *
  * \return 0 ako je program uspesno zavrsen.
  */
int main(void)
{
    int izbor;

    /* Ucitaj postojece podatke iz fajlova. Ako fajlovi ne postoje (prvo pokretanje),
       funkcije vracaju RENT_FILE_ERROR i program pocinje sa praznim listama. */
    (void)ucitajAutomobile(CARS_FILE);
    (void)ucitajIznajmljivanja(RENTALS_FILE);

    do
    {
        prikaziMeni();
        printf("Unesite izbor: ");

        if (scanf("%d", &izbor) != 1)
        {
            printf("\nNevalidan unos. Pokusajte ponovo.\n\n");
            ocistiUlazniBafer();
            izbor = -1;
            continue;
        }
        ocistiUlazniBafer();

        switch (izbor)
        {
        case 1:
            dodajAutomobil(CARS_FILE);
            break;
        case 2:
            prikaziAutomobile();
            break;
        case 3:
            obrisiAutomobil(CARS_FILE);
            break;
        case 4:
            iznajmiAutomobil(CARS_FILE, RENTALS_FILE);
            break;
        case 5:
            vratiAutomobil(CARS_FILE, RENTALS_FILE);
            break;
        case 6:
            prikaziIznajmljivanja();
            break;
        case 0:
            printf("\nHvala na koriscenju sistema. Dovidjenja!\n");
            break;
        default:
            printf("\nNepostojeca opcija. Pokusajte ponovo.\n\n");
            break;
        }

    } while (izbor != 0);

    return 0;
}
