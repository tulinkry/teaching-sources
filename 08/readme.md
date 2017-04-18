# Polymorfismus a dědičnost

Program demonstrující práci s dědičností tříd.

## virus.cpp

Program obsahuje dvě hlavní třídy - člověka a virus. Třída CPerson si drží informaci o virech, kterými se daný člověk nakazil, jméno člověka, věk a hodnotu zdraví.
Každý virus má nějaké jméno a může ovlivnit člověka pomocí metody `progress ( CPerson & person )`, kde libovolně může upravovat hodnotu zdraví člověka.

Život člověka je symbolizován smyčkou v hlavním programu, kde v každém cyklu člověk zestárne o 1 rok a aplikují se na něj všechny viry, které stihl pochytat.

Z příkladu je nutné si odnést několik důležitých poznatků:
 - pro správnou funkci jsou potřeba ukazatele nebo reference (`CVirus *`, `CVirus &`, `const CVirus *`, `CVirus *const`, `const CVirus &`)
   - jak ve vnitřním kontejneru (vector)
   - tak i v parametrech dalších funkcí
 - jediný, kdo zná konkrétní typ dané instance, je ta daná instance
   - využítí polymorfismu při přepisu metod
   - logiku přesunout do metod konkrétních implementací podtříd
 - pokud bychom potřebovali znát pro další krok algoritmu konkrétní typ dané instance a pracně bychom ho zjišťovali pomocí triků např. s typeid, **dochází k porušení celého návrhu** a dědění je zbytečné