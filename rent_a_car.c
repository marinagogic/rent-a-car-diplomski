/**
 * \file rent_a_car.c
 *
 * \brief Konzolna aplikacija za upravljanje rent-a-car sistemom.
 *
 * Aplikacija omogucava dodavanje, brisanje, iznajmljivanje i vracanje
 * automobila, kao i pregled istorije iznajmljivanja.
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

Automobil       automobili[MAX_AUTOMOBILA];        /**< Niz svih automobila trenutno ucitanih u memoriju. */
int             brojAutomobila = 0;                /**< Trenutan broj automobila u nizu \ref automobili. */

Iznajmljivanje  iznajmljivanja[MAX_IZNAJMLJIVANJA]; /**< Niz svih zapisa o iznajmljivanju ucitanih u memoriju. */
int             brojIznajmljivanja = 0;             /**< Trenutan broj zapisa u nizu \ref iznajmljivanja. */

 /* Rad sa fajlovima */
void ucitajAutomobile(void);
void sacuvajAutomobile(void);
void ucitajIznajmljivanja(void);
void sacuvajIznajmljivanja(void);

/* Pomocne funkcije */
int  sledeciIdAutomobila(void);
int  sledeciIdIznajmljivanja(void);
int  pronadjiAutomobilPoId(int id);
void ocistiUlazniBafer(void);

/* Ciste (pure) funkcije */
float       izracunajUkupnuCijenu(int brojDana, float cijenaPoDanu);
int         jeAutomobilDostupan(const Automobil* automobil);
int         jeBrojDanaValidan(int brojDana);
int         jeGodisteValidno(int godiste);
int         jeCijenaValidna(float cijena);
const char* formatirajStatusAutomobila(int dostupan);

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
  * \brief Racuna ukupnu cijenu iznajmljivanja.
  *
  * Funkcija nema nikakvih zavisnosti od globalnog stanja programa niti od
  * ulazno/izlaznih operacija, sto je cini direktno testabilnom.
  *
  * \param [in] brojDana      Broj dana iznajmljivanja.
  * \param [in] cijenaPoDanu  Cijena iznajmljivanja po danu, u KM.
  *
  * \return Ukupna cijena iznajmljivanja (brojDana * cijenaPoDanu).
  */
