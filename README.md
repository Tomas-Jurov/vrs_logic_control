# Dji Tello - Logic control

![Dron](https://i.ytimg.com/vi/nZ1o8TMZymE/maxresdefault.jpg)

# Obsah

- [Úvod](#Úvod)
- [Náhlad](#Náhlad)
- [Komunikácia](#Komunikácia)
- [Funkcionalita](#Funkcionalita)

# Úvod

![Urk](http://malylubo.sk/wp-content/uploads/2012/11/logo.png)

Tento repozitár vznikol ako semestrálne zadanie Slovenskej Technickej univerzity z predmetu VRS.

V nasledujúcom článku sa bližšie pozrieme na riadenie drona Dji Tello zapomoci mikrokontrolera programovaného v STM, s niekolkými zaujímavími funkciami. 


# Náhlad

Víziou projektu je mať spustený nekonečný ciklus nahraný v mikrokontroleri, ktorý neustále posiela príkazy aklo riadiť drona.

Použité funkcie:

* command               - Vstupný režim SDK
* takeoff               - Tello automatický vzlet
* land                  - Tello utomatické pristátie
* streamon/streamoff    - Zapnutie/Vypnutie streamovania videa

Kompletnú dokumentáciu príkazov nájdeme [tu](https://terra-1-g.djicdn.com/2d4dce68897a46b19fc717f3576b7c6a/Tello%20编程相关/For%20Tello/Tello%20SDK%20Documentation%20EN_1.3_1122.pdf).

# Komunikácia

Komunikuje to UARTom

# Funkcionalita

Použite funkcie