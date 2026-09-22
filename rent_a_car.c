/**
 * \file rent_a_car.c
 *
 * \brief Konzolna aplikacija za upravljanje rent-a-car sistemom.
 *
 * Aplikacija omogucava dodavanje, brisanje, iznajmljivanje i vracanje
 * automobila, kao i pregled istorije iznajmljivanja.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_AUTOMOBILA      100   /**< Maksimalan broj automobila koji se moze cuvati u memoriji. */
#define MAX_IZNAJMLJIVANJA  200   /**< Maksimalan broj zapisa o iznajmljivanju koji se moze cuvati u memoriji. */

#define CARS_FILE     "cars.txt"     /**< Naziv fajla u kojem se cuvaju podaci o automobilima. */
#define RENTALS_FILE  "rentals.txt"  /**< Naziv fajla u kojem se cuvaju podaci o iznajmljivanjima. */

#define DUZINA_STRINGA   30   /**< Maksimalna duzina stringa za marku i model automobila. */
#define DUZINA_IMENA     50   /**< Maksimalna duzina stringa za ime i prezime klijenta. */
#define DUZINA_DATUMA    11   /**< Duzina stringa za datum u formatu DD-MM-GGGG (ukljucujuci '\0'). */

#define MIN_GODISTE   1950   /**< Najmanje dozvoljeno godiste automobila. */
#define MAX_GODISTE   2100   /**< Najvece dozvoljeno godiste automobila. */

#define MIN_BROJ_DANA    1    /**< Najmanji dozvoljen broj dana iznajmljivanja. */
#define MAX_BROJ_DANA  365    /**< Najveci dozvoljen broj dana iznajmljivanja. */


 /**
  * \brief Struktura koja opisuje jedan automobil u sistemu.
  */
typedef struct
{
    int   id;                          /**< Jedinstveni identifikator automobila. */
    char  marka[DUZINA_STRINGA];       /**< Marka automobila (npr. "Volkswagen"). */
    char  model[DUZINA_STRINGA];       /**< Model automobila (npr. "Golf"). */
    int   godiste;                     /**< Godiste automobila. */
    float cijena_po_danu;              /**< Cijena iznajmljivanja po danu, u KM. */
    int   dostupan;                    /**< 1 = automobil je dostupan za iznajmljivanje, 0 = trenutno je iznajmljen. */
} Automobil;

/**
 * \brief Struktura koja opisuje jedan zapis o iznajmljivanju automobila.
 */
typedef struct
{
    int   id;                          /**< Jedinstveni identifikator zapisa o iznajmljivanju. */
    int   id_automobila;               /**< ID automobila na koji se zapis odnosi. */
    char  ime[DUZINA_IMENA];           /**< Ime klijenta. */
    char  prezime[DUZINA_IMENA];       /**< Prezime klijenta. */
    char  datum_pocetka[DUZINA_DATUMA];/**< Datum pocetka iznajmljivanja (format DD-MM-GGGG). */
    char  datum_kraja[DUZINA_DATUMA];  /**< Datum kraja iznajmljivanja (format DD-MM-GGGG). */
    int   broj_dana;                   /**< Broj dana na koji je automobil iznajmljen. */
    float ukupna_cijena;               /**< Ukupna cijena iznajmljivanja, u KM. */
    int   aktivno;                     /**< 1 = automobil jos nije vracen, 0 = iznajmljivanje je zavrseno. */
} Iznajmljivanje;

/**
 * \brief Status kodovi koje vracaju funkcije poslovne logike.
 */
