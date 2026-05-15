#include "funkcijos.h"
#include "mano_vector.h"

// Zmogus
Zmogus::Zmogus()
    : vardas_(""), pavarde_("") {}

Zmogus::Zmogus(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {}

const std::string& Zmogus::getVardas() const {
    return vardas_;
}

const std::string& Zmogus::getPavarde() const {
    return pavarde_;
}

void Zmogus::setVardas(const std::string& value) {
    vardas_ = value;
}

void Zmogus::setPavarde(const std::string& value) {
    pavarde_ = value;
}

// Studentas: konstruktoriai
Studentas::Studentas()
    : Zmogus(),
      namuDarbaiVid100_(0),
      namuDarbaiMed100_(0),
      egzaminas_(0),
      ND_() {}

Studentas::Studentas(const std::string& vardas,
                     const std::string& pavarde,
                     uint8_t egzaminas,
                     uint16_t namuDarbaiVid100,
                     uint16_t namuDarbaiMed100,
                     const Vector<short int>& ND)
    : Zmogus(vardas, pavarde),
      namuDarbaiVid100_(namuDarbaiVid100),
      namuDarbaiMed100_(namuDarbaiMed100),
      egzaminas_(egzaminas),
      ND_(ND) {}

Studentas::~Studentas() = default;

Studentas::Studentas(const Studentas& other)
    : Zmogus(other),
      namuDarbaiVid100_(other.namuDarbaiVid100_),
      namuDarbaiMed100_(other.namuDarbaiMed100_),
      egzaminas_(other.egzaminas_),
      ND_(other.ND_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        namuDarbaiVid100_ = other.namuDarbaiVid100_;
        namuDarbaiMed100_ = other.namuDarbaiMed100_;
        egzaminas_ = other.egzaminas_;
        ND_ = other.ND_;
    }
    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : Zmogus(std::move(other.vardas_), std::move(other.pavarde_)),
      namuDarbaiVid100_(other.namuDarbaiVid100_),
      namuDarbaiMed100_(other.namuDarbaiMed100_),
      egzaminas_(other.egzaminas_),
      ND_(std::move(other.ND_)) {
    other.namuDarbaiVid100_ = 0;
    other.namuDarbaiMed100_ = 0;
    other.egzaminas_ = 0;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        namuDarbaiVid100_ = other.namuDarbaiVid100_;
        namuDarbaiMed100_ = other.namuDarbaiMed100_;
        egzaminas_ = other.egzaminas_;
        ND_ = std::move(other.ND_);

        other.namuDarbaiVid100_ = 0;
        other.namuDarbaiMed100_ = 0;
        other.egzaminas_ = 0;
    }
    return *this;
}

// Studentas metodai
uint16_t Studentas::getNamuDarbaiVid100() const {
    return namuDarbaiVid100_;
}

uint16_t Studentas::getNamuDarbaiMed100() const {
    return namuDarbaiMed100_;
}

uint8_t Studentas::getEgzaminas() const {
    return egzaminas_;
}

const Vector<short int>& Studentas::getND() const {
    return ND_;
}

void Studentas::setNamuDarbaiVid100(uint16_t value) {
    namuDarbaiVid100_ = value;
}

void Studentas::setNamuDarbaiMed100(uint16_t value) {
    namuDarbaiMed100_ = value;
}

void Studentas::setEgzaminas(uint8_t value) {
    egzaminas_ = value;
}

void Studentas::setND(const Vector<short int>& value) {
    ND_ = value;
}

void Studentas::addND(short int pazymys) {
    ND_.push_back(pazymys);
}

double Studentas::galutinisVid() const {
    return (namuDarbaiVid100_ / 100.0) * 0.4 + egzaminas_ * 0.6;
}

double Studentas::galutinisMed() const {
    return (namuDarbaiMed100_ / 100.0) * 0.4 + egzaminas_ * 0.6;
}

std::string Studentas::tipas() const {
    return "Studentas";
}

