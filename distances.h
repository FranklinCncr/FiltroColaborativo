#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <ctime>
using namespace std;

struct nodo{
       string name;
       string element;
       double rating;
       struct nodo *sgte;
};
typedef struct nodo *Tlista;

void inser(Tlista &lista,string n, string str, double r){
    Tlista q;
    q = new(struct nodo);
    q->name = n;
    q->element = str;
    q->rating = r;
    q->sgte=lista;
    lista  = q;
}
void print(Tlista &lista)
{
    Tlista temp=lista;
    while(temp != NULL){
          std::cout << temp->name <<" "<<temp->element<<" "<<temp->rating<< endl;
          temp = temp->sgte;
    }
}

void destruc(Tlista &lista)
{
     Tlista sig;
     sig=NULL;
     while(lista != NULL)
     {
        sig=lista->sgte;
        delete(lista);
        lista=sig;
     }
}
void fillList(Tlista &listin,string name, string bd, string type){
    ifstream file;
    string strBD ="E:/Proyectos/QT/TBD2/"+bd+"/"+type+"/"+name+".csv";
    file.open(strBD);
    char cadena[40];
    string element,rating;

    file>>cadena;
    element=cadena;
    file>>cadena;
    rating=cadena;
    while(rating!=element){
        inser(listin, name, element, atof(rating.c_str()));
        file>>cadena;
        element=cadena;
        file>>cadena;
        rating=cadena;

    }
    file.close();
}
void fillListMaxMin(Tlista &listin,string name, string bd, string type, double &max, double &min){
    ifstream file;
    string strBD ="E:/Proyectos/QT/TBD2/"+bd+"/"+type+"/"+name+".csv";
    file.open(strBD);
    char cadena[40];
    double numrating;
    string element,rating;

    file>>cadena;
    element=cadena;
    file>>cadena;
    rating=cadena;
    while(rating!=element){
        numrating = atof(rating.c_str());
        inser(listin, name, element, numrating);
        if(numrating>max){
            max=numrating;
        }
        if(numrating<min){
            min=numrating;
        }
        file>>cadena;
        element=cadena;
        file>>cadena;
        rating=cadena;
    }
    file.close();
}
void normalize(Tlista &lista, Tlista &listin,double max,double min){
    Tlista temp=lista;
    double ratingNorm=0;
    while(temp != NULL){
          ratingNorm =(2*(temp->rating-min)-(max-min))/(max-min);
          inser(listin, temp->name, temp->element, ratingNorm);
          temp = temp->sgte;
    }
}
double dev(Tlista &L1, Tlista &L2, int &cont){
    Tlista temp=L1;
    Tlista temp2=L2;
    double sum=0;
    while(temp != NULL){
          while(temp2 !=NULL){
            if(temp->element == temp2->element){
                sum+=temp->rating - temp2->rating;
                cont++;
            }
            temp2=temp2->sgte;
          }
          temp2 = L2;
          temp = temp->sgte;
    }
    if(cont!=0){
       sum=sum/cont;
    }
    else{
        sum=0;
    }

    return sum;
}
double promedio(string name, string db){
    ifstream file;
    string strBD ="E:/Proyectos/QT/TBD2/"+db+"/"+"user"+"/"+name+".csv";
    file.open(strBD);
    char cadena[40];
    double ratingprom=0;
    int cont=0;
    string element,rating;

    file>>cadena;
    element=cadena;
    file>>cadena;
    rating=cadena;
    while(rating!=element){
        ratingprom+=atof(rating.c_str());
        cont++;
        file>>cadena;
        element=cadena;
        file>>cadena;
        rating=cadena;
    }
    file.close();
    ratingprom=ratingprom/cont;
    return ratingprom;
}

double cosAjus(Tlista &L1, Tlista &L2, string db){
    Tlista temp=L1;
    Tlista temp2=L2;
    double sumN=0,sumD1=0,sumD2=0;
    double prom=0;
    while(temp != NULL){
          while(temp2 !=NULL){
            if(temp->element == temp2->element){
                prom=promedio(temp->element,db);
                sumN+=(temp->rating - prom)*(temp2->rating-prom);
                sumD1+=pow(temp->rating-prom,2);
                sumD2+=pow(temp2->rating-prom,2);
            }
            temp2=temp2->sgte;
          }
          temp2 = L2;
          temp = temp->sgte;
    }    
    sumD1=sqrt(sumD1)*sqrt(sumD2);
    if(sumD1!=0){
        sumN=sumN/sumD1;
    }
    else{
        sumN=0;
    }
    return sumN;
}

