/**
 * \file rent_a_car_logic.c
 *
 * \brief Implementacija poslovne logike rent-a-car sistema.
 *
 * Ovaj fajl namjerno ne sadrzi main(), scanf/printf pozive, globalne
 * promjenljive niti fopen/fclose - sto ga cini pogodnim za direktno
 * ukljucivanje u Google Test i Parasoft C/C++test projekte.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rent_a_car_logic.h"

 /**
  * \brief Pronalazi indeks aktivnog zapisa o iznajmljivanju za dati automobil.
  *
  * \param [in] niz            Niz zapisa o iznajmljivanju koji se pretrazuje.
  * \param [in] brojElemenata  Broj validnih elemenata u nizu \p niz.
  * \param [in] idAutomobila   ID automobila za koji se trazi aktivan zapis.
  *
  * \return Indeks prvog aktivnog zapisa za dati automobil, ili -1 ako takav
  *         zapis ne postoji ili je \p niz NULL.
  */
int pronadjiAktivnoIznajmljivanjeZaAuto(const Iznajmljivanje niz[], int brojElemenata, int idAutomobila)
{
    int i;

    if (niz == NULL)
    {
        return -1;
    }

    for (i = 0; i < brojElemenata; i++)
    {
        if (niz[i].id_automobila == idAutomobila && niz[i].aktivno == 1)
        {
            return i;
        }
    }
    return -1;
}

/**
 * \brief Racuna ukupnu cijenu iznajmljivanja.
 *
 * \param [in] brojDana      Broj dana iznajmljivanja.
 * \param [in] cijenaPoDanu  Cijena iznajmljivanja po danu, u KM.
 *
 * \return Ukupna cijena iznajmljivanja (brojDana * cijenaPoDanu), ili
 *         -1.0f ako je broj dana ili cijena po danu nevalidna.
 */
float izracunajUkupnuCijenu(int brojDana, float cijenaPoDanu)
{
    if (!jeBrojDanaValidan(brojDana))
    {
        return -1.0f;
    }

    if (!jeCijenaValidna(cijenaPoDanu))
    {
        return -1.0f;
    }

    return brojDana * cijenaPoDanu;
}

/**
 * \brief Provjerava da li je automobil trenutno dostupan za iznajmljivanje.
 *
 * \param [in] automobil Pokazivac na automobil koji se provjerava. Automobil
 *                        se ne mijenja (parametar je oznacen kao const).
 *
 * \return 1 ako je automobil dostupan, 0 ako je iznajmljen ili ako je
 *         prosledjen null pokazivac.
 */
int jeAutomobilDostupan(const Automobil* automobil)
{
    if (automobil == NULL)
    {
        return 0;
    }
    return (automobil->dostupan == 1);
}

/**
 * \brief Provjerava da li je broj dana iznajmljivanja validan.
 *
 * \param [in] brojDana Broj dana koji se provjerava.
 *
 * \return 1 ako je brojDana u opsegu [\ref MIN_BROJ_DANA, \ref MAX_BROJ_DANA], inace 0.
 */
int jeBrojDanaValidan(int brojDana)
{
    return (brojDana >= MIN_BROJ_DANA && brojDana <= MAX_BROJ_DANA);
}

/**
 * \brief Provjerava da li je godiste automobila u dozvoljenom opsegu.
 *
 * \param [in] godiste Godiste koje se provjerava.
 *
 * \return 1 ako je godiste izmedju \ref MIN_GODISTE i \ref MAX_GODISTE (ukljucivo), inace 0.
 */
int jeGodisteValidno(int godiste)
{
    return (godiste >= MIN_GODISTE && godiste <= MAX_GODISTE);
}

/**
 * \brief Provjerava da li je cijena po danu validna.
 *
 * \param [in] cijena Cijena koja se provjerava.
 *
 * \return 1 ako je cijena veca od nule, inace 0.
 */
int jeCijenaValidna(float cijena)
{
    return (cijena > 0.0f);
}

/**
 * \brief Vraca tekstualni opis statusa automobila.
 *
 * \param [in] dostupan Status dostupnosti automobila (1 = dostupan, 0 = iznajmljen).
 *
 * \return Pokazivac na staticki string "Dostupan" ili "Iznajmljen".
 */
const char* formatirajStatusAutomobila(int dostupan)
{
    if (dostupan == 1)
    {
        return "Dostupan";
    }
    return "Iznajmljen";
}

/**
 * \brief Vraca citljiv tekstualni opis za dati \ref RentStatus.
 *
 * \param [in] status Status kod ciji se opis trazi.
 *
 * \return Pokazivac na staticki string sa opisom statusa.
 */
