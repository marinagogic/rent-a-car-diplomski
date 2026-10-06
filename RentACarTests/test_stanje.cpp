/**
 * \file test_stanje.cpp
 *
 * \brief Google Test jedinicni testovi za pomocne funkcije nad globalnim
 *        stanjem rent-a-car sistema (rent_a_car_stanje.h/.c).
 *
 * Funkcije koje se testiraju zavise od globalnih nizova, pa se koristi
 * fixture klasa \ref GlobalnoStanje koja prije svakog testa vraca globalno
 * stanje na pocetne vrijednosti. Time se obezbjedjuje da su testovi
 * nezavisni jedni od drugih, bez obzira na redoslijed izvrsavanja.
 */

 //#include "pch.h"
#include "gtest/gtest.h"
#include <string.h>

extern "C" {
#include "rent_a_car_stanje.h"
}

/**
 * \brief Fixture klasa koja resetuje globalno stanje prije i poslije svakog testa.
 *
 * Sadrzi i pomocne metode za dodavanje elemenata u globalne nizove, kako bi
 * testovi bili kraci i citljiviji.
 */
class GlobalnoStanje : public ::testing::Test
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

    /** Dodaje automobil sa datim ID-om na kraj globalnog niza. */
    static void dodajAuto(int id)
    {
        automobili[brojAutomobila].id = id;
        brojAutomobila++;
    }

    /** Dodaje zapis o iznajmljivanju sa datim ID-om na kraj globalnog niza. */
    static void dodajIznajmljivanje(int id)
    {
        iznajmljivanja[brojIznajmljivanja].id = id;
        brojIznajmljivanja++;
    }
};

/* ======================= sledeciIdAutomobila ======================= */

/**
 * \tracehead{SledeciIdAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdAutomobila" u slucaju kada je niz automobila prazan (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 0
 * 2. Pozvati funkciju sledeciIdAutomobila.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdAutomobila vraca 1.
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdAutomobila_PrazanNizVracaJedan)
{
    EXPECT_EQ(1, sledeciIdAutomobila());
}

/**
 * \tracehead{SledeciIdAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdAutomobila" u slucaju kada niz sadrzi tacno jedan automobil (analiza granicnih vrijednosti - najmanji neprazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 1
 *  * brojAutomobila = 1
 * 2. Pozvati funkciju sledeciIdAutomobila.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdAutomobila vraca 2.
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdAutomobila_JedanElementVracaDva)
{
    dodajAuto(1);
    EXPECT_EQ(2, sledeciIdAutomobila());
}

/**
 * \tracehead{SledeciIdAutomobila_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdAutomobila" u slucaju kada najveci ID nije na posljednjoj poziciji niza.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 1, automobili[1].id = 5, automobili[2].id = 3
 *  * brojAutomobila = 3
 * 2. Pozvati funkciju sledeciIdAutomobila.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdAutomobila vraca 6 (najveci ID + 1, a ne posljednji ID + 1).
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdAutomobila_NajveciIdNijePosljednji)
{
    dodajAuto(1);
    dodajAuto(5);
    dodajAuto(3);
    EXPECT_EQ(6, sledeciIdAutomobila());
}

/**
 * \tracehead{SledeciIdAutomobila_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdAutomobila" u slucaju kada u nizu postoji "rupa" u ID-ovima, npr. nakon brisanja automobila.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 1, automobili[1].id = 3
 *  * brojAutomobila = 2
 * 2. Pozvati funkciju sledeciIdAutomobila.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdAutomobila vraca 4 (upraznjeni ID 2 se ne koristi ponovo).
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdAutomobila_RupaUIdovimaSeNePopunjava)
{
    dodajAuto(1);
    dodajAuto(3);
    EXPECT_EQ(4, sledeciIdAutomobila());
}

/**
 * \tracehead{SledeciIdAutomobila_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdAutomobila" u slucaju kada se iza posljednjeg validnog elementa u nizu nalazi zaostali podatak (analiza granicnih vrijednosti - element na indeksu brojAutomobila).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 1
 *  * brojAutomobila = 1
 *  * automobili[1].id = 99 (van opsega validnih elemenata)
 * 2. Pozvati funkciju sledeciIdAutomobila.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdAutomobila vraca 2 (element van opsega brojAutomobila se ignorise).
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdAutomobila_IgnoriseElementeVanOpsega)
{
    dodajAuto(1);
    automobili[1].id = 99;
    EXPECT_EQ(2, sledeciIdAutomobila());
}

/* ======================= sledeciIdIznajmljivanja ======================= */

