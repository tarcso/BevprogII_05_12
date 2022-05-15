#include "gordmenu.hpp"
#include "menuelem.hpp"
#include "szambeall.hpp"
#include "pushbutton.hpp"
#include "Window.hpp"
#include "textbox.hpp"
#include "szovegszerk.hpp"
#include <vector>
#include <fstream>
#include <functional>

using namespace genv;

const int XX = 400;
const int YY = 600;


class Kliens
{
    private:
        std::string m_nev;

    public:
        Kliens(std::string s) : m_nev(s)
        {}

        std::string getName() const
        {
            return m_nev;
        }

};

class Car
{
    private:
        std::string m_szov;

    public:
        Car(std::string s) : m_szov(s)
        {}

        std::string getType() const
        {
            return m_szov;
        }
};

class Kiadas
{
    private:
        Car* m_c;
        Kliens* m_k;
    
    public:
        Kiadas(Kliens* k, Car* c) : m_c(c), m_k(k)
        {}

        std::string getKiad()
        {
            return m_k->getName() + ": " + m_c->getType();
        }

        std::string getCar() const
        {
            return m_c->getType();
        }

        std::string getKliens() const
        {
            return m_k->getName();
        }
};

class Allapot
{
    private:
        std::vector<Kliens*> kliensek;
        std::vector<Car*> autok;
        std::vector<Kiadas*> kiadott;

    public:
        Allapot(){}

        std::vector<std::string> getKliens()
        {
            std::vector<std::string> vec;
            for (size_t i = 0; i < kliensek.size(); i++)
            {
                vec.push_back(kliensek[i]->getName());
            }
            return vec;
        }

        std::vector<std::string> getCar()
        {
            std::vector<std::string> vec;
            for(Car* c : autok)
            {
                vec.push_back(c->getType());
            }
            return vec;
        }

        std::vector<std::string> getKiadott()
        {
            std::vector<std::string> vec;
            for(Kiadas* k : kiadott)
            {
                vec.push_back(k->getKiad());
            }
            return vec;
        }

        bool addCar(std::string s)
        {
            for (size_t i = 0; i < autok.size(); i++)
            {
                if(autok[i]->getType() == s) 
                {
                    return false;
                }
            }            
            autok.push_back(new Car(s));
            return true;
        }

        bool addKliens(std::string s)
        {   
            for (size_t i = 0; i < kliensek.size(); i++)
            {
                if(kliensek[i]->getName() == s) 
                {
                    return false;
                }
            }
            
            kliensek.push_back(new Kliens(s));
            return true;
        }

        bool addKiadas(int kliens, int car)
        {
            if(kliensek.empty()) return false;
            if(autok.empty()) return false;
            for (size_t i = 0; i < kiadott.size(); i++)
            {
                if(kiadott[i]->getKiad() ==kliensek[kliens]->getName() + ": " + autok[car]->getType()) 
                {
                    return false;
                }
            }
            kiadott.push_back(new Kiadas(kliensek[kliens], autok[car]));
            autok.erase(autok.begin() + car);
            kliensek.erase(kliensek.begin() + kliens);
            return true;
        }

        bool RemoveKiadas(int index)
        {
            if(kiadott.empty()) return false;
            addCar(kiadott[index]->getCar());
            addKliens(kiadott[index]->getKliens());
            kiadott.erase(kiadott.begin() + index);
            return true;
        }
        
};

class AutoKolcsonzo : public Window
{
    private:
        GordMenu* g1;
        GordMenu* g2;
        GordMenu* g3;
        SzovegSzerk* s1;
        SzovegSzerk* s2;
        PushButton* p1;
        PushButton* p2;
        PushButton* p3;
        PushButton* p4;
        Allapot a;

    public:
        AutoKolcsonzo()
        {
            screenx = XX;
            screeny = YY;
            a.addCar("bmw1");
            a.addCar("bmw2");
            a.addCar("bmw3");
            a.addCar("bmw4");
            a.addCar("merci");
            a.addCar("tesla");
            a.addKliens("Balazs");
            a.addKliens("Csongi");
            a.addKliens("Cili");
            a.addKiadas(0, 0);
            g3 = new GordMenu(this, 20, 220, 250, 30, "kiadott", a.getKiadott(), 3);
            g2 = new GordMenu(this, 20, 170, 250, 30, "autok", a.getCar(), 3);
            g1 = new GordMenu(this, 20, 120, 250, 30, "kliensek", a.getKliens(), 3);
            s1 = new SzovegSzerk(this, 20, 20, 250, 30);
            s2 = new SzovegSzerk(this, 20, 70, 250, 30);
            p1 = new PushButton(this, 290, 20, 100, 30, "Hozzáad", [this](){
                if(a.addKliens(s1->allapot()))
                g1->replaceVec(a.getKliens());
            });
            p2 = new PushButton(this, 290, 70, 100, 30, "Hozzáad", [this](){
                if(a.addCar(s2->allapot()))
                    g2->replaceVec(a.getCar());
            });
            p3 = new PushButton(this, 290, 120, 100, 80, "Elviszi", [this](){
                if(a.addKiadas(g1->allapot(), g2->allapot()))
                {
                    g1->replaceVec(a.getKliens());
                    g2->replaceVec(a.getCar());
                    g3->replaceVec(a.getKiadott());
                }
            });
            p4 = new PushButton(this, 290, 220, 100, 30, "Visszahoz", [this](){

                if(a.RemoveKiadas(g3->allapot()))
                {
                    g1->replaceVec(a.getKliens());
                    g2->replaceVec(a.getCar());
                    g3->replaceVec(a.getKiadott());
                }
            });
            
        }

        void esemeny(const std::string& ki_mondta)
        {}
};

int main()
{
    gout.open(XX, YY);
    gout.load_font("LiberationSans-Regular.ttf");
    AutoKolcsonzo* k = new AutoKolcsonzo;
    k->event_loop();
    return 0;
}
