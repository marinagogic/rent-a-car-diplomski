/**
 * \file rent_a_car_fajlovi.c
 *
 * \brief Implementacija ucitavanja i cuvanja podataka u tekstualnim fajlovima.
 *
 * Citanje i pisanje fajlova je odvojeno od parsiranja pojedinacnih linija -
 * za parsiranje se koriste \ref parsirajAutomobil i \ref parsirajIznajmljivanje
 * iz rent_a_car_logic.c.
 */

#include <stdio.h>
#include "rent_a_car_logic.h"
#include "rent_a_car_stanje.h"
#include "rent_a_car_fajlovi.h"

/**
 * \brief Ucitava sve automobile iz datog fajla u niz \ref automobili.
 *
 * Postojeci sadrzaj niza se odbacuje (\ref brojAutomobila se postavlja na 0).
 * Linije koje ne mogu biti parsirane se preskacu. Ucitava se najvise
 * \ref MAX_AUTOMOBILA automobila, a ostatak fajla se ignorise.
 *
 * \param [in] putanja Putanja do fajla iz kojeg se ucitava.
 *
 * \return \ref RENT_NULL_POINTER ako je \p putanja NULL,
 *         \ref RENT_FILE_ERROR ako fajl ne moze biti otvoren (npr. ne postoji -
 *         ocekivano pri prvom pokretanju programa; niz ostaje prazan),
 *         inace \ref RENT_OK.
 */
RentStatus ucitajAutomobile(const char* putanja)
{
    FILE* fp;
    char linija[256];

    brojAutomobila = 0;

    if (putanja == NULL)
    {
        return RENT_NULL_POINTER;
    }

    fp = fopen(putanja, "r");
    if (fp == NULL)
    {
        return RENT_FILE_ERROR;
    }

    while (fgets(linija, sizeof(linija), fp) != NULL && brojAutomobila < MAX_AUTOMOBILA)
    {
        Automobil a;

        if (parsirajAutomobil(linija, &a) == RENT_OK)
        {
            automobili[brojAutomobila] = a;
            brojAutomobila++;
        }
    }

    fclose(fp);
    return RENT_OK;
}

/**
 * \brief Cuva sve automobile iz niza \ref automobili u dati fajl.
 *
 * Postojeci sadrzaj fajla se u potpunosti zamjenjuje trenutnim stanjem
 * niza. Svaki automobil se upisuje u jednu liniju formata
 * "id;marka;model;godiste;cijena;dostupan", sa cijenom na dvije decimale.
 *
 * \param [in] putanja Putanja do fajla u koji se cuva.
 *
 * \return \ref RENT_NULL_POINTER ako je \p putanja NULL,
 *         \ref RENT_FILE_ERROR ako fajl ne moze biti otvoren za pisanje
 *         (tada se ispisuje i poruka o gresci), inace \ref RENT_OK.
 */
RentStatus sacuvajAutomobile(const char* putanja)
{
    FILE* fp;
    int i;

    if (putanja == NULL)
    {
        return RENT_NULL_POINTER;
    }

    fp = fopen(putanja, "w");
    if (fp == NULL)
    {
        printf("\n%s (%s)\n\n", opisStatusa(RENT_FILE_ERROR), putanja);
        return RENT_FILE_ERROR;
    }

    for (i = 0; i < brojAutomobila; i++)
    {
        fprintf(fp, "%d;%s;%s;%d;%.2f;%d\n",
            automobili[i].id,
            automobili[i].marka,
            automobili[i].model,
            automobili[i].godiste,
            automobili[i].cijena_po_danu,
            automobili[i].dostupan);
    }

    fclose(fp);
    return RENT_OK;
}

/**
 * \brief Ucitava sve zapise o iznajmljivanju iz datog fajla u niz \ref iznajmljivanja.
 *
 * Postojeci sadrzaj niza se odbacuje (\ref brojIznajmljivanja se postavlja
 * na 0). Linije koje ne mogu biti parsirane se preskacu. Ucitava se najvise
 * \ref MAX_IZNAJMLJIVANJA zapisa, a ostatak fajla se ignorise.
 *
 * \param [in] putanja Putanja do fajla iz kojeg se ucitava.
 *
 * \return \ref RENT_NULL_POINTER ako je \p putanja NULL,
 *         \ref RENT_FILE_ERROR ako fajl ne moze biti otvoren (niz ostaje prazan),
 *         inace \ref RENT_OK.
 */
RentStatus ucitajIznajmljivanja(const char* putanja)
{
    FILE* fp;
    char linija[256];

    brojIznajmljivanja = 0;

    if (putanja == NULL)
    {
        return RENT_NULL_POINTER;
    }

    fp = fopen(putanja, "r");
    if (fp == NULL)
    {
        return RENT_FILE_ERROR;
    }

    while (fgets(linija, sizeof(linija), fp) != NULL && brojIznajmljivanja < MAX_IZNAJMLJIVANJA)
    {
        Iznajmljivanje r;

        if (parsirajIznajmljivanje(linija, &r) == RENT_OK)
        {
            iznajmljivanja[brojIznajmljivanja] = r;
            brojIznajmljivanja++;
        }
    }

    fclose(fp);
    return RENT_OK;
}

/**
 * \brief Cuva sve zapise o iznajmljivanju iz niza \ref iznajmljivanja u dati fajl.
 *
 * Postojeci sadrzaj fajla se u potpunosti zamjenjuje trenutnim stanjem niza.
 *
 * \param [in] putanja Putanja do fajla u koji se cuva.
 *
 * \return \ref RENT_NULL_POINTER ako je \p putanja NULL,
 *         \ref RENT_FILE_ERROR ako fajl ne moze biti otvoren za pisanje
 *         (tada se ispisuje i poruka o gresci), inace \ref RENT_OK.
 */
RentStatus sacuvajIznajmljivanja(const char* putanja)
{
    FILE* fp;
    int i;

    if (putanja == NULL)
    {
        return RENT_NULL_POINTER;
    }

    fp = fopen(putanja, "w");
    if (fp == NULL)
    {
        printf("\n%s (%s)\n\n", opisStatusa(RENT_FILE_ERROR), putanja);
        return RENT_FILE_ERROR;
    }

    for (i = 0; i < brojIznajmljivanja; i++)
    {
        fprintf(fp, "%d;%d;%s;%s;%s;%s;%d;%.2f;%d\n",
            iznajmljivanja[i].id,
            iznajmljivanja[i].id_automobila,
            iznajmljivanja[i].ime,
            iznajmljivanja[i].prezime,
            iznajmljivanja[i].datum_pocetka,
            iznajmljivanja[i].datum_kraja,
            iznajmljivanja[i].broj_dana,
            iznajmljivanja[i].ukupna_cijena,
            iznajmljivanja[i].aktivno);
    }

    fclose(fp);
    return RENT_OK;
}
