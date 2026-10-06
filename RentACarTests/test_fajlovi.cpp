/**
 * \file test_fajlovi.cpp
 *
 * \brief Google Test testovi za ucitavanje i cuvanje podataka u fajlovima
 *        (rent_a_car_fajlovi.h/.c).
 *
 * Funkcije koje se testiraju rade sa stvarnim fajlovima na disku, pa ovi
 * testovi imaju karakter integracionih testova (funkcija + fajl sistem).
 * Da bi testovi bili ponovljivi i nezavisni, svaki test radi sa privremenim
 * fajlovima poznatog sadrzaja, koji se brisu prije i poslije svakog testa.
 * Stvarni fajlovi aplikacije (cars.txt, rentals.txt) se nikad ne koriste.
 */

 //#include "pch.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <string>

extern "C" {
#include "rent_a_car_stanje.h"
#include "rent_a_car_fajlovi.h"
}

static const char* const TEST_AUTOMOBILI = "gtest_tmp_automobili.txt";          /**< Privremeni fajl za automobile. */
static const char* const TEST_IZNAJMLJIVANJA = "gtest_tmp_iznajmljivanja.txt";  /**< Privremeni fajl za iznajmljivanja. */
static const char* const NEVALIDNA_PUTANJA = "gtest_nepostojeci_folder/fajl.txt"; /**< Putanja u folderu koji ne postoji. */

/**
 * \brief Fixture klasa za testove rada sa fajlovima.
 *
 * Prije i poslije svakog testa resetuje globalno stanje i brise privremene
 * fajlove, a sadrzi i pomocne metode za pravljenje i citanje fajlova.
 */
class Fajlovi : public ::testing::Test
{
protected:
    void SetUp() override
    {
        resetujStanje();
        remove(TEST_AUTOMOBILI);
        remove(TEST_IZNAJMLJIVANJA);
    }

    void TearDown() override
    {
        resetujStanje();
        remove(TEST_AUTOMOBILI);
        remove(TEST_IZNAJMLJIVANJA);
    }

    static void resetujStanje()
    {
        memset(automobili, 0, sizeof(automobili));
        memset(iznajmljivanja, 0, sizeof(iznajmljivanja));
        brojAutomobila = 0;
        brojIznajmljivanja = 0;
    }

    /** Pravi fajl sa zadatim sadrzajem (postojeci sadrzaj se prepisuje). */
    static void upisiFajl(const char* putanja, const std::string& sadrzaj)
    {
        FILE* fp = fopen(putanja, "w");
        ASSERT_NE(nullptr, fp) << "Nije moguce napraviti privremeni fajl " << putanja;
        fputs(sadrzaj.c_str(), fp);
        fclose(fp);
    }

    /** Cita kompletan sadrzaj fajla u string. */
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

