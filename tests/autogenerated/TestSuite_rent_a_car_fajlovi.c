/**
 * \file TestSuite_rent_a_car_fajlovi.c
 *
 * \brief Parasoft C/C++test jedinicni testovi za ucitavanje i cuvanje podataka u fajlovima (rent_a_car_fajlovi.c).
 *
 * Vecina testova radi sa privremenim fajlovima, kao i u Google Testu.
 * Dva dodatna testa (TC_08 i TC_06) koriste stub za fopen sa Stub
 * Callback-om, pa simuliraju gresku pri otvaranju fajla bez ikakvih
 * izmjena na disku - to u Google Testu nije moguce bez dodatnih alata.
 * Poruke o greskama citaju se preko stuba za printf (stubs/stubs_stdio.c).
 *
 * Test slucajevi (ID-jevi u \tracehead) odgovaraju Google Test testovima
 * istog naziva, kako bi se rezultati dva alata mogli direktno porediti.
 */
#include "cpptest.h"

/* CPPTEST_TEST_SUITE_CODE_BEGIN AdditionalIncludes */
#include <stdio.h>
#include <string.h>
#include "rent_a_car_stanje.h"
#include "rent_a_car_fajlovi.h"
/* Kontrola korisnickih stubova iz stubs/stubs_stdio.c */
void stub_resetuj(void);
void stub_postaviUnos(const char* unos);
const char* stub_uhvaceniIspis(void);
const char* stub_preostaliUnos(void);
/* CPPTEST_TEST_SUITE_CODE_END AdditionalIncludes */

CPPTEST_CONTEXT("/RentACar/rent_a_car_fajlovi.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/RentACar/rent_a_car_fajlovi.c");

static const char* const TEST_AUTOMOBILI = "parasoft_tmp_automobili.txt";          /**< Privremeni fajl za automobile. */
static const char* const TEST_IZNAJMLJIVANJA = "parasoft_tmp_iznajmljivanja.txt";  /**< Privremeni fajl za iznajmljivanja. */
static const char* const NEVALIDNA_PUTANJA = "parasoft_nepostojeci_folder/fajl.txt"; /**< Putanja u folderu koji ne postoji. */

static int g_brojPozivaFopen = 0;  /**< Koliko puta je stub callback za fopen pozvan. */

/**
 * \brief Stub callback za fopen: simulira neuspjeh otvaranja fajla.
 *
 * Koristi se uz korisnicki stub za fopen iz stubs/stubs_stdio.c: u testovima
 * u kojima callback nije registrovan poziva se pravi fopen, a u testovima
 * koji ga registruju, fopen "ne uspije" (vraca NULL).
 *
 * Brojac g_brojPozivaFopen broji pozive za privremeni fajl testa
 * (TEST_AUTOMOBILI). Test provjerava samo da je callback pozvan, a ne tacan
 * broj poziva: u Parasoftu se, zbog nacina na koji Parasoft lancano poziva
 * stubove, callback za jedan poziv fopen moze izvrsiti vise puta.
 */
void CppTest_StubCallback_fopen_vratiNull(CppTest_StubCallInfo* stubCallInfo, FILE** __return,
    const char* filename, const char* mode)
{
    (void)stubCallInfo;
    (void)mode;
    if (filename != NULL && strcmp(filename, TEST_AUTOMOBILI) == 0)
    {
        g_brojPozivaFopen++;
    }
    *__return = NULL;
}

EXTERN_C_LINKAGE void TestSuite_rent_a_car_fajlovi_gtest_testSuiteBegin(void);
EXTERN_C_LINKAGE int TestSuite_rent_a_car_fajlovi_gtest_callTest(const char*);

