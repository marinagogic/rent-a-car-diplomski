/**
 * \file TestSuite_rent_a_car_akcije.c
 *
 * \brief Parasoft C/C++test jedinicni testovi za akcije glavnog menija (rent_a_car_akcije.c).
 *
 * Funkcije istovremeno citaju unos (scanf, getchar), ispisuju poruke
 * (printf), mijenjaju globalno stanje i cuvaju podatke u fajlove.
 * U Google Testu je za to bilo potrebno preusmjeravanje stdin (freopen)
 * i hvatanje stdout (CaptureStdout). U Parasoftu scanf, getchar i printf
 * zamjenjuju korisnicki stubovi (stubs/stubs_stdio.c): test zadaje
 * unos sa stub_postaviUnos(), a ispis cita sa stub_uhvaceniIspis().
 * Fajlovi se, kao i u Google Testu, cuvaju u privremene fajlove.
 *
 * Test slucajevi (ID-jevi u \tracehead) odgovaraju Google Test testovima
 * istog naziva, kako bi se rezultati dva alata mogli direktno porediti.
 */
#include "cpptest.h"

/* CPPTEST_TEST_SUITE_CODE_BEGIN AdditionalIncludes */
#include <stdio.h>
#include <string.h>
#include "rent_a_car_stanje.h"
#include "rent_a_car_akcije.h"
/* Kontrola korisnickih stubova iz stubs/stubs_stdio.c */
void stub_resetuj(void);
void stub_postaviUnos(const char* unos);
const char* stub_uhvaceniIspis(void);
const char* stub_preostaliUnos(void);
/* CPPTEST_TEST_SUITE_CODE_END AdditionalIncludes */

CPPTEST_CONTEXT("/RentACar/rent_a_car_akcije.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/RentACar/rent_a_car_akcije.c");

static const char* const TEST_AUTOMOBILI = "parasoft_tmp_akcije_automobili.txt";          /**< Privremeni fajl za automobile. */
static const char* const TEST_IZNAJMLJIVANJA = "parasoft_tmp_akcije_iznajmljivanja.txt";  /**< Privremeni fajl za iznajmljivanja. */

/**
 * \brief Tabela podataka za test DodajAutomobil_NevalidanUnosNeDodaje.
 *
 * Prvi red je naziv kolone, a svaki sljedeci red je jedan simulirani unos
 * (test se izvrsava 4 puta).
 */
const char* DS_DODAJ_NEVALIDAN_UNOS[5][1] = {
    { "unos" },
    { "Volkswagen\nGolf\nabc\n" },          /* slova umjesto godista */
    { "Volkswagen\nGolf\n2020\nabc\n" },    /* slova umjesto cijene */
    { "" },                                   /* kraj ulaza prije marke */
    { "Volkswagen\n" },                       /* kraj ulaza prije modela */
};

/**
 * \brief Tabela podataka za test IznajmiAutomobil_NevalidanUnosOtkazuje (test se izvrsava 6 puta).
 */
const char* DS_IZNAJMI_NEVALIDAN_UNOS[7][1] = {
    { "unos" },
    { "abc\n" },                                              /* slova umjesto ID-a */
    { "1\n" },                                                /* kraj ulaza prije imena */
    { "1\nMarina\n" },                                        /* kraj ulaza prije prezimena */
    { "1\nMarina\nGogic\n" },                                 /* kraj ulaza prije datuma pocetka */
    { "1\nMarina\nGogic\n27-07-2026\n" },                     /* kraj ulaza prije datuma kraja */
    { "1\nMarina\nGogic\n27-07-2026\n30-07-2026\nabc\n" },   /* slova umjesto broja dana */
};

EXTERN_C_LINKAGE void TestSuite_rent_a_car_akcije_gtest_testSuiteBegin(void);
EXTERN_C_LINKAGE int TestSuite_rent_a_car_akcije_gtest_callTest(const char*);

