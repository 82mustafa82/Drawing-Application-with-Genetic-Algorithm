#include <bits/stdc++.h>
using namespace std;

// genler
const string GENES = " *\n";

// hedef
const string TARGET = "                    \n"
                      "                    \n"
                      "                    \n"
                      "     **      **     \n"
                      "     **      **     \n"
                      "   ******  ******   \n"
                      "   ******  ******   \n"
                      "   **************   \n"
                      "   **************   \n"
                      "   **************   \n"
                      "   **************   \n"
                      "     **********     \n"
                      "     **********     \n"
                      "       ******       \n"
                      "       ******       \n"
                      "         **         \n"
                      "         **         \n"
                      "                    \n"
                      "                    \n"
                      "                    \n";

int random_num(int start, int end) // rastgele sayı üreten işlev
{
    int range = (end-start)+1; // aralık belirle
    int random_int = start+(rand()%range); // rastgele tam sayı oluştur
    return random_int; // rastgele sayıyı döndür
}

char mutated_genes() // mustasyon için rastgele gen oluşturan işlev
{
    int len = GENES.size(); // genlerin boyutunu al
    int r = random_num(0, len-1); // rastgele bir sayı seç
    return GENES[r]; // seçilen sayı indisindeki geni döndür
}

string create_gnome() // gen dizisi oluşturan işlev
{
    int len = TARGET.size(); // TARGET'ın boyutunu al
    string gnome = ""; // gnome'u ilklendir
    for(int i = 0;i<len;i++) // TARGET'ın boyutu kadar dönsün
        gnome += mutated_genes(); // gen ataması yap
    return gnome; // gnome'u döndür
}

class Individual // birey sınıfı
{
public:
    string chromosome; // kromozom
    int fitness; // uygunluk
    Individual(string chromosome);
    Individual mate(Individual parent2);
    int cal_fitness();
};

Individual::Individual(string chromosome) // yapılandırıcı
{
    this->chromosome = chromosome;  // kromozom atama
    fitness = cal_fitness(); // uygunluk atama
};

Individual Individual::mate(Individual par2) // iki eş bireyden yavru üreten işlev
{

    string child_chromosome = ""; // yavru için kromozom değeri taşıyan değişken

    int len = chromosome.size(); // kromozom boyutu
    for(int i = 0;i<len;i++)
    {
        float p = random_num(0, 100)/100; // rastgele olasılık

        if(p < 0.45) // prob 0.45'ten küçükse gen ekle
            child_chromosome += chromosome[i];

        else if(p < 0.90) // prob, 0.45 ve 0.9 arasında ise gen ekle
            child_chromosome += par2.chromosome[i];

        else // değilse, rastgele gen ekle
            child_chromosome += mutated_genes();
    }

    return Individual(child_chromosome); // yavru kromozomu kullanarak yeni birey oluşturma
};

int Individual::cal_fitness() // uygunluk puanını hesaplayan işlev
{
    int len = TARGET.size(); // hedef boyutu
    int fitness = 0; // uygunluk puanı
    for(int i = 0;i<len;i++)
    {
        if(chromosome[i] != TARGET[i])
            fitness++;
    }
    return fitness;
};

bool operator<(const Individual &ind1, const Individual &ind2) // Overloading < operator
{
    return ind1.fitness < ind2.fitness;
}

int main() // ana fonksiyon
{
    srand((unsigned)(time(0))); // sistem saati kullanılarak rastgele sayı üretilir

    int generation = 0; // geçerli jenerasyon değişkeni

    vector<Individual> population; // individual sınıfına ait vektör değişkeni
    bool found = false; // bitiş kontrol değişkeni

    for(int i = 0;i<100;i++) // başlangıç nüfusu oluşturma
    {
        string gnome = create_gnome(); // tahnmin (gnome) oluşturma
        population.push_back(Individual(gnome));
    }

    while(! found) // found 0 olduğu sürece
    {
        sort(population.begin(), population.end()); // popülasyonu artan sırada sırala

        if(population[0].fitness <= 0) // uygunluk puanı 0 olursa, döngüden çık
        {
            found = true;
            break;
        }

        vector<Individual> new_generation; // yeni jenerasyon için yeni yavrular üret

        // en uygun nüfusun %10'unu bir sonraki nesle gönder
        int s = (10*100)/100;
        for(int i = 0;i<s;i++)
            new_generation.push_back(population[i]);

        // geri kalanların en uygun %50'sinden yavru üret
        s = (90*100)/100;
        for(int i = 0;i<s;i++)
        {
            int len = population.size(); // popülasyon boyutu
            int r = random_num(0, 50); // rastgele bir tam sayı üret
            Individual parent1 = population[r]; // bir birey oluştur
            r = random_num(0, 50); // rastgele bir tam sayı üret
            Individual parent2 = population[r]; // eş birey oluştur
            Individual offspring = parent1.mate(parent2); // eş bireylerde yavru birey üret
            new_generation.push_back(offspring); // yavruyu, yeni jenerasyona ekle
        }
        population = new_generation; // yeni jenerasyonu, geçerli popülasyona ata
        if(generation % 100 == 0){
            cout<< "Generation: " << generation << "\n";
            cout<< "String: \n"<< population[0].chromosome <<"\n";
            cout<< "Fitness: "<< population[0].fitness << "\n\n";
        }


        generation++;
     }
     cout<< "Generation: " << generation << "\n";
    cout<< "String: \n"<< population[0].chromosome <<"\n";
    cout<< "Fitness: "<< population[0].fitness << "\n\n";
}
