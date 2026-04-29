#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include "Hotel.h"
#include "CameraStandard.h"
#include "Apartament.h"
#include "Penthouse.h"
#include "ExceptiiHotel.h"

const std::string kDataFile = "hotel_data.txt";
const std::string kHistoryFile = "hotel_history.txt";

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}

std::string askToken(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    if (!(std::cin >> value)) {
        clearInputBuffer();
        throw EroareDateInvalide("expected text input");
    }
    return value;
}

int askInt(const std::string& prompt) {
    std::cout << prompt;
    int value = 0;
    if (!(std::cin >> value)) {
        clearInputBuffer();
        throw EroareDateInvalide("expected integer input");
    }
    return value;
}

double askDouble(const std::string& prompt) {
    std::cout << prompt;
    double value = 0.0;
    if (!(std::cin >> value)) {
        clearInputBuffer();
        throw EroareDateInvalide("expected numeric input");
    }
    return value;
}

bool loadSetup(const std::string& path, std::string& hotelName, std::string& adminName) {
    std::ifstream in(path);
    if (!in) return false;
    if (!std::getline(in, hotelName)) return false;
    if (!std::getline(in, adminName)) return false;
    return !(hotelName.empty() || adminName.empty());
}

bool saveSetup(const std::string& path, const std::string& hotelName, const std::string& adminName) {
    std::ofstream out(path, std::ios::trunc);
    if (!out) return false;
    out << hotelName << '\n';
    out << adminName << '\n';
    return true;
}

bool appendOperation(const std::string& path, const std::string& type, const std::vector<std::string>& fields) {
    std::ofstream out(path, std::ios::app);
    if (!out) return false;
    out << type << '\n';
    for (const auto& field : fields) out << field << '\n';
    out << '\n';
    return true;
}

void replayOperations(const std::string& path, Hotel& hotel) {
    std::ifstream in(path);
    if (!in) return;

    std::string type;
    while (in >> type) {
        try {
            if (type == "ADD_STANDARD") {
                int nr = 0;
                double pret = 0.0;
                if (!(in >> nr >> pret)) break;
                hotel.adaugaCamera(std::make_shared<CameraStandard>(nr, pret));
            } else if (type == "ADD_APARTAMENT") {
                int nr = 0;
                double pret = 0.0, taxa = 0.0;
                if (!(in >> nr >> pret >> taxa)) break;
                hotel.adaugaCamera(std::make_shared<Apartament>(nr, pret, taxa));
            } else if (type == "ADD_PENTHOUSE") {
                int nr = 0;
                double pret = 0.0;
                if (!(in >> nr >> pret)) break;
                hotel.adaugaCamera(std::make_shared<Penthouse>(nr, pret, false));
            } else if (type == "REZERVARE") {
                int nr = 0, nopti = 0;
                std::string client;
                if (!(in >> nr >> client >> nopti)) break;
                hotel.rezervaCamera(nr, client, nopti);
            } else if (type == "VIP") {
                hotel.oferaPachetSpaVIP();
            } else {
                std::cout << "Operatiune necunoscuta in istoric: " << type << '\n';
                break;
            }
        } catch (const std::exception& e) {
            std::cout << "Eroare la incarcarea istoricului: " << e.what() << '\n';
            break;
        }
    }
}

void populateDefaultRooms(Hotel& hotel) {
    try {
        hotel.adaugaCamera(std::make_shared<CameraStandard>(101, 150.0));
        hotel.adaugaCamera(std::make_shared<CameraStandard>(102, 150.0));
        hotel.adaugaCamera(std::make_shared<Apartament>(201, 350.0, 50.0));
        hotel.adaugaCamera(std::make_shared<Apartament>(202, 350.0, 50.0));
        hotel.adaugaCamera(std::make_shared<Penthouse>(301, 1000.0, false));
    } catch (const EroareHotel&) {
    }
}

