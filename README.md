# Vector konteinerio projektas (STL imitacija)

## 1. Projekto aprašymas

Šiame projekte realizuota nuosava `Vector<T>` klasė, imituojanti `std::vector` funkcionalumą.  
Konteineris palaiko dinaminę atmintį, `push_back`, `insert`, `erase`, iteraciją, copy ir move semantiką.

Taip pat atliktas palyginimas su `std::vector` pagal veikimo greitį.

---

## 2. Realizuotos pagrindinės funkcijos (STL analogai)

### push_back
Prideda elementą į vektoriaus galą.

v.push_back(10);

---

### insert
Įterpia elementą į nurodytą vietą.

v.insert(1, 99);

---

### erase
Pašalina elementą pagal indeksą.

v.erase(0);

---

### reserve
Padidina talpą iš anksto.

v.reserve(1000);

---

### operator[]
Prieiga prie elemento.

int x = v[0];

---

### Papildomai realizuota:
- copy constructor
- copy assignment
- move constructor
- move assignment
- begin(), end()
- size(), capacity()
- shrink_to_fit()
- clear()

---

## 3. Testų paleidimas

Testai paleidžiami per funkciją:

int main() {
    testClass();
}

Jei gaunama klaida:
undefined reference to testClass()

reiškia, kad reikia į kompiliaciją įtraukti .cpp failą:

g++ main.cpp funkcijos.cpp -o app

---

## 4. Spartos analizė (push_back)

Rezultatai:

SIZE = 10000  
std::vector: 9.2e-05 s  
Vector:       6.3e-05 s  

SIZE = 100000  
std::vector: 0.00066 s  
Vector:       0.00056 s  

SIZE = 1000000  
std::vector: 0.003499 s  
Vector:       0.003694 s  

SIZE = 10000000  
std::vector: 0.035827 s  
Vector:       0.03508 s  

SIZE = 100000000  
std::vector: 0.270734 s  
Vector:       0.316023 s  

---

## 5. Analizė

- Mažiems dydžiams Vector kartais greitesnis dėl paprastesnės implementacijos
- Dideliems dydžiams std::vector dažniausiai efektyvesnis

---

## 6. Testuotos funkcijos

- push_back
- insert
- erase
- copy/move
- file read/write
- studentų apdorojimas

---

## 7. Išvada

Sukurta Vector<T> klasė:
- atitinka ~80–90% std::vector funkcionalumo
- palaiko move semantics
- veikia su realiais duomenimis
- leidžia atlikti performance analizę

---

## 8. Paleidimas

g++ main.cpp funkcijos.cpp -O2 -o app
./app