float izracunajUkupnuCijenu(int brojDana, float cijenaPoDanu)
{
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
 * \return 1 ako je brojDana veci od nule, inace 0.
 */
int jeBrojDanaValidan(int brojDana)
{
    return (brojDana > 0);
}

/**
 * \brief Provjerava da li je godiste automobila u dozvoljenom opsegu.
 *
 * \param [in] godiste Godiste koje se provjerava.
 *
 * \return 1 ako je godiste izmedju 1950 i 2100 (ukljucivo), inace 0.
 */
int jeGodisteValidno(int godiste)
{
    return (godiste >= 1950 && godiste <= 2100);
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
  * \brief Ucitava sve automobile iz fajla \ref CARS_FILE u niz \ref automobili.
  *
  * Format jedne linije u fajlu je:
  * `id;marka;model;godiste;cijena_po_danu;dostupan`
  *
  * Ako fajl ne postoji, funkcija tiho zavrsava rad i program nastavlja sa
  * praznom listom automobila - ovo je ocekivano ponasanje pri prvom
  * pokretanju programa.
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

        int uneseno = sscanf(linija, "%d;%29[^;];%29[^;];%d;%f;%d",
            &a.id,
            a.marka,
            a.model,
            &a.godiste,
            &a.cijena_po_danu,
            &a.dostupan);

        if (uneseno == 6)
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
        printf("\nGRESKA: Ne mogu da otvorim %s za pisanje!\n\n", CARS_FILE);
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
  * Format jedne linije u fajlu je:
  * `id;id_automobila;ime;prezime;datum_pocetka;datum_kraja;broj_dana;ukupna_cijena;aktivno`
  *
  * Ako fajl ne postoji, funkcija tiho zavrsava rad i program nastavlja sa
  * praznom listom iznajmljivanja.
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

        int uneseno = sscanf(linija, "%d;%d;%49[^;];%49[^;];%10[^;];%10[^;];%d;%f;%d",
            &r.id,
            &r.id_automobila,
            r.ime,
            r.prezime,
            r.datum_pocetka,
            r.datum_kraja,
            &r.broj_dana,
            &r.ukupna_cijena,
            &r.aktivno);

        if (uneseno == 9)
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
        printf("\nGRESKA: Ne mogu da otvorim %s za pisanje!\n\n", RENTALS_FILE);
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
  * Funkcija trazi od korisnika marku, model, godiste i cijenu po danu.
  * Novi automobil dobija ID preko funkcije \ref sledeciIdAutomobila i
  * podrazumevano se oznacava kao dostupan. Godiste i cijena se validiraju
  * pomocu funkcija \ref jeGodisteValidno i \ref jeCijenaValidna - ako neka
  * od provjera ne prodje, automobil se ne dodaje. Nakon uspesnog dodavanja,
  * stanje se cuva u fajl pozivom funkcije \ref sacuvajAutomobile.
  */
void dodajAutomobil(void)
{
    Automobil noviAuto;

    if (brojAutomobila >= MAX_AUTOMOBILA)
    {
        printf("\nDostignut je maksimalan broj automobila (%d).\n\n", MAX_AUTOMOBILA);
        return;
    }

    noviAuto.id = sledeciIdAutomobila();

    printf("\n--- Dodavanje novog automobila ---\n");

    printf("Marka: ");
    scanf("%29s", noviAuto.marka);

    printf("Model: ");
    scanf("%29s", noviAuto.model);

    printf("Godiste: ");
    scanf("%d", &noviAuto.godiste);

    printf("Cijena po danu (KM): ");
    scanf("%f", &noviAuto.cijena_po_danu);

    ocistiUlazniBafer();

    if (!jeGodisteValidno(noviAuto.godiste))
    {
        printf("\nGodiste nije u dozvoljenom opsegu (1950-2100). Automobil nije dodat.\n\n");
        return;
    }

    if (!jeCijenaValidna(noviAuto.cijena_po_danu))
    {
        printf("\nCijena po danu mora biti veca od nule. Automobil nije dodat.\n\n");
        return;
    }

    noviAuto.dostupan = 1; /* novi automobil je odmah dostupan */

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
  * Automobil se moze obrisati samo ako trenutno nije iznajmljen (provjera
  * preko funkcije \ref jeAutomobilDostupan). Nakon brisanja, svi naredni
  * elementi u nizu \ref automobili se pomjeraju za jedno mjesto ulijevo,
  * a novo stanje se cuva pozivom funkcije \ref sacuvajAutomobile.
  */
void obrisiAutomobil(void)
{
    int id, indeks, i;

    printf("\n--- Brisanje automobila ---\n");
    printf("Unesite ID automobila koji zelite obrisati: ");
    scanf("%d", &id);
    ocistiUlazniBafer();

    indeks = pronadjiAutomobilPoId(id);

    if (indeks == -1)
    {
        printf("\nAutomobil sa ID %d ne postoji.\n\n", id);
        return;
    }

    if (!jeAutomobilDostupan(&automobili[indeks]))
    {
        printf("\nAutomobil je trenutno iznajmljen i ne moze biti obrisan.\n\n");
        return;
    }

    /* Pomjeri sve elemente iza obrisanog automobila za jedno mjesto ulijevo */
    for (i = indeks; i < brojAutomobila - 1; i++)
    {
        automobili[i] = automobili[i + 1];
    }
    brojAutomobila--;

    sacuvajAutomobile();

    printf("\nAutomobil je uspjesno obrisan.\n\n");
}

 /**
  * \brief Iznajmljuje odabrani automobil na osnovu podataka koje unese korisnik.
  *
  * Funkcija prvo prikazuje listu automobila, zatim trazi ID automobila,
  * podatke o klijentu, datume i broj dana iznajmljivanja. Broj dana se
  * validira preko funkcije \ref jeBrojDanaValidan, a ukupna cijena se
  * racuna preko funkcije \ref izracunajUkupnuCijenu. Ako je automobil vec
  * iznajmljen (provjera preko \ref jeAutomobilDostupan), iznajmljivanje se
  * odbija. Nakon uspesnog iznajmljivanja, i lista automobila i lista
  * iznajmljivanja se cuvaju u odgovarajuce fajlove.
  */
void iznajmiAutomobil(void)
{
    int id, indeks;
    Iznajmljivanje novoIznajmljivanje;

    if (brojIznajmljivanja >= MAX_IZNAJMLJIVANJA)
    {
        printf("\nDostignut je maksimalan broj iznajmljivanja.\n\n");
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
        printf("\nAutomobil sa ID %d ne postoji.\n\n", id);
        return;
    }

    if (!jeAutomobilDostupan(&automobili[indeks]))
    {
        printf("\nAutomobil je vec iznajmljen.\n\n");
        return;
    }

    novoIznajmljivanje.id = sledeciIdIznajmljivanja();
    novoIznajmljivanje.id_automobila = id;

    printf("Ime klijenta: ");
    scanf("%49s", novoIznajmljivanje.ime);

    printf("Prezime klijenta: ");
    scanf("%49s", novoIznajmljivanje.prezime);

    printf("Datum pocetka (DD-MM-GGGG): ");
    scanf("%10s", novoIznajmljivanje.datum_pocetka);

    printf("Datum kraja (DD-MM-GGGG): ");
    scanf("%10s", novoIznajmljivanje.datum_kraja);

    printf("Broj dana iznajmljivanja: ");
    scanf("%d", &novoIznajmljivanje.broj_dana);

    ocistiUlazniBafer();

    if (!jeBrojDanaValidan(novoIznajmljivanje.broj_dana))
    {
        printf("\nBroj dana mora biti veci od nule. Iznajmljivanje otkazano.\n\n");
        return;
    }

    novoIznajmljivanje.ukupna_cijena =
        izracunajUkupnuCijenu(novoIznajmljivanje.broj_dana, automobili[indeks].cijena_po_danu);
    novoIznajmljivanje.aktivno = 1;

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
  * Funkcija pronalazi aktivan zapis o iznajmljivanju za dati automobil
  * (polje \e aktivno postavljeno na 1) i oznacava ga kao zavrsen. Status
  * automobila se azurira na "dostupan" bez obzira na to da li je aktivan
  * zapis pronadjen, uz odgovarajuce upozorenje ako zapis nije nadjen -
  * ovo je zastitna mjera protiv nekonzistentnog stanja podataka.
  */
void vratiAutomobil(void)
{
    int idAuta, indeksAuta, i, pronadjeno;

    printf("\n--- Vracanje automobila ---\n");
    printf("Unesite ID automobila koji se vraca: ");
    scanf("%d", &idAuta);
    ocistiUlazniBafer();

    indeksAuta = pronadjiAutomobilPoId(idAuta);

    if (indeksAuta == -1)
    {
        printf("\nAutomobil sa ID %d ne postoji.\n\n", idAuta);
        return;
    }

    if (jeAutomobilDostupan(&automobili[indeksAuta]))
    {
        printf("\nOvaj automobil trenutno nije iznajmljen.\n\n");
        return;
    }

    /* Pronadji aktivan zapis iznajmljivanja za ovaj automobil */
    pronadjeno = 0;
    for (i = 0; i < brojIznajmljivanja; i++)
    {
        if (iznajmljivanja[i].id_automobila == idAuta && iznajmljivanja[i].aktivno == 1)
        {
            iznajmljivanja[i].aktivno = 0;
            pronadjeno = 1;
            break;
        }
    }

    if (!pronadjeno)
    {
        printf("\nUPOZORENJE: Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil.\n");
        printf("Status automobila ce ipak biti azuriran na 'Dostupan'.\n\n");
    }

    automobili[indeksAuta].dostupan = 1;

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
