# Dji Tello - Logic control

![Dron](https://i.ytimg.com/vi/nZ1o8TMZymE/maxresdefault.jpg)

# Obsah

- [Úvod](#Úvod)
- [Náhlad](#Náhlad)
- [Komunikácia](#Komunikácia)
- [Funkcionalita](#Funkcionalita)

# Úvod

V nasledujúcom článku sa bližšie pozrieme na riadenie drona Dji Tello zapomoci mikrokontrolera programovaného v STM, s niekolkými zaujímavími funkciami. 

Tento repozitár vznikol ako semestrálne zadanie Slovenskej Technickej univerzity z predmetu VRS.

# Náhlad

Víziou projektu je mať spustený nekonečný ciklus nahraný v mikrokontroleri, ktorý neustále posiela príkazy aklo riadiť drona.

Použité príkazy:

* 110 - vyfajci mi kokot

Kompletnú dokumentáciu príkazov nájdeme [tu](https://terra-1-g.djicdn.com/2d4dce68897a46b19fc717f3576b7c6a/Tello%20编程相关/For%20Tello/Tello%20SDK%20Documentation%20EN_1.3_1122.pdf)

# Komunikácia

Komunikuje to UARTom

# Funkcionalita

Použite funkcie