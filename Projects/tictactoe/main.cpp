/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkej�: risti (X), nolla (0) ja tyhj� (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysyt��n koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimm�iseksi t�ytetty� peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi paattya myos sellaiseen tilanteeseen, ett� peliruudukko on
 * t�ynn� merkkej�, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pit�� olla
 * peliruudukon sis�ll�, tai koordinaatit saavat ylitty� tai alittua
 * korkeintaan yhdell�. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdell�, peliruudukko laajenee oikealle ja alasp�in. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alasp�in. Peliruudukko siis pysyy aina neli�n muotoisena.
 *   Pelin p��ttyess� kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * Ohjelman kirjoittaja
 * Nimi: Väinö Pollari, Leevi Kukkonen
 * Opiskelijanumero: H274459, H284712
 * K�ytt�j�tunnus: pollari ( Git-repositorion hakemistonimi. )
 * E-Mail: vaino.pollari@tuni.fi, leevi.kukkonen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Funktio tulostaa pelilaudan.
// Parametreinaan funktio käyttää vektoria, jonka alkiona on vektoreita.
void print_board(vector<vector<char>>& game_board, ostream& stream)
{
    int SIZE = game_board.size();
    // Rivien numeroiden tulostus:
    stream << "  ";
    for( int x = 0; x < SIZE; ++x ) {
        // 10 ja siitä yli menevät rivien nrot vain jakojäännöksinä,
        // jotta mahtuu ASCII-pelilautaan
        stream << (x + 1) % 10 << ' ';


    }
    stream << endl;



    // Tulostetaaan sarakkeiden numerot ja rivit
    for( int y = 0; y < SIZE; ++y)
    {
        //Tässä jakojäännös myös sarakkeiden numeroille
        stream << (y+1) % 10 << ' ';
        for( int x = 0; x < SIZE; ++x ) {
            stream << game_board.at(x).at(y);
            stream << " ";
        }
        stream << endl;
    }



}



// Funktio muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa arvon -1. Arvo
//-1 siksi, että kyseinen koordinaatti ei pelilaudalla ole mahdollinen. Funktio
// palauttaa arvon -2, jos pelaaja haluaa lopettaa pelin(syöttää q:n).
// Parametrinaan funktio ottaa string-muotoisen tekstin.
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else if(str == "q"){
        return -2;
    }
    else
    {
        return -1;
    }
}









//Funktio tarkistaa koordinaattien oikeellisuuden. Ottaa parametriksi pelilaudan,
// Muuntaa annetut koordinaatit kokonaisluvuiksi ja palauttaa vektorin,
//jonka alkioina ovat koordinaatit. Funktio lukee pelaajan syötteen.
// Parametrinaan funktio käyttää vuorossa olevan pelaajan merkkiä (X/0). Tämän
// lisäksi tulostaa tektin, jossa pyytää pelaajaa antamaan koordinaatit.
vector<int> coordinates (char player){
    string input = "";
    cout << "For " << player << ", enter coordinates: x y> ";
    getline(cin,input);
    string temporary;
    istringstream ss(input);
    vector<int> koordinaatit = {};

    while(getline(ss,temporary,' ')){
        koordinaatit.push_back(stoi_with_check(temporary));

    }


    return koordinaatit;
}


// Tarkistaa voiton vaakariviltä.
bool is_horizontally(const vector<vector<char>>& board, char mark)
{
    unsigned int SIZE = board.size();

    // Luodaan testivektorit, joita käytetään voiton tarkistukseen
    vector<char> test_vec;
    vector<char> win_vec(SIZE, mark);

    // Looppi käy rivi kerrallaan alkiot läpi ja lisää merkit testivektoriin
    // Jos testivektori identtinen voittovektorin kanssa, palautetaan true.
    for(unsigned int i = 0; i < SIZE; ++i )
    {
       test_vec.clear();
       for(unsigned int j = 0; j < SIZE; ++j)
       {
           test_vec.push_back(board.at(j).at(i));

       }

       // Jos molemmat testivektorit ovat identtisiä, palautetaan
       // true.
       if(test_vec == win_vec)
       {
           return true;
       }

    }

    return false;

}

