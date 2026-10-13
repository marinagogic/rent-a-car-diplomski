/**
 * \file TestSuite_rent_a_car_prikaz.c
 *
 * \brief Parasoft C/C++test jedinicni testovi za funkcije ispisa (rent_a_car_prikaz.c).
 *
 * Funkcije ispisuju tekst pomocu printf. Umjesto preusmjeravanja
 * standardnog izlaza (CaptureStdout u Google Testu), Parasoft poziv
 * printf zamjenjuje korisnickim stubom (stubs/stubs_stdio.c) koji
 * ispis upisuje u memoriju, odakle ga test cita preko stub_uhvaceniIspis().
 *
 * Test slucajevi (ID-jevi u \tracehead) odgovaraju Google Test testovima
 * istog naziva, kako bi se rezultati dva alata mogli direktno porediti.
 */
#include "cpptest.h"

/* CPPTEST_TEST_SUITE_CODE_BEGIN AdditionalIncludes */
#include <string.h>
#include "rent_a_car_stanje.h"
#include "rent_a_car_prikaz.h"
/* Kontrola korisnickih stubova iz stubs/stubs_stdio.c */
void stub_resetuj(void);
void stub_postaviUnos(const char* unos);
const char* stub_uhvaceniIspis(void);
const char* stub_preostaliUnos(void);
/* CPPTEST_TEST_SUITE_CODE_END AdditionalIncludes */

CPPTEST_CONTEXT("/RentACar/rent_a_car_prikaz.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/RentACar/rent_a_car_prikaz.c");



EXTERN_C_LINKAGE void TestSuite_rent_a_car_prikaz_gtest_testSuiteBegin(void);
EXTERN_C_LINKAGE int TestSuite_rent_a_car_prikaz_gtest_callTest(const char*);

CPPTEST_TEST_SUITE(TestSuite_rent_a_car_prikaz_gtest);
        CPPTEST_TEST_SUITE_SETUP(TestSuite_rent_a_car_prikaz_gtest_testSuiteSetUp);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziMeni_SadrziNaslovISveOpcije);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziMeni_IspravnaStruktura);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_PrazanNizIspisujePoruku);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_JedanAutomobilTacanFormatReda);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_IznajmljenAutomobilIspisujeStatus);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_ViseAutomobilaIspisujeSveRedom);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_NeIspisujeElementeVanOpsega);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_CijenaSaDvijeDecimale);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_PrazanNizIspisujePoruku);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_AktivnoIznajmljivanjeTacanFormatReda);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_ZavrsenoIznajmljivanjeIspisujeStatus);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_ViseZapisaIspisujeSveRedom);
        CPPTEST_TEST(TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_NeIspisujeElementeVanOpsega);
        CPPTEST_TEST_SUITE_TEARDOWN(TestSuite_rent_a_car_prikaz_gtest_testSuiteTearDown);
CPPTEST_TEST_SUITE_END();

