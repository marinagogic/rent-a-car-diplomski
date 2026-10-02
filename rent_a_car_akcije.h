/**
 * \file rent_a_car_akcije.h
 *
 * \brief Akcije glavnog menija rent-a-car sistema (unos, ispis i izmjena stanja).
 */

#ifndef RENT_A_CAR_AKCIJE_H
#define RENT_A_CAR_AKCIJE_H

#ifdef __cplusplus
extern "C" {
#endif

    /* Pomocna funkcija za rad sa standardnim ulazom */
    void ocistiUlazniBafer(void);

    /* Akcije menija */
    void dodajAutomobil(const char* fajlAutomobila);
    void obrisiAutomobil(const char* fajlAutomobila);
    void iznajmiAutomobil(const char* fajlAutomobila, const char* fajlIznajmljivanja);
    void vratiAutomobil(const char* fajlAutomobila, const char* fajlIznajmljivanja);

#ifdef __cplusplus
}
#endif

#endif /* RENT_A_CAR_AKCIJE_H */
