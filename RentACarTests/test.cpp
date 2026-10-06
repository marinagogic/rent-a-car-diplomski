/**
 * \file rent_a_car_tests.cpp
 *
 * \brief Google Test jedinicni testovi za poslovnu logiku rent-a-car sistema.
 *
 * Testovi pokrivaju pozitivne, negativne i granicne (boundary) scenarije za
 * funkcije iz rent_a_car_logic.h/.c, bez zavisnosti od standardnog ulaza/
 * izlaza, globalnog stanja ili rada sa fajlovima.
 */

 //#include "pch.h"
#include "gtest/gtest.h"
#include <string.h>

extern "C" {
#include "rent_a_car_logic.h"
}

/* ======================= jeGodisteValidno ======================= */

/**
 * \tracehead{JeGodisteValidno_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste u sredini dozvoljenog opsega (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = 2020
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 1 (godiste je validno).
 * \endfield
 */
TEST(JeGodisteValidno, ValidnoGodisteUSredini)
{
    EXPECT_EQ(1, jeGodisteValidno(2020));
}

/**
 * \tracehead{JeGodisteValidno_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste jednako donjoj granici MIN_GODISTE (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MIN_GODISTE (1950)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 1 (donja granica je validna vrijednost).
 * \endfield
 */
TEST(JeGodisteValidno, DonjaGranicaJeValidna)
{
    EXPECT_EQ(1, jeGodisteValidno(MIN_GODISTE));
}

/**
 * \tracehead{JeGodisteValidno_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste jednako gornjoj granici MAX_GODISTE (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MAX_GODISTE (2100)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 1 (gornja granica je validna vrijednost).
 * \endfield
 */
TEST(JeGodisteValidno, GornjaGranicaJeValidna)
{
    EXPECT_EQ(1, jeGodisteValidno(MAX_GODISTE));
}

/**
 * \tracehead{JeGodisteValidno_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste tek ispod donje granice (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MIN_GODISTE - 1 (1949)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 0 (godiste nije validno).
 * \endfield
 */
TEST(JeGodisteValidno, IspodDonjeGraniceNijeValidno)
{
    EXPECT_EQ(0, jeGodisteValidno(MIN_GODISTE - 1));
}

/**
 * \tracehead{JeGodisteValidno_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste tek iznad gornje granice (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MAX_GODISTE + 1 (2101)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 0 (godiste nije validno).
 * \endfield
 */
TEST(JeGodisteValidno, IznadGornjeGraniceNijeValidno)
{
    EXPECT_EQ(0, jeGodisteValidno(MAX_GODISTE + 1));
}

/* ======================= jeCijenaValidna ======================= */

/**
 * \tracehead{JeCijenaValidna_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena veca od nule (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = 45.5
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 1 (cijena je validna).
 * \endfield
 */
TEST(JeCijenaValidna, PozitivnaCijenaJeValidna)
{
    EXPECT_EQ(1, jeCijenaValidna(45.5f));
}

/**
 * \tracehead{JeCijenaValidna_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena jednaka nuli (analiza granicnih vrijednosti - granica izmedju nevalidnih i validnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = 0.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 0 (nula nije validna cijena).
 * \endfield
 */
TEST(JeCijenaValidna, NulaNijeValidna)
{
    EXPECT_EQ(0, jeCijenaValidna(0.0f));
}

/**
 * \tracehead{JeCijenaValidna_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena negativna (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = -10.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 0 (cijena nije validna).
 * \endfield
 */
TEST(JeCijenaValidna, NegativnaCijenaNijeValidna)
{
    EXPECT_EQ(0, jeCijenaValidna(-10.0f));
}

/**
 * \tracehead{JeCijenaValidna_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena najmanja cijena koja se moze izraziti u KM sa preciznoscu od dvije decimale, 0.01 KM (analiza granicnih vrijednosti - validna vrijednost neposredno iznad granice 0).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = 0.01
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 1 (cijena je validna).
 * \endfield
 */
TEST(JeCijenaValidna, NajmanjaPozitivnaCijenaJeValidna)
{
    EXPECT_EQ(1, jeCijenaValidna(0.01f));
}

/* ======================= jeBrojDanaValidan ======================= */

/**
 * \tracehead{JeBrojDanaValidan_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana u sredini dozvoljenog opsega (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = 10
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 1 (broj dana je validan).
 * \endfield
 */
TEST(JeBrojDanaValidan, ValidanBrojUSredini)
{
    EXPECT_EQ(1, jeBrojDanaValidan(10));
}

/**
 * \tracehead{JeBrojDanaValidan_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana jednak donjoj granici MIN_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = MIN_BROJ_DANA (1)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 1 (donja granica je validna vrijednost).
 * \endfield
 */
TEST(JeBrojDanaValidan, DonjaGranicaJeValidna)
{
    EXPECT_EQ(1, jeBrojDanaValidan(MIN_BROJ_DANA));
}

/**
 * \tracehead{JeBrojDanaValidan_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana jednak gornjoj granici MAX_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = MAX_BROJ_DANA (365)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 1 (gornja granica je validna vrijednost).
 * \endfield
 */
TEST(JeBrojDanaValidan, GornjaGranicaJeValidna)
{
    EXPECT_EQ(1, jeBrojDanaValidan(MAX_BROJ_DANA));
}

/**
 * \tracehead{JeBrojDanaValidan_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana jednak nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = 0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 0 (broj dana nije validan).
 * \endfield
 */
TEST(JeBrojDanaValidan, NulaNijeValidna)
{
    EXPECT_EQ(0, jeBrojDanaValidan(0));
}

/**
 * \tracehead{JeBrojDanaValidan_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana tek iznad gornje granice (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = MAX_BROJ_DANA + 1 (366)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 0 (broj dana nije validan).
 * \endfield
 */
TEST(JeBrojDanaValidan, IznadGornjeGraniceNijeValidno)
{
    EXPECT_EQ(0, jeBrojDanaValidan(MAX_BROJ_DANA + 1));
}

