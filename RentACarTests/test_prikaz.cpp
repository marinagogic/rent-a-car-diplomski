/**
 * \file test_prikaz.cpp
 *
 * \brief Google Test jedinicni testovi za funkcije ispisa rent-a-car sistema
 *        (rent_a_car_prikaz.h/.c).
 *
 * Funkcije koje se testiraju ne vracaju vrijednost, vec ispisuju tekst na
 * standardni izlaz. Zato se ispis "hvata" pomocu ugradjenih Google Test
 * funkcija testing::internal::CaptureStdout() i GetCapturedStdout(), koje
 * privremeno preusmjeravaju stdout u memoriju. Nakon toga se provjerava
 * sadrzaj uhvacenog teksta.
 */

 //#include "pch.h"
#include "gtest/gtest.h"
#include <string.h>
#include <string>

extern "C" {
#include "rent_a_car_stanje.h"
#include "rent_a_car_prikaz.h"
}

/**
 * \brief Provjerava da li ispis sadrzi dati tekst.
 *
 * Vraca AssertionResult kako bi Google Test, u slucaju neuspjeha, ispisao
 * i trazeni tekst i kompletan uhvaceni ispis.
 */
static ::testing::AssertionResult Sadrzi(const std::string& ispis, const std::string& tekst)
{
    if (ispis.find(tekst) != std::string::npos)
    {
        return ::testing::AssertionSuccess();
    }
    return ::testing::AssertionFailure()
        << "Ispis ne sadrzi \"" << tekst << "\".\nUhvaceni ispis:\n" << ispis;
}

/** \brief Broji koliko puta se tekst pojavljuje u ispisu. */
static int BrojPojavljivanja(const std::string& ispis, const std::string& tekst)
{
    int broj = 0;
    size_t pozicija = ispis.find(tekst);
    while (pozicija != std::string::npos)
    {
        broj++;
        pozicija = ispis.find(tekst, pozicija + tekst.length());
    }
    return broj;
}

/**
 * \brief Fixture klasa za testove ispisa.
 *
 * Prije i poslije svakog testa resetuje globalno stanje, a metodom
 * \ref uhvatiIspis poziva funkciju ispisa i vraca sve sto je ona ispisala.
 */
class Prikaz : public ::testing::Test
{
protected:
    void SetUp() override
    {
        resetujStanje();
    }

    void TearDown() override
    {
        resetujStanje();
    }

    static void resetujStanje()
    {
        memset(automobili, 0, sizeof(automobili));
        memset(iznajmljivanja, 0, sizeof(iznajmljivanja));
        brojAutomobila = 0;
        brojIznajmljivanja = 0;
    }

    /** Poziva funkciju ispisa i vraca kompletan tekst koji je ispisan na stdout. */
    static std::string uhvatiIspis(void (*funkcija)(void))
    {
        ::testing::internal::CaptureStdout();
        funkcija();
        return ::testing::internal::GetCapturedStdout();
    }

    static void dodajAuto(int id, const char* marka, const char* model,
        int godiste, float cijena, int dostupan)
    {
        Automobil* a = &automobili[brojAutomobila];
        a->id = id;
        strcpy(a->marka, marka);
        strcpy(a->model, model);
        a->godiste = godiste;
        a->cijena_po_danu = cijena;
        a->dostupan = dostupan;
        brojAutomobila++;
    }

    static void dodajIznajmljivanje(int id, int idAuta, const char* ime, const char* prezime,
        const char* pocetak, const char* kraj, int dani, float cijena, int aktivno)
    {
        Iznajmljivanje* r = &iznajmljivanja[brojIznajmljivanja];
        r->id = id;
        r->id_automobila = idAuta;
        strcpy(r->ime, ime);
        strcpy(r->prezime, prezime);
        strcpy(r->datum_pocetka, pocetak);
        strcpy(r->datum_kraja, kraj);
        r->broj_dana = dani;
        r->ukupna_cijena = cijena;
        r->aktivno = aktivno;
        brojIznajmljivanja++;
    }
};

/* ======================= prikaziMeni ======================= */

/**
 * \tracehead{PrikaziMeni_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziMeni" u pogledu ispisa naslova i svih opcija menija.
 *
 * \field{Specifikacija testa}
 * 1. Zapoceti hvatanje standardnog izlaza.
 * 2. Pozvati funkciju prikaziMeni.
 * 3. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi naslov "RENT A CAR SISTEM".
 * 2. Ispis sadrzi svih 7 opcija menija (1-6 i 0 za izlaz), svaku sa tacnim tekstom.
 * \endfield
 */
