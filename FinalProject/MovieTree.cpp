/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#include "MovieTree.h"
#include "BoxOfficeTree.h"
#include "AcademyAwardTree.h"
#include <iostream>
#include <fstream>  //allows istream/ostream
#include <stdlib.h> //allows atoi
#include <sstream>
#include<limits>


using namespace std;

MovieTree::MovieTree()
{
    root = NULL;
    int ranking;
    string title;
    string director;
    int year;
    string studio;
    string rankingSTR;
    string yearSTR;


    ifstream infile;
    infile.open("Top100Movies.txt");
    while(infile.good())
    {
        getline(infile, rankingSTR, '.');
        getline(infile, title, '.');
        getline(infile, director, '.');
        getline(infile, yearSTR, '.');
        getline(infile, studio);
        if(!infile)
        {
            break;
        }

        ranking = atoi(rankingSTR.c_str());
        year= atoi(yearSTR.c_str());

        /*cout << ranking << endl;
        cout <<  title << endl;
        cout <<  director << endl;
        cout <<  year <<endl;
        cout <<  studio << endl;
        cout << "-------------" << endl;*/

        addMovieNode(ranking, title, director, year, studio);

    }

}

MovieTree::~MovieTree()
{
    //cout << "Goodbye!" << endl;
    //DeleteAll(root);

}


//======================PRINT MOVIE INVENTORY=================================
void MovieTree::printMovieInventory()
{
    printMovieInventory(root);

}

void MovieTree::printMovieInventory(MovieNode *node)
{
    if(node->leftChild != NULL)
    {
        printMovieInventory(node->leftChild);
    }
    cout<<"Movie: "<< node->title <<endl;
    if(node->rightChild != NULL)
    {
        printMovieInventory(node->rightChild);
    }

}

//===============================ADD MOVIE NODE ============================================
void MovieTree::addMovieNode(int ranking, string title,string director, int releaseYear, string studio)
{
        MovieNode *tmp = root;
        MovieNode *parent = NULL;
        MovieNode *node = new MovieNode;
        node->leftChild = NULL;
        node->rightChild = NULL;
        node->parent = NULL;
        node->ranking = ranking;
        node->title = title;
        node->director = director;
        node->year = releaseYear;
        node->studio = studio;


    while(tmp != NULL)
        {
            parent = tmp;
            node -> parent = tmp;

                if(node->title.compare(tmp->title) < 0) //compare input value to root key
                {
                    tmp = tmp->leftChild;
                }
                else
                {
                    tmp = tmp->rightChild;
                }
        }

        //=========ADD to tree==============
            if (parent == NULL) //check if tree is empty
            {
                root = node;
            }
            else if(node->title.compare(node->parent->title) < 0) //if left < parent, add to left
            {
                parent->leftChild = node;
                node->parent = parent;

            }
            else //otherwise, add to right
            {
                parent->rightChild = node;
                node->parent = parent;

            }
}
//========================================FIND MOVE ============================================
void MovieTree::findMovie(string title)
{
    MovieNode *node = search(title);
    if(node != NULL )
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Director:" << node->director << endl;
        cout << "Year:" << node->year << endl;
        cout << "Studio:" << node->studio << endl;

    }
    else
    {
        cout << "Movie not found." << endl;
    }





}

MovieNode* MovieTree::search(string title)
{
    MovieNode *node;
    cout << "Enter title:" << endl;
    cin.clear();
    cin.ignore(100,'\n');
    getline(cin,title);

    node = root;

        while(node != NULL)
        {
            if (title.compare(node->title) < 0)
            {
               node = node->leftChild;
            }
            else if(title.compare(node->title) > 0)
            {
                node = node->rightChild;

            }
            else
            {
                 return node;
            }

        }

        return NULL;

}


//================================COUNT MOVIE NODES=================================
void MovieTree::countMovieNodes(MovieNode *node, int *c)
{
    if(node->leftChild != NULL)
    {
        countMovieNodes(node->leftChild, c);
    }
    *c = *c +1;
    if(node->rightChild != NULL)
    {
        countMovieNodes(node->rightChild, c);
    }
}

int MovieTree::countMovieNodes()
{
    int *c = new int;
    *c=0;
    countMovieNodes(root, c);
    return *c;

}


