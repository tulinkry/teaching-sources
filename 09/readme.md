# Výjimky a jejich zpracování

Program demonstrující práci výjimkami.

## main.cpp

Základní práce s výjimkami
1. Propagace skrz graf volajících funkcí
2. Zachytávání pomocí klauzule `catch`
3. Správná práce s pamětí při zpracování výjimek
4. Výhodnější než návratové kódy z C
5. Dědičnost s typem `std::exception`

Obecně je vhodné
 - nezachytávat výjimky, které neumím zpracovat

## file.cpp

Program demonstrující práci s výjimkami v c++. Program obsahuje třídu CFile, která realizuje soubor. Parametrem konstruktoru je cesta k danému souboru.
Hlavní metodou je metoda `GetFile`, která vrátí celý obsah souboru jako `std::string`. Chyby jsou signalizovány výjimkami, za chybu je považováno:
 - jméno souboru je `NULL` ukazatel
 - soubor neexistuje
 - soubor je nečitelný