void printHotelStats(const Hotel& hotel) {
    std::cout << "\n=== Statistici Generale Hotel ===\n";
    std::cout << hotel << '\n';
    std::cout << "Sistem activ. Datele sunt protejate si incapsulate.\n";
    std::cout << "---------------------------------\n";
}

void adminMenu(Hotel& hotel, const std::string& adminName) {
    while (true) {
        std::cout << "\n=== Admin Menu (" << adminName << ") ===\n";
        std::cout << "1 - Adauga Camera Standard\n";
        std::cout << "2 - Adauga Apartament\n";
        std::cout << "3 - Adauga Penthouse\n";
        std::cout << "4 - Activeaza Pachet VIP (Toate Penthouse-urile)\n";
        std::cout << "5 - Afiseaza date hotel (General)\n";
        std::cout << "6 - Statistici Avansate\n";
        std::cout << "0 - Back\n";

        int option = 0;
        try {
            option = askInt("Alege: ");
            clearScreen();
            if (option == 0) break;

            switch (option) {
            case 1: {
                int nr = askInt("Numar: ");
                double pret = askDouble("Pret: ");
                hotel.adaugaCamera(std::make_shared<CameraStandard>(nr, pret));
                appendOperation(kHistoryFile, "ADD_STANDARD", {std::to_string(nr), std::to_string(pret)});
                break;
            }
            case 2: {
                int nr = askInt("Numar: ");
                double pret = askDouble("Pret: ");
                double taxa = askDouble("Taxa: ");
                hotel.adaugaCamera(std::make_shared<Apartament>(nr, pret, taxa));
                appendOperation(kHistoryFile, "ADD_APARTAMENT", {std::to_string(nr), std::to_string(pret), std::to_string(taxa)});
                break;
            }
            case 3: {
                int nr = askInt("Numar: ");
                double pret = askDouble("Pret: ");
                hotel.adaugaCamera(std::make_shared<Penthouse>(nr, pret, false));
                appendOperation(kHistoryFile, "ADD_PENTHOUSE", {std::to_string(nr), std::to_string(pret)});
                break;
            }
            case 4:
                hotel.oferaPachetSpaVIP();
                appendOperation(kHistoryFile, "VIP", {});
                std::cout << "S-a aplicat VIP.\n";
                break;
            case 5:
                std::cout << hotel << '\n';
                hotel.afiseazaToateCamerele();
                break;
            case 6:
                printHotelStats(hotel);
                break;
            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        } catch (const EroareHotel& e) {
            std::cout << e.what() << '\n';
        }
    }
}

void receptionistMenu(Hotel& hotel) {
    while (true) {
        std::cout << "\n=== Receptionist Menu ===\n";
        std::cout << "1 - Vizualizare Camere Disponibile\n";
        std::cout << "2 - Forteaza Rezervare\n";
        std::cout << "3 - Afisare Detalii Actuale\n";
        std::cout << "0 - Back\n";

        int option = 0;
        try {
            option = askInt("Alege: ");
            clearScreen();
            if (option == 0) break;

            switch (option) {
            case 1:
                hotel.afiseazaToateCamerele();
                break;
            case 2: {
                int nr = askInt("Numar camera: ");
                std::string client = askToken("Nume Client: ");
                int nopti = askInt("Nopti: ");
                hotel.rezervaCamera(nr, client, nopti);
                appendOperation(kHistoryFile, "REZERVARE", {std::to_string(nr), client, std::to_string(nopti)});
                break;
            }
            case 3:
                std::cout << "Sistem functional.\n";
                break;
            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        } catch (const EroareHotel& e) {
            std::cout << e.what() << '\n';
        }
    }
}

void clientMenu(Hotel& hotel) {
    try {
        std::string userName = askToken("Nume utilizator: ");

        while (true) {
            std::cout << "\n=== Client Menu (" << userName << ") ===\n";
            std::cout << "1 - Oferta Camere\n";
            std::cout << "2 - Rezervare\n";
            std::cout << "0 - Back\n";

            int option = askInt("Alege: ");
            clearScreen();
            if (option == 0) break;

            switch (option) {
            case 1:
                hotel.afiseazaToateCamerele();
                break;
            case 2: {
                int nr = askInt("Numar dorit: ");
                int nopti = askInt("Nopti cazare: ");
                hotel.rezervaCamera(nr, userName, nopti);
                appendOperation(kHistoryFile, "REZERVARE", {std::to_string(nr), userName, std::to_string(nopti)});
                std::cout << "Procedura incheiata cu succes.\n";
                break;
            }
            default:
                std::cout << "Optiune invalida.\n";
                break;
            }
        }
    } catch (const EroareHotel& e) {
        std::cout << e.what() << '\n';
    }
}

void demonstrateFunctionality(Hotel& hotel) {
    std::cout << "\n=== DEMONSTRATION ===\n";
    
    populateDefaultRooms(hotel);

    std::cout << "\n--- Status Initial ---\n";
    std::cout << hotel << '\n';
    hotel.afiseazaToateCamerele();

    bool demoOpsOk = false;
    try {
        hotel.rezervaCamera(101, "DemoClient1", 4);
        hotel.rezervaCamera(201, "DemoClient2", 2);
        hotel.rezervaCamera(301, "DemoClientVIP", 7);
        hotel.oferaPachetSpaVIP();
        demoOpsOk = true;
    } catch (const EroareHotel& e) {
        std::cout << "Eroare in executia demonstratiei: " << e.what() << '\n';
    }

    if (!demoOpsOk) {
        std::cout << "Oprire de siguranta demo.\n";
        return;
    }

    std::cout << "\n--- Dupa Operatiuni ---\n";
    hotel.afiseazaToateCamerele();

    std::cout << "\n--- Test Copy/Assignment ---\n";
    Hotel copyByCtor(hotel);
    std::cout << "Clone test 1: " << copyByCtor << '\n';
    
    Hotel copyByAssign("Temporary");
    copyByAssign = hotel;
    std::cout << "Clone test 2: " << copyByAssign << '\n';

    printHotelStats(hotel);

    std::cout << "=== END DEMO ===\n";
}

int main() {
    std::cout << "=== Gestiune Hotel Console ===\n";
    bool terminal = 1;

    std::string hotelName;
    std::string adminName;

    if (terminal) {
        if (!loadSetup(kDataFile, hotelName, adminName)) {
            std::cout << "No valid data file found. Initial setup required.\n";
            try {
                hotelName = askToken("Nume_Hotel: ");
                adminName = askToken("Nume_Admin: ");
            } catch (const EroareHotel& e) {
                std::cout << e.what() << '\n';
                return 1;
            }

            if (!saveSetup(kDataFile, hotelName, adminName)) {
                std::cout << "Failed to create data file.\n";
                return 1;
            }
        } else {
            std::cout << "Loaded data from " << kDataFile << ".\n";
        }
    } else {
        hotelName = "Test_Hotel";
        adminName = "Test_Admin";
    }

    Hotel hotel(hotelName);

    if (!terminal) {
        demonstrateFunctionality(hotel);
        return 0;
    }

    replayOperations(kHistoryFile, hotel);

    while (terminal) {
        std::cout << "\n=== Choose Role ===\n";
        std::cout << "a - Admin\n";
        std::cout << "b - Receptionist\n";
        std::cout << "c - Client\n";
        std::cout << "d - Exit\n";

        try {
            std::string optionText = askToken("Introdu: ");
            clearScreen();
            char option = optionText[0];

            switch (option) {
            case 'a':
                adminMenu(hotel, adminName);
                break;
            case 'b':
                receptionistMenu(hotel);
                break;
            case 'c':
                clientMenu(hotel);
                break;
            case 'd':
                std::cout << "Bye.\n";
                terminal = false;
                break;
            default:
                std::cout << "Unknown option.\n";
                break;
            }
        } catch (const EroareHotel& e) {
            std::cout << e.what() << '\n';
        }
    }

    return 0;
}