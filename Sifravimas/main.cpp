#include <iostream>
#include <cstring>

using namespace std;

const char LT_ABC_ARRAY[32] = // Ab�c�l� saugojama masyve.
{
    'A', '�', 'B', 'C', '�', 'D', 'E', '�', '�', 'F', 'G', 'H', 'I', '�', 'Y', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', '�', 'T', 'U', '�', '�', 'V', 'Z', '�'
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
        int number_M = 0, number_K = 0;// Kintamieji kurie nurodis pradinio zodzio ir �ifravimo �od�io raides vieta LT_ABC_ARRAY masyve.

        for(int j = 0; j < n; j++)
        {
            switch(koduote)
            {
                case 1:
                {
                    if(LT_ABC_ARRAY[j] == M[i]) number_M = j; // Jeigu abeceles masyve sutampa su pradinio zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)

                    if(LT_ABC_ARRAY[j] == K[i]) number_K = j; // Jeigu abeceles masyve sutampa su �ifravimo zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)
                }
                case 2:
                {
                    if(ASCII_ARRAY[j] == M[i]) number_M = j; // Jeigu abeceles masyve sutampa su pradinio zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)

                    if(ASCII_ARRAY[j] == K[i]) number_K = j; // Jeigu abeceles masyve sutampa su �ifravimo zodzio X-aja raide priskiriame lygiam jo vietai masyve (pozicija pvz. U = 26)
                }
            }
        }

        int galutinis_skaicius; // Galutinis rezultatas
        galutinis_skaicius = (number_M + number_K) % n; // Sifruojame raide formules c(itasis) = M-itasis+K-itasis(mod n)

        switch(koduote) {
            case 1:
            {
                C[i] = LT_ABC_ARRAY[galutinis_skaicius]; // �ra�ome atitinkam� raid� � C masyv�.
                break;
            }
            case 2:
            {
                C[i] = ASCII_ARRAY[galutinis_skaicius];
                break;
            }
        }
    }
    cout << "U��ifruotas �odis: ";
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
        /* Formul� i� esm�s veikt� ta�iau, b�na, jog pirmasis skai�ius b�na ma�as, at�mus jis �gyja neigiam� reik�m�, tod�l nesigauna �odis
         * Tod�l reikia tikrinti ar jis ma�esnis u� 0 at�mus, jeigu taip tai yra b�das prie skai�iaus, kuris rei�kia kiek i� viso �od�i� yra ab�c�l�je prid�jus neigiam� skai�i�,
         * yra gaunamas teisingas rezultatas (reikiamos raid�s pozicija skaitmenimis), kuri� apa�ioje �ra�ome � masyv�. */
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
    cout << "De�ifruotas �odis: ";
    for(int zx = 0; zx < masyvo_ilgis; zx++)
        cout << M[zx];
}

int main() {
    system("chcp 1257");

    cout << "�ifravimo de�ifravimo sistema\n";
    cout << "Pasirinkite: \n";
    cout << "1 - u��ifruoti tekst� \n";
    cout << "2 - de�ifruoti tekst� \n";

    int choice;

    cin >> choice;

    if(choice > 2)
    {
        cout << "[KLAIDA]: Tokio meniu pasirinkimo n�ra!";
        return 0;
    }

    cout << "Pasirinkite: \n";
    cout << "1 - LT ab�c�l� \n";
    cout << "2 - ASCII koduot� \n";

    int koduote, n;

    cin >> koduote;

    switch(koduote)
    {
        case 1:
        {
            n = sizeof(LT_ABC_ARRAY); // Lietuvi� ab�c�leje yra 32 �od�iai. Dydis priklausys nuo ab�c�l�s masyvo.
            break;
        }
        case 2:
        {
            n = sizeof(ASCII_ARRAY);
            break;
        }
        default:
        {
            cout << "[KLAIDA]: Toks koduot�s pasirinkimas negalimas (neegzistuoja)!";
            return 0;
        }
    }

    char M_TEMP[50] = {0};

    cout << "�veskite pradin� tekst� (ne ilgesnis negu 50 simboli�): ";

    cin >> M_TEMP;

    if(strlen(M_TEMP) > 50) cout << "[KLAIDA]: Pradinio teksto ilgis negali b�ti didesnis negu 50 simboli�!";

    /*
        * �emiau �io komentaro: Gauname �od�io ilg�, kur� naudosime naujam pradinio teksto masyvo ilgiui nustatyti, taipogi �ifravimo rakto maksimaliam ilgiui nustatyti,
        * kadangi bus �inomas pradinio teksto ilgis
    */

    int array_length = strlen(M_TEMP);


    char M_PERMA[array_length]; // Nuolatinis masyvas, kuriame saugojamas pradinis tekstas.

    if(koduote != 2) // Jeigu ne ASCII.
    {
        for(int ax = 0; ax < array_length; ax++)
        {
            M_PERMA[ax] = M_TEMP[ax]; // Perkeliame tekst� i� laikino masyvo � nuolatin� masyv�.
            M_PERMA[ax] = toupper(M_PERMA[ax]); // Teksto raides pakei�iame did�iosiomis.
        }
    }
    else
    {
        for(int ax = 0; ax < array_length; ax++)
            M_PERMA[ax] = M_TEMP[ax];
    }
    /* Tikriname ar pradiniame tekste n�ra nesusijusi� simboli� su tam tikra ab�c�le */

    if(!IsUsingAllowedSymbols( M_PERMA, LT_ABC_ARRAY, n, array_length) )
    {
        cout << "[KLAIDA]: Pradiniame �odyje yra neleistin� simboli�! (t.y kurie nepriklauso ab�c�lei)";
        return 0;
    }

    char K[array_length];

    cout << "�veskite �ifravimo rakt� " << "(jis negali b�ti ilgesnis nei " << array_length << " simboliai):";

    cin >> K;

    if(strlen(K) > array_length) {
        cout << "[KLAIDA]: �ifravimo rakto ilgis negali b�ti ilgesnis u� pradinio teksto ilg� " << "t.y " << array_length << " negu simboli� (-ai)";
        return 0;
    }

    if(koduote != 2) // Jeigu ne ASCII
    {
        for(int zx = 0; zx < array_length; zx++) {
            K[zx] = toupper(K[zx]);
        }
    }

    if(strlen(K) < array_length) // Jeigu �ifravimo raktas trumpesnis u� pradinio teksto ilg�
    {
        // Tuomet dapildome �ifravimo rakta jo pradiniais simboliais pvz.: Pradinis zodis LABAS, o �ifravimo raktas yra KEY, tuomet jis atrodys KEYKE
        int x = 0; // Raides pozicija is �ifravimo rakto raides, t.y eina nuo 0, kad zinoti kuria raide reikia prideti prie masyvo.
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
        cout << "[KLAIDA]: �ifravimo rakte yra neleistin� simboli� (t.y kurie nepriklauso ab�c�lei)";
        return 0;
    }

    char C[array_length]; // U��ifruoto teksto masyvas.


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