// Perdengti operatoriai
std::istream& operator>>(std::istream& in, Studentas& s) {
    std::string vardas, pavarde;
    in >> vardas >> pavarde;

    if (!in) return in;

    s.setVardas(vardas);
    s.setPavarde(pavarde);

    Vector<short int> nd;
    int x = 0;

    while (in >> x) {
        nd.push_back(static_cast<short int>(x));
        if (in.peek() == '\n') break;
    }

    if (!nd.empty()) {
        s.setEgzaminas(static_cast<uint8_t>(nd.back()));
        nd.pop_back();

        int suma = 0;
        for (short int v : nd) {
            suma += v;
        }

        std::sort(nd.begin(), nd.end());

        const std::size_t n = nd.size();
        double med = 0.0;

        if (n > 0) {
            if (n % 2 == 0) {
                med = (nd[n / 2 - 1] + nd[n / 2]) / 2.0;
            } else {
                med = nd[n / 2];
            }
        }

        s.setNamuDarbaiVid100(
            (n > 0)
                ? static_cast<uint16_t>((static_cast<double>(suma) / static_cast<double>(n)) * 100.0)
                : 0
        );

        s.setNamuDarbaiMed100(static_cast<uint16_t>(med * 100.0));
        s.setND(nd);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const Studentas& s) {
    out << std::left
        << std::setw(12) << s.getVardas()
        << std::setw(15) << s.getPavarde()
        << std::setw(10) << s.galutinisVid()
        << std::setw(10) << s.galutinisMed();

    return out;
}

// Failo skaitymas
Vector<Studentas> readFile(const std::string& filename, bool saveND) {
    std::ifstream in(filename);
    Vector<Studentas> studentai;

    if (!in) {
        std::cout << "Nepavyko atidaryti failo\n";
        return studentai;
    }

    std::string line;
    std::getline(in, line); // header

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Studentas temp;
        ss >> temp;

        if (temp.getVardas().empty() || temp.getPavarde().empty()) continue;

        if (!saveND) {
            temp.setND({});
        }

        studentai.push_back(temp);
    }

    return studentai;
}

// Skaitymas is terminalo
Vector<Studentas> readTerminal() {
    Vector<Studentas> studentai;
    Studentas temp;

    int mode = 0;
    int kiekND = 0;
    int mokiniai = 0;

    std::cout << "Rezimas:\n1 - rankinis\n2 - random pazymiai\n3 - random vardai ir pazymiai\n";
    char whatMode[2]{};
    std::cin.getline(whatMode, 2);

    switch (whatMode[0]) {
        case '1':
            mode = 1;
            break;

        case '2': {
            mode = 2;
            std::cout << "Namu darbu pazymiu skaicius: ";
            std::string ndSkaicius;
            std::getline(std::cin, ndSkaicius);
            try {
                kiekND = std::stoi(ndSkaicius);
            } catch (...) {
                std::cout << "Ne skaicius!\n";
                return {};
            }
            break;
        }

        case '3': {
            mode = 3;
            std::cout << "Namu darbu pazymiu skaicius:\n";
            try {
                std::cin >> kiekND;
                std::cout << "Mokiniu kiekis:\n";
                std::cin >> mokiniai;
                std::cin.ignore();
            } catch (...) {
                std::cout << "Ne skaicius!\n";
                return {};
            }
            break;
        }

        default:
            std::cout << "Netinkamas\n";
            return {};
    }

    while (!(mode == 3 && mokiniai == 0)) {
        temp = Studentas{};
        std::string stringTemp;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 10);

        if (mode != 3) {
            std::cout << "Norint baigti parasykite 'baigti'\nVardas: ";
            std::getline(std::cin, stringTemp);
            if (stringTemp == "baigti") break;
            temp.setVardas(stringTemp);

            std::cout << "Pavarde: ";
            std::getline(std::cin, stringTemp);
            temp.setPavarde(stringTemp);
        } else {
            std::string vardai[11] = {
                "Jonas","Mantas","Lukas","Tomas","Dovydas",
                "Karolis","Rokas","Paulius","Andrius","Gabrielius","Dominykas"
            };
            std::string pavardes[11] = {
                "Kazlauskas","Jankauskas","Petrauskas","Balciunas","Zukauskas",
                "Vasiliauskas","Butkus","Navickas","Urbonas","Kavaliauskas","Stankevicius"
            };

            temp.setVardas(vardai[distrib(gen)]);
            temp.setPavarde(pavardes[distrib(gen)]);
        }

        int suma = 0;
        int kiek = 0;
        Vector<int> nd_pazymiai;

        if (mode == 1) {
            std::cout << "Iveskite namu darbu pazymius (atskirtus tarpais): ";
            std::getline(std::cin, stringTemp);

            std::stringstream ss(stringTemp);
            int paz = 0;

            while (ss >> paz) {
                if (paz < 0 || paz > 10) {
                    std::cout << "Netinkamas pazymys (0-10). Ignoruojamas.\n";
                    continue;
                }
                suma += paz;
                nd_pazymiai.push_back(paz);
                kiek++;
            }
        } else {
            for (int i = 0; i < kiekND; i++) {
                int paz = distrib(gen);
                suma += paz;
                nd_pazymiai.push_back(paz);
                kiek++;
            }

            temp.setEgzaminas(static_cast<uint8_t>(distrib(gen)));
        }

        std::sort(nd_pazymiai.begin(), nd_pazymiai.end());

        double nd_med = 0.0;

        if (kiek > 0) {
            if (kiek % 2 == 0) {
                nd_med = (nd_pazymiai[kiek / 2 - 1] + nd_pazymiai[kiek / 2]) / 2.0;
            } else {
                nd_med = nd_pazymiai[kiek / 2];
            }
        }

        temp.setNamuDarbaiMed100(static_cast<uint16_t>(nd_med * 100.0));

        if (kiek > 0) {
            temp.setNamuDarbaiVid100(
                static_cast<uint16_t>((static_cast<double>(suma) / static_cast<double>(kiek)) * 100.0)
            );
        } else {
            temp.setNamuDarbaiVid100(0);
        }

        if (mode == 1) {
            std::cout << "Egzamino pazymys: ";
            std::getline(std::cin, stringTemp);
            temp.setEgzaminas(static_cast<uint8_t>(std::stoi(stringTemp)));
        }

        studentai.push_back(temp);
        mokiniai--;
    }

    return studentai;
}

