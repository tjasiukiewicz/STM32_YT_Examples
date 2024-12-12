Drugie podejście do separacji projektu.
1. Pozostawiamy pliki main.c i main.h w stanie pierwotnym.
2. Dodajemy nowe pliki entry.hpp oraz entry.cpp.
3. Definiujemy funkcję void entry(void), osłaniając ją dyrektywą extern "C"
4. W pliku main.c, dodajemy włączenie nagłówka entry.hpp oraz wywołanie 
   funkcji entry() w ramach main(). Pętla while(1), przesunięta do entry().
5. W pliku entry.cpp, dodajemy włączenie nagłówka main.h w celu dostępu do 
   definicji peryferiów.
   
Projekt dalej wrażliwy na uruchomienie generatora kodu w tryb niezależnych 
modułów w C. Powstające zależności, pojawiają się jednak w pliku main.c, 
w postaci włączeń nagłówków. W przypadku takiej rekonfiguracji, należy
ponownie włączać je manualnie w pliku entry.cpp.

Zalety:
- Lepsza separacja kodu C++ od C
- Jeden definiowany punkt wejścia
- Działające dalej mechanizmy C (np. at_exit()...)
- Mniejsze sprzężenie w przypadku generowania oddzielnych modułów *.c/*.h

Wady:
- Ciągle nie rozwiązany w pełni problem wrażliwości na generowanie oddzielnych
  modułów przez generator kodu
- Konieczność kopiowania włączeń do pliku entry.cpp w przypadku zmian powodowanych
  generatorem kodu pracującym w trybie oddzielnych modułów
  
 