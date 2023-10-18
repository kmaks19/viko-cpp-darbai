#include <iostream>
#include <cstring>

using namespace std;

const char LT_ABC_ARRAY[32] = // Abëcëlë saugojama masyve.
{
    'A', 'À', 'B', 'C', 'È', 'D', 'E', 'Æ', 'Ë', 'F', 'G', 'H', 'I', 'Á', 'Y', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'Ð', 'T', 'U', 'Ø', 'Û', 'V', 'Z', 'Þ'
};

const char ASCII_ARRAY[94] =
{
    '!', '\u0021', '#', '$', '%', '&', '\u0027', '(', ')', '*', '+', ',', '-', \
    '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', \
    ':', ';', '<', '=', '>', '?', '@', \
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', \
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\u005C', ']', '^', \
    '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', \
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~'
};

bool IsUsingAllowedSymbols(const char WordArray[], const char ABC_Array[], const int abc_word_count, const int WordArray_word_count)
{
    int x = 0;
    for(int i = 0; i < WordArray_word_count; i++)
    {
        for (int j = 0; j < abc_word_count; j++)
        {
            if (WordArray[i] == ABC_Array[j])
            {
                x++;
                continue;
            }
        }
    }
    if(x == WordArray_word_count) return true;
    else return false;
}

void Encrypt(const char M[], const char K[], char C[], const int n, const int masyvo_ilgis, const int koduote)
{
    // Koduote = 1 - LT
    // Koduote = 2 - ASCII
    for(int i = 0; i < masyvo_ilgis; i++)
    {
        int number_M = 0, number_K = 0;// Kintamieji kurie nurodis pradinio zodzio ir ðifravimo þodþio raides vieta LT_ABC_ARRAY masyve.

        for(int j = 0; j < n; j++)
        {
            switch(koduote)
            {
                case 1:
                {
                    if(LT_ABC_ARRAY[j] == M[i]) number_M = j; // Jeigu abeceles masyve sutampa su pradinio zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)

                    if(LT_ABC_ARRAY[j] == K[i]) number_K = j; // Jeigu abeceles masyve sutampa su ðifravimo zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)
                }
                case 2:
                {
                    if(ASCII_ARRAY[j] == M[i]) number_M = j; // Jeigu abeceles masyve sutampa su pradinio zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)

                    if(ASCII_ARRAY[j] == K[i]) number_K = j; // Jeigu abeceles masyve sutampa su ðifravimo zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)
                }
            }
        }

        int galutinis_skaicius; // Galutinis rezultatas
        galutinis_skaicius = (number_M + number_K) % n; // Sifruojame raide formules c(itasis) = M-itasis+K-itasis(mod n)

        switch(koduote) {
            case 1:
            {
                C[i] = LT_ABC_ARRAY[galutinis_skaicius]; // Áraðome atitinkamà raidæ á C masyvà.
                break;
            }
            case 2:
            {
                C[i] = ASCII_ARRAY[galutinis_skaicius];
                break;
            }
        }
    }
    cout << "Uþðifruotas þodis: ";
    for(int zx = 0; zx < masyvo_ilgis; zx++)
        cout << C[zx];
}

void Decrypt(char M[], const char K[], const int n, const int masyvo_ilgis, const int koduote)
{
    // Koduote = 1 - LT
    // Koduote = 2 - ASCII
    int pozicija_masyve_pradinio, pozicija_masyve_slaptojo_rakto;

    for(int i = 0; i < masyvo_ilgis; i++)
    {
        for(int j = 0; j < n; j++)
        {
            switch(koduote)
            {
                case 1:
                {
                    if(LT_ABC_ARRAY[j] == M[i]) pozicija_masyve_pradinio = j;

                    if(LT_ABC_ARRAY[j] == K[i]) pozicija_masyve_slaptojo_rakto = j;
                }
                case 2:
                {
                    if(ASCII_ARRAY[j] == M[i]) pozicija_masyve_pradinio = j;

                    if(ASCII_ARRAY[j] == K[i]) pozicija_masyve_slaptojo_rakto = j;
                }
            }

        }

        int galutinis_skaicius = pozicija_masyve_pradinio - pozicija_masyve_slaptojo_rakto + (n%n);
        /* Formulë ið esmës veiktø taèiau, bûna, jog pirmasis skaièius bûna maþas, atëmus jis ágyja neigiamà reikðmæ, todël nesigauna þodis
         * Todël reikia tikrinti ar jis maþesnis uþ 0 atëmus, jeigu taip tai yra bûdas prie skaièiaus, kuris reiðkia kiek ið viso þodþiø yra abëcëlëje pridëjus neigiamà skaièiø,
         * yra gaunamas teisingas rezultatas (reikiamos raidës pozicija skaitmenimis), kurià apaèioje áraðome á masyvà. */
        if(galutinis_skaicius < 0) galutinis_skaicius = n+(galutinis_skaicius);

        switch(koduote)
        {
            case 1:
            {
                M[i] = LT_ABC_ARRAY[galutinis_skaicius];
                break;
            }
            case 2:
            {
                M[i] = ASCII_ARRAY[galutinis_skaicius];
                break;
            }
        }
    }
    cout << "Deðifruotas þodis: ";
    for(int zx = 0; zx < masyvo_ilgis; zx++)
        cout << M[zx];
}

