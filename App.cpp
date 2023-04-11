#include "App.h"

#include <iostream>

#include "Bridges.h"
#include "DataSource.h"
#include "Menu.h"
#include "data_src/MovieActorWikidata.h"

using namespace std;
using namespace bridges;

App::App(vector<MovieActorWikidata> &movies_vector) {
    cout << "Got " << movies_vector.size() << " movies...\n";

    for (int i = 0; i < movies_vector.size(); i++) {
        movies_by_name[movies_vector[i].getMovieName()].insert(
            movies_vector[i].getActorName());
    }
}

void App::showAllMovies() {
    for (db_iter it = movies_by_name.begin(); it != movies_by_name.end();
         it++) {
        cout << it->first << endl;
        showActorsInAMovie(it);
    }
}

void App::showActorsInAMovie(const db_iter &movie_it) {
    for (set<string>::iterator it = movie_it->second.begin();it != movie_it->second.end(); it++) {
        cout << *it << endl;
    }
}

void App::getMovieNameAndShowActors() {
    string movie_name;
    cout << "Enter a movie name to see the list of actors: ";
    cin.ignore();
    getline(cin, movie_name);

    // Algorithm:
    // use find() on movies_by_name to search for movie_name.
    // if found, print out the actors.
    // else, print out a nice message saying the movie was not found.
}

void App::showAllMoviesForAnActor() {
    string actor_name;
    cout << "Enter an actor name to show all movies for that actor: ";
    cin.ignore();
    getline(cin, actor_name);

    // TODO:
    // Algorithm:
    // create a variable, movies_by_actor, that is a set of strings.
    // loop through movies_by_name.
    //   use find(actor_name) on the set of actors for each movie. (The set of
    //      actors is it->second).
    //   if found, add the movie name to movies_by_name. (the movie name is in
    //      it->first)

    // TODO:
    // loop through movies_by_actor and print out each item.
}

void App::run() {
    while (true) {
        char choice = getMenuChoice();
        if (choice == Menu::QUIT) {
            break;
        }
        perform(choice);
    }
}

void App::perform(char choice) {
    switch (choice) {
        case 'a':
            showAllMovies();
            break;
        case 'b':
            getMovieNameAndShowActors();
            break;
        case 'c':
            showAllMoviesForAnActor();
            break;
        default:
            cerr << "\n*** choice " << choice << " is not supported\n" << endl;
    }
}

char App::getMenuChoice() const {
    Menu menu;
    char choice;
    while (true) {
        cout << '\n' << menu << flush;
        cin >> choice;
        if (menu.containsChoice(choice)) {
            break;
        }
        cout << "\n*** " << choice << " is not supported!\n" << endl;
    }
    return choice;
}