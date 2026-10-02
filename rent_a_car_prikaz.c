/**
 * \file rent_a_car_prikaz.c
 *
 * \brief Implementacija funkcija za ispis menija i tabelarnih pregleda.
 */

#include <stdio.h>
#include "rent_a_car_logic.h"
#include "rent_a_car_stanje.h"
#include "rent_a_car_prikaz.h"

/**
 * \brief Ispisuje glavni meni sa svim dostupnim opcijama na standardni izlaz.
 */
void prikaziMeni(void)
{
    printf("======================================\n");
    printf("         RENT A CAR SISTEM\n");
    printf("======================================\n");
    printf(" 1. Dodaj novi automobil\n");
    printf(" 2. Prikazi sve automobile\n");
    printf(" 3. Obrisi automobil\n");
    printf(" 4. Iznajmi automobil\n");
    printf(" 5. Vrati automobil\n");
    printf(" 6. Prikazi sva iznajmljivanja\n");
    printf(" 0. Izlaz\n");
    printf("======================================\n");
}

/**
 * \brief Ispisuje tabelarni pregled svih automobila trenutno u sistemu.
 *
 * Za status svakog automobila koristi funkciju \ref formatirajStatusAutomobila.
 * Ako trenutno nema unetih automobila, ispisuje odgovarajucu poruku.
 */
void prikaziAutomobile(void)
{
    int i;

    printf("\n--- Lista automobila ---\n");

    if (brojAutomobila == 0)
    {
        printf("Trenutno nema unesenih automobila.\n\n");
        return;
    }

    printf("%-4s %-15s %-15s %-8s %-12s %-12s\n",
        "ID", "Marka", "Model", "Godiste", "Cijena/dan", "Status");
    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < brojAutomobila; i++)
    {
        printf("%-4d %-15s %-15s %-8d %-12.2f %-12s\n",
            automobili[i].id,
            automobili[i].marka,
            automobili[i].model,
            automobili[i].godiste,
            automobili[i].cijena_po_danu,
            formatirajStatusAutomobila(automobili[i].dostupan));
    }
    printf("\n");
}

/**
 * \brief Ispisuje tabelarni pregled svih zapisa o iznajmljivanju.
 *
 * Prikazuje i aktivna (automobil jos nije vracen) i zavrsena
 * iznajmljivanja, sa naznakom statusa za svaki zapis.
 */
void prikaziIznajmljivanja(void)
{
    int i;

    printf("\n--- Lista iznajmljivanja ---\n");

    if (brojIznajmljivanja == 0)
    {
        printf("Trenutno nema evidentiranih iznajmljivanja.\n\n");
        return;
    }

    printf("%-4s %-8s %-12s %-12s %-12s %-12s %-6s %-10s %-10s\n",
        "ID", "AutoID", "Ime", "Prezime", "Pocetak", "Kraj", "Dani", "Cijena", "Status");
    printf("----------------------------------------------------------------------------------------\n");

    for (i = 0; i < brojIznajmljivanja; i++)
    {
        printf("%-4d %-8d %-12s %-12s %-12s %-12s %-6d %-10.2f %-10s\n",
            iznajmljivanja[i].id,
            iznajmljivanja[i].id_automobila,
            iznajmljivanja[i].ime,
            iznajmljivanja[i].prezime,
            iznajmljivanja[i].datum_pocetka,
            iznajmljivanja[i].datum_kraja,
            iznajmljivanja[i].broj_dana,
            iznajmljivanja[i].ukupna_cijena,
            iznajmljivanja[i].aktivno ? "Aktivno" : "Zavrseno");
    }
    printf("\n");
}
