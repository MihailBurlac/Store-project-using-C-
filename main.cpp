#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Produs {
public:
    int id;
    string nume, descriere;
    double discount;
    double pret_intreg, pret_discount;

    virtual void calculDiscount() = 0;

    bool operator==(const Produs &produs) const {
        bool result;
        result = false;
        if (id == produs.id)
            result = true;
        return result;
    }
};

class Laptopuri : public Produs {
public:
    void calculDiscount() override {
        pret_discount = pret_intreg - pret_intreg * discount / 100;
    }

    Laptopuri() = default;

    Laptopuri(int Nid, string Ndescriere, double Ndiscount, double Npret) {
        id = Nid;
        nume = "Laptopuri";
        descriere = Ndescriere;
        pret_intreg = Npret;
        discount = Ndiscount;
    }
};

class Telefoane : public Produs {
public:
    void calculDiscount() override {
        pret_discount = pret_intreg - pret_intreg * discount / 100;
    }

    Telefoane() = default;

    Telefoane(int Nid, string Ndescriere, double Ndiscount, double Npret) {
        id = Nid;
        nume = "Telefoane";
        descriere = Ndescriere;
        pret_intreg = Npret;
        discount = Ndiscount;
    }
};

class Periferice : public Produs {
public:
    void calculDiscount() override {
        pret_discount = pret_intreg - pret_intreg * discount / 100;
    }

    Periferice() = default;

    Periferice(int Nid, string Ndescriere, double Ndiscount, double Npret) {
        id = Nid;
        nume = "Laptopuri";
        descriere = Ndescriere;
        pret_intreg = Npret;
        discount = Ndiscount;
    }
};

class Comanda {
public:
    vector<Produs *> produse;
    int secunda, minuta, ora, ziua, luna, anul;
    string stare;

    void getTime() {
        time_t now = time(nullptr);
        struct tm *local = localtime(&now);
        ora = local->tm_hour;
        minuta = local->tm_min;
        secunda = local->tm_sec;
        ziua = local->tm_mday;
        luna = local->tm_mon + 1;
        anul = local->tm_year + 1900;
    }
};

