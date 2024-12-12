Projekt:

Prosty projekt dla platformy NUCLEO-G474RE, prezentujący pracę portu szeregowego
oraz diody led.

Założenia:
1. Podstawa do prezentacji konfiguracji w trybie C++.
   Celowo wprowadzone przekazanie parametrów, by w przyszłości przenieść
   je do argumentów szablonowych.
2. Działanie programu w pamięci RAM (prostota, brak "wypalania flash")
3. Niewrażliwość na konfigurację CubeMX wbudowanego w STM32CubeIDE.
   Możliwe przełączenie peryferium z trybu HAL <-> LL.
   Możliwe wydzielenie kodu peryferiów do oddzielnych plików *.c/*.h
   Możliwa publikacja/prywatność użytych funkcji.
4. Ze względu na prostotę, brak wydzielonych plików projektu dla funkcji
   obsługujących LPUART i GPIO.