TEST_F(Prikaz, PrikaziMeni_SadrziNaslovISveOpcije)
{
    std::string ispis = uhvatiIspis(prikaziMeni);

    EXPECT_TRUE(Sadrzi(ispis, "RENT A CAR SISTEM"));
    EXPECT_TRUE(Sadrzi(ispis, " 1. Dodaj novi automobil\n"));
    EXPECT_TRUE(Sadrzi(ispis, " 2. Prikazi sve automobile\n"));
    EXPECT_TRUE(Sadrzi(ispis, " 3. Obrisi automobil\n"));
    EXPECT_TRUE(Sadrzi(ispis, " 4. Iznajmi automobil\n"));
    EXPECT_TRUE(Sadrzi(ispis, " 5. Vrati automobil\n"));
    EXPECT_TRUE(Sadrzi(ispis, " 6. Prikazi sva iznajmljivanja\n"));
    EXPECT_TRUE(Sadrzi(ispis, " 0. Izlaz\n"));
}

/**
 * \tracehead{PrikaziMeni_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziMeni" u pogledu strukture ispisa (broj linija i okvir menija).
 *
 * \field{Specifikacija testa}
 * 1. Zapoceti hvatanje standardnog izlaza.
 * 2. Pozvati funkciju prikaziMeni.
 * 3. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis ima tacno 11 linija (3 linije zaglavlja, 7 opcija, 1 zavrsna linija).
 * 2. Linija okvira "======================================" pojavljuje se tacno 3 puta.
 * \endfield
 */
TEST_F(Prikaz, PrikaziMeni_IspravnaStruktura)
{
    std::string ispis = uhvatiIspis(prikaziMeni);

    EXPECT_EQ(11, BrojPojavljivanja(ispis, "\n"));
    EXPECT_EQ(3, BrojPojavljivanja(ispis, "======================================\n"));
}

/* ======================= prikaziAutomobile ======================= */

/**
 * \tracehead{PrikaziAutomobile_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada nema unesenih automobila (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 0
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi poruku "Trenutno nema unesenih automobila.".
 * 2. Ispis ne sadrzi zaglavlje tabele (kolonu "Marka").
 * \endfield
 */
TEST_F(Prikaz, PrikaziAutomobile_PrazanNizIspisujePoruku)
{
    std::string ispis = uhvatiIspis(prikaziAutomobile);

    EXPECT_TRUE(Sadrzi(ispis, "Trenutno nema unesenih automobila."));
    EXPECT_EQ(std::string::npos, ispis.find("Marka"));
}

/**
 * \tracehead{PrikaziAutomobile_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada postoji jedan dostupan automobil (provjera tacnog formata reda tabele).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 1, marka = "Volkswagen", model = "Golf", godiste = 2020, cijena_po_danu = 45.5, dostupan = 1}
 *  * brojAutomobila = 1
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi zaglavlje tabele sa kolonama ID, Marka, Model, Godiste, Cijena/dan i Status.
 * 2. Ispis sadrzi red tabele tacno u formatu:
 *  * "1    Volkswagen      Golf            2020     45.50        Dostupan    "
 * 3. Ispis ne sadrzi poruku o praznoj listi.
 * \endfield
 */
TEST_F(Prikaz, PrikaziAutomobile_JedanAutomobilTacanFormatReda)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.5f, 1);

    std::string ispis = uhvatiIspis(prikaziAutomobile);

    EXPECT_TRUE(Sadrzi(ispis, "ID   Marka           Model           Godiste  Cijena/dan   Status"));
    EXPECT_TRUE(Sadrzi(ispis, "1    Volkswagen      Golf            2020     45.50        Dostupan    \n"));
    EXPECT_EQ(std::string::npos, ispis.find("Trenutno nema"));
}

/**
 * \tracehead{PrikaziAutomobile_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada je automobil iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 2, marka = "Skoda", model = "Octavia", godiste = 2019, cijena_po_danu = 60.0, dostupan = 0}
 *  * brojAutomobila = 1
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi status "Iznajmljen".
 * 2. Ispis ne sadrzi status "Dostupan".
 * \endfield
 */