    /** Provjerava da li fajl postoji. */
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

/* ======================= ucitajAutomobile ======================= */

/**
 * \tracehead{UcitajAutomobile_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada fajl ne postoji (npr. prvo pokretanje programa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 5 (simulira prethodno ucitane podatke)
 * 2. Obezbijediti da privremeni fajl ne postoji.
 * 3. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl koji ne postoji
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_FILE_ERROR.
 * 2. Vrijednost brojAutomobila je jednaka 0 (lista je prazna).
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_NepostojeciFajlDajePraznuListu)
{
    brojAutomobila = 5;

    EXPECT_EQ(RENT_FILE_ERROR, ucitajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ(0, brojAutomobila);
}

/**
 * \tracehead{UcitajAutomobile_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada je fajl prazan (analiza granicnih vrijednosti - fajl bez ijedne linije).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl bez sadrzaja.
 * 2. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka 0.
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_PrazanFajl)
{
    upisiFajl(TEST_AUTOMOBILI, "");

    EXPECT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ(0, brojAutomobila);
}

/**
 * \tracehead{UcitajAutomobile_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada fajl sadrzi validne linije.
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sljedecim sadrzajem:
 *  * "1;Volkswagen;Golf;2020;45.50;1"
 *  * "2;Skoda;Octavia;2019;60.00;0"
 * 2. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka 2.
 * 3. Svi podaci oba automobila su ispravno ucitani, redoslijedom iz fajla.
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_ValidneLinijeSeUcitavaju)
{
    upisiFajl(TEST_AUTOMOBILI,
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "2;Skoda;Octavia;2019;60.00;0\n");

    ASSERT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    ASSERT_EQ(2, brojAutomobila);

    EXPECT_EQ(1, automobili[0].id);
    EXPECT_STREQ("Volkswagen", automobili[0].marka);
    EXPECT_STREQ("Golf", automobili[0].model);
    EXPECT_EQ(2020, automobili[0].godiste);
    EXPECT_FLOAT_EQ(45.50f, automobili[0].cijena_po_danu);
    EXPECT_EQ(1, automobili[0].dostupan);

    EXPECT_EQ(2, automobili[1].id);
    EXPECT_STREQ("Skoda", automobili[1].marka);
    EXPECT_STREQ("Octavia", automobili[1].model);
    EXPECT_EQ(2019, automobili[1].godiste);
    EXPECT_FLOAT_EQ(60.00f, automobili[1].cijena_po_danu);
    EXPECT_EQ(0, automobili[1].dostupan);
}

/**
 * \tracehead{UcitajAutomobile_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada fajl, pored validnih, sadrzi i nevalidne i prazne linije (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sljedecim sadrzajem:
 *  * "1;Volkswagen;Golf;2020;45.50;1"
 *  * "ovo nije validna linija"
 *  * "" (prazna linija)
 *  * "3;Audi;A4;abcd;80.00;1" (tekst umjesto godista)
 *  * "2;Skoda;Octavia;2019;60.00;0"
 * 2. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka 2 (nevalidne linije su preskocene).
 * 3. Ucitani su automobili sa id = 1 i id = 2.
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_NevalidneLinijeSePreskacu)
{
    upisiFajl(TEST_AUTOMOBILI,
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "ovo nije validna linija\n"
        "\n"
        "3;Audi;A4;abcd;80.00;1\n"
        "2;Skoda;Octavia;2019;60.00;0\n");

    ASSERT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    ASSERT_EQ(2, brojAutomobila);
    EXPECT_EQ(1, automobili[0].id);
    EXPECT_EQ(2, automobili[1].id);
}

/**
 * \tracehead{UcitajAutomobile_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada posljednja linija fajla nije zavrsena znakom za novi red.
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sljedecim sadrzajem (bez '\n' na kraju):
 *  * "1;Volkswagen;Golf;2020;45.50;1"
 *  * "2;Skoda;Octavia;2019;60.00;0"
 * 2. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka 2 (i posljednja linija je ucitana).
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_PosljednjaLinijaBezNovogReda)
{
    upisiFajl(TEST_AUTOMOBILI,
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "2;Skoda;Octavia;2019;60.00;0");

    ASSERT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ(2, brojAutomobila);
    EXPECT_EQ(2, automobili[1].id);
}

/**
 * \tracehead{UcitajAutomobile_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada fajl sadrzi vise automobila nego sto niz moze da primi (analiza granicnih vrijednosti - MAX_AUTOMOBILA + 1).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa MAX_AUTOMOBILA + 1 (101) validnih linija, sa id vrijednostima od 1 do 101.
 * 2. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka MAX_AUTOMOBILA (100).
 * 3. Posljednji ucitani automobil ima id = 100 (automobil sa id = 101 nije ucitan, nema prekoracenja niza).
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_NeUcitavaViseOdMaksimuma)
{
    std::string sadrzaj;
    for (int i = 1; i <= MAX_AUTOMOBILA + 1; i++)
    {
        sadrzaj += std::to_string(i) + ";Marka;Model;2020;50.00;1\n";
    }
    upisiFajl(TEST_AUTOMOBILI, sadrzaj);

    ASSERT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ(MAX_AUTOMOBILA, brojAutomobila);
    EXPECT_EQ(MAX_AUTOMOBILA, automobili[MAX_AUTOMOBILA - 1].id);
}

/**
 * \tracehead{UcitajAutomobile_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada je parametar putanja NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_NULL_POINTER.
 * 2. Vrijednost brojAutomobila je jednaka 0.
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_NullPutanjaVracaNullPointer)
{
    EXPECT_EQ(RENT_NULL_POINTER, ucitajAutomobile(NULL));
    EXPECT_EQ(0, brojAutomobila);
}

/**
 * \tracehead{UcitajAutomobile_TC_07, Funkcionalni test}
 * Test provjerava ponasanje funkcije "ucitajAutomobile" u slucaju kada linija ima ispravan format, ali vrijednosti van dozvoljenog opsega (godiste 1800, negativna cijena).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sljedecim sadrzajem:
 *  * "1;Volkswagen;Golf;1800;-5.00;1"
 * 2. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka 1 - pri ucitavanju se provjerava samo format linije, ne i validnost vrijednosti (dokumentuje trenutno ponasanje sistema).
 * \endfield
 */
TEST_F(Fajlovi, UcitajAutomobile_NeValidiraVrijednosti)
{
    upisiFajl(TEST_AUTOMOBILI, "1;Volkswagen;Golf;1800;-5.00;1\n");

    ASSERT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ(1, brojAutomobila);
    EXPECT_EQ(1800, automobili[0].godiste);
}

/* ======================= sacuvajAutomobile ======================= */

/**
 * \tracehead{SacuvajAutomobile_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u pogledu tacnog sadrzaja i formata upisanog fajla.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 2 automobila:
 *  * {id = 1, "Volkswagen", "Golf", 2020, 45.5, dostupan = 1}
 *  * {id = 2, "Skoda", "Octavia", 2019, 60.0, dostupan = 0}
 * 2. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_OK.
 * 2. Sadrzaj fajla je tacno:
 *  * "1;Volkswagen;Golf;2020;45.50;1"
 *  * "2;Skoda;Octavia;2019;60.00;0"
 * \endfield
 */
TEST_F(Fajlovi, SacuvajAutomobile_TacanSadrzajFajla)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.5f, 1);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);

    ASSERT_EQ(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ(
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "2;Skoda;Octavia;2019;60.00;0\n",
        procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{SacuvajAutomobile_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u slucaju kada je niz automobila prazan (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 0
 * 2. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_OK.
 * 2. Fajl je napravljen i prazan je.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajAutomobile_PrazanNizPraviPrazanFajl)
{
    ASSERT_EQ(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    EXPECT_TRUE(postojiFajl(TEST_AUTOMOBILI));
    EXPECT_EQ("", procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{SacuvajAutomobile_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u slucaju kada fajl vec postoji i ima sadrzaj.
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sadrzajem "stari sadrzaj koji treba nestati".
 * 2. Postaviti globalno stanje sa 1 automobilom:
 *  * {id = 1, "Fiat", "Punto", 2015, 30.0, dostupan = 1}
 * 3. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_OK.
 * 2. Sadrzaj fajla je tacno "1;Fiat;Punto;2015;30.00;1" (stari sadrzaj je u potpunosti zamijenjen).
 * \endfield
 */
TEST_F(Fajlovi, SacuvajAutomobile_PrepisujePostojeciSadrzaj)
{
    upisiFajl(TEST_AUTOMOBILI, "stari sadrzaj koji treba nestati\n");
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);

    ASSERT_EQ(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    EXPECT_EQ("1;Fiat;Punto;2015;30.00;1\n", procitajFajl(TEST_AUTOMOBILI));
}

/**
 * \tracehead{SacuvajAutomobile_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u slucaju kada fajl ne moze biti otvoren za pisanje (negativan test - folder ne postoji).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 automobilom.
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = putanja u folderu koji ne postoji
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_FILE_ERROR.
 * 2. Ispisana je poruka "Greska pri radu sa fajlom." zajedno sa putanjom fajla.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajAutomobile_NevalidnaPutanjaVracaGresku)
{
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);

    ::testing::internal::CaptureStdout();
    RentStatus status = sacuvajAutomobile(NEVALIDNA_PUTANJA);
    std::string ispis = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(RENT_FILE_ERROR, status);
    EXPECT_NE(std::string::npos, ispis.find("Greska pri radu sa fajlom."));
    EXPECT_NE(std::string::npos, ispis.find(NEVALIDNA_PUTANJA));
}

/**
 * \tracehead{SacuvajAutomobile_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u slucaju kada je parametar putanja NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajAutomobile_NullPutanjaVracaNullPointer)
{
    EXPECT_EQ(RENT_NULL_POINTER, sacuvajAutomobile(NULL));
}

/**
 * \tracehead{SacuvajAutomobile_TC_05, Funkcionalni test}
 * Test provjerava da se podaci sacuvani funkcijom "sacuvajAutomobile" ponovo ucitavaju funkcijom "ucitajAutomobile" bez gubitka ili izmjene (kompatibilnost formata pisanja i citanja).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 2 automobila:
 *  * {id = 4, "Volkswagen", "Golf", 2020, 45.5, dostupan = 1}
 *  * {id = 9, "Skoda", "Octavia", 2019, 60.0, dostupan = 0}
 * 2. Pozvati funkciju sacuvajAutomobile sa privremenim fajlom.
 * 3. Resetovati globalno stanje.
 * 4. Pozvati funkciju ucitajAutomobile sa istim privremenim fajlom.
 * 5. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Obje funkcije vracaju RENT_OK.
 * 2. Vrijednost brojAutomobila je jednaka 2.
 * 3. Svi podaci oba automobila su identicni podacima prije cuvanja.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajAutomobile_CuvanjeIUcitavanjeDajuIstePodatke)
{
    dodajAuto(4, "Volkswagen", "Golf", 2020, 45.5f, 1);
    dodajAuto(9, "Skoda", "Octavia", 2019, 60.0f, 0);

    ASSERT_EQ(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    resetujStanje();
    ASSERT_EQ(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));

    ASSERT_EQ(2, brojAutomobila);
    EXPECT_EQ(4, automobili[0].id);
    EXPECT_STREQ("Volkswagen", automobili[0].marka);
    EXPECT_STREQ("Golf", automobili[0].model);
    EXPECT_EQ(2020, automobili[0].godiste);
    EXPECT_FLOAT_EQ(45.5f, automobili[0].cijena_po_danu);
    EXPECT_EQ(1, automobili[0].dostupan);
    EXPECT_EQ(9, automobili[1].id);
    EXPECT_STREQ("Skoda", automobili[1].marka);
    EXPECT_EQ(0, automobili[1].dostupan);
}

/* ======================= ucitajIznajmljivanja ======================= */

/**
 * \tracehead{UcitajIznajmljivanja_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajIznajmljivanja" u slucaju kada fajl ne postoji.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojIznajmljivanja = 5 (simulira prethodno ucitane podatke)
 * 2. Obezbijediti da privremeni fajl ne postoji.
 * 3. Pozvati funkciju ucitajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = privremeni fajl koji ne postoji
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajIznajmljivanja vraca RENT_FILE_ERROR.
 * 2. Vrijednost brojIznajmljivanja je jednaka 0.
 * \endfield
 */
TEST_F(Fajlovi, UcitajIznajmljivanja_NepostojeciFajlDajePraznuListu)
{
    brojIznajmljivanja = 5;

    EXPECT_EQ(RENT_FILE_ERROR, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    EXPECT_EQ(0, brojIznajmljivanja);
}

/**
 * \tracehead{UcitajIznajmljivanja_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajIznajmljivanja" u slucaju kada fajl sadrzi validne linije.
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sljedecim sadrzajem:
 *  * "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1"
 *  * "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0"
 * 2. Pozvati funkciju ucitajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajIznajmljivanja vraca RENT_OK.
 * 2. Vrijednost brojIznajmljivanja je jednaka 2.
 * 3. Svih 9 polja prvog zapisa je ispravno ucitano, a drugi zapis ima id = 2 i aktivno = 0.
 * \endfield
 */
TEST_F(Fajlovi, UcitajIznajmljivanja_ValidneLinijeSeUcitavaju)
{
    upisiFajl(TEST_IZNAJMLJIVANJA,
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
        "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0\n");

    ASSERT_EQ(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    ASSERT_EQ(2, brojIznajmljivanja);

    EXPECT_EQ(1, iznajmljivanja[0].id);
    EXPECT_EQ(3, iznajmljivanja[0].id_automobila);
    EXPECT_STREQ("Marina", iznajmljivanja[0].ime);
    EXPECT_STREQ("Gogic", iznajmljivanja[0].prezime);
    EXPECT_STREQ("27-07-2026", iznajmljivanja[0].datum_pocetka);
    EXPECT_STREQ("28-07-2026", iznajmljivanja[0].datum_kraja);
    EXPECT_EQ(1, iznajmljivanja[0].broj_dana);
    EXPECT_FLOAT_EQ(90.00f, iznajmljivanja[0].ukupna_cijena);
    EXPECT_EQ(1, iznajmljivanja[0].aktivno);

    EXPECT_EQ(2, iznajmljivanja[1].id);
    EXPECT_EQ(0, iznajmljivanja[1].aktivno);
}

/**
 * \tracehead{UcitajIznajmljivanja_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajIznajmljivanja" u slucaju kada fajl, pored validnih, sadrzi i nevalidne linije (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa sljedecim sadrzajem:
 *  * "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1"
 *  * "1;3;Marina" (nepotpuna linija)
 *  * "" (prazna linija)
 *  * "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0"
 * 2. Pozvati funkciju ucitajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajIznajmljivanja vraca RENT_OK.
 * 2. Vrijednost brojIznajmljivanja je jednaka 2 (nevalidne linije su preskocene).
 * \endfield
 */
TEST_F(Fajlovi, UcitajIznajmljivanja_NevalidneLinijeSePreskacu)
{
    upisiFajl(TEST_IZNAJMLJIVANJA,
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
        "1;3;Marina\n"
        "\n"
        "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0\n");

    ASSERT_EQ(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    ASSERT_EQ(2, brojIznajmljivanja);
    EXPECT_EQ(1, iznajmljivanja[0].id);
    EXPECT_EQ(2, iznajmljivanja[1].id);
}

/**
 * \tracehead{UcitajIznajmljivanja_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajIznajmljivanja" u slucaju kada fajl sadrzi vise zapisa nego sto niz moze da primi (analiza granicnih vrijednosti - MAX_IZNAJMLJIVANJA + 1).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa MAX_IZNAJMLJIVANJA + 1 (201) validnih linija, sa id vrijednostima od 1 do 201.
 * 2. Pozvati funkciju ucitajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajIznajmljivanja vraca RENT_OK.
 * 2. Vrijednost brojIznajmljivanja je jednaka MAX_IZNAJMLJIVANJA (200).
 * 3. Posljednji ucitani zapis ima id = 200 (nema prekoracenja niza).
 * \endfield
 */
TEST_F(Fajlovi, UcitajIznajmljivanja_NeUcitavaViseOdMaksimuma)
{
    std::string sadrzaj;
    for (int i = 1; i <= MAX_IZNAJMLJIVANJA + 1; i++)
    {
        sadrzaj += std::to_string(i) + ";1;Ime;Prezime;01-01-2026;02-01-2026;1;50.00;0\n";
    }
    upisiFajl(TEST_IZNAJMLJIVANJA, sadrzaj);

    ASSERT_EQ(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    EXPECT_EQ(MAX_IZNAJMLJIVANJA, brojIznajmljivanja);
    EXPECT_EQ(MAX_IZNAJMLJIVANJA, iznajmljivanja[MAX_IZNAJMLJIVANJA - 1].id);
}

/**
 * \tracehead{UcitajIznajmljivanja_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajIznajmljivanja" u slucaju kada je parametar putanja NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju ucitajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajIznajmljivanja vraca RENT_NULL_POINTER.
 * 2. Vrijednost brojIznajmljivanja je jednaka 0.
 * \endfield
 */
TEST_F(Fajlovi, UcitajIznajmljivanja_NullPutanjaVracaNullPointer)
{
    EXPECT_EQ(RENT_NULL_POINTER, ucitajIznajmljivanja(NULL));
    EXPECT_EQ(0, brojIznajmljivanja);
}

/* ======================= sacuvajIznajmljivanja ======================= */

/**
 * \tracehead{SacuvajIznajmljivanja_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajIznajmljivanja" u pogledu tacnog sadrzaja i formata upisanog fajla.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 2 zapisa:
 *  * {id = 1, id_automobila = 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1 dan, 90.0, aktivno = 1}
 *  * {id = 2, id_automobila = 5, "Marko", "Markovic", "01-01-2026", "05-01-2026", 4 dana, 200.0, aktivno = 0}
 * 2. Pozvati funkciju sacuvajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajIznajmljivanja vraca RENT_OK.
 * 2. Sadrzaj fajla je tacno:
 *  * "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1"
 *  * "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0"
 * \endfield
 */
TEST_F(Fajlovi, SacuvajIznajmljivanja_TacanSadrzajFajla)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);
    dodajIznajmljivanje(2, 5, "Marko", "Markovic", "01-01-2026", "05-01-2026", 4, 200.0f, 0);

    ASSERT_EQ(RENT_OK, sacuvajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    EXPECT_EQ(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
        "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0\n",
        procitajFajl(TEST_IZNAJMLJIVANJA));
}

/**
 * \tracehead{SacuvajIznajmljivanja_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajIznajmljivanja" u slucaju kada je niz zapisa prazan (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojIznajmljivanja = 0
 * 2. Pozvati funkciju sacuvajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajIznajmljivanja vraca RENT_OK.
 * 2. Fajl je napravljen i prazan je.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajIznajmljivanja_PrazanNizPraviPrazanFajl)
{
    ASSERT_EQ(RENT_OK, sacuvajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    EXPECT_TRUE(postojiFajl(TEST_IZNAJMLJIVANJA));
    EXPECT_EQ("", procitajFajl(TEST_IZNAJMLJIVANJA));
}

/**
 * \tracehead{SacuvajIznajmljivanja_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajIznajmljivanja" u slucaju kada fajl ne moze biti otvoren za pisanje (negativan test - folder ne postoji).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 zapisom.
 * 2. Zapoceti hvatanje standardnog izlaza.
 * 3. Pozvati funkciju sacuvajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = putanja u folderu koji ne postoji
 * 4. Zavrsiti hvatanje standardnog izlaza i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajIznajmljivanja vraca RENT_FILE_ERROR.
 * 2. Ispisana je poruka "Greska pri radu sa fajlom." zajedno sa putanjom fajla.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajIznajmljivanja_NevalidnaPutanjaVracaGresku)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);

    ::testing::internal::CaptureStdout();
    RentStatus status = sacuvajIznajmljivanja(NEVALIDNA_PUTANJA);
    std::string ispis = ::testing::internal::GetCapturedStdout();

    EXPECT_EQ(RENT_FILE_ERROR, status);
    EXPECT_NE(std::string::npos, ispis.find("Greska pri radu sa fajlom."));
    EXPECT_NE(std::string::npos, ispis.find(NEVALIDNA_PUTANJA));
}

/**
 * \tracehead{SacuvajIznajmljivanja_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajIznajmljivanja" u slucaju kada je parametar putanja NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju sacuvajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajIznajmljivanja vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajIznajmljivanja_NullPutanjaVracaNullPointer)
{
    EXPECT_EQ(RENT_NULL_POINTER, sacuvajIznajmljivanja(NULL));
}

/**
 * \tracehead{SacuvajIznajmljivanja_TC_04, Funkcionalni test}
 * Test provjerava da se podaci sacuvani funkcijom "sacuvajIznajmljivanja" ponovo ucitavaju funkcijom "ucitajIznajmljivanja" bez gubitka ili izmjene (kompatibilnost formata pisanja i citanja).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 zapisom:
 *  * {id = 7, id_automobila = 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1 dan, 90.0, aktivno = 1}
 * 2. Pozvati funkciju sacuvajIznajmljivanja sa privremenim fajlom.
 * 3. Resetovati globalno stanje.
 * 4. Pozvati funkciju ucitajIznajmljivanja sa istim privremenim fajlom.
 * 5. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Obje funkcije vracaju RENT_OK.
 * 2. Vrijednost brojIznajmljivanja je jednaka 1.
 * 3. Svih 9 polja zapisa je identicno podacima prije cuvanja.
 * \endfield
 */
TEST_F(Fajlovi, SacuvajIznajmljivanja_CuvanjeIUcitavanjeDajuIstePodatke)
{
    dodajIznajmljivanje(7, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);

    ASSERT_EQ(RENT_OK, sacuvajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    resetujStanje();
    ASSERT_EQ(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));

    ASSERT_EQ(1, brojIznajmljivanja);
    EXPECT_EQ(7, iznajmljivanja[0].id);
    EXPECT_EQ(3, iznajmljivanja[0].id_automobila);
    EXPECT_STREQ("Marina", iznajmljivanja[0].ime);
    EXPECT_STREQ("Gogic", iznajmljivanja[0].prezime);
    EXPECT_STREQ("27-07-2026", iznajmljivanja[0].datum_pocetka);
    EXPECT_STREQ("28-07-2026", iznajmljivanja[0].datum_kraja);
    EXPECT_EQ(1, iznajmljivanja[0].broj_dana);
    EXPECT_FLOAT_EQ(90.0f, iznajmljivanja[0].ukupna_cijena);
    EXPECT_EQ(1, iznajmljivanja[0].aktivno);
}
