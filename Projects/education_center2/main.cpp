//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

/* Kurssikeskus
 *
 * Kuvaus:
 *   Ohjelma lukee kurssikeskuksen tiedot tietorakenteeseen: ohjelmaan on sisälletty
 *   käyttöliittymä, jonka abulla käyttäjä voi komennosta riippuen hakea erilaisia tietoja
 *   kursseihin liittyen.
 *   Käyttäjän täytyy syöttää määrtelmien mukainen tiedosto, jotta kurssien tietoihin
 *   pääsy olisi mahdollista. Jos tiedosto on virheellinen, antaa ohjelma siitä virheilmoituksen ja lopettaa
 *   ohjelman suorittamisen.
 *   Ohjelma antaa myös virheilmoitukset käyttäjälle, jos komennot tai niihin liittyvät
 *   parametrit ovat virheellisiä. Tällöin ohjelma kuitenkin antaa käyttäjän syöttää komennot
 *   uudelleeen. Ohjelman loppuu tällöi vasta käyttäjän syötettyä komento = "quit".
 *
 * Ohjelman kirjoittanut:
 * Nimet: Leevi Kukkonen (H284712) ja Väinö Pollari (H274459)
 * Sähköpostit: leevi.kukkonen@tuni.fi & vaino.pollari@tuni.fi
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ostream>


//Kurssi olio joka sisältää kaikki sen tiedot
using namespace std;
struct Course{
    string name;
    string location;
    int enrollments;
};

//Vertailee kahta string tyypin muuttujaa
bool compareFunction(string a, string b){
    return a<b;
}


//Funktio saa parametrikseen listan teemoista ja tulostaa ne kaikki
void print_themes(const vector<string> themes_list){
    vector<string> sorted_themes=themes_list;
    sort(sorted_themes.begin(),sorted_themes.end(),compareFunction);
    for (unsigned int i = 0; i<sorted_themes.size();++i){
        cout << sorted_themes[i]<<endl;
    }
}

//Funktio palauttaa totuusarvon sen perusteella löytääkö se teeman mapista
bool find_theme(const map <string,vector<Course>> themes, const string theme_to_find)
{
    if(themes.find(theme_to_find) != themes.end())
    {
        return true;
    }
    else {
        return false;
    }
}


bool is_location_in_map(const map<string, vector<Course>> themes, string location)
{
    map<string, vector<Course>> copy_map = themes;
    map <string,vector<Course>>::iterator iter;
    iter = copy_map.begin();

    string locationToCheck = location;
    bool in_map = false;

    while(iter != copy_map.end()){
        unsigned int index = 0;
        while(index < copy_map.at(iter->first).size()){
            if(copy_map.at(iter->first).at(index).location == locationToCheck){
                in_map = true;
                index += 1;
            }
            else {
                index += 1;
            }
        }
        ++iter;
    }

    return in_map;
}

//Funktio saa parametreikseen käyttäjän syötteen, sekä oliot sisältävän mapin.
//Se tulostaa kaikki yhdessä kaupungissa järjestettävät kurssit
void print_courses_in_the_city(const map <string,vector<Course>> themes,const string location, string theme){
    map<string,int> sorted_courses;
    vector<string> sorted_names;
    string theme2 = theme;
    const char somechar ='"';
    unsigned int empty = 0;

    if (theme2.front() == somechar and theme2.back()== somechar){
        theme2.pop_back();
        theme2.replace(0,1,"");

    }
    // Etsitään teema
    bool theme_exist = find_theme(themes, theme2);
    // Selviettän alla olevan totuusarvon avulla, että
    // onko paikkakunta map:ssa.
    bool location_exist = is_location_in_map(themes, location);

    if(location_exist == true and theme_exist == true)
    {
        for (unsigned int i = 0; i < themes.at(theme2).size(); ++i){
                if(themes.at(theme2)[i].location == location){
                    sorted_courses.insert({themes.at(theme2)[i].name,themes.at(theme2)[i].enrollments});
                    sorted_names.push_back(themes.at(theme2)[i].name);
                }
            }
    }



    // Seuraavaksi käydään läpi virhetilanteet, jos mikään näistä ei toteudu
    // niin tulostetaan kurssit
    if(theme_exist == false and location_exist == false)
    {
        cout << "Error: unknown theme" << endl;
    }

    else if(theme_exist == false and location_exist == true)
    {
        cout << "Error: unknown theme" << endl;
    }

    else if(theme_exist == true and location_exist == false)
    {
        cout << "Error: unknown location" << endl;
    }


    else if(sorted_courses.size() == empty)
    {
        cout << " Error: unknown location" << endl;
    }

    else {
        sort(sorted_names.begin(),sorted_names.end(),compareFunction);
        for(unsigned int i=0;i<sorted_names.size();++i){
            if(sorted_courses.at(sorted_names[i])<50){
                cout << sorted_names[i]<< " --- "<<sorted_courses.at(sorted_names[i])<<" enrollments"<<endl;

            }
            else{
                cout << sorted_names[i]<< " --- full"<<endl;
            }
        }
    }

}

//Funktio saa parametreikseen oliot sisältävän mapin ja tulostaa kaikkien olioiden
//Kurssin nimi ominaisuuden.
void available_courses(const map <string,vector<Course>> themes){
    map <string,vector<Course>> copy_of_themes = themes;
    map <string,vector<Course>>::iterator iter;
    vector<string> alphabetical_order;
    iter = copy_of_themes.begin();
    while(iter != copy_of_themes.end()){
        unsigned int a = 0;
        while(a<copy_of_themes.at(iter->first).size()){
            if(copy_of_themes.at(iter->first)[a].enrollments<50){
                string row = iter->first + " : "+copy_of_themes.at(iter->first)[a].location+" : "+copy_of_themes.at(iter->first)[a].name;
                vector<string>::iterator check;
                check = find(alphabetical_order.begin(),alphabetical_order.end(),row);
                if (check == alphabetical_order.end()){
                    alphabetical_order.push_back(row);
                }
            }
            a += 1;
        }
        ++iter;
    }
    sort(alphabetical_order.begin(),alphabetical_order.end(),compareFunction);
    for(unsigned int i = 0;i<alphabetical_order.size();++i){
        cout << alphabetical_order[i]<<endl;
    }

}

//Funktio saa käyttäjän syötteen, sekä oliomapin parametreikseen ja tulostaa
//Kaikki yhden teeman all jäävät kurssit
void courses_in_theme(const map <string,vector<Course>> themes, const string theme_name){
    map <string,vector<Course>> copy_of_themes = themes;
    vector<string> alphabetical_order (2, " ");
    map <string,vector<Course>>::iterator iter;
    iter = copy_of_themes.begin();
    multimap<string,string> test;

    while(iter != copy_of_themes.end()){
        unsigned int a = 0;
        while(a < copy_of_themes.at(iter->first).size()){
            if(iter->first == theme_name){
                string location = copy_of_themes.at(iter->first)[a].location;
                string name = copy_of_themes.at(iter->first)[a].name;


                auto check = test.equal_range(location);

                if (check.first->second == name and check.first->first == location)
                {
                //Automaattitesterin kanssa oli hieman ongelmia, tämä oli ensimmäinen
                    //tapa jolla se hyväksyi funktion outputin.
                    //Tyhjä if lause poistaa kahteen kertaan esiintyvät kurssit
                }

                else {
                    test.insert({location, name});

                }

            }
            a += 1;
        }
        ++iter;
    }

    multimap <string,string>::iterator iter_two;
    iter_two = test.begin();

    while(iter_two != test.end())
    {
        cout << iter_two->first << " : " << iter_two->second << endl;
        ++iter_two;
    }

}

//Tulostaa kaikki yhdessä kaupungissa järjestettävät kurssit

void courses_in_location(const map <string,vector<Course>> themes, const string location){
    vector<string> alphabetical_courses;
    map <string,vector<Course>> copy_of_themes = themes;
    map <string,vector<Course>>::iterator iter;
    iter = copy_of_themes.begin();
    while(iter != copy_of_themes.end()){
        unsigned int a = 0;
        while(a < copy_of_themes.at(iter->first).size()){
            if(copy_of_themes.at(iter->first)[a].location == location){
                string course = copy_of_themes.at(iter->first)[a].name;
                vector<string>::iterator check;
                check = find(alphabetical_courses.begin(),alphabetical_courses.end(),course);
                if (check == alphabetical_courses.end()){
                    alphabetical_courses.push_back(course);
                }
            }
            a += 1;
        }
        ++iter;
    }

    if(alphabetical_courses.size() == 0)
    {
        cout << "Error: unknown location" << endl;
    }

    else {
            sort(alphabetical_courses.begin(), alphabetical_courses.end());
            for(string course_name : alphabetical_courses)
            {
                cout << course_name << endl;
            }

    }
}

//Tulostaa suosituimman kurssin nimen ja sen kuinka monta osallistujaa niillä on
void favorite_theme(map<string,vector<Course>>courses){
    vector <string> already_checked_themes;
    map <string,vector<Course>> copy_of_courses = courses;
    map <string,vector<Course>>::iterator iter;

    map <string,int> themes;
    map <string, int>::iterator it;
    iter = copy_of_courses.begin();

    while(iter != copy_of_courses.end()){
        unsigned int index = 0;
        while(index < copy_of_courses.at(iter->first).size()){
            string theme = iter->first;
            int enrollments = copy_of_courses.at(iter->first).at(index).enrollments;
            vector<string>::iterator check;
            check = find(already_checked_themes.begin(),already_checked_themes.end(),theme);

            if(check == already_checked_themes.end()){
                already_checked_themes.push_back(theme);

                it = themes.find(theme);

                if (it != themes.end()){
                    it->second += enrollments;
                    themes.insert({theme, enrollments});
                }
                else{
                    themes.insert({theme, enrollments});
                }
            }
            else {
                themes.at(theme) += enrollments;
            }

            index += 1;
        }

        ++iter;
    }

    map <string, int>::iterator itera;
    itera = themes.begin();
    int current_max = 0;

    while(itera != themes.end())
    {
        if(itera->second >= current_max)
        {
            current_max = itera->second;
        }
        ++itera;
    }

    // Tarkistetaan, että missä teemoissa on eniten osallistujia ja
    // tallenetaan ne listaan
    map <string, int>::iterator check_iter;
    check_iter = themes.begin();
    vector <string> favorite_themes;

    while(check_iter != themes.end())
    {
        if(check_iter->second == current_max)
        {
            favorite_themes.push_back(check_iter->first);
        }
        ++check_iter;
    }

    // Tulostetaan suosituimmat listat
    if(current_max > 0)
    {
        cout << current_max << " enrollments in themes" << endl;
    }
    else {
        cout << "No enrollments" << endl;
    }
    for(auto theme_name : favorite_themes)
    {
        cout << "--- " << theme_name << endl;
    }
}

// Poistaa yhden kurssin kaikista olioista
map <string,vector<Course>> cancel_course(const map <string,vector<Course>> themes,const string course_name){
    map <string,vector<Course>> copy_of_themes = themes;
    map <string,vector<Course>>::iterator iter;
    iter = copy_of_themes.begin();
    string courseToFind = course_name;

    while(iter != copy_of_themes.end()){
        unsigned int index = 0;
        while(index < copy_of_themes.at(iter->first).size()){
            if(copy_of_themes.at(iter->first).at(index).name == courseToFind){
                copy_of_themes.at(iter->first).erase(copy_of_themes.at(iter->first).begin() + index);
            }
            else {
                index += 1;
            }
        }
        ++iter;
    }

    cout << course_name << " cancelled in all locations" << endl;
    return copy_of_themes;

}


bool is_course_in_map(const map<string, vector<Course>> themes, string course_name)
{
    map<string, vector<Course>> copy_map = themes;
    map <string,vector<Course>>::iterator iter;
    iter = copy_map.begin();

    string courseToCheck = course_name;
    bool in_map = false;

    while(iter != copy_map.end()){
        unsigned int index = 0;
        while(index < copy_map.at(iter->first).size()){
            if(copy_map.at(iter->first).at(index).name == courseToCheck){
                in_map = true;
                index += 1;
            }
            else {
                index += 1;
            }
        }
        ++iter;
    }

    return in_map;
}

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.

vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

bool check_fields(const vector<string>& row)
{
    vector <string> line = row;
    if(line.at(3) == "full")
    {
        line.at(3) = "50";
    }

    for(string alkio : line)
    {
        if(alkio == "")
        {
            return true;
        }
    }

    if(line.size() < 4)
    {
        return true;
    }

    if(stoi(line.at(3)) < 1)
    {
        return true;
    }

    else {
        return false;
    }
}

//Avaa tiedoston, jakaa sen mappiin, kutsuu muita funktioita ja käsittelee käyttäjän
//komennot.
bool handler(){
    //Input filen nimi, tarkistetaan onko se oikeanlainen
    cout << "Input file: ";
    string filename;
    getline(cin,filename);
    ifstream file(filename);

    map <string,vector<Course>> themes;
    vector<string> themes_list;
    if (! file){
        cout << "Error: the input file cannot be opened"<<endl;
        return false;
    }


    else{
        //Luetaan tiedosto ja isketään se map+struct rakenteeseen. Tämän jakamisen hoitaa
        //split funktio
        string row;
        while(getline(file,row)){
            vector<string> words;
            Course add;
            string delimiter = ";";
            words = split(row, delimiter);
            bool is_field_empty = check_fields(words);
            if(is_field_empty)
            {
                cout << "Error: empty field" << endl;
                return false;
            }
            else {
                if (words[3]=="full"){
                    add = {words[1],words[2],50};
                }
                else{
                    add = {words[1],words[2],stoi(words[3])};
                }
                if (themes.find(words[0])!=themes.end()){
                    themes.at(words[0]).push_back(add);
                }
                else{
                    themes.insert({words[0],{add}});
                    themes_list.push_back(words[0]);
                }
            }

        }
    }


    cout << "> ";
    string command;
    getline(cin,command);
    //Game loop, voisi olla oma funktionsa. Tässä annetaan komennot, tallennetaan
    //ne vektoriin ja kutsutaan funktioita niiden perusteella
    // Alla olevalla iteraattorilla voi tehdä virhetarkastelua

    while(command != "quit"){
        vector<string> splitted_command;
        splitted_command = split(command," ");
        if(splitted_command.size()==4){
            splitted_command[2]+=" "+splitted_command[3];

        }
        if(splitted_command[0] == "themes"){
            print_themes(themes_list);
        }

        else if (splitted_command[0] == "courses"){
            if(splitted_command.size() == 3)
            {
                print_courses_in_the_city(themes,splitted_command[1],splitted_command[2]);
            }
            else {
                cout << "Error: error in command courses" << endl;
            }
        }

        else if(splitted_command[0] == "available"){
            available_courses(themes);
        }
        //Toimii
        else if(splitted_command[0]=="courses_in_theme"){
            if(splitted_command.size() == 2)
            {
                if(themes.find(splitted_command[1]) != themes.end())
                {
                    courses_in_theme(themes,splitted_command[1]);
                }
                else {
                    cout << "Error: unknown theme" << endl;
                }
            }
            else {
                cout << "Error: error in command courses_in_theme" << endl;
            }
        }

        else if(splitted_command[0]=="favorite_theme"){
            favorite_theme(themes);

        }
        else if(splitted_command[0]=="courses_in_location"){
            if(splitted_command.size() == 2)
            {
                courses_in_location(themes, splitted_command[1]);
            }

            else {
                cout << "Error: error in command courses_in_location" << endl;
            }
        }

        else if(splitted_command[0]=="cancel"){
            if(splitted_command.size() == 2)
            {
                bool course_exist = is_course_in_map(themes, splitted_command[1]);
                if(course_exist != false)
                {
                    themes = cancel_course(themes, splitted_command[1]);
                }
                else {
                    cout << "Error: unknown course" << endl;
                }
            }

            else {
                cout << "Error: error in command cancel" << endl;
            }

        }
        else {
            cout << "Error: Unknown command: " << splitted_command[0] << endl;
        }

        cout << "> ";
        getline(cin,command);
    }

    return true;
}
//Erittäin lyhyt main
int main()
{
    bool success = handler();

    if(success)
    {
        return EXIT_SUCCESS;
    }

    else {
        return EXIT_FAILURE;
    }
}