CPPTEST_TEST_SUITE(TestSuite_rent_a_car_akcije_gtest);
        CPPTEST_TEST_SUITE_SETUP(TestSuite_rent_a_car_akcije_gtest_testSuiteSetUp);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_ValidanUnosDodajeAutomobil);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_DodjeljujeSledeciId);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_GranicneVrijednostiSuDozvoljene);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NevalidnoGodisteNeDodaje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NultaCijenaNeDodaje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_MaksimalanBrojAutomobila);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_PostojeciDostupanSeBrise);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_NepostojeciId);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_IznajmljenSeNeBrise);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_ValidanUnosIznajmljuje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_DodjeljujeSledeciId);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NepostojeciId);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_VecIznajmljenAutomobil);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NevalidanBrojDanaOtkazuje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_MaksimalanBrojZapisa);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_IznajmljenSeVraca);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_NepostojeciId);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_AutomobilNijeIznajmljen);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_BezAktivnogZapisaIspisujeUpozorenje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_ZavrsavaSamoAktivanZapis);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_OcistiUlazniBafer_OdbacujeOstatakReda);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_OcistiUlazniBafer_ZaustavljaSeNaKrajuUlaza);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_NenumerickiIdNeBrise);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_NenumerickiIdNeVraca);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_JednoSlobodnoMjestoDodaje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_PredugackiPodaciSeSkracujuUFajlu);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_PrekoracenBrojDanaOtkazuje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_JednoSlobodnoMjestoIznajmljuje);
        CPPTEST_TEST(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_PredugackiPodaciSeSkracujuUFajlu);
        CPPTEST_TEST_DS(TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NevalidanUnosNeDodaje, CPPTEST_DS_ARRAY(DS_DODAJ_NEVALIDAN_UNOS, 5, 1));
        CPPTEST_TEST_DS(TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NevalidanUnosOtkazuje, CPPTEST_DS_ARRAY(DS_IZNAJMI_NEVALIDAN_UNOS, 7, 1));
        CPPTEST_TEST_SUITE_TEARDOWN(TestSuite_rent_a_car_akcije_gtest_testSuiteTearDown);
CPPTEST_TEST_SUITE_END();