typedef enum
{
    RENT_OK = 0,                /**< Operacija uspjesno izvrsena. */
    RENT_NULL_POINTER,          /**< Prosledjen je NULL pokazivac tamo gdje se ocekivao validan. */
    RENT_INVALID_YEAR,          /**< Godiste automobila nije u dozvoljenom opsegu. */
    RENT_INVALID_PRICE,         /**< Cijena po danu nije veca od nule. */
    RENT_INVALID_DAYS,          /**< Broj dana iznajmljivanja nije u dozvoljenom opsegu. */
    RENT_INVALID_ID,            /**< Nevalidan ID (npr. van opsega niza). */
    RENT_CAR_NOT_FOUND,         /**< Automobil sa datim ID-om ne postoji. */
    RENT_CAR_NOT_AVAILABLE,     /**< Automobil je trenutno iznajmljen. */
    RENT_CAR_ALREADY_AVAILABLE, /**< Automobil vec nije iznajmljen (vracanje nije potrebno). */
    RENT_RENTAL_NOT_FOUND,      /**< Nije pronadjen aktivan zapis iznajmljivanja. */
    RENT_LIMIT_REACHED,         /**< Dostignut je maksimalan broj zapisa u nizu. */
    RENT_PARSE_ERROR,           /**< Greska pri parsiranju linije iz fajla. */
    RENT_FILE_ERROR             /**< Greska pri radu sa fajlom. */
} RentStatus;

Automobil       automobili[MAX_AUTOMOBILA];        /**< Niz svih automobila trenutno ucitanih u memoriju. */
int             brojAutomobila = 0;                /**< Trenutan broj automobila u nizu \ref automobili. */

Iznajmljivanje  iznajmljivanja[MAX_IZNAJMLJIVANJA]; /**< Niz svih zapisa o iznajmljivanju ucitanih u memoriju. */
int             brojIznajmljivanja = 0;             /**< Trenutan broj zapisa u nizu \ref iznajmljivanja. */

/* Rad sa fajlovima */
void ucitajAutomobile(void);
void sacuvajAutomobile(void);
void ucitajIznajmljivanja(void);
void sacuvajIznajmljivanja(void);
RentStatus parsirajAutomobil(const char* linija, Automobil* automobil);
RentStatus parsirajIznajmljivanje(const char* linija, Iznajmljivanje* iznajmljivanje);

/* Pomocne funkcije */
int  sledeciIdAutomobila(void);
int  sledeciIdIznajmljivanja(void);
int  pronadjiAutomobilPoId(int id);
int  pronadjiAktivnoIznajmljivanjeZaAuto(const Iznajmljivanje niz[], int brojElemenata, int idAutomobila);
void ocistiUlazniBafer(void);

/* Ciste (pure) funkcije - poslovna logika bez I/O i bez globalnog stanja, lako testabilne */
float       izracunajUkupnuCijenu(int brojDana, float cijenaPoDanu);
int         jeAutomobilDostupan(const Automobil* automobil);
int         jeBrojDanaValidan(int brojDana);
int         jeGodisteValidno(int godiste);
int         jeCijenaValidna(float cijena);
const char* formatirajStatusAutomobila(int dostupan);
const char* opisStatusa(RentStatus status);

RentStatus validirajAutomobil(const Automobil* automobil);
RentStatus kreirajAutomobil(Automobil* noviAutomobil, int id, const char* marka, const char* model,
    int godiste, float cijenaPoDanu);
RentStatus validirajBrisanjeAutomobila(const Automobil* automobil);
RentStatus obrisiAutomobilNaIndeksu(Automobil niz[], int* brojElemenata, int indeks);
RentStatus pripremiIznajmljivanje(Iznajmljivanje* iznajmljivanje, int id, int idAutomobila, float cijenaPoDanu,
    const char* ime, const char* prezime, const char* datumPocetka, const char* datumKraja, int brojDana);
RentStatus obradiVracanjeAutomobila(Automobil* automobil, Iznajmljivanje* iznajmljivanje);

/* Funkcionalnosti menija */
void dodajAutomobil(void);
void prikaziAutomobile(void);
void obrisiAutomobil(void);
void iznajmiAutomobil(void);
void vratiAutomobil(void);
void prikaziIznajmljivanja(void);
void prikaziMeni(void);

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

    /* Ucitaj postojece podatke iz fajlova (ako fajlovi ne postoje, pocinje se prazno) */
    ucitajAutomobile();
    ucitajIznajmljivanja();

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
            dodajAutomobil();
            break;
        case 2:
            prikaziAutomobile();
            break;
        case 3:
            obrisiAutomobil();
            break;
        case 4:
            iznajmiAutomobil();
            break;
        case 5:
            vratiAutomobil();
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

/***********************************************************************************************************************
 * Prikaz menija
 **********************************************************************************************************************/

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

