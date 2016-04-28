/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#include "AcademyAwardTree.h"
#include "BoxOfficeTree.h"
#include "MovieTree.h"
#include <iostream>
#include <fstream>  //allows istream/ostream
#include <stdlib.h> //allows atoi
#include <sstream>
#include<limits>

using namespace std;

AcademyAwardTree::AcademyAwardTree()
{
    awardRoot = NULL;
    string title;
    int year;
    int wins;
    int nominations;

    string yearSTR;
    string winsSTR;
    string nominationsSTR;

    ifstream infile;
    infile.open("academyAwards.txt");
    while(infile.good())
    {
        getline(infile, title, '.');
        getline(infile, yearSTR, '.');
        getline(infile, winsSTR, '.');
        getline(infile, nominationsSTR);

        if(!infile)
        {
            break;
        }

        year = atoi(yearSTR.c_str());
        wins = atoi(winsSTR.c_str());
        nominations = atoi(nominationsSTR.c_str());

        /*cout <<  title << endl;
        cout <<  year <<endl;
        cout << wins << endl;
        cout << nominations << endl;
        cout << "-------------" << endl;*/

        addAcademyAwardNode(title, year, wins, nominations);

    }
    infile.close();
}

AcademyAwardTree::~AcademyAwardTree()
{
    //dtor
    //cout << "Goodbye!" << endl;
}


//======================PRINT MOVIE INVENTORY=================================
void AcademyAwardTree::printAcademyAwardInventory()
{
    printAcademyAwardInventory(awardRoot);

}

void AcademyAwardTree::printAcademyAwardInventory(AcademyAwardNode *node)
{
    if(node->leftChild != NULL)
    {
        printAcademyAwardInventory(node->leftChild);
    }
    cout<<"Movie: "<< node->title <<endl;
    if(node->rightChild != NULL)
    {
        printAcademyAwardInventory(node->rightChild);
    }

}


//===============================ADD MOVIE NODE ============================================
void AcademyAwardTree::addAcademyAwardNode(string title, int year, int wins, int nominations)
{
        AcademyAwardNode *tmp = awardRoot;
        AcademyAwardNode *parent = NULL;
        AcademyAwardNode *node = new AcademyAwardNode;
        node->leftChild = NULL;
        node->rightChild = NULL;
        node->parent = NULL;
        node->title = title;
        node->year = year;
        node->wins = wins;
        node->nominations = nominations;

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
                awardRoot = node;
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
AcademyAwardNode* AcademyAwardTree::findAcademyAwardMovie(string title)
{
    AcademyAwardNode *node = search(title);
    if(node != NULL )
    {
        if(node->genre == "")
        {
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year: " << node->year << endl;
            cout << "Wins: " << node->wins << endl;
            cout << "Nominations: " << node->nominations << endl;
            return node;
        }
        else
        {
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year: " << node->year << endl;
            cout << "Wins: " << node->wins << endl;
            cout << "Nominations: " << node->nominations << endl;
            cout << "Genre: " << node->genre << endl;
            return node;

        }

    }
    else
    {
        cout << "Movie not found." << endl;
        return NULL;
    }





}

AcademyAwardNode* AcademyAwardTree::search(string title)
{
    AcademyAwardNode *node;
    cout << "Enter title:" << endl;
    cin.clear();
    cin.ignore(100,'\n');
    getline(cin,title);

    node = awardRoot;

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
void AcademyAwardTree::countAcademyAwardNodes(AcademyAwardNode *node, int *c)
{
    if(node->leftChild != NULL)
    {
        countAcademyAwardNodes(node->leftChild, c);
    }
    *c = *c +1;
    if(node->rightChild != NULL)
    {
        countAcademyAwardNodes(node->rightChild, c);
    }
}

int AcademyAwardTree::countAcademyAwardNodes()
{
    int *c = new int;
    *c=0;
    countAcademyAwardNodes(awardRoot, c);
    return *c;

}


//==================================DELETE MOVIE NODE=========================================
void AcademyAwardTree::deleteAcademyAwardNode(string title)
{
   AcademyAwardNode *node = search(title);
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
            AcademyAwardNode *minn;
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
                AcademyAwardNode *x = node->rightChild;
                if(node->parent!=NULL){
                    if(node->parent->leftChild == node){
                        node->parent->leftChild = x;
                    }else{
                        node->parent->rightChild = x;
                    }
                }
                x->parent = node->parent;
            }else if(node->rightChild == NULL){
                AcademyAwardNode *x = node->leftChild;
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


AcademyAwardNode* AcademyAwardTree::treeMinimum(AcademyAwardNode *node)
{
    while(node->leftChild != NULL)
    {
        node = node->leftChild;
    }
    return node;

}

void AcademyAwardTree::searchByYear(AcademyAwardNode *node, int year)
{
    if(node != NULL)
    {
        if(node->year == year)
        {
            cout << node->title << " " << node->year << endl;
            found = true;
        }
        searchByYear(node->leftChild, year);
        searchByYear(node->rightChild, year);
    }

}

void AcademyAwardTree::searchByYear()
{
    int year;
    cout << "Enter what year of the Academy Awards you want to see between 1929-2015: " << endl;
    cin >> year;
    cout << endl;
    cout << "Displaying all Academy Award nominated films in " << year << "..." << endl;
    searchByYear(awardRoot,year);
    if(found == false)
    {
        cout << "This year is not in the list" << endl;

    }
    else
    {
        found = false;
    }

}

AcademyAwardNode* AcademyAwardTree::winnerSearch(AcademyAwardNode *node, int numAwards, int year1, int year2)
{
    if(node != NULL)
    {
        if(node->year >= year1 && node->year <= year2 && node->wins >= numAwards)
        {
            cout << node->title << " " << node->year << " " << node->wins << endl;
            return node;
        }
        winnerSearch(node->leftChild, numAwards, year1, year2);
        winnerSearch(node->rightChild, numAwards, year1, year2);
    }
    return NULL;


}
void AcademyAwardTree::winnerSearch()
{
    int numAwards;
    int year1;
    int year2;
    cout << "Enter minimum amount of awards won: " << endl;
    cin >> numAwards;
    cout << "Enter range of years you want to see: " << endl;
    cout << "Year 1: ";
    cin >> year1;
    cout << "Year 2: ";
    cin >> year2;
    AcademyAwardNode *node = winnerSearch(awardRoot,numAwards, year1, year2);

    if(node == NULL)
    {
        cout << "No movies found for your search" << endl;
    }

}

AcademyAwardNode* AcademyAwardTree::searchAll(string title)
{
    AcademyAwardNode *node;
    node = awardRoot;

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

string AcademyAwardTree::searchAllMovies(string title)
{
    AcademyAwardNode* node = searchAll(title);

    if(node != NULL)
    {
        return "Movie Found";
    }
    else
    {
        return "Movie NOT Found";
    }
}

void AcademyAwardTree::percentageWon(string title)
{
    AcademyAwardNode *node = search(title);
    if(node!= NULL)
    {

    double noms = node->nominations;
    double wins = node->wins;
    double percentage = wins/noms;
    percentage = percentage * 100;
    int percent = percentage;

    cout << "Wins: " << node->wins << endl;
    cout << "Nominations: " << node->nominations << endl;

    cout << node->title << " won " << percent << "% of the awards it was nominated for." << endl;
    }
    else
    {
        cout << "Movie Not Found" << endl;
    }
}

void AcademyAwardTree::addGenre(string title)
{
    AcademyAwardNode *node = findAcademyAwardMovie(title);
    string genre;

    if(node != NULL)
    {
        if(node->genre == "")
        {
            cout << "Enter Genre: ";
            cin >> genre;
            node->genre = genre;

            cout << endl;
            cout << "UPDATED NODE:" << endl;
            cout << endl;

            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year: " << node->year << endl;
            cout << "Wins: " << node->wins << endl;
            cout << "Nominations: " << node->nominations << endl;
            cout << "Genre: " << node->genre << endl;
        }
        else
        {
            cout << "This movie already has a genre assigned to it." << endl;
        }
    }
    else
    {
        cout << "Try again" << endl;
    }


}



