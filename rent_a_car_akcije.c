/**
 * \file rent_a_car_akcije.c
 *
 * \brief Akcije glavnog menija rent-a-car sistema.
 *
 * Funkcije citaju unos korisnika sa standardnog ulaza, ispisuju poruke na
 * standardni izlaz i mijenjaju globalno stanje. Svu validaciju i racunanje
 * prepustaju poslovnoj logici iz rent_a_car_logic.c. Putanje fajlova se
 * prosledjuju kao parametri, kako testovi ne bi mijenjali stvarne podatke.
 */

#include <stdio.h>
#include "rent_a_car_logic.h"
#include "rent_a_car_stanje.h"
#include "rent_a_car_prikaz.h"
#include "rent_a_car_fajlovi.h"
#include "rent_a_car_akcije.h"

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
 * \brief Ucitava podatke o novom automobilu sa standardnog ulaza i dodaje
 *        ga u sistem.
 *
 * Funkcija samo cita unos sa standardnog ulaza i prosledjuje ga funkciji
 * \ref kreirajAutomobil, koja obavlja svu validaciju i popunjava strukturu.
 *
 * Povratna vrijednost svakog poziva scanf se provjerava. Ako unos nije
 * validan (npr. slova umjesto broja) ili je dostignut kraj ulaza, ispisuje
 * se poruka, preostali unos se odbacuje i funkcija se zavrsava bez izmjena.
 *
 * \param [in] fajlAutomobila Putanja do fajla u koji se cuvaju automobili.
 */
