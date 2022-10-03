# Jednoręki bandyta
Jednoręki bandyta - RTP 95, HF 30

"Gra" jednoręki bandyta losuje domyślnie 100 tysięcy wierszy na pięciu bębnach spośród ośmiu cyfr.

Stawka wynosi 100, kredyt 500 tysięcy


Wszystkie losowania i zmieniającą się wartość kredytu można zapisać do pliku używając opcji `-plik`

Stosunek zwrotu jest na poziomie 95%.

Częstotliwość trafień wynosi 30%.



**Kompilacja:**

`gcc jb.c -o jb`

**Uruchomienie:**

`./jb`

lub

`./jb -gier 100000 -kredyt 500000 -plik plik.txt`

![alt text](https://github.com/ato-zen/jednoreki-bandyta/blob/main/zrzut-ekranu.png?raw=true)
