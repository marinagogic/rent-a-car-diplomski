/**
 * \file test_akcije.cpp
 *
 * \brief Google Test testovi za akcije glavnog menija rent-a-car sistema
 *        (rent_a_car_akcije.h/.c).
 *
 * Funkcije koje se testiraju istovremeno citaju unos korisnika (scanf),
 * ispisuju poruke (printf), mijenjaju globalno stanje i cuvaju podatke u
 * fajlove. Zato svaki test:
 *  1. simulira unos korisnika - "otkucane" vrijednosti se upisuju u
 *     privremeni fajl, a standardni ulaz se preusmjerava na njega (freopen),
 *  2. hvata ispis funkcije (CaptureStdout / GetCapturedStdout),
 *  3. radi nad poznatim globalnim stanjem, koje se resetuje prije i poslije
 *     svakog testa, i nad privremenim fajlovima umjesto stvarnih.
 */

 //#include "pch.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <functional>

extern "C" {
#include "rent_a_car_stanje.h"
#include "rent_a_car_akcije.h"
}

/* Kompatibilnost sa starijim verzijama Google Testa (npr. 1.8.1 iz Visual
   Studio NuGet paketa), u kojima makro INSTANTIATE_TEST_SUITE_P ne postoji,
   vec se isti makro zove INSTANTIATE_TEST_CASE_P. */
#ifndef INSTANTIATE_TEST_SUITE_P
#define INSTANTIATE_TEST_SUITE_P INSTANTIATE_TEST_CASE_P
#endif

static const char* const TEST_AUTOMOBILI = "gtest_tmp_akcije_automobili.txt";          /**< Privremeni fajl za automobile. */
static const char* const TEST_IZNAJMLJIVANJA = "gtest_tmp_akcije_iznajmljivanja.txt";  /**< Privremeni fajl za iznajmljivanja. */
static const char* const TEST_ULAZ = "gtest_tmp_ulaz.txt";                              /**< Privremeni fajl sa simuliranim unosom. */

#ifdef _WIN32
static const char* const PRAZAN_UREDJAJ = "NUL";        /**< Prazan uredjaj na Windows-u. */
#else
static const char* const PRAZAN_UREDJAJ = "/dev/null";  /**< Prazan uredjaj na Linux-u. */
#endif

/** \brief Provjerava da li tekst sadrzi dati podstring, sa citljivom porukom u slucaju neuspjeha. */
static ::testing::AssertionResult Sadrzi(const std::string& ispis, const std::string& tekst)
{
    if (ispis.find(tekst) != std::string::npos)
    {
        return ::testing::AssertionSuccess();
    }
    return ::testing::AssertionFailure()
        << "Ispis ne sadrzi \"" << tekst << "\".\nUhvaceni ispis:\n" << ispis;
}

/**
 * \brief Fixture klasa za testove akcija menija.
 *
 * Prije i poslije svakog testa resetuje globalno stanje i brise privremene
 * fajlove. Metoda \ref izvrsi simulira unos korisnika i vraca uhvaceni ispis.
 */
class Akcije : public ::testing::Test
{
protected:
    void SetUp() override
    {
        resetujStanje();
        obrisiPrivremeneFajlove();
    }

    void TearDown() override
    {
        /* Standardni ulaz se preusmjerava na prazan uredjaj, kako bi fajl sa
           simuliranim unosom bio zatvoren i mogao biti obrisan. */
        (void)freopen(PRAZAN_UREDJAJ, "r", stdin);
        obrisiPrivremeneFajlove();
        resetujStanje();
    }

    static void resetujStanje()
    {
        memset(automobili, 0, sizeof(automobili));
        memset(iznajmljivanja, 0, sizeof(iznajmljivanja));
        brojAutomobila = 0;
        brojIznajmljivanja = 0;
    }

    static void obrisiPrivremeneFajlove()
    {
        remove(TEST_AUTOMOBILI);
        remove(TEST_IZNAJMLJIVANJA);
        remove(TEST_ULAZ);
    }