/***********************************************************************************************************************
 * Pomocne funkcije
 **********************************************************************************************************************/

 /**
  * \brief Prazni ulazni bafer nakon poziva funkcije scanf.
  *
  * Cita i odbacuje sve karaktere iz standardnog ulaza sve dok ne naidje na
  * znak novog reda ili kraj ulaza. Poziva se nakon svakog scanf poziva kako
  * bi naredni unos korisnika bio ispravno procitan.
  */
void ocistiUlazniBafer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* namerno prazno telo petlje */
    }
}

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
 * \return \ref RENT_NULL_POINTER ako je neki od pokazivaca NULL,
 *         \ref RENT_INVALID_YEAR / \ref RENT_INVALID_PRICE ako podaci nisu validni,
 *         inace \ref RENT_OK (automobil je popunjen i oznacen kao dostupan).
 */
RentStatus kreirajAutomobil(Automobil* noviAutomobil, int id, const char* marka, const char* model,
    int godiste, float cijenaPoDanu)
{
    RentStatus status;

    if (noviAutomobil == NULL || marka == NULL || model == NULL)
    {
        return RENT_NULL_POINTER;
    }

    noviAutomobil->id = id;

    strncpy(noviAutomobil->marka, marka, DUZINA_STRINGA - 1);
    noviAutomobil->marka[DUZINA_STRINGA - 1] = '\0';

    strncpy(noviAutomobil->model, model, DUZINA_STRINGA - 1);
    noviAutomobil->model[DUZINA_STRINGA - 1] = '\0';

    noviAutomobil->godiste = godiste;
    noviAutomobil->cijena_po_danu = cijenaPoDanu;
    noviAutomobil->dostupan = 1; /* novi automobil je odmah dostupan, ako prodje validaciju */

    status = validirajAutomobil(noviAutomobil);
    return status;
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

/**
 * \brief Ucitava sve automobile iz fajla \ref CARS_FILE u niz \ref automobili.
 *
 * Citanje fajla je odvojeno od parsiranja linija - za samo parsiranje se
 * koristi \ref parsirajAutomobil. Ako fajl ne postoji, funkcija tiho
 * zavrsava rad i program nastavlja sa praznom listom automobila - ovo je
 * ocekivano ponasanje pri prvom pokretanju programa.
 */
void ucitajAutomobile(void)
{
    FILE* fp;
    char linija[256];

    brojAutomobila = 0;

    fp = fopen(CARS_FILE, "r");
    if (fp == NULL)
    {
        /* Fajl jos ne postoji - to je u redu, pocinjemo sa praznom listom */
        return;
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
}

/**
 * \brief Cuva sve automobile iz niza \ref automobili u fajl \ref CARS_FILE.
 *
 * Postojeci sadrzaj fajla se u potpunosti zamjenjuje trenutnim stanjem
 * niza \ref automobili. Poziva se nakon svake izmene (dodavanje, brisanje,
 * promena statusa) kako bi podaci ostali trajno sacuvani.
 */
void sacuvajAutomobile(void)
{
    FILE* fp;
    int i;

    fp = fopen(CARS_FILE, "w");
    if (fp == NULL)
    {
        printf("\n%s (%s)\n\n", opisStatusa(RENT_FILE_ERROR), CARS_FILE);
        return;
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
}

/**
 * \brief Ucitava sve zapise o iznajmljivanju iz fajla \ref RENTALS_FILE.
 *
 * Citanje fajla je odvojeno od parsiranja linija - za samo parsiranje se
 * koristi \ref parsirajIznajmljivanje. Ako fajl ne postoji, funkcija tiho
 * zavrsava rad i program nastavlja sa praznom listom iznajmljivanja.
 */
void ucitajIznajmljivanja(void)
{
    FILE* fp;
    char linija[256];

    brojIznajmljivanja = 0;

    fp = fopen(RENTALS_FILE, "r");
    if (fp == NULL)
    {
        return;
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
}

/**
 * \brief Cuva sve zapise o iznajmljivanju u fajl \ref RENTALS_FILE.
 *
 * Postojeci sadrzaj fajla se u potpunosti zamjenjuje trenutnim stanjem
 * niza \ref iznajmljivanja.
 */
void sacuvajIznajmljivanja(void)
{
    FILE* fp;
    int i;

    fp = fopen(RENTALS_FILE, "w");
    if (fp == NULL)
    {
        printf("\n%s (%s)\n\n", opisStatusa(RENT_FILE_ERROR), RENTALS_FILE);
        return;
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
}

/**
 * \brief Ucitava podatke o novom automobilu sa standardnog ulaza i dodaje
 *        ga u sistem.
 *
 * Funkcija samo cita unos sa standardnog ulaza i prosledjuje ga funkciji
 * \ref kreirajAutomobil, koja obavlja svu validaciju i popunjava strukturu.
 */
void dodajAutomobil(void)
{
    Automobil noviAuto;
    char marka[DUZINA_STRINGA];
    char model[DUZINA_STRINGA];
    int godiste;
    float cijenaPoDanu;
    RentStatus status;

    if (brojAutomobila >= MAX_AUTOMOBILA)
    {
        printf("\nDostignut je maksimalan broj automobila (%d).\n\n", MAX_AUTOMOBILA);
        return;
    }

    printf("\n--- Dodavanje novog automobila ---\n");

    printf("Marka: ");
    scanf("%29s", marka);

    printf("Model: ");
    scanf("%29s", model);

    printf("Godiste: ");
    scanf("%d", &godiste);

    printf("Cijena po danu (KM): ");
    scanf("%f", &cijenaPoDanu);

    ocistiUlazniBafer();

    status = kreirajAutomobil(&noviAuto, sledeciIdAutomobila(), marka, model, godiste, cijenaPoDanu);

    if (status != RENT_OK)
    {
        printf("\n%s Automobil nije dodat.\n\n", opisStatusa(status));
        return;
    }

    automobili[brojAutomobila] = noviAuto;
    brojAutomobila++;

    sacuvajAutomobile();

    printf("\nAutomobil je uspjesno dodat! (ID: %d)\n\n", noviAuto.id);
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
 * \brief Brise automobil na osnovu ID-a koji unese korisnik.
 *
 * Funkcija cita ID, pronalazi automobil, a validaciju da li automobil
 * smije biti obrisan prepusta \ref validirajBrisanjeAutomobila. Samo
 * uklanjanje elementa iz niza obavlja \ref obrisiAutomobilNaIndeksu.
 */
void obrisiAutomobil(void)
{
    int id, indeks;
    RentStatus status;

    printf("\n--- Brisanje automobila ---\n");
    printf("Unesite ID automobila koji zelite obrisati: ");
    scanf("%d", &id);
    ocistiUlazniBafer();

    indeks = pronadjiAutomobilPoId(id);

    if (indeks == -1)
    {
        printf("\n%s (ID %d)\n\n", opisStatusa(RENT_CAR_NOT_FOUND), id);
        return;
    }

    status = validirajBrisanjeAutomobila(&automobili[indeks]);
    if (status != RENT_OK)
    {
        printf("\n%s\n\n", opisStatusa(status));
        return;
    }

    obrisiAutomobilNaIndeksu(automobili, &brojAutomobila, indeks);

    sacuvajAutomobile();

    printf("\nAutomobil je uspjesno obrisan.\n\n");
}

/**
 * \brief Iznajmljuje odabrani automobil na osnovu podataka koje unese korisnik.
 *
 * Funkcija cita unos (ID automobila, podatke o klijentu, datume, broj dana)
 * i prosledjuje ga funkciji \ref pripremiIznajmljivanje, koja obavlja svu
 * validaciju, racunanje ukupne cijene i popunjavanje strukture. Ovdje
 * ostaje samo provjera postojanja/dostupnosti automobila i I/O.
 */
void iznajmiAutomobil(void)
{
    int id, indeks;
    char ime[DUZINA_IMENA];
    char prezime[DUZINA_IMENA];
    char datumPocetka[DUZINA_DATUMA];
    char datumKraja[DUZINA_DATUMA];
    int brojDana;
    Iznajmljivanje novoIznajmljivanje;
    RentStatus status;

    if (brojIznajmljivanja >= MAX_IZNAJMLJIVANJA)
    {
        printf("\n%s\n\n", opisStatusa(RENT_LIMIT_REACHED));
        return;
    }

    printf("\n--- Iznajmljivanje automobila ---\n");

    prikaziAutomobile();

    printf("Unesite ID automobila koji zelite iznajmiti: ");
    scanf("%d", &id);
    ocistiUlazniBafer();

    indeks = pronadjiAutomobilPoId(id);

    if (indeks == -1)
    {
        printf("\n%s (ID %d)\n\n", opisStatusa(RENT_CAR_NOT_FOUND), id);
        return;
    }

    if (!jeAutomobilDostupan(&automobili[indeks]))
    {
        printf("\n%s\n\n", opisStatusa(RENT_CAR_NOT_AVAILABLE));
        return;
    }

    printf("Ime klijenta: ");
    scanf("%49s", ime);

    printf("Prezime klijenta: ");
    scanf("%49s", prezime);

    printf("Datum pocetka (DD-MM-GGGG): ");
    scanf("%10s", datumPocetka);

    printf("Datum kraja (DD-MM-GGGG): ");
    scanf("%10s", datumKraja);

    printf("Broj dana iznajmljivanja: ");
    scanf("%d", &brojDana);

    ocistiUlazniBafer();

    status = pripremiIznajmljivanje(&novoIznajmljivanje, sledeciIdIznajmljivanja(), id,
        automobili[indeks].cijena_po_danu, ime, prezime, datumPocetka, datumKraja, brojDana);

    if (status != RENT_OK)
    {
        printf("\n%s Iznajmljivanje otkazano.\n\n", opisStatusa(status));
        return;
    }

    iznajmljivanja[brojIznajmljivanja] = novoIznajmljivanje;
    brojIznajmljivanja++;

    /* Oznaci automobil kao iznajmljen */
    automobili[indeks].dostupan = 0;

    sacuvajIznajmljivanja();
    sacuvajAutomobile();

    printf("\nAutomobil je uspjesno iznajmljen!\n");
    printf("Ukupna cijena: %.2f KM\n\n", novoIznajmljivanje.ukupna_cijena);
}

/**
 *\brief Vraca iznajmljeni automobil na osnovu ID-a koji unese korisnik.
 *
 * Funkcija pronalazi automobil i (preko \ref pronadjiAktivnoIznajmljivanjeZaAuto)
 * njegov aktivan zapis o iznajmljivanju, a svu logiku azuriranja statusa
 * prepusta \ref obradiVracanjeAutomobila. Ovdje ostaje samo I/O i ispis
 * odgovarajuce poruke na osnovu vracenog statusa.
 */
void vratiAutomobil(void)
{
    int idAuta, indeksAuta, indeksIznajmljivanja;
    Iznajmljivanje* iznajmljivanjePok;
    RentStatus status;

    printf("\n--- Vracanje automobila ---\n");
    printf("Unesite ID automobila koji se vraca: ");
    scanf("%d", &idAuta);
    ocistiUlazniBafer();

    indeksAuta = pronadjiAutomobilPoId(idAuta);

    if (indeksAuta == -1)
    {
        printf("\n%s (ID %d)\n\n", opisStatusa(RENT_CAR_NOT_FOUND), idAuta);
        return;
    }

    indeksIznajmljivanja = pronadjiAktivnoIznajmljivanjeZaAuto(iznajmljivanja, brojIznajmljivanja, idAuta);
    iznajmljivanjePok = (indeksIznajmljivanja != -1) ? &iznajmljivanja[indeksIznajmljivanja] : NULL;

    status = obradiVracanjeAutomobila(&automobili[indeksAuta], iznajmljivanjePok);

    if (status == RENT_CAR_ALREADY_AVAILABLE)
    {
        printf("\n%s\n\n", opisStatusa(status));
        return;
    }

    if (status == RENT_RENTAL_NOT_FOUND)
    {
        printf("\nUPOZORENJE: %s\n", opisStatusa(status));
        printf("Status automobila ce ipak biti azuriran na 'Dostupan'.\n\n");
    }

    sacuvajAutomobile();
    sacuvajIznajmljivanja();

    printf("\nAutomobil je uspjesno vracen.\n\n");
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