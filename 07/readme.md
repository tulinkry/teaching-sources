# STL

Program demonstrující práci se s částmi knihovny STL.

## shopping.cpp

Cílem programu je v seznamu zboží v regálech v souboru `regals.txt`, které jsou napsané tak, jak jdou za sebou v supermarketu, najít nejlepší možný
průchod supermarketem vzhledem k seznamu zboží k nákupu v `list.txt`.

## Lambda funkce

Anonymní funkce

```c++
[] // (1) capture list
( int a, const vector<string> & b ) // (2) parametry
{
	// (3) tělo funkce
	// ...
}
```

1. Capture list slouží k zachytnutí proměnných v aktuálním kontextu (v kontextu, kde lambda funkce vzniká). Tyto proměnné lze následně použít v těle lambda funkce.
   Proměnné lze předat dvěma způsoby:
   1. Hodnotou (pouze jméno proměnné)
      Proměnnou pak **nelze** v lambda výrazu měnit
      ```c++
      int counter;
      vector<int> x;
      [counter, x] () {}
      ```
   2. Referencí (& + jméno proměnné)
      Proměnnou **lze** v těle lambda výrazu libovolně měnit (či volat metody bez `const` kvantifikátoru)
      ```c++
      int counter;
      vector<int> x;
      [&counter, &x] () {}
      ```

   Lze také využít zkratky pro zachytnutí všech proměnných aktuálního kontextu:
    - `[*]` hodnotou
    - `[&]` referencí
   
   Nebo lze zachytnout ukazatel `this` pro použití třídních proměnných či metod:
   - `[this]` pouze hodnotou

2. Parametry mají stejný význam jako deklarace parametrů u normální funkce.
3. Tělo funkce obsahuje stejné výrazy jako u normální funkce a navíc může libovolně používat proměnné zachycené v capture listu.

## Funktory

Objekt (třída nebo struktura), která se tváří, že ho lze volat jako funkci - přetěžuje operátor volání funkce.

```c++
class lambda
{
	private:
		// zachytnutí kontextu - reference je nutná, aby se změna promítla do volajícího
		// případne lze použít ukazatel
		map<string, int> & m_listOfOrders;
	public:
		// vytvoření objektu s nastavením vnitřích proměnných - kontextu v místě, kde objekt vzniká
		lambda ( map<string, int> & listOfOrders ) : m_listOfOrders ( listOfOrders )
		{}
		// přětížení operátor volání obsahuje samotnou logiku funktoru
		void operator() ( int a, const vector<string> & b )
		{
			// tělo funkce
			// ...
			m_listOfOrders["order 1"] = a;
		}
};
```

Kompilátor z lambda výrazů generuje funktory se správným zachováním aktuálního kontextu přes konstruktor - lambda výraz je tedy pouhá syntaktická zkratka k funktoru.
