/**
 * \file TestSuite_rent_a_car_logic.c
 *
 * \brief Parasoft C/C++test jedinicni testovi za poslovnu logiku (rent_a_car_logic.c).
 *
 * Funkcije poslovne logike ne zavise od standardnog ulaza/izlaza,
 * globalnog stanja ni fajlova, pa za njih nisu potrebni stubovi.
 *
 * Test slucajevi (ID-jevi u \tracehead) odgovaraju Google Test testovima
 * istog naziva, kako bi se rezultati dva alata mogli direktno porediti.
 */
#include "cpptest.h"

/* CPPTEST_TEST_SUITE_CODE_BEGIN AdditionalIncludes */
#include <string.h>
#include "rent_a_car_logic.h"
/* CPPTEST_TEST_SUITE_CODE_END AdditionalIncludes */

CPPTEST_CONTEXT("/RentACar/rent_a_car_logic.c");
CPPTEST_TEST_SUITE_INCLUDED_TO("/RentACar/rent_a_car_logic.c");

EXTERN_C_LINKAGE void TestSuite_rent_a_car_logic_gtest_testSuiteBegin(void);
EXTERN_C_LINKAGE int TestSuite_rent_a_car_logic_gtest_callTest(const char*);

CPPTEST_TEST_SUITE(TestSuite_rent_a_car_logic_gtest);
        CPPTEST_TEST_SUITE_SETUP(TestSuite_rent_a_car_logic_gtest_testSuiteSetUp);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_ValidnoGodisteUSredini);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_DonjaGranicaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_GornjaGranicaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_IspodDonjeGraniceNijeValidno);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_IznadGornjeGraniceNijeValidno);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_PozitivnaCijenaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NulaNijeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NegativnaCijenaNijeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NajmanjaPozitivnaCijenaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_ValidanBrojUSredini);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_DonjaGranicaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_GornjaGranicaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_NulaNijeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_IznadGornjeGraniceNijeValidno);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_NegativanBrojNijeValidan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_FormatirajStatusAutomobila_DostupanVracaTacanString);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_FormatirajStatusAutomobila_IznajmljenVracaTacanString);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_ValidniUlaziDajuTacanRezultat);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NevalidanBrojDanaVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_PrekoracenBrojDanaVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NevalidnaCijenaVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NegativnaCijenaVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_DonjaGranicaBrojaDana);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_GornjaGranicaBrojaDana);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_DostupanAutomobilVracaJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_IznajmljenAutomobilVracaNulu);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_NullPokazivacVracaNulu);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_ValidanAutomobilVracaOk);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NevalidnoGodisteVracaInvalidYear);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NevalidnaCijenaVracaInvalidPrice);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NullPokazivacVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ValidniPodaciPopunjavajuStrukturu);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnoGodisteVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullMarkaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullModelVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullAutomobilVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnaCijenaVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_PredugackaMarkaSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_MarkaNaGraniciDuzineSeNeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_MarkaPrekoGraniceDuzineSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ModelNaGraniciDuzineSeNeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ModelPrekoGraniceDuzineSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnoGodisteNeMijenjaStrukturu);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnaCijenaNeMijenjaStrukturu);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_DostupanAutomobilMozeSeObrisati);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_IznajmljenAutomobilNeMozeSeObrisati);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_NullPokazivacVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjeIzSredineNizaPomjeraElemente);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NevalidanIndeksVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NullNizVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NullBrojElemenataVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NegativanIndeksVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjePoslednjegElementa);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjePrvogElementa);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ValidniPodaciDajuAktivnoIznajmljivanje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NevalidanBrojDanaVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NevalidnaCijenaVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullIznajmljivanjeVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullImeVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullPrezimeVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullDatumPocetkaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullDatumKrajaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DonjaGranicaBrojaDanaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_GornjaGranicaBrojaDanaJeValidna);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrekoracenBrojDanaVracaGresku);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ImeNaGraniciDuzineSeNeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ImePrekoGraniceDuzineSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrezimeNaGraniciDuzineSeNeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrezimePrekoGraniceDuzineSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumPocetkaNaGraniciDuzineSeNeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumPocetkaPrekoGraniceDuzineSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumKrajaNaGraniciDuzineSeNeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumKrajaPrekoGraniceDuzineSeSkracuje);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_VracanjeSaPronadjenimZapisom);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_VracanjeBezPronadjenogZapisa);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_AutomobilKojiVecNijeIznajmljen);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_NullAutomobilVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PronalaziAktivanZapis);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_VracaMinusJedanAkoNemaAktivnog);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_NullNizVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PreskaceAktivanZapisDrugogAutomobila);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PrazanNizVracaMinusJedan);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_AktivanZapisNaPrvojPoziciji);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_ValidnaLinijaSeParsiraUspjesno);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NepotpunaLinijaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_PraznaLinijaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NullLinijaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NullAutomobilVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickoGodisteVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickiIdVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickaCijenaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickoPoljeDostupanVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_ValidnaLinijaSeParsiraUspjesno);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NepotpunaLinijaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NullLinijaVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NullIznajmljivanjeVracaNullPointer);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_PraznaLinijaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiBrojDanaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiIdVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiIdAutomobilaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickaUkupnaCijenaVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickoPoljeAktivnoVracaParseError);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_OpisStatusa_PrvaGrupaStatusaVracaTacanOpis);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_OpisStatusa_DrugaGrupaStatusaVracaTacanOpis);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_OpisStatusa_InvalidIdVracaTacanOpis);
        CPPTEST_TEST(TestSuite_rent_a_car_logic_gtest_OpisStatusa_NepoznatStatusVracaDefaultOpis);
        CPPTEST_TEST_SUITE_TEARDOWN(TestSuite_rent_a_car_logic_gtest_testSuiteTearDown);
CPPTEST_TEST_SUITE_END();

