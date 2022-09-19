# jednoreki-bandyta
Jednoręki bandyta - RTS 95, HF 30

"Gra" jednoręki bandyta losuje domyślnie 100 tysięcy wierszy na pięciu bębnach spośród ośmiu cyfr.

Domyślną stawką jest wartość 100.

Domyślny kredyt to 500 tysięcy.

Wszystkie losowania i zmieniającą się wartość kredytu można zapisać do pliku używając opcji _-plik_

Stosunek zwrotu jest na poziomie 95%.

Częstotliwość trafień jest na poziomie 30%.



**Kompilacja:**

_gcc jb.c -o jb_

**Uruchomienie:**

_./jb_

lub

_./jb -gier 100000 -kredyt 500000 -plik plik.txt_


