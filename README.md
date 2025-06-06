# 🤖 NHF1 - Robtun

### Nagy Házi Feladat

---

## 📌 Projekt Leírás

**Robtun** egy szöveges felületen futó, karakteralapú túlélő-típusú játék, amely a `Programozás Alapjai 2.` kurzus keretében készült a **2024 tavaszi félévben**.

A cél, hogy a játékos a térképen mozogva elkerülje az ellenségeket, és minél tovább túléljen. A játékmenet turn-alapú, és különféle entitásokat tartalmaz: játékos, akadály, robot ellenfelek.

---

## 📁 Projekt Felépítése

```bash
nhf1_robtun/
├── cpp/              # Forrásfájlok (játéklogika, entitások)
├── include/          # Header fájlok
├── data/             # Térképek, konfigurációk
├── tests/            # Tesztfájlok
├── main.cpp          # Program belépési pontja
├── README.md         # Ez a fájl
└── Makefile          # Fordításhoz szükséges fájl
```

---

## ⚙️ Fő Funkciók

- 🧍‍♂️ Játékos mozgás (WASD)
- 🤖 Robot entitások mozgása mesterséges logikával
- 🧱 Falak, akadályok
- 📉 Életpont kezelés
- 💾 Térkép betöltés fájlból
- 🪦 Game Over és újrakezdés lehetőség

---

## 🧪 Tesztelés

A `tests` mappában egységtesztek találhatók.

```bash
g++ tests/test_runner.cpp -o test_runner
./test_runner
```

---

## 🛠️ Fordítás

A projekt Makefile-al építhető:

```bash
make
./robtun
```

---

## 🎮 Játékmenet

- A játék terminálon fut.
- A térképen a következő szimbólumok jelennek meg:
  - `@` – játékos
  - `#` – fal
  - `R` – robot
  - `.` – szabad mező
- A játék célja a minél hosszabb túlélés.

---

## 📄 Követelmények

- C++11 vagy újabb
- Fordító (g++, clang++)
- Unix-szerű környezet (Linux / macOS ajánlott)

---

## 👨‍💻 Készítette

RobiiHUN  
2024, 