// Failo generavimas
void generateFile(int kiekStud, int kiekND, std::string fileName) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cout << "Nepavyko sukurti failo.\n";
        return;
    }

    outFile << std::left
            << std::setw(14) << "Vardas"
            << std::setw(17) << "Pavarde";

    for (int i = 1; i <= kiekND; i++) {
        outFile << std::setw(10) << ("ND" + std::to_string(i));
    }
    outFile << std::setw(10) << "Egz." << "\n";

    for (int i = 1; i <= kiekStud; i++) {
        outFile << std::left
                << std::setw(14) << ("Vardas" + std::to_string(i))
                << std::setw(17) << ("Pavarde" + std::to_string(i));

        for (int j = 0; j <= kiekND; j++) {
            outFile << std::setw(10) << distrib(gen);
        }
        outFile << "\n";
    }
}

// Studentu skaidymas i failus
void splitStudents(std::string dataFileName, std::string newFileName) {
    Vector<Studentas> mokiniai = readFile(dataFileName, true);

    std::ofstream outGood("good_" + newFileName);
    std::ofstream outBad("bad_" + newFileName);

    if (!outGood || !outBad) {
        std::cout << "Nepavyko sukurti failo.\n";
        return;
    }

    if (mokiniai.empty()) return;

    int kiekND = static_cast<int>(mokiniai[0].getND().size());

    auto printHeader = [&](std::ostream& out) {
        out << std::left
            << std::setw(14) << "Vardas"
            << std::setw(17) << "Pavarde";

        for (int i = 1; i <= kiekND; i++) {
            out << std::setw(10) << ("ND" + std::to_string(i));
        }

        out << std::setw(10) << "Egz." << "\n";
    };

    printHeader(outGood);
    printHeader(outBad);

    for (const auto& s : mokiniai) {
        std::ostream& out = (s.galutinisVid() >= 5.0) ? outGood : outBad;

        out << std::left
            << std::setw(14) << s.getVardas()
            << std::setw(17) << s.getPavarde();

        for (short int nd : s.getND()) {
            out << std::setw(10) << nd;
        }

        out << std::setw(10) << static_cast<int>(s.getEgzaminas()) << "\n";
    }
}

// Testavimo funkcijos
void testFileCreation(int kiekStud, int kiekND, const std::string& fileName) {
    auto start = std::chrono::high_resolution_clock::now();
    generateFile(kiekStud, kiekND, fileName);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Failo sukurimo laikas: "
              << std::chrono::duration<double>(end - start).count() << " s\n";
}