void dodajAutomobil(const char* fajlAutomobila)
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
    if (scanf("%29s", marka) != 1)
    {
        printf("\nNevalidan unos. Automobil nije dodat.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Model: ");
    if (scanf("%29s", model) != 1)
    {
        printf("\nNevalidan unos. Automobil nije dodat.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Godiste: ");
    if (scanf("%d", &godiste) != 1)
    {
        printf("\nNevalidan unos. Automobil nije dodat.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Cijena po danu (KM): ");
    if (scanf("%f", &cijenaPoDanu) != 1)
    {
        printf("\nNevalidan unos. Automobil nije dodat.\n\n");
        ocistiUlazniBafer();
        return;
    }

    ocistiUlazniBafer();

    status = kreirajAutomobil(&noviAuto, sledeciIdAutomobila(), marka, model, godiste, cijenaPoDanu);

    if (status != RENT_OK)
    {
        printf("\n%s Automobil nije dodat.\n\n", opisStatusa(status));
        return;
    }

    automobili[brojAutomobila] = noviAuto;
    brojAutomobila++;

    (void)sacuvajAutomobile(fajlAutomobila);

    printf("\nAutomobil je uspjesno dodat! (ID: %d)\n\n", noviAuto.id);
}

/**
 * \brief Brise automobil na osnovu ID-a koji unese korisnik.
 *
 * Funkcija cita ID, pronalazi automobil, a validaciju da li automobil
 * smije biti obrisan prepusta \ref validirajBrisanjeAutomobila. Samo
 * uklanjanje elementa iz niza obavlja \ref obrisiAutomobilNaIndeksu.
 *
 * Povratna vrijednost svakog poziva scanf se provjerava. Ako unos nije
 * validan (npr. slova umjesto broja) ili je dostignut kraj ulaza, ispisuje
 * se poruka, preostali unos se odbacuje i funkcija se zavrsava bez izmjena.
 *
 * \param [in] fajlAutomobila Putanja do fajla u koji se cuvaju automobili.
 */
void obrisiAutomobil(const char* fajlAutomobila)
{
    int id, indeks;
    RentStatus status;

    printf("\n--- Brisanje automobila ---\n");
    printf("Unesite ID automobila koji zelite obrisati: ");
    if (scanf("%d", &id) != 1)
    {
        printf("\nNevalidan unos. Automobil nije obrisan.\n\n");
        ocistiUlazniBafer();
        return;
    }
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

    (void)sacuvajAutomobile(fajlAutomobila);

    printf("\nAutomobil je uspjesno obrisan.\n\n");
}

/**
 * \brief Iznajmljuje odabrani automobil na osnovu podataka koje unese korisnik.
 *
 * Funkcija cita unos (ID automobila, podatke o klijentu, datume, broj dana)
 * i prosledjuje ga funkciji \ref pripremiIznajmljivanje, koja obavlja svu
 * validaciju, racunanje ukupne cijene i popunjavanje strukture. Ovdje
 * ostaje samo provjera postojanja/dostupnosti automobila i I/O.
 *
 * Povratna vrijednost svakog poziva scanf se provjerava. Ako unos nije
 * validan (npr. slova umjesto broja) ili je dostignut kraj ulaza, ispisuje
 * se poruka, preostali unos se odbacuje i funkcija se zavrsava bez izmjena.
 *
 * \param [in] fajlAutomobila Putanja do fajla u koji se cuvaju automobili.
 * \param [in] fajlIznajmljivanja Putanja do fajla u koji se cuvaju iznajmljivanja.
 */
void iznajmiAutomobil(const char* fajlAutomobila, const char* fajlIznajmljivanja)
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
    if (scanf("%d", &id) != 1)
    {
        printf("\nNevalidan unos. Iznajmljivanje otkazano.\n\n");
        ocistiUlazniBafer();
        return;
    }
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
    if (scanf("%49s", ime) != 1)
    {
        printf("\nNevalidan unos. Iznajmljivanje otkazano.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Prezime klijenta: ");
    if (scanf("%49s", prezime) != 1)
    {
        printf("\nNevalidan unos. Iznajmljivanje otkazano.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Datum pocetka (DD-MM-GGGG): ");
    if (scanf("%10s", datumPocetka) != 1)
    {
        printf("\nNevalidan unos. Iznajmljivanje otkazano.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Datum kraja (DD-MM-GGGG): ");
    if (scanf("%10s", datumKraja) != 1)
    {
        printf("\nNevalidan unos. Iznajmljivanje otkazano.\n\n");
        ocistiUlazniBafer();
        return;
    }

    printf("Broj dana iznajmljivanja: ");
    if (scanf("%d", &brojDana) != 1)
    {
        printf("\nNevalidan unos. Iznajmljivanje otkazano.\n\n");
        ocistiUlazniBafer();
        return;
    }

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

    (void)sacuvajIznajmljivanja(fajlIznajmljivanja);
    (void)sacuvajAutomobile(fajlAutomobila);

    printf("\nAutomobil je uspjesno iznajmljen!\n");
    printf("Ukupna cijena: %.2f KM\n\n", novoIznajmljivanje.ukupna_cijena);
}

/**
 * \brief Vraca iznajmljeni automobil na osnovu ID-a koji unese korisnik.
 *
 * Funkcija pronalazi automobil i (preko \ref pronadjiAktivnoIznajmljivanjeZaAuto)
 * njegov aktivan zapis o iznajmljivanju, a svu logiku azuriranja statusa
 * prepusta \ref obradiVracanjeAutomobila. Ovdje ostaje samo I/O i ispis
 * odgovarajuce poruke na osnovu vracenog statusa.
 *
 * Povratna vrijednost svakog poziva scanf se provjerava. Ako unos nije
 * validan (npr. slova umjesto broja) ili je dostignut kraj ulaza, ispisuje
 * se poruka, preostali unos se odbacuje i funkcija se zavrsava bez izmjena.
 *
 * \param [in] fajlAutomobila Putanja do fajla u koji se cuvaju automobili.
 * \param [in] fajlIznajmljivanja Putanja do fajla u koji se cuvaju iznajmljivanja.
 */
void vratiAutomobil(const char* fajlAutomobila, const char* fajlIznajmljivanja)
{
    int idAuta, indeksAuta, indeksIznajmljivanja;
    Iznajmljivanje* iznajmljivanjePok;
    RentStatus status;

    printf("\n--- Vracanje automobila ---\n");
    printf("Unesite ID automobila koji se vraca: ");
    if (scanf("%d", &idAuta) != 1)
    {
        printf("\nNevalidan unos. Automobil nije vracen.\n\n");
        ocistiUlazniBafer();
        return;
    }
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

    (void)sacuvajAutomobile(fajlAutomobila);
    (void)sacuvajIznajmljivanja(fajlIznajmljivanja);

    printf("\nAutomobil je uspjesno vracen.\n\n");
}