TEST_F(Prikaz, PrikaziAutomobile_IznajmljenAutomobilIspisujeStatus)
{
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);

    std::string ispis = uhvatiIspis(prikaziAutomobile);

    EXPECT_TRUE(Sadrzi(ispis, "Iznajmljen"));
    EXPECT_EQ(std::string::npos, ispis.find("Dostupan"));
}

/**
 * \tracehead{PrikaziAutomobile_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada postoji vise automobila.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 3 automobila:
 *  * id = 1, "Volkswagen" "Golf", dostupan = 1
 *  * id = 2, "Skoda" "Octavia", dostupan = 0
 *  * id = 3, "Audi" "A4", dostupan = 1
 *  * brojAutomobila = 3
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi sve tri marke.
 * 2. Status "Dostupan" se pojavljuje tacno 2 puta, a "Iznajmljen" tacno 1 put.
 * 3. Automobili su ispisani redoslijedom kojim su u nizu (Volkswagen prije Skoda, Skoda prije Audi).
 * \endfield
 */
TEST_F(Prikaz, PrikaziAutomobile_ViseAutomobilaIspisujeSveRedom)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);
    dodajAuto(3, "Audi", "A4", 2021, 80.0f, 1);

    std::string ispis = uhvatiIspis(prikaziAutomobile);

    EXPECT_TRUE(Sadrzi(ispis, "Volkswagen"));
    EXPECT_TRUE(Sadrzi(ispis, "Skoda"));
    EXPECT_TRUE(Sadrzi(ispis, "Audi"));
    EXPECT_EQ(2, BrojPojavljivanja(ispis, "Dostupan"));
    EXPECT_EQ(1, BrojPojavljivanja(ispis, "Iznajmljen"));
    EXPECT_LT(ispis.find("Volkswagen"), ispis.find("Skoda"));
    EXPECT_LT(ispis.find("Skoda"), ispis.find("Audi"));
}

/**
 * \tracehead{PrikaziAutomobile_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada se iza posljednjeg validnog elementa nalazi zaostali (obrisani) automobil (analiza granicnih vrijednosti - element na indeksu brojAutomobila).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 1, marka = "Volkswagen", ...}
 *  * brojAutomobila = 1
 *  * automobili[1].marka = "Obrisani" (van opsega validnih elemenata)
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi "Volkswagen".
 * 2. Ispis ne sadrzi "Obrisani".
 * \endfield
 */
TEST_F(Prikaz, PrikaziAutomobile_NeIspisujeElementeVanOpsega)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    strcpy(automobili[1].marka, "Obrisani");

    std::string ispis = uhvatiIspis(prikaziAutomobile);

    EXPECT_TRUE(Sadrzi(ispis, "Volkswagen"));
    EXPECT_EQ(std::string::npos, ispis.find("Obrisani"));
}

/**
 * \tracehead{PrikaziAutomobile_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u pogledu formatiranja cijene na dvije decimale.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 1, marka = "Fiat", model = "Punto", godiste = 2015, cijena_po_danu = 30.0, dostupan = 1}
 *  * brojAutomobila = 1
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Cijena je ispisana kao "30.00" (tacno dvije decimale).
 * \endfield
 */
TEST_F(Prikaz, PrikaziAutomobile_CijenaSaDvijeDecimale)
{
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);

    std::string ispis = uhvatiIspis(prikaziAutomobile);

    EXPECT_TRUE(Sadrzi(ispis, " 30.00 "));
}

/* ======================= prikaziIznajmljivanja ======================= */

/**
 * \tracehead{PrikaziIznajmljivanja_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada nema evidentiranih iznajmljivanja (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojIznajmljivanja = 0
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi poruku "Trenutno nema evidentiranih iznajmljivanja.".
 * 2. Ispis ne sadrzi zaglavlje tabele (kolonu "AutoID").
 * \endfield
 */
TEST_F(Prikaz, PrikaziIznajmljivanja_PrazanNizIspisujePoruku)
{
    std::string ispis = uhvatiIspis(prikaziIznajmljivanja);

    EXPECT_TRUE(Sadrzi(ispis, "Trenutno nema evidentiranih iznajmljivanja."));
    EXPECT_EQ(std::string::npos, ispis.find("AutoID"));
}

