#include "funkcijos.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <type_traits>

void testAbstractBaseClass() {
    static_assert(std::is_abstract<Zmogus>::value, "Zmogus turi buti abstrakti klase");
    static_assert(std::is_base_of<Zmogus, Studentas>::value, "Studentas turi paveldeti is Zmogus");

    Studentas s;
    Zmogus* z = &s;

    assert(z->getVardas() == "");
    assert(z->getPavarde() == "");
    assert(z->tipas() == "Studentas");
}

void testDefaultConstructor() {
    Studentas s;

    assert(s.getVardas() == "");
    assert(s.getPavarde() == "");
    assert(s.getEgzaminas() == 0);
    assert(s.getNamuDarbaiVid100() == 0);
    assert(s.getNamuDarbaiMed100() == 0);
    assert(s.getND().empty());
}

void testParameterizedConstructor() {
    Studentas s("Jonas", "Jonaitis", 9, 850, 900, {8, 9, 10});

    assert(s.getVardas() == "Jonas");
    assert(s.getPavarde() == "Jonaitis");
    assert(s.getEgzaminas() == 9);
    assert(s.getNamuDarbaiVid100() == 850);
    assert(s.getNamuDarbaiMed100() == 900);
    assert(s.getND().size() == 3);
    assert(s.getND()[0] == 8);
    assert(s.getND()[1] == 9);
    assert(s.getND()[2] == 10);
}

void testCopyConstructor() {
    Studentas a("Ona", "Onaite", 8, 700, 800, {6, 7, 8});
    Studentas b(a);

    assert(b.getVardas() == a.getVardas());
    assert(b.getPavarde() == a.getPavarde());
    assert(b.getEgzaminas() == a.getEgzaminas());
    assert(b.getNamuDarbaiVid100() == a.getNamuDarbaiVid100());
    assert(b.getNamuDarbaiMed100() == a.getNamuDarbaiMed100());
    assert(b.getND() == a.getND());
}

void testCopyAssignment() {
    Studentas a("Petras", "Petraitis", 10, 900, 900, {9, 9, 9});
    Studentas b;

    b = a;

    assert(b.getVardas() == a.getVardas());
    assert(b.getPavarde() == a.getPavarde());
    assert(b.getEgzaminas() == a.getEgzaminas());
    assert(b.getNamuDarbaiVid100() == a.getNamuDarbaiVid100());
    assert(b.getNamuDarbaiMed100() == a.getNamuDarbaiMed100());
    assert(b.getND() == a.getND());
}

void testSelfCopyAssignment() {
    Studentas a("Mantas", "Mantaitis", 7, 650, 700, {6, 7, 8});

    a = a;

    assert(a.getVardas() == "Mantas");
    assert(a.getPavarde() == "Mantaitis");
    assert(a.getEgzaminas() == 7);
    assert(a.getNamuDarbaiVid100() == 650);
    assert(a.getNamuDarbaiMed100() == 700);
    assert(a.getND().size() == 3);
}

void testMoveConstructor() {
    Studentas a("Lukas", "Lukaitis", 8, 750, 800, {7, 8, 9});
    Studentas b(std::move(a));

    assert(b.getVardas() == "Lukas");
    assert(b.getPavarde() == "Lukaitis");
    assert(b.getEgzaminas() == 8);
    assert(b.getNamuDarbaiVid100() == 750);
    assert(b.getNamuDarbaiMed100() == 800);
    assert(b.getND().size() == 3);
    assert(b.getND()[0] == 7);
    assert(b.getND()[1] == 8);
    assert(b.getND()[2] == 9);

    assert(a.getEgzaminas() == 0);
    assert(a.getNamuDarbaiVid100() == 0);
    assert(a.getNamuDarbaiMed100() == 0);
}

