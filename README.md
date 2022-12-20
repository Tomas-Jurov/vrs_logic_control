# Dji Tello - Logic control


![Dron](https://i.ytimg.com/vi/nZ1o8TMZymE/maxresdefault.jpg)


# Obsah

- [Úvod](#Úvod)
- [Náhlad](#Náhlad)
- [Komunikácia](#Komunikácia)
- [Funkcionalita](#Funkcionalita)
- [Vrs-connector-reppo](#Vrs-connector-reppo)
- [Prvotné_nastavenie](#Prvotné_nastavenie)
- [Ovládanie](#Ovládanie)


# Úvod

![Urk](https://scontent.fbts10-1.fna.fbcdn.net/v/t39.30808-6/306322762_499480958850983_2907576443193663122_n.png?_nc_cat=107&ccb=1-7&_nc_sid=09cbfe&_nc_ohc=NORjCJxOTYQAX-SmdjF&_nc_ht=scontent.fbts10-1.fna&oh=00_AfA6CxFE6rTwqjAkPdStfiKP1iWnQ1qeSIIGtprEQyf9XQ&oe=63A62F8E)

Tento repozitár vznikol ako semestrálne zadanie Slovenskej Technickej univerzity z predmetu VRS.

V nasledujúcom článku sa bližšie pozrieme na riadenie drona Dji Tello zapomoci mikrokontrolera programovaného v stm32, s niekolkými zaujímavími funkciami. 


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

*  Zapnuté - Dron je v manuálnom riadení ovládaní zapomoci operátora
*  Vypnuté - Dron je v rukách umelej inteligencie, ktorá je vytrénovaná lietať za ludskou tvárou


## Komunikácia

Komunikácia prebieha medzi počítačom a mikrokontrolkerom za pomoci UARTu.


# Funkcionalita

Použite funkcie


# Vrs-connector-reppo

Používame ešte jeden [repozitár](https://github.com/Tomas-Jurov/vrs-connector), ktorý slúži na prepojenie medzi stm32 a dronom. Je tvorený dvoma threadmi :

1.  Získava a posiela spatnú vezbu do stm32 ohladom dronu. Inými slovami riadi celé STMko.
2.  Streamuje obraz kameri na web, a zároven je v ňom implementované riadenie pomocou neurónovej siete.

Technológie použité v tomto repozitáry:
* Flask             - je v ňom písaný backend
* PySerial          - UART komunikácia medzi počítačom a notebookom
* UDP-protokol      - (knižnica DJITelloPy) ovládanie drona
* Mediapipe         - neurónova sieť vytrénovaná pre nasledovanie tváre

Kompletná dokumentácia na rozbehnutie tohto reppa sa nachádza [tu](https://github.com/Tomas-Jurov/vrs-connector/blob/main/requirements.txt).


# Prvotné_nastavenie

1. Naklonovanie tohto repozitáru do svojho počítača
2. Následne uploadovať na stm32
3. Spustenie commandu `pip install -r requirements.txt`, (nainštaluje potrebné dependencie)
4. Pustenie aplikácie - flaskApp.py


# Ovládanie

![Džoistik](https://media.icdn.hu/product/GalleryMod/2021-05/701455/resp/1649584_dji_tello_dron__gamesir_t1d_kontroller_csomag.webp)

Po tom ako sme si prvotne nastavili náš projekt, sa môžeme pustit do ovládania:

*  Páčky k sebe(k telu) - vzlietnutie
*  Následne treba dať páčky naspet do neutrálnej pozícií - ustálenie
*  Následne pomocou páčiek je možné intuitívne riadenie - dron bude lietať ako mu povieme
*  Podržanie lavého džoistika do dola(pár sekúnd) - pristátie
*  Stlačenie tlačidla - prepnutie medzi manuálnym a automatickým riadením