/**
 * \tracehead{JeBrojDanaValidan_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana negativan (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = -5
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 0 (broj dana nije validan).
 * \endfield
 */
TEST(JeBrojDanaValidan, NegativanBrojNijeValidan)
{
    EXPECT_EQ(0, jeBrojDanaValidan(-5));
}

/* ======================= formatirajStatusAutomobila ======================= */

/**
 * \tracehead{FormatirajStatusAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "formatirajStatusAutomobila" u slucaju kada je automobil dostupan.
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju formatirajStatusAutomobila sa sljedecim argumentom:
 *  * dostupan = 1
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija formatirajStatusAutomobila vraca string "Dostupan".
 * \endfield
 */
TEST(FormatirajStatusAutomobila, DostupanVracaTacanString)
{
    EXPECT_STREQ("Dostupan", formatirajStatusAutomobila(1));
}

/**
 * \tracehead{FormatirajStatusAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "formatirajStatusAutomobila" u slucaju kada je automobil iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju formatirajStatusAutomobila sa sljedecim argumentom:
 *  * dostupan = 0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija formatirajStatusAutomobila vraca string "Iznajmljen".
 * \endfield
 */
TEST(FormatirajStatusAutomobila, IznajmljenVracaTacanString)
{
    EXPECT_STREQ("Iznajmljen", formatirajStatusAutomobila(0));
}

/* ======================= izracunajUkupnuCijenu ======================= */

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada su i broj dana i cijena po danu validni.
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 3
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca 150.0 (3 * 50.0).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, ValidniUlaziDajuTacanRezultat)
{
    EXPECT_FLOAT_EQ(150.0f, izracunajUkupnuCijenu(3, 50.0f));
}

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je broj dana jednak nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 0
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, NevalidanBrojDanaVracaMinusJedan)
{
    EXPECT_FLOAT_EQ(-1.0f, izracunajUkupnuCijenu(0, 50.0f));
}

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada broj dana prelazi gornju granicu (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = MAX_BROJ_DANA + 1 (366)
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, PrekoracenBrojDanaVracaMinusJedan)
{
    EXPECT_FLOAT_EQ(-1.0f, izracunajUkupnuCijenu(MAX_BROJ_DANA + 1, 50.0f));
}

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je cijena po danu jednaka nuli (analiza granicnih vrijednosti - granica izmedju nevalidnih i validnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 3
 *  * cijenaPoDanu = 0.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, NevalidnaCijenaVracaMinusJedan)
{
    EXPECT_FLOAT_EQ(-1.0f, izracunajUkupnuCijenu(3, 0.0f));
}

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je cijena po danu negativna (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 3
 *  * cijenaPoDanu = -20.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, NegativnaCijenaVracaMinusJedan)
{
    EXPECT_FLOAT_EQ(-1.0f, izracunajUkupnuCijenu(3, -20.0f));
}

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je broj dana jednak donjoj granici MIN_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = MIN_BROJ_DANA (1)
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca 50.0 (1 * 50.0).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, DonjaGranicaBrojaDana)
{
    EXPECT_FLOAT_EQ(50.0f, izracunajUkupnuCijenu(MIN_BROJ_DANA, 50.0f));
}

/**
 * \tracehead{IzracunajUkupnuCijenu_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je broj dana jednak gornjoj granici MAX_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = MAX_BROJ_DANA (365)
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca 18250.0 (365 * 50.0).
 * \endfield
 */
TEST(IzracunajUkupnuCijenu, GornjaGranicaBrojaDana)
{
    EXPECT_FLOAT_EQ(18250.0f, izracunajUkupnuCijenu(MAX_BROJ_DANA, 50.0f));
}

/* ======================= jeAutomobilDostupan ======================= */

/**
 * \tracehead{JeAutomobilDostupan_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeAutomobilDostupan" u slucaju kada je automobil dostupan.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 1.
 * 2. Pozvati funkciju jeAutomobilDostupan sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeAutomobilDostupan vraca 1.
 * \endfield
 */
TEST(JeAutomobilDostupan, DostupanAutomobilVracaJedan)
{
    Automobil a = {};
    a.dostupan = 1;
    EXPECT_EQ(1, jeAutomobilDostupan(&a));
}

/**
 * \tracehead{JeAutomobilDostupan_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeAutomobilDostupan" u slucaju kada je automobil iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Pozvati funkciju jeAutomobilDostupan sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeAutomobilDostupan vraca 0.
 * \endfield
 */
TEST(JeAutomobilDostupan, IznajmljenAutomobilVracaNulu)
{
    Automobil a = {};
    a.dostupan = 0;
    EXPECT_EQ(0, jeAutomobilDostupan(&a));
}

/**
 * \tracehead{JeAutomobilDostupan_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeAutomobilDostupan" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeAutomobilDostupan sa sljedecim argumentom:
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeAutomobilDostupan vraca 0 i ne dolazi do pada programa.
 * \endfield
 */
TEST(JeAutomobilDostupan, NullPokazivacVracaNulu)
{
    EXPECT_EQ(0, jeAutomobilDostupan(NULL));
}

/* ======================= validirajAutomobil ======================= */

/**
 * \tracehead{ValidirajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada su godiste i cijena automobila validni.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa sljedecim vrijednostima:
 *  * godiste = 2020
 *  * cijena_po_danu = 45.0
 * 2. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_OK.
 * \endfield
 */
TEST(ValidirajAutomobil, ValidanAutomobilVracaOk)
{
    Automobil a = {};
    a.godiste = 2020;
    a.cijena_po_danu = 45.0f;
    EXPECT_EQ(RENT_OK, validirajAutomobil(&a));
}

/**
 * \tracehead{ValidirajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada godiste automobila nije u dozvoljenom opsegu.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa sljedecim vrijednostima:
 *  * godiste = 1900
 *  * cijena_po_danu = 45.0
 * 2. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_INVALID_YEAR.
 * \endfield
 */