int main() {
    while (true) {
        cout << "Tastati C + tasta Enter pentru a adauga o comanda noua" << endl
             << "R + tasta Enter pentru a vizualiza optiunile de rapoarte" << endl
             << "A + tasta Enter pentru a anula o comanda plasata in urma cu 30 de zile" << endl
            << "Pentru a opri programul, scrieti 'exit'"<<endl;
        string cerinta;
        while (true) {
            cin >> cerinta;
            if (cerinta != "C" && cerinta != "R" && cerinta != "A" && cerinta !="exit") {
                cout << "Introduceti o cerinta valida!" << endl;
                continue;
            } else
                break;
        }
        if(cerinta=="exit"){
            break;
        } else
        if (cerinta == "C") {
            Comanda comanda;
            while (true) {
                ofstream f("comenzi.txt", ios::app);
                ifstream fin("comenzi.txt");
                string helper, helper2;
                vector<Comanda> comenzi;
                while (fin >> helper) {
                    Comanda comanda_plasata;
                    fin >> helper >> helper >> helper >> helper;
                    stringstream ss;
                    ss << helper;
                    getline(ss, helper2, ':');
                    comanda_plasata.ora = stoi(helper2);
                    getline(ss, helper2, ':');
                    comanda_plasata.minuta = stoi(helper2);
                    getline(ss, helper2, ':');
                    comanda_plasata.secunda = stoi(helper2);
                    ss.clear();
                    fin >> helper;
                    ss << helper;
                    getline(ss, helper2, '/');
                    comanda_plasata.ziua = stoi(helper2);
                    getline(ss, helper2, '/');
                    comanda_plasata.luna = stoi(helper2);
                    getline(ss, helper2, '/');
                    comanda_plasata.anul = stoi(helper2);
                    fin >> helper;
                    comanda_plasata.stare = helper;
                    int id;
                    while (true) {
                        string descriere, nume;
                        float discount, pret_intreg, pret_discount;
                        fin >> id >> nume >> descriere;
                        fin >> helper >> helper >> helper;
                        fin >> pret_intreg;
                        fin >> helper >> helper >> helper >> helper;
                        fin >> pret_discount;
                        fin >> helper >> helper;
                        fin >> discount;
                        if (nume == "Laptopuri") {
                            comanda_plasata.produse.push_back(new Laptopuri(id, descriere, discount, pret_intreg));
                        }
                        if (nume == "Telefoane") {
                            comanda_plasata.produse.push_back(new Telefoane(id, descriere, discount, pret_intreg));
                        }
                        if (nume == "Periferice") {
                            comanda_plasata.produse.push_back(new Periferice(id, descriere, discount, pret_intreg));
                        }
                        fin >> helper;
                        if (helper.size() == 2)
                            break;
                    }
                    comenzi.push_back(comanda_plasata);

                }
                for (int i = 0; i < comenzi.size(); i++) {
                    for (int j = 0; j < comenzi[i].produse.size(); j++) {
                        comenzi[i].produse[j]->calculDiscount();
                    }
                }
                /*for (auto it: comenzi) {
                    cout << it.ora << " " << it.minuta << " " << it.secunda << " " << it.ziua << " " << it.luna
                         << " "
                         << it.anul << endl;
                    for (auto x: it.produse) {
                        cout << x->nume << " " << x->id << " " << x->descriere << " " << x->pret_intreg << " "
                             << x->pret_discount << " " << x->discount << endl;
                    }
                }*/
                int id;
                string nume, descriere;
                double pret, discount;
                cout << "Apasati tasta Enter dupa fiecare valoare introdusa!" << endl;
                cout << "Categorie (1 pentru Laptopuri, 2 pentru Telefoane, 3 pentru Periferice  + tasta Enter):";
                while (true) {
                    cin >> nume;
                    if (nume == "1") {
                        nume = "Laptopuri";
                        break;
                    } else if (nume == "2") {
                        nume = "Telefoane";
                        break;
                    } else if (nume == "3") {
                        nume = "Periferice";
                        break;
                    } else
                        cout << "Introduceti o categorie valida!" << endl;
                }
                cout << "id (>=1000 EX: 1234 + Enter):";
                while (true) {
                    cin >> id;
                    int k = 1;
                    for (auto &i: comenzi) {
                        for (auto &j: i.produse) {
                            if (id == j->id) {
                                k = 0;
                            }
                        }
                    }
                    for (auto &it: comanda.produse) {
                        if (id == it->id) {
                            k = 0;
                        }
                    }
                    if (k == 0) {
                        cout << "Introduceti un id diferit fata de cele inregistrate!" << endl;
                        continue;
                    }
                    if (id < 1000) {
                        cout << "Introduceti un id mai mare de 1000!" << endl;
                    } else {
                        break;
                    }
                }
                cout << "Descriere (Fara spatii):";
                getchar();
                while (true) {
                    getline(cin, descriere);
                    if (descriere.empty()) {
                        cout << "Introduceti o descriere valida!" << endl;
                        continue;
                    }
                    int k = 0;
                    for (char i: descriere) {
                        if (i == ' ') {
                            k++;
                            cout << "Introduceti o descriere fara spatii!" << endl;
                            break;
                        }
                    }
                    if (k == 0)
                        break;
                }
                cout << "Pret (EX: 1250 + Enter):";
                cin >> pret;
                cout << "Discount (in % EX: 15 + Enter):";
                cin >> discount;
                cout << endl;
                if (nume == "Laptopuri") {
                    comanda.produse.push_back(new Laptopuri(id, descriere, discount, pret));
                }
                if (nume == "Telefoane") {
                    comanda.produse.push_back(new Telefoane(id, descriere, discount, pret));
                }
                if (nume == "Periferice") {
                    comanda.produse.push_back(new Periferice(id, descriere, discount, pret));
                }
                cout << "Daca doriti sa mai introduceti alte produse in aceasta comanda, tastati C + tasta Enter"
                     << endl;
                cout
                        << "Daca doriti sa incheiati comanda, tastati 1, 2 sau 3 + tasta Enter in functie de starea comenzii"
                        << endl;
                cout << "1 pentru ~Neplasata~, 2 pentru ~In procesare~, 3 ~pentru Livrata~ " << endl;
                string conditie;
                cin >> conditie;
                if (conditie == "C") {
                    continue;
                } else if (conditie == "1" || conditie == "2" || conditie == "3") {
                    switch (conditie[0]) {
                        case '1': {
                            comanda.stare = "Neplasata";
                            break;
                        }
                        case '2': {
                            comanda.stare = "In_procesare";
                            break;
                        }
                        case '3': {
                            comanda.stare = "Livrata";
                            break;
                        }
                    }
                    comanda.getTime();
                    f << endl << "Comanda din data de ";
                    f << comanda.ora << ":" << comanda.minuta << ":" << comanda.secunda << " " << comanda.ziua
                      << "/"
                      << comanda.luna << "/" << comanda.anul << " " << comanda.stare << endl;
                    for (int i = 0; i < comanda.produse.size(); i++) {
                        comanda.produse[i]->calculDiscount();
                    }
                    for (int i = 0; i < comanda.produse.size() - 1; i++) {
                        f << comanda.produse[i]->id << " " << comanda.produse[i]->nume << " "
                          << comanda.produse[i]->descriere << "   Pret fara discount: "
                          << comanda.produse[i]->pret_intreg
                          << " LEI   Pret cu discount: " << comanda.produse[i]->pret_discount << " LEI   Discount "
                          << comanda.produse[i]->discount
                          << "%" << endl;
                    }
                    f << comanda.produse[comanda.produse.size() - 1]->id << " "
                      << comanda.produse[comanda.produse.size() - 1]->nume << " "
                      << comanda.produse[comanda.produse.size() - 1]->descriere << "   Pret fara discount: "
                      << comanda.produse[comanda.produse.size() - 1]->pret_intreg
                      << " LEI   Pret cu discount: " << comanda.produse[comanda.produse.size() - 1]->pret_discount
                      << " LEI   Discount " << comanda.produse[comanda.produse.size() - 1]->discount
                      << "%%" << endl;
                    cout << "Comanda cu id-ul " << id << " fost inregistrata cu succes la ora " << comanda.ora
                         << ":"
                         << comanda.minuta << ":" << comanda.secunda << " in data de " << comanda.ziua << "/"
                         << comanda.luna
                         << "/" << comanda.anul << endl;
                    f.close();
                    fin.close();
                    break;
                }
            }
        }
        if (cerinta == "R") {
            while (true) {
                ofstream f("comenzi.txt", ios::app);
                ifstream fin("comenzi.txt");
                string helper, helper2;
                vector<Comanda> comenzi;
                while (fin >> helper) {
                    Comanda comanda_plasata;
                    fin >> helper >> helper >> helper >> helper;
                    stringstream ss;
                    ss << helper;
                    getline(ss, helper2, ':');
                    comanda_plasata.ora = stoi(helper2);
                    getline(ss, helper2, ':');
                    comanda_plasata.minuta = stoi(helper2);
                    getline(ss, helper2, ':');
                    comanda_plasata.secunda = stoi(helper2);
                    ss.clear();
                    fin >> helper;
                    ss << helper;
                    getline(ss, helper2, '/');
                    comanda_plasata.ziua = stoi(helper2);
                    getline(ss, helper2, '/');
                    comanda_plasata.luna = stoi(helper2);
                    getline(ss, helper2, '/');
                    comanda_plasata.anul = stoi(helper2);
                    fin >> helper;
                    comanda_plasata.stare = helper;
                    int id;
                    while (true) {
                        string descriere, nume;
                        float discount, pret_intreg, pret_discount;
                        fin >> id >> nume >> descriere;
                        fin >> helper >> helper >> helper;
                        fin >> pret_intreg;
                        fin >> helper >> helper >> helper >> helper;
                        fin >> pret_discount;
                        fin >> helper >> helper;
                        fin >> discount;
                        if (nume == "Laptopuri") {
                            comanda_plasata.produse.push_back(new Laptopuri(id, descriere, discount, pret_intreg));
                        }
                        if (nume == "Telefoane") {
                            comanda_plasata.produse.push_back(new Telefoane(id, descriere, discount, pret_intreg));
                        }
                        if (nume == "Periferice") {
                            comanda_plasata.produse.push_back(new Periferice(id, descriere, discount, pret_intreg));
                        }
                        fin >> helper;
                        if (helper.size() == 2)
                            break;
                    }
                    comenzi.push_back(comanda_plasata);

                }
                for (int i = 0; i < comenzi.size(); i++) {
                    for (int j = 0; j < comenzi[i].produse.size(); j++) {
                        comenzi[i].produse[j]->calculDiscount();
                    }
                }
                cout
                        << "~~Pentru a vizualiza toate comenzile, tastati S total + tasta Enter"
                        << endl;
                cout
                        << endl
                        << "~~Pentru a afisa raportul preturilor pentru o anumita luna si an, scrieti S luna anul urmat de 1, 2 sau 3 functie de starea comenzii + tasta Enter"
                        << endl;
                cout << "1 pentru ~Neplasata~, 2 pentru ~In_procesare~, 3 pentru ~Livrata~ " << endl;
                cout << "-EX-: Pentru comenzile livrate a lunii ianuarie 2022 vom scrie: S 1 2022 3" << endl;
                cout
                        << endl
                        << "~~Pentru a afisa raportul preturilor pentru un anumit an, scrieti S anul urmat de 1, 2 sau 3 functie de starea comenzii + tasta Enter"
                        << endl;
                cout << "-EX-: Pentru comenzile neplasate din anul 2022 vom scrie: S 2022 1" << endl;
                cout
                        << endl
                        << "~~Pentru a afisa raportul preturilor pentru o anumita categorie, scrieti S T, L, sau P urmat de 1, 2 sau 3 functie de starea comenzii + tasta Enter"
                        << endl;
                cout << "T pentru ~Telefoane~, L pentru ~Laptopuri~, P pentru ~Periferice~ " << endl;
                cout << "-EX-: Pentru comenzile de laptopuri livrate vom scrie: S L 3" << endl;
                cout << "~~Pentru a va intoarce in meniul principal, tastai B + tasta Enter" << endl;
                int k=0;
                while (true) {
                    cin >> cerinta;
                    if (cerinta == "B") {
                        k=1;
                        break;
                    } else if (cerinta != "S") {
                        cout << "Introduceti un cod de vizualizare a rapoartelor corect!" << endl;
                    } else break;
                }
                if(k==1){
                    break;
                } else
                if (cerinta == "S") {
                    float sum = 0;
                    int produse = 0, comenzi_ = 0;
                    string helper3, helper4, helper5;
                    cin >> helper3;
                    if (helper3 == "total") {
                        for (int j = 0; j < comenzi.size(); j++) {
                            cout << endl << "Comanda din data de ";
                            cout << comenzi[j].ora << ":" << comenzi[j].minuta << ":" << comenzi[j].secunda << " "
                                 << comenzi[j].ziua << "/"
                                 << comenzi[j].luna << "/" << comenzi[j].anul << " " << comenzi[j].stare << endl;
                            for (int i = 0; i < comenzi[j].produse.size(); i++) {
                                cout << comenzi[j].produse[i]->id << " " << comenzi[j].produse[i]->nume << " "
                                     << comenzi[j].produse[i]->descriere << "   Pret fara discount: "
                                     << comenzi[j].produse[i]->pret_intreg
                                     << " LEI   Pret cu discount: " << comenzi[j].produse[i]->pret_discount
                                     << " LEI   Discount "
                                     << comenzi[j].produse[i]->discount
                                     << "%" << endl;
                            }
                        }
                    } else if (helper3.size() <= 2 && helper3 != "L" && helper3 != "T" && helper3 != "P") {
                        cin >> helper5 >> helper4;
                        if (helper4 == "1") {
                            helper4 = "Neplasata";
                        } else if (helper4 == "2") {
                            helper4 = "In_procesare";
                        } else if (helper4 == "3") {
                            helper4 = "Livrata";
                        }
                        int luna, anul;
                        luna = stoi(helper3);
                        anul = stoi(helper5);
                        for (auto &i: comenzi) {
                            if (i.luna == luna && i.stare == helper4 && i.anul == anul) {
                                comenzi_++;
                                for (auto j: i.produse) {
                                    sum += j->pret_discount;
                                    produse++;
                                }
                            }
                        }
                        cout << "Luna ~" << luna << "~ a anului ~" << anul << "~ a inregistrat un numar de " << comenzi_
                             << " comenzi cu starea ~" << helper4 << "~, acestea continand " << produse
                             << " produse in valoare de " << sum
                             << " LEI avand o medie de " << (double) sum / produse << " LEI" << endl;
                    } else if (helper3.size() == 4) {
                        cin >> helper4;
                        if (helper4 == "1") {
                            helper4 = "Neplasata";
                        } else if (helper4 == "2") {
                            helper4 = "In_procesare";
                        } else if (helper4 == "3") {
                            helper4 = "Livrata";
                        }
                        int anul;
                        anul = stoi(helper3);
                        for (auto &i: comenzi) {
                            if (i.anul == anul && i.stare == helper4) {
                                comenzi_++;
                                for (auto j: i.produse) {
                                    sum += j->pret_discount;
                                    produse++;
                                }
                            }
                        }
                        cout << "Anul ~" << anul << "~ a inregistrat un numar de " << comenzi_
                             << " comenzi cu starea ~" << helper4 << "~, acestea continand " << produse
                             << " produse in valoare de " << sum
                             << " LEI avand o medie de " << (double) sum / produse << " LEI" << endl;
                    } else if (helper3 == "L" || helper3 == "T" || helper3 == "P") {
                        cin >> helper4;
                        if (helper4 == "1") {
                            helper4 = "Neplasata";
                        } else if (helper4 == "2") {
                            helper4 = "In_procesare";
                        } else if (helper4 == "3") {
                            helper4 = "Livrata";
                        }
                        if (helper3 == "T") {
                            helper3 = "Telefoane";
                        } else if (helper3 == "L") {
                            helper3 = "Laptopuri";
                        } else if (helper3 == "P") {
                            helper3 = "Periferice";
                        }
                        for (auto i: comenzi) {
                            for (auto j: i.produse) {
                                if (j->nume == helper3 && i.stare == helper4) {
                                    sum += j->pret_discount;
                                    produse++;
                                }
                            }
                        }
                        cout << "Categoria ~" << helper3 << "~ cu starea ~" << helper4
                             << "~, a inregistrat un numar de " << produse
                             << " produse in valoare de " << sum
                             << " LEI avand o medie de " << (double) sum / produse << " LEI" << endl;
                    } else {
                        cout << "Introduceti un cod de vizualizare a rapoartelor corect!" << endl;
                    }
                    cout << endl << "~Pentru a vizualiza alte rapoarte, tastati R + tasta Enter" << endl;
                    cout
                            << "~Pentru a incheia vizualizarea si a va intoarce in meniul principal, tastati E + tasta Enter"
                            << endl;
                    string conditie;
                    cin >> conditie;
                    if (conditie == "R") {
                        continue;
                    } else if (conditie == "E") {
                        cout << "Rapoartele au fost inchise cu succes!" << endl;
                        break;
                    }
                }
                f.close();
                fin.close();
            }

        }
        if (cerinta == "A") {
            while (true) {
                ofstream f("comenzi.txt", ios::app);
                ifstream fin("comenzi.txt");
                string helper, helper2;
                vector<Comanda> comenzi;
                while (fin >> helper) {
                    Comanda comanda_plasata;
                    fin >> helper >> helper >> helper >> helper;
                    stringstream ss;
                    ss << helper;
                    getline(ss, helper2, ':');
                    comanda_plasata.ora = stoi(helper2);
                    getline(ss, helper2, ':');
                    comanda_plasata.minuta = stoi(helper2);
                    getline(ss, helper2, ':');
                    comanda_plasata.secunda = stoi(helper2);
                    ss.clear();
                    fin >> helper;
                    ss << helper;
                    getline(ss, helper2, '/');
                    comanda_plasata.ziua = stoi(helper2);
                    getline(ss, helper2, '/');
                    comanda_plasata.luna = stoi(helper2);
                    getline(ss, helper2, '/');
                    comanda_plasata.anul = stoi(helper2);
                    fin >> helper;
                    comanda_plasata.stare = helper;
                    int id;
                    while (true) {
                        string descriere, nume;
                        float discount, pret_intreg, pret_discount;
                        fin >> id >> nume >> descriere;
                        fin >> helper >> helper >> helper;
                        fin >> pret_intreg;
                        fin >> helper >> helper >> helper >> helper;
                        fin >> pret_discount;
                        fin >> helper >> helper;
                        fin >> discount;
                        if (nume == "Laptopuri") {
                            comanda_plasata.produse.push_back(new Laptopuri(id, descriere, discount, pret_intreg));
                        }
                        if (nume == "Telefoane") {
                            comanda_plasata.produse.push_back(new Telefoane(id, descriere, discount, pret_intreg));
                        }
                        if (nume == "Periferice") {
                            comanda_plasata.produse.push_back(new Periferice(id, descriere, discount, pret_intreg));
                        }
                        fin >> helper;
                        if (helper.size() == 2)
                            break;
                    }
                    comenzi.push_back(comanda_plasata);

                }
                for (int i = 0; i < comenzi.size(); i++) {
                    for (int j = 0; j < comenzi[i].produse.size(); j++) {
                        comenzi[i].produse[j]->calculDiscount();
                    }
                }
                cout
                        << "Pentru a anula o comanda inregistrata in urma cu cel tarziu 30 de zile, introduceti id-ul a cel putin un produs din acea comanda + tasta Enter"
                        << endl;
                cout << "Sau introduceti id-ul 0 pentru a opri anularea" << endl;
                f.close();
                fin.close();
                ofstream fout("comenzi.txt");
                string stid;
                int r = 1;
                while (true) {
                    int ziua, luna, anul;
                    time_t now = time(nullptr);
                    struct tm *local = localtime(&now);
                    ziua = local->tm_mday;
                    luna = local->tm_mon + 1;
                    anul = local->tm_year + 1900;
                    cin >> stid;
                    if (stid == "0") {
                        r = 2;
                        break;
                    }
                    int id;
                    id = stoi(stid);
                    int k = 0;
                    for (int i = 0; i < comenzi.size(); i++) {
                        for (int j = 0; j < comenzi[i].produse.size(); j++) {
                            if (comenzi[i].produse[j]->id == id) {
                                if (((ziua + luna * 30.4 + anul * 365.25) -
                                     (comenzi[i].ziua + comenzi[i].luna * 30.4 + comenzi[i].anul * 365.25)) > 30) {
                                    r = 0;
                                    cout
                                            << "Comanda a fost plasata intr-un interval mai mare de 30 de zile, deci nu poate fi anulata!"
                                            << endl;

                                    break;
                                }
                                k++;
                                comenzi.erase(comenzi.begin() + i);
                            }
                        }
                    }
                    if (k == 0 && r == 1) {
                        cout << "Introduceti un id valid!" << endl;
                        cout << "Sau introduceti id-ul 0 pentru a opri anularea" << endl;
                    } else
                        break;
                }

                for (int j = 0; j < comenzi.size(); j++) {
                    fout << endl << "Comanda din data de ";
                    fout << comenzi[j].ora << ":" << comenzi[j].minuta << ":" << comenzi[j].secunda << " "
                         << comenzi[j].ziua << "/"
                         << comenzi[j].luna << "/" << comenzi[j].anul << " " << comenzi[j].stare << endl;
                    for (int i = 0; i < comenzi[j].produse.size() - 1; i++) {
                        fout << comenzi[j].produse[i]->id << " " << comenzi[j].produse[i]->nume << " "
                             << comenzi[j].produse[i]->descriere << "   Pret fara discount: "
                             << comenzi[j].produse[i]->pret_intreg
                             << " LEI   Pret cu discount: " << comenzi[j].produse[i]->pret_discount
                             << " LEI   Discount "
                             << comenzi[j].produse[i]->discount
                             << "%" << endl;
                    }
                    fout << comenzi[j].produse[comenzi[j].produse.size() - 1]->id << " "
                         << comenzi[j].produse[comenzi[j].produse.size() - 1]->nume << " "
                         << comenzi[j].produse[comenzi[j].produse.size() - 1]->descriere
                         << "   Pret fara discount: "
                         << comenzi[j].produse[comenzi[j].produse.size() - 1]->pret_intreg
                         << " LEI   Pret cu discount: "
                         << comenzi[j].produse[comenzi[j].produse.size() - 1]->pret_discount
                         << " LEI   Discount " << comenzi[j].produse[comenzi[j].produse.size() - 1]->discount
                         << "%%" << endl;
                }
                if (r == 1)
                    cout << "Comanda a fost anulata cu succes!" << endl;
                if (r == 2)
                    cout << "Anularea a fost anulata cu succes! :)" << endl;
                cout << "Pentru a anula alta coamanda tastati A + Enter" << endl
                     << "Pentru a incheia aceasta sesiune, tastati E + Enter" << endl;
                string conditie;
                cin >> conditie;
                if (conditie == "A") {
                    continue;
                } else if (conditie == "E") {
                    cout << "Sesiunea a fost incheiata cu succes!" << endl;
                    fout.close();
                    break;
                }
            }
        }
    }
    return 0;
}
