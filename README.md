# Dji Tello - Logic control

![Dron](https://i.ytimg.com/vi/nZ1o8TMZymE/maxresdefault.jpg)

# Obsah

- [Úvod](#Úvod)
- [Náhlad](#Náhlad)
- [Komunikácia](#Komunikácia)
- [Funkcionalita](#Funkcionalita)

# Úvod

![Urk](https://scontent.fbts10-1.fna.fbcdn.net/v/t39.30808-6/306322762_499480958850983_2907576443193663122_n.png?_nc_cat=107&ccb=1-7&_nc_sid=09cbfe&_nc_ohc=NORjCJxOTYQAX-SmdjF&_nc_ht=scontent.fbts10-1.fna&oh=00_AfA6CxFE6rTwqjAkPdStfiKP1iWnQ1qeSIIGtprEQyf9XQ&oe=63A62F8E)

Tento repozitár vznikol ako semestrálne zadanie Slovenskej Technickej univerzity z predmetu VRS.

V nasledujúcom článku sa bližšie pozrieme na riadenie drona Dji Tello zapomoci mikrokontrolera programovaného v STM, s niekolkými zaujímavími funkciami. 


# Náhlad

Víziou projektu je mať spustený nekonečný ciklus nahraný v mikrokontroleri, ktorý neustále posiela príkazy aklo riadiť drona.

Použité funkcie(HAL knižnica):

* command               - Vstupný režim SDK
* takeoff               - Tello automatický vzlet
* land                  - Tello utomatické pristátie
* streamon/streamoff    - Zapnutie/Vypnutie streamovania videa

Kompletnú dokumentáciu príkazov nájdeme [tu](https://terra-1-g.djicdn.com/2d4dce68897a46b19fc717f3576b7c6a/Tello%20编程相关/For%20Tello/Tello%20SDK%20Documentation%20EN_1.3_1122.pdf).

Nasledujúcou vymoženosťou je možnosť prepnúť si ovládanie dorna za pomoci tlačidla.
Tlačidlo je buď zapnuté alebo vypnuté:

1.  Zapnuté - Dron je v manuálnom riadení ovládaní zapomoci operátora
2.  Vypnuté - Dron je v rukách umelej inteligencie, ktorá je vytrénovaná prenasledovať, tým pádom lietať, za ludskou tvárou

# Komunikácia

Komunikácia prebieha medzi počítačom a mikrokontrolkerom za pomoci UARTu.

# Funkcionalita

Použite funkcie