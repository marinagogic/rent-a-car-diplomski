/**
 * \file TestSuite_rent_a_car_stanje.c
 *
 * \brief Parasoft C/C++test jedinicni testovi za pomocne funkcije nad globalnim stanjem (rent_a_car_stanje.c).
 *
 * Funkcije zavise od globalnih nizova, pa setUp() i tearDown() prije i
 * poslije svakog testa vracaju globalno stanje na pocetne vrijednosti.
 *
 * Test slucajevi (ID-jevi u \tracehead) odgovaraju Google Test testovima
 * istog naziva, kako bi se rezultati dva alata mogli direktno porediti.
 */
#include "cpptest.h"

/* CPPTEST_TEST_SUITE_CODE_BEGIN AdditionalIncludes */
#include <string.h>
#include "rent_a_car_stanje.h"
/* CPPTEST_TEST_SUITE_CODE_END AdditionalIncludes */

CPPTEST_CONTEXT("/RentACar/rent_a_car_stanje.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/RentACar/rent_a_car_stanje.c");



EXTERN_C_LINKAGE void TestSuite_rent_a_car_stanje_gtest_testSuiteBegin(void);
EXTERN_C_LINKAGE int TestSuite_rent_a_car_stanje_gtest_callTest(const char*);

CPPTEST_TEST_SUITE(TestSuite_rent_a_car_stanje_gtest);
        CPPTEST_TEST_SUITE_SETUP(TestSuite_rent_a_car_stanje_gtest_testSuiteSetUp);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_PrazanNizVracaJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_JedanElementVracaDva);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_NajveciIdNijePosljednji);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_RupaUIdovimaSeNePopunjava);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_IgnoriseElementeVanOpsega);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_PrazanNizVracaJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_JedanElementVracaDva);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_NajveciIdNijePosljednji);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_IgnoriseElementeVanOpsega);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PrazanNizVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PrvaPozicija);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_SrednjaPozicija);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PosljednjaPozicija);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_NepostojeciIdVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_IgnoriseElementeVanOpsega);
        CPPTEST_TEST(TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_DupliranIdVracaPrviIndeks);
        CPPTEST_TEST_SUITE_TEARDOWN(TestSuite_rent_a_car_stanje_gtest_testSuiteTearDown);
CPPTEST_TEST_SUITE_END();

