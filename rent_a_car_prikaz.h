/**
 * \file rent_a_car_prikaz.h
 *
 * \brief Funkcije za ispis menija i tabelarnih pregleda na standardni izlaz.
 *
 * Izdvojene su iz main.c kako bi mogle biti testirane nezavisno od funkcije
 * main(). Ne citaju nista sa standardnog ulaza - samo ispisuju trenutno
 * stanje globalnih nizova iz rent_a_car_stanje.h.
 */

#ifndef RENT_A_CAR_PRIKAZ_H
#define RENT_A_CAR_PRIKAZ_H

#ifdef __cplusplus
extern "C" {
#endif

    void prikaziMeni(void);
    void prikaziAutomobile(void);
    void prikaziIznajmljivanja(void);

#ifdef __cplusplus
}
#endif

#endif /* RENT_A_CAR_PRIKAZ_H */