TEST(ValidirajAutomobil, NevalidnoGodisteVracaInvalidYear)
{
    Automobil a = {};
    a.godiste = 1900;
    a.cijena_po_danu = 45.0f;
    EXPECT_EQ(RENT_INVALID_YEAR, validirajAutomobil(&a));
}

/**
 * \tracehead{ValidirajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada je godiste validno, ali cijena po danu nije validna.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa sljedecim vrijednostima:
 *  * godiste = 2020
 *  * cijena_po_danu = -5.0
 * 2. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_INVALID_PRICE.
 * \endfield
 */
TEST(ValidirajAutomobil, NevalidnaCijenaVracaInvalidPrice)
{
    Automobil a = {};
    a.godiste = 2020;
    a.cijena_po_danu = -5.0f;
    EXPECT_EQ(RENT_INVALID_PRICE, validirajAutomobil(&a));
}

/**
 * \tracehead{ValidirajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ValidirajAutomobil, NullPokazivacVracaNullPointer)
{
    EXPECT_EQ(RENT_NULL_POINTER, validirajAutomobil(NULL));
}

/* ======================= kreirajAutomobil ======================= */

/**
 * \tracehead{KreirajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada su svi ulazni podaci validni.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Struktura "a" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijena_po_danu = 45.0
 *  * dostupan = 1 (novi automobil je dostupan).
 * \endfield
 */
TEST(KreirajAutomobil, ValidniPodaciPopunjavajuStrukturu)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 2020, 45.0f);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(1, a.id);
    EXPECT_STREQ("Volkswagen", a.marka);
    EXPECT_STREQ("Golf", a.model);
    EXPECT_EQ(2020, a.godiste);
    EXPECT_FLOAT_EQ(45.0f, a.cijena_po_danu);
    EXPECT_EQ(1, a.dostupan);
}

/**
 * \tracehead{KreirajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada godiste nije u dozvoljenom opsegu.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 1800
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_YEAR.
 * \endfield
 */
TEST(KreirajAutomobil, NevalidnoGodisteVracaGresku)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 1800, 45.0f);
    EXPECT_EQ(RENT_INVALID_YEAR, status);
}

/**
 * \tracehead{KreirajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je parametar marka NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = NULL
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(KreirajAutomobil, NullMarkaVracaNullPointer)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, NULL, "Golf", 2020, 45.0f);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{KreirajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je parametar model NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = NULL
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(KreirajAutomobil, NullModelVracaNullPointer)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", NULL, 2020, 45.0f);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{KreirajAutomobil_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je parametar noviAutomobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = NULL
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_NULL_POINTER i ne dolazi do pada programa.
 * \endfield
 */
TEST(KreirajAutomobil, NullAutomobilVracaNullPointer)
{
    RentStatus status = kreirajAutomobil(NULL, 1, "Volkswagen", "Golf", 2020, 45.0f);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{KreirajAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je godiste validno, ali cijena po danu nije validna (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = -5.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_PRICE.
 * \endfield
 */
TEST(KreirajAutomobil, NevalidnaCijenaVracaGresku)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 2020, -5.0f);
    EXPECT_EQ(RENT_INVALID_PRICE, status);
}

/**
 * \tracehead{KreirajAutomobil_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je marka znatno duza od maksimalne dozvoljene duzine (podjela na klase ekvivalencije - klasa predugackih stringova).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = string od 40 karaktera
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Duzina stringa a.marka je jednaka DUZINA_STRINGA - 1 (29), tj. marka je skracena i ispravno zavrsena znakom '\0'.
 * \endfield
 */
TEST(KreirajAutomobil, PredugackaMarkaSeSkracuje)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "Golf", 2020, 45.0f);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ((size_t)(DUZINA_STRINGA - 1), strlen(a.marka));
}

/**
 * \tracehead{KreirajAutomobil_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada marka ima tacno DUZINA_STRINGA - 1 (29) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (29 karaktera)
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.marka je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (marka nije skracena).
 * \endfield
 */
TEST(KreirajAutomobil, MarkaNaGraniciDuzineSeNeSkracuje)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "ABCDEFGHIJABCDEFGHIJABCDEFGHI", "Golf", 2020, 45.0f);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.marka);
}

/**
 * \tracehead{KreirajAutomobil_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada marka ima DUZINA_STRINGA (30) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (30 karaktera)
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.marka je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (poslednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
TEST(KreirajAutomobil, MarkaPrekoGraniceDuzineSeSkracuje)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "Golf", 2020, 45.0f);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.marka);
}

/**
 * \tracehead{KreirajAutomobil_TC_09, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada model ima tacno DUZINA_STRINGA - 1 (29) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (29 karaktera)
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.model je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (model nije skracen).
 * \endfield
 */
TEST(KreirajAutomobil, ModelNaGraniciDuzineSeNeSkracuje)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "ABCDEFGHIJABCDEFGHIJABCDEFGHI", 2020, 45.0f);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.model);
}

/**
 * \tracehead{KreirajAutomobil_TC_10, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada model ima DUZINA_STRINGA (30) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (30 karaktera)
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.model je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
TEST(KreirajAutomobil, ModelPrekoGraniceDuzineSeSkracuje)
{
    Automobil a = {};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ", 2020, 45.0f);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.model);
}

/**
 * \tracehead{KreirajAutomobil_TC_11, Funkcionalni test}
 * Test provjerava da funkcija "kreirajAutomobil" ne mijenja izlaznu strukturu kada godiste nije validno (negativan test - stanje izlaznog parametra nakon greske).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil i popuniti ga postojecim podacima:
 *  * id = 7, marka = "Staro", model = "Auto", godiste = 2000, cijena_po_danu = 10.0, dostupan = 0
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 1800
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_YEAR.
 * 2. Struktura "a" je nepromijenjena (sva polja imaju vrijednosti iz koraka 1), tj. funkcija ne upisuje podatke prije uspjesne validacije.
 * \endfield
 */