    /**
     * \brief Simulira unos korisnika, izvrsava akciju i vraca sve sto je ispisano.
     *
     * \param unos   Tekst koji "korisnik otkuca" (svaka vrijednost u svom redu).
     * \param akcija Funkcija koja se izvrsava.
     */
    static std::string izvrsi(const std::string& unos, const std::function<void(void)>& akcija)
    {
        FILE* fp = fopen(TEST_ULAZ, "w");
        if (fp == NULL)
        {
            ADD_FAILURE() << "Nije moguce napraviti fajl sa simuliranim unosom.";
            return "";
        }
        fputs(unos.c_str(), fp);
        fclose(fp);

        if (freopen(TEST_ULAZ, "r", stdin) == NULL)
        {
            ADD_FAILURE() << "Nije moguce preusmjeriti standardni ulaz.";
            return "";
        }

        ::testing::internal::CaptureStdout();
        akcija();
        return ::testing::internal::GetCapturedStdout();
    }

    static std::string procitajFajl(const char* putanja)
    {
        std::string sadrzaj;
        FILE* fp = fopen(putanja, "r");
        if (fp == NULL)
        {
            return sadrzaj;
        }
        int c;
        while ((c = fgetc(fp)) != EOF)
        {
            sadrzaj += (char)c;
        }
        fclose(fp);
        return sadrzaj;
    }