CPPTEST_TEST_SUITE(TestSuite_rent_a_car_fajlovi_gtest);
        CPPTEST_TEST_SUITE_SETUP(TestSuite_rent_a_car_fajlovi_gtest_testSuiteSetUp);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NepostojeciFajlDajePraznuListu);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_PrazanFajl);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_ValidneLinijeSeUcitavaju);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NevalidneLinijeSePreskacu);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_PosljednjaLinijaBezNovogReda);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NeUcitavaViseOdMaksimuma);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NullPutanjaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NeValidiraVrijednosti);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_TacanSadrzajFajla);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_PrazanNizPraviPrazanFajl);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_PrepisujePostojeciSadrzaj);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_NevalidnaPutanjaVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_NullPutanjaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_CuvanjeIUcitavanjeDajuIstePodatke);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NepostojeciFajlDajePraznuListu);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_ValidneLinijeSeUcitavaju);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NevalidneLinijeSePreskacu);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NeUcitavaViseOdMaksimuma);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NullPutanjaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_TacanSadrzajFajla);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_PrazanNizPraviPrazanFajl);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_NevalidnaPutanjaVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_NullPutanjaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_CuvanjeIUcitavanjeDajuIstePodatke);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_FopenGreskaStub);
        CPPTEST_TEST(TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_FopenGreskaStub);
        CPPTEST_TEST_SUITE_TEARDOWN(TestSuite_rent_a_car_fajlovi_gtest_testSuiteTearDown);
CPPTEST_TEST_SUITE_END();

