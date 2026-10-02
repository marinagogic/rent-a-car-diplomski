/**
 * \file rent_a_car_stanje.c
 *
 * \brief Definicija globalnog stanja i pomocnih funkcija rent-a-car sistema.
 *
 * Funkcije u ovom fajlu ne koriste scanf/printf niti rad sa fajlovima -
 * zavise iskljucivo od globalnih nizova, pa se mogu testirati tako sto se
 * u testu popune nizovi, pozove funkcija i provjeri rezultat.
 */

#include "rent_a_car_stanje.h"

Automobil       automobili[MAX_AUTOMOBILA];
int             brojAutomobila = 0;

Iznajmljivanje  iznajmljivanja[MAX_IZNAJMLJIVANJA];
int             brojIznajmljivanja = 0;

/**
 * \brief Racuna sledeci slobodan ID za novi automobil.
 *
 * \return Najveci postojeci ID u nizu \ref automobili uvecan za 1.
 *         Ako trenutno nema unetih automobila, vraca 1.
 */
int sledeciIdAutomobila(void)
{
    int i;
    int maxId = 0;

    for (i = 0; i < brojAutomobila; i++)
    {
        if (automobili[i].id > maxId)
        {
            maxId = automobili[i].id;
        }
    }
    return maxId + 1;
}

/**
 * \brief Racuna sledeci slobodan ID za novi zapis o iznajmljivanju.
 *
 * \return Najveci postojeci ID u nizu \ref iznajmljivanja uvecan za 1.
 *         Ako trenutno nema unetih zapisa, vraca 1.
 */
int sledeciIdIznajmljivanja(void)
{
    int i;
    int maxId = 0;

    for (i = 0; i < brojIznajmljivanja; i++)
    {
        if (iznajmljivanja[i].id > maxId)
        {
            maxId = iznajmljivanja[i].id;
        }
    }
    return maxId + 1;
}

/**
 * \brief Pronalazi automobil u nizu \ref automobili na osnovu njegovog ID-a.
 *
 * \param [in] id ID automobila koji se trazi.
 *
 * \return Indeks automobila u nizu \ref automobili, ili -1 ako automobil
 *         sa datim ID-om ne postoji.
 */
int pronadjiAutomobilPoId(int id)
{
    int i;

    for (i = 0; i < brojAutomobila; i++)
    {
        if (automobili[i].id == id)
        {
            return i;
        }
    }
    return -1;
}