//==================================DELETE MOVIE NODE=========================================
void MovieTree::deleteMovieNode(string title)
{
   MovieNode *node = search(title);

    if(node!=NULL){
        if(node->leftChild == NULL && node->rightChild == NULL){
            //No Child
            if(node->parent!=NULL){
                if(node->parent->leftChild==node){
                    node->parent->leftChild = NULL;
                }else{
                    node->parent->rightChild = NULL;
                }
            }
            node=NULL;
        }else if(node->leftChild != NULL && node->rightChild != NULL){
            //Two Children
            MovieNode *minn;
            minn = treeMinimum(node->rightChild);
            if(minn == node->rightChild){
                node->leftChild->parent = minn;
                minn->leftChild = node->leftChild;
                if(node->parent!=NULL){
                    if(node->parent->leftChild == node){
                        node->parent->leftChild = minn;

                    }else{
                        node->parent->rightChild = minn;
                    }
                }
                minn->parent = node->parent;
                //node->parent->leftChild = minn;
                //minn->parent = node->parent;
                //node->leftChild->parent = minn;
                //minn->leftChild = node->leftChild;
            }else{
                minn->parent->leftChild = minn->rightChild;
                minn->rightChild->parent = minn->parent;
                if(node->parent!=NULL){
                    if(node->parent->leftChild == node){
                        node->parent->leftChild=minn;
                    }else{
                        node->parent->rightChild=minn;
                    }
                }
                minn->parent = node->parent;
                //node->parent->leftChild = minn;
                minn->leftChild = node->leftChild;
                minn->rightChild = node->rightChild;
                node->rightChild->parent = minn;
                node->leftChild->parent = minn;

            }

        }else{
            //One Child
            if(node->leftChild==NULL){
                MovieNode *x = node->rightChild;
                if(node->parent!=NULL){
                    if(node->parent->leftChild == node){
                        node->parent->leftChild = x;
                    }else{
                        node->parent->rightChild = x;
                    }
                }
                x->parent = node->parent;
            }else if(node->rightChild == NULL){
                MovieNode *x = node->leftChild;
                if(node->parent!=NULL){
                    if(node->parent->leftChild == node){
                        node->parent->leftChild = x;
                    }else{
                        node->parent->rightChild = x;
                    }
                }
                x->parent = node->parent;

            }
        }

    delete node;
    }
    //delete node;
    else{
        cout << "Movie not found." << endl;
    }

}


MovieNode* MovieTree::treeMinimum(MovieNode *node)
{
    while(node->leftChild != NULL)
    {
        node = node->leftChild;
    }
    return node;

}
MovieNode* MovieTree::searchAll(string title)
{
    MovieNode *node;
    node = root;

        while(node != NULL)
        {
            if (title.compare(node->title) < 0)
            {
               node = node->leftChild;

            }
            else if(title.compare(node->title) > 0)
            {
                node = node->rightChild;

            }
            else
            {
                 return node;
            }

        }

        return NULL;
}

string MovieTree::searchAllMovies(string title)
{
    MovieNode* node = searchAll(title);

    if(node != NULL)
    {
        return "Movie Found";
    }
    else
    {
        return "Movie NOT Found";
    }
}

MovieNode* MovieTree::searchByDirector(MovieNode *node, string director)
{
    if(node != NULL)
    {
        if(node->director == director)
        {
            cout << node->director << " directed " << node->title << " in " << node->year << endl;
            found = true;

        }

        searchByDirector(node->leftChild, director);
        searchByDirector(node->rightChild, director);

    }


}

