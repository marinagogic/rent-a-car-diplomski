/**
 * \file main.c
 *
 * \brief Konzolna aplikacija za upravljanje rent-a-car sistemom.
 *
 * Aplikacija omogucava dodavanje, brisanje, iznajmljivanje i vracanje
 * automobila, kao i pregled istorije iznajmljivanja.
 *
 * Ovaj fajl sadrzi samo meni, ulazno/izlazne operacije, globalno stanje i
 * rad sa fajlovima. Sva poslovna logika (validacija, racunanje, parsiranje)
 * nalazi se u rent_a_car_logic.h / rent_a_car_logic.c i moze se testirati
 * nezavisno od ovog fajla.
 */

#include <stdio.h>
#include <stdlib.h>
#include "rent_a_car_logic.h"

#define MAX_AUTOMOBILA      100   /**< Maksimalan broj automobila koji se moze cuvati u memoriji. */
#define MAX_IZNAJMLJIVANJA  200   /**< Maksimalan broj zapisa o iznajmljivanju koji se moze cuvati u memoriji. */

#define CARS_FILE     "cars.txt"     /**< Naziv fajla u kojem se cuvaju podaci o automobilima. */
#define RENTALS_FILE  "rentals.txt"  /**< Naziv fajla u kojem se cuvaju podaci o iznajmljivanjima. */

Automobil       automobili[MAX_AUTOMOBILA];        /**< Niz svih automobila trenutno ucitanih u memoriju. */
int             brojAutomobila = 0;                /**< Trenutan broj automobila u nizu \ref automobili. */

Iznajmljivanje  iznajmljivanja[MAX_IZNAJMLJIVANJA]; /**< Niz svih zapisa o iznajmljivanju ucitanih u memoriju. */
int             brojIznajmljivanja = 0;             /**< Trenutan broj zapisa u nizu \ref iznajmljivanja. */

/* Rad sa fajlovima */
void ucitajAutomobile(void);
void sacuvajAutomobile(void);
void ucitajIznajmljivanja(void);
void sacuvajIznajmljivanja(void);

/* Pomocne funkcije koje zavise od globalnog stanja */
int  sledeciIdAutomobila(void);
int  sledeciIdIznajmljivanja(void);
int  pronadjiAutomobilPoId(int id);
void ocistiUlazniBafer(void);

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