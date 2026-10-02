/**
 * \file rent_a_car_fajlovi.h
 *
 * \brief Ucitavanje i cuvanje podataka rent-a-car sistema u tekstualnim fajlovima.
 *
 * Funkcije su izdvojene iz main.c i prosirene parametrom \p putanja, umjesto
 * da koriste fiksno zadata imena fajlova. Na taj nacin aplikacija radi sa
 * stvarnim fajlovima (cars.txt, rentals.txt), a testovi sa privremenim
 * fajlovima, bez rizika da se prepisu stvarni podaci. Funkcije vracaju
 * \ref RentStatus kako bi uspjeh ili neuspjeh operacije mogao da se provjeri.
 */

#ifndef RENT_A_CAR_FAJLOVI_H
#define RENT_A_CAR_FAJLOVI_H

#include "rent_a_car_logic.h"

#ifdef __cplusplus
extern "C" {
#endif

    RentStatus ucitajAutomobile(const char* putanja);
    RentStatus sacuvajAutomobile(const char* putanja);
    RentStatus ucitajIznajmljivanja(const char* putanja);
    RentStatus sacuvajIznajmljivanja(const char* putanja);

#ifdef __cplusplus
}
#endif

#endif /* RENT_A_CAR_FAJLOVI_H */