TEST(KreirajAutomobil, NevalidnoGodisteNeMijenjaStrukturu)
{
    Automobil a = {};
    a.id = 7;
    strcpy(a.marka, "Staro");
    strcpy(a.model, "Auto");
    a.godiste = 2000;
    a.cijena_po_danu = 10.0f;
    a.dostupan = 0;

    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 1800, 45.0f);

    ASSERT_EQ(RENT_INVALID_YEAR, status);
    EXPECT_EQ(7, a.id);
    EXPECT_STREQ("Staro", a.marka);
    EXPECT_STREQ("Auto", a.model);
    EXPECT_EQ(2000, a.godiste);
    EXPECT_FLOAT_EQ(10.0f, a.cijena_po_danu);
    EXPECT_EQ(0, a.dostupan);
}

/**
 * \tracehead{KreirajAutomobil_TC_12, Funkcionalni test}
 * Test provjerava da funkcija "kreirajAutomobil" ne mijenja izlaznu strukturu kada cijena po danu nije validna (negativan test - stanje izlaznog parametra nakon greske).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil i popuniti ga postojecim podacima:
 *  * id = 7, marka = "Staro", model = "Auto", godiste = 2000, cijena_po_danu = 10.0, dostupan = 0
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = -5.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_PRICE.
 * 2. Struktura "a" je nepromijenjena (sva polja imaju vrijednosti iz koraka 1), tj. funkcija ne upisuje podatke prije uspjesne validacije.
 * \endfield
 */
TEST(KreirajAutomobil, NevalidnaCijenaNeMijenjaStrukturu)
{
    Automobil a = {};
    a.id = 7;
    strcpy(a.marka, "Staro");
    strcpy(a.model, "Auto");
    a.godiste = 2000;
    a.cijena_po_danu = 10.0f;
    a.dostupan = 0;

    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 2020, -5.0f);

    ASSERT_EQ(RENT_INVALID_PRICE, status);
    EXPECT_EQ(7, a.id);
    EXPECT_STREQ("Staro", a.marka);
    EXPECT_STREQ("Auto", a.model);
    EXPECT_EQ(2000, a.godiste);
    EXPECT_FLOAT_EQ(10.0f, a.cijena_po_danu);
    EXPECT_EQ(0, a.dostupan);
}

/* ======================= validirajBrisanjeAutomobila ======================= */

/**
 * \tracehead{ValidirajBrisanjeAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajBrisanjeAutomobila" u slucaju kada je automobil dostupan (brisanje je dozvoljeno).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 1.
 * 2. Pozvati funkciju validirajBrisanjeAutomobila sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajBrisanjeAutomobila vraca RENT_OK.
 * \endfield
 */
TEST(ValidirajBrisanjeAutomobila, DostupanAutomobilMozeSeObrisati)
{
    Automobil a = {};
    a.dostupan = 1;
    EXPECT_EQ(RENT_OK, validirajBrisanjeAutomobila(&a));
}

/**
 * \tracehead{ValidirajBrisanjeAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajBrisanjeAutomobila" u slucaju kada je automobil trenutno iznajmljen (brisanje nije dozvoljeno).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Pozvati funkciju validirajBrisanjeAutomobila sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajBrisanjeAutomobila vraca RENT_CAR_NOT_AVAILABLE.
 * \endfield
 */
TEST(ValidirajBrisanjeAutomobila, IznajmljenAutomobilNeMozeSeObrisati)
{
    Automobil a = {};
    a.dostupan = 0;
    EXPECT_EQ(RENT_CAR_NOT_AVAILABLE, validirajBrisanjeAutomobila(&a));
}

/**
 * \tracehead{ValidirajBrisanjeAutomobila_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajBrisanjeAutomobila" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju validirajBrisanjeAutomobila sa sljedecim argumentom:
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajBrisanjeAutomobila vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ValidirajBrisanjeAutomobila, NullPokazivacVracaNullPointer)
{
    EXPECT_EQ(RENT_NULL_POINTER, validirajBrisanjeAutomobila(NULL));
}

/* ======================= obrisiAutomobilNaIndeksu ======================= */

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada se brise element iz sredine niza.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil sa id vrijednostima 1, 2 i 3.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 1
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_OK.
 * 2. Vrijednost brojElemenata je jednaka 2.
 * 3. Element niz[0] ima id = 1 (nepromijenjen).
 * 4. Element niz[1] ima id = 3 (pomjeren sa pozicije 2).
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, BrisanjeIzSredineNizaPomjeraElemente)
{
    Automobil niz[3] = {};
    int brojElemenata = 3;

    niz[0].id = 1;
    niz[1].id = 2;
    niz[2].id = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 1);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(2, brojElemenata);
    EXPECT_EQ(1, niz[0].id);
    EXPECT_EQ(3, niz[1].id);
}

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je indeks jednak broju elemenata niza (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 3 (jednak broju elemenata)
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_INVALID_ID.
 * 2. Vrijednost brojElemenata je jednaka 3 (nepromijenjena).
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, NevalidanIndeksVracaGresku)
{
    Automobil niz[3] = {};
    int brojElemenata = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 3);

    EXPECT_EQ(RENT_INVALID_ID, status);
    EXPECT_EQ(3, brojElemenata);
}

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je parametar niz NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati brojElemenata = 3.
 * 2. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = NULL
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, NullNizVracaNullPointer)
{
    int brojElemenata = 3;
    EXPECT_EQ(RENT_NULL_POINTER, obrisiAutomobilNaIndeksu(NULL, &brojElemenata, 0));
}

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je parametar brojElemenata NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil.
 * 2. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = NULL
 *  * indeks = 0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, NullBrojElemenataVracaNullPointer)
{
    Automobil niz[3] = {};
    EXPECT_EQ(RENT_NULL_POINTER, obrisiAutomobilNaIndeksu(niz, NULL, 0));
}

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je indeks negativan (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = -1
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_INVALID_ID.
 * 2. Vrijednost brojElemenata je jednaka 3 (nepromijenjena).
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, NegativanIndeksVracaGresku)
{
    Automobil niz[3] = {};
    int brojElemenata = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, -1);

    EXPECT_EQ(RENT_INVALID_ID, status);
    EXPECT_EQ(3, brojElemenata);
}

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada se brise poslednji element niza (analiza granicnih vrijednosti - najveci validan indeks).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil sa id vrijednostima 1, 2 i 3.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 2
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_OK.
 * 2. Vrijednost brojElemenata je jednaka 2.
 * 3. Elementi niz[0] i niz[1] imaju id = 1 i id = 2 (nepromijenjeni).
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, BrisanjePoslednjegElementa)
{
    Automobil niz[3] = {};
    int brojElemenata = 3;

    niz[0].id = 1;
    niz[1].id = 2;
    niz[2].id = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 2);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(2, brojElemenata);
    EXPECT_EQ(1, niz[0].id);
    EXPECT_EQ(2, niz[1].id);
}

