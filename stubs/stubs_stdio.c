#include "cpptest.h"

/**
 * \file stubs_stdio.c
 *
 * \brief Korisnicki stubovi (user stubs) za funkcije standardne biblioteke
 *        printf, scanf, getchar, fopen i fprintf.
 *
 */

/* Zaglavlja u kojima su originalne funkcije deklarisane, i pomocna zaglavlja. */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define VELICINA_ISPISA 65536   /**< Najveci broj znakova uhvacenog ispisa. */
#define VELICINA_UNOSA  4096    /**< Najveci broj znakova simuliranog unosa. */

/* ------------------------------------------------------------------ */
/* Stanje stubova                                                     */
/* ------------------------------------------------------------------ */

static char   g_ispis[VELICINA_ISPISA];  /**< Sav tekst koji je testirani kod ispisao. */
static size_t g_duzinaIspisa = 0;        /**< Trenutna duzina uhvacenog ispisa. */
static char   g_unos[VELICINA_UNOSA];    /**< Simulirani unos korisnika. */
static size_t g_duzinaUnosa = 0;         /**< Duzina simuliranog unosa. */
static size_t g_pozicija = 0;            /**< Pozicija sljedeceg neprocitanog znaka u g_unos. */

/* ------------------------------------------------------------------ */
/* Funkcije kojima testovi upravljaju stubovima                        */
/* ------------------------------------------------------------------ */

/**
 * \brief Brise uhvaceni ispis i simulirani unos.
 *
 * Poziva se u setUp() i tearDown() funkcijama test suite-ova, kako bi svaki
 * test poceo sa praznim ispisom i bez preostalog unosa iz prethodnog testa.
 */
EXTERN_C_LINKAGE void stub_resetuj(void)
{
    g_ispis[0] = '\0';
    g_duzinaIspisa = 0;
    g_unos[0] = '\0';
    g_duzinaUnosa = 0;
    g_pozicija = 0;
}

/**
 * \brief Zadaje tekst koji ce "korisnik otkucati".
 *
 * Svaka vrijednost se navodi u posebnom redu, npr. "Volkswagen\nGolf\n2020\n45.5\n".
 * Ovaj tekst zatim citaju stubovi za scanf i getchar.
 *
 * \param unos Simulirani unos korisnika (NULL se tretira kao prazan unos).
 */
EXTERN_C_LINKAGE void stub_postaviUnos(const char* unos)
{
    if (unos == NULL)
    {
        unos = "";
    }
    strncpy(g_unos, unos, VELICINA_UNOSA - 1);
    g_unos[VELICINA_UNOSA - 1] = '\0';
    g_duzinaUnosa = strlen(g_unos);
    g_pozicija = 0;
}

/**
 * \brief Vraca sav tekst koji je testirani kod ispisao od posljednjeg resetovanja.
 *
 * \return Pokazivac na uhvaceni ispis.
 */
EXTERN_C_LINKAGE const char* stub_uhvaceniIspis(void)
{
    return g_ispis;
}

/**
 * \brief Vraca dio simuliranog unosa koji testirani kod jos nije procitao.
 *
 * \return Pokazivac na neprocitani dio unosa.
 */
EXTERN_C_LINKAGE const char* stub_preostaliUnos(void)
{
    return g_unos + g_pozicija;
}

/* ------------------------------------------------------------------ */
/* printf                                                              */
/* ------------------------------------------------------------------ */

/**
 * \brief Stub za printf: umjesto ispisa na ekran, tekst se dodaje u g_ispis.
 *
 * Tekst se formatira na isti nacin kao kod pravog printf (vsnprintf), pa
 * test moze provjeriti tacan izgled ispisa.
 *
 * \param format Format string, kao kod printf.
 * \return Broj formatiranih znakova, kao kod printf.
 */