/**
 * \tracehead{PrikaziIznajmljivanja_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada postoji jedno aktivno iznajmljivanje (provjera tacnog formata reda tabele).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0] = {id = 1, id_automobila = 3, ime = "Marina", prezime = "Gogic", datum_pocetka = "27-07-2026", datum_kraja = "28-07-2026", broj_dana = 1, ukupna_cijena = 90.0, aktivno = 1}
 *  * brojIznajmljivanja = 1
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi zaglavlje tabele sa svim kolonama.
 * 2. Ispis sadrzi red tabele tacno u formatu:
 *  * "1    3        Marina       Gogic        27-07-2026   28-07-2026   1      90.00      Aktivno   "
 * \endfield
 */
TEST_F(Prikaz, PrikaziIznajmljivanja_AktivnoIznajmljivanjeTacanFormatReda)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);

    std::string ispis = uhvatiIspis(prikaziIznajmljivanja);

    EXPECT_TRUE(Sadrzi(ispis, "ID   AutoID   Ime          Prezime      Pocetak      Kraj         Dani   Cijena     Status"));
    EXPECT_TRUE(Sadrzi(ispis, "1    3        Marina       Gogic        27-07-2026   28-07-2026   1      90.00      Aktivno   \n"));
}

/**
 * \tracehead{PrikaziIznajmljivanja_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada je iznajmljivanje zavrseno.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0] = {id = 1, id_automobila = 3, ime = "Marko", ..., aktivno = 0}
 *  * brojIznajmljivanja = 1
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi status "Zavrseno".
 * 2. Ispis ne sadrzi status "Aktivno".
 * \endfield
 */
TEST_F(Prikaz, PrikaziIznajmljivanja_ZavrsenoIznajmljivanjeIspisujeStatus)
{
    dodajIznajmljivanje(1, 3, "Marko", "Markovic", "01-01-2026", "05-01-2026", 4, 200.0f, 0);

    std::string ispis = uhvatiIspis(prikaziIznajmljivanja);

    EXPECT_TRUE(Sadrzi(ispis, "Zavrseno"));
    EXPECT_EQ(std::string::npos, ispis.find("Aktivno"));
}

/**
 * \tracehead{PrikaziIznajmljivanja_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada postoje i aktivna i zavrsena iznajmljivanja.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 3 zapisa:
 *  * id = 1, ime = "Ana", aktivno = 0
 *  * id = 2, ime = "Petar", aktivno = 1
 *  * id = 3, ime = "Jovana", aktivno = 0
 *  * brojIznajmljivanja = 3
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Status "Zavrseno" se pojavljuje tacno 2 puta, a "Aktivno" tacno 1 put.
 * 2. Zapisi su ispisani redoslijedom kojim su u nizu (Ana, Petar, Jovana).
 * \endfield
 */
TEST_F(Prikaz, PrikaziIznajmljivanja_ViseZapisaIspisujeSveRedom)
{
    dodajIznajmljivanje(1, 1, "Ana", "Anic", "01-01-2026", "03-01-2026", 2, 100.0f, 0);
    dodajIznajmljivanje(2, 2, "Petar", "Petrovic", "05-01-2026", "08-01-2026", 3, 180.0f, 1);
    dodajIznajmljivanje(3, 1, "Jovana", "Jovic", "10-01-2026", "11-01-2026", 1, 50.0f, 0);

    std::string ispis = uhvatiIspis(prikaziIznajmljivanja);

    EXPECT_EQ(2, BrojPojavljivanja(ispis, "Zavrseno"));
    EXPECT_EQ(1, BrojPojavljivanja(ispis, "Aktivno"));
    EXPECT_LT(ispis.find("Ana"), ispis.find("Petar"));
    EXPECT_LT(ispis.find("Petar"), ispis.find("Jovana"));
}

/**
 * \tracehead{PrikaziIznajmljivanja_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada se iza posljednjeg validnog elementa nalazi zaostali zapis (analiza granicnih vrijednosti - element na indeksu brojIznajmljivanja).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0] = {id = 1, ime = "Marina", ...}
 *  * brojIznajmljivanja = 1
 *  * iznajmljivanja[1].ime = "Zaostali" (van opsega validnih elemenata)
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi "Marina".
 * 2. Ispis ne sadrzi "Zaostali".
 * \endfield
 */
TEST_F(Prikaz, PrikaziIznajmljivanja_NeIspisujeElementeVanOpsega)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);
    strcpy(iznajmljivanja[1].ime, "Zaostali");

    std::string ispis = uhvatiIspis(prikaziIznajmljivanja);

    EXPECT_TRUE(Sadrzi(ispis, "Marina"));
    EXPECT_EQ(std::string::npos, ispis.find("Zaostali"));
}