/**
 * \tracehead{SledeciIdIznajmljivanja_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdIznajmljivanja" u slucaju kada je niz iznajmljivanja prazan (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojIznajmljivanja = 0
 * 2. Pozvati funkciju sledeciIdIznajmljivanja.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdIznajmljivanja vraca 1.
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdIznajmljivanja_PrazanNizVracaJedan)
{
    EXPECT_EQ(1, sledeciIdIznajmljivanja());
}

/**
 * \tracehead{SledeciIdIznajmljivanja_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdIznajmljivanja" u slucaju kada niz sadrzi tacno jedan zapis (analiza granicnih vrijednosti - najmanji neprazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0].id = 1
 *  * brojIznajmljivanja = 1
 * 2. Pozvati funkciju sledeciIdIznajmljivanja.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdIznajmljivanja vraca 2.
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdIznajmljivanja_JedanElementVracaDva)
{
    dodajIznajmljivanje(1);
    EXPECT_EQ(2, sledeciIdIznajmljivanja());
}

/**
 * \tracehead{SledeciIdIznajmljivanja_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdIznajmljivanja" u slucaju kada najveci ID nije na posljednjoj poziciji niza.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0].id = 2, iznajmljivanja[1].id = 7, iznajmljivanja[2].id = 4
 *  * brojIznajmljivanja = 3
 * 2. Pozvati funkciju sledeciIdIznajmljivanja.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdIznajmljivanja vraca 8.
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdIznajmljivanja_NajveciIdNijePosljednji)
{
    dodajIznajmljivanje(2);
    dodajIznajmljivanje(7);
    dodajIznajmljivanje(4);
    EXPECT_EQ(8, sledeciIdIznajmljivanja());
}

/**
 * \tracehead{SledeciIdIznajmljivanja_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sledeciIdIznajmljivanja" u slucaju kada se iza posljednjeg validnog elementa u nizu nalazi zaostali podatak (analiza granicnih vrijednosti - element na indeksu brojIznajmljivanja).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0].id = 1
 *  * brojIznajmljivanja = 1
 *  * iznajmljivanja[1].id = 99 (van opsega validnih elemenata)
 * 2. Pozvati funkciju sledeciIdIznajmljivanja.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sledeciIdIznajmljivanja vraca 2 (element van opsega se ignorise).
 * \endfield
 */
TEST_F(GlobalnoStanje, SledeciIdIznajmljivanja_IgnoriseElementeVanOpsega)
{
    dodajIznajmljivanje(1);
    iznajmljivanja[1].id = 99;
    EXPECT_EQ(2, sledeciIdIznajmljivanja());
}

/* ======================= pronadjiAutomobilPoId ======================= */

/**
 * \tracehead{PronadjiAutomobilPoId_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada je niz automobila prazan (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 0
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 1
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca -1.
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_PrazanNizVracaMinusJedan)
{
    EXPECT_EQ(-1, pronadjiAutomobilPoId(1));
}

/**
 * \tracehead{PronadjiAutomobilPoId_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada se trazeni automobil nalazi na prvoj poziciji niza (analiza granicnih vrijednosti - najmanji moguci indeks).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 10, automobili[1].id = 20, automobili[2].id = 30
 *  * brojAutomobila = 3
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 10
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca 0.
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_PrvaPozicija)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    EXPECT_EQ(0, pronadjiAutomobilPoId(10));
}

/**
 * \tracehead{PronadjiAutomobilPoId_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada se trazeni automobil nalazi u sredini niza (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 10, automobili[1].id = 20, automobili[2].id = 30
 *  * brojAutomobila = 3
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 20
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca 1.
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_SrednjaPozicija)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    EXPECT_EQ(1, pronadjiAutomobilPoId(20));
}

/**
 * \tracehead{PronadjiAutomobilPoId_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada se trazeni automobil nalazi na posljednjoj poziciji niza (analiza granicnih vrijednosti - najveci validan indeks).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 10, automobili[1].id = 20, automobili[2].id = 30
 *  * brojAutomobila = 3
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 30
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca 2.
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_PosljednjaPozicija)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    EXPECT_EQ(2, pronadjiAutomobilPoId(30));
}

/**
 * \tracehead{PronadjiAutomobilPoId_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada automobil sa trazenim ID-om ne postoji u nizu (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 10, automobili[1].id = 20, automobili[2].id = 30
 *  * brojAutomobila = 3
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 99
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca -1.
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_NepostojeciIdVracaMinusJedan)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    EXPECT_EQ(-1, pronadjiAutomobilPoId(99));
}

/**
 * \tracehead{PronadjiAutomobilPoId_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada se automobil sa trazenim ID-om nalazi u nizu, ali iza posljednjeg validnog elementa (analiza granicnih vrijednosti - element na indeksu brojAutomobila).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 10
 *  * brojAutomobila = 1
 *  * automobili[1].id = 20 (van opsega validnih elemenata, npr. zaostao nakon brisanja)
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 20
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca -1 (obrisani automobil se ne pronalazi).
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_IgnoriseElementeVanOpsega)
{
    dodajAuto(10);
    automobili[1].id = 20;
    EXPECT_EQ(-1, pronadjiAutomobilPoId(20));
}

/**
 * \tracehead{PronadjiAutomobilPoId_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAutomobilPoId" u slucaju kada vise automobila ima isti ID (nekonzistentni podaci, npr. rucno izmijenjen fajl).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0].id = 10, automobili[1].id = 20, automobili[2].id = 20
 *  * brojAutomobila = 3
 * 2. Pozvati funkciju pronadjiAutomobilPoId sa sljedecim argumentom:
 *  * id = 20
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAutomobilPoId vraca 1 (indeks prvog pronadjenog elementa).
 * \endfield
 */
TEST_F(GlobalnoStanje, PronadjiAutomobilPoId_DupliranIdVracaPrviIndeks)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(20);
    EXPECT_EQ(1, pronadjiAutomobilPoId(20));
}