void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_PrazanNizVracaJedan(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_JedanElementVracaDva(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_NajveciIdNijePosljednji(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_RupaUIdovimaSeNePopunjava(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_IgnoriseElementeVanOpsega(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_PrazanNizVracaJedan(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_JedanElementVracaDva(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_NajveciIdNijePosljednji(void);
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_IgnoriseElementeVanOpsega(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PrazanNizVracaMinusJedan(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PrvaPozicija(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_SrednjaPozicija(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PosljednjaPozicija(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_NepostojeciIdVracaMinusJedan(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_IgnoriseElementeVanOpsega(void);
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_DupliranIdVracaPrviIndeks(void);

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_rent_a_car_stanje_gtest);

/* ------------------------------------------------------------------ */
/* Pomocne funkcije                                                    */
/* ------------------------------------------------------------------ */

/** Vraca globalne nizove i brojace na pocetne vrijednosti. */
static void resetujStanje(void)
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

/* ------------------------------------------------------------------ */
/* setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */

void TestSuite_rent_a_car_stanje_gtest_testSuiteSetUp(void);
void TestSuite_rent_a_car_stanje_gtest_testSuiteSetUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteSetUp */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteSetUp */
}

void TestSuite_rent_a_car_stanje_gtest_testSuiteTearDown(void);
void TestSuite_rent_a_car_stanje_gtest_testSuiteTearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteTearDown */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteTearDown */
}

/** Poziva se prije svakog testa. */
void TestSuite_rent_a_car_stanje_gtest_setUp(void);
void TestSuite_rent_a_car_stanje_gtest_setUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseSetUp */
    resetujStanje();
/* CPPTEST_TEST_SUITE_CODE_END TestCaseSetUp */
}

/** Poziva se poslije svakog testa. */
void TestSuite_rent_a_car_stanje_gtest_tearDown(void);
void TestSuite_rent_a_car_stanje_gtest_tearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseTearDown */
    resetujStanje();
/* CPPTEST_TEST_SUITE_CODE_END TestCaseTearDown */
}


/* CPPTEST_TEST_CASE_BEGIN SledeciIdAutomobila_PrazanNizVracaJedan */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_PrazanNizVracaJedan(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, sledeciIdAutomobila());
}
/* CPPTEST_TEST_CASE_END SledeciIdAutomobila_PrazanNizVracaJedan */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdAutomobila_JedanElementVracaDva */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_JedanElementVracaDva(void)
{
    dodajAuto(1);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, sledeciIdAutomobila());
}
/* CPPTEST_TEST_CASE_END SledeciIdAutomobila_JedanElementVracaDva */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdAutomobila_NajveciIdNijePosljednji */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_NajveciIdNijePosljednji(void)
{
    dodajAuto(1);
    dodajAuto(5);
    dodajAuto(3);
    CPPTEST_ASSERT_INTEGER_EQUAL(6, sledeciIdAutomobila());
}
/* CPPTEST_TEST_CASE_END SledeciIdAutomobila_NajveciIdNijePosljednji */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdAutomobila_RupaUIdovimaSeNePopunjava */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_RupaUIdovimaSeNePopunjava(void)
{
    dodajAuto(1);
    dodajAuto(3);
    CPPTEST_ASSERT_INTEGER_EQUAL(4, sledeciIdAutomobila());
}
/* CPPTEST_TEST_CASE_END SledeciIdAutomobila_RupaUIdovimaSeNePopunjava */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdAutomobila_IgnoriseElementeVanOpsega */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdAutomobila_IgnoriseElementeVanOpsega(void)
{
    dodajAuto(1);
    automobili[1].id = 99;
    CPPTEST_ASSERT_INTEGER_EQUAL(2, sledeciIdAutomobila());
}
/* CPPTEST_TEST_CASE_END SledeciIdAutomobila_IgnoriseElementeVanOpsega */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdIznajmljivanja_PrazanNizVracaJedan */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_PrazanNizVracaJedan(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, sledeciIdIznajmljivanja());
}
/* CPPTEST_TEST_CASE_END SledeciIdIznajmljivanja_PrazanNizVracaJedan */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdIznajmljivanja_JedanElementVracaDva */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_JedanElementVracaDva(void)
{
    dodajIznajmljivanje(1);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, sledeciIdIznajmljivanja());
}
/* CPPTEST_TEST_CASE_END SledeciIdIznajmljivanja_JedanElementVracaDva */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdIznajmljivanja_NajveciIdNijePosljednji */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_NajveciIdNijePosljednji(void)
{
    dodajIznajmljivanje(2);
    dodajIznajmljivanje(7);
    dodajIznajmljivanje(4);
    CPPTEST_ASSERT_INTEGER_EQUAL(8, sledeciIdIznajmljivanja());
}
/* CPPTEST_TEST_CASE_END SledeciIdIznajmljivanja_NajveciIdNijePosljednji */

/* CPPTEST_TEST_CASE_BEGIN SledeciIdIznajmljivanja_IgnoriseElementeVanOpsega */
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
void TestSuite_rent_a_car_stanje_gtest_SledeciIdIznajmljivanja_IgnoriseElementeVanOpsega(void)
{
    dodajIznajmljivanje(1);
    iznajmljivanja[1].id = 99;
    CPPTEST_ASSERT_INTEGER_EQUAL(2, sledeciIdIznajmljivanja());
}
/* CPPTEST_TEST_CASE_END SledeciIdIznajmljivanja_IgnoriseElementeVanOpsega */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_PrazanNizVracaMinusJedan */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PrazanNizVracaMinusJedan(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(-1, pronadjiAutomobilPoId(1));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_PrazanNizVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_PrvaPozicija */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PrvaPozicija(void)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, pronadjiAutomobilPoId(10));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_PrvaPozicija */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_SrednjaPozicija */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_SrednjaPozicija(void)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, pronadjiAutomobilPoId(20));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_SrednjaPozicija */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_PosljednjaPozicija */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_PosljednjaPozicija(void)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, pronadjiAutomobilPoId(30));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_PosljednjaPozicija */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_NepostojeciIdVracaMinusJedan */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_NepostojeciIdVracaMinusJedan(void)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(30);
    CPPTEST_ASSERT_INTEGER_EQUAL(-1, pronadjiAutomobilPoId(99));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_NepostojeciIdVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_IgnoriseElementeVanOpsega */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_IgnoriseElementeVanOpsega(void)
{
    dodajAuto(10);
    automobili[1].id = 20;
    CPPTEST_ASSERT_INTEGER_EQUAL(-1, pronadjiAutomobilPoId(20));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_IgnoriseElementeVanOpsega */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAutomobilPoId_DupliranIdVracaPrviIndeks */
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
void TestSuite_rent_a_car_stanje_gtest_PronadjiAutomobilPoId_DupliranIdVracaPrviIndeks(void)
{
    dodajAuto(10);
    dodajAuto(20);
    dodajAuto(20);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, pronadjiAutomobilPoId(20));
}
/* CPPTEST_TEST_CASE_END PronadjiAutomobilPoId_DupliranIdVracaPrviIndeks */
