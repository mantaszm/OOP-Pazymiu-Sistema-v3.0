# Vector vs std::vector spartos ir atminties perskirstymo analizė

## Tikslas

Šioje dalyje buvo palyginta mano sukurta `Vector` klasė su `std::vector`, įvertinant:

- `push_back()` vykdymo laiką
- atminties perskirstymų skaičių
- bendrą elgesio panašumą

---

## Testavimo metodas

Buvo matuojama, kiek laiko užtrunka užpildyti konteinerius naudojant `push_back()` funkciją.

Testuoti dydžiai:
- 10 000
- 100 000
- 1 000 000
- 10 000 000
- 100 000 000

Kiekvienam dydžiui palyginti:
- `std::vector`
- `Vector`

Taip pat skaičiuoti atminties perskirstymai.

---

## Rezultatai (push_back)

SIZE = 10000  
std::vector: 9.2e-05 s  
Vector: 6.3e-05 s  

SIZE = 100000  
std::vector: 0.00066 s  
Vector: 0.00056 s  

SIZE = 1000000  
std::vector: 0.003499 s  
Vector: 0.003694 s  

SIZE = 10000000  
std::vector: 0.035827 s  
Vector: 0.03508 s  

SIZE = 100000000  
std::vector: 0.270734 s  
Vector: 0.316023 s  

---

## Atminties perskirstymai

std::vector reallocations: 28  
Vector reallocations: 28  

---

## Analizė

Abi implementacijos naudoja panašią `capacity` didinimo strategiją (apie 2x didinimą), todėl:

- perskirstymų skaičius yra identiškas
- augimas vyksta logaritmiškai

Tai rodo, kad `Vector` elgiasi labai panašiai kaip `std::vector` atminties valdymo prasme.

---

## Išvada

- `Vector` ir `std::vector` turi beveik identišką `push_back` spartą
- mažiems ir vidutiniams dydžiams skirtumai minimalūs
- dideliems dydžiams `std::vector` turi nedidelį pranašumą
- perskirstymų skaičius identiškas (28)

Bendra išvada: sukurta `Vector` klasė yra artima `std::vector` realizacijai tiek funkcionalumo, tiek našumo prasme.