void testDataProcessing(const std::string& fileName) {
    auto t0 = std::chrono::high_resolution_clock::now();
    Vector<Studentas> students = readFile(fileName, true);
    auto t1 = std::chrono::high_resolution_clock::now();

    Vector<Studentas> good, bad;
    for (const auto& s : students) {
        if (s.galutinisVid() >= 5.0) {
            good.push_back(s);
        } else {
            bad.push_back(s);
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << "Failo nuskaitymo laikas: "
              << std::chrono::duration<double>(t1 - t0).count() << " s\n";
    std::cout << "Studentu skirstymo laikas: "
              << std::chrono::duration<double>(t2 - t1).count() << " s\n";
    std::cout << "Bendras laikas: "
              << std::chrono::duration<double>(t2 - t0).count() << " s\n";
}

void testTime(int testSize, int ndSize) {
    std::cout << "Dydis: " << testSize << "\n";
    testFileCreation(testSize, ndSize, "students.txt");
    testDataProcessing("students.txt");
}

template<typename Container>
double testPushBack(Container& c, size_t sz) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < sz; ++i) {
        c.push_back(static_cast<int>(i));
    }

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double>(end - start).count();
}

void runTimeBenchmarks(size_t sz) {
    std::cout << "\nSIZE = " << sz << "\n";

    // Vector
    Vector<int> v1;
    double t1 = testPushBack(v1, sz);

    // my vector
    Vector<int> v2;
    double t2 = testPushBack(v2, sz);

    std::cout << "Vector: " << t1 << " s\n";
    std::cout << "Vector      : " << t2 << " s\n";
}

size_t testStdVector(size_t n) {
    Vector<int> c;

    size_t reallocs = 0;
    size_t prev_capacity = 0;

    for (size_t i = 0; i < n; ++i) {
        c.push_back(i);

        if (c.capacity() != prev_capacity) {
            prev_capacity = c.capacity();
            ++reallocs;
        }
    }

    return reallocs;
}

size_t testMyVector(size_t n) {
    Vector<int> v;

    for (size_t i = 0; i < n; ++i)
        v.push_back(i);

    return v.getReallocations();
}

// VECTOR strategijos
void splitVector1(const Vector<Studentas>& studentai,
                  Vector<Studentas>& vargsiukai,
                  Vector<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (s.galutinisVid() < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakai.push_back(s);
        }
    }
}

void splitVector2(Vector<Studentas>& studentai,
                  Vector<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end();) {
        if (it->galutinisVid() < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

void splitVector3(Vector<Studentas>& studentai,
                  Vector<Studentas>& vargsiukai) {
    auto it = std::partition(studentai.begin(), studentai.end(),
        [](const Studentas& s) {
            return s.galutinisVid() >= 5.0;
        });

    for (auto i = it; i != studentai.end(); ++i) {
        vargsiukai.push_back(*i);
    }

    studentai.erase(it, studentai.end());
}

// LIST strategijos
void splitList1(const std::list<Studentas>& studentai,
                std::list<Studentas>& vargsiukai,
                std::list<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (s.galutinisVid() < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakai.push_back(s);
        }
    }
}

void splitList2(std::list<Studentas>& studentai,
                std::list<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end();) {
        if (it->galutinisVid() < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

void splitList3(std::list<Studentas>& studentai,
                std::list<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end();) {
        if (it->galutinisVid() < 5.0) {
            auto temp = it++;
            vargsiukai.splice(vargsiukai.end(), studentai, temp);
        } else {
            ++it;
        }
    }
}

// DEQUE strategijos
void splitDeque1(const std::deque<Studentas>& studentai,
                 std::deque<Studentas>& vargsiukai,
                 std::deque<Studentas>& kietiakai) {
    for (const auto& s : studentai) {
        if (s.galutinisVid() < 5.0) {
            vargsiukai.push_back(s);
        } else {
            kietiakai.push_back(s);
        }
    }
}

void splitDeque2(std::deque<Studentas>& studentai,
                 std::deque<Studentas>& vargsiukai) {
    for (auto it = studentai.begin(); it != studentai.end();) {
        if (it->galutinisVid() < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
}

void splitDeque3(std::deque<Studentas>& studentai,
                 std::deque<Studentas>& vargsiukai) {
    auto it = std::partition(studentai.begin(), studentai.end(),
        [](const Studentas& s) {
            return s.galutinisVid() >= 5.0;
        });

    for (auto i = it; i != studentai.end(); ++i) {
        vargsiukai.push_back(*i);
    }

    studentai.erase(it, studentai.end());
}

template double testPushBack(std::vector<int>&, size_t);
template double testPushBack(Vector<int>&, size_t);