int main() {
    system("chcp 1257");

    cout << "Ðifravimo deðifravimo sistema\n";
    cout << "Pasirinkite: \n";
    cout << "1 - uþðifruoti tekstà \n";
    cout << "2 - deðifruoti tekstà \n";

    int choice;

    cin >> choice;

    if(choice > 2)
    {
        cout << "[KLAIDA]: Tokio meniu pasirinkimo nëra!";
        return 0;
    }

    cout << "Pasirinkite: \n";
    cout << "1 - LT abëcëlë \n";
    cout << "2 - ASCII koduotë \n";

    int koduote, n;

    cin >> koduote;

    switch(koduote)
    {
        case 1:
        {
            n = sizeof(LT_ABC_ARRAY); // Lietuviø abëcëleje yra 32 þodþiai. Dydis priklausys nuo abëcëlës masyvo.
            break;
        }
        case 2:
        {
            n = sizeof(ASCII_ARRAY);
            break;
        }
        default:
        {
            cout << "[KLAIDA]: Toks koduotës pasirinkimas negalimas (neegzistuoja)!";
            return 0;
        }
    }

    char M_TEMP[50] = {0};

    cout << "Áveskite pradiná tekstà (ne ilgesnis negu 50 simboliø): ";

    cin >> M_TEMP;

    if(strlen(M_TEMP) > 50) cout << "[KLAIDA]: Pradinio teksto ilgis negali bûti didesnis negu 50 simboliø!";

    /*
        * Þemiau ðio komentaro: Gauname þodþio ilgá, kurá naudosime naujam pradinio teksto masyvo ilgiui nustatyti, taipogi ðifravimo rakto maksimaliam ilgiui nustatyti,
        * kadangi bus þinomas pradinio teksto ilgis
    */

    int array_length = strlen(M_TEMP);


    char M_PERMA[array_length]; // Nuolatinis masyvas, kuriame saugojamas pradinis tekstas.

    if(koduote != 2) // Jeigu ne ASCII.
    {
        for(int ax = 0; ax < array_length; ax++)
        {
            M_PERMA[ax] = M_TEMP[ax]; // Perkeliame tekstà ið laikino masyvo á nuolatiná masyvà.
            M_PERMA[ax] = toupper(M_PERMA[ax]); // Teksto raides pakeièiame didþiosiomis.
        }
    }
    else
    {
        for(int ax = 0; ax < array_length; ax++)
            M_PERMA[ax] = M_TEMP[ax];
    }
    /* Tikriname ar pradiniame tekste nëra nesusijusiø simboliø su tam tikra abëcële */

    if(!IsUsingAllowedSymbols( M_PERMA, LT_ABC_ARRAY, n, array_length) )
    {
        cout << "[KLAIDA]: Pradiniame þodyje yra neleistinø simboliø! (t.y kurie nepriklauso abëcëlei)";
        return 0;
    }

    char K[array_length];

    cout << "Áveskite ðifravimo raktà " << "(jis negali bûti ilgesnis nei " << array_length << " simboliai):";

    cin >> K;

    if(strlen(K) > array_length) {
        cout << "[KLAIDA]: Ðifravimo rakto ilgis negali bûti ilgesnis uþ pradinio teksto ilgá " << "t.y " << array_length << " negu simboliø (-ai)";
        return 0;
    }

    if(koduote != 2) // Jeigu ne ASCII
    {
        for(int zx = 0; zx < array_length; zx++) {
            K[zx] = toupper(K[zx]);
        }
    }

    if(strlen(K) < array_length) // Jeigu ðifravimo raktas trumpesnis uþ pradinio teksto ilgá
    {
        // Tuomet dapildome ðifravimo rakta jo pradiniais simboliais pvz.: Pradinis zodis LABAS, o ðifravimo raktas yra KEY, tuomet jis atrodys KEYKE
        int x = 0; // Raides pozicija is ðifravimo rakto raides, t.y eina nuo 0, kad zinoti kuria raide reikia prideti prie masyvo.
        for(int i = strlen(K); i <= array_length; i++)
        {
            if(K[x] == K[i-1])
            {
                x++;
                K[i] = K[x];
            }
            else
            {
                K[i] = K[x];
                x++;
            }
        }
    }

    if(!IsUsingAllowedSymbols( K, LT_ABC_ARRAY, n, array_length ) )
    {
        cout << "[KLAIDA]: Ðifravimo rakte yra neleistinø simboliø (t.y kurie nepriklauso abëcëlei)";
        return 0;
    }

    char C[array_length]; // Uþðifruoto teksto masyvas.


    switch(koduote)
    {
        case 1: // LT
        {
            switch(choice)
            {
                case 1:  // ENCRYPT
                {
                    Encrypt(M_PERMA, K, C, n, array_length, 1); // Sifruojame pasirinkta zodi (iskvieciame funkcija)
                    break;
                }
                case 2: // DECRYPT
                {
                    Decrypt(M_PERMA, K, n, array_length, 1); // Issifruojame pasirinkta zodi (iskvieciame funkcija)
                    break;
                }
            }
            break;
        }
        case 2: // ASCII
        {
            switch(choice)
            {
                case 1:
                {
                    Encrypt(M_PERMA, K, C, n, array_length, 2);
                    break;
                }
                case 2:
                {
                    Decrypt(M_PERMA, K, n, array_length, 2);
                    break;
                }
            }
        }
        break;
    }
    return 0;
}
