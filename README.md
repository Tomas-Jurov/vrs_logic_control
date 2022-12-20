# Dji Tello - Logic control


![Dron](https://i.ytimg.com/vi/nZ1o8TMZymE/maxresdefault.jpg)


# Obsah

- [Úvod](#Úvod)
- [Náhľad](#Náhľad)
- [Komunikácia](#Komunikácia)
- [Funkcionalita](#Funkcionalita)
- [Vrs-connector-repo](#Vrs-connector-repo)
- [Setup](#Setup)
- [Ovládanie](#Ovládanie)


# Úvod

<p align="center">
    <img width="200" src="https://scontent.fbts10-1.fna.fbcdn.net/v/t39.30808-6/306322762_499480958850983_2907576443193663122_n.png?_nc_cat=107&ccb=1-7&_nc_sid=09cbfe&_nc_ohc=NORjCJxOTYQAX-SmdjF&_nc_ht=scontent.fbts10-1.fna&oh=00_AfA6CxFE6rTwqjAkPdStfiKP1iWnQ1qeSIIGtprEQyf9XQ&oe=63A62F8E" alt="Material Bread logo">
</p>

Tento repozitár vznikol ako semestrálne zadanie Slovenskej Technickej univerzity z predmetu VRS.

Cieľom semestrálneho zadania bolo ovládať drona pomocou joystickov za pomoci mikrokontroléra STM32F303K8T6 


# Náhľad

Mikrokontrolér STM32 slúži na získavanie natočení joysticku a na základe naprogramovanej logiky posiela connectoru (čo je v preklade bridge medzi mikrokontrolérom a dronom) príkazy na ovládanie dronu.

Kód je napísaný za pomoci knižnice HAL a kód je kompilovaný pomocou autovygenerovaného Makefilu na základe .ioc súbora

Využivané periféria sú 2 joysticky, ľavý joystick slúži na throttle a yaw, pravý na roll, pitch
Pridávne periférium je mechanické tlačidlo, ktoré slúži na prepínanie automatického/manuálneho módu

Funkcie používané zo SDK drona DJI Tello
* command               - Slúži na nadviazanie komunikácie s dronom
* takeoff               - Automatické vzlietnutie
* land                  - Atomatické pristátie
* streamon/streamoff    - Zapnutie/Vypnutie stream-u

Kompletnú dokumentáciu príkazov nájdeme [tu](https://terra-1-g.djicdn.com/2d4dce68897a46b19fc717f3576b7c6a/Tello%20编程相关/For%20Tello/Tello%20SDK%20Documentation%20EN_1.3_1122.pdf).


## Komunikácia

Komunikácia prebieha za pomoci middle mana, čo je v našom prípade počítač(repo connector), pomocou UART a následne za pomoci SDK a UDP protokolu s dronom DJI Tello


# Funkcionalita

Použite funkcie


# Vrs-connector-repo

Repozitár connector [repozitár](https://github.com/Tomas-Jurov/vrs-connector) slúži na komunikáciu s dronom pomocou UDP protokolu a zároveň publishuje získane video na vlastnú webovú stránku

1.  Pre ošetrenie nedovoleného správania sa posiela z drona spätná väzba a na základe nej logic controller vyhodnotí, či danú sadu príkazov môže požadovať
2.  Stream publishovaný na vlastnú webovú stránku obsahuje face recognition, ktorý sa dá použiť na automatický mód drona, do ktorého sa dostaneme pomocou stlačenia mechanického tlačidla

Technológie použité v tomto repozitáry:
* Flask             - Backend framework
* PySerial          - UART protocol handler
* DJI TelloPy       - UDP protocol + safty features
* Mediapipe         - CNN od spoločnosti google
* OpenCV            - Spracovanie obrazu


# Setup

1. Stiahnutie otagovaných release verzií connectora a logic controllera
2. Otvoriť logic controller v STM32 CubeIDE a nahratie projektu do čipu AMR Cortex M4
3. Správne pozapájať všetky potrebné periféria obrázok sa nachádza na konci README
4. Otvoriť connector + vytvorenie venv a následne stiahnutie všetkých potrebných dependencií pomocou `pip install -r requirements.txt`
5. Spustenie aplikácie, main sa nachádza v súbore - flaskApp.py


# Ovládanie

*  Páčky k sebe(k telu) - vzlietnutie
*  Následne treba vrátiť páčky do neutrálnej pozície
*  Ľavý joystick slúži na throttle a yaw natočenie
*  Pravý joystick roll a pitch
*  Držanie throttlu smerom dolu po dobu 1 sekundy - pristatie
*  Stlačenie tlačidla - prepínanie medzi manuálnym a automatickým módom

![Joystick](https://media.icdn.hu/product/GalleryMod/2021-05/701455/resp/1649584_dji_tello_dron__gamesir_t1d_kontroller_csomag.webp)