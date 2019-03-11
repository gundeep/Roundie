//
//  main.cpp
//  Round Round Roundie
//
//  Created by gundeep on 3/8/19.
//  Copyright © 2019 home. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <time.h>

using namespace std;

/* Co-ordinates Horizontal - X
 Vertical | Z
 */

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        
        return hash1 ^ hash2;
    }
};

unsigned int _BoardDimX = 0;
unsigned int _BoardDimZ = 0;

bool _WantToContinue = false;

using hashedPair = pair<unsigned int, unsigned int>;

using UnorderedMap = unordered_map<hashedPair, pair<bool,bool>, pair_hash>;

bool isRoundieInList(UnorderedMap *roundiesPosList, hashedPair posInBoard)
{
    UnorderedMap::iterator iter = roundiesPosList->find(posInBoard);
    
    bool result = false;
    result = (iter != roundiesPosList->end()) ? true:false;
    
    return result;
}

bool isRoundieUnhappy(UnorderedMap *roundiesPosList, hashedPair posInBoard)
{
    UnorderedMap::iterator iter = roundiesPosList->find(posInBoard);
    
    bool result = false;
    result = (iter != roundiesPosList->end()) ? true:false;
    
    if (result == true)
    {
        if (iter->second.first == true)
            return true;
    }
    return false;
}

bool isRoundieActive(UnorderedMap *roundiesPosList, hashedPair posInBoard)
{
    UnorderedMap::iterator iter = roundiesPosList->find(posInBoard);
    
    bool result = false;
    result = (iter != roundiesPosList->end()) ? true:false;
    
    if (result == true)
    {
        if (iter->second.second == true)
            return true;
    }
    return false;
}

void markRoundieActive(UnorderedMap *roundiesPosList, hashedPair posInBoard)
{
    for (auto iter = roundiesPosList->begin(); iter != roundiesPosList->end(); iter++)
    {
        if (iter->first == posInBoard)
        {
            iter->second.second = true;
        }
        else
        {
            iter->second.second = false;
        }
    }
    return;
}

void visualRepOfFlatWorld(unsigned int xDim, unsigned int zDim, UnorderedMap *roundiesPosList)
{
    cout<<endl;
    for (unsigned int a = xDim; a > 0; a--)
    {
        cout<<xDim-a <<"  ";
        for (unsigned int b = zDim; b > 0; b--)
        {
            bool roundiePlaced = false;
            hashedPair checkPosInList = {xDim - b, zDim - a};
            bool doesPositionExist = false;
            bool roundieUnhappy = false;
            bool roundieIsActive = false;
            
            doesPositionExist = isRoundieInList(roundiesPosList, checkPosInList);
            roundieUnhappy = isRoundieUnhappy(roundiesPosList, checkPosInList);
            roundieIsActive = isRoundieActive(roundiesPosList, checkPosInList);
            
            if (doesPositionExist)
            {
                if (roundieUnhappy)
                {
                    if (roundieIsActive)
                        printf("@|");
                    else
                        printf("x|");
                }
                else
                    printf("0|");
                
                roundiePlaced = true;
            }
            
            if (!roundiePlaced)
            {
                printf(" |");
            }
        }
        printf("\n");
    }
    cout<<endl;
}

int insertRoundie(unsigned int posX, unsigned int posZ, UnorderedMap *roundiesPosList)
{
    if (posX > _BoardDimX || posZ > _BoardDimZ)
    {
        cout<<"Roundie co-ordinates ("<<posX<<","<<posZ<<") not in range, try again!\n";
        return 0;
    }
    
    if (isRoundieInList(roundiesPosList, hashedPair(posX,posZ)))
    {
        cout<<"Position is not free! \n";
        return 0;
    }
    
    hashedPair tempPair = {posX, posZ};
    roundiesPosList->insert({tempPair, make_pair(false, false)});
    
    cout<<"Inserted Roundie at ("<<posX<<","<<posZ<<")\n";
    return 1;
}

void showCurrentBoardStatus(UnorderedMap *roundiesPosList)
{
    visualRepOfFlatWorld(_BoardDimX, _BoardDimZ, roundiesPosList);
}

void deleteRoundie(unsigned int posX, unsigned int posZ, UnorderedMap *roundiesPosList)
{
    if (posX > _BoardDimX || posZ > _BoardDimZ)
    {
        cout<<"Roundie co-ordinates ("<<posX<<","<<posZ<<") not in range, try again!\n";
        return;
    }
    
    hashedPair tempPair = {posX, posZ};
    //roundiesPosList->erase(std::remove(roundiesPosList->begin(), roundiesPosList->end(), tempPair), roundiesPosList->end());
    if (isRoundieInList(roundiesPosList, tempPair))
    {
        roundiesPosList->erase(tempPair);
    }
    else
        cout<<"No Roundie at ("<<posX<<","<<posZ<<")\n";
    
}

void markUnhappyRoundies(UnorderedMap *roundiesPosList)
{
    if (roundiesPosList->size() < 2)
    {
        cout<<"Need at least two roundies on board to mark unhappy ones";
        return;
    }
    
    cout << "Marking unhappy roundies in the flatworld.\n";
    
    for (auto iter = roundiesPosList->begin(); iter != roundiesPosList->end(); iter++)
    {
        auto iter2 = iter;
        iter2++;
        for (; iter2 != roundiesPosList->end(); iter2++)
        {
            int z2 = iter2->first.second;
            int z1 = iter->first.second;
            int x2 = iter2->first.first;
            int x1 = iter->first.first;
            
            double radians = atan2(z2 - z1, x2 - x1);
            double product = abs(cos(radians) * sin(radians));
            double epsilon = 0.001;
            
            if (product <= epsilon || product > 1 - epsilon || (product <= 0.5 + epsilon && product >= 0.5 - epsilon))
            {
                iter2->second.first = true;
                iter->second.first = true;
            }
        }
    }
}