    static bool postojiFajl(const char* putanja)
    {
        FILE* fp = fopen(putanja, "r");
        if (fp == NULL)
        {
            return false;
        }
        fclose(fp);
        return true;
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

    static void dodajIznajmljivanje(int id, int idAuta, int aktivno)
    {
        Iznajmljivanje* r = &iznajmljivanja[brojIznajmljivanja];
        r->id = id;
        r->id_automobila = idAuta;
        strcpy(r->ime, "Ana");
        strcpy(r->prezime, "Anic");
        strcpy(r->datum_pocetka, "01-01-2026");
        strcpy(r->datum_kraja, "03-01-2026");
        r->broj_dana = 2;
        r->ukupna_cijena = 100.0f;
        r->aktivno = aktivno;
        brojIznajmljivanja++;
    }

    /* Omotaci oko akcija, sa putanjama do privremenih fajlova */
    static void dodaj() { dodajAutomobil(TEST_AUTOMOBILI); }
    static void obrisi() { obrisiAutomobil(TEST_AUTOMOBILI); }
    static void iznajmi() { iznajmiAutomobil(TEST_AUTOMOBILI, TEST_IZNAJMLJIVANJA); }
    static void vrati() { vratiAutomobil(TEST_AUTOMOBILI, TEST_IZNAJMLJIVANJA); }
};

/* ======================= dodajAutomobil ======================= */

/**
 * \tracehead{DodajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "dodajAutomobil" u slucaju validnog unosa (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 0
 * 2. Simulirati unos korisnika:
 *  * marka = "Volkswagen", model = "Golf", godiste = 2020, cijena = 45.5
 * 3. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka 1.
 * 2. Automobil ima id = 1, unesene podatke i dostupan = 1.
 * 3. Ispisana je poruka "Automobil je uspjesno dodat! (ID: 1)".
 * 4. Fajl automobila sadrzi tacno liniju "1;Volkswagen;Golf;2020;45.50;1".
 * \endfield
 */
TEST_F(Akcije, DodajAutomobil_ValidanUnosDodajeAutomobil)
{
    std::string ispis = izvrsi("Volkswagen\nGolf\n2020\n45.5\n", dodaj);

    ASSERT_EQ(1, brojAutomobila);
    EXPECT_EQ(1, automobili[0].id);
    EXPECT_STREQ("Volkswagen", automobili[0].marka);
    EXPECT_STREQ("Golf", automobili[0].model);
    EXPECT_EQ(2020, automobili[0].godiste);
    EXPECT_FLOAT_EQ(45.5f, automobili[0].cijena_po_danu);
    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno dodat! (ID: 1)"));
    EXPECT_EQ("1;Volkswagen;Golf;2020;45.50;1\n", procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{DodajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava da funkcija "dodajAutomobil" novom automobilu dodjeljuje sledeci slobodan ID kada u sistemu vec postoje automobili.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 2 automobila (id = 1 i id = 5).
 * 2. Simulirati unos korisnika:
 *  * marka = "Audi", model = "A4", godiste = 2021, cijena = 80
 * 3. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka 3.
 * 2. Novi automobil je dodat na kraj niza i ima id = 6.
 * 3. Ispisana je poruka "Automobil je uspjesno dodat! (ID: 6)".
 * \endfield
 */
TEST_F(Akcije, DodajAutomobil_DodjeljujeSledeciId)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajAuto(5, "Skoda", "Octavia", 2019, 60.0f, 1);

    std::string ispis = izvrsi("Audi\nA4\n2021\n80\n", dodaj);

    ASSERT_EQ(3, brojAutomobila);
    EXPECT_EQ(6, automobili[2].id);
    EXPECT_STREQ("Audi", automobili[2].marka);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno dodat! (ID: 6)"));
}

/**
 * \tracehead{DodajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "dodajAutomobil" za najmanje dozvoljeno godiste i najmanju pozitivnu cijenu (analiza granicnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika:
 *  * marka = "Fiat", model = "500", godiste = 1950, cijena = 0.01
 * 2. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka 1 (automobil je dodat).
 * 2. Ispisana je poruka o uspjesnom dodavanju.
 * \endfield
 */
TEST_F(Akcije, DodajAutomobil_GranicneVrijednostiSuDozvoljene)
{
    std::string ispis = izvrsi("Fiat\n500\n1950\n0.01\n", dodaj);

    EXPECT_EQ(1, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno dodat!"));
}

/**
 * \tracehead{DodajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "dodajAutomobil" u slucaju nevalidnog godista (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika:
 *  * marka = "Volkswagen", model = "Golf", godiste = 1800, cijena = 45
 * 2. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka 0 (automobil nije dodat).
 * 2. Ispisana je poruka "Godiste nije u dozvoljenom opsegu (1950-2100). Automobil nije dodat.".
 * 3. Fajl automobila nije napravljen (nista nije sacuvano).
 * \endfield
 */
TEST_F(Akcije, DodajAutomobil_NevalidnoGodisteNeDodaje)
{
    std::string ispis = izvrsi("Volkswagen\nGolf\n1800\n45\n", dodaj);

    EXPECT_EQ(0, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Godiste nije u dozvoljenom opsegu (1950-2100). Automobil nije dodat."));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{DodajAutomobil_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "dodajAutomobil" u slucaju kada je unesena cijena jednaka nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost).
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika:
 *  * marka = "Volkswagen", model = "Golf", godiste = 2020, cijena = 0
 * 2. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka 0.
 * 2. Ispisana je poruka "Cijena po danu mora biti veca od nule. Automobil nije dodat.".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, DodajAutomobil_NultaCijenaNeDodaje)
{
    std::string ispis = izvrsi("Volkswagen\nGolf\n2020\n0\n", dodaj);

    EXPECT_EQ(0, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Cijena po danu mora biti veca od nule. Automobil nije dodat."));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{DodajAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "dodajAutomobil" u slucaju kada je dostignut maksimalan broj automobila (analiza granicnih vrijednosti - MAX_AUTOMOBILA).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = MAX_AUTOMOBILA (100)
 * 2. Simulirati unos korisnika sa validnim podacima.
 * 3. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila ostaje MAX_AUTOMOBILA (nema upisa van granica niza).
 * 2. Ispisana je poruka "Dostignut je maksimalan broj automobila (100).".
 * 3. Funkcija ne trazi unos podataka (nije ispisan upit "Marka:").
 * \endfield
 */
TEST_F(Akcije, DodajAutomobil_MaksimalanBrojAutomobila)
{
    brojAutomobila = MAX_AUTOMOBILA;

    std::string ispis = izvrsi("Volkswagen\nGolf\n2020\n45\n", dodaj);

    EXPECT_EQ(MAX_AUTOMOBILA, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Dostignut je maksimalan broj automobila (100)."));
    EXPECT_EQ(std::string::npos, ispis.find("Marka:"));
}

/* ======================= obrisiAutomobil ======================= */

/**
 * \tracehead{ObrisiAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobil" u slucaju brisanja postojeceg, dostupnog automobila (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 2 dostupna automobila (id = 1 i id = 2).
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju obrisiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka 1, a preostali automobil ima id = 2.
 * 2. Ispisana je poruka "Automobil je uspjesno obrisan.".
 * 3. Fajl automobila sadrzi samo automobil sa id = 2.
 * \endfield
 */
TEST_F(Akcije, ObrisiAutomobil_PostojeciDostupanSeBrise)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 1);

    std::string ispis = izvrsi("1\n", obrisi);

    ASSERT_EQ(1, brojAutomobila);
    EXPECT_EQ(2, automobili[0].id);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno obrisan."));
    EXPECT_EQ("2;Skoda;Octavia;2019;60.00;1\n", procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{ObrisiAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobil" u slucaju kada automobil sa unesenim ID-om ne postoji (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 automobilom (id = 1).
 * 2. Simulirati unos korisnika:
 *  * ID = 99
 * 3. Pozvati funkciju obrisiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila ostaje 1.
 * 2. Ispisana je poruka "Automobil sa datim ID-om ne postoji. (ID 99)".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, ObrisiAutomobil_NepostojeciId)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    std::string ispis = izvrsi("99\n", obrisi);

    EXPECT_EQ(1, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil sa datim ID-om ne postoji. (ID 99)"));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{ObrisiAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobil" u slucaju kada je automobil trenutno iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 iznajmljenim automobilom (id = 1, dostupan = 0).
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju obrisiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila ostaje 1 (iznajmljen automobil se ne brise).
 * 2. Ispisana je poruka "Automobil je trenutno iznajmljen.".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, ObrisiAutomobil_IznajmljenSeNeBrise)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    std::string ispis = izvrsi("1\n", obrisi);

    EXPECT_EQ(1, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je trenutno iznajmljen."));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/* ======================= iznajmiAutomobil ======================= */

/**
 * \tracehead{IznajmiAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju validnog unosa za dostupan automobil (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom:
 *  * {id = 1, "Volkswagen", "Golf", 2020, cijena_po_danu = 45.0, dostupan = 1}
 * 2. Simulirati unos korisnika:
 *  * ID = 1, ime = "Marina", prezime = "Gogic", pocetak = "27-07-2026", kraj = "30-07-2026", broj dana = 3
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja je jednaka 1, a zapis sadrzi sve unesene podatke, ukupnu cijenu 135.0 i aktivno = 1.
 * 2. Automobil je oznacen kao iznajmljen (dostupan = 0).
 * 3. Ispisane su poruke "Automobil je uspjesno iznajmljen!" i "Ukupna cijena: 135.00 KM".
 * 4. Oba fajla sadrze azurirane podatke.
 * \endfield
 */
TEST_F(Akcije, IznajmiAutomobil_ValidanUnosIznajmljuje)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    std::string ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n30-07-2026\n3\n", iznajmi);

    ASSERT_EQ(1, brojIznajmljivanja);
    EXPECT_EQ(1, iznajmljivanja[0].id);
    EXPECT_EQ(1, iznajmljivanja[0].id_automobila);
    EXPECT_STREQ("Marina", iznajmljivanja[0].ime);
    EXPECT_STREQ("Gogic", iznajmljivanja[0].prezime);
    EXPECT_STREQ("27-07-2026", iznajmljivanja[0].datum_pocetka);
    EXPECT_STREQ("30-07-2026", iznajmljivanja[0].datum_kraja);
    EXPECT_EQ(3, iznajmljivanja[0].broj_dana);
    EXPECT_FLOAT_EQ(135.0f, iznajmljivanja[0].ukupna_cijena);
    EXPECT_EQ(1, iznajmljivanja[0].aktivno);
    EXPECT_EQ(0, automobili[0].dostupan);

    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno iznajmljen!"));
    EXPECT_TRUE(Sadrzi(ispis, "Ukupna cijena: 135.00 KM"));

    EXPECT_EQ("1;1;Marina;Gogic;27-07-2026;30-07-2026;3;135.00;1\n", procitajFajl(TEST_IZNAJMLJIVANJA));
    EXPECT_EQ("1;Volkswagen;Golf;2020;45.00;0\n", procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{IznajmiAutomobil_TC_01, Funkcionalni test}
 * Test provjerava da funkcija "iznajmiAutomobil" novom zapisu dodjeljuje sledeci slobodan ID kada vec postoje zapisi o iznajmljivanju.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 1 dostupan automobil (id = 1)
 *  * 1 zavrseno iznajmljivanje (id = 3)
 * 2. Simulirati unos korisnika sa validnim podacima za automobil id = 1.
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja je jednaka 2.
 * 2. Novi zapis ima id = 4.
 * \endfield
 */
TEST_F(Akcije, IznajmiAutomobil_DodjeljujeSledeciId)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajIznajmljivanje(3, 1, 0);

    izvrsi("1\nMarina\nGogic\n27-07-2026\n28-07-2026\n1\n", iznajmi);

    ASSERT_EQ(2, brojIznajmljivanja);
    EXPECT_EQ(4, iznajmljivanja[1].id);
}

/**
 * \tracehead{IznajmiAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju kada automobil sa unesenim ID-om ne postoji (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 automobilom (id = 1).
 * 2. Simulirati unos korisnika:
 *  * ID = 99
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja ostaje 0.
 * 2. Ispisana je poruka "Automobil sa datim ID-om ne postoji. (ID 99)".
 * 3. Funkcija ne trazi podatke o klijentu (nije ispisan upit "Ime klijenta:").
 * \endfield
 */
TEST_F(Akcije, IznajmiAutomobil_NepostojeciId)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    std::string ispis = izvrsi("99\n", iznajmi);

    EXPECT_EQ(0, brojIznajmljivanja);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil sa datim ID-om ne postoji. (ID 99)"));
    EXPECT_EQ(std::string::npos, ispis.find("Ime klijenta:"));
}

/**
 * \tracehead{IznajmiAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju kada je automobil vec iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 iznajmljenim automobilom (id = 1, dostupan = 0).
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja ostaje 0.
 * 2. Ispisana je poruka "Automobil je trenutno iznajmljen.".
 * 3. Funkcija ne trazi podatke o klijentu.
 * \endfield
 */
TEST_F(Akcije, IznajmiAutomobil_VecIznajmljenAutomobil)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    std::string ispis = izvrsi("1\n", iznajmi);

    EXPECT_EQ(0, brojIznajmljivanja);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je trenutno iznajmljen."));
    EXPECT_EQ(std::string::npos, ispis.find("Ime klijenta:"));
}

/**
 * \tracehead{IznajmiAutomobil_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju kada je unesen nevalidan broj dana (analiza granicnih vrijednosti - broj dana = 0).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom (id = 1).
 * 2. Simulirati unos korisnika:
 *  * ID = 1, ime = "Marina", prezime = "Gogic", pocetak = "27-07-2026", kraj = "27-07-2026", broj dana = 0
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja ostaje 0.
 * 2. Automobil ostaje dostupan (dostupan = 1).
 * 3. Ispisana je poruka "Broj dana mora biti u opsegu 1-365. Iznajmljivanje otkazano.".
 * 4. Nijedan fajl nije napravljen.
 * \endfield
 */
TEST_F(Akcije, IznajmiAutomobil_NevalidanBrojDanaOtkazuje)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    std::string ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n27-07-2026\n0\n", iznajmi);

    EXPECT_EQ(0, brojIznajmljivanja);
    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_TRUE(Sadrzi(ispis, "Broj dana mora biti u opsegu 1-365. Iznajmljivanje otkazano."));
    EXPECT_FALSE(postojiFajl(TEST_IZNAJMLJIVANJA));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{IznajmiAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju kada je dostignut maksimalan broj zapisa o iznajmljivanju (analiza granicnih vrijednosti - MAX_IZNAJMLJIVANJA).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 1 dostupan automobil (id = 1)
 *  * brojIznajmljivanja = MAX_IZNAJMLJIVANJA (200)
 * 2. Simulirati unos korisnika sa validnim podacima.
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja ostaje MAX_IZNAJMLJIVANJA (nema upisa van granica niza).
 * 2. Automobil ostaje dostupan.
 * 3. Ispisana je poruka "Dostignut je maksimalan dozvoljeni broj zapisa.".
 * \endfield
 */
TEST_F(Akcije, IznajmiAutomobil_MaksimalanBrojZapisa)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    brojIznajmljivanja = MAX_IZNAJMLJIVANJA;

    std::string ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n28-07-2026\n1\n", iznajmi);

    EXPECT_EQ(MAX_IZNAJMLJIVANJA, brojIznajmljivanja);
    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_TRUE(Sadrzi(ispis, "Dostignut je maksimalan dozvoljeni broj zapisa."));
}

/* ======================= vratiAutomobil ======================= */

/**
 * \tracehead{VratiAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "vratiAutomobil" u slucaju vracanja iznajmljenog automobila koji ima aktivan zapis (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 1 iznajmljen automobil (id = 1, dostupan = 0)
 *  * 1 aktivno iznajmljivanje za automobil id = 1
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju vratiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Automobil je oznacen kao dostupan (dostupan = 1).
 * 2. Zapis o iznajmljivanju je oznacen kao zavrsen (aktivno = 0).
 * 3. Ispisana je poruka "Automobil je uspjesno vracen.", bez upozorenja.
 * 4. Oba fajla sadrze azurirane podatke.
 * \endfield
 */
TEST_F(Akcije, VratiAutomobil_IznajmljenSeVraca)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);
    dodajIznajmljivanje(1, 1, 1);

    std::string ispis = izvrsi("1\n", vrati);

    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_EQ(0, iznajmljivanja[0].aktivno);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno vracen."));
    EXPECT_EQ(std::string::npos, ispis.find("UPOZORENJE"));
    EXPECT_EQ("1;Volkswagen;Golf;2020;45.00;1\n", procitajFajl(TEST_AUTOMOBILI));
    EXPECT_EQ("1;1;Ana;Anic;01-01-2026;03-01-2026;2;100.00;0\n", procitajFajl(TEST_IZNAJMLJIVANJA));
}

/**
 * \tracehead{VratiAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "vratiAutomobil" u slucaju kada automobil sa unesenim ID-om ne postoji (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 iznajmljenim automobilom (id = 1).
 * 2. Simulirati unos korisnika:
 *  * ID = 99
 * 3. Pozvati funkciju vratiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Automobil sa id = 1 ostaje iznajmljen.
 * 2. Ispisana je poruka "Automobil sa datim ID-om ne postoji. (ID 99)".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, VratiAutomobil_NepostojeciId)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    std::string ispis = izvrsi("99\n", vrati);

    EXPECT_EQ(0, automobili[0].dostupan);
    EXPECT_TRUE(Sadrzi(ispis, "Automobil sa datim ID-om ne postoji. (ID 99)"));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{VratiAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "vratiAutomobil" u slucaju kada automobil nije iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom (id = 1, dostupan = 1).
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju vratiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispisana je poruka "Ovaj automobil trenutno nije iznajmljen.".
 * 2. Nije ispisana poruka o uspjesnom vracanju.
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, VratiAutomobil_AutomobilNijeIznajmljen)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    std::string ispis = izvrsi("1\n", vrati);

    EXPECT_TRUE(Sadrzi(ispis, "Ovaj automobil trenutno nije iznajmljen."));
    EXPECT_EQ(std::string::npos, ispis.find("uspjesno vracen"));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{VratiAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "vratiAutomobil" u slucaju kada je automobil oznacen kao iznajmljen, ali ne postoji aktivan zapis o iznajmljivanju (nekonzistentni podaci).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 1 iznajmljen automobil (id = 1, dostupan = 0)
 *  * nema zapisa o iznajmljivanju
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju vratiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispisano je upozorenje "UPOZORENJE: Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil.".
 * 2. Automobil je ipak oznacen kao dostupan (dostupan = 1) i ispisana je poruka o uspjesnom vracanju.
 * 3. Fajl automobila sadrzi azurirani status.
 * \endfield
 */
TEST_F(Akcije, VratiAutomobil_BezAktivnogZapisaIspisujeUpozorenje)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    std::string ispis = izvrsi("1\n", vrati);

    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_TRUE(Sadrzi(ispis, "UPOZORENJE: Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil."));
    EXPECT_TRUE(Sadrzi(ispis, "Automobil je uspjesno vracen."));
    EXPECT_EQ("1;Volkswagen;Golf;2020;45.00;1\n", procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{VratiAutomobil_TC_04, Funkcionalni test}
 * Test provjerava da funkcija "vratiAutomobil" zavrsava samo aktivan zapis o iznajmljivanju, a ne mijenja ranije zavrsene zapise za isti automobil niti zapise drugih automobila.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 2 iznajmljena automobila (id = 1 i id = 2)
 *  * zapis id = 1: automobil 1, zavrsen (aktivno = 0)
 *  * zapis id = 2: automobil 2, aktivan
 *  * zapis id = 3: automobil 1, aktivan
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 * 3. Pozvati funkciju vratiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Zapis id = 3 je zavrsen (aktivno = 0).
 * 2. Zapis id = 1 ostaje zavrsen, a zapis id = 2 (drugi automobil) ostaje aktivan.
 * 3. Automobil 1 je dostupan, a automobil 2 ostaje iznajmljen.
 * \endfield
 */
TEST_F(Akcije, VratiAutomobil_ZavrsavaSamoAktivanZapis)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);
    dodajIznajmljivanje(1, 1, 0);
    dodajIznajmljivanje(2, 2, 1);
    dodajIznajmljivanje(3, 1, 1);

    izvrsi("1\n", vrati);

    EXPECT_EQ(0, iznajmljivanja[2].aktivno);
    EXPECT_EQ(0, iznajmljivanja[0].aktivno);
    EXPECT_EQ(1, iznajmljivanja[1].aktivno);
    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_EQ(0, automobili[1].dostupan);
}

/* ======================= ocistiUlazniBafer ======================= */

/**
 * \tracehead{OcistiUlazniBafer_TC_00, Funkcionalni test}
 * Test provjerava da funkcija "ocistiUlazniBafer" odbacuje ostatak tekuceg reda unosa, ukljucujuci znak za novi red, a da sledeci red ostaje netaknut.
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika:
 *  * "visak teksta u redu" (prvi red)
 *  * "sledeci" (drugi red)
 * 2. Pozvati funkciju ocistiUlazniBafer.
 * 3. Procitati sledecu rijec sa standardnog ulaza.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Procitana rijec je "sledeci" (citav prvi red je odbacen).
 * \endfield
 */
TEST_F(Akcije, OcistiUlazniBafer_OdbacujeOstatakReda)
{
    char rijec[32] = "";

    izvrsi("visak teksta u redu\nsledeci\n", [&rijec]() {
        ocistiUlazniBafer();
        if (scanf("%31s", rijec) != 1)
        {
            rijec[0] = '\0';
        }
        });

    EXPECT_STREQ("sledeci", rijec);
}

/**
 * \tracehead{OcistiUlazniBafer_TC_01, Funkcionalni test}
 * Test provjerava da se funkcija "ocistiUlazniBafer" zavrsava kada dodje do kraja ulaza, cak i ako red nije zavrsen znakom za novi red (granicni slucaj - kraj ulaza).
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika bez znaka za novi red na kraju:
 *  * "tekst bez novog reda"
 * 2. Pozvati funkciju ocistiUlazniBafer.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija se zavrsava (ne ulazi u beskonacnu petlju).
 * 2. Sledece citanje sa standardnog ulaza vraca EOF (sav unos je odbacen).
 * \endfield
 */
TEST_F(Akcije, OcistiUlazniBafer_ZaustavljaSeNaKrajuUlaza)
{
    int sledeciZnak = 0;

    izvrsi("tekst bez novog reda", [&sledeciZnak]() {
        ocistiUlazniBafer();
        sledeciZnak = getchar();
        });

    EXPECT_EQ(EOF, sledeciZnak);
}

/* ======================= Nevalidan unos (parametrizovani testovi) ======================= */

/**
 * \brief Parametrizovani fixture za testove nevalidnog unosa kod dodavanja automobila.
 *
 * Parametar je tekst simuliranog unosa. Svi slucajevi imaju isti ocekivani
 * rezultat, pa se umjesto vise skoro identicnih testova koristi jedan
 * test koji Google Test izvrsava za svaku vrijednost parametra.
 */
class DodajAutomobilNevalidanUnos : public Akcije, public ::testing::WithParamInterface<const char*> {};

/**
 * \tracehead{DodajAutomobil_TC_06, Funkcionalni test}
 * Parametrizovani test provjerava ispravno ponasanje funkcije "dodajAutomobil" u slucaju nevalidnog unosa (negativan test - podjela na klase ekvivalencije).
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika za svaki od sljedecih slucajeva:
 *  * [0] slova umjesto godista: "Volkswagen", "Golf", "abc"
 *  * [1] slova umjesto cijene: "Volkswagen", "Golf", "2020", "abc"
 *  * [2] kraj ulaza prije marke: "" (prazan unos)
 *  * [3] kraj ulaza prije modela: "Volkswagen"
 * 2. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed (za svaki slucaj)
 * 1. Vrijednost brojAutomobila je jednaka 0 (automobil nije dodat).
 * 2. Ispisana je poruka "Nevalidan unos. Automobil nije dodat.".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_P(DodajAutomobilNevalidanUnos, NeDodajeAutomobil)
{
    std::string ispis = izvrsi(GetParam(), dodaj);

    EXPECT_EQ(0, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Nevalidan unos. Automobil nije dodat."));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

INSTANTIATE_TEST_SUITE_P(Akcije, DodajAutomobilNevalidanUnos,
    ::testing::Values(
        "Volkswagen\nGolf\nabc\n",
        "Volkswagen\nGolf\n2020\nabc\n",
        "",
        "Volkswagen\n"));

/**
 * \brief Parametrizovani fixture za testove nevalidnog unosa kod iznajmljivanja.
 *
 * Prije svakog testa u sistemu postoji jedan dostupan automobil (id = 1).
 */
class IznajmiAutomobilNevalidanUnos : public Akcije, public ::testing::WithParamInterface<const char*>
{
protected:
    void SetUp() override
    {
        Akcije::SetUp();
        dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    }
};

/**
 * \tracehead{IznajmiAutomobil_TC_06, Funkcionalni test}
 * Parametrizovani test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju nevalidnog unosa (negativan test - podjela na klase ekvivalencije).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom (id = 1).
 * 2. Simulirati unos korisnika za svaki od sljedecih slucajeva:
 *  * [0] slova umjesto ID-a: "abc"
 *  * [1] kraj ulaza prije imena: "1"
 *  * [2] kraj ulaza prije prezimena: "1", "Marina"
 *  * [3] kraj ulaza prije datuma pocetka: "1", "Marina", "Gogic"
 *  * [4] kraj ulaza prije datuma kraja: "1", "Marina", "Gogic", "27-07-2026"
 *  * [5] slova umjesto broja dana: "1", "Marina", "Gogic", "27-07-2026", "30-07-2026", "abc"
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed (za svaki slucaj)
 * 1. Vrijednost brojIznajmljivanja je jednaka 0.
 * 2. Automobil ostaje dostupan (dostupan = 1).
 * 3. Ispisana je poruka "Nevalidan unos. Iznajmljivanje otkazano.".
 * 4. Nijedan fajl nije napravljen.
 * \endfield
 */
TEST_P(IznajmiAutomobilNevalidanUnos, OtkazujeIznajmljivanje)
{
    std::string ispis = izvrsi(GetParam(), iznajmi);

    EXPECT_EQ(0, brojIznajmljivanja);
    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_TRUE(Sadrzi(ispis, "Nevalidan unos. Iznajmljivanje otkazano."));
    EXPECT_FALSE(postojiFajl(TEST_IZNAJMLJIVANJA));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

INSTANTIATE_TEST_SUITE_P(Akcije, IznajmiAutomobilNevalidanUnos,
    ::testing::Values(
        "abc\n",
        "1\n",
        "1\nMarina\n",
        "1\nMarina\nGogic\n",
        "1\nMarina\nGogic\n27-07-2026\n",
        "1\nMarina\nGogic\n27-07-2026\n30-07-2026\nabc\n"));

/**
 * \tracehead{ObrisiAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobil" u slucaju kada je umjesto ID-a uneseno slovo (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom (id = 1).
 * 2. Simulirati unos korisnika:
 *  * "abc"
 * 3. Pozvati funkciju obrisiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila ostaje 1.
 * 2. Ispisana je poruka "Nevalidan unos. Automobil nije obrisan.".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, ObrisiAutomobil_NenumerickiIdNeBrise)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    std::string ispis = izvrsi("abc\n", obrisi);

    EXPECT_EQ(1, brojAutomobila);
    EXPECT_TRUE(Sadrzi(ispis, "Nevalidan unos. Automobil nije obrisan."));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{VratiAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "vratiAutomobil" u slucaju kada je umjesto ID-a uneseno slovo (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 1 iznajmljen automobil (id = 1, dostupan = 0)
 *  * 1 aktivno iznajmljivanje za automobil id = 1
 * 2. Simulirati unos korisnika:
 *  * "abc"
 * 3. Pozvati funkciju vratiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Automobil ostaje iznajmljen, a zapis ostaje aktivan.
 * 2. Ispisana je poruka "Nevalidan unos. Automobil nije vracen.".
 * 3. Fajl automobila nije napravljen.
 * \endfield
 */
TEST_F(Akcije, VratiAutomobil_NenumerickiIdNeVraca)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);
    dodajIznajmljivanje(1, 1, 1);

    std::string ispis = izvrsi("abc\n", vrati);

    EXPECT_EQ(0, automobili[0].dostupan);
    EXPECT_EQ(1, iznajmljivanja[0].aktivno);
    EXPECT_TRUE(Sadrzi(ispis, "Nevalidan unos. Automobil nije vracen."));
    EXPECT_FALSE(postojiFajl(TEST_AUTOMOBILI));
}