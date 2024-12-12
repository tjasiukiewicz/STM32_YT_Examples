Pierwsze podejście do separacji projektu. 
1. Zamiana nazwy plików main.c oraz main.h na main.cpp oraz main.hpp.
2. CubeIDE uparcie generuje pliki main.c i main.h, w związku z tym, wyłączamy 
je z projektu (pamiętać należy o wykonaniu konfiguracji dla wszystkich celów)
3. Zmieniamy włączanie nagłówka main.h w pliku main.cpp na main.hpp

Niestety projekt jest wrażliwy na przełączenie generatora kodu w tryb
niezależnych modułów w C:
(Project Manager -> Code Generator -> Generate peripheral initialization as a pair ... )
Powstające zależności, bardzo utrudniają wydzielenie do jednego pliku oraz
wymagają kopiowania do pliku main.cpp.
Brak włączenia generatora wielu plików peryferiów, i tak wymaga kopiowania 
ew. zmieniającego się pliku main.c i main.hpp.

Zalety:
- Proste do wykonania
- Proste do zrozumienia

Wady:
- Wymaga kopiowania nowo generowanych części kodu z main.c/h do main.cpp/hpp
- W praktyce uniemożliwia uruchomienie generowania oddzielnych modułów *.c/*.h