void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NepostojeciFajlDajePraznuListu(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_PrazanFajl(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_ValidneLinijeSeUcitavaju(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NevalidneLinijeSePreskacu(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_PosljednjaLinijaBezNovogReda(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NeUcitavaViseOdMaksimuma(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NullPutanjaVracaNullPointer(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NeValidiraVrijednosti(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_TacanSadrzajFajla(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_PrazanNizPraviPrazanFajl(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_PrepisujePostojeciSadrzaj(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_NevalidnaPutanjaVracaGresku(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_NullPutanjaVracaNullPointer(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_CuvanjeIUcitavanjeDajuIstePodatke(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NepostojeciFajlDajePraznuListu(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_ValidneLinijeSeUcitavaju(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NevalidneLinijeSePreskacu(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NeUcitavaViseOdMaksimuma(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NullPutanjaVracaNullPointer(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_TacanSadrzajFajla(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_PrazanNizPraviPrazanFajl(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_NevalidnaPutanjaVracaGresku(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_NullPutanjaVracaNullPointer(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_CuvanjeIUcitavanjeDajuIstePodatke(void);
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_FopenGreskaStub(void);
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_FopenGreskaStub(void);

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_rent_a_car_fajlovi_gtest);

/* ------------------------------------------------------------------ */
/* Pomocne funkcije                                                    */
/* ------------------------------------------------------------------ */

/** Broj i velicina bafera u koje se cuvaju kopije ispisa i sadrzaja fajlova. */
#define BROJ_KOPIJA 8
#define VELICINA_KOPIJE 65536

static char g_kopije[BROJ_KOPIJA][VELICINA_KOPIJE];  /**< Baferi za kopije teksta. */
static int g_sledecaKopija = 0;                       /**< Indeks sljedeceg slobodnog bafera. */

/**
 * Vraca slobodan bafer za kopiju teksta. Baferi se koriste u krug, pa jedan
 * test moze istovremeno cuvati do BROJ_KOPIJA razlicitih tekstova.
 */
static char* noviBafer(void)
{
    char* bafer = g_kopije[g_sledecaKopija];
    g_sledecaKopija = (g_sledecaKopija + 1) % BROJ_KOPIJA;
    bafer[0] = '\0';
    return bafer;
}

/** Vraca globalne nizove i brojace na pocetne vrijednosti. */
static void resetujStanje(void)
{
    memset(automobili, 0, sizeof(automobili));
    memset(iznajmljivanja, 0, sizeof(iznajmljivanja));
    brojAutomobila = 0;
    brojIznajmljivanja = 0;
}

/** Pravi fajl sa zadatim sadrzajem (postojeci sadrzaj se prepisuje). */
static void upisiFajl(const char* putanja, const char* sadrzaj)
{
    FILE* fp = fopen(putanja, "w");
    CPPTEST_ASSERT_MESSAGE("Nije moguce napraviti privremeni fajl", fp != NULL);
    fputs(sadrzaj, fp);
    fclose(fp);
}

/** Cita kompletan sadrzaj fajla (prazan tekst ako fajl ne postoji). */
static const char* procitajFajl(const char* putanja)
{
    char* sadrzaj = noviBafer();
    size_t duzina = 0;
    int c;
    FILE* fp = fopen(putanja, "r");
    if (fp == NULL)
    {
        return sadrzaj;
    }
    while ((c = fgetc(fp)) != EOF && duzina < VELICINA_KOPIJE - 1)
    {
        sadrzaj[duzina++] = (char)c;
    }
    sadrzaj[duzina] = '\0';
    fclose(fp);
    return sadrzaj;
}

/** Provjerava da li fajl postoji (1 - postoji, 0 - ne postoji). */
static int postojiFajl(const char* putanja)
{
    FILE* fp = fopen(putanja, "r");
    if (fp == NULL)
    {
        return 0;
    }
    fclose(fp);
    return 1;
}

/** Vraca 1 ako uhvaceni ispis sadrzi dati tekst, inace 0. */
static int sadrzi(const char* ispis, const char* tekst)
{
    return strstr(ispis, tekst) != NULL;
}

/** Dodaje automobil sa datim podacima na kraj globalnog niza. */
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

/** Dodaje zapis o iznajmljivanju sa datim podacima na kraj globalnog niza. */
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

/* ------------------------------------------------------------------ */
/* setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */

void TestSuite_rent_a_car_fajlovi_gtest_testSuiteSetUp(void);
void TestSuite_rent_a_car_fajlovi_gtest_testSuiteSetUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteSetUp */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteSetUp */
}

void TestSuite_rent_a_car_fajlovi_gtest_testSuiteTearDown(void);
void TestSuite_rent_a_car_fajlovi_gtest_testSuiteTearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteTearDown */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteTearDown */
}

/** Poziva se prije svakog testa. */
void TestSuite_rent_a_car_fajlovi_gtest_setUp(void);
void TestSuite_rent_a_car_fajlovi_gtest_setUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseSetUp */
    resetujStanje();
    stub_resetuj();
    remove(TEST_AUTOMOBILI);
    remove(TEST_IZNAJMLJIVANJA);
/* CPPTEST_TEST_SUITE_CODE_END TestCaseSetUp */
}

/** Poziva se poslije svakog testa. */
void TestSuite_rent_a_car_fajlovi_gtest_tearDown(void);
void TestSuite_rent_a_car_fajlovi_gtest_tearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseTearDown */
    resetujStanje();
    stub_resetuj();
    remove(TEST_AUTOMOBILI);
    remove(TEST_IZNAJMLJIVANJA);
/* CPPTEST_TEST_SUITE_CODE_END TestCaseTearDown */
}


/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_NepostojeciFajlDajePraznuListu */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NepostojeciFajlDajePraznuListu(void)
{
    brojAutomobila = 5;

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_FILE_ERROR, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_NepostojeciFajlDajePraznuListu */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_PrazanFajl */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_PrazanFajl(void)
{
    upisiFajl(TEST_AUTOMOBILI, "");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_PrazanFajl */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_ValidneLinijeSeUcitavaju */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_ValidneLinijeSeUcitavaju(void)
{
    upisiFajl(TEST_AUTOMOBILI,
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "2;Skoda;Octavia;2019;60.00;0\n");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojAutomobila);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Volkswagen", automobili[0].marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Golf", automobili[0].model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2020, automobili[0].godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(45.50f, automobili[0].cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);

    CPPTEST_ASSERT_INTEGER_EQUAL(2, automobili[1].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Skoda", automobili[1].marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Octavia", automobili[1].model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2019, automobili[1].godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(60.00f, automobili[1].cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[1].dostupan);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_ValidneLinijeSeUcitavaju */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_NevalidneLinijeSePreskacu */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NevalidneLinijeSePreskacu(void)
{
    upisiFajl(TEST_AUTOMOBILI,
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "ovo nije validna linija\n"
        "\n"
        "3;Audi;A4;abcd;80.00;1\n"
        "2;Skoda;Octavia;2019;60.00;0\n");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, automobili[1].id);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_NevalidneLinijeSePreskacu */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_PosljednjaLinijaBezNovogReda */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_PosljednjaLinijaBezNovogReda(void)
{
    upisiFajl(TEST_AUTOMOBILI,
        "1;Volkswagen;Golf;2020;45.50;1\n"
        "2;Skoda;Octavia;2019;60.00;0");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, automobili[1].id);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_PosljednjaLinijaBezNovogReda */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_NeUcitavaViseOdMaksimuma */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NeUcitavaViseOdMaksimuma(void)
{
    FILE* fp = fopen(TEST_AUTOMOBILI, "w");
    CPPTEST_ASSERT_MESSAGE("Nije moguce napraviti privremeni fajl", fp != NULL);
    for (int i = 1; i <= MAX_AUTOMOBILA + 1; i++)
    {
        fprintf(fp, "%d;Marka;Model;2020;50.00;1\n", i);
    }
    fclose(fp);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_AUTOMOBILA, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_AUTOMOBILA, automobili[MAX_AUTOMOBILA - 1].id);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_NeUcitavaViseOdMaksimuma */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_NullPutanjaVracaNullPointer */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NullPutanjaVracaNullPointer(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, ucitajAutomobile(NULL));
    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_NullPutanjaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_NeValidiraVrijednosti */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_NeValidiraVrijednosti(void)
{
    upisiFajl(TEST_AUTOMOBILI, "1;Volkswagen;Golf;1800;-5.00;1\n");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(1800, automobili[0].godiste);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_NeValidiraVrijednosti */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_TacanSadrzajFajla */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_TacanSadrzajFajla(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.5f, 1);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;Volkswagen;Golf;2020;45.50;1\n"
        "2;Skoda;Octavia;2019;60.00;0\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_TacanSadrzajFajla */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_PrazanNizPraviPrazanFajl */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_PrazanNizPraviPrazanFajl(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT(postojiFajl(TEST_AUTOMOBILI));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("", sadrzaj);
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_PrazanNizPraviPrazanFajl */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_PrepisujePostojeciSadrzaj */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_PrepisujePostojeciSadrzaj(void)
{
    upisiFajl(TEST_AUTOMOBILI, "stari sadrzaj koji treba nestati\n");
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;Fiat;Punto;2015;30.00;1\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_PrepisujePostojeciSadrzaj */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_NevalidnaPutanjaVracaGresku */
/**
 * \tracehead{SacuvajAutomobile_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u slucaju kada fajl ne moze biti otvoren za pisanje (negativan test - folder ne postoji).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 automobilom.
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = putanja u folderu koji ne postoji
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_FILE_ERROR.
 * 2. Ispisana je poruka "Greska pri radu sa fajlom." zajedno sa putanjom fajla.
 * \endfield
 */
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_NevalidnaPutanjaVracaGresku(void)
{
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);

    stub_resetuj();
    RentStatus status = sacuvajAutomobile(NEVALIDNA_PUTANJA);
    const char* ispis = stub_uhvaceniIspis();

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_FILE_ERROR, status);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Greska pri radu sa fajlom.", sadrzi(ispis, "Greska pri radu sa fajlom."));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi trazeni tekst", sadrzi(ispis, NEVALIDNA_PUTANJA));
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_NevalidnaPutanjaVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_NullPutanjaVracaNullPointer */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_NullPutanjaVracaNullPointer(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, sacuvajAutomobile(NULL));
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_NullPutanjaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_CuvanjeIUcitavanjeDajuIstePodatke */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_CuvanjeIUcitavanjeDajuIstePodatke(void)
{
    dodajAuto(4, "Volkswagen", "Golf", 2020, 45.5f, 1);
    dodajAuto(9, "Skoda", "Octavia", 2019, 60.0f, 0);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajAutomobile(TEST_AUTOMOBILI));
    resetujStanje();
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajAutomobile(TEST_AUTOMOBILI));

    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(4, automobili[0].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Volkswagen", automobili[0].marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Golf", automobili[0].model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2020, automobili[0].godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(45.5f, automobili[0].cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_INTEGER_EQUAL(9, automobili[1].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Skoda", automobili[1].marka);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[1].dostupan);
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_CuvanjeIUcitavanjeDajuIstePodatke */

/* CPPTEST_TEST_CASE_BEGIN UcitajIznajmljivanja_NepostojeciFajlDajePraznuListu */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NepostojeciFajlDajePraznuListu(void)
{
    brojIznajmljivanja = 5;

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_FILE_ERROR, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
}
/* CPPTEST_TEST_CASE_END UcitajIznajmljivanja_NepostojeciFajlDajePraznuListu */

/* CPPTEST_TEST_CASE_BEGIN UcitajIznajmljivanja_ValidneLinijeSeUcitavaju */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_ValidneLinijeSeUcitavaju(void)
{
    upisiFajl(TEST_IZNAJMLJIVANJA,
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
        "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0\n");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojIznajmljivanja);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, iznajmljivanja[0].id_automobila);
    CPPTEST_ASSERT_CSTR_EQUAL("Marina", iznajmljivanja[0].ime);
    CPPTEST_ASSERT_CSTR_EQUAL("Gogic", iznajmljivanja[0].prezime);
    CPPTEST_ASSERT_CSTR_EQUAL("27-07-2026", iznajmljivanja[0].datum_pocetka);
    CPPTEST_ASSERT_CSTR_EQUAL("28-07-2026", iznajmljivanja[0].datum_kraja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(90.00f, iznajmljivanja[0].ukupna_cijena, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].aktivno);

    CPPTEST_ASSERT_INTEGER_EQUAL(2, iznajmljivanja[1].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, iznajmljivanja[1].aktivno);
}
/* CPPTEST_TEST_CASE_END UcitajIznajmljivanja_ValidneLinijeSeUcitavaju */

/* CPPTEST_TEST_CASE_BEGIN UcitajIznajmljivanja_NevalidneLinijeSePreskacu */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NevalidneLinijeSePreskacu(void)
{
    upisiFajl(TEST_IZNAJMLJIVANJA,
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
        "1;3;Marina\n"
        "\n"
        "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0\n");

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, iznajmljivanja[1].id);
}
/* CPPTEST_TEST_CASE_END UcitajIznajmljivanja_NevalidneLinijeSePreskacu */

/* CPPTEST_TEST_CASE_BEGIN UcitajIznajmljivanja_NeUcitavaViseOdMaksimuma */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NeUcitavaViseOdMaksimuma(void)
{
    FILE* fp = fopen(TEST_IZNAJMLJIVANJA, "w");
    CPPTEST_ASSERT_MESSAGE("Nije moguce napraviti privremeni fajl", fp != NULL);
    for (int i = 1; i <= MAX_IZNAJMLJIVANJA + 1; i++)
    {
        fprintf(fp, "%d;1;Ime;Prezime;01-01-2026;02-01-2026;1;50.00;0\n", i);
    }
    fclose(fp);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_IZNAJMLJIVANJA, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_IZNAJMLJIVANJA, iznajmljivanja[MAX_IZNAJMLJIVANJA - 1].id);
}
/* CPPTEST_TEST_CASE_END UcitajIznajmljivanja_NeUcitavaViseOdMaksimuma */

/* CPPTEST_TEST_CASE_BEGIN UcitajIznajmljivanja_NullPutanjaVracaNullPointer */
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
void TestSuite_rent_a_car_fajlovi_gtest_UcitajIznajmljivanja_NullPutanjaVracaNullPointer(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, ucitajIznajmljivanja(NULL));
    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
}
/* CPPTEST_TEST_CASE_END UcitajIznajmljivanja_NullPutanjaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN SacuvajIznajmljivanja_TacanSadrzajFajla */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_TacanSadrzajFajla(void)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);
    dodajIznajmljivanje(2, 5, "Marko", "Markovic", "01-01-2026", "05-01-2026", 4, 200.0f, 0);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    const char* sadrzaj = procitajFajl(TEST_IZNAJMLJIVANJA);
    CPPTEST_ASSERT_CSTR_EQUAL("1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
        "2;5;Marko;Markovic;01-01-2026;05-01-2026;4;200.00;0\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END SacuvajIznajmljivanja_TacanSadrzajFajla */

/* CPPTEST_TEST_CASE_BEGIN SacuvajIznajmljivanja_PrazanNizPraviPrazanFajl */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_PrazanNizPraviPrazanFajl(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    CPPTEST_ASSERT(postojiFajl(TEST_IZNAJMLJIVANJA));
    const char* sadrzaj = procitajFajl(TEST_IZNAJMLJIVANJA);
    CPPTEST_ASSERT_CSTR_EQUAL("", sadrzaj);
}
/* CPPTEST_TEST_CASE_END SacuvajIznajmljivanja_PrazanNizPraviPrazanFajl */

/* CPPTEST_TEST_CASE_BEGIN SacuvajIznajmljivanja_NevalidnaPutanjaVracaGresku */
/**
 * \tracehead{SacuvajIznajmljivanja_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajIznajmljivanja" u slucaju kada fajl ne moze biti otvoren za pisanje (negativan test - folder ne postoji).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 zapisom.
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju sacuvajIznajmljivanja sa sljedecim argumentom:
 *  * putanja = putanja u folderu koji ne postoji
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajIznajmljivanja vraca RENT_FILE_ERROR.
 * 2. Ispisana je poruka "Greska pri radu sa fajlom." zajedno sa putanjom fajla.
 * \endfield
 */
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_NevalidnaPutanjaVracaGresku(void)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);

    stub_resetuj();
    RentStatus status = sacuvajIznajmljivanja(NEVALIDNA_PUTANJA);
    const char* ispis = stub_uhvaceniIspis();

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_FILE_ERROR, status);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Greska pri radu sa fajlom.", sadrzi(ispis, "Greska pri radu sa fajlom."));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi trazeni tekst", sadrzi(ispis, NEVALIDNA_PUTANJA));
}
/* CPPTEST_TEST_CASE_END SacuvajIznajmljivanja_NevalidnaPutanjaVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN SacuvajIznajmljivanja_NullPutanjaVracaNullPointer */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_NullPutanjaVracaNullPointer(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, sacuvajIznajmljivanja(NULL));
}
/* CPPTEST_TEST_CASE_END SacuvajIznajmljivanja_NullPutanjaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN SacuvajIznajmljivanja_CuvanjeIUcitavanjeDajuIstePodatke */
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
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajIznajmljivanja_CuvanjeIUcitavanjeDajuIstePodatke(void)
{
    dodajIznajmljivanje(7, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, sacuvajIznajmljivanja(TEST_IZNAJMLJIVANJA));
    resetujStanje();
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, ucitajIznajmljivanja(TEST_IZNAJMLJIVANJA));

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(7, iznajmljivanja[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, iznajmljivanja[0].id_automobila);
    CPPTEST_ASSERT_CSTR_EQUAL("Marina", iznajmljivanja[0].ime);
    CPPTEST_ASSERT_CSTR_EQUAL("Gogic", iznajmljivanja[0].prezime);
    CPPTEST_ASSERT_CSTR_EQUAL("27-07-2026", iznajmljivanja[0].datum_pocetka);
    CPPTEST_ASSERT_CSTR_EQUAL("28-07-2026", iznajmljivanja[0].datum_kraja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(90.0f, iznajmljivanja[0].ukupna_cijena, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].aktivno);
}
/* CPPTEST_TEST_CASE_END SacuvajIznajmljivanja_CuvanjeIUcitavanjeDajuIstePodatke */

/* CPPTEST_TEST_CASE_BEGIN UcitajAutomobile_FopenGreskaStub */
/**
 * \tracehead{UcitajAutomobile_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "ucitajAutomobile" u slucaju kada otvaranje fajla ne uspije, iako fajl postoji (negativan test - greska simulirana stubom za fopen).
 *
 * \field{Specifikacija testa}
 * 1. Napraviti privremeni fajl sa jednom validnom linijom.
 * 2. Registrovati stub callback za fopen koji uvijek vraca NULL.
 * 3. Pozvati funkciju ucitajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija ucitajAutomobile vraca RENT_FILE_ERROR.
 * 2. Vrijednost brojAutomobila je jednaka 0.
 * 3. Stub za fopen je pozvan za privremeni fajl (callback je aktivan).
 * \endfield
 *
 * Napomena: ovaj test nema ekvivalent u Google Test testovima - tamo se
 * neuspjeh fopen moze izazvati samo stvarnim stanjem fajl sistema.
 */
void TestSuite_rent_a_car_fajlovi_gtest_UcitajAutomobile_FopenGreskaStub(void)
{
    upisiFajl(TEST_AUTOMOBILI, "1;Volkswagen;Golf;2020;45.50;1\n");
    g_brojPozivaFopen = 0;

    CPPTEST_REGISTER_STUB_CALLBACK("fopen", &CppTest_StubCallback_fopen_vratiNull);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_FILE_ERROR, ucitajAutomobile(TEST_AUTOMOBILI));
    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Stub za fopen treba da bude pozvan za privremeni fajl", g_brojPozivaFopen >= 1);
}
/* CPPTEST_TEST_CASE_END UcitajAutomobile_FopenGreskaStub */

/* CPPTEST_TEST_CASE_BEGIN SacuvajAutomobile_FopenGreskaStub */
/**
 * \tracehead{SacuvajAutomobile_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "sacuvajAutomobile" u slucaju kada otvaranje fajla za pisanje ne uspije (negativan test - greska simulirana stubom za fopen, npr. pun disk ili zabrana pisanja).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 automobilom.
 * 2. Registrovati stub callback za fopen koji uvijek vraca NULL.
 * 3. Pozvati funkciju sacuvajAutomobile sa sljedecim argumentom:
 *  * putanja = privremeni fajl (validna putanja)
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija sacuvajAutomobile vraca RENT_FILE_ERROR.
 * 2. Ispisana je poruka "Greska pri radu sa fajlom.".
 * 3. Stub za fopen je pozvan za privremeni fajl (callback je aktivan).
 * \endfield
 *
 * Napomena: ovaj test nema ekvivalent u Google Test testovima.
 */
void TestSuite_rent_a_car_fajlovi_gtest_SacuvajAutomobile_FopenGreskaStub(void)
{
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);
    g_brojPozivaFopen = 0;

    CPPTEST_REGISTER_STUB_CALLBACK("fopen", &CppTest_StubCallback_fopen_vratiNull);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_FILE_ERROR, sacuvajAutomobile(TEST_AUTOMOBILI));
    const char* ispis = stub_uhvaceniIspis();
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Greska pri radu sa fajlom.", sadrzi(ispis, "Greska pri radu sa fajlom."));
    CPPTEST_ASSERT_MESSAGE("Stub za fopen treba da bude pozvan za privremeni fajl", g_brojPozivaFopen >= 1);
}
/* CPPTEST_TEST_CASE_END SacuvajAutomobile_FopenGreskaStub */
