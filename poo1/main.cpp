#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

#define dim 1000

class Examen{
protected:
    char denumire[dim];
    double partial;
    double quiz;
    static int crt;
public:
    Examen( char sir[dim], double x = 0, double y = 0){
        strcpy(denumire, sir);
        this->partial = x;
        this->quiz = y;
        crt++;
    }

    Examen(const Examen&ob){
        strcpy(denumire, ob.denumire);
        partial = ob.partial;
        quiz = ob.quiz;
        crt = ob.crt;
    }
    virtual ~Examen(){
        denumire[0] = '\0';
        partial = 0;
        quiz = 0;
        crt--;
    }
    static int getcrt(){
        return crt;
    }
    void setO(double x){
        partial = x;
    }
    void setQ(double x){
        quiz = x;
    }
    double getO(){
        return this->partial;
    }
    double getQ(){
        return this->quiz;
    }
    char* getd(){
        return this->denumire;
    }
    void setnume(char sir[dim]){
        strcpy(denumire, sir);
    }

    Examen&operator=(const Examen& ob);
    friend istream&operator>>(istream&in, Examen& ob);

    virtual void afisare(){
        double x;
        cout<<"Materia cu numarul curent "<<crt<<" este: "<<denumire<<endl;
        cout<<"Nota la partial este(0-50 puncte): "<<partial<<endl;
        if(quiz != 0) cout<<"Nota quiz suplimentar(0-20 puncte): "<<quiz<<endl;
        cout<<"Deci nota finala la partial este: ";
            x = partial + quiz;
            cout<<x;
            if(x>50) cout<<" care se rotunjeste la 50 de puncte."<<endl;
    }
};

Examen& Examen::operator=(const Examen&ob){
    if(this==&ob) return (*this);
    strcpy(denumire, ob.denumire);
    this->partial = ob.partial;
    this->quiz = ob.quiz;
    crt = ob.crt;

    return (*this);
}

istream&operator>>(istream& in, Examen& ob){
    cout<<"Denumirea materiei la care se da examenul oral este: ";
    in>>ob.denumire;
    cout<<"Nota la examenul oral este(0-50 puncte): ";
    in>>ob.partial;

    try{
        if(ob.partial >= 25 && ob.partial <= 50) throw 1;
        else  throw "Nu";
    }
    catch(const int){
        int ok;
        cout<<"Studentul doreste sa-si mareasca nota? 1-Da 0-Nu"<<endl;
        in>>ok;
        if(ok == 1) {
            cout<<"Nota la quiz este (0-20 puncte): ";
            in>>ob.quiz;
            if(ob.quiz >20 || ob.quiz <0){
                cout<<"Ati introdus gresit nota la quiz-ul suplimentar. Va rugam sa o faceti din nou. ";
                in>>ob.quiz;
            }
        }
    }
    catch(const char *s){
        if(ob.partial > 50 || ob.partial < 0)
        {
            cout<<"Ati introdus gresit nota la examenul oral. Va rugam sa o faceti din nou. ";
            in>>ob.partial;
        }
        if(ob.partial < 25){
            ob.quiz = -1;
        }
        else{
            int ok;
            double x;
            cout<<"Studentul doreste sa-si mareasca nota? 1-Da 0-Nu";
            in>>ok;
            if(ok == 1) {
                cout<<"Nota la quiz este (0-20 puncte): ";
                in>>ob.quiz;
                if(ob.quiz >20 || ob.quiz <0){
                    cout<<"Ati introdus gresit nota la quiz-ul suplimentar. Va rugam sa o faceti din nou. ";
                    in>>ob.quiz;
                }
            }
        }
    }
    return in;
}

class ExamScris:public Examen{
    double scris;
    double punctaj;
public:
    ExamScris(double x = 0, double y = 0, char sir[dim] = NULL, double z = 0, double t = 0):Examen(sir, z, t){
        this->punctaj = y;
        this->scris = x;
    }
    ExamScris(const ExamScris&ob):Examen(ob) {
        scris = ob.scris;
        punctaj = ob.punctaj;
    }
    double getS(){
        return this->scris;
    }
    double getP(){
        return this->punctaj;
    }
    void setS(double x){
        scris = x;
    }
    void setP(double x){
        punctaj = x;
    }

    virtual ~ExamScris(){
        denumire[0] = '\0';
        scris = 0;
        punctaj = 0;
        partial = 0;
        quiz = 0;
    }

    friend istream&operator>>(istream& in, ExamScris& ob);
    ExamScris&operator=(const ExamScris&ob);

    void afisare(){
        double x = 0;
        Examen::afisare();
        cout<<"Nota examen scris: "<<scris<<endl;
        cout<<"Nota punctaj proiect(0-10 puncte): "<<punctaj<<endl;
        try{
            if((partial >=25 && scris >= 25) || (partial < 25 && scris >= 50)) throw 1;
            else throw "nu";
        }
        catch(const int){
            cout<<"Examenul a fost luat cu nota finala: ";
            if(partial >= 25){
                if(partial + quiz > 50) x = 50 + scris + punctaj;
                else x = (partial + quiz + scris) +punctaj;
            }
            else{
                x = scris + punctaj;
            }
            cout<<x/10;
            if(x>100) cout<<" care se rotunjeste la 10."<<endl;
        }
        catch(const char*){
            cout<<"Examenul nu a fost luat."<<endl;
        }
        cout<<endl;
    }

};