void testMoveAssignment() {
    Studentas a("Ieva", "Ievaite", 9, 880, 900, {8, 9, 10});
    Studentas b;

    b = std::move(a);

    assert(b.getVardas() == "Ieva");
    assert(b.getPavarde() == "Ievaite");
    assert(b.getEgzaminas() == 9);
    assert(b.getNamuDarbaiVid100() == 880);
    assert(b.getNamuDarbaiMed100() == 900);
    assert(b.getND().size() == 3);
    assert(b.getND()[0] == 8);
    assert(b.getND()[1] == 9);
    assert(b.getND()[2] == 10);

    assert(a.getEgzaminas() == 0);
    assert(a.getNamuDarbaiVid100() == 0);
    assert(a.getNamuDarbaiMed100() == 0);
}

void testSelfMoveAssignment() {
    Studentas a("Rokas", "Rokaitis", 6, 600, 600, {6, 6, 6});

    a = std::move(a);

    assert(a.getVardas() == "Rokas");
    assert(a.getPavarde() == "Rokaitis");
    assert(a.getEgzaminas() == 6);
    assert(a.getNamuDarbaiVid100() == 600);
    assert(a.getNamuDarbaiMed100() == 600);
    assert(a.getND().size() == 3);
}

void testDestructor() {
    {
        Studentas s("Temp", "Temp", 5, 500, 500, {5, 5, 5});
        assert(s.getVardas() == "Temp");
    }

    assert(true);
}

void testGenerateFile() {
    const std::string fileName = "test_generated.txt";
    generateFile(5, 3, fileName);

    std::ifstream in(fileName);
    assert(in.is_open());

    std::string line;
    std::getline(in, line);
    assert(!line.empty());

    int lineCount = 0;
    while (std::getline(in, line)) {
        ++lineCount;
    }

    assert(lineCount == 5);
}

void testReadFile() {
    const std::string fileName = "test_input.txt";
    std::ofstream out(fileName);

    out << "Vardas Pavarde ND1 ND2 ND3 Egz.\n";
    out << "Jonas Jonaitis 8 9 10 7\n";
    out << "Ona Onaite 6 7 8 9\n";
    out.close();

    Vector<Studentas> studentai = readFile(fileName, true);

    assert(studentai.size() == 2);

    assert(studentai[0].getVardas() == "Jonas");
    assert(studentai[0].getPavarde() == "Jonaitis");
    assert(studentai[0].getEgzaminas() == 7);
    assert(studentai[0].getND().size() == 3);
    assert(studentai[0].getND()[0] == 8);
    assert(studentai[0].getND()[1] == 9);
    assert(studentai[0].getND()[2] == 10);

    assert(studentai[1].getVardas() == "Ona");
    assert(studentai[1].getPavarde() == "Onaite");
    assert(studentai[1].getEgzaminas() == 9);
    assert(studentai[1].getND().size() == 3);
    assert(studentai[1].getND()[0] == 6);
    assert(studentai[1].getND()[1] == 7);
    assert(studentai[1].getND()[2] == 8);
}

void testReadFileWithoutSavingND() {
    const std::string fileName = "test_input_no_nd.txt";
    std::ofstream out(fileName);

    out << "Vardas Pavarde ND1 ND2 Egz.\n";
    out << "Tomas Tomaitis 5 6 7\n";
    out.close();

    Vector<Studentas> studentai = readFile(fileName, false);

    assert(studentai.size() == 1);
    assert(studentai[0].getVardas() == "Tomas");
    assert(studentai[0].getPavarde() == "Tomaitis");
    assert(studentai[0].getEgzaminas() == 7);
    assert(studentai[0].getND().empty());
}

void testClass() {
    testAbstractBaseClass();

    testDefaultConstructor();
    testParameterizedConstructor();

    testCopyConstructor();
    testCopyAssignment();
    testSelfCopyAssignment();

    testMoveConstructor();
    testMoveAssignment();
    testSelfMoveAssignment();

    testDestructor();

    testGenerateFile();
    testReadFile();
    testReadFileWithoutSavingND();

    std::cout << "Visi pasirinkti testai sekmingai praeiti.\n";
}