// Tarkistaa voiton pystyriviltä.
bool is_vertically(const vector<vector<char>>& board, char mark)
{
    unsigned int SIZE = board.size();

    // Luodaan testivektorit, joita käytetään voiton tarkistukseen
    vector<char> win_vec(SIZE, mark); // "Voittosarake", jossa kaikki pelaajan merkkejä
    vector<char> test_vec;

    unsigned int counter = 0;

    // Looppi käy sarake kerrallaan alkiot läpi ja lisää merkit testivektoriin
    // Jos testivektori identtinen voittovektorin kanssa, palautetaan true.
    while(counter < SIZE)
    {
        test_vec.clear();
        for(unsigned int i = 0; i < SIZE; ++i )
        {
            test_vec.push_back(board.at(counter).at(i));

        }

        if(win_vec == test_vec)
        {
            return true;
        }

        ++counter;
    }

    return false;

}

// Tarkistaa voiton diagonaaleilta.
bool is_diagonally(const vector<vector<char>>& board, char mark)
{
    unsigned int SIZE = board.size();
    vector<char> test_vec;
    vector<char> win_vec(SIZE, mark);

    // Looppi käy diagonaalien alkiot läpi ja lisää merkit testivektoriin
    // Jos testivektori identtinen voittovektorin kanssa, palautetaan true.
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        test_vec.push_back(board.at(i).at(i));
    }

    if(test_vec == win_vec)
    {
        return true;
    }

    else {
        test_vec.clear();
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            test_vec.push_back(board.at(j).at(SIZE - j - 1));
        }

        if(test_vec == win_vec)
        {
            return true;
        }
    }

    return false;



}

//Voitontarkastelu, funktion palauttaa true, jos voittaja ja
// muuten palauttaa false.
// Jos palauttaa true niin funkio tulostaa ennen true-arvon
// palautusta voittotekstin (eli cross/nought won diagonally/vertically/horizontally
bool is_player_winner(const vector<vector<char>>& board, int player_turns)
{
    string player;
    char mark;
    if(player_turns % 2 == 0)
    {
        player = "Cross";
        mark = 'X';
    }

    else {
        player = "Nought";
        mark = '0';
    }

    // Rivien läpikäynti:
    if(is_horizontally(board, mark))
    {
        cout << player << " won horizontally" << endl;
        return true;
    }

    // Sarakkaeiden läpikäynti:
    else if(is_vertically(board, mark))
    {
        cout << player << " won vertically" << endl;
        return true;
    }

    // diagonaalit:
    else if(is_diagonally(board, mark))
    {
        cout << player << " won diagonally" << endl;
        return true;
    }



    return false;

}