void TestSuite_rent_a_car_prikaz_gtest_PrikaziMeni_SadrziNaslovISveOpcije(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziMeni_IspravnaStruktura(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_PrazanNizIspisujePoruku(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_JedanAutomobilTacanFormatReda(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_IznajmljenAutomobilIspisujeStatus(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_ViseAutomobilaIspisujeSveRedom(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_NeIspisujeElementeVanOpsega(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_CijenaSaDvijeDecimale(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_PrazanNizIspisujePoruku(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_AktivnoIznajmljivanjeTacanFormatReda(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_ZavrsenoIznajmljivanjeIspisujeStatus(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_ViseZapisaIspisujeSveRedom(void);
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_NeIspisujeElementeVanOpsega(void);

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_rent_a_car_prikaz_gtest);

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

/** Izvrsava funkciju i vraca sve sto je ispisala preko stuba za printf. */
static const char* uhvatiIspis(void (*funkcija)(void))
{
    stub_resetuj();
    funkcija();
    return sacuvajKopiju(stub_uhvaceniIspis());
}

/**
 * Vraca poziciju prvog pojavljivanja teksta u ispisu, ili najveci moguci
 * broj ako tekst ne postoji (kao std::string::npos u Google Test testovima).
 */
static size_t pozicija(const char* ispis, const char* tekst)
{
    const char* p = strstr(ispis, tekst);
    return (p != NULL) ? (size_t)(p - ispis) : (size_t)-1;
}

/** Vraca 1 ako uhvaceni ispis sadrzi dati tekst, inace 0. */
static int sadrzi(const char* ispis, const char* tekst)
{
    return strstr(ispis, tekst) != NULL;
}

/** Broji koliko puta se tekst pojavljuje u ispisu. */
static int BrojPojavljivanja(const char* ispis, const char* tekst)
{
    int broj = 0;
    size_t duzina = strlen(tekst);
    const char* pozicija = strstr(ispis, tekst);
    while (pozicija != NULL)
    {
        broj++;
        pozicija = strstr(pozicija + duzina, tekst);
    }
    return broj;
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

void TestSuite_rent_a_car_prikaz_gtest_testSuiteSetUp(void);
void TestSuite_rent_a_car_prikaz_gtest_testSuiteSetUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteSetUp */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteSetUp */
}

void TestSuite_rent_a_car_prikaz_gtest_testSuiteTearDown(void);
void TestSuite_rent_a_car_prikaz_gtest_testSuiteTearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteTearDown */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteTearDown */
}

/** Poziva se prije svakog testa. */
void TestSuite_rent_a_car_prikaz_gtest_setUp(void);
void TestSuite_rent_a_car_prikaz_gtest_setUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseSetUp */
    resetujStanje();
    stub_resetuj();
/* CPPTEST_TEST_SUITE_CODE_END TestCaseSetUp */
}

/** Poziva se poslije svakog testa. */
void TestSuite_rent_a_car_prikaz_gtest_tearDown(void);
void TestSuite_rent_a_car_prikaz_gtest_tearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseTearDown */
    resetujStanje();
    stub_resetuj();
/* CPPTEST_TEST_SUITE_CODE_END TestCaseTearDown */
}


/* CPPTEST_TEST_CASE_BEGIN PrikaziMeni_SadrziNaslovISveOpcije */
/**
 * \tracehead{PrikaziMeni_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziMeni" u pogledu ispisa naslova i svih opcija menija.
 *
 * \field{Specifikacija testa}
 * 1. Resetovati stub za printf (prazan uhvaceni ispis).
 * 2. Pozvati funkciju prikaziMeni.
 * 3. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi naslov "RENT A CAR SISTEM".
 * 2. Ispis sadrzi svih 7 opcija menija (1-6 i 0 za izlaz), svaku sa tacnim tekstom.
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziMeni_SadrziNaslovISveOpcije(void)
{
    const char* ispis = uhvatiIspis(prikaziMeni);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: RENT A CAR SISTEM", sadrzi(ispis, "RENT A CAR SISTEM"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  1. Dodaj novi automobil\\n", sadrzi(ispis, " 1. Dodaj novi automobil\n"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  2. Prikazi sve automobile\\n", sadrzi(ispis, " 2. Prikazi sve automobile\n"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  3. Obrisi automobil\\n", sadrzi(ispis, " 3. Obrisi automobil\n"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  4. Iznajmi automobil\\n", sadrzi(ispis, " 4. Iznajmi automobil\n"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  5. Vrati automobil\\n", sadrzi(ispis, " 5. Vrati automobil\n"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  6. Prikazi sva iznajmljivanja\\n", sadrzi(ispis, " 6. Prikazi sva iznajmljivanja\n"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  0. Izlaz\\n", sadrzi(ispis, " 0. Izlaz\n"));
}
/* CPPTEST_TEST_CASE_END PrikaziMeni_SadrziNaslovISveOpcije */

/* CPPTEST_TEST_CASE_BEGIN PrikaziMeni_IspravnaStruktura */
/**
 * \tracehead{PrikaziMeni_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziMeni" u pogledu strukture ispisa (broj linija i okvir menija).
 *
 * \field{Specifikacija testa}
 * 1. Resetovati stub za printf (prazan uhvaceni ispis).
 * 2. Pozvati funkciju prikaziMeni.
 * 3. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis ima tacno 11 linija (3 linije zaglavlja, 7 opcija, 1 zavrsna linija).
 * 2. Linija okvira "======================================" pojavljuje se tacno 3 puta.
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziMeni_IspravnaStruktura(void)
{
    const char* ispis = uhvatiIspis(prikaziMeni);

    CPPTEST_ASSERT_INTEGER_EQUAL(11, BrojPojavljivanja(ispis, "\n"));
    CPPTEST_ASSERT_INTEGER_EQUAL(3, BrojPojavljivanja(ispis, "======================================\n"));
}
/* CPPTEST_TEST_CASE_END PrikaziMeni_IspravnaStruktura */

/* CPPTEST_TEST_CASE_BEGIN PrikaziAutomobile_PrazanNizIspisujePoruku */
/**
 * \tracehead{PrikaziAutomobile_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada nema unesenih automobila (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojAutomobila = 0
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi poruku "Trenutno nema unesenih automobila.".
 * 2. Ispis ne sadrzi zaglavlje tabele (kolonu "Marka").
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_PrazanNizIspisujePoruku(void)
{
    const char* ispis = uhvatiIspis(prikaziAutomobile);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Trenutno nema unesenih automobila.", sadrzi(ispis, "Trenutno nema unesenih automobila."));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Marka", !sadrzi(ispis, "Marka"));
}
/* CPPTEST_TEST_CASE_END PrikaziAutomobile_PrazanNizIspisujePoruku */

/* CPPTEST_TEST_CASE_BEGIN PrikaziAutomobile_JedanAutomobilTacanFormatReda */
/**
 * \tracehead{PrikaziAutomobile_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada postoji jedan dostupan automobil (provjera tacnog formata reda tabele).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 1, marka = "Volkswagen", model = "Golf", godiste = 2020, cijena_po_danu = 45.5, dostupan = 1}
 *  * brojAutomobila = 1
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
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
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_JedanAutomobilTacanFormatReda(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.5f, 1);

    const char* ispis = uhvatiIspis(prikaziAutomobile);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: ID   Marka           Model           Godiste  Cijena/dan   Status", sadrzi(ispis, "ID   Marka           Model           Godiste  Cijena/dan   Status"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: 1    Volkswagen      Golf            2020     45.50        Dostupan    \\n", sadrzi(ispis, "1    Volkswagen      Golf            2020     45.50        Dostupan    \n"));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Trenutno nema", !sadrzi(ispis, "Trenutno nema"));
}
/* CPPTEST_TEST_CASE_END PrikaziAutomobile_JedanAutomobilTacanFormatReda */

/* CPPTEST_TEST_CASE_BEGIN PrikaziAutomobile_IznajmljenAutomobilIspisujeStatus */
/**
 * \tracehead{PrikaziAutomobile_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada je automobil iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 2, marka = "Skoda", model = "Octavia", godiste = 2019, cijena_po_danu = 60.0, dostupan = 0}
 *  * brojAutomobila = 1
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi status "Iznajmljen".
 * 2. Ispis ne sadrzi status "Dostupan".
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_IznajmljenAutomobilIspisujeStatus(void)
{
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);

    const char* ispis = uhvatiIspis(prikaziAutomobile);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Iznajmljen", sadrzi(ispis, "Iznajmljen"));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Dostupan", !sadrzi(ispis, "Dostupan"));
}
/* CPPTEST_TEST_CASE_END PrikaziAutomobile_IznajmljenAutomobilIspisujeStatus */

/* CPPTEST_TEST_CASE_BEGIN PrikaziAutomobile_ViseAutomobilaIspisujeSveRedom */
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
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi sve tri marke.
 * 2. Status "Dostupan" se pojavljuje tacno 2 puta, a "Iznajmljen" tacno 1 put.
 * 3. Automobili su ispisani redoslijedom kojim su u nizu (Volkswagen prije Skoda, Skoda prije Audi).
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_ViseAutomobilaIspisujeSveRedom(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    dodajAuto(2, "Skoda", "Octavia", 2019, 60.0f, 0);
    dodajAuto(3, "Audi", "A4", 2021, 80.0f, 1);

    const char* ispis = uhvatiIspis(prikaziAutomobile);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Volkswagen", sadrzi(ispis, "Volkswagen"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Skoda", sadrzi(ispis, "Skoda"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Audi", sadrzi(ispis, "Audi"));
    CPPTEST_ASSERT_INTEGER_EQUAL(2, BrojPojavljivanja(ispis, "Dostupan"));
    CPPTEST_ASSERT_INTEGER_EQUAL(1, BrojPojavljivanja(ispis, "Iznajmljen"));
    CPPTEST_ASSERT((pozicija(ispis, "Volkswagen")) < (pozicija(ispis, "Skoda")));
    CPPTEST_ASSERT((pozicija(ispis, "Skoda")) < (pozicija(ispis, "Audi")));
}
/* CPPTEST_TEST_CASE_END PrikaziAutomobile_ViseAutomobilaIspisujeSveRedom */

/* CPPTEST_TEST_CASE_BEGIN PrikaziAutomobile_NeIspisujeElementeVanOpsega */
/**
 * \tracehead{PrikaziAutomobile_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u slucaju kada se iza posljednjeg validnog elementa nalazi zaostali (obrisani) automobil (analiza granicnih vrijednosti - element na indeksu brojAutomobila).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 1, marka = "Volkswagen", ...}
 *  * brojAutomobila = 1
 *  * automobili[1].marka = "Obrisani" (van opsega validnih elemenata)
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi "Volkswagen".
 * 2. Ispis ne sadrzi "Obrisani".
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_NeIspisujeElementeVanOpsega(void)
{
    dodajAuto(1, "Volkswagen", "Golf", 2020, 45.0f, 1);
    strcpy(automobili[1].marka, "Obrisani");

    const char* ispis = uhvatiIspis(prikaziAutomobile);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Volkswagen", sadrzi(ispis, "Volkswagen"));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Obrisani", !sadrzi(ispis, "Obrisani"));
}
/* CPPTEST_TEST_CASE_END PrikaziAutomobile_NeIspisujeElementeVanOpsega */

/* CPPTEST_TEST_CASE_BEGIN PrikaziAutomobile_CijenaSaDvijeDecimale */
/**
 * \tracehead{PrikaziAutomobile_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziAutomobile" u pogledu formatiranja cijene na dvije decimale.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * automobili[0] = {id = 1, marka = "Fiat", model = "Punto", godiste = 2015, cijena_po_danu = 30.0, dostupan = 1}
 *  * brojAutomobila = 1
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziAutomobile.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Cijena je ispisana kao "30.00" (tacno dvije decimale).
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziAutomobile_CijenaSaDvijeDecimale(void)
{
    dodajAuto(1, "Fiat", "Punto", 2015, 30.0f, 1);

    const char* ispis = uhvatiIspis(prikaziAutomobile);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi:  30.00 ", sadrzi(ispis, " 30.00 "));
}
/* CPPTEST_TEST_CASE_END PrikaziAutomobile_CijenaSaDvijeDecimale */

/* CPPTEST_TEST_CASE_BEGIN PrikaziIznajmljivanja_PrazanNizIspisujePoruku */
/**
 * \tracehead{PrikaziIznajmljivanja_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada nema evidentiranih iznajmljivanja (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * brojIznajmljivanja = 0
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi poruku "Trenutno nema evidentiranih iznajmljivanja.".
 * 2. Ispis ne sadrzi zaglavlje tabele (kolonu "AutoID").
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_PrazanNizIspisujePoruku(void)
{
    const char* ispis = uhvatiIspis(prikaziIznajmljivanja);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Trenutno nema evidentiranih iznajmljivanja.", sadrzi(ispis, "Trenutno nema evidentiranih iznajmljivanja."));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: AutoID", !sadrzi(ispis, "AutoID"));
}
/* CPPTEST_TEST_CASE_END PrikaziIznajmljivanja_PrazanNizIspisujePoruku */

/* CPPTEST_TEST_CASE_BEGIN PrikaziIznajmljivanja_AktivnoIznajmljivanjeTacanFormatReda */
/**
 * \tracehead{PrikaziIznajmljivanja_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada postoji jedno aktivno iznajmljivanje (provjera tacnog formata reda tabele).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0] = {id = 1, id_automobila = 3, ime = "Marina", prezime = "Gogic", datum_pocetka = "27-07-2026", datum_kraja = "28-07-2026", broj_dana = 1, ukupna_cijena = 90.0, aktivno = 1}
 *  * brojIznajmljivanja = 1
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi zaglavlje tabele sa svim kolonama.
 * 2. Ispis sadrzi red tabele tacno u formatu:
 *  * "1    3        Marina       Gogic        27-07-2026   28-07-2026   1      90.00      Aktivno   "
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_AktivnoIznajmljivanjeTacanFormatReda(void)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);

    const char* ispis = uhvatiIspis(prikaziIznajmljivanja);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: ID   AutoID   Ime          Prezime      Pocetak      Kraj         Dani   Cijena     Status", sadrzi(ispis, "ID   AutoID   Ime          Prezime      Pocetak      Kraj         Dani   Cijena     Status"));
    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: 1    3        Marina       Gogic        27-07-2026   28-07-2026   1      90.00      Aktivno   \\n", sadrzi(ispis, "1    3        Marina       Gogic        27-07-2026   28-07-2026   1      90.00      Aktivno   \n"));
}
/* CPPTEST_TEST_CASE_END PrikaziIznajmljivanja_AktivnoIznajmljivanjeTacanFormatReda */

/* CPPTEST_TEST_CASE_BEGIN PrikaziIznajmljivanja_ZavrsenoIznajmljivanjeIspisujeStatus */
/**
 * \tracehead{PrikaziIznajmljivanja_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada je iznajmljivanje zavrseno.
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0] = {id = 1, id_automobila = 3, ime = "Marko", ..., aktivno = 0}
 *  * brojIznajmljivanja = 1
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi status "Zavrseno".
 * 2. Ispis ne sadrzi status "Aktivno".
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_ZavrsenoIznajmljivanjeIspisujeStatus(void)
{
    dodajIznajmljivanje(1, 3, "Marko", "Markovic", "01-01-2026", "05-01-2026", 4, 200.0f, 0);

    const char* ispis = uhvatiIspis(prikaziIznajmljivanja);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Zavrseno", sadrzi(ispis, "Zavrseno"));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Aktivno", !sadrzi(ispis, "Aktivno"));
}
/* CPPTEST_TEST_CASE_END PrikaziIznajmljivanja_ZavrsenoIznajmljivanjeIspisujeStatus */

/* CPPTEST_TEST_CASE_BEGIN PrikaziIznajmljivanja_ViseZapisaIspisujeSveRedom */
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
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Status "Zavrseno" se pojavljuje tacno 2 puta, a "Aktivno" tacno 1 put.
 * 2. Zapisi su ispisani redoslijedom kojim su u nizu (Ana, Petar, Jovana).
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_ViseZapisaIspisujeSveRedom(void)
{
    dodajIznajmljivanje(1, 1, "Ana", "Anic", "01-01-2026", "03-01-2026", 2, 100.0f, 0);
    dodajIznajmljivanje(2, 2, "Petar", "Petrovic", "05-01-2026", "08-01-2026", 3, 180.0f, 1);
    dodajIznajmljivanje(3, 1, "Jovana", "Jovic", "10-01-2026", "11-01-2026", 1, 50.0f, 0);

    const char* ispis = uhvatiIspis(prikaziIznajmljivanja);

    CPPTEST_ASSERT_INTEGER_EQUAL(2, BrojPojavljivanja(ispis, "Zavrseno"));
    CPPTEST_ASSERT_INTEGER_EQUAL(1, BrojPojavljivanja(ispis, "Aktivno"));
    CPPTEST_ASSERT((pozicija(ispis, "Ana")) < (pozicija(ispis, "Petar")));
    CPPTEST_ASSERT((pozicija(ispis, "Petar")) < (pozicija(ispis, "Jovana")));
}
/* CPPTEST_TEST_CASE_END PrikaziIznajmljivanja_ViseZapisaIspisujeSveRedom */

/* CPPTEST_TEST_CASE_BEGIN PrikaziIznajmljivanja_NeIspisujeElementeVanOpsega */
/**
 * \tracehead{PrikaziIznajmljivanja_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "prikaziIznajmljivanja" u slucaju kada se iza posljednjeg validnog elementa nalazi zaostali zapis (analiza granicnih vrijednosti - element na indeksu brojIznajmljivanja).
 *
 * \field{Specifikacija testa}
 * 1. Postaviti globalno stanje:
 *  * iznajmljivanja[0] = {id = 1, ime = "Marina", ...}
 *  * brojIznajmljivanja = 1
 *  * iznajmljivanja[1].ime = "Zaostali" (van opsega validnih elemenata)
 * 2. Resetovati stub za printf (prazan uhvaceni ispis).
 * 3. Pozvati funkciju prikaziIznajmljivanja.
 * 4. Procitati ispis uhvacen stubom za printf i provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Ispis sadrzi "Marina".
 * 2. Ispis ne sadrzi "Zaostali".
 * \endfield
 */
void TestSuite_rent_a_car_prikaz_gtest_PrikaziIznajmljivanja_NeIspisujeElementeVanOpsega(void)
{
    dodajIznajmljivanje(1, 3, "Marina", "Gogic", "27-07-2026", "28-07-2026", 1, 90.0f, 1);
    strcpy(iznajmljivanja[1].ime, "Zaostali");

    const char* ispis = uhvatiIspis(prikaziIznajmljivanja);

    CPPTEST_ASSERT_MESSAGE("Ispis treba da sadrzi: Marina", sadrzi(ispis, "Marina"));
    CPPTEST_ASSERT_MESSAGE("Ispis ne smije sadrzati: Zaostali", !sadrzi(ispis, "Zaostali"));
}
/* CPPTEST_TEST_CASE_END PrikaziIznajmljivanja_NeIspisujeElementeVanOpsega */
