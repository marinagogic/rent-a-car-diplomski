/**
 * \file rent_a_car_stanje.h
 *
 * \brief Globalno stanje rent-a-car sistema i pomocne funkcije nad njim.
 *
 * Ovaj modul je izdvojen iz main.c kako bi pomocne funkcije koje zavise
 * samo od globalnih nizova (bez scanf/printf i rada sa fajlovima) mogle
 * biti testirane nezavisno od korisnickog interfejsa, kao i da bi main.c
 * (koji sadrzi funkciju main()) mogao biti izostavljen iz test projekta.
 */

#ifndef RENT_A_CAR_STANJE_H
#define RENT_A_CAR_STANJE_H

#include "rent_a_car_logic.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_AUTOMOBILA      100   /**< Maksimalan broj automobila koji se moze cuvati u memoriji. */
#define MAX_IZNAJMLJIVANJA  200   /**< Maksimalan broj zapisa o iznajmljivanju koji se moze cuvati u memoriji. */

    extern Automobil      automobili[MAX_AUTOMOBILA];          /**< Niz svih automobila ucitanih u memoriju. */
    extern int            brojAutomobila;                      /**< Trenutan broj automobila u nizu \ref automobili. */

    extern Iznajmljivanje iznajmljivanja[MAX_IZNAJMLJIVANJA];  /**< Niz svih zapisa o iznajmljivanju. */
    extern int            brojIznajmljivanja;                  /**< Trenutan broj zapisa u nizu \ref iznajmljivanja. */

    /* Pomocne funkcije koje zavise od globalnog stanja */
    int sledeciIdAutomobila(void);
    int sledeciIdIznajmljivanja(void);
    int pronadjiAutomobilPoId(int id);

#ifdef __cplusplus
}
#endif

#endif /* RENT_A_CAR_STANJE_H */