void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_ValidnoGodisteUSredini(void);
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_DonjaGranicaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_GornjaGranicaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_IspodDonjeGraniceNijeValidno(void);
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_IznadGornjeGraniceNijeValidno(void);
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_PozitivnaCijenaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NulaNijeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NegativnaCijenaNijeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NajmanjaPozitivnaCijenaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_ValidanBrojUSredini(void);
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_DonjaGranicaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_GornjaGranicaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_NulaNijeValidna(void);
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_IznadGornjeGraniceNijeValidno(void);
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_NegativanBrojNijeValidan(void);
void TestSuite_rent_a_car_logic_gtest_FormatirajStatusAutomobila_DostupanVracaTacanString(void);
void TestSuite_rent_a_car_logic_gtest_FormatirajStatusAutomobila_IznajmljenVracaTacanString(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_ValidniUlaziDajuTacanRezultat(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NevalidanBrojDanaVracaMinusJedan(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_PrekoracenBrojDanaVracaMinusJedan(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NevalidnaCijenaVracaMinusJedan(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NegativnaCijenaVracaMinusJedan(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_DonjaGranicaBrojaDana(void);
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_GornjaGranicaBrojaDana(void);
void TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_DostupanAutomobilVracaJedan(void);
void TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_IznajmljenAutomobilVracaNulu(void);
void TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_NullPokazivacVracaNulu(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_ValidanAutomobilVracaOk(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NevalidnoGodisteVracaInvalidYear(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NevalidnaCijenaVracaInvalidPrice(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NullPokazivacVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ValidniPodaciPopunjavajuStrukturu(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnoGodisteVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullMarkaVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullModelVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullAutomobilVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnaCijenaVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_PredugackaMarkaSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_MarkaNaGraniciDuzineSeNeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_MarkaPrekoGraniceDuzineSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ModelNaGraniciDuzineSeNeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ModelPrekoGraniceDuzineSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnoGodisteNeMijenjaStrukturu(void);
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnaCijenaNeMijenjaStrukturu(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_DostupanAutomobilMozeSeObrisati(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_IznajmljenAutomobilNeMozeSeObrisati(void);
void TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_NullPokazivacVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjeIzSredineNizaPomjeraElemente(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NevalidanIndeksVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NullNizVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NullBrojElemenataVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NegativanIndeksVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjePoslednjegElementa(void);
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjePrvogElementa(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ValidniPodaciDajuAktivnoIznajmljivanje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NevalidanBrojDanaVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NevalidnaCijenaVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullIznajmljivanjeVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullImeVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullPrezimeVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullDatumPocetkaVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullDatumKrajaVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DonjaGranicaBrojaDanaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_GornjaGranicaBrojaDanaJeValidna(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrekoracenBrojDanaVracaGresku(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ImeNaGraniciDuzineSeNeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ImePrekoGraniceDuzineSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrezimeNaGraniciDuzineSeNeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrezimePrekoGraniceDuzineSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumPocetkaNaGraniciDuzineSeNeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumPocetkaPrekoGraniceDuzineSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumKrajaNaGraniciDuzineSeNeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumKrajaPrekoGraniceDuzineSeSkracuje(void);
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_VracanjeSaPronadjenimZapisom(void);
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_VracanjeBezPronadjenogZapisa(void);
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_AutomobilKojiVecNijeIznajmljen(void);
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_NullAutomobilVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PronalaziAktivanZapis(void);
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_VracaMinusJedanAkoNemaAktivnog(void);
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_NullNizVracaMinusJedan(void);
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PreskaceAktivanZapisDrugogAutomobila(void);
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PrazanNizVracaMinusJedan(void);
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_AktivanZapisNaPrvojPoziciji(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_ValidnaLinijaSeParsiraUspjesno(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NepotpunaLinijaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_PraznaLinijaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NullLinijaVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NullAutomobilVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickoGodisteVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickiIdVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickaCijenaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickoPoljeDostupanVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_ValidnaLinijaSeParsiraUspjesno(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NepotpunaLinijaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NullLinijaVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NullIznajmljivanjeVracaNullPointer(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_PraznaLinijaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiBrojDanaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiIdVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiIdAutomobilaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickaUkupnaCijenaVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickoPoljeAktivnoVracaParseError(void);
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_PrvaGrupaStatusaVracaTacanOpis(void);
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_DrugaGrupaStatusaVracaTacanOpis(void);
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_InvalidIdVracaTacanOpis(void);
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_NepoznatStatusVracaDefaultOpis(void);

CPPTEST_TEST_SUITE_REGISTRATION(TestSuite_rent_a_car_logic_gtest);

void TestSuite_rent_a_car_logic_gtest_testSuiteSetUp(void);
void TestSuite_rent_a_car_logic_gtest_testSuiteSetUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteSetUp */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteSetUp */
}

void TestSuite_rent_a_car_logic_gtest_testSuiteTearDown(void);
void TestSuite_rent_a_car_logic_gtest_testSuiteTearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestSuiteTearDown */
/* CPPTEST_TEST_SUITE_CODE_END TestSuiteTearDown */
}

/** Poziva se prije svakog testa. */
void TestSuite_rent_a_car_logic_gtest_setUp(void);
void TestSuite_rent_a_car_logic_gtest_setUp(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseSetUp */
/* CPPTEST_TEST_SUITE_CODE_END TestCaseSetUp */
}

/** Poziva se poslije svakog testa. */
void TestSuite_rent_a_car_logic_gtest_tearDown(void);
void TestSuite_rent_a_car_logic_gtest_tearDown(void)
{
/* CPPTEST_TEST_SUITE_CODE_BEGIN TestCaseTearDown */
/* CPPTEST_TEST_SUITE_CODE_END TestCaseTearDown */
}


/* CPPTEST_TEST_CASE_BEGIN JeGodisteValidno_ValidnoGodisteUSredini */
/**
 * \tracehead{JeGodisteValidno_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste u sredini dozvoljenog opsega (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = 2020
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 1 (godiste je validno).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_ValidnoGodisteUSredini(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeGodisteValidno(2020));
}
/* CPPTEST_TEST_CASE_END JeGodisteValidno_ValidnoGodisteUSredini */

/* CPPTEST_TEST_CASE_BEGIN JeGodisteValidno_DonjaGranicaJeValidna */
/**
 * \tracehead{JeGodisteValidno_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste jednako donjoj granici MIN_GODISTE (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MIN_GODISTE (1950)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 1 (donja granica je validna vrijednost).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_DonjaGranicaJeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeGodisteValidno(MIN_GODISTE));
}
/* CPPTEST_TEST_CASE_END JeGodisteValidno_DonjaGranicaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeGodisteValidno_GornjaGranicaJeValidna */
/**
 * \tracehead{JeGodisteValidno_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste jednako gornjoj granici MAX_GODISTE (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MAX_GODISTE (2100)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 1 (gornja granica je validna vrijednost).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_GornjaGranicaJeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeGodisteValidno(MAX_GODISTE));
}
/* CPPTEST_TEST_CASE_END JeGodisteValidno_GornjaGranicaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeGodisteValidno_IspodDonjeGraniceNijeValidno */
/**
 * \tracehead{JeGodisteValidno_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste tek ispod donje granice (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MIN_GODISTE - 1 (1949)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 0 (godiste nije validno).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_IspodDonjeGraniceNijeValidno(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeGodisteValidno(MIN_GODISTE - 1));
}
/* CPPTEST_TEST_CASE_END JeGodisteValidno_IspodDonjeGraniceNijeValidno */

/* CPPTEST_TEST_CASE_BEGIN JeGodisteValidno_IznadGornjeGraniceNijeValidno */
/**
 * \tracehead{JeGodisteValidno_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeGodisteValidno" u slucaju kada je godiste tek iznad gornje granice (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeGodisteValidno sa sljedecim argumentom:
 *  * godiste = MAX_GODISTE + 1 (2101)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeGodisteValidno vraca 0 (godiste nije validno).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeGodisteValidno_IznadGornjeGraniceNijeValidno(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeGodisteValidno(MAX_GODISTE + 1));
}
/* CPPTEST_TEST_CASE_END JeGodisteValidno_IznadGornjeGraniceNijeValidno */

/* CPPTEST_TEST_CASE_BEGIN JeCijenaValidna_PozitivnaCijenaJeValidna */
/**
 * \tracehead{JeCijenaValidna_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena veca od nule (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = 45.5
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 1 (cijena je validna).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_PozitivnaCijenaJeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeCijenaValidna(45.5f));
}
/* CPPTEST_TEST_CASE_END JeCijenaValidna_PozitivnaCijenaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeCijenaValidna_NulaNijeValidna */
/**
 * \tracehead{JeCijenaValidna_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena jednaka nuli (analiza granicnih vrijednosti - granica izmedju nevalidnih i validnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = 0.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 0 (nula nije validna cijena).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NulaNijeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeCijenaValidna(0.0f));
}
/* CPPTEST_TEST_CASE_END JeCijenaValidna_NulaNijeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeCijenaValidna_NegativnaCijenaNijeValidna */
/**
 * \tracehead{JeCijenaValidna_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena negativna (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = -10.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 0 (cijena nije validna).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NegativnaCijenaNijeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeCijenaValidna(-10.0f));
}
/* CPPTEST_TEST_CASE_END JeCijenaValidna_NegativnaCijenaNijeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeCijenaValidna_NajmanjaPozitivnaCijenaJeValidna */
/**
 * \tracehead{JeCijenaValidna_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeCijenaValidna" u slucaju kada je cijena najmanja cijena koja se moze izraziti u KM sa preciznoscu od dvije decimale, 0.01 KM (analiza granicnih vrijednosti - validna vrijednost neposredno iznad granice 0).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeCijenaValidna sa sljedecim argumentom:
 *  * cijena = 0.01
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeCijenaValidna vraca 1 (cijena je validna).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeCijenaValidna_NajmanjaPozitivnaCijenaJeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeCijenaValidna(0.01f));
}
/* CPPTEST_TEST_CASE_END JeCijenaValidna_NajmanjaPozitivnaCijenaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeBrojDanaValidan_ValidanBrojUSredini */
/**
 * \tracehead{JeBrojDanaValidan_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana u sredini dozvoljenog opsega (podjela na klase ekvivalencije - validna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = 10
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 1 (broj dana je validan).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_ValidanBrojUSredini(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeBrojDanaValidan(10));
}
/* CPPTEST_TEST_CASE_END JeBrojDanaValidan_ValidanBrojUSredini */

/* CPPTEST_TEST_CASE_BEGIN JeBrojDanaValidan_DonjaGranicaJeValidna */
/**
 * \tracehead{JeBrojDanaValidan_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana jednak donjoj granici MIN_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = MIN_BROJ_DANA (1)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 1 (donja granica je validna vrijednost).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_DonjaGranicaJeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeBrojDanaValidan(MIN_BROJ_DANA));
}
/* CPPTEST_TEST_CASE_END JeBrojDanaValidan_DonjaGranicaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeBrojDanaValidan_GornjaGranicaJeValidna */
/**
 * \tracehead{JeBrojDanaValidan_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana jednak gornjoj granici MAX_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = MAX_BROJ_DANA (365)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 1 (gornja granica je validna vrijednost).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_GornjaGranicaJeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeBrojDanaValidan(MAX_BROJ_DANA));
}
/* CPPTEST_TEST_CASE_END JeBrojDanaValidan_GornjaGranicaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeBrojDanaValidan_NulaNijeValidna */
/**
 * \tracehead{JeBrojDanaValidan_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana jednak nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = 0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 0 (broj dana nije validan).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_NulaNijeValidna(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeBrojDanaValidan(0));
}
/* CPPTEST_TEST_CASE_END JeBrojDanaValidan_NulaNijeValidna */

/* CPPTEST_TEST_CASE_BEGIN JeBrojDanaValidan_IznadGornjeGraniceNijeValidno */
/**
 * \tracehead{JeBrojDanaValidan_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana tek iznad gornje granice (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = MAX_BROJ_DANA + 1 (366)
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 0 (broj dana nije validan).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_IznadGornjeGraniceNijeValidno(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeBrojDanaValidan(MAX_BROJ_DANA + 1));
}
/* CPPTEST_TEST_CASE_END JeBrojDanaValidan_IznadGornjeGraniceNijeValidno */

/* CPPTEST_TEST_CASE_BEGIN JeBrojDanaValidan_NegativanBrojNijeValidan */
/**
 * \tracehead{JeBrojDanaValidan_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeBrojDanaValidan" u slucaju kada je broj dana negativan (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeBrojDanaValidan sa sljedecim argumentom:
 *  * brojDana = -5
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeBrojDanaValidan vraca 0 (broj dana nije validan).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeBrojDanaValidan_NegativanBrojNijeValidan(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeBrojDanaValidan(-5));
}
/* CPPTEST_TEST_CASE_END JeBrojDanaValidan_NegativanBrojNijeValidan */

/* CPPTEST_TEST_CASE_BEGIN FormatirajStatusAutomobila_DostupanVracaTacanString */
/**
 * \tracehead{FormatirajStatusAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "formatirajStatusAutomobila" u slucaju kada je automobil dostupan.
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju formatirajStatusAutomobila sa sljedecim argumentom:
 *  * dostupan = 1
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija formatirajStatusAutomobila vraca string "Dostupan".
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_FormatirajStatusAutomobila_DostupanVracaTacanString(void)
{
    CPPTEST_ASSERT_CSTR_EQUAL("Dostupan", formatirajStatusAutomobila(1));
}
/* CPPTEST_TEST_CASE_END FormatirajStatusAutomobila_DostupanVracaTacanString */

/* CPPTEST_TEST_CASE_BEGIN FormatirajStatusAutomobila_IznajmljenVracaTacanString */
/**
 * \tracehead{FormatirajStatusAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "formatirajStatusAutomobila" u slucaju kada je automobil iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju formatirajStatusAutomobila sa sljedecim argumentom:
 *  * dostupan = 0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija formatirajStatusAutomobila vraca string "Iznajmljen".
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_FormatirajStatusAutomobila_IznajmljenVracaTacanString(void)
{
    CPPTEST_ASSERT_CSTR_EQUAL("Iznajmljen", formatirajStatusAutomobila(0));
}
/* CPPTEST_TEST_CASE_END FormatirajStatusAutomobila_IznajmljenVracaTacanString */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_ValidniUlaziDajuTacanRezultat */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada su i broj dana i cijena po danu validni.
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 3
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca 150.0 (3 * 50.0).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_ValidniUlaziDajuTacanRezultat(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(150.0f, izracunajUkupnuCijenu(3, 50.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_ValidniUlaziDajuTacanRezultat */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_NevalidanBrojDanaVracaMinusJedan */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je broj dana jednak nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 0
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NevalidanBrojDanaVracaMinusJedan(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(-1.0f, izracunajUkupnuCijenu(0, 50.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_NevalidanBrojDanaVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_PrekoracenBrojDanaVracaMinusJedan */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada broj dana prelazi gornju granicu (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = MAX_BROJ_DANA + 1 (366)
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_PrekoracenBrojDanaVracaMinusJedan(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(-1.0f, izracunajUkupnuCijenu(MAX_BROJ_DANA + 1, 50.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_PrekoracenBrojDanaVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_NevalidnaCijenaVracaMinusJedan */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je cijena po danu jednaka nuli (analiza granicnih vrijednosti - granica izmedju nevalidnih i validnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 3
 *  * cijenaPoDanu = 0.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NevalidnaCijenaVracaMinusJedan(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(-1.0f, izracunajUkupnuCijenu(3, 0.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_NevalidnaCijenaVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_NegativnaCijenaVracaMinusJedan */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je cijena po danu negativna (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = 3
 *  * cijenaPoDanu = -20.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca -1.0 (vrijednost greske).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_NegativnaCijenaVracaMinusJedan(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(-1.0f, izracunajUkupnuCijenu(3, -20.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_NegativnaCijenaVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_DonjaGranicaBrojaDana */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je broj dana jednak donjoj granici MIN_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = MIN_BROJ_DANA (1)
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca 50.0 (1 * 50.0).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_DonjaGranicaBrojaDana(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(50.0f, izracunajUkupnuCijenu(MIN_BROJ_DANA, 50.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_DonjaGranicaBrojaDana */

/* CPPTEST_TEST_CASE_BEGIN IzracunajUkupnuCijenu_GornjaGranicaBrojaDana */
/**
 * \tracehead{IzracunajUkupnuCijenu_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "izracunajUkupnuCijenu" u slucaju kada je broj dana jednak gornjoj granici MAX_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju izracunajUkupnuCijenu sa sljedecim argumentima:
 *  * brojDana = MAX_BROJ_DANA (365)
 *  * cijenaPoDanu = 50.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija izracunajUkupnuCijenu vraca 18250.0 (365 * 50.0).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_IzracunajUkupnuCijenu_GornjaGranicaBrojaDana(void)
{
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(18250.0f, izracunajUkupnuCijenu(MAX_BROJ_DANA, 50.0f), 0.001);
}
/* CPPTEST_TEST_CASE_END IzracunajUkupnuCijenu_GornjaGranicaBrojaDana */

/* CPPTEST_TEST_CASE_BEGIN JeAutomobilDostupan_DostupanAutomobilVracaJedan */
/**
 * \tracehead{JeAutomobilDostupan_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeAutomobilDostupan" u slucaju kada je automobil dostupan.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 1.
 * 2. Pozvati funkciju jeAutomobilDostupan sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeAutomobilDostupan vraca 1.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_DostupanAutomobilVracaJedan(void)
{
    Automobil a = {0};
    a.dostupan = 1;
    CPPTEST_ASSERT_INTEGER_EQUAL(1, jeAutomobilDostupan(&a));
}
/* CPPTEST_TEST_CASE_END JeAutomobilDostupan_DostupanAutomobilVracaJedan */

/* CPPTEST_TEST_CASE_BEGIN JeAutomobilDostupan_IznajmljenAutomobilVracaNulu */
/**
 * \tracehead{JeAutomobilDostupan_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeAutomobilDostupan" u slucaju kada je automobil iznajmljen.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Pozvati funkciju jeAutomobilDostupan sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeAutomobilDostupan vraca 0.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_IznajmljenAutomobilVracaNulu(void)
{
    Automobil a = {0};
    a.dostupan = 0;
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeAutomobilDostupan(&a));
}
/* CPPTEST_TEST_CASE_END JeAutomobilDostupan_IznajmljenAutomobilVracaNulu */

/* CPPTEST_TEST_CASE_BEGIN JeAutomobilDostupan_NullPokazivacVracaNulu */
/**
 * \tracehead{JeAutomobilDostupan_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "jeAutomobilDostupan" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju jeAutomobilDostupan sa sljedecim argumentom:
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija jeAutomobilDostupan vraca 0 i ne dolazi do pada programa.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_JeAutomobilDostupan_NullPokazivacVracaNulu(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(0, jeAutomobilDostupan(NULL));
}
/* CPPTEST_TEST_CASE_END JeAutomobilDostupan_NullPokazivacVracaNulu */

/* CPPTEST_TEST_CASE_BEGIN ValidirajAutomobil_ValidanAutomobilVracaOk */
/**
 * \tracehead{ValidirajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada su godiste i cijena automobila validni.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa sljedecim vrijednostima:
 *  * godiste = 2020
 *  * cijena_po_danu = 45.0
 * 2. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_OK.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_ValidanAutomobilVracaOk(void)
{
    Automobil a = {0};
    a.godiste = 2020;
    a.cijena_po_danu = 45.0f;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, validirajAutomobil(&a));
}
/* CPPTEST_TEST_CASE_END ValidirajAutomobil_ValidanAutomobilVracaOk */

/* CPPTEST_TEST_CASE_BEGIN ValidirajAutomobil_NevalidnoGodisteVracaInvalidYear */
/**
 * \tracehead{ValidirajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada godiste automobila nije u dozvoljenom opsegu.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa sljedecim vrijednostima:
 *  * godiste = 1900
 *  * cijena_po_danu = 45.0
 * 2. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_INVALID_YEAR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NevalidnoGodisteVracaInvalidYear(void)
{
    Automobil a = {0};
    a.godiste = 1900;
    a.cijena_po_danu = 45.0f;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_YEAR, validirajAutomobil(&a));
}
/* CPPTEST_TEST_CASE_END ValidirajAutomobil_NevalidnoGodisteVracaInvalidYear */

/* CPPTEST_TEST_CASE_BEGIN ValidirajAutomobil_NevalidnaCijenaVracaInvalidPrice */
/**
 * \tracehead{ValidirajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada je godiste validno, ali cijena po danu nije validna.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa sljedecim vrijednostima:
 *  * godiste = 2020
 *  * cijena_po_danu = -5.0
 * 2. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_INVALID_PRICE.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NevalidnaCijenaVracaInvalidPrice(void)
{
    Automobil a = {0};
    a.godiste = 2020;
    a.cijena_po_danu = -5.0f;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_PRICE, validirajAutomobil(&a));
}
/* CPPTEST_TEST_CASE_END ValidirajAutomobil_NevalidnaCijenaVracaInvalidPrice */

/* CPPTEST_TEST_CASE_BEGIN ValidirajAutomobil_NullPokazivacVracaNullPointer */
/**
 * \tracehead{ValidirajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajAutomobil" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju validirajAutomobil sa sljedecim argumentom:
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajAutomobil_NullPokazivacVracaNullPointer(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, validirajAutomobil(NULL));
}
/* CPPTEST_TEST_CASE_END ValidirajAutomobil_NullPokazivacVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_ValidniPodaciPopunjavajuStrukturu */
/**
 * \tracehead{KreirajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada su svi ulazni podaci validni.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Struktura "a" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijena_po_danu = 45.0
 *  * dostupan = 1 (novi automobil je dostupan).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ValidniPodaciPopunjavajuStrukturu(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 2020, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, a.id);
    CPPTEST_ASSERT_CSTR_EQUAL("Volkswagen", a.marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Golf", a.model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2020, a.godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(45.0f, a.cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, a.dostupan);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_ValidniPodaciPopunjavajuStrukturu */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NevalidnoGodisteVracaGresku */
/**
 * \tracehead{KreirajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada godiste nije u dozvoljenom opsegu.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 1800
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_YEAR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnoGodisteVracaGresku(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 1800, 45.0f);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_YEAR, status);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NevalidnoGodisteVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NullMarkaVracaNullPointer */
/**
 * \tracehead{KreirajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je parametar marka NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = NULL
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullMarkaVracaNullPointer(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, NULL, "Golf", 2020, 45.0f);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NullMarkaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NullModelVracaNullPointer */
/**
 * \tracehead{KreirajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je parametar model NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = NULL
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullModelVracaNullPointer(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", NULL, 2020, 45.0f);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NullModelVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NullAutomobilVracaNullPointer */
/**
 * \tracehead{KreirajAutomobil_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je parametar noviAutomobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = NULL
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_NULL_POINTER i ne dolazi do pada programa.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NullAutomobilVracaNullPointer(void)
{
    RentStatus status = kreirajAutomobil(NULL, 1, "Volkswagen", "Golf", 2020, 45.0f);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NullAutomobilVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NevalidnaCijenaVracaGresku */
/**
 * \tracehead{KreirajAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je godiste validno, ali cijena po danu nije validna (podjela na klase ekvivalencije - nevalidna klasa).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = -5.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_PRICE.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnaCijenaVracaGresku(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 2020, -5.0f);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_PRICE, status);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NevalidnaCijenaVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_PredugackaMarkaSeSkracuje */
/**
 * \tracehead{KreirajAutomobil_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada je marka znatno duza od maksimalne dozvoljene duzine (podjela na klase ekvivalencije - klasa predugackih stringova).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = string od 40 karaktera
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Duzina stringa a.marka je jednaka DUZINA_STRINGA - 1 (29), tj. marka je skracena i ispravno zavrsena znakom '\0'.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_PredugackaMarkaSeSkracuje(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "Golf", 2020, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL((size_t)(DUZINA_STRINGA - 1), strlen(a.marka));
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_PredugackaMarkaSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_MarkaNaGraniciDuzineSeNeSkracuje */
/**
 * \tracehead{KreirajAutomobil_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada marka ima tacno DUZINA_STRINGA - 1 (29) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (29 karaktera)
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.marka je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (marka nije skracena).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_MarkaNaGraniciDuzineSeNeSkracuje(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "ABCDEFGHIJABCDEFGHIJABCDEFGHI", "Golf", 2020, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.marka);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_MarkaNaGraniciDuzineSeNeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_MarkaPrekoGraniceDuzineSeSkracuje */
/**
 * \tracehead{KreirajAutomobil_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada marka ima DUZINA_STRINGA (30) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (30 karaktera)
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.marka je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (poslednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_MarkaPrekoGraniceDuzineSeSkracuje(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "Golf", 2020, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.marka);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_MarkaPrekoGraniceDuzineSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_ModelNaGraniciDuzineSeNeSkracuje */
/**
 * \tracehead{KreirajAutomobil_TC_09, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada model ima tacno DUZINA_STRINGA - 1 (29) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (29 karaktera)
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.model je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (model nije skracen).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ModelNaGraniciDuzineSeNeSkracuje(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "ABCDEFGHIJABCDEFGHIJABCDEFGHI", 2020, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.model);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_ModelNaGraniciDuzineSeNeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_ModelPrekoGraniceDuzineSeSkracuje */
/**
 * \tracehead{KreirajAutomobil_TC_10, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "kreirajAutomobil" u slucaju kada model ima DUZINA_STRINGA (30) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (30 karaktera)
 *  * godiste = 2020
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_OK.
 * 2. Vrijednost a.model je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHI" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_ModelPrekoGraniceDuzineSeSkracuje(void)
{
    Automobil a = {0};
    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJ", 2020, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHI", a.model);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_ModelPrekoGraniceDuzineSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NevalidnoGodisteNeMijenjaStrukturu */
/**
 * \tracehead{KreirajAutomobil_TC_11, Funkcionalni test}
 * Test provjerava da funkcija "kreirajAutomobil" ne mijenja izlaznu strukturu kada godiste nije validno (negativan test - stanje izlaznog parametra nakon greske).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil i popuniti ga postojecim podacima:
 *  * id = 7, marka = "Staro", model = "Auto", godiste = 2000, cijena_po_danu = 10.0, dostupan = 0
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 1800
 *  * cijenaPoDanu = 45.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_YEAR.
 * 2. Struktura "a" je nepromijenjena (sva polja imaju vrijednosti iz koraka 1), tj. funkcija ne upisuje podatke prije uspjesne validacije.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnoGodisteNeMijenjaStrukturu(void)
{
    Automobil a = {0};
    a.id = 7;
    strcpy(a.marka, "Staro");
    strcpy(a.model, "Auto");
    a.godiste = 2000;
    a.cijena_po_danu = 10.0f;
    a.dostupan = 0;

    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 1800, 45.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_YEAR, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(7, a.id);
    CPPTEST_ASSERT_CSTR_EQUAL("Staro", a.marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Auto", a.model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2000, a.godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(10.0f, a.cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, a.dostupan);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NevalidnoGodisteNeMijenjaStrukturu */

/* CPPTEST_TEST_CASE_BEGIN KreirajAutomobil_NevalidnaCijenaNeMijenjaStrukturu */
/**
 * \tracehead{KreirajAutomobil_TC_12, Funkcionalni test}
 * Test provjerava da funkcija "kreirajAutomobil" ne mijenja izlaznu strukturu kada cijena po danu nije validna (negativan test - stanje izlaznog parametra nakon greske).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil i popuniti ga postojecim podacima:
 *  * id = 7, marka = "Staro", model = "Auto", godiste = 2000, cijena_po_danu = 10.0, dostupan = 0
 * 2. Pozvati funkciju kreirajAutomobil sa sljedecim argumentima:
 *  * noviAutomobil = adresa testnog automobila "a"
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijenaPoDanu = -5.0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija kreirajAutomobil vraca RENT_INVALID_PRICE.
 * 2. Struktura "a" je nepromijenjena (sva polja imaju vrijednosti iz koraka 1), tj. funkcija ne upisuje podatke prije uspjesne validacije.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_KreirajAutomobil_NevalidnaCijenaNeMijenjaStrukturu(void)
{
    Automobil a = {0};
    a.id = 7;
    strcpy(a.marka, "Staro");
    strcpy(a.model, "Auto");
    a.godiste = 2000;
    a.cijena_po_danu = 10.0f;
    a.dostupan = 0;

    RentStatus status = kreirajAutomobil(&a, 1, "Volkswagen", "Golf", 2020, -5.0f);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_PRICE, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(7, a.id);
    CPPTEST_ASSERT_CSTR_EQUAL("Staro", a.marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Auto", a.model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2000, a.godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(10.0f, a.cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, a.dostupan);
}
/* CPPTEST_TEST_CASE_END KreirajAutomobil_NevalidnaCijenaNeMijenjaStrukturu */

/* CPPTEST_TEST_CASE_BEGIN ValidirajBrisanjeAutomobila_DostupanAutomobilMozeSeObrisati */
/**
 * \tracehead{ValidirajBrisanjeAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajBrisanjeAutomobila" u slucaju kada je automobil dostupan (brisanje je dozvoljeno).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 1.
 * 2. Pozvati funkciju validirajBrisanjeAutomobila sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajBrisanjeAutomobila vraca RENT_OK.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_DostupanAutomobilMozeSeObrisati(void)
{
    Automobil a = {0};
    a.dostupan = 1;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, validirajBrisanjeAutomobila(&a));
}
/* CPPTEST_TEST_CASE_END ValidirajBrisanjeAutomobila_DostupanAutomobilMozeSeObrisati */

/* CPPTEST_TEST_CASE_BEGIN ValidirajBrisanjeAutomobila_IznajmljenAutomobilNeMozeSeObrisati */
/**
 * \tracehead{ValidirajBrisanjeAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajBrisanjeAutomobila" u slucaju kada je automobil trenutno iznajmljen (brisanje nije dozvoljeno).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Pozvati funkciju validirajBrisanjeAutomobila sa sljedecim argumentom:
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajBrisanjeAutomobila vraca RENT_CAR_NOT_AVAILABLE.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_IznajmljenAutomobilNeMozeSeObrisati(void)
{
    Automobil a = {0};
    a.dostupan = 0;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_CAR_NOT_AVAILABLE, validirajBrisanjeAutomobila(&a));
}
/* CPPTEST_TEST_CASE_END ValidirajBrisanjeAutomobila_IznajmljenAutomobilNeMozeSeObrisati */

/* CPPTEST_TEST_CASE_BEGIN ValidirajBrisanjeAutomobila_NullPokazivacVracaNullPointer */
/**
 * \tracehead{ValidirajBrisanjeAutomobila_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "validirajBrisanjeAutomobila" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju validirajBrisanjeAutomobila sa sljedecim argumentom:
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija validirajBrisanjeAutomobila vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ValidirajBrisanjeAutomobila_NullPokazivacVracaNullPointer(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, validirajBrisanjeAutomobila(NULL));
}
/* CPPTEST_TEST_CASE_END ValidirajBrisanjeAutomobila_NullPokazivacVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_BrisanjeIzSredineNizaPomjeraElemente */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada se brise element iz sredine niza.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil sa id vrijednostima 1, 2 i 3.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 1
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_OK.
 * 2. Vrijednost brojElemenata je jednaka 2.
 * 3. Element niz[0] ima id = 1 (nepromijenjen).
 * 4. Element niz[1] ima id = 3 (pomjeren sa pozicije 2).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjeIzSredineNizaPomjeraElemente(void)
{
    Automobil niz[3] = {0};
    int brojElemenata = 3;

    niz[0].id = 1;
    niz[1].id = 2;
    niz[2].id = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 1);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojElemenata);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, niz[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, niz[1].id);
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_BrisanjeIzSredineNizaPomjeraElemente */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_NevalidanIndeksVracaGresku */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je indeks jednak broju elemenata niza (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 3 (jednak broju elemenata)
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_INVALID_ID.
 * 2. Vrijednost brojElemenata je jednaka 3 (nepromijenjena).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NevalidanIndeksVracaGresku(void)
{
    Automobil niz[3] = {0};
    int brojElemenata = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 3);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_ID, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, brojElemenata);
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_NevalidanIndeksVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_NullNizVracaNullPointer */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je parametar niz NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati brojElemenata = 3.
 * 2. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = NULL
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NullNizVracaNullPointer(void)
{
    int brojElemenata = 3;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, obrisiAutomobilNaIndeksu(NULL, &brojElemenata, 0));
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_NullNizVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_NullBrojElemenataVracaNullPointer */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je parametar brojElemenata NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil.
 * 2. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = NULL
 *  * indeks = 0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NullBrojElemenataVracaNullPointer(void)
{
    Automobil niz[3] = {0};
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, obrisiAutomobilNaIndeksu(niz, NULL, 0));
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_NullBrojElemenataVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_NegativanIndeksVracaGresku */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada je indeks negativan (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = -1
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_INVALID_ID.
 * 2. Vrijednost brojElemenata je jednaka 3 (nepromijenjena).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_NegativanIndeksVracaGresku(void)
{
    Automobil niz[3] = {0};
    int brojElemenata = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, -1);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_ID, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, brojElemenata);
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_NegativanIndeksVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_BrisanjePoslednjegElementa */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada se brise poslednji element niza (analiza granicnih vrijednosti - najveci validan indeks).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil sa id vrijednostima 1, 2 i 3.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 2
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_OK.
 * 2. Vrijednost brojElemenata je jednaka 2.
 * 3. Elementi niz[0] i niz[1] imaju id = 1 i id = 2 (nepromijenjeni).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjePoslednjegElementa(void)
{
    Automobil niz[3] = {0};
    int brojElemenata = 3;

    niz[0].id = 1;
    niz[1].id = 2;
    niz[2].id = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 2);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojElemenata);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, niz[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, niz[1].id);
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_BrisanjePoslednjegElementa */

/* CPPTEST_TEST_CASE_BEGIN ObrisiAutomobilNaIndeksu_BrisanjePrvogElementa */
/**
 * \tracehead{ObrisiAutomobilNaIndeksu_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obrisiAutomobilNaIndeksu" u slucaju kada se brise prvi element niza (analiza granicnih vrijednosti - najmanji validan indeks).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 3 elementa tipa Automobil sa id vrijednostima 1, 2 i 3.
 * 2. Definisati brojElemenata = 3.
 * 3. Pozvati funkciju obrisiAutomobilNaIndeksu sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = adresa promjenljive brojElemenata
 *  * indeks = 0
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obrisiAutomobilNaIndeksu vraca RENT_OK.
 * 2. Vrijednost brojElemenata je jednaka 2.
 * 3. Element niz[0] ima id = 2 (pomjeren sa pozicije 1).
 * 4. Element niz[1] ima id = 3 (pomjeren sa pozicije 2).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObrisiAutomobilNaIndeksu_BrisanjePrvogElementa(void)
{
    Automobil niz[3] = {0};
    int brojElemenata = 3;

    niz[0].id = 1;
    niz[1].id = 2;
    niz[2].id = 3;

    RentStatus status = obrisiAutomobilNaIndeksu(niz, &brojElemenata, 0);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, brojElemenata);
    CPPTEST_ASSERT_INTEGER_EQUAL(2, niz[0].id);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, niz[1].id);
}
/* CPPTEST_TEST_CASE_END ObrisiAutomobilNaIndeksu_BrisanjePrvogElementa */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_ValidniPodaciDajuAktivnoIznajmljivanje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada su svi ulazni podaci validni.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Struktura "r" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * id_automobila = 5
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datum_pocetka = "01-01-2026"
 *  * datum_kraja = "05-01-2026"
 *  * broj_dana = 4
 *  * ukupna_cijena = 200.0 (4 * 50.0)
 *  * aktivno = 1
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ValidniPodaciDajuAktivnoIznajmljivanje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, r.id);
    CPPTEST_ASSERT_INTEGER_EQUAL(5, r.id_automobila);
    CPPTEST_ASSERT_CSTR_EQUAL("Marko", r.ime);
    CPPTEST_ASSERT_CSTR_EQUAL("Markovic", r.prezime);
    CPPTEST_ASSERT_CSTR_EQUAL("01-01-2026", r.datum_pocetka);
    CPPTEST_ASSERT_CSTR_EQUAL("05-01-2026", r.datum_kraja);
    CPPTEST_ASSERT_INTEGER_EQUAL(4, r.broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(200.0f, r.ukupna_cijena, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, r.aktivno);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_ValidniPodaciDajuAktivnoIznajmljivanje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NevalidanBrojDanaVracaGresku */
/**
 * \tracehead{PripremiIznajmljivanje_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je broj dana jednak nuli (analiza granicnih vrijednosti - prva nevalidna vrijednost ispod opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "01-01-2026"
 *  * brojDana = 0
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_INVALID_DAYS.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NevalidanBrojDanaVracaGresku(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "01-01-2026", 0);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_DAYS, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NevalidanBrojDanaVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NevalidnaCijenaVracaGresku */
/**
 * \tracehead{PripremiIznajmljivanje_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je cijena po danu jednaka nuli (analiza granicnih vrijednosti - granica izmedju nevalidnih i validnih vrijednosti).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 0.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_INVALID_PRICE.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NevalidnaCijenaVracaGresku(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 0.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_PRICE, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NevalidnaCijenaVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NullIznajmljivanjeVracaNullPointer */
/**
 * \tracehead{PripremiIznajmljivanje_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar iznajmljivanje NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = NULL
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullIznajmljivanjeVracaNullPointer(void)
{
    RentStatus status = pripremiIznajmljivanje(NULL, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NullIznajmljivanjeVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NullImeVracaNullPointer */
/**
 * \tracehead{PripremiIznajmljivanje_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar ime NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = NULL
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullImeVracaNullPointer(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        NULL, "Markovic", "01-01-2026", "05-01-2026", 4);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NullImeVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NullPrezimeVracaNullPointer */
/**
 * \tracehead{PripremiIznajmljivanje_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar prezime NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = NULL
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullPrezimeVracaNullPointer(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", NULL, "01-01-2026", "05-01-2026", 4);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NullPrezimeVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NullDatumPocetkaVracaNullPointer */
/**
 * \tracehead{PripremiIznajmljivanje_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar datumPocetka NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = NULL
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullDatumPocetkaVracaNullPointer(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", NULL, "05-01-2026", 4);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NullDatumPocetkaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_NullDatumKrajaVracaNullPointer */
/**
 * \tracehead{PripremiIznajmljivanje_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je parametar datumKraja NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = NULL
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_NullDatumKrajaVracaNullPointer(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", NULL, 4);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_NullDatumKrajaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_DonjaGranicaBrojaDanaJeValidna */
/**
 * \tracehead{PripremiIznajmljivanje_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je broj dana jednak donjoj granici MIN_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "02-01-2026"
 *  * brojDana = MIN_BROJ_DANA (1)
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.broj_dana je jednaka 1.
 * 3. Vrijednost r.ukupna_cijena je jednaka 50.0 (1 * 50.0).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DonjaGranicaBrojaDanaJeValidna(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "02-01-2026", MIN_BROJ_DANA);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(MIN_BROJ_DANA, r.broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(50.0f, r.ukupna_cijena, 0.001);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_DonjaGranicaBrojaDanaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_GornjaGranicaBrojaDanaJeValidna */
/**
 * \tracehead{PripremiIznajmljivanje_TC_09, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada je broj dana jednak gornjoj granici MAX_BROJ_DANA (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "01-01-2027"
 *  * brojDana = MAX_BROJ_DANA (365)
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.broj_dana je jednaka 365.
 * 3. Vrijednost r.ukupna_cijena je jednaka 18250.0 (365 * 50.0).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_GornjaGranicaBrojaDanaJeValidna(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "01-01-2027", MAX_BROJ_DANA);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(MAX_BROJ_DANA, r.broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(18250.0f, r.ukupna_cijena, 0.001);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_GornjaGranicaBrojaDanaJeValidna */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_PrekoracenBrojDanaVracaGresku */
/**
 * \tracehead{PripremiIznajmljivanje_TC_10, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada broj dana prelazi gornju granicu (analiza granicnih vrijednosti - prva nevalidna vrijednost iznad opsega).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "02-01-2027"
 *  * brojDana = MAX_BROJ_DANA + 1 (366)
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_INVALID_DAYS.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrekoracenBrojDanaVracaGresku(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "02-01-2027", MAX_BROJ_DANA + 1);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_INVALID_DAYS, status);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_PrekoracenBrojDanaVracaGresku */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_ImeNaGraniciDuzineSeNeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_11, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada ime ima tacno DUZINA_IMENA - 1 (49) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (49 karaktera)
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.ime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (ime nije skraceno).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ImeNaGraniciDuzineSeNeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", "Markovic", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.ime);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_ImeNaGraniciDuzineSeNeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_ImePrekoGraniceDuzineSeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_12, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada ime ima DUZINA_IMENA (50) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (50 karaktera)
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.ime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_ImePrekoGraniceDuzineSeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "Markovic", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.ime);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_ImePrekoGraniceDuzineSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_PrezimeNaGraniciDuzineSeNeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_13, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada prezime ima tacno DUZINA_IMENA - 1 (49) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (49 karaktera)
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.prezime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (prezime nije skracen).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrezimeNaGraniciDuzineSeNeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.prezime);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_PrezimeNaGraniciDuzineSeNeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_PrezimePrekoGraniceDuzineSeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_14, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada prezime ima DUZINA_IMENA (50) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ" (50 karaktera)
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.prezime je jednaka "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_PrezimePrekoGraniceDuzineSeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHI", r.prezime);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_PrezimePrekoGraniceDuzineSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_DatumPocetkaNaGraniciDuzineSeNeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_15, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum pocetka ima tacno DUZINA_DATUMA - 1 (10) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026" (10 karaktera)
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_pocetka je jednaka "01-01-2026" (datum pocetka nije skracen).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumPocetkaNaGraniciDuzineSeNeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("01-01-2026", r.datum_pocetka);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_DatumPocetkaNaGraniciDuzineSeNeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_DatumPocetkaPrekoGraniceDuzineSeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_16, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum pocetka ima DUZINA_DATUMA (11) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-20260" (11 karaktera)
 *  * datumKraja = "05-01-2026"
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_pocetka je jednaka "01-01-2026" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumPocetkaPrekoGraniceDuzineSeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-20260", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("01-01-2026", r.datum_pocetka);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_DatumPocetkaPrekoGraniceDuzineSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_DatumKrajaNaGraniciDuzineSeNeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_17, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum kraja ima tacno DUZINA_DATUMA - 1 (10) karaktera, sto je najduzi string koji staje u polje bez skracivanja (analiza granicnih vrijednosti - na granici).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-2026" (10 karaktera)
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_kraja je jednaka "05-01-2026" (datum kraja nije skracen).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumKrajaNaGraniciDuzineSeNeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-2026", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("05-01-2026", r.datum_kraja);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_DatumKrajaNaGraniciDuzineSeNeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN PripremiIznajmljivanje_DatumKrajaPrekoGraniceDuzineSeSkracuje */
/**
 * \tracehead{PripremiIznajmljivanje_TC_18, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pripremiIznajmljivanje" u slucaju kada datum kraja ima DUZINA_DATUMA (11) karaktera, sto je najkraci string koji mora biti skracen (analiza granicnih vrijednosti - prva vrijednost iznad granice).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju pripremiIznajmljivanje sa sljedecim argumentima:
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 *  * id = 1
 *  * idAutomobila = 5
 *  * cijenaPoDanu = 50.0
 *  * ime = "Marko"
 *  * prezime = "Markovic"
 *  * datumPocetka = "01-01-2026"
 *  * datumKraja = "05-01-20260" (11 karaktera)
 *  * brojDana = 4
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pripremiIznajmljivanje vraca RENT_OK.
 * 2. Vrijednost r.datum_kraja je jednaka "05-01-2026" (posljednji karakter je odsjecen, string je ispravno zavrsen znakom '\0').
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PripremiIznajmljivanje_DatumKrajaPrekoGraniceDuzineSeSkracuje(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = pripremiIznajmljivanje(&r, 1, 5, 50.0f,
        "Marko", "Markovic", "01-01-2026", "05-01-20260", 4);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_CSTR_EQUAL("05-01-2026", r.datum_kraja);
}
/* CPPTEST_TEST_CASE_END PripremiIznajmljivanje_DatumKrajaPrekoGraniceDuzineSeSkracuje */

/* CPPTEST_TEST_CASE_BEGIN ObradiVracanjeAutomobila_VracanjeSaPronadjenimZapisom */
/**
 * \tracehead{ObradiVracanjeAutomobila_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je automobil iznajmljen i aktivan zapis o iznajmljivanju je pronadjen.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje sa aktivno = 1.
 * 3. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = adresa testnog automobila "a"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 4. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_OK.
 * 2. Vrijednost a.dostupan je jednaka 1 (automobil je ponovo dostupan).
 * 3. Vrijednost r.aktivno je jednaka 0 (iznajmljivanje je zavrseno).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_VracanjeSaPronadjenimZapisom(void)
{
    Automobil a = {0};
    Iznajmljivanje r = {0};
    a.dostupan = 0;
    r.aktivno = 1;

    RentStatus status = obradiVracanjeAutomobila(&a, &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, a.dostupan);
    CPPTEST_ASSERT_INTEGER_EQUAL(0, r.aktivno);
}
/* CPPTEST_TEST_CASE_END ObradiVracanjeAutomobila_VracanjeSaPronadjenimZapisom */

/* CPPTEST_TEST_CASE_BEGIN ObradiVracanjeAutomobila_VracanjeBezPronadjenogZapisa */
/**
 * \tracehead{ObradiVracanjeAutomobila_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je automobil iznajmljen, ali aktivan zapis o iznajmljivanju nije pronadjen.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 0.
 * 2. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = adresa testnog automobila "a"
 *  * iznajmljivanje = NULL
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_RENTAL_NOT_FOUND.
 * 2. Vrijednost a.dostupan je jednaka 1 (status automobila se ipak azurira).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_VracanjeBezPronadjenogZapisa(void)
{
    Automobil a = {0};
    a.dostupan = 0;

    RentStatus status = obradiVracanjeAutomobila(&a, NULL);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_RENTAL_NOT_FOUND, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, a.dostupan); /* status automobila se ipak azurira */
}
/* CPPTEST_TEST_CASE_END ObradiVracanjeAutomobila_VracanjeBezPronadjenogZapisa */

/* CPPTEST_TEST_CASE_BEGIN ObradiVracanjeAutomobila_AutomobilKojiVecNijeIznajmljen */
/**
 * \tracehead{ObradiVracanjeAutomobila_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je automobil vec dostupan (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil sa dostupan = 1.
 * 2. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = adresa testnog automobila "a"
 *  * iznajmljivanje = NULL
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_CAR_ALREADY_AVAILABLE.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_AutomobilKojiVecNijeIznajmljen(void)
{
    Automobil a = {0};
    a.dostupan = 1;

    RentStatus status = obradiVracanjeAutomobila(&a, NULL);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_CAR_ALREADY_AVAILABLE, status);
}
/* CPPTEST_TEST_CASE_END ObradiVracanjeAutomobila_AutomobilKojiVecNijeIznajmljen */

/* CPPTEST_TEST_CASE_BEGIN ObradiVracanjeAutomobila_NullAutomobilVracaNullPointer */
/**
 * \tracehead{ObradiVracanjeAutomobila_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "obradiVracanjeAutomobila" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje sa aktivno = 1.
 * 2. Pozvati funkciju obradiVracanjeAutomobila sa sljedecim argumentima:
 *  * automobil = NULL
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija obradiVracanjeAutomobila vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ObradiVracanjeAutomobila_NullAutomobilVracaNullPointer(void)
{
    Iznajmljivanje r = {0};
    r.aktivno = 1;
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, obradiVracanjeAutomobila(NULL, &r));
}
/* CPPTEST_TEST_CASE_END ObradiVracanjeAutomobila_NullAutomobilVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAktivnoIznajmljivanjeZaAuto_PronalaziAktivanZapis */
/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada niz sadrzi neaktivno i aktivno iznajmljivanje za isti automobil.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 0
 *  * niz[1]: id_automobila = 5, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca 1 (indeks aktivnog iznajmljivanja).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PronalaziAktivanZapis(void)
{
    Iznajmljivanje niz[2] = {0};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 0;
    niz[1].id_automobila = 5;
    niz[1].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, indeks);
}
/* CPPTEST_TEST_CASE_END PronadjiAktivnoIznajmljivanjeZaAuto_PronalaziAktivanZapis */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAktivnoIznajmljivanjeZaAuto_VracaMinusJedanAkoNemaAktivnog */
/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada ne postoji aktivno iznajmljivanje za dati automobil.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 0
 *  * niz[1]: id_automobila = 5, aktivno = 0
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca -1 (aktivno iznajmljivanje nije pronadjeno).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_VracaMinusJedanAkoNemaAktivnog(void)
{
    Iznajmljivanje niz[2] = {0};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 0;
    niz[1].id_automobila = 5;
    niz[1].aktivno = 0;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    CPPTEST_ASSERT_INTEGER_EQUAL(-1, indeks);
}
/* CPPTEST_TEST_CASE_END PronadjiAktivnoIznajmljivanjeZaAuto_VracaMinusJedanAkoNemaAktivnog */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAktivnoIznajmljivanjeZaAuto_NullNizVracaMinusJedan */
/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada je parametar niz NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = NULL
 *  * brojElemenata = 0
 *  * idAutomobila = 5
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca -1.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_NullNizVracaMinusJedan(void)
{
    CPPTEST_ASSERT_INTEGER_EQUAL(-1, pronadjiAktivnoIznajmljivanjeZaAuto(NULL, 0, 5));
}
/* CPPTEST_TEST_CASE_END PronadjiAktivnoIznajmljivanjeZaAuto_NullNizVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAktivnoIznajmljivanjeZaAuto_PreskaceAktivanZapisDrugogAutomobila */
/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada niz sadrzi aktivno iznajmljivanje za drugi automobil prije aktivnog iznajmljivanja za trazeni automobil.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 7, aktivno = 1
 *  * niz[1]: id_automobila = 5, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca 1 (aktivno iznajmljivanje drugog automobila se preskace).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PreskaceAktivanZapisDrugogAutomobila(void)
{
    Iznajmljivanje niz[2] = {0};
    niz[0].id_automobila = 7;
    niz[0].aktivno = 1;
    niz[1].id_automobila = 5;
    niz[1].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    CPPTEST_ASSERT_INTEGER_EQUAL(1, indeks);
}
/* CPPTEST_TEST_CASE_END PronadjiAktivnoIznajmljivanjeZaAuto_PreskaceAktivanZapisDrugogAutomobila */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAktivnoIznajmljivanjeZaAuto_PrazanNizVracaMinusJedan */
/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada je broj elemenata niza jednak nuli (analiza granicnih vrijednosti - prazan niz).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 1 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 0
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca -1 (niz se tretira kao prazan, iako niz[0] sadrzi aktivan zapis za trazeni automobil).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_PrazanNizVracaMinusJedan(void)
{
    Iznajmljivanje niz[1] = {0};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 0, 5);

    CPPTEST_ASSERT_INTEGER_EQUAL(-1, indeks);
}
/* CPPTEST_TEST_CASE_END PronadjiAktivnoIznajmljivanjeZaAuto_PrazanNizVracaMinusJedan */

/* CPPTEST_TEST_CASE_BEGIN PronadjiAktivnoIznajmljivanjeZaAuto_AktivanZapisNaPrvojPoziciji */
/**
 * \tracehead{PronadjiAktivnoIznajmljivanjeZaAuto_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "pronadjiAktivnoIznajmljivanjeZaAuto" u slucaju kada se aktivno iznajmljivanje nalazi na prvoj poziciji niza (analiza granicnih vrijednosti - najmanji moguci indeks rezultata).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni niz "niz" od 2 elementa tipa Iznajmljivanje sa sljedecim vrijednostima:
 *  * niz[0]: id_automobila = 5, aktivno = 1
 *  * niz[1]: id_automobila = 6, aktivno = 1
 * 2. Pozvati funkciju pronadjiAktivnoIznajmljivanjeZaAuto sa sljedecim argumentima:
 *  * niz = testni niz "niz"
 *  * brojElemenata = 2
 *  * idAutomobila = 5
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija pronadjiAktivnoIznajmljivanjeZaAuto vraca 0 (indeks prvog elementa).
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_PronadjiAktivnoIznajmljivanjeZaAuto_AktivanZapisNaPrvojPoziciji(void)
{
    Iznajmljivanje niz[2] = {0};
    niz[0].id_automobila = 5;
    niz[0].aktivno = 1;
    niz[1].id_automobila = 6;
    niz[1].aktivno = 1;

    int indeks = pronadjiAktivnoIznajmljivanjeZaAuto(niz, 2, 5);

    CPPTEST_ASSERT_INTEGER_EQUAL(0, indeks);
}
/* CPPTEST_TEST_CASE_END PronadjiAktivnoIznajmljivanjeZaAuto_AktivanZapisNaPrvojPoziciji */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_ValidnaLinijaSeParsiraUspjesno */
/**
 * \tracehead{ParsirajAutomobil_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada linija sadrzi svih 6 ocekivanih polja.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;45.50;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_OK.
 * 2. Struktura "a" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * marka = "Volkswagen"
 *  * model = "Golf"
 *  * godiste = 2020
 *  * cijena_po_danu = 45.50
 *  * dostupan = 1
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_ValidnaLinijaSeParsiraUspjesno(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;45.50;1\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, a.id);
    CPPTEST_ASSERT_CSTR_EQUAL("Volkswagen", a.marka);
    CPPTEST_ASSERT_CSTR_EQUAL("Golf", a.model);
    CPPTEST_ASSERT_INTEGER_EQUAL(2020, a.godiste);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(45.50f, a.cijena_po_danu, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, a.dostupan);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_ValidnaLinijaSeParsiraUspjesno */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NepotpunaLinijaVracaParseError */
/**
 * \tracehead{ParsirajAutomobil_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada linija ima manje polja od ocekivanog (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NepotpunaLinijaVracaParseError(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NepotpunaLinijaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_PraznaLinijaVracaParseError */
/**
 * \tracehead{ParsirajAutomobil_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada je linija prazna (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_PraznaLinijaVracaParseError(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_PraznaLinijaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NullLinijaVracaNullPointer */
/**
 * \tracehead{ParsirajAutomobil_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada je parametar linija NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = NULL
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NullLinijaVracaNullPointer(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil(NULL, &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NullLinijaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NullAutomobilVracaNullPointer */
/**
 * \tracehead{ParsirajAutomobil_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada je parametar automobil NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;45.50;1\n"
 *  * automobil = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NullAutomobilVracaNullPointer(void)
{
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;45.50;1\n", NULL);
    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NullAutomobilVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NenumerickoGodisteVracaParseError */
/**
 * \tracehead{ParsirajAutomobil_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (godiste) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;abcd;45.50;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickoGodisteVracaParseError(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;abcd;45.50;1\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NenumerickoGodisteVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NenumerickiIdVracaParseError */
/**
 * \tracehead{ParsirajAutomobil_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (id) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "abc;Volkswagen;Golf;2020;45.50;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickiIdVracaParseError(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("abc;Volkswagen;Golf;2020;45.50;1\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NenumerickiIdVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NenumerickaCijenaVracaParseError */
/**
 * \tracehead{ParsirajAutomobil_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (cijena po danu) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;abc;1\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickaCijenaVracaParseError(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;abc;1\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NenumerickaCijenaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajAutomobil_NenumerickoPoljeDostupanVracaParseError */
/**
 * \tracehead{ParsirajAutomobil_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajAutomobil" u slucaju kada numericko polje (dostupan) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testni automobil "a" tipa Automobil.
 * 2. Pozvati funkciju parsirajAutomobil sa sljedecim argumentima:
 *  * linija = "1;Volkswagen;Golf;2020;45.50;abc\n"
 *  * automobil = adresa testnog automobila "a"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajAutomobil vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajAutomobil_NenumerickoPoljeDostupanVracaParseError(void)
{
    Automobil a = {0};
    RentStatus status = parsirajAutomobil("1;Volkswagen;Golf;2020;45.50;abc\n", &a);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajAutomobil_NenumerickoPoljeDostupanVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_ValidnaLinijaSeParsiraUspjesno */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada linija sadrzi svih 9 ocekivanih polja.
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_OK.
 * 2. Struktura "r" je popunjena sljedecim vrijednostima:
 *  * id = 1
 *  * id_automobila = 3
 *  * ime = "Marina"
 *  * prezime = "Gogic"
 *  * broj_dana = 1
 *  * ukupna_cijena = 90.00
 *  * aktivno = 1
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_ValidnaLinijaSeParsiraUspjesno(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_OK, status);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, r.id);
    CPPTEST_ASSERT_INTEGER_EQUAL(3, r.id_automobila);
    CPPTEST_ASSERT_CSTR_EQUAL("Marina", r.ime);
    CPPTEST_ASSERT_CSTR_EQUAL("Gogic", r.prezime);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, r.broj_dana);
    CPPTEST_ASSERT_FLOAT_EQUAL_DELTA(90.00f, r.ukupna_cijena, 0.001);
    CPPTEST_ASSERT_INTEGER_EQUAL(1, r.aktivno);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_ValidnaLinijaSeParsiraUspjesno */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NepotpunaLinijaVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada linija ima manje polja od ocekivanog (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NepotpunaLinijaVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje("1;3;Marina\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NepotpunaLinijaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NullLinijaVracaNullPointer */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada je parametar linija NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = NULL
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NullLinijaVracaNullPointer(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje(NULL, &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NullLinijaVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NullIznajmljivanjeVracaNullPointer */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada je parametar iznajmljivanje NULL (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = NULL
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_NULL_POINTER.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NullIznajmljivanjeVracaNullPointer(void)
{
    RentStatus status = parsirajIznajmljivanje(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", NULL);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_NULL_POINTER, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NullIznajmljivanjeVracaNullPointer */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_PraznaLinijaVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_04, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada je linija prazna (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_PraznaLinijaVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje("\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_PraznaLinijaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NenumerickiBrojDanaVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_05, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (broj dana) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;abc;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiBrojDanaVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje(
        "1;3;Marina;Gogic;27-07-2026;28-07-2026;abc;90.00;1\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NenumerickiBrojDanaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NenumerickiIdVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_06, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (id) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "abc;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiIdVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje("abc;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NenumerickiIdVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NenumerickiIdAutomobilaVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_07, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (ID automobila) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;abc;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickiIdAutomobilaVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje("1;abc;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;1\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NenumerickiIdAutomobilaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NenumerickaUkupnaCijenaVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_08, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (ukupna cijena) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;abc;1\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickaUkupnaCijenaVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje("1;3;Marina;Gogic;27-07-2026;28-07-2026;1;abc;1\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NenumerickaUkupnaCijenaVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN ParsirajIznajmljivanje_NenumerickoPoljeAktivnoVracaParseError */
/**
 * \tracehead{ParsirajIznajmljivanje_TC_09, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "parsirajIznajmljivanje" u slucaju kada numericko polje (aktivno) sadrzi tekst umjesto broja (negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Definisati testno iznajmljivanje "r" tipa Iznajmljivanje.
 * 2. Pozvati funkciju parsirajIznajmljivanje sa sljedecim argumentima:
 *  * linija = "1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;abc\n"
 *  * iznajmljivanje = adresa testnog iznajmljivanja "r"
 * 3. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija parsirajIznajmljivanje vraca RENT_PARSE_ERROR.
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_ParsirajIznajmljivanje_NenumerickoPoljeAktivnoVracaParseError(void)
{
    Iznajmljivanje r = {0};
    RentStatus status = parsirajIznajmljivanje("1;3;Marina;Gogic;27-07-2026;28-07-2026;1;90.00;abc\n", &r);

    CPPTEST_ASSERT_INTEGER_EQUAL(RENT_PARSE_ERROR, status);
}
/* CPPTEST_TEST_CASE_END ParsirajIznajmljivanje_NenumerickoPoljeAktivnoVracaParseError */

/* CPPTEST_TEST_CASE_BEGIN OpisStatusa_PrvaGrupaStatusaVracaTacanOpis */
/**
 * \tracehead{OpisStatusa_TC_00, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" za prvu grupu RentStatus vrijednosti (pokrivenost naredbi - statement coverage grana switch iskaza).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa redom sa sljedecim argumentima:
 *  * status = RENT_OK
 *  * status = RENT_INVALID_YEAR
 *  * status = RENT_INVALID_PRICE
 *  * status = RENT_INVALID_DAYS
 *  * status = RENT_CAR_NOT_FOUND
 *  * status = RENT_CAR_NOT_AVAILABLE
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa za svaki status kod vraca tacno odgovarajuci opis:
 *  * RENT_OK: "Operacija je uspjesno izvrsena."
 *  * RENT_INVALID_YEAR: "Godiste nije u dozvoljenom opsegu (1950-2100)."
 *  * RENT_INVALID_PRICE: "Cijena po danu mora biti veca od nule."
 *  * RENT_INVALID_DAYS: "Broj dana mora biti u opsegu 1-365."
 *  * RENT_CAR_NOT_FOUND: "Automobil sa datim ID-om ne postoji."
 *  * RENT_CAR_NOT_AVAILABLE: "Automobil je trenutno iznajmljen."
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_PrvaGrupaStatusaVracaTacanOpis(void)
{
    CPPTEST_ASSERT_CSTR_EQUAL("Operacija je uspjesno izvrsena.", opisStatusa(RENT_OK));
    CPPTEST_ASSERT_CSTR_EQUAL("Godiste nije u dozvoljenom opsegu (1950-2100).", opisStatusa(RENT_INVALID_YEAR));
    CPPTEST_ASSERT_CSTR_EQUAL("Cijena po danu mora biti veca od nule.", opisStatusa(RENT_INVALID_PRICE));
    CPPTEST_ASSERT_CSTR_EQUAL("Broj dana mora biti u opsegu 1-365.", opisStatusa(RENT_INVALID_DAYS));
    CPPTEST_ASSERT_CSTR_EQUAL("Automobil sa datim ID-om ne postoji.", opisStatusa(RENT_CAR_NOT_FOUND));
    CPPTEST_ASSERT_CSTR_EQUAL("Automobil je trenutno iznajmljen.", opisStatusa(RENT_CAR_NOT_AVAILABLE));
}
/* CPPTEST_TEST_CASE_END OpisStatusa_PrvaGrupaStatusaVracaTacanOpis */

/* CPPTEST_TEST_CASE_BEGIN OpisStatusa_DrugaGrupaStatusaVracaTacanOpis */
/**
 * \tracehead{OpisStatusa_TC_01, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" za drugu grupu RentStatus vrijednosti (pokrivenost naredbi - statement coverage grana switch iskaza).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa redom sa sljedecim argumentima:
 *  * status = RENT_NULL_POINTER
 *  * status = RENT_CAR_ALREADY_AVAILABLE
 *  * status = RENT_RENTAL_NOT_FOUND
 *  * status = RENT_LIMIT_REACHED
 *  * status = RENT_PARSE_ERROR
 *  * status = RENT_FILE_ERROR
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa za svaki status kod vraca tacno odgovarajuci opis:
 *  * RENT_NULL_POINTER: "GRESKA: Nevalidan (null) pokazivac."
 *  * RENT_CAR_ALREADY_AVAILABLE: "Ovaj automobil trenutno nije iznajmljen."
 *  * RENT_RENTAL_NOT_FOUND: "Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil."
 *  * RENT_LIMIT_REACHED: "Dostignut je maksimalan dozvoljeni broj zapisa."
 *  * RENT_PARSE_ERROR: "Greska pri parsiranju linije iz fajla."
 *  * RENT_FILE_ERROR: "Greska pri radu sa fajlom."
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_DrugaGrupaStatusaVracaTacanOpis(void)
{
    CPPTEST_ASSERT_CSTR_EQUAL("GRESKA: Nevalidan (null) pokazivac.", opisStatusa(RENT_NULL_POINTER));
    CPPTEST_ASSERT_CSTR_EQUAL("Ovaj automobil trenutno nije iznajmljen.", opisStatusa(RENT_CAR_ALREADY_AVAILABLE));
    CPPTEST_ASSERT_CSTR_EQUAL("Nije pronadjen aktivan zapis iznajmljivanja za ovaj automobil.", opisStatusa(RENT_RENTAL_NOT_FOUND));
    CPPTEST_ASSERT_CSTR_EQUAL("Dostignut je maksimalan dozvoljeni broj zapisa.", opisStatusa(RENT_LIMIT_REACHED));
    CPPTEST_ASSERT_CSTR_EQUAL("Greska pri parsiranju linije iz fajla.", opisStatusa(RENT_PARSE_ERROR));
    CPPTEST_ASSERT_CSTR_EQUAL("Greska pri radu sa fajlom.", opisStatusa(RENT_FILE_ERROR));
}
/* CPPTEST_TEST_CASE_END OpisStatusa_DrugaGrupaStatusaVracaTacanOpis */

/* CPPTEST_TEST_CASE_BEGIN OpisStatusa_InvalidIdVracaTacanOpis */
/**
 * \tracehead{OpisStatusa_TC_02, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" u slucaju kada je status jednak RENT_INVALID_ID (pokrivenost naredbi - statement coverage grana switch iskaza).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa sa sljedecim argumentom:
 *  * status = RENT_INVALID_ID
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa vraca tacno opis "Nevalidan ID.".
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_InvalidIdVracaTacanOpis(void)
{
    CPPTEST_ASSERT_CSTR_EQUAL("Nevalidan ID.", opisStatusa(RENT_INVALID_ID));
}
/* CPPTEST_TEST_CASE_END OpisStatusa_InvalidIdVracaTacanOpis */

/* CPPTEST_TEST_CASE_BEGIN OpisStatusa_NepoznatStatusVracaDefaultOpis */
/**
 * \tracehead{OpisStatusa_TC_03, Funkcionalni test}
 * Test provjerava ispravno ponasanje funkcije "opisStatusa" u slucaju kada status nije definisana RentStatus vrijednost (pokrivenost grana - branch coverage default grane, negativan test).
 *
 * \field{Specifikacija testa}
 * 1. Pozvati funkciju opisStatusa sa sljedecim argumentom:
 *  * status = (RentStatus) 999
 * 2. Provjeriti ocekivane rezultate.
 * \endfield
 *
 * \field{Ocekivani rezultati}
 * Ocekivani rezultat je Passed
 * 1. Funkcija opisStatusa vraca string "Nepoznat status.".
 * \endfield
 */
void TestSuite_rent_a_car_logic_gtest_OpisStatusa_NepoznatStatusVracaDefaultOpis(void)
{
    CPPTEST_ASSERT_CSTR_EQUAL("Nepoznat status.", opisStatusa((RentStatus)999));
}
/* CPPTEST_TEST_CASE_END OpisStatusa_NepoznatStatusVracaDefaultOpis */