/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada se brise prvi element niza (analiza granicnih vrijednosti - najmanji validan indeks).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil sa id vrijednostima 1, 2 i 3.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 0
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_OK.
 * 2. Vrijednost brojElemenata je jednaka 2.
 * 3. Element niz[0] ima id = 2 (pomjeren sa pozicije 1).
 * 4. Element niz[1] ima id = 3 (pomjeren sa pozicije 2).
 * \endfield
 */
TEST(ObrisiAutomobilNaIndeksu, BrisanjePrvogElementa)
{
    Automobil niz[3] = {};
    int brojElemenata = 3;

    niz[0].id = 1;
    niz[1].id = 2;
    niz[2].id = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 0);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(2, brojElemenata);
    EXPECT_EQ(2, niz[0].id);
    EXPECT_EQ(3, niz[1].id);
}

/* ======================= pripremiIznajmljivanje ======================= */

/**
 * \tracehead{PripremiIznajmljivanje_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada su svi ulazni podaci validni.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Struktura "r" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * id_automobila = 5
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datum_pocetka = "01-01-2026"
 *  * datum_kraja = "05-01-2026"
 *  * broj_dana = 4
 *  * ukupna_cijena = 200.0 (4 * 50.0)
 *  * aktivno = 1
 * \endfield
 */
TEST(PripremiIznajmljivanje, ValidniPodaciDajuAktivnoIznajmljivanje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(1, r.id);
    EXPECT_EQ(5, r.id_automobila);
    EXPECT_STREQ("Marko", r.ime);
    EXPECT_STREQ("Markovic", r.prezime);
    EXPECT_STREQ("01-01-2026", r.datum_pocetka);
    EXPECT_STREQ("05-01-2026", r.datum_kraja);
    EXPECT_EQ(4, r.broj_dana);
    EXPECT_FLOAT_EQ(200.0f, r.ukupna_cijena);
    EXPECT_EQ(1, r.aktivno);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je broj dana jednak nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "01-01-2026"
 *  * brojDana = 0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_INVALID_DAYS.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NevalidanBrojDanaVracaGresku)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "01-01-2026", 0);

    EXPECT_EQ(RENT_INVALID_DAYS, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je cijena po danu jednaka nuli (analiza granicnih vrijednosti - granica izmedju nevalidnih i validnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 0.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_INVALID_PRICE.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NevalidnaCijenaVracaGresku)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 0.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    EXPECT_EQ(RENT_INVALID_PRICE, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar iznajmljivanje NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = NULL
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NullIznajmljivanjeVracaNullPointer)
{
    RentStatus status = pripremiIznajmljivanje(NULL, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar ime NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = NULL
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NullImeVracaNullPointer)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        NULL, "Markovic", "01-01-2026", "05-01-2026", 4);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar prezime NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = NULL
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NullPrezimeVracaNullPointer)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", NULL, "01-01-2026", "05-01-2026", 4);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar datumPocetka NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = NULL
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NullDatumPocetkaVracaNullPointer)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", NULL, "05-01-2026", 4);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar datumKraja NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = NULL
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(PripremiIznajmljivanje, NullDatumKrajaVracaNullPointer)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", NULL, 4);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je broj dana jednak donjoj granici MIN_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "02-01-2026"
 *  * brojDana = MIN_BROJ_DANA (1)
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.broj_dana je jednaka 1.
 * 3. Vrijednost r.ukupna_cijena je jednaka 50.0 (1 * 50.0).
 * \endfield
 */
TEST(PripremiIznajmljivanje, DonjaGranicaBrojaDanaJeValidna)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "02-01-2026", MIN_BROJ_DANA);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(MIN_BROJ_DANA, r.broj_dana);
    EXPECT_FLOAT_EQ(50.0f, r.ukupna_cijena);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_09, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je broj dana jednak gornjoj granici MAX_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "01-01-2027"
 *  * brojDana = MAX_BROJ_DANA (365)
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.broj_dana je jednaka 365.
 * 3. Vrijednost r.ukupna_cijena je jednaka 18250.0 (365 * 50.0).
 * \endfield
 */
TEST(PripremiIznajmljivanje, GornjaGranicaBrojaDanaJeValidna)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "01-01-2027", MAX_BROJ_DANA);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(MAX_BROJ_DANA, r.broj_dana);
    EXPECT_FLOAT_EQ(18250.0f, r.ukupna_cijena);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_10, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada broj dana prelazi gornju granicu (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "02-01-2027"
 *  * brojDana = MAX_BROJ_DANA + 1 (366)
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_INVALID_DAYS.
 * \endfield
 */
TEST(PripremiIznajmljivanje, PrekoracenBrojDanaVracaGresku)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "02-01-2027", MAX_BROJ_DANA + 1);

    EXPECT_EQ(RENT_INVALID_DAYS, status);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_11, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada ime ima tacno DUZINA_IMENA - 1 (49) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (49 karaktera)
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.ime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (ime nije skraceno).
 * \endfield
 */