// Funktio kutsuu muita funktioita ja pitää pelin käynnissä, kunnes
// pelaaja lopettaa pelin, jomkumpi voittaa tai pelilauta on täynnä.
void Game_loop(vector<vector<char>> board){
    // Funktiossa käytettävät muuttujat:
    bool quit = false;
    unsigned long int SIZE = board.size();
    int MAX_TURNS = SIZE * SIZE;

    bool is_winner = false;
    int turns = 0;
    char player;

    // Looppi pyörii niin kauan, kunnes
    while(is_winner == false and turns < MAX_TURNS)
    {
        SIZE = board.size();
        MAX_TURNS = SIZE * SIZE;

        // Vuorotellaan pelaajia, vuoross X tai 0 riippuen turns-muuttujan
        // arvosta.
        if(turns % 2 == 0)
        {
            player = 'X';
        }

        else {
            player = '0';
        }

        unsigned int x;
        unsigned int y;
        vector<int> coordinate_vec = coordinates(player);
        int size_coordinate = coordinate_vec.size();
        unsigned long int comparison_y;
        unsigned long int comparison_x;

        // Jos käyttäjä on syöttänyt 2 koordinaattia, ne määritetään
        // muuttujiin.
        if (size_coordinate == 2)
        {
            comparison_x = coordinate_vec.at(0);
            comparison_y = coordinate_vec.at(1);
        }

        // Jos käyttäjä on syöttänyt pelkästänn komennon 'q', katkaistaan
        // looppi. coordinates-funktio palauttaa tällöin -2.
        if(coordinate_vec.at(0) == -2 and size_coordinate == 1)
        {
            cout << "Why on earth you are giving up the game?" << endl;
            quit = true;
            break;
        }

        // Jos arvoja on liian monta:
        else if(size_coordinate != 2){
            coordinate_vec.clear();
            cout << "Coordinate outside the board " << endl;
        }

        // jos jompikumpi arvoista on liian suuria.:
        else if (comparison_y > SIZE + 1 or comparison_x > SIZE + 1){
            coordinate_vec.clear();
            cout << "Coordinate outside the board" << endl;

        }

        // Jos koordinaatit alittavat ja ylittävät samaan aikaan pelilaudan
        else if(comparison_x == SIZE + 1 and comparison_y == 0)
        {
            coordinate_vec.clear();
            cout << "Coordinate outside the board" << endl;
        }

        // Jos koordinaatit alittavat ja ylittävät samaan aikaan pelilaudan
        else if(comparison_y == SIZE + 1 and comparison_x == 0)
        {
            coordinate_vec.clear();
            cout << "Coordinate outside the board" << endl;
        }

        // Jos koordinaatit ovat hyväksytyt:
        else {
            // miinustetaan molemmista muuttujista 1, jotta sopivat yhteen
            // vektorien indeksoinnin kanssa.
            x = coordinate_vec.at(0) - 1;
            y = coordinate_vec.at(1) - 1;
            int amount = 0;
            int amount2 = 0;

            // Alla olevat 2 while-looppia tarkastavat onko syötetty kirjaimia
            while(amount < size_coordinate)
            {
                if (coordinate_vec.at(amount) == -1)
                {
                    cout << "Coordinate outside the board" << endl;
                    amount++;
                }

                else{
                    amount++;
                }
            }

            while(amount2 < size_coordinate)
            {
                if (coordinate_vec.at(amount2) == -2){
                    cout << "Coordinate outside the board" << endl;
                    amount2++;
                }
                else{
                    amount2++;
                }
            }

            // muuttuja tarkoittaa käyttäjän antamaa koordinaattia 0.
            unsigned int zero = -1;
            // Jos x ja y on laudalla, niin tarkistetaan onko paikka tyhjä. Jos
            // ei ole, niin lisätään pelaajan merkki paikalle.
            if(x < SIZE and y < SIZE)
            {

                if(board.at(x).at(y) != 'X' and board.at(x).at(y) != '0')
                {
                    board.at(x).at(y) = player;
                    print_board(board, std::cout);
                    cout << endl;
                    is_winner = is_player_winner(board, turns);
                    if(is_winner)
                    {
                        break;
                    }
                    ++turns;
                }

                else {
                    cout << "The given place is already occupied" << endl;
                }
            }


            // Pelilaudan laajennus jos VAIN TOINEN x:stä ja y:stä on yhtä isompi kuin
            // pelilaudan koko. Tämän lisäksi lisätään merkki paikalle.
            else if(x == SIZE or y == SIZE)
            {
                ++x;
                ++y;
                for(unsigned int index = 0; index < SIZE; ++index)
                {
                    board.at(index).push_back('.');
                }

                vector<char> new_row(SIZE + 1, '.');

                // tulostaa pelilaudan ja tarkistaa voiton
                board.push_back(new_row);
                board.at(x - 1).at(y - 1) = player;
                print_board(board, std::cout);
                cout << endl;
                is_winner = is_player_winner(board, turns);
                if(is_winner)
                {
                    break;
                }
                ++turns;

            }

            // Laajennus vasemmalle ja ylös:
            else if(x == zero or y == zero)
            {

                vector<char> new_row(SIZE + 1, '.');
                vector<vector<char>> temporary_board(SIZE + 1, new_row);


                if(x == zero and y != zero){
                    temporary_board.at(0).at(y+1) = player;
                }
                else if(y == zero and x != zero){
                    temporary_board.at(x+1).at(0) = player;
                }
                else{
                    temporary_board.at(0).at(0) = player;

                }

                // Kopioi alkuperäisen laudan uuteen lautaan.
                for(unsigned int i = 0; i < SIZE; ++i )
                {
                    for(unsigned int j = 0; j < SIZE; ++j)
                    {
                        temporary_board.at(i+1).at(j+1) = board.at(i).at(j);
                    }

                }
                // tulostaa pelilaudan ja tarkistaa voiton
                board = temporary_board;
                print_board(board, std::cout);
                cout << endl;
                is_winner = is_player_winner(board, turns);
                if(is_winner)
                {
                    break;
                }
                ++turns;


            }

    }

    }

    // Tulostaa tekstin, jos peli loppui tasapeliin.
    if(turns == MAX_TURNS and is_winner == false and quit == false)
    {
        cout << "No empty places" << endl;
        cout << "Game over!" << endl;
    }


    else if(quit == false)
    {
        cout << "Game over!" << endl;
    }


}




int main()
{
    cout << "Start game:" << endl;

    // Luodaan 3x3 pöytä
    vector<vector<char>> board = {{'.', '.', '.' }, {'.', '.', '.' }, {'.', '.', '.' }};

    // tulostaa pelilaudan ja kutsuu game_loop funktiota.
    print_board(board, std::cout);
    cout << endl;
    Game_loop(board);


    return EXIT_SUCCESS;
}
