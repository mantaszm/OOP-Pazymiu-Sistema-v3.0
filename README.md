# OOP Pazymiu Sistema v1.5 + My Vector realizacija

## Projekto aprašymas

Ši programa yra studentų pažymių valdymo sistema, kurioje realizuota:
- std::vector konteineris
- custom Vector (My Vector)
- jų palyginimas pagal:
  - push_back spartą
  - atminties perskirstymus (reallocations)
  - failų skaitymą
  - studentų dalinimo algoritmus

---

## Funkcionalumas

Programa leidžia:
- Įvesti studentus terminale
- Nuskaityti iš failo
- Generuoti testinius failus
- Padalinti studentus į grupes (vargsiukai / kietiakai)
- Testuoti 3 split strategijas
- Lyginti std::vector ir My Vector
- Matuoti push_back ir reallocations

---

## VECTOR 3 STRATEGIJOS REZULTATAI

### 100 000 studentų

| Konteineris | Dalinimo laikas | Read laikas |
|------------|----------------|-------------|
| std::vector | 0.023389 s | 0.386926 s |
| My Vector   | 0.028158 s | 0.354138 s |

---

### 1 000 000 studentų

| Konteineris | Dalinimo laikas | Read laikas |
|------------|----------------|-------------|
| std::vector | 0.214749 s | 3.78705 s |
| My Vector   | 0.251329 s | 3.48407 s |

---

### 10 000 000 studentų

| Konteineris | Dalinimo laikas | Read laikas |
|------------|----------------|-------------|
| std::vector | 2.51136 s | 82.1892 s |
| My Vector   | 3.48541 s | 80.6484 s |

---

## PUSH_BACK SPARTA (VEKTORIAUS PILDYMAS)

Buvo atliktas testas, kai į tuščią konteinerį dedami elementai naudojant `push_back()`.

### Rezultatai

| Elementų kiekis | std::vector | My Vector |
|----------------|-------------|-----------|
| 10 000 | labai greita (~0.0001 s) | labai greita (~0.0001 s) |
| 100 000 | ~0.0006 s | ~0.0005 s |
| 1 000 000 | ~0.003–0.004 s | ~0.003–0.004 s |
| 10 000 000 | ~0.03–0.04 s | ~0.03–0.04 s |
| 100 000 000 | ~0.2–0.3 s | ~0.3 s |

---

## RELOKACIJOS (100M elementų)

| Konteineris | Reallocations |
|------------|--------------|
| std::vector | 28 |
| My Vector   | 28 |

---

## IŠVADOS

- std::vector yra šiek tiek greitesnis split operacijose
- My Vector labai artimas std::vector push_back našumui
- Abu konteineriai turi O(n) augimą
- Reallocacijos sutampa → teisinga grow strategija
- My Vector yra tinkamas STL imitacijos sprendimas

---

## TECHNINĖ INFORMACIJA

My Vector palaiko:
- push_back
- erase (iterator)
- begin / end
- dynamic resizing
- realloc tracking

---

## TESTAVIMO SCENARIJAI

- push_back benchmarking (10k → 100M)
- Vector vs std::vector palyginimas
- splitVector1/2/3 strategijos
- failų generavimas ir skaitymas

---

## BUILD

g++ -O2 -std=c++17 *.cpp -o app

---

## PASTABOS

- Naudotas chrono high_resolution_clock
- Testai atlikti release režimu
- Rezultatai gali skirtis pagal CPU apkrovą