void MovieTree::searchByDirector()
{
    string director;
    cout << "Enter your favorite director: " << endl;
    cin.clear();
    cin.ignore(100,'\n');
    getline(cin,director);
    cout << endl;
    cout << "Displaying all movies directed by " << director << "..." << endl;
    searchByDirector(root,director);
    if(found == false)
    {
        cout << "No Movies were found directed by " << director << "in the top 100 rated movie list." << endl;
    }
    else
    {
        found = false;
    }


}
/*
void MovieTree::director(){
	string director;
	cout<<"Enter the name of your favorite director: "<<endl;
	getline(cin, director);
	findDirector(director);
}
*/
void MovieTree::era(){
	int era =1;
	int upper;
	int lower;
	//while(era)
    //{
	cout<<"Which era would you like to see movies from?"<<endl;
	cout<<"1. 1930-1949"<<endl;
	cout<<"2. 1950-1959"<<endl;
	cout<<"3. 1960-1969"<<endl;
	cout<<"4. 1970-1979"<<endl;
	cout<<"5. 1980-1989"<<endl;
	cout<<"6. 1990-1999"<<endl;
	cout<<"7. 2000-2009"<<endl;
	cin>>era;
    /*while(!(cin >> era))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number between 1 and 7" << endl;
        break;

    }*/
	if (era==1){
		upper=1949;
		lower=1930;
		findEra(lower, upper);
	}
	else if (era==2){
		upper=1959;
		lower=1950;
		findEra(lower, upper);
	}
	else if (era==3){
		upper=1969;
		lower=1960;
		findEra(lower, upper);
	}
	else if (era==4){
		upper=1979;
		lower=1970;
		findEra(lower, upper);
	}
	else if (era==5){
		upper=1989;
		lower=1980;
		findEra(lower, upper);
	}
	else if (era==6){
		upper=1999;
		lower=1990;
		findEra(lower, upper);
	}
	else if (era==7){
		upper=2009;
		lower=2000;
		findEra(lower, upper);
	}
    else
    {
        cout << "Invalid Option"<< endl;

    }

}

void MovieTree::rank(){
	int rank;
	int u;
	int l;
	cout<<"What ranking of movie would you like to watch?"<<endl;
	cout<<"1. 1-10"<<endl;
	cout<<"2. 11-20"<<endl;
	cout<<"3. 21-35"<<endl;
	cout<<"4. 36-50"<<endl;
	cout<<"5. 51-65"<<endl;
	cout<<"6. 66-80"<<endl;
	cout<<"7. 81-100"<<endl;
	cin>>rank;

	if (rank==1){
		u=10;
		l=1;
	}
	else if (rank==2){
		u=20;
		l=11;
	}
	else if (rank==3){
		u=35;
		l=21;
	}
	else if (rank==4){
		u=50;
		l=36;
	}
	else if (rank==5){
		u=65;
		l=51;
	}
	else if (rank==6){
		u=80;
		l=66;
	}
	else if (rank==7){
		u=100;
		l=81;
	}
	else{
		cout<<"Invalid option"<<endl;
		return;
	}
	findRank(l, u);
}
/*
void MovieTree::checkNode(MovieNode *node, string director){
	if (node->leftChild!=NULL){
		checkNode(node->leftChild, director);
	}

	directorCompare(node, director);

	if (node->rightChild!=NULL){
		checkNode(node->rightChild, director);
	}
}*/
/*
void MovieTree::directorCompare(MovieNode *node, string director){

	if (node->director==director){
		cout<<node->title<<" "<<endl;
	}

	return;
}


void MovieTree::findDirector(string director){
	cout<<"Movies directed by "<<director<<": "<<endl;
	checkNode(root, director);
	return;
}
*/
void MovieTree::findEra(int lower, int upper){
	cout<<"Movies between "<<lower<<" and "<<upper<<": "<<endl;
	checkEra(root, lower, upper);
}

void MovieTree::checkEra(MovieNode *node, int lower, int upper){
	if (node->leftChild!=NULL){
		checkEra(node->leftChild, lower, upper);
	}

	if (node->year>=lower && node->year<=upper){
		cout<<node->title<<endl;
	}

	if (node->rightChild!=NULL){
		checkEra(node->rightChild, lower, upper);
	}
}

void MovieTree::findRank(int lower, int upper){
	cout<<"Movies with a top ranking between "<<lower<<" and "<<upper<<": "<<endl;
	checkRank( root,lower, upper);
	for (int i=lower;i<=upper;i++){
		cout<<order[i]->ranking<<". "<<order[i]->title<<endl;
	}
	//return;
}

void MovieTree::checkRank(MovieNode *node, int lower, int upper){
	if (node->leftChild!=NULL){
		checkRank(node->leftChild, lower, upper);
	}

	if (node->ranking>=lower && node->ranking<=upper){
		//cout<<node->ranking <<". "<<node->title<<endl;
		order[node->ranking]=node;
	}

	if (node->rightChild!=NULL){
		checkRank(node->rightChild, lower, upper);
	}
}