/** User stub definition for function: int printf(const char *__restrict__, ...) */
EXTERN_C_LINKAGE int printf (const char * _MT_var50, ...) ;
EXTERN_C_LINKAGE int CppTest_Stub_printf (const char * format, ...)
{
    char bafer[1024];
    va_list argumenti;
    int duzina;

    CPPTEST_STUB_CALLED("printf");

    va_start(argumenti, format);
    duzina = vsnprintf(bafer, sizeof(bafer), format, argumenti);
    va_end(argumenti);

    if (duzina > 0)
    {
        size_t n = strlen(bafer);
        if (g_duzinaIspisa + n >= VELICINA_ISPISA)
        {
            n = VELICINA_ISPISA - 1 - g_duzinaIspisa;
        }
        memcpy(g_ispis + g_duzinaIspisa, bafer, n);
        g_duzinaIspisa += n;
        g_ispis[g_duzinaIspisa] = '\0';
    }
    return duzina;
}

/* ------------------------------------------------------------------ */
/* scanf                                                               */
/* ------------------------------------------------------------------ */

/**
 * \brief Stub za scanf: cita jednu vrijednost iz simuliranog unosa.
 *
 * Podrzava formate koje koristi aplikacija ("%d", "%f", "%29s", "%49s",
 * "%10s") i ponasa se kao pravi scanf:
 *  1. preskace bjeline (razmake i znakove za novi red);
 *  2. pokusava da procita jednu vrijednost i pomjera poziciju samo za
 *     procitane znakove (npr. kod "%d" i unosa "12abc" procita se samo "12");
 *  3. ako vrijednost nije validna (npr. slova umjesto broja), nista se ne
 *     trosi iz unosa i vraca se 0;
 *  4. kada vise nema unosa, vraca se EOF.
 *
 * \param format Format string, kao kod scanf.
 * \return 1 ako je vrijednost procitana, 0 ako unos nije validan, EOF na kraju unosa.
 */
/** User stub definition for function: int scanf(const char *__restrict__, ...) */
EXTERN_C_LINKAGE int scanf (const char * _MT_var51, ...) ;
EXTERN_C_LINKAGE int CppTest_Stub_scanf (const char * format, ...)
{
    char rijec[VELICINA_UNOSA];
    size_t kraj;
    size_t duzinaRijeci;
    size_t potroseno;
    int procitano;
    int sirina = 0;
    const char* p;
    char* krajBroja = NULL;
    va_list argumenti;

    CPPTEST_STUB_CALLED("scanf");

    /* Preskakanje bjelina (pravi scanf ih preskace prije %d, %f i %s). */
    while (g_pozicija < g_duzinaUnosa && isspace((unsigned char)g_unos[g_pozicija]))
    {
        g_pozicija++;
    }
    if (g_pozicija >= g_duzinaUnosa)
    {
        return EOF;
    }

    /* Izdvajanje rijeci do sljedece bjeline. */
    kraj = g_pozicija;
    while (kraj < g_duzinaUnosa && !isspace((unsigned char)g_unos[kraj]))
    {
        kraj++;
    }
    duzinaRijeci = kraj - g_pozicija;
    memcpy(rijec, g_unos + g_pozicija, duzinaRijeci);
    rijec[duzinaRijeci] = '\0';

    va_start(argumenti, format);
    procitano = vsscanf(rijec, format, argumenti);
    va_end(argumenti);

    if (procitano != 1)
    {
        return 0;   /* nevalidan unos ostaje u ulazu, kao kod pravog scanf */
    }

    /* Odredjivanje koliko je znakova potroseno, u zavisnosti od konverzije u formatu. */
    p = strchr(format, '%') + 1;
    while (isdigit((unsigned char)*p))
    {
        sirina = sirina * 10 + (*p - '0');
        p++;
    }

    potroseno = duzinaRijeci;
    if (*p == 'd')
    {
        (void)strtol(rijec, &krajBroja, 10);
        potroseno = (size_t)(krajBroja - rijec);
    }
    else if (*p == 'f')
    {
        (void)strtod(rijec, &krajBroja);
        potroseno = (size_t)(krajBroja - rijec);
    }
    else if (*p == 's' && sirina > 0 && (size_t)sirina < potroseno)
    {
        potroseno = (size_t)sirina;
    }

    g_pozicija += potroseno;
    return procitano;
}

/* ------------------------------------------------------------------ */
/* getchar                                                             */
/* ------------------------------------------------------------------ */

