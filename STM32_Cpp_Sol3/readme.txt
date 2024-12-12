Trzecie podejście do separacji projektu.
1. Wyłączamy generowanie funkcji main() w geneatorze kodu
(Project Manager -> Project -> Do not generate the main() )
2. Poprawiamy sygnaturę funkcji w entry.hpp/cpp, na int main(void). Dalej
   powinna być otoczona dyrektywą extern "C", bo jest wywoływana w kodzie
   startowym (z poziomu asemblera), jeszcze w trybie pracy języka C
3. Do kodu w entry.cpp, dodajemy włączenie nagłówka main.h w celu dostępu do
   definicji peryferiów.
4. W kodzie funkcji main() w pliku entry.cpp, dodajemy wywołania inicjujące
   peryferia platformy.
5. W pliku entry.cpp, dodajemy deklaracje funkcji inicjujących peryferia
   platformy. Powinny one być obecne dalej w sekcji objętej dyrektywą 
   extern "C" bo są definiowane w języku C.
6. Wyłączamy ukrycie widocznosci funkcji jako static w 
   (Project Manager -> Advanced Settings -> Visibility (Static) ) 
   dla wszystkich funkcji. Powinne być one dostępne z poziomu C++
7. Dodajemy dyrektywę wywołania HAL_Init(), tylko w przypadku konfiguracji 
   w trybie HAL, a nie LL

Projekt buduje się  i działa w każdym trybie ingerencji generatora kodu.
Tak w przypadku generowania do modułów *.h/*.c, jak i wariantowemu generowaniu
kodu obsługi urządzeń w trybie biblioteki Low Level.

Zalety:
- Pełna separacja kodu C++ od C
- Naturalny punkt wejścia do kodu (main())
- Działające mechanizmy z języka C
- Możliwość generowania kodu LL i/lub HAL
- Brak sprzężenia w związku z generowaniem modułów w *.c/*.h

Wady:
- Niewątpliwie złożona konfiguracja od poziomu domyślnego projektu C++ w
  CubeIDE
- Konieczność dodawania wywołania inicjalizacji/obsługi peryferium w pliku
  entry.cpp, w przypadku dodania obsługi w generatorze kodu 