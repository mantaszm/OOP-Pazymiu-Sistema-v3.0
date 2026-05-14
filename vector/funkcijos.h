#ifndef OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H
#define OOP_PAZYMIU_SISTEMA_FUNKCIJOS_H

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <string>
#include <random>
#include <cstring>
#include <sstream>
#include <utility>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus();
    Zmogus(const std::string& vardas, const std::string& pavarde);
    virtual ~Zmogus() = default;

    const std::string& getVardas() const;
    const std::string& getPavarde() const;

    void setVardas(const std::string& value);
    void setPavarde(const std::string& value);

    virtual std::string tipas() const = 0;
};

class Studentas : public Zmogus {
private:
    uint16_t namuDarbaiVid100_;
    uint16_t namuDarbaiMed100_;
    uint8_t egzaminas_;
    std::vector<short int> ND_;

public:
    Studentas();
    ~Studentas();

    Studentas(const std::string& vardas,
              const std::string& pavarde,
              uint8_t egzaminas,
              uint16_t namuDarbaiVid100,
              uint16_t namuDarbaiMed100,
              const std::vector<short int>& ND = {});

    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(Studentas&& other) noexcept;

    uint16_t getNamuDarbaiVid100() const;
    uint16_t getNamuDarbaiMed100() const;
    uint8_t getEgzaminas() const;
    const std::vector<short int>& getND() const;

    void setNamuDarbaiVid100(uint16_t value);
    void setNamuDarbaiMed100(uint16_t value);
    void setEgzaminas(uint8_t value);
    void setND(const std::vector<short int>& value);
    void addND(short int pazymys);

    double galutinisVid() const;
    double galutinisMed() const;

    std::string tipas() const override;
};

std::istream& operator>>(std::istream& in, Studentas& s);
std::ostream& operator<<(std::ostream& out, const Studentas& s);

std::vector<Studentas> readFile(const std::string& filename, bool saveND = false);
std::vector<Studentas> readTerminal();
void generateFile(int kiekStud, int kiekND, std::string fileName);
void splitStudents(std::string dataFileName, std::string newFileName);
void testFileCreation(int kiekStud, int kiekND, const std::string& fileName);
void testDataProcessing(const std::string& fileName);
void testTime(int testSize, int ndSize);
void testClass();

template<typename Container>
double testPushBack(Container& c, size_t sz);
void runBenchmarks(size_t sz);

void splitVector1(const std::vector<Studentas>& studentai,
                  std::vector<Studentas>& vargsiukai,
                  std::vector<Studentas>& kietiakai);

void splitVector2(std::vector<Studentas>& studentai,
                  std::vector<Studentas>& vargsiukai);

void splitVector3(std::vector<Studentas>& studentai,
                  std::vector<Studentas>& vargsiukai);

void splitList1(const std::list<Studentas>& studentai,
                std::list<Studentas>& vargsiukai,
                std::list<Studentas>& kietiakai);

void splitList2(std::list<Studentas>& studentai,
                std::list<Studentas>& vargsiukai);

void splitList3(std::list<Studentas>& studentai,
                std::list<Studentas>& vargsiukai);

void splitDeque1(const std::deque<Studentas>& studentai,
                 std::deque<Studentas>& vargsiukai,
                 std::deque<Studentas>& kietiakai);

void splitDeque2(std::deque<Studentas>& studentai,
                 std::deque<Studentas>& vargsiukai);

void splitDeque3(std::deque<Studentas>& studentai,
                 std::deque<Studentas>& vargsiukai);

#endif