const char* opisStatusa(RentStatus status)
{
    switch (status)
    {
    case RENT_OK:
        return "Operacija je uspjesno izvrsena.";
    case RENT_NULL_POINTER:
        return "GRESKA: Nevalidan (null) pokazivac.";
    case RENT_INVALID_YEAR:
        return "Godiste nije u dozvoljenom opsegu (1950-2100).";
    case RENT_INVALID_PRICE:
        return "Cijena po danu mora biti veca od nule.";
    case RENT_INVALID_DAYS:
        return "Broj dana mora biti u opsegu 1-365.";
    case RENT_INVALID_ID:
        return "Nevalidan ID.";
    case RENT_CAR_NOT_FOUND:
        return "Automobil sa datim ID-om ne postoji.";
    case RENT_CAR_NOT_AVAILABLE:
        return "Automobil je trenutno iznajmljen.";
    case RENT_CAR_ALREADY_AVAILABLE:
        return "Ovaj automobil trenutno nije iznajmljen.";
    case RENT_RENTAL_NOT_FOUND:
        return "Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil.";
    case RENT_LIMIT_REACHED:
        return "Dostignut je maksimalan dozvoljeni broj zapisa.";
    case RENT_PARSE_ERROR:
        return "Greska pri parsiranju linije iz fajla.";
    case RENT_FILE_ERROR:
        return "Greska pri radu sa fajlom.";
    default:
        return "Nepoznat status.";
    }
}

/**
 * \brief Validira podatke automobila (godiste i cijenu po danu).
 *
 * \param [in] automobil Automobil ciji se podaci provjeravaju.
 *
 * \return \ref RENT_NULL_POINTER ako je \p automobil NULL,
 *         \ref RENT_INVALID_YEAR ako godiste nije validno,
 *         \ref RENT_INVALID_PRICE ako cijena po danu nije validna,
 *         inace \ref RENT_OK.
 */
RentStatus validirajAutomobil(const Automobil* automobil)
{
    if (automobil == NULL)
    {
        return RENT_NULL_POINTER;
    }

    if (!jeGodisteValidno(automobil->godiste))
    {
        return RENT_INVALID_YEAR;
    }

    if (!jeCijenaValidna(automobil->cijena_po_danu))
    {
        return RENT_INVALID_PRICE;
    }

    return RENT_OK;
}

/**
 * \brief Popunjava strukturu novog automobila i validira njegove podatke.
 *
 * \param [out] noviAutomobil Struktura koja se popunjava.
 * \param [in]  id            ID koji ce biti dodijeljen automobilu.
 * \param [in]  marka         Marka automobila (kopira se, max \ref DUZINA_STRINGA - 1 karaktera).
 * \param [in]  model         Model automobila (kopira se, max \ref DUZINA_STRINGA - 1 karaktera).
 * \param [in]  godiste       Godiste automobila.
 * \param [in]  cijenaPoDanu  Cijena iznajmljivanja po danu.
 *
 * Struktura \p noviAutomobil se mijenja samo ako su svi podaci validni.
 * Ako validacija ne prodje (ili je neki pokazivac NULL), struktura ostaje
 * nepromijenjena.
 *
 * \return \ref RENT_NULL_POINTER ako je neki od pokazivaca NULL,
 *         \ref RENT_INVALID_YEAR / \ref RENT_INVALID_PRICE ako podaci nisu validni,
 *         inace \ref RENT_OK (automobil je popunjen i oznacen kao dostupan).
 */
RentStatus kreirajAutomobil(Automobil* noviAutomobil, int id, const char* marka, const char* model,
    int godiste, float cijenaPoDanu)
{
    Automobil privremeni;
    RentStatus status;

    if (noviAutomobil == NULL || marka == NULL || model == NULL)
    {
        return RENT_NULL_POINTER;
    }

    /* Podaci se prvo upisuju u privremenu strukturu, kako izlazna struktura
       ne bi bila djelimicno popunjena ako validacija ne prodje. */
    privremeni.id = id;

    strncpy(privremeni.marka, marka, DUZINA_STRINGA - 1);
    privremeni.marka[DUZINA_STRINGA - 1] = '\0';

    strncpy(privremeni.model, model, DUZINA_STRINGA - 1);
    privremeni.model[DUZINA_STRINGA - 1] = '\0';

    privremeni.godiste = godiste;
    privremeni.cijena_po_danu = cijenaPoDanu;
    privremeni.dostupan = 1; /* novi automobil je odmah dostupan */

    status = validirajAutomobil(&privremeni);
    if (status != RENT_OK)
    {
        return status;
    }

    *noviAutomobil = privremeni;
    return RENT_OK;
}

