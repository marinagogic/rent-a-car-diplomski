/**
 * \file rent_a_car_logic.h
 *
 * \brief Deklaracije poslovne logike rent-a-car sistema.
 *
 * Sve funkcije deklarisane ovdje su namjerno nezavisne od standardnog
 * ulaza/izlaza (scanf/printf), globalnog stanja i rada sa fajlovima (osim
 * parsiranja stringa vec ucitanog iz fajla), kako bi bile jednostavno
 * testabilne iz Google Test (C++) i Parasoft C/C++test okruzenja.
 */

#ifndef RENT_A_CAR_LOGIC_H
#define RENT_A_CAR_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

#define DUZINA_STRINGA   30   /**< Maksimalna duzina stringa za marku i model automobila. */
#define DUZINA_IMENA     50   /**< Maksimalna duzina stringa za ime i prezime klijenta. */
#define DUZINA_DATUMA    11   /**< Duzina stringa za datum u formatu DD-MM-GGGG (ukljucujuci '\0'). */

#define MIN_GODISTE   1950   /**< Najmanje dozvoljeno godiste automobila. */
#define MAX_GODISTE   2100   /**< Najvece dozvoljeno godiste automobila. */

#define MIN_BROJ_DANA    1    /**< Najmanji dozvoljen broj dana iznajmljivanja. */
#define MAX_BROJ_DANA  365    /**< Najveci dozvoljen broj dana iznajmljivanja. */

    /**
     * \brief Struktura koja opisuje jedan automobil u sistemu.
     */
    typedef struct
    {
        int   id;                          /**< Jedinstveni identifikator automobila. */
        char  marka[DUZINA_STRINGA];       /**< Marka automobila (npr. "Volkswagen"). */
        char  model[DUZINA_STRINGA];       /**< Model automobila (npr. "Golf"). */
        int   godiste;                     /**< Godiste automobila. */
        float cijena_po_danu;              /**< Cijena iznajmljivanja po danu, u KM. */
        int   dostupan;                    /**< 1 = automobil je dostupan za iznajmljivanje, 0 = trenutno je iznajmljen. */
    } Automobil;

    /**
     * \brief Struktura koja opisuje jedan zapis o iznajmljivanju automobila.
     */
    typedef struct
    {
        int   id;                          /**< Jedinstveni identifikator zapisa o iznajmljivanju. */
        int   id_automobila;               /**< ID automobila na koji se zapis odnosi. */
        char  ime[DUZINA_IMENA];           /**< Ime klijenta. */
        char  prezime[DUZINA_IMENA];       /**< Prezime klijenta. */
        char  datum_pocetka[DUZINA_DATUMA];/**< Datum pocetka iznajmljivanja (format DD-MM-GGGG). */
        char  datum_kraja[DUZINA_DATUMA];  /**< Datum kraja iznajmljivanja (format DD-MM-GGGG). */
        int   broj_dana;                   /**< Broj dana na koji je automobil iznajmljen. */
        float ukupna_cijena;               /**< Ukupna cijena iznajmljivanja, u KM. */
        int   aktivno;                     /**< 1 = automobil jos nije vracen, 0 = iznajmljivanje je zavrseno. */
    } Iznajmljivanje;

    /**
     * \brief Status kodovi koje vracaju funkcije poslovne logike.
     */
    typedef enum
    {
        RENT_OK = 0,                /**< Operacija uspjesno izvrsena. */
        RENT_NULL_POINTER,          /**< Prosledjen je NULL pokazivac tamo gdje se ocekivao validan. */
        RENT_INVALID_YEAR,          /**< Godiste automobila nije u dozvoljenom opsegu. */
        RENT_INVALID_PRICE,         /**< Cijena po danu nije veca od nule. */
        RENT_INVALID_DAYS,          /**< Broj dana iznajmljivanja nije u dozvoljenom opsegu. */
        RENT_INVALID_ID,            /**< Nevalidan ID (npr. van opsega niza). */
        RENT_CAR_NOT_FOUND,         /**< Automobil sa datim ID-om ne postoji. */
        RENT_CAR_NOT_AVAILABLE,     /**< Automobil je trenutno iznajmljen. */
        RENT_CAR_ALREADY_AVAILABLE, /**< Automobil vec nije iznajmljen (vracanje nije potrebno). */
        RENT_RENTAL_NOT_FOUND,      /**< Nije pronadjen aktivan zapis iznajmljivanja. */
        RENT_LIMIT_REACHED,         /**< Dostignut je maksimalan broj zapisa u nizu. */
        RENT_PARSE_ERROR,           /**< Greska pri parsiranju linije iz fajla. */
        RENT_FILE_ERROR             /**< Greska pri radu sa fajlom. */
    } RentStatus;

    /* Ciste (pure) funkcije - bez I/O i bez globalnog stanja */
    float       izracunajUkupnuCijenu(int brojDana, float cijenaPoDanu);
    int         jeAutomobilDostupan(const Automobil* automobil);
    int         jeBrojDanaValidan(int brojDana);
    int         jeGodisteValidno(int godiste);
    int         jeCijenaValidna(float cijena);
    const char* formatirajStatusAutomobila(int dostupan);
    const char* opisStatusa(RentStatus status);

    /* Poslovna logika nad automobilima */
    RentStatus validirajAutomobil(const Automobil* automobil);
    RentStatus kreirajAutomobil(Automobil* noviAutomobil, int id, const char* marka, const char* model,
        int godiste, float cijenaPoDanu);
    RentStatus validirajBrisanjeAutomobila(const Automobil* automobil);
    RentStatus obrisiAutomobilNaIndeksu(Automobil niz[], int* brojElemenata, int indeks);

    /* Poslovna logika nad iznajmljivanjima */
    int pronadjiAktivnoIznajmljivanjeZaAuto(const Iznajmljivanje niz[], int brojElemenata, int idAutomobila);
    RentStatus pripremiIznajmljivanje(Iznajmljivanje* iznajmljivanje, int id, int idAutomobila, float cijenaPoDanu,
        const char* ime, const char* prezime, const char* datumPocetka, const char* datumKraja, int brojDana);
    RentStatus obradiVracanjeAutomobila(Automobil* automobil, Iznajmljivanje* iznajmljivanje);

    /* Parsiranje linija iz fajlova (bez otvaranja/citanja fajlova) */
    RentStatus parsirajAutomobil(const char* linija, Automobil* automobil);
    RentStatus parsirajIznajmljivanje(const char* linija, Iznajmljivanje* iznajmljivanje);

#ifdef __cplusplus
}
#endif

#endif /* RENT_A_CAR_LOGIC_H */