/**
 * \brief Stub za getchar: vraca sljedeci znak simuliranog unosa.
 *
 * Koristi ga funkcija ocistiUlazniBafer(), koja odbacuje ostatak reda.
 *
 * \return Sljedeci znak unosa, ili EOF kada vise nema unosa.
 */
/** User stub definition for function: int getchar(void) */
EXTERN_C_LINKAGE int getchar (void) ;
EXTERN_C_LINKAGE int CppTest_Stub_getchar (void)
{
    CPPTEST_STUB_CALLED("getchar");

    if (g_pozicija >= g_duzinaUnosa)
    {
        return EOF;
    }
    return (unsigned char)g_unos[g_pozicija++];
}

/* ------------------------------------------------------------------ */
/* fopen                                                               */
/* ------------------------------------------------------------------ */

/**
 * \brief Stub za fopen: poziva originalni fopen, osim ako test registruje callback.
 *
 * Ako test nije registrovao stub callback, poziva se originalna funkcija i
 * fajl se stvarno otvara. Ako jeste (CPPTEST_REGISTER_STUB_CALLBACK("fopen", ...)),
 * rezultat odredjuje callback funkcija iz testa - tako testovi
 * UcitajAutomobile_FopenGreskaStub i SacuvajAutomobile_FopenGreskaStub
 * simuliraju da otvaranje fajla ne uspije.
 *
 * \param putanja Putanja do fajla.
 * \param mod     Nacin otvaranja ("r", "w", ...).
 * \return Pokazivac na otvoreni fajl, ili NULL ako otvaranje nije uspjelo.
 */
/** User stub definition for function: FILE * fopen(const char *__restrict__, const char *__restrict__) */
EXTERN_C_LINKAGE FILE * fopen (const char * _MT_var52, const char * _MT_var53) ;
EXTERN_C_LINKAGE FILE * CppTest_Stub_fopen (const char * putanja, const char * mod)
{
    CPPTEST_STUB_CALLED("fopen");

    FILE * __return = NULL;

    /**
     * This section enables Dynamic Stub Configuration with Stub Callbacks.
     *
     * 1. Define stub callback function in test suite file - use the following signature:
     *     void CppTest_StubCallback_SomeName(CppTest_StubCallInfo* stubCallInfo, FILE ** __return, const char * putanja, const char * mod)
     *
     * 2. Register stub callback in test case function - use the following code:
     *     CPPTEST_REGISTER_STUB_CALLBACK("fopen", &CppTest_StubCallback_SomeName);
     */
    if (CPPTEST_STUB_HAS_CALLBACK()) {
        CPPTEST_STUB_CALLBACK_PARAMS(FILE ** __return, const char * putanja, const char * mod);
        CPPTEST_STUB_INVOKE_CALLBACK(&__return, putanja, mod);

    } else {
        /* Callback nije registrovan: poziva se originalna funkcija. */
        __return = fopen(putanja, mod);
    }

    return __return;
}

/* ------------------------------------------------------------------ */
/* fprintf                                                             */
/* ------------------------------------------------------------------ */

/**
 * \brief Stub za fprintf: poziva originalnu funkciju (preko vfprintf).
 *
 * Postoji samo zato da bi se umjesto Parasoftovog "safe" stuba, koji ne
 * pise u fajl, koristila prava funkcija i podaci stvarno upisali u fajl.
 *
 * \param fajl   Fajl u koji se pise.
 * \param format Format string, kao kod fprintf.
 * \return Broj upisanih znakova, kao kod fprintf.
 */
/** User stub definition for function: int fprintf(FILE *__restrict__, const char *__restrict__, ...) */
EXTERN_C_LINKAGE int fprintf (FILE * _MT_var54, const char * _MT_var55, ...) ;
EXTERN_C_LINKAGE int CppTest_Stub_fprintf (FILE * fajl, const char * format, ...)
{
    va_list argumenti;
    int __return;

    CPPTEST_STUB_CALLED("fprintf");

    va_start(argumenti, format);
    __return = vfprintf(fajl, format, argumenti);
    va_end(argumenti);

    return __return;
}
