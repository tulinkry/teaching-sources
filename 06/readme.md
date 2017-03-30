# Šablony tříd

Program demonstrující práci se šablonami.

## cargo.cpp

CCargo - třída symbolizující náklad o nějaké hmotnosti v tunách, ke které
je přiřazen způsob dopravy - cena na tunokilometr.

Třída disponuje metodou `transfer(src, dest, km)`, která přesune zboží ze skladu `src`
do skladu `dest` a vrátí cenu za tento transfer. Cena je určena jako `váha zboží * počet km * cena na km`.

1. Implementace, kde typ dopravy je celé číslo symbolizující cenu na tunokilometr
2. Implementace šablonou, kde typ dopravy je generický parametr šablony
3. Implementace dalších typů, které lze použít jako parametr šablony CCargo