istream&operator>>(istream& in, ExamScris&ob){
    in>>(Examen&)ob;
    try{
        if(ob.partial < 25) throw 1;
        else throw "Da";
    }

    catch(const int){
        cout<<"Partialul nu a fost luat."<<endl;
        cout<<"Nota de la examenul scris este(0-100 puncte): ";
        in>>ob.scris;
        if(ob.scris > 100 || ob.scris < 0) {
            cout<<"Ati introdus gresit nota de la examen. Va rugam sa o faceti din nou. ";
            in>>ob.scris;
        }
        cout<<"Punctajul obtinut de la proiect este(0-10 puncte): ";
        in>>ob.punctaj;
    }
    catch(const char*){
        cout<<"Partialul a fost luat."<<endl;
        cout<<"Nota de la examenul scris este(0-50 puncte): ";
        in>>ob.scris;
        if(ob.scris > 50 || ob.scris < 0) {
            cout<<"Ati introdus gresit nota de la examen. Va rugam sa o faceti din nou. ";
            in>>ob.scris;
        }
        cout<<"Punctajul obtinut de la proiect este(0-10 puncte): ";
        in>>ob.punctaj;
    }

    return in;
}

ExamScris& ExamScris::operator=(const ExamScris& ob){
    if(this==&ob) return (*this);
    this->partial = ob.partial;
    this->quiz = ob.quiz;
    this->scris = ob.scris;
    this->punctaj = ob.punctaj;
    strcpy(denumire, ob.denumire);
    crt = ob.crt;
    return (*this);
}

int Examen::crt = 0;

template <class S>
class Catalog{
protected:
    char nume[dim];
    static int mat;
    int nrExamene;
    vector <S*> exam;
public:
    Catalog(char sir[dim] = NULL, int nr = 0){
        strcpy(nume, sir);
        nrExamene = nr;
        mat++;
    }
    Catalog(const Catalog<S> &ob){
        exam = ob.exam;
        mat = ob.mat;
        nrExamene = ob.nrExamene;
        strcpy(nume, ob.nume);
    }
    ~Catalog(){
        int i;
        for(i=0; i<nrExamene; i++){
            delete exam[i];
        }
        mat--;
    }

    Catalog<S> &operator =(const Catalog<S> &ob){
        exam = ob.exam;
        mat = ob.mat;
        nrExamene = ob.nrExamene;
        strcpy(nume, ob.nume);

        return (*this);
    }
    Catalog<S> &operator +=(S &ob){
        exam.push_back(&ob);
        return (*this);
    }

    char* getnume(){
        return nume;
    }

    int getnrexam(){
        return nrExamene;
    }

    void setnrexam(int x){
        this->nrExamene = x;
    }
    void setnume(char sir[dim]){
        strcpy(nume, sir);
    }

    void afisare(){
        try{
            if(Examen::getcrt() == 0) throw 0;
            else throw "da";
        }
        catch(const int){
            if(Examen::getcrt() == 0) cout<<"Nu au fost introduse informatii despre niciun examen. \n";
        }
        catch(const char*){
        cout<<"Studentul "<<nume<<" cu numarul matricol "<<mat<<" are urmatoarele note:"<<endl;
        int i;
        for(i=0; i<Examen::getcrt(); i++)
            if(ExamScris *s1 = dynamic_cast<ExamScris*>(exam[i]))   s1->afisare();
        }
    }
};

template<class S>
int Catalog<S>::mat = 0;

template <> class Catalog<unsigned>: public ExamScris{
	unsigned int suma;
public:
	Catalog(){
	suma = 0;}
	~Catalog(){
	suma = 0;}
	Catalog(Catalog<unsigned> &m)
	{
		suma=m.suma;
	}
	Catalog <unsigned>& operator +=(unsigned int m)
	{
		suma=suma+m;
		return *this;
	}
	void calcul_medie()
	{
		cout<<(unsigned int)suma/Examen::getcrt()<<"\n";
	}
};

void meniu(){
cout<<"1. Adaugati examen la o materie noua."<<endl;
cout<<"2. Afisati catalogul."<<endl;
}

int main(){
    char sir[dim];
    int x;

    cout<<"Numele studentului este(in cazul mai multor prenume, va rugam sa introduceti unul singur): ";
    cin.getline(sir, dim);
    cout<<"Numar examene: ";
    cin>>x;

    Catalog <ExamScris> stud(sir, x);

    meniu();
    int t;
    cout<<"Alegeti un numar."<<endl;
    cin>>t;
    while(t>=1 && t<=2){

            ExamScris *exx;
            switch(t){
             case 1:
                {
                    try{
                        if(Examen::getcrt() == stud.getnrexam()) throw 0;
                        else throw "Da";
                    }
                    catch(const int){
                        cout<<"Nu se mai poate introduce un alt examen in catalog, fiindca se va depasi numarul. \n";
                    }
                    catch(const char*){
                        exx = new ExamScris(0, 0, "", 0, 0);
                        cin>>(*exx);
                        stud += (*exx);
                    }
                }break;
             case 2:
                {
                    stud.afisare();
                }break;
            }

            cout<<"Alegeti un numar."<<endl;
            cin>>t;
    }

    int i;
    Catalog<unsigned> studi;
    for(i=0; i<Examen::getcrt(); i++){
        unsigned int x;
        cout<<"Nota este: ";
        cin>>x;
        studi += x;
    }
    studi.calcul_medie();

    return 0;
}