/**
 * \brief Provjerava da li automobil smije biti obrisan.
 *
 * \param [in] automobil Automobil koji se provjerava.
 *
 * \return \ref RENT_NULL_POINTER ako je \p automobil NULL,
 *         \ref RENT_CAR_NOT_AVAILABLE ako je automobil trenutno iznajmljen,
 *         inace \ref RENT_OK.
 */
RentStatus validirajBrisanjeAutomobila(const Automobil* automobil)
{
    if (automobil == NULL)
    {
        return RENT_NULL_POINTER;
    }

    if (!jeAutomobilDostupan(automobil))
    {
        return RENT_CAR_NOT_AVAILABLE;
    }

    return RENT_OK;
}

/**
 * \brief Uklanja automobil sa datog indeksa iz niza, pomjerajuci ostale elemente.
 *
 * \param [in,out] niz            Niz automobila iz kojeg se uklanja element.
 * \param [in,out] brojElemenata  Pokazivac na trenutni broj elemenata u nizu; umanjuje se za 1 pri uspjehu.
 * \param [in]     indeks         Indeks elementa koji se uklanja.
 *
 * \return \ref RENT_NULL_POINTER ako je \p niz ili \p brojElemenata NULL,
 *         \ref RENT_INVALID_ID ako je \p indeks van opsega,
 *         inace \ref RENT_OK.
 */
RentStatus obrisiAutomobilNaIndeksu(Automobil niz[], int* brojElemenata, int indeks)
{
    int i;

    if (niz == NULL || brojElemenata == NULL)
    {
        return RENT_NULL_POINTER;
    }

    if (indeks < 0 || indeks >= *brojElemenata)
    {
        return RENT_INVALID_ID;
    }

    for (i = indeks; i < *brojElemenata - 1; i++)
    {
        niz[i] = niz[i + 1];
    }
    (*brojElemenata)--;

    return RENT_OK;
}

/**
 * \brief Popunjava i validira novi zapis o iznajmljivanju.
 *
 * \param [out] iznajmljivanje Struktura koja se popunjava.
 * \param [in]  id             ID novog zapisa o iznajmljivanju.
 * \param [in]  idAutomobila   ID automobila koji se iznajmljuje.
 * \param [in]  cijenaPoDanu   Cijena po danu za dati automobil.
 * \param [in]  ime            Ime klijenta (kopira se, max \ref DUZINA_IMENA - 1 karaktera).
 * \param [in]  prezime        Prezime klijenta (kopira se, max \ref DUZINA_IMENA - 1 karaktera).
 * \param [in]  datumPocetka   Datum pocetka iznajmljivanja (kopira se, max \ref DUZINA_DATUMA - 1 karaktera).
 * \param [in]  datumKraja     Datum kraja iznajmljivanja (kopira se, max \ref DUZINA_DATUMA - 1 karaktera).
 * \param [in]  brojDana       Broj dana iznajmljivanja.
 *
 * \return \ref RENT_NULL_POINTER ako je neki od pokazivaca NULL,
 *         \ref RENT_INVALID_DAYS ako broj dana nije validan,
 *         \ref RENT_INVALID_PRICE ako cijena po danu nije validna,
 *         inace \ref RENT_OK.
 */
RentStatus pripremiIznajmljivanje(Iznajmljivanje* iznajmljivanje, int id, int idAutomobila, float cijenaPoDanu,
    const char* ime, const char* prezime, const char* datumPocetka, const char* datumKraja, int brojDana)
{
    float ukupnaCijena;

    if (iznajmljivanje == NULL || ime == NULL || prezime == NULL || datumPocetka == NULL || datumKraja == NULL)
    {
        return RENT_NULL_POINTER;
    }

    if (!jeBrojDanaValidan(brojDana))
    {
        return RENT_INVALID_DAYS;
    }

    if (!jeCijenaValidna(cijenaPoDanu))
    {
        return RENT_INVALID_PRICE;
    }

    ukupnaCijena = izracunajUkupnuCijenu(brojDana, cijenaPoDanu);
    if (ukupnaCijena < 0.0f)
    {
        return RENT_INVALID_DAYS;
    }

    iznajmljivanje->id = id;
    iznajmljivanje->id_automobila = idAutomobila;

    strncpy(iznajmljivanje->ime, ime, DUZINA_IMENA - 1);
    iznajmljivanje->ime[DUZINA_IMENA - 1] = '\0';

    strncpy(iznajmljivanje->prezime, prezime, DUZINA_IMENA - 1);
    iznajmljivanje->prezime[DUZINA_IMENA - 1] = '\0';

    strncpy(iznajmljivanje->datum_pocetka, datumPocetka, DUZINA_DATUMA - 1);
    iznajmljivanje->datum_pocetka[DUZINA_DATUMA - 1] = '\0';

    strncpy(iznajmljivanje->datum_kraja, datumKraja, DUZINA_DATUMA - 1);
    iznajmljivanje->datum_kraja[DUZINA_DATUMA - 1] = '\0';

    iznajmljivanje->broj_dana = brojDana;
    iznajmljivanje->ukupna_cijena = ukupnaCijena;
    iznajmljivanje->aktivno = 1;

    return RENT_OK;
}