void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_ValidanUnosDodajeAutomobil(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_DodjeljujeSledeciId(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_GranicneVrijednostiSuDozvoljene(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NevalidnoGodisteNeDodaje(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NultaCijenaNeDodaje(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_MaksimalanBrojAutomobila(void);
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_PostojeciDostupanSeBrise(void);
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_NepostojeciId(void);
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_IznajmljenSeNeBrise(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_ValidanUnosIznajmljuje(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_DodjeljujeSledeciId(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NepostojeciId(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_VecIznajmljenAutomobil(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NevalidanBrojDanaOtkazuje(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_MaksimalanBrojZapisa(void);
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_IznajmljenSeVraca(void);
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_NepostojeciId(void);
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_AutomobilNijeIznajmljen(void);
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_BezAktivnogZapisaIspisujeUpozorenje(void);
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_ZavrsavaSamoAktivanZapis(void);
void TestSuite_rent_a_car_akcije_gtest_OcistiUlazniBafer_OdbacujeOstatakReda(void);
void TestSuite_rent_a_car_akcije_gtest_OcistiUlazniBafer_ZaustavljaSeNaKrajuUlaza(void);
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_NenumerickiIdNeBrise(void);
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_NenumerickiIdNeVraca(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_JednoSlobodnoMjestoDodaje(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_PredugackiPodaciSeSkracujuUFajlu(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_PrekoracenBrojDanaOtkazuje(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_JednoSlobodnoMjestoIznajmljuje(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_PredugackiPodaciSeSkracujuUFajlu(void);
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NevalidanUnosNeDodaje(void);
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NevalidanUnosOtkazuje(void);

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_rent_a_car_akcije_gtest);

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

/** Pravi kopiju teksta (npr. uhvacenog ispisa) koju kasniji ispis ne mijenja. */
static const char* sacuvajKopiju(const char* tekst)
{
    char* bafer = noviBafer();
    strncpy(bafer, tekst, VELICINA_KOPIJE - 1);
    bafer[VELICINA_KOPIJE - 1] = '\0';
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

/** Brise privremene fajlove koje testovi koriste. */
static void obrisiPrivremeneFajlove(void)
{
    remove(TEST_AUTOMOBILI);
    remove(TEST_IZNAJMLJIVANJA);
}

/**
 * Simulira unos korisnika preko stuba za scanf/getchar, izvrsava akciju
 * i vraca sve sto je ispisano preko stuba za printf.
 */
static const char* izvrsi(const char* unos, void (*akcija)(void))
{
    stub_resetuj();
    stub_postaviUnos(unos);
    akcija();
    return sacuvajKopiju(stub_uhvaceniIspis());
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

/** Dodaje zapis o iznajmljivanju (sa fiksnim podacima klijenta) na kraj globalnog niza. */
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

static void dodaj(void)    { dodajAutomobil(TEST_AUTOMOBILI); }

static void obrisi(void)   { obrisiAutomobil(TEST_AUTOMOBILI); }

static void iznajmi(void)  { iznajmiAutomobil(TEST_AUTOMOBILI, TEST_IZNAJMLJIVANJA); }

static void vrati(void)    { vratiAutomobil(TEST_AUTOMOBILI, TEST_IZNAJMLJIVANJA); }

/* ------------------------------------------------------------------ */
/* setUp / tearDown                                                    */
/* ------------------------------------------------------------------ */

void TestSuite_rent_a_car_akcije_gtest_testSuiteSetUp(void);
void TestSuite_rent_a_car_akcije_gtest_testSuiteSetUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteSetUp */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteSetUp */
}

void TestSuite_rent_a_car_akcije_gtest_testSuiteTearDown(void);
void TestSuite_rent_a_car_akcije_gtest_testSuiteTearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteTearDown */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteTearDown */
}

/** Poziva se prije svakog testa. */
void TestSuite_rent_a_car_akcije_gtest_setUp(void);
void TestSuite_rent_a_car_akcije_gtest_setUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseSetUp */
    resetujStanje();
    stub_resetuj();
    obrisiPrivremeneFajlove();
/* CPPTEST_TEST_SUITE_CODE_END TestCaseSetUp */
}

/** Poziva se poslije svakog testa. */
void TestSuite_rent_a_car_akcije_gtest_tearDown(void);
void TestSuite_rent_a_car_akcije_gtest_tearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseTearDown */
    obrisiPrivremeneFajlove();
    resetujStanje();
    stub_resetuj();
/* CPPTEST_TEST_SUITE_CODE_END TestCaseTearDown */
}


/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_ValidanUnosDodajeAutomobil */
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
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_ValidanUnosDodajeAutomobil(void)
{
    const char* ispis = izvrsi("Volkswagen\nGolf\n2020\n45.5\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Volkswagen", automobili[0].marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Golf", automobili[0].model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2020, automobili[0].godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(45.5f, automobili[0].cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno dodat! (ID: 1)", sadrzi(ispis, "Automobil je uspjesno dodat! (ID: 1)"));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;Volkswagen;Golf;2020;45.50;1\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_ValidanUnosDodajeAutomobil */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_DodjeljujeSledeciId */
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
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_DodjeljujeSledeciId(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajAuto(5, "Skoda", "Octavia", 2019, 60.0f, 1);

    const char* ispis = izvrsi("Audi\nA4\n2021\n80\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(3, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(6, automobili[2].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Audi", automobili[2].marka);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno dodat! (ID: 6)", sadrzi(ispis, "Automobil je uspjesno dodat! (ID: 6)"));
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_DodjeljujeSledeciId */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_GranicneVrijednostiSuDozvoljene */
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
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_GranicneVrijednostiSuDozvoljene(void)
{
    const char* ispis = izvrsi("Fiat\n500\n1950\n0.01\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno dodat!", sadrzi(ispis, "Automobil je uspjesno dodat!"));
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_GranicneVrijednostiSuDozvoljene */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_NevalidnoGodisteNeDodaje */
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
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NevalidnoGodisteNeDodaje(void)
{
    const char* ispis = izvrsi("Volkswagen\nGolf\n1800\n45\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Godiste nije u dozvoljenom opsegu (1950-2100). Automobil nije dodat.", sadrzi(ispis, "Godiste nije u dozvoljenom opsegu (1950-2100). Automobil nije dodat."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_NevalidnoGodisteNeDodaje */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_NultaCijenaNeDodaje */
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
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NultaCijenaNeDodaje(void)
{
    const char* ispis = izvrsi("Volkswagen\nGolf\n2020\n0\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Cijena po danu mora biti veca od nule. Automobil nije dodat.", sadrzi(ispis, "Cijena po danu mora biti veca od nule. Automobil nije dodat."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_NultaCijenaNeDodaje */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_MaksimalanBrojAutomobila */
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
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_MaksimalanBrojAutomobila(void)
{
    brojAutomobila = MAX_AUTOMOBILA;

    const char* ispis = izvrsi("Volkswagen\nGolf\n2020\n45\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_AUTOMOBILA, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Dostignut je maksimalan broj automobila (100).", sadrzi(ispis, "Dostignut je maksimalan broj automobila (100)."));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Marka:", !sadrzi(ispis, "Marka:"));
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_MaksimalanBrojAutomobila */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobil_PostojeciDostupanSeBrise */
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
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_PostojeciDostupanSeBrise(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 1);

    const char* ispis = izvrsi("1\n", obrisi);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, automobili[0].id);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno obrisan.", sadrzi(ispis, "Automobil je uspjesno obrisan."));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("2;Skoda;Octavia;2019;60.00;1\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobil_PostojeciDostupanSeBrise */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobil_NepostojeciId */
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
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_NepostojeciId(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi("99\n", obrisi);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil sa datim ID-om ne postoji. (ID 99)", sadrzi(ispis, "Automobil sa datim ID-om ne postoji. (ID 99)"));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobil_NepostojeciId */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobil_IznajmljenSeNeBrise */
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
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_IznajmljenSeNeBrise(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    const char* ispis = izvrsi("1\n", obrisi);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je trenutno iznajmljen.", sadrzi(ispis, "Automobil je trenutno iznajmljen."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobil_IznajmljenSeNeBrise */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_ValidanUnosIznajmljuje */
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_ValidanUnosIznajmljuje(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n30-07-2026\n3\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].id_automobila);
    CPPTEST_ASSERT_CSTR_EQUAL("Marina", iznajmljivanja[0].ime);
    CPPTEST_ASSERT_CSTR_EQUAL("Gogic", iznajmljivanja[0].prezime);
    CPPTEST_ASSERT_CSTR_EQUAL("27-07-2026", iznajmljivanja[0].datum_pocetka);
    CPPTEST_ASSERT_CSTR_EQUAL("30-07-2026", iznajmljivanja[0].datum_kraja);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, iznajmljivanja[0].broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(135.0f, iznajmljivanja[0].ukupna_cijena, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].aktivno);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[0].dostupan);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno iznajmljen!", sadrzi(ispis, "Automobil je uspjesno iznajmljen!"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Ukupna cijena: 135.00 KM", sadrzi(ispis, "Ukupna cijena: 135.00 KM"));

    const char* sadrzaj = procitajFajl(TEST_IZNAJMLJIVANJA);
    CPPTEST_ASSERT_CSTR_EQUAL("1;1;Marina;Gogic;27-07-2026;30-07-2026;3;135.00;1\n", sadrzaj);
    const char* sadrzaj2 = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;Volkswagen;Golf;2020;45.00;0\n", sadrzaj2);
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_ValidanUnosIznajmljuje */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_DodjeljujeSledeciId */
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_DodjeljujeSledeciId(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajIznajmljivanje(3, 1, 0);

    izvrsi("1\nMarina\nGogic\n27-07-2026\n28-07-2026\n1\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(4, iznajmljivanja[1].id);
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_DodjeljujeSledeciId */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_NepostojeciId */
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NepostojeciId(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi("99\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil sa datim ID-om ne postoji. (ID 99)", sadrzi(ispis, "Automobil sa datim ID-om ne postoji. (ID 99)"));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Ime klijenta:", !sadrzi(ispis, "Ime klijenta:"));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_NepostojeciId */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_VecIznajmljenAutomobil */
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_VecIznajmljenAutomobil(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    const char* ispis = izvrsi("1\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je trenutno iznajmljen.", sadrzi(ispis, "Automobil je trenutno iznajmljen."));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Ime klijenta:", !sadrzi(ispis, "Ime klijenta:"));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_VecIznajmljenAutomobil */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_NevalidanBrojDanaOtkazuje */
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NevalidanBrojDanaOtkazuje(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n27-07-2026\n0\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Broj dana mora biti u opsegu 1-365. Iznajmljivanje otkazano.", sadrzi(ispis, "Broj dana mora biti u opsegu 1-365. Iznajmljivanje otkazano."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_IZNAJMLJIVANJA)));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_NevalidanBrojDanaOtkazuje */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_MaksimalanBrojZapisa */
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_MaksimalanBrojZapisa(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    brojIznajmljivanja = MAX_IZNAJMLJIVANJA;

    const char* ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n28-07-2026\n1\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_IZNAJMLJIVANJA, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Dostignut je maksimalan dozvoljeni broj zapisa.", sadrzi(ispis, "Dostignut je maksimalan dozvoljeni broj zapisa."));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_MaksimalanBrojZapisa */

/* CPPTEST_TEST_CASE_BEGIN VratiAutomobil_IznajmljenSeVraca */
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
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_IznajmljenSeVraca(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);
    dodajIznajmljivanje(1, 1, 1);

    const char* ispis = izvrsi("1\n", vrati);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, iznajmljivanja[0].aktivno);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno vracen.", sadrzi(ispis, "Automobil je uspjesno vracen."));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: UPOZORENJE", !sadrzi(ispis, "UPOZORENJE"));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;Volkswagen;Golf;2020;45.00;1\n", sadrzaj);
    const char* sadrzaj2 = procitajFajl(TEST_IZNAJMLJIVANJA);
    CPPTEST_ASSERT_CSTR_EQUAL("1;1;Ana;Anic;01-01-2026;03-01-2026;2;100.00;0\n", sadrzaj2);
}
/* CPPTEST_TEST_CASE_END VratiAutomobil_IznajmljenSeVraca */

/* CPPTEST_TEST_CASE_BEGIN VratiAutomobil_NepostojeciId */
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
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_NepostojeciId(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    const char* ispis = izvrsi("99\n", vrati);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil sa datim ID-om ne postoji. (ID 99)", sadrzi(ispis, "Automobil sa datim ID-om ne postoji. (ID 99)"));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END VratiAutomobil_NepostojeciId */

/* CPPTEST_TEST_CASE_BEGIN VratiAutomobil_AutomobilNijeIznajmljen */
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
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_AutomobilNijeIznajmljen(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi("1\n", vrati);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Ovaj automobil trenutno nije iznajmljen.", sadrzi(ispis, "Ovaj automobil trenutno nije iznajmljen."));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: uspjesno vracen", !sadrzi(ispis, "uspjesno vracen"));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END VratiAutomobil_AutomobilNijeIznajmljen */

/* CPPTEST_TEST_CASE_BEGIN VratiAutomobil_BezAktivnogZapisaIspisujeUpozorenje */
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
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_BezAktivnogZapisaIspisujeUpozorenje(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);

    const char* ispis = izvrsi("1\n", vrati);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: UPOZORENJE: Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil.", sadrzi(ispis, "UPOZORENJE: Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil."));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno vracen.", sadrzi(ispis, "Automobil je uspjesno vracen."));
    const char* sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;Volkswagen;Golf;2020;45.00;1\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END VratiAutomobil_BezAktivnogZapisaIspisujeUpozorenje */

/* CPPTEST_TEST_CASE_BEGIN VratiAutomobil_ZavrsavaSamoAktivanZapis */
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
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_ZavrsavaSamoAktivanZapis(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);
    dodajIznajmljivanje(1, 1, 0);
    dodajIznajmljivanje(2, 2, 1);
    dodajIznajmljivanje(3, 1, 1);

    izvrsi("1\n", vrati);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, iznajmljivanja[2].aktivno);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, iznajmljivanja[0].aktivno);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[1].aktivno);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[1].dostupan);
}
/* CPPTEST_TEST_CASE_END VratiAutomobil_ZavrsavaSamoAktivanZapis */

/* CPPTEST_TEST_CASE_BEGIN OcistiUlazniBafer_OdbacujeOstatakReda */
/**
 * \tracehead{OcistiUlazniBafer_TC_00, Funkcionalni test}
 * Test provjerava da funkcija "ocistiUlazniBafer" odbacuje ostatak tekuceg reda unosa, ukljucujuci znak za novi red, a da sledeci red ostaje netaknut.
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika:
 *  * "visak teksta u redu" (prvi red)
 *  * "sledeci" (drugi red)
 * 2. Pozvati funkciju ocistiUlazniBafer.
 * 3. Procitati preostali (neprocitani) dio simuliranog unosa.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Preostali unos je tacno "sledeci\n" (citav prvi red, ukljucujuci znak za novi red, je odbacen).
 * \endfield
 */
void TestSuite_rent_a_car_akcije_gtest_OcistiUlazniBafer_OdbacujeOstatakReda(void)
{
    stub_resetuj();
    stub_postaviUnos("visak teksta u redu\nsledeci\n");

    ocistiUlazniBafer();

    CPPTEST_ASSERT_CSTR_EQUAL("sledeci\n", stub_preostaliUnos());
}
/* CPPTEST_TEST_CASE_END OcistiUlazniBafer_OdbacujeOstatakReda */

/* CPPTEST_TEST_CASE_BEGIN OcistiUlazniBafer_ZaustavljaSeNaKrajuUlaza */
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
 * 2. Preostali unos je prazan (sav unos je odbacen).
 * \endfield
 */
void TestSuite_rent_a_car_akcije_gtest_OcistiUlazniBafer_ZaustavljaSeNaKrajuUlaza(void)
{
    stub_resetuj();
    stub_postaviUnos("tekst bez novog reda");

    ocistiUlazniBafer();

    CPPTEST_ASSERT_CSTR_EQUAL("", stub_preostaliUnos());
}
/* CPPTEST_TEST_CASE_END OcistiUlazniBafer_ZaustavljaSeNaKrajuUlaza */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobil_NenumerickiIdNeBrise */
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
void TestSuite_rent_a_car_akcije_gtest_ObrisiAutomobil_NenumerickiIdNeBrise(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi("abc\n", obrisi);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Nevalidan unos. Automobil nije obrisan.", sadrzi(ispis, "Nevalidan unos. Automobil nije obrisan."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobil_NenumerickiIdNeBrise */

/* CPPTEST_TEST_CASE_BEGIN VratiAutomobil_NenumerickiIdNeVraca */
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
void TestSuite_rent_a_car_akcije_gtest_VratiAutomobil_NenumerickiIdNeVraca(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 0);
    dodajIznajmljivanje(1, 1, 1);

    const char* ispis = izvrsi("abc\n", vrati);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[0].dostupan);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[0].aktivno);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Nevalidan unos. Automobil nije vracen.", sadrzi(ispis, "Nevalidan unos. Automobil nije vracen."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END VratiAutomobil_NenumerickiIdNeVraca */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_NevalidanUnosNeDodaje */
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
 *
 * Napomena: Google Test ovaj slucaj pokriva parametrizovanim testom
 * (TEST_P), a Parasoft testom vodjenim podacima (CPPTEST_TEST_DS) -
 * test se izvrsava jednom za svaki red tabele podataka.
 */
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_NevalidanUnosNeDodaje(void)
{
    const char* unos = CPPTEST_DS_GET_CSTR("unos");

    const char* ispis = izvrsi(unos, dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojAutomobila);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Nevalidan unos. Automobil nije dodat.", sadrzi(ispis, "Nevalidan unos. Automobil nije dodat."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_NevalidanUnosNeDodaje */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_NevalidanUnosOtkazuje */
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
 *
 * Napomena: Google Test ovaj slucaj pokriva parametrizovanim testom
 * (TEST_P), a Parasoft testom vodjenim podacima (CPPTEST_TEST_DS) -
 * test se izvrsava jednom za svaki red tabele podataka.
 */
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_NevalidanUnosOtkazuje(void)
{
    const char* unos = CPPTEST_DS_GET_CSTR("unos");
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    const char* ispis = izvrsi(unos, iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Nevalidan unos. Iznajmljivanje otkazano.", sadrzi(ispis, "Nevalidan unos. Iznajmljivanje otkazano."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_IZNAJMLJIVANJA)));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_NevalidanUnosOtkazuje */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_JednoSlobodnoMjestoDodaje */
/**
 * \tracehead{DodajAutomobil_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "dodajAutomobil" u slucaju kada je u nizu ostalo tacno jedno slobodno mjesto (analiza granicnih vrijednosti - MAX_AUTOMOBILA - 1, posljednja validna vrijednost).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = MAX_AUTOMOBILA - 1 (99), automobili sa id = 1 .. 99
 * 2. Simulirati unos korisnika:
 *  * marka = "Volkswagen", model = "Golf", godiste = 2020, cijena = 45
 * 3. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojAutomobila je jednaka MAX_AUTOMOBILA (automobil je dodat na posljednje slobodno mjesto).
 * 2. Novi automobil ima id = 100.
 * 3. Ispisana je poruka "Automobil je uspjesno dodat! (ID: 100)".
 * 4. Posljednja linija fajla automobila je "100;Volkswagen;Golf;2020;45.00;1".
 * \endfield
 */
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_JednoSlobodnoMjestoDodaje(void)
{
    const char* ispis;
    const char* sadrzaj;
    const char* posljednjaLinija = "100;Volkswagen;Golf;2020;45.00;1\n";
    size_t duzinaSadrzaja;
    size_t duzinaLinije = strlen(posljednjaLinija);
    int i;

    for (i = 1; i < MAX_AUTOMOBILA; i++)
    {
        dodajAuto(i, "Fiat", "Punto", 2015, 30.0f, 1);
    }
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_AUTOMOBILA - 1, brojAutomobila);

    ispis = izvrsi("Volkswagen\nGolf\n2020\n45\n", dodaj);

    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_AUTOMOBILA, brojAutomobila);
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_AUTOMOBILA, automobili[MAX_AUTOMOBILA - 1].id);
    CPPTEST_ASSERT_CSTR_EQUAL("Volkswagen", automobili[MAX_AUTOMOBILA - 1].marka);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno dodat! (ID: 100)", sadrzi(ispis, "Automobil je uspjesno dodat! (ID: 100)"));

    sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    duzinaSadrzaja = strlen(sadrzaj);
    CPPTEST_ASSERT(duzinaSadrzaja >= duzinaLinije);
    CPPTEST_ASSERT_CSTR_EQUAL(posljednjaLinija, sadrzaj + duzinaSadrzaja - duzinaLinije);
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_JednoSlobodnoMjestoDodaje */

/* CPPTEST_TEST_CASE_BEGIN DodajAutomobil_PredugackiPodaciSeSkracujuUFajlu */
/**
 * \tracehead{DodajAutomobil_TC_08, Funkcionalni test}
 * Test provjerava da funkcija "dodajAutomobil" predugacku marku i model skracuje na najveci dozvoljeni broj znakova (DUZINA_STRINGA - 1 = 29), da ostali podaci ostaju ispravni i da se skraceni podaci ispravno upisuju u fajl (analiza granicnih vrijednosti - unos duzi od dozvoljenog).
 *
 * \field{Specifikacija testa}
 * 1. Simulirati unos korisnika:
 *  * marka = 35 znakova ("ABCDEFGHIJKLMNOPQRSTUVWXYZ" + "123456789")
 *  * model = 35 znakova ("abcdefghijklmnopqrstuvwxyz" + "123456789")
 *  * godiste = 2020, cijena = 45.5
 * 2. Pozvati funkciju dodajAutomobil i uhvatiti ispis.
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Automobil je dodat (brojAutomobila = 1).
 * 2. Marka i model sadrze samo prvih 29 znakova unosa.
 * 3. Godiste je 2020 i cijena 45.5 (visak marke i modela nije procitan kao vrijednost sljedeceg polja).
 * 4. Fajl automobila sadrzi liniju sa skracenom markom i modelom i ispravnim ostalim podacima.
 * \endfield
 */
void TestSuite_rent_a_car_akcije_gtest_DodajAutomobil_PredugackiPodaciSeSkracujuUFajlu(void)
{
    const char* ispis = izvrsi(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789\n"
        "abcdefghijklmnopqrstuvwxyz123456789\n"
        "2020\n"
        "45.5\n", dodaj);
    const char* sadrzaj;

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojAutomobila);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJKLMNOPQRSTUVWXYZ123", automobili[0].marka);
    CPPTEST_ASSERT_CSTR_EQUAL("abcdefghijklmnopqrstuvwxyz123", automobili[0].model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2020, automobili[0].godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(45.5f, automobili[0].cijena_po_danu, 0.001);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno dodat! (ID: 1)", sadrzi(ispis, "Automobil je uspjesno dodat! (ID: 1)"));
    sadrzaj = procitajFajl(TEST_AUTOMOBILI);
    CPPTEST_ASSERT_CSTR_EQUAL("1;ABCDEFGHIJKLMNOPQRSTUVWXYZ123;abcdefghijklmnopqrstuvwxyz123;2020;45.50;1\n", sadrzaj);
}
/* CPPTEST_TEST_CASE_END DodajAutomobil_PredugackiPodaciSeSkracujuUFajlu */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_PrekoracenBrojDanaOtkazuje */
/**
 * \tracehead{IznajmiAutomobil_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju kada je unesen broj dana veci od dozvoljenog (analiza granicnih vrijednosti - broj dana = 366, prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom (id = 1).
 * 2. Simulirati unos korisnika:
 *  * ID = 1, ime = "Marina", prezime = "Gogic", pocetak = "01-01-2026", kraj = "02-01-2027", broj dana = 366
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
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_PrekoracenBrojDanaOtkazuje(void)
{
    const char* ispis;

    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    ispis = izvrsi("1\nMarina\nGogic\n01-01-2026\n02-01-2027\n366\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Broj dana mora biti u opsegu 1-365. Iznajmljivanje otkazano.", sadrzi(ispis, "Broj dana mora biti u opsegu 1-365. Iznajmljivanje otkazano."));
    CPPTEST_ASSERT(!(postojiFajl(TEST_IZNAJMLJIVANJA)));
    CPPTEST_ASSERT(!(postojiFajl(TEST_AUTOMOBILI)));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_PrekoracenBrojDanaOtkazuje */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_JednoSlobodnoMjestoIznajmljuje */
/**
 * \tracehead{IznajmiAutomobil_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "iznajmiAutomobil" u slucaju kada je u nizu zapisa ostalo tacno jedno slobodno mjesto (analiza granicnih vrijednosti - MAX_IZNAJMLJIVANJA - 1, posljednja validna vrijednost).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * 1 dostupan automobil (id = 1)
 *  * brojIznajmljivanja = MAX_IZNAJMLJIVANJA - 1 (199), zavrseni zapisi sa id = 1 .. 199
 * 2. Simulirati unos korisnika:
 *  * ID = 1, ime = "Marina", prezime = "Gogic", pocetak = "27-07-2026", kraj = "28-07-2026", broj dana = 1
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Vrijednost brojIznajmljivanja je jednaka MAX_IZNAJMLJIVANJA (zapis je dodat na posljednje slobodno mjesto).
 * 2. Novi zapis ima id = 200 i aktivno = 1.
 * 3. Automobil je oznacen kao iznajmljen (dostupan = 0).
 * 4. Ispisana je poruka "Automobil je uspjesno iznajmljen!".
 * \endfield
 */
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_JednoSlobodnoMjestoIznajmljuje(void)
{
    const char* ispis;
    int i;

    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    for (i = 1; i < MAX_IZNAJMLJIVANJA; i++)
    {
        dodajIznajmljivanje(i, 1, 0);
    }
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_IZNAJMLJIVANJA - 1, brojIznajmljivanja);

    ispis = izvrsi("1\nMarina\nGogic\n27-07-2026\n28-07-2026\n1\n", iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_IZNAJMLJIVANJA, brojIznajmljivanja);
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_IZNAJMLJIVANJA, iznajmljivanja[MAX_IZNAJMLJIVANJA - 1].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, iznajmljivanja[MAX_IZNAJMLJIVANJA - 1].aktivno);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, automobili[0].dostupan);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Automobil je uspjesno iznajmljen!", sadrzi(ispis, "Automobil je uspjesno iznajmljen!"));
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_JednoSlobodnoMjestoIznajmljuje */

/* CPPTEST_TEST_CASE_BEGIN IznajmiAutomobil_PredugackiPodaciSeSkracujuUFajlu */
/**
 * \tracehead{IznajmiAutomobil_TC_09, Funkcionalni test}
 * Test provjerava da funkcija "iznajmiAutomobil" predugacko ime, prezime i datume skracuje na najveci dozvoljeni broj znakova (ime i prezime: DUZINA_IMENA - 1 = 49, datum: DUZINA_DATUMA - 1 = 10), da ostali podaci ostaju ispravni i da se skraceni podaci ispravno upisuju u fajl (analiza granicnih vrijednosti - unos duzi od dozvoljenog).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje sa 1 dostupnim automobilom (id = 1, cijena_po_danu = 45.0).
 * 2. Simulirati unos korisnika:
 *  * ID = 1
 *  * ime = 60 znakova (49 x "A" + "VISAKIMENAX")
 *  * prezime = 60 znakova (49 x "B" + "VISAKPREZXY")
 *  * pocetak = "27-07-2026XY", kraj = "30-07-2026XY" (po 12 znakova)
 *  * broj dana = 3
 * 3. Pozvati funkciju iznajmiAutomobil i uhvatiti ispis.
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Zapis je dodat (brojIznajmljivanja = 1).
 * 2. Ime i prezime sadrze samo prvih 49 znakova, a datumi samo prvih 10 znakova unosa.
 * 3. Broj dana je 3 i ukupna cijena 135.0 (visak nije procitan kao vrijednost sljedeceg polja).
 * 4. Fajl iznajmljivanja sadrzi liniju sa skracenim podacima i ispravnim brojem dana i cijenom.
 * \endfield
 */
void TestSuite_rent_a_car_akcije_gtest_IznajmiAutomobil_PredugackiPodaciSeSkracujuUFajlu(void)
{
    char ime49[50];
    char prezime49[50];
    char unos[256];
    char ocekivanaLinija[256];
    const char* ispis;
    const char* sadrzaj;

    memset(ime49, 'A', 49);
    ime49[49] = '\0';
    memset(prezime49, 'B', 49);
    prezime49[49] = '\0';
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);

    /* ime i prezime po 60 znakova, datumi po 12 znakova */
    sprintf(unos, "1\n%sVISAKIMENAX\n%sVISAKPREZXY\n27-07-2026XY\n30-07-2026XY\n3\n", ime49, prezime49);
    ispis = izvrsi(unos, iznajmi);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, brojIznajmljivanja);
    CPPTEST_ASSERT_CSTR_EQUAL(ime49, iznajmljivanja[0].ime);
    CPPTEST_ASSERT_CSTR_EQUAL(prezime49, iznajmljivanja[0].prezime);
    CPPTEST_ASSERT_CSTR_EQUAL("27-07-2026", iznajmljivanja[0].datum_pocetka);
    CPPTEST_ASSERT_CSTR_EQUAL("30-07-2026", iznajmljivanja[0].datum_kraja);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, iznajmljivanja[0].broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(135.0f, iznajmljivanja[0].ukupna_cijena, 0.001);
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Ukupna cijena: 135.00 KM", sadrzi(ispis, "Ukupna cijena: 135.00 KM"));

    sprintf(ocekivanaLinija, "1;1;%s;%s;27-07-2026;30-07-2026;3;135.00;1\n", ime49, prezime49);
    sadrzaj = procitajFajl(TEST_IZNAJMLJIVANJA);
    CPPTEST_ASSERT_CSTR_EQUAL(ocekivanaLinija, sadrzaj);
}
/* CPPTEST_TEST_CASE_END IznajmiAutomobil_PredugackiPodaciSeSkracujuUFajlu */
