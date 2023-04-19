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

    // uses find() on movies_by_name to search for movie_name.
    // if found, prints out the actors. Otherwise, prints out error message.
    if (movies_by_name.find(movie_name) != movies_by_name.end()) {
        showActorsInAMovie(movies_by_name.find(movie_name));
    } else {
        cout << "Movie not found... " << endl;
    }
}

void App::showAllMoviesForAnActor() {
    string actor_name;
    cout << "Enter an actor name to show all movies for that actor: ";
    cin.ignore();
    getline(cin, actor_name);

    // loops through all movies, if a movie contains the actor, add the title to
    // the set movies_by_actor
    set<string> movies_by_actor;
    for (db_iter it = movies_by_name.begin(); it != movies_by_name.end();
         ++it) {
        if (it->second.find(actor_name) != it->second.end()) {
            movies_by_actor.insert(it->first);
        }
    }
    // prints out all movies in set
    for (set<string>::iterator it = movies_by_actor.begin();
         it != movies_by_actor.end(); ++it) {
        cout << *it << endl;
    }
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