/**
 * \brief Obradjuje vracanje automobila (poslovna logika, bez I/O).
 *
 * \param [in,out] automobil       Automobil koji se vraca.
 * \param [in,out] iznajmljivanje  Pokazivac na aktivan zapis iznajmljivanja za ovaj automobil,
 *                                 ili NULL ako takav zapis nije pronadjen.
 *
 * \return \ref RENT_NULL_POINTER ako je \p automobil NULL,
 *         \ref RENT_CAR_ALREADY_AVAILABLE ako automobil vec nije iznajmljen,
 *         \ref RENT_RENTAL_NOT_FOUND ako \p iznajmljivanje nije prosledjen (NULL) -
 *         u tom slucaju je status automobila i dalje azuriran na dostupan,
 *         inace \ref RENT_OK.
 */
RentStatus obradiVracanjeAutomobila(Automobil* automobil, Iznajmljivanje* iznajmljivanje)
{
    if (automobil == NULL)
    {
        return RENT_NULL_POINTER;
    }

    if (jeAutomobilDostupan(automobil))
    {
        return RENT_CAR_ALREADY_AVAILABLE;
    }

    /* Status automobila se azurira bez obzira na to da li je aktivan zapis pronadjen -
       ovo je zastitna mjera protiv nekonzistentnog stanja podataka. */
    automobil->dostupan = 1;

    if (iznajmljivanje == NULL)
    {
        return RENT_RENTAL_NOT_FOUND;
    }

    iznajmljivanje->aktivno = 0;
    return RENT_OK;
}

/**
 * \brief Parsira jednu liniju teksta u strukturu \ref Automobil.
 *
 * \param [in]  linija    Linija teksta koja se parsira.
 * \param [out] automobil Struktura u koju se upisuje rezultat parsiranja.
 *
 * \return \ref RENT_NULL_POINTER ako je \p linija ili \p automobil NULL,
 *         \ref RENT_PARSE_ERROR ako linija nema svih 6 ocekivanih polja,
 *         inace \ref RENT_OK.
 */
RentStatus parsirajAutomobil(const char* linija, Automobil* automobil)
{
    int uneseno;

    if (linija == NULL || automobil == NULL)
    {
        return RENT_NULL_POINTER;
    }

    uneseno = sscanf(linija, "%d;%29[^;];%29[^;];%d;%f;%d",
        &automobil->id,
        automobil->marka,
        automobil->model,
        &automobil->godiste,
        &automobil->cijena_po_danu,
        &automobil->dostupan);

    if (uneseno != 6)
    {
        return RENT_PARSE_ERROR;
    }

    return RENT_OK;
}

/**
 * \brief Parsira jednu liniju teksta u strukturu \ref Iznajmljivanje.
 *
 * \param [in]  linija         Linija teksta koja se parsira.
 * \param [out] iznajmljivanje Struktura u koju se upisuje rezultat parsiranja.
 *
 * \return \ref RENT_NULL_POINTER ako je \p linija ili \p iznajmljivanje NULL,
 *         \ref RENT_PARSE_ERROR ako linija nema svih 9 ocekivanih polja,
 *         inace \ref RENT_OK.
 */
RentStatus parsirajIznajmljivanje(const char* linija, Iznajmljivanje* iznajmljivanje)
{
    int uneseno;

    if (linija == NULL || iznajmljivanje == NULL)
    {
        return RENT_NULL_POINTER;
    }

    uneseno = sscanf(linija, "%d;%d;%49[^;];%49[^;];%10[^;];%10[^;];%d;%f;%d",
        &iznajmljivanje->id,
        &iznajmljivanje->id_automobila,
        iznajmljivanje->ime,
        iznajmljivanje->prezime,
        iznajmljivanje->datum_pocetka,
        iznajmljivanje->datum_kraja,
        &iznajmljivanje->broj_dana,
        &iznajmljivanje->ukupna_cijena,
        &iznajmljivanje->aktivno);

    if (uneseno != 9)
    {
        return RENT_PARSE_ERROR;
    }

    return RENT_OK;
}