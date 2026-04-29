# Proiect POO - Gestiune Hotel

## a) Enuntul problemei

Hotelul administreaza camere si rezervari care lucreaza zilnic cu clienti fizici si cu operatii interne de gestiune. In practica, datele despre camere, preturi si rezervari sunt dispersate, iar urmarirea situatiei devine dificila atunci cand volumul de operatii creste. Pentru a standardiza modul de lucru, compania doreste o aplicatie C++ in terminal care sa simuleze activitatea reala a receptiei.

Hotelul opereaza cu un sistem de camere diversificat: Standard, Apartament (care include o taxa de curatenie) si Penthouse (care poate include un pachet VIP). Aceste atribute sunt folosite la rezervari si influenteaza pretul si detaliile afisate de hotel.

In aplicatie exista trei roluri: admin, receptionist si client. Admin-ul poate adauga camere, seta taxe si activa pachete VIP. Receptionist-ul poate vizualiza oferta si poate efectua rezervari fortate in sistem. Clientul poate consulta oferta disponibila si poate initia rezervari. Fiecare operatie valida trebuie inregistrata in istoric si pastrata pentru consultare ulterioara.

Aplicatia va ilustra urmatoarele functionalitati:

1. initializarea hotelului cu nume si admin
2. adaugarea si actualizarea ofertei de camere pe tipuri (Standard, Apartament, Penthouse)
3. efectuarea rezervarilor cu validari de existenta a camerei
4. activarea pachetelor VIP exclusiv pentru Penthouse-uri
5. afisarea informatiilor disponibile pentru fiecare rol (admin, receptionist, client)
6. calculul si afisarea statisticilor generale ale hotelului
7. persistenta configurarii si a operatiilor in fisier text
8. reincarcarea datelor la rulare si continuarea sesiunilor
9. rulare in doua moduri: interactiv si demonstrativ

---

## b) Modul de rezolvare

### 1. Organizarea codului

1. fisierele `.h` contin declaratii de clase si semnaturi de functii
2. fisierele `.cpp` contin implementarile

### 2. Ierarhii si mostenire

1. ierarhie camere: `Camera` (baza) -> `CameraStandard`, `Apartament`, `Penthouse`
2. clasele baza sunt proprii proiectului, nu derivate din clase predefinite ale domeniului

### 3. Polimorfism, virtuale pure, NVI

1. in `Camera` exista functii virtuale pentru afisare si calculare detalii specifice
2. in `Camera` exista virtual pur pentru functia `clone()`
3. in `Camera` este folosita interfata non-virtuala (prin functii prieten ca `operator<<`) pentru afisarea detaliilor

### 4. Stocare polimorfica si apel prin pointer la baza

1. `Hotel` stocheaza camerele in `std::vector<std::shared_ptr<Camera>>`
2. apelurile de comportament se fac prin pointer la baza (`clone`, afisare, rezervare)

### 5. Copiere corecta

1. clasa `Hotel` are copy constructor cu clonare polimorfica a camerelor
2. operatorul de atribuire este implementat prin copy-and-swap

### 6. Downcast cu sens

1. in activarea pachetelor VIP se foloseste `std::dynamic_pointer_cast`
2. downcast-ul separa camerele de tip `Penthouse` de restul camerelor pentru a apela functia specifica `activeazaPachetVip()`

### 7. STL modern

1. `std::string` pentru campuri text
2. `std::vector` pentru colectii
3. `std::shared_ptr` pentru gestiune de memorie in ierarhia polimorfica

### 8. Exceptii proprii si tratarea erorilor

1. ierarhie de exceptii: `EroareHotel`, `EroareDateInvalide`
2. exceptiile sunt aruncate in validari si reguli de functionare
3. exceptiile sunt tratate cu `try/catch` in zonele de interactiune (`main`, meniuri, replay, demo)

### 9. Persistenta si scenarii de rulare

1. configurarea initiala si operatiile sunt salvate in fisier text
2. aplicatia poate reincarca operatiile la rulare ulterioara
3. exista mod interactiv (meniu pe roluri) si mod demonstrativ (test functional)