double cosenoAjustado(string bd,string bduser, string bditem){
    Tlista listUser = NULL;
    Tlista listUserNorm = NULL;
    Tlista listItem = NULL;
    double max=-99,min=99;

    fillListMaxMin(listUser,bduser,bd,"user",max,min);    
    fillList(listItem,bditem,bd,"item");
    normalize(listUser,listUserNorm,max,min);

    Tlista temp= listUserNorm;
    Tlista listItemTemp = NULL;
    double sumN=0;
    double sumD=0;
    double cos=0;

    while(temp != NULL){
        fillList(listItemTemp,temp->element,bd,"item");
        cos=cosAjus(listItem,listItemTemp,bd);
        sumN+= (temp->rating*cos);
        sumD+= abs(cos);
        destruc(listItemTemp);
        temp=temp->sgte;
    }
    sumN=sumN/sumD;
    sumN=0.5*((sumN+1)*(max-min))+min;
    return sumN;
}
double euclidiana(string bd,string bduser, string bduser2){
    Tlista listUser = NULL;
    Tlista listUser2 = NULL;

    fillList(listUser,bduser,bd,"user");
    fillList(listUser2,bduser2,bd,"user");

    Tlista Temp = NULL;
    Tlista Temp2 = NULL;
    Temp=listUser;
    Temp2=listUser2;
    double sumN=0;
    while(Temp!=NULL){
        while(Temp2!=NULL){
            if(Temp->element==Temp2->element){
                sumN+=pow(Temp->rating-Temp2->rating,2);
            }
            Temp2=Temp2->sgte;
        }
        Temp=Temp->sgte;
    }
    sumN=sqrt(sumN);

    return sumN;
}
double slopOne(string bd,string bduser, string bditem){
    Tlista listUser = NULL;
    Tlista listItem = NULL;
    fillList(listUser,bduser,bd,"user");
    fillList(listItem,bditem,bd,"item");

    Tlista temp= listUser;
    Tlista listItemTemp = NULL;
    double sumN=0;
    double sumD=0;
    int cont=0;
    double devVal=0;

    while(temp != NULL){
        fillList(listItemTemp,temp->element,bd,"item");
        devVal=dev(listItem,listItemTemp,cont);
        sumN+= (temp->rating+devVal)*cont;
        sumD+= cont;
        cont=0;
        destruc(listItemTemp);
        temp=temp->sgte;
    }    
    sumN=sumN/sumD;
    return sumN;
}
bool noexiste(string db, string name){
    char cadena[40];
    ifstream file;
    file.open(db);

    string act,ant;

    file.open(db);
    file>>cadena;
    ant=cadena;
    if(ant==name){
        return false;
    }
    cout<<ant<<endl;
    file>>cadena;

    act=cadena;
    if(act==name){
        return false;
    }
    cout<<act<<endl;
    while(ant!=act){
        act=ant;
        file>>cadena;
        act=cadena;
        if(act==name){
            return false;
        }
        cout<<act<<endl;
    }
    return true;
    file.close();

}
double jaccard(string bd,string bduser, string bduser2){
    Tlista listUser = NULL;
    Tlista listUser2 = NULL;

    fillList(listUser,bduser,bd,"user");
    fillList(listUser2,bduser2,bd,"user");

    Tlista Temp = NULL;
    Tlista Temp2 = NULL;
    Temp=listUser;
    Temp2=listUser2;
    double cont1=0;
    double cont2=0;
    while(Temp!=NULL){
        while(Temp2!=NULL){
            if(Temp->element==Temp2->element){
                cont1++;
            }
            Temp2=Temp2->sgte;
            cont2++;
        }
        Temp=Temp->sgte;
    }
    cont1=cont1/cont2;

    return cont1;
}
double pearson(string bd,string bduser, string bduser2){
    Tlista listUser = NULL;
    Tlista listUser2 = NULL;

    fillList(listUser,bduser,bd,"user");
    fillList(listUser2,bduser2,bd,"user");

    Tlista Temp = NULL;
    Tlista Temp2 = NULL;
    Temp=listUser;
    Temp2=listUser2;
    double sumN=0;
    double sumD=0;
    while(Temp!=NULL){
        while(Temp2!=NULL){
            if(Temp->element==Temp2->element){
                sumN+=(Temp->rating-Temp->rating)*(Temp2->rating-Temp2->rating);
                sumD+=pow(Temp->rating-Temp->rating,2)*pow(Temp->rating-Temp->rating,2);
            }
            Temp2=Temp2->sgte;
        }
        Temp=Temp->sgte;
    }
    sumD=sqrt(sumN);
    sumN=sumN/sumD;
    return sumN;
}
double minkowsky(string bd,string bduser, string bduser2){
    Tlista listUser = NULL;
    Tlista listUser2 = NULL;

    fillList(listUser,bduser,bd,"user");
    fillList(listUser2,bduser2,bd,"user");

    Tlista Temp = NULL;
    Tlista Temp2 = NULL;
    Temp=listUser;
    Temp2=listUser2;
    double sumN=0;
    while(Temp!=NULL){
        while(Temp2!=NULL){
            if(Temp->element==Temp2->element){
                sumN+=pow(Temp->rating-Temp2->rating,2);
            }
            Temp2=Temp2->sgte;
        }
        Temp=Temp->sgte;
    }
    sumN=sqrt(sumN);

    return sumN;
}
double coseno(string bd,string bduser, string bduser2){
    Tlista listUser = NULL;
    Tlista listUser2 = NULL;

    fillList(listUser,bduser,bd,"user");
    fillList(listUser2,bduser2,bd,"user");

    Tlista Temp = NULL;
    Tlista Temp2 = NULL;
    Temp=listUser;
    Temp2=listUser2;
    double sumN=0;
    while(Temp!=NULL){
        while(Temp2!=NULL){
            if(Temp->element==Temp2->element){
                sumN+=pow(Temp->rating-Temp2->rating,2);
            }
            Temp2=Temp2->sgte;
        }
        Temp=Temp->sgte;
    }
    sumN=sqrt(sumN);

    return sumN;
}
double manhatan(string bd,string bduser, string bduser2){
    Tlista listUser = NULL;
    Tlista listUser2 = NULL;

    fillList(listUser,bduser,bd,"user");
    fillList(listUser2,bduser2,bd,"user");

    Tlista Temp = NULL;
    Tlista Temp2 = NULL;
    Temp=listUser;
    Temp2=listUser2;
    double sumN=0;
    while(Temp!=NULL){
        while(Temp2!=NULL){
            if(Temp->element==Temp2->element){
                sumN+=abs(Temp->rating-Temp2->rating);
            }
            Temp2=Temp2->sgte;
        }
        Temp=Temp->sgte;
    }

    return sumN;
}