TEST(PripremiIznajmljivanje, ImeNaGraniciDuzineSeNeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", "Markovic", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.ime);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_12, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada ime ima DUZINA_IMENA (50) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (50 karaktera)
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.ime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
TEST(PripremiIznajmljivanje, ImePrekoGraniceDuzineSeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "Markovic", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.ime);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_13, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada prezime ima tacno DUZINA_IMENA - 1 (49) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (49 karaktera)
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.prezime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (prezime nije skracen).
 * \endfield
 */
TEST(PripremiIznajmljivanje, PrezimeNaGraniciDuzineSeNeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.prezime);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_14, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada prezime ima DUZINA_IMENA (50) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (50 karaktera)
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.prezime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
TEST(PripremiIznajmljivanje, PrezimePrekoGraniceDuzineSeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.prezime);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_15, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum pocetka ima tacno DUZINA_DATUMA - 1 (10) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026" (10 karaktera)
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_pocetka je jednaka "01-01-2026" (datum pocetka nije skracen).
 * \endfield
 */
TEST(PripremiIznajmljivanje, DatumPocetkaNaGraniciDuzineSeNeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("01-01-2026", r.datum_pocetka);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_16, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum pocetka ima DUZINA_DATUMA (11) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-20260" (11 karaktera)
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_pocetka je jednaka "01-01-2026" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
TEST(PripremiIznajmljivanje, DatumPocetkaPrekoGraniceDuzineSeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-20260", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("01-01-2026", r.datum_pocetka);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_17, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum kraja ima tacno DUZINA_DATUMA - 1 (10) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026" (10 karaktera)
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_kraja je jednaka "05-01-2026" (datum kraja nije skracen).
 * \endfield
 */
TEST(PripremiIznajmljivanje, DatumKrajaNaGraniciDuzineSeNeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("05-01-2026", r.datum_kraja);
}

/**
 * \tracehead{PripremiIznajmljivanje_TC_18, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum kraja ima DUZINA_DATUMA (11) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-20260" (11 karaktera)
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_kraja je jednaka "05-01-2026" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
TEST(PripremiIznajmljivanje, DatumKrajaPrekoGraniceDuzineSeSkracuje)
{
    Iznajmljivanje r = {};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-20260", 4);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_STREQ("05-01-2026", r.datum_kraja);
}

/* ======================= obradiVracanjeAutomobila ======================= */

/**
 * \tracehead{ObradiVracanjeAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je automobil iznajmljen i aktivan zapis o iznajmljivanju je pronadjen.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje sa aktivno = 1.
 * 3. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = adresa testnog automobila "a"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_OK.
 * 2. Vrijednost a.dostupan je jednaka 1 (automobil je ponovo dostupan).
 * 3. Vrijednost r.aktivno je jednaka 0 (iznajmljivanje je zavrseno).
 * \endfield
 */
TEST(ObradiVracanjeAutomobila, VracanjeSaPronadjenimZapisom)
{
    Automobil a = {};
    Iznajmljivanje r = {};
    a.dostupan = 0;
    r.aktivno = 1;

    RentStatus status = obradiVracanjeAutomobila(&a, &r);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(1, a.dostupan);
    EXPECT_EQ(0, r.aktivno);
}

/**
 * \tracehead{ObradiVracanjeAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je automobil iznajmljen, ali aktivan zapis o iznajmljivanju nije pronadjen.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = adresa testnog automobila "a"
 *  * iznajmljivanje = NULL
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_RENTAL_NOT_FOUND.
 * 2. Vrijednost a.dostupan je jednaka 1 (status automobila se ipak azurira).
 * \endfield
 */
TEST(ObradiVracanjeAutomobila, VracanjeBezPronadjenogZapisa)
{
    Automobil a = {};
    a.dostupan = 0;

    RentStatus status = obradiVracanjeAutomobila(&a, NULL);

    EXPECT_EQ(RENT_RENTAL_NOT_FOUND, status);
    EXPECT_EQ(1, a.dostupan); /* status automobila se ipak azurira */
}

/**
 * \tracehead{ObradiVracanjeAutomobila_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je automobil vec dostupan (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 1.
 * 2. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = adresa testnog automobila "a"
 *  * iznajmljivanje = NULL
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_CAR_ALREADY_AVAILABLE.
 * \endfield
 */
TEST(ObradiVracanjeAutomobila, AutomobilKojiVecNijeIznajmljen)
{
    Automobil a = {};
    a.dostupan = 1;

    RentStatus status = obradiVracanjeAutomobila(&a, NULL);

    EXPECT_EQ(RENT_CAR_ALREADY_AVAILABLE, status);
}

/**
 * \tracehead{ObradiVracanjeAutomobila_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje sa aktivno = 1.
 * 2. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = NULL
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ObradiVracanjeAutomobila, NullAutomobilVracaNullPointer)
{
    Iznajmljivanje r = {};
    r.aktivno = 1;
    EXPECT_EQ(RENT_NULL_POINTER, obradiVracanjeAutomobila(NULL, &r));
}

/* ======================= pronadjiAktivnoIznajmljivanjeZaAuto ======================= */

/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada niz sadrzi neaktivno i aktivno iznajmljivanje za isti automobil.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 0
 *  * niz[1]: id_automobila = 5, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca 1 (indeks aktivnog iznajmljivanja).
 * \endfield
 */
TEST(PronadjiAktivnoIznajmljivanjeZaAuto, PronalaziAktivanZapis)
{
    Iznajmljivanje niz[2] = {};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 0;
    niz[1].id_automobila = 5;
    niz[1].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    EXPECT_EQ(1, indeks);
}

/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada ne postoji aktivno iznajmljivanje za dati automobil.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 0
 *  * niz[1]: id_automobila = 5, aktivno = 0
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca -1 (aktivno iznajmljivanje nije pronadjeno).
 * \endfield
 */
TEST(PronadjiAktivnoIznajmljivanjeZaAuto, VracaMinusJedanAkoNemaAktivnog)
{
    Iznajmljivanje niz[2] = {};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 0;
    niz[1].id_automobila = 5;
    niz[1].aktivno = 0;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    EXPECT_EQ(-1, indeks);
}

/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada je parametar niz NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = NULL
 *  * brojElemenata = 0
 *  * idAutomobila = 5
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca -1.
 * \endfield
 */
TEST(PronadjiAktivnoIznajmljivanjeZaAuto, NullNizVracaMinusJedan)
{
    EXPECT_EQ(-1, pronadjiAktivnoIznajmljivanjeZaAuto(NULL, 0, 5));
}

/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada niz sadrzi aktivno iznajmljivanje za drugi automobil prije aktivnog iznajmljivanja za trazeni automobil.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 7, aktivno = 1
 *  * niz[1]: id_automobila = 5, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca 1 (aktivno iznajmljivanje drugog automobila se preskace).
 * \endfield
 */
TEST(PronadjiAktivnoIznajmljivanjeZaAuto, PreskaceAktivanZapisDrugogAutomobila)
{
    Iznajmljivanje niz[2] = {};
    niz[0].id_automobila = 7;
    niz[0].aktivno = 1;
    niz[1].id_automobila = 5;
    niz[1].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    EXPECT_EQ(1, indeks);
}

/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada je broj elemenata niza jednak nuli (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 1 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 0
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca -1 (niz se tretira kao prazan, iako niz[0] sadrzi aktivan zapis za trazeni automobil).
 * \endfield
 */
TEST(PronadjiAktivnoIznajmljivanjeZaAuto, PrazanNizVracaMinusJedan)
{
    Iznajmljivanje niz[1] = {};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 0, 5);

    EXPECT_EQ(-1, indeks);
}

/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada se aktivno iznajmljivanje nalazi na prvoj poziciji niza (analiza granicnih vrijednosti - najmanji moguci indeks rezultata).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 1
 *  * niz[1]: id_automobila = 6, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca 0 (indeks prvog elementa).
 * \endfield
 */
TEST(PronadjiAktivnoIznajmljivanjeZaAuto, AktivanZapisNaPrvojPoziciji)
{
    Iznajmljivanje niz[2] = {};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 1;
    niz[1].id_automobila = 6;
    niz[1].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    EXPECT_EQ(0, indeks);
}

/* ======================= parsirajAutomobil ======================= */

/**
 * \tracehead{ParsirajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada linija sadrzi svih 6 ocekivanih polja.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;45.50;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_OK.
 * 2. Struktura "a" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijena_po_danu = 45.50
 *  * dostupan = 1
 * \endfield
 */
TEST(ParsirajAutomobil, ValidnaLinijaSeParsiraUspjesno)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;45.50;1\n", &a);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(1, a.id);
    EXPECT_STREQ("Volkswagen", a.marka);
    EXPECT_STREQ("Golf", a.model);
    EXPECT_EQ(2020, a.godiste);
    EXPECT_FLOAT_EQ(45.50f, a.cijena_po_danu);
    EXPECT_EQ(1, a.dostupan);
}

/**
 * \tracehead{ParsirajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada linija ima manje polja od ocekivanog (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajAutomobil, NepotpunaLinijaVracaParseError)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf\n", &a);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada je linija prazna (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajAutomobil, PraznaLinijaVracaParseError)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("\n", &a);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada je parametar linija NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = NULL
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ParsirajAutomobil, NullLinijaVracaNullPointer)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil(NULL, &a);

    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;45.50;1\n"
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ParsirajAutomobil, NullAutomobilVracaNullPointer)
{
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;45.50;1\n", NULL);
    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (godiste) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;abcd;45.50;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajAutomobil, NenumerickoGodisteVracaParseError)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;abcd;45.50;1\n", &a);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (id) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "abc;Volkswagen;Golf;2020;45.50;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajAutomobil, NenumerickiIdVracaParseError)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("abc;Volkswagen;Golf;2020;45.50;1\n", &a);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (cijena po danu) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;abc;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajAutomobil, NenumerickaCijenaVracaParseError)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;abc;1\n", &a);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajAutomobil_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (dostupan) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;45.50;abc\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajAutomobil, NenumerickoPoljeDostupanVracaParseError)
{
    Automobil a = {};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;45.50;abc\n", &a);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/* ======================= parsirajIznajmljivanje ======================= */

/**
 * \tracehead{ParsirajIznajmljivanje_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada linija sadrzi svih 9 ocekivanih polja.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_OK.
 * 2. Struktura "r" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * id_automobila = 3
 *  * ime = "Marina"
 *  * prezime = "Gogic"
 *  * broj_dana = 1
 *  * ukupna_cijena = 90.00
 *  * aktivno = 1
 * \endfield
 */
TEST(ParsirajIznajmljivanje, ValidnaLinijaSeParsiraUspjesno)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", &r);

    ASSERT_EQ(RENT_OK, status);
    EXPECT_EQ(1, r.id);
    EXPECT_EQ(3, r.id_automobila);
    EXPECT_STREQ("Marina", r.ime);
    EXPECT_STREQ("Gogic", r.prezime);
    EXPECT_EQ(1, r.broj_dana);
    EXPECT_FLOAT_EQ(90.00f, r.ukupna_cijena);
    EXPECT_EQ(1, r.aktivno);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada linija ima manje polja od ocekivanog (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NepotpunaLinijaVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje("1;3;Marina\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada je parametar linija NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = NULL
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NullLinijaVracaNullPointer)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje(NULL, &r);

    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada je parametar iznajmljivanje NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NullIznajmljivanjeVracaNullPointer)
{
    RentStatus status = parsirajIznajmljivanje(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", NULL);

    EXPECT_EQ(RENT_NULL_POINTER, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada je linija prazna (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, PraznaLinijaVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje("\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (broj dana) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;abc;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NenumerickiBrojDanaVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;abc;90.00;1\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (id) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "abc;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NenumerickiIdVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje("abc;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (ID automobila) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;abc;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NenumerickiIdAutomobilaVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje("1;abc;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (ukupna cijena) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;abc;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NenumerickaUkupnaCijenaVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje("1;3;Marina;Gogic;27-07-2026;28-07-2026;1;abc;1\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/**
 * \tracehead{ParsirajIznajmljivanje_TC_09, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (aktivno) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;abc\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
TEST(ParsirajIznajmljivanje, NenumerickoPoljeAktivnoVracaParseError)
{
    Iznajmljivanje r = {};
    RentStatus status = parsirajIznajmljivanje("1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;abc\n", &r);

    EXPECT_EQ(RENT_PARSE_ERROR, status);
}

/* ======================= opisStatusa ======================= */

/**
 * \tracehead{OpisStatusa_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" za prvu grupu RentStatus vrijednosti (pokrivenost naredbi - statement coverage grana switch iskaza).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa redom sa sljedecim argumentima:
 *  * status = RENT_OK
 *  * status = RENT_INVALID_YEAR
 *  * status = RENT_INVALID_PRICE
 *  * status = RENT_INVALID_DAYS
 *  * status = RENT_CAR_NOT_FOUND
 *  * status = RENT_CAR_NOT_AVAILABLE
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa za svaki status kod vraca tacno odgovarajuci opis:
 *  * RENT_OK: "Operacija je uspjesno izvrsena."
 *  * RENT_INVALID_YEAR: "Godiste nije u dozvoljenom opsegu (1950-2100)."
 *  * RENT_INVALID_PRICE: "Cijena po danu mora biti veca od nule."
 *  * RENT_INVALID_DAYS: "Broj dana mora biti u opsegu 1-365."
 *  * RENT_CAR_NOT_FOUND: "Automobil sa datim ID-om ne postoji."
 *  * RENT_CAR_NOT_AVAILABLE: "Automobil je trenutno iznajmljen."
 * \endfield
 */
TEST(OpisStatusa, PrvaGrupaStatusaVracaTacanOpis)
{
    EXPECT_STREQ("Operacija je uspjesno izvrsena.", opisStatusa(RENT_OK));
    EXPECT_STREQ("Godiste nije u dozvoljenom opsegu (1950-2100).", opisStatusa(RENT_INVALID_YEAR));
    EXPECT_STREQ("Cijena po danu mora biti veca od nule.", opisStatusa(RENT_INVALID_PRICE));
    EXPECT_STREQ("Broj dana mora biti u opsegu 1-365.", opisStatusa(RENT_INVALID_DAYS));
    EXPECT_STREQ("Automobil sa datim ID-om ne postoji.", opisStatusa(RENT_CAR_NOT_FOUND));
    EXPECT_STREQ("Automobil je trenutno iznajmljen.", opisStatusa(RENT_CAR_NOT_AVAILABLE));
}

/**
 * \tracehead{OpisStatusa_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" za drugu grupu RentStatus vrijednosti (pokrivenost naredbi - statement coverage grana switch iskaza).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa redom sa sljedecim argumentima:
 *  * status = RENT_NULL_POINTER
 *  * status = RENT_CAR_ALREADY_AVAILABLE
 *  * status = RENT_RENTAL_NOT_FOUND
 *  * status = RENT_LIMIT_REACHED
 *  * status = RENT_PARSE_ERROR
 *  * status = RENT_FILE_ERROR
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa za svaki status kod vraca tacno odgovarajuci opis:
 *  * RENT_NULL_POINTER: "GRESKA: Nevalidan (null) pokazivac."
 *  * RENT_CAR_ALREADY_AVAILABLE: "Ovaj automobil trenutno nije iznajmljen."
 *  * RENT_RENTAL_NOT_FOUND: "Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil."
 *  * RENT_LIMIT_REACHED: "Dostignut je maksimalan dozvoljeni broj zapisa."
 *  * RENT_PARSE_ERROR: "Greska pri parsiranju linije iz fajla."
 *  * RENT_FILE_ERROR: "Greska pri radu sa fajlom."
 * \endfield
 */
TEST(OpisStatusa, DrugaGrupaStatusaVracaTacanOpis)
{
    EXPECT_STREQ("GRESKA: Nevalidan (null) pokazivac.", opisStatusa(RENT_NULL_POINTER));
    EXPECT_STREQ("Ovaj automobil trenutno nije iznajmljen.", opisStatusa(RENT_CAR_ALREADY_AVAILABLE));
    EXPECT_STREQ("Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil.", opisStatusa(RENT_RENTAL_NOT_FOUND));
    EXPECT_STREQ("Dostignut je maksimalan dozvoljeni broj zapisa.", opisStatusa(RENT_LIMIT_REACHED));
    EXPECT_STREQ("Greska pri parsiranju linije iz fajla.", opisStatusa(RENT_PARSE_ERROR));
    EXPECT_STREQ("Greska pri radu sa fajlom.", opisStatusa(RENT_FILE_ERROR));
}

/**
 * \tracehead{OpisStatusa_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" u slucaju kada je status jednak RENT_INVALID_ID (pokrivenost naredbi - statement coverage grana switch iskaza).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa sa sljedecim argumentom:
 *  * status = RENT_INVALID_ID
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa vraca tacno opis "Nevalidan ID.".
 * \endfield
 */
TEST(OpisStatusa, InvalidIdVracaTacanOpis)
{
    EXPECT_STREQ("Nevalidan ID.", opisStatusa(RENT_INVALID_ID));
}

/**
 * \tracehead{OpisStatusa_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" u slucaju kada status nije definisana RentStatus vrijednost (pokrivenost grana - branch coverage default grane, negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa sa sljedecim argumentom:
 *  * status = (RentStatus) 999
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa vraca string "Nepoznat status.".
 * \endfield
 */
TEST(OpisStatusa, NepoznatStatusVracaDefaultOpis)
{
    EXPECT_STREQ("Nepoznat status.", opisStatusa((RentStatus)999));
}