void insertRandomRoundies(unsigned int numRandomRoundies, UnorderedMap *roundiesPosList)
{
    // Because of warning of implicit conversion losing precision.
    srand(static_cast<unsigned int>(time(NULL)));
    
    int X = rand() % _BoardDimX;
    int Z = rand() % _BoardDimZ;
    hashedPair posInBoard = {X, Z};
    
    for (int i = 0; i<numRandomRoundies; i++)
    {
        while (isRoundieInList(roundiesPosList, posInBoard)) {
            X = rand() % _BoardDimX;
            Z = rand() % _BoardDimZ;
            posInBoard = {X, Z};
        }
        insertRoundie(X, Z, roundiesPosList);
    }
}

void checkIfContinue(UnorderedMap *roundiesPosList)
{
    cout<<"Would you like to continue? \n";
    showCurrentBoardStatus(roundiesPosList);
    cin>>_WantToContinue;
    if (!_WantToContinue)
    {
        exit(0);
    }
}

void selectUnhappyRoundieToStart(unsigned int xPos, unsigned int zPos, UnorderedMap *roundiesPosList)
{
    // if the roundie is off the board and its still in the hashMap it dies.
    if (xPos >= _BoardDimX || zPos >= _BoardDimZ)
    {
        cout<< "Roundie Location enetered is out of the board \n";
        deleteRoundie(xPos, zPos, roundiesPosList);
        return;
    }
    
    if (!isRoundieUnhappy(roundiesPosList, hashedPair(xPos,zPos)))
    {
        cout<< "Not an unhappy roundie, quitting! \n";
        return;
    }
    
    for (auto iter = roundiesPosList->begin(); iter != roundiesPosList->end(); iter++)
    {
        // Ignore the current roundie itself.
        if (iter->first.first == xPos && iter->first.second == zPos)
            continue;
        
        int z1 = zPos;
        int z2 = iter->first.second;
        int x1 = xPos;
        int x2 = iter->first.first;
        
        // Returns the principal value of the arc tangent of z/x, expressed in radians.
        double radians = atan2(z2 - z1, x2 - x1);
        double product = abs(cos(radians) * sin(radians));
        //cout<<x2 << "  " << z2 <<"   "<< radians<<"  "<<product<<endl; //Debug
        
        double epsilon = 0.001;
        
        if (product <= epsilon || product > 1 - epsilon || (product <= 0.5 + epsilon && product >= 0.5 - epsilon))
        {
            // move in that direction
            cout<<"Moving in direction ("<<xPos<<","<<zPos<<") to ("<<iter->first.first<<","<<iter->first.second<<")\n";
            
            int xNew, zNew, lastRoundieX, lastRoundieZ;
            bool firstBallHasBeenHit = false;
            bool lastRoundieInitialized = false;
            
            for (unsigned radius = 1; ; radius++)
            {
                xNew = xPos + radius * round(cos(radians));
                zNew = zPos + radius * round(sin(radians));
                
                //cout << "Visiting xNew  " <<xNew << " zNew "<<zNew<<endl; // Debug updated positions.
                bool result = isRoundieUnhappy(roundiesPosList, hashedPair(xNew, zNew));
                
                if (result == true)
                {
                    cout<<"Collision! with ("<<xNew<<","<<zNew<<")\n";
                    markRoundieActive(roundiesPosList, hashedPair(xNew, zNew));
                    deleteRoundie(xPos, zPos, roundiesPosList);
                    checkIfContinue(roundiesPosList);
                    
                    iter->second.second = true;
                    if (firstBallHasBeenHit)
                    {
                        lastRoundieInitialized = true;
                        lastRoundieX = xNew;
                        lastRoundieZ = zNew;
                        continue;
                    }
                    firstBallHasBeenHit = true;
                    continue;
                }

                // Edge case when the roundie to start with is on the edge of the table and walks along the edge.
                if (((zPos != zNew) && zNew >= _BoardDimZ-1) ||
                    ((xPos != xNew) && xNew >= _BoardDimX-1) ||
                    ((zPos != zNew) && zNew <= 0) ||
                    ((xPos != xNew) && xNew <= 0))
                {
                    cout<<"Exiting because end of the board has been reached \n";
                    exit(0);
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    // Using Unordered map and not multimap, because there is only one roundie per location.
    UnorderedMap roundiesPosList;
    
    unsigned int unhappyX, unhappyZ, newX, newZ;
    
    cout<<"Enter board X dimension \n";
    cin>>_BoardDimX;
    cout<<"Enter board Z dimension \n";
    cin>>_BoardDimZ;

    insertRandomRoundies(7, &roundiesPosList);
    showCurrentBoardStatus(&roundiesPosList);
    
    do{
        cout<<"X co-ordinate of roundie you want to insert\n";
        cin>>newX;
        cout<<"Z co-ordinate of roundie you want to insert\n";
        cin>>newZ;
    }while (!insertRoundie(newX, newZ, &roundiesPosList));

    showCurrentBoardStatus(&roundiesPosList);
    
    markUnhappyRoundies(&roundiesPosList);
    showCurrentBoardStatus(&roundiesPosList);
    
    do {
    cout<<"X co-ordinate of unhappy roundie you want to start moving\n";
    cin>>unhappyX;
    cout<<"Z co-ordinate of unhappy roundie you want to start moving\n";
    cin>>unhappyZ;
    } while (!isRoundieUnhappy(&roundiesPosList, hashedPair(unhappyX,unhappyZ)));
    
    selectUnhappyRoundieToStart(unhappyX, unhappyZ, &roundiesPosList);
